#pragma once

#include <Stamina\DataTable\DT.h>
#include <Stamina\ObjectImpl.h>

#include "plug_func.h"
#include "core_tools.h"

#pragma pack(push, 1)

namespace Konnekt {

  /** 
   * @defgroup gr_msg Obs³uga wiadomoœci tekstowych.
   * @{
   */

  using Stamina::DT::tColId;

  /**
   * Struktura zosta³a ZAST¥PIONA przez #Message ! MessageOld jest binarnie zgodne z cMessage, ale nie powinno byæ u¿ywane
   *
   * @obsolete
   */
  class MessageOld {
  public:
    unsigned short _s_size;
    unsigned int _id;
    Net::tNet _net;             
    unsigned int _type;        
    char * _chFromUid;
    char * _chToUid;
    char * _chBody;
    char * _chExt;
    unsigned int _flag;
    struct sUIAction _action;
    unsigned int _notify;
    __int64 _time;

    MessageOld() {
      _s_size = sizeof(MessageOld);
      _id = 0;
      _net = Net::none;  
      _type = 0;
      _flag = 0;
      _notify = 0; 
      _action = sUIAction(0,0); 
      _chFromUid = _chToUid = _chBody = _chExt = "";
      _time = 0;
    }
  };

  /** 
   * Klasa s³u¿¹ca do obs³ugi wiadomoœci tekstowych. Zawiera wszystkie potrzebne deklaracje
   *
   * @attention Obiekt jest tylko kopi¹ wiadomoœci w kolejce...
   */
  class Message: protected MessageOld {
  public:
    /**  
     * Typy wiadomoœci tekstowych
     *
     * Do typu wiadomoœci mo¿na dodaæ bit #MT_MASK_NOTONLIST oznaczaj¹c tym samym, 
     * ¿e wiadomoœæ nie jest zwi¹zana z list¹ kontaktów.
     * Czêœæ typów ma ten bit ustawiony domyœlnie...
     */
    enum enType {
      typeAll             = -1,
      typeNone            = 0,
      typeMask_NotOnList  = 0x1000, ///< Oznacza ¿e ta wiadomosc nie zostanie wyœwietlona na liscie, ani nie zostanie sprawdzone czy docelowy kontakt na liœcie siê znajduje
      typeMask            = 0xFFF,  ///< Maskuje bity odpowiedzialne za sam typ wiadomoœci.

      typeMessage         = 1,      ///< Zwyk³a wiadomoœæ.
      typeQuickEvent      = 2,      ///< Krótka notka (kasowana automatycznie w kolejce) (np. wiadomoœæ nie dosz³a itp.)
      typeCntEvent        = 3,      ///< wydarzenie (np. ktoœ mnie doda³ do swojej listy itp.) zwi¹zane z kontaktem na liœcie
      typeEvent           = (typeCntEvent | typeMask_NotOnList),    ///< wydarzenie (np. ktoœ mnie doda³ do swojej listy itp.)
      typeServerEvent     = (4 | typeMask_NotOnList),    ///< Wiadomoœæ od serwera.
      typeAuthorize       = 5,      ///< Proœba o autoryzacje (ICQ).
      typeConference      = 6,      ///< Wiadomoœæ konferencyjna.
      typeFile            = 7,      ///< Przes³anie pliku.
      typeMail            = 8,      ///< Email.
      typeSMS             = 9,      ///< Np. potwierdzenie dotarcia sms'ów.
      typeSound           = 10,     ///< Rozmowa g³osowa.
      typeUrl             = (11 | typeMask_NotOnList),   ///< URL. Jako dodatkowe parametry w ext przyjmuje Width i Heigth

      typeSpecial         = 12,     ///< Nieokreslona wiadomosc.
      typeSpecial_NOL     = (13 | typeMask_NotOnList),   ///< Nieokreslona wiadomosc spoza listy.
      typeImage           = 15,     ///< Obraz, sciezka do pliku w cMessage::ext - #MEX_FILE_PATH
      typeBoard           = 16
    };

    /**
     * Flagi wiadomoœci tekstowych
     */
    enum enFlags {
      flagNone              = 0,
      flagSend              = 2,      ///< Wiadomoœæ przeznaczona do wys³ania
      flagNoEvents          = 4,      ///< #mtQuickEvent maj¹ nie byæ wysy³ane
      flagNoSave            = 8,      ///< Wiadomoœæ nie zostanie zapisana na dysk ...
      flagRequestOpen       = 0x10,   ///< #IM_MSG_OPEN / #IM_MSG_SEND zostanie wys³ane z #IMC_MESSSAGEQUEUE tylko gdy zostanie ono wywo³ane dla tego typu i sieci wiadomoœci.
      flagProcessing        = 0x20,   ///< Flaga wewnêtrzna oznaczaj¹ca ¿e wiadomoœæ jest w trakcie przetwarzania, Nie powinna byæ u¿ywana!
      flagOpened            = 0x40,   ///< Wiadomoœæ ju¿ zosta³a otwarta. Teraz czeka w kolejce na usuniêcie. Flaga ta jest czyszczona podczas zamykania.     
      flagHandled           = 0x40,   ///< Wiadomoœæ zosta³a w pe³ni obs³u¿ona i czeka na usuniêcie (to samo co flagOpened). Tyczy siê równie¿ wiadomoœci wysy³anych...
      flagHandledByUI       = 0x80,   ///< Wiadomoœæ zostanie obs³u¿ona przez UI
      flagAutomated         = 0x100,  ///< Wiadomoœæ zosta³a stworzona przez jakiœ "automatyczny" proces, wiêc, gdy jesteœmy ukryci, nie powinna byæ wysy³ana.
      flagHTML              = 0x200,  ///< Treœæ wiadomoœci zawiera znaczniki HTML, a znaki specjalne s¹ kodowane (przynajmniej > = &gt; < = &lt; i " = &quot; Html powinien byæ sformatowany jak XHTML (<img/>, wszystkie atrybuty w "" itd..)

      /**
       * Interfejs obs³u¿y wyœwietlanie wiadomoœci w menu.
       * Za ikonkê pos³u¿y cMessage::notify, nazwê pozycji w menu ustawiamy
       * w Ext jako parametr "ActionTitle". Je¿eli ustawiona jest cMessage::action
       * zostanie ona wys³ana po otwarciu wiadomoœci. W przeciwnym razie zostanie
       * wywo³ane IM_MSG_OPEN.
       * Wtyczka musi w #IM_MSG_RCV zadeklarowaæ obs³ugê wiadomoœci.
       */
      flagMenuByUI          = 0x400, 
      flagLeaveAsIs         = 0x800,    ///< Zabrania wtyczkom zmiany treœci, w tym wyœwietlania emotikon
      flagHide              = 0x1000,   ///< Nie wyœwietla wiadomoœci w interfejsie (w tej chwili w oknie rozmowy)
      flagDontAddToHistory  = 0x2000,   ///< Nie zapisuje w historii
      flagRemoved           = 0x4000,   ///< Wiadomoœæ zosta³a usuniêta, ale jest jeszcze przetwarzana (i wtedy zostanie usuniêta definitywnie)

      flagLoaded            = 0x8000,   ///< Wiadomoœæ zosta³a za³adowana z pliku (po ponownym uruchomieniu aplikacji)

      flag_QE_Normal        = 0x10000,  ///< MT_QUICKEVENT narysuje zwyk³¹ czcionk¹...
      flag_QE_ShowTime      = 0x20000,  ///< MT_QUICKEVENT poka¿e czas nadejœcia...
    };

  public:
    Message() {
      _s_size = sizeof(Message);
    }
    Message(const Message& msg);

    Message& operator = (const Message& msg);

    unsigned int structSize() const {
      return _s_size;
    }

    bool isStructV2() const {
      return structSize() >= sizeof(*this);
    }

    /** 
     * Identyfikator wiadomoœci.
     *
     * @attention ustawiany przez "rdzeñ". 
     */
    unsigned int getId() const {
      return _id;              
    }

    void setId(unsigned int id) {
      _id = id;
    }

    /** 
     * Sieæ wtyczek do których skierowana jest wiadomoœæ.
     */
    Net::tNet getNet() const {
      return _net;             
    }

    void setNet(Net::tNet net) {
      _net = net;
    }

    /** 
     * Typ wiadomoœci.
     */
    enType getType() const {
      return (enType) _type;
    }

    void setType(enType type) {
      _type = type;
    }

    ///< UID nadawcy.
    Stamina::String Message::getFromUid() const {
      return getObsoleteString(this->_fromUid, this->_chFromUid, this->isStructV2());
    }
    void Message::setFromUid(const Stamina::StringRef& uid) {
      setObsoleteString(uid, this->_fromUid, this->_chFromUid, this->isStructV2());
    }

    /// UID odbiorcy.
    Stamina::String getToUid() const {
      return getObsoleteString(this->_toUid, this->_chToUid, this->isStructV2());
    }
    void setToUid(const Stamina::StringRef& uid) {
      setObsoleteString(uid, this->_toUid, this->_chToUid, this->isStructV2());
    }

    /// UID odbiorcy wiadomoœci wysy³anej / nadawcy wiadomoœci przychodz¹cej
    Stamina::String getUid() const {
      if (isBeingSent()) {
        return getToUid();
      } else {
        return getFromUid();
      }
    }
    /// UID odbiorcy wiadomoœci wysy³anej / nadawcy wiadomoœci przychodz¹cej
    void setUid(const Stamina::StringRef& uid) {
      if (isBeingSent()) {
        setToUid(uid);
      } else {
        setFromUid(uid);
      }
    }

    /// Treœæ wiadomoœci.
    Stamina::String getBody() const {
      return getObsoleteString(this->_body, this->_chBody, this->isStructV2());
    }
    void setBody(const Stamina::StringRef& body) {
      setObsoleteString(body, this->_body, this->_chBody, this->isStructV2());
    }

    /** 
     * Informacje rozszerzone.
     * Zapisane jako 
     * @code 
     * #EXT_PARAM nazwa=wartoœæ #EXT_PARAM nazwa2=wartoœæ2
     * ...
     * @endcode
     * patrz: getExtParam() / setExtParam() .
     */
    Stamina::String getExt(bool refresh = false) const {
      return getObsoleteString(this->_ext, this->_chExt, this->isStructV2());
    }
    void setExt(const Stamina::StringRef& ext, bool store = false) {
      setObsoleteString(ext, this->_ext, this->_chExt, this->isStructV2());
    }

    Stamina::String getExtParam(const Stamina::StringRef& name, bool refresh = false) const {
      return ::GetExtParam(getExt(refresh), name);
    }
    void setExtParam(const Stamina::StringRef& name, const Stamina::StringRef& value, bool store = false) {
      setExt( ::SetExtParam(getExt(store), name, value), store );
    }

    /** 
     * Flagi wiadomoœci.
     */
    enFlags getFlags() const {
      return (enFlags) _flag;
    }

    void setFlags(enFlags flags) {
      _flag = flags;
    }

    bool getOneFlag(enFlags flag) const {
      return (_flag & flag) == flag;
    }

    void setOneFlag(enFlags flag, bool value) {
      setFlags( (enFlags) ((_flag & ~flag) | (value ? flag : 0)) );
    }

    /// Akcja powiadomienia dla wiadomoœci.
    struct sUIAction getAction() const {
      return _action;
    }

    void setAction(struct sUIAction act) {
      _action = act;
    }
    
    /// Akcja i ikonka powiadomienia dla wiadomoœci.
    unsigned int getNotify() const {
      return _notify;
    }

    void setNotify(unsigned int notify) {
      _notify = notify;
    }

    /// czas odebrania wiadomoœci w formacie zgodnym z Time64 (zapisane jako __int64).
    __int64 getTime() const {
      return _time;
    }

    void setTime(__int64 time) {
      _time = time;
    }

    bool isBeingSent() const {
      return getOneFlag(flagSend);
    }

    unsigned int getProcessingChainPos() const;
    bool isBeingProcessed() const;

    bool isRemoved() const {
      return getOneFlag(flagRemoved);
    }

    bool isAlreadyHandled() const {
      return getOneFlag(flagHandled);
    }

    /** 
     * Wczytuje wiadomoœæ z kolejki.
     */
    bool loadFromQueue(unsigned int msgId);

    /** 
     * Aktualizuje wiadomoœæ w kolejce.
     *
     * @warning Tylko dla wiadomoœci które ju¿ istniej¹ w kolejce!
     */
    bool saveToQueue();

    /** 
     * Dodaje wiadomoœæ do kolejki.
     *
     * @return ID wiadomosci
     */
    unsigned int addToQueue(bool runQueue, Controler* ctrl = 0);

    /** 
     * Próbuje przyj¹æ / rozes³aæ t¹ wiadomoœæ.
     */
    void runQueue(Controler* ctrl = 0);

    /** 
     * Usuwa wiadomoœæ z kolejki
     */
    void removeFromQueue();

    /** 
     * Oznacza wiadomoœæ jako przetworzon¹.
     *
     * Po skoñczeniu przetwarzania wiadomoœci, na któr¹ odpowiedzieliœmy flag¹ IM_MSG_processing wysy³amy ten komunikat, by rdzeñ "odznaczy³" nasz¹ wiadomoœæ. 
     * #IMC_MESSAGEPROCESSED wysy³a siê tylko, gdy wiadomoœæ nie zosta³a od razu usuniêta.
     */
    void setAsProcessed(bool setAsRemoved);

  public:
    /**
     * @defgroup mex_ Nazwy wartoœci w polach Message::getExtParam, MessageAck::getExtParam
     * @brief \no
     * @{
     */

    const static char* extAddInfo;
    const static char* extDisplay;
    const static char* extTitle;
    const static char* extNoSound; ///< Nie zostanie odegrany dŸwiêk
    const static char* extFile_Path;
    const static char* extFile_Size;
    const static char* extFile_Transfer_Time;
    const static char* extFile_Transfered;
    const static char* extFile_Error;

    /** @} */ // mex_

  public:
    /** 
     * Zwroty z IM_MSG_* 
     * #IM_MSG_RCV, #IM_MSG_SEND i #IM_MSG_OPEN mog¹ zwróciæ po³¹czone takie flagi.  
     */
    enum enMessageResult {
       resultOk     = 1, ///< Flaga zwrotna #resultRCV - Musi byæ ustawiona jesli wtyczka zamierza obs³u¿yæ wiadomoœæ.
       resultDelete = 2, ///< Wiadomoœæ powinna zostaæ niezw³ocznie usuniêta...
       resultUpdate = 4, ///< Zawartoœæ wiadomoœci zosta³a zmieniona i powinna zostaæ zaktualizowana jej kopia w kolejce.
       /** 
        * Flaga zwrotna #resultOPEN i #resultSEND - Wiadomoœæ jest dalej przetwarzana (np w osobnym w¹tku) i zostanie usuniêta z kolejki poprzez #IMC_MESSAGEREMOVE,
        * lub zakoñczy przetwarzanie poprzez #IMC_MESSAGEPROCESSED.
        */
       resultProcessing = 8
    };

    /** 
     * Struktura do przesy³ania komunikatów o wiadomoœciach.
     */
    class IM: public sIMessage_base {
    public:
      /** 
       * Obiekt wiadomoœci.
       */
      Message* msg;
      int param2;
      class iMessageHandler* handler;

      IM(tIMid IMid, Net::tNet net, enIMessageType type, Message* msg, int param2 = 0): sIMessage_base(IMid, net, type), msg(msg), param2(param2) {
        this->s_size = sizeof(*this);
      }

    public:
      static const tIMCid imcNewMessage = 100;
      static const tIMCid imcSetProcessed = 108;

      /** 
       * Komunikat przy którym wtyczka powinna sprawdziæ czy obs³uguje dany typ wiadomoœci (MessageIM*).
       * Wtyczki odpytywane s¹ "od koñca". Ostatnia, która zwróci
       * IM_MSG_RCV_ok bêdzie otrzymywaæ równie¿ IM_MSG_OPEN.
       *
       * @return (int) Po³¹czone flagi @ref im_msg_, lub 0 jeœli nie obs³uguje takich wiadomoœci.
       */
      static const tIMid imReceiveMessage = IM_BASE + 100;

       /** 
        * Wiadomoœæ powinna zostaæ wys³ana (MessageIM*).
        *
        * @return Jeœli siê uda³o powinno zróciæ enMessageResult.
        */
       static const tIMid imSendMessage = IM_SHARE + 100;
       
       /** 
        * Wiadomoœæ powinna zostaæ otwarta (MessageIM*).
        *
        * @return Jeœli siê uda³o powinno zróciæ enMessageResult.
        */
       static const tIMid imOpenMessage = IM_SHARE + 101;
    };

  public:
    // Msg
    const static tColId colId            = (unsigned int) 0; ///< #DT_CT_INT ID.
    const static tColId colNet           = 1;   ///< #DT_CT_INT Sieæ.
    const static tColId colType          = 2;   ///< #DT_CT_INT Typ.
    const static tColId colFromUid       = 3;   ///< #DT_CT_PCHAR Od UIDa (odebrana).
    const static tColId colToUid         = 4;   ///< #DT_CT_PCHAR Do UIDa (wysy³ana).
    const static tColId colBody          = 5;   ///< #DT_CT_PCHAR Treœæ.
    const static tColId colExt           = 6;   ///< #DT_CT_PCHAR Dodatkowe informacje.
    const static tColId colFlag          = 7;   ///< #DT_CT_INT Flaga.
    const static tColId colActionP       = 8;   ///< #DT_CT_INT | #DT_CF_NOSAVE  Grupa akcji.
    const static tColId colActionI       = 12;  ///< #DT_CT_INT | #DT_CF_NOSAVE Akcja.
    const static tColId colNotify        = 9;   ///< #DT_CT_INT | #DT_CF_NOSAVE  Ikonka powiadomienia.
    const static tColId colHandler       = 10;  ///< #DT_CT_INT | #DT_CF_NOSAVE Wtyczka obs³uguj¹ca.
    const static tColId colTime          = 11;  ///< #DT_CT_64 Czas jako cTime64 Czas odebrania/wys³ania.
    const static tColId colProcessing    = 13;

    // #define C_MSG_COLCOUNT                 14 // ostatni

  private:
    Stamina::String _fromUid;
    Stamina::String _toUid;
    Stamina::String _body;
    Stamina::String _ext;
  };

  typedef Message::enType tMsgType;
  typedef Message::enFlags tMsgFlags;
  typedef Message::enMessageResult tMsgResult;

  inline tMsgFlags operator | (tMsgFlags a, tMsgFlags b) {
    return (tMsgFlags) ((int) a | (int) b);
  }

  inline tMsgResult operator | (tMsgResult a, tMsgResult b) {
    return (tMsgResult) ((int) a | (int) b);
  }

  /** 
   * Klasa do wyszukiwania wiadomoœci.
   * Metody same wywo³uj¹ odpowiednie komunikaty
   */
  class MessageSelect {
  private:
    unsigned short _s_size;
  public:
    int net; ///< Sieæ kontaktu. Ustaw na #NET_BC aby u¿yæ wszystkich sieci.
  private:
    char * _chUid; ///< UID kontaktu. Ustaw 0 aby u¿yæ wszystkich.

  public:
    Stamina::String getUid() const {
      return getObsoleteString(this->_uid, this->_chUid, this->isStructV2());
    }
    void setUid(const Stamina::StringRef& uid) {
      setObsoleteString(uid, this->_uid, this->_chUid, this->isStructV2());
    }
    bool gotUid() const {
      return getUid().empty() == false;
    }

    unsigned int structSize() const {
      return _s_size;
    }

    bool isStructV2() const {
      return structSize() >= sizeof(*this);
    }

    Message::enType type;     ///< Typ wiadomoœci. Ustaw na -1 ¿eby u¿yæ wszystkich.
    Message::enFlags wflag;   ///< Tylko wiadomoœci posiadaj¹ce te flagi. 0 ¿eby u¿yæ wszystkich.
    Message::enFlags woflag;  ///< Tylko wiadomoœci nie posiadaj¹ce tych flag. 0 ¿eby u¿yæ wszystkich.
    int id;                   ///< ID wiadomoœci, -1 ¿eby u¿yæ wszystkich.
    unsigned int position;    ///< Które z kolei przyj¹æ dopasowanie?

    MessageSelect(Net::tNet net = Net::broadcast, const char * uid = 0, Message::enType type = Message::typeAll, Message::enFlags wflag = Message::flagNone, Message::enFlags woflag = Message::flagNone) {
      this->_s_size = sizeof(*this);
      this->net = net;
      this->_chUid = (char*) uid;
      this->_uid = uid;
      this->type = type;
      this->wflag = wflag;
      this->woflag = woflag;
      this->id = -1;
      this->position = 0;
    }

    const static unsigned int sizeV1 = 30;

  private:
    Stamina::String _uid;

  public:
    /** 
     * Struktura do przesy³ania komunikatów o wiadomoœciach.
     */
    class IM: public sIMessage_base {
    public:
      /** 
       * Obiekt wiadomoœci.
       */
      MessageSelect* select;
      int param2;

      IM(tIMid IMid, MessageSelect* select, int param2 = 0): sIMessage_base(IMid, Net::core, imtCore), select(select), param2(param2) {
        this->s_size = sizeof(*this);
      }

    public:
      static const tIMCid imcMessageQueue = 101;
      static const tIMCid imcMessageWaiting = 103;
      static const tIMCid imcMessageRemove = 104;
      static const tIMCid imcMessageGet = 106;
    };

  public:
    /** 
     * Sprawdza kolejkê wiadomoœci.
     * Próbuje przyj¹æ/rozes³aæ oczekuj¹ce wiadomoœci wg. podanych kryteriów.
     */
    void runQueue(Controler* ctrl = 0);

    /** 
     * Podaje ile wiadomoœci oczekuje w kolejce
     */
    int getCount();

    /** 
     * Usuwa wybrane wiadomoœci 
     */
    int removeFromQueue(unsigned int limit = -1);

    bool getMessage(Message&);
  };


  /**
   * Struktura do przekazywania informacji o stanie przesy³anych wiadomoœci.
   * Mo¿na ni¹ podawaæ jakie wyst¹pi³y problemy, lub co sta³o siê z wiadomoœci¹
   * po wys³aniu (np. czeka na serwerze, lub dosz³a do odbiorcy...)
   * @attention @a id @b musi byæ ustawiony na numer potwierdzanej i @b istniej¹cej wiadomoœci.
   * W miêdzyczasie wiadomoœæ ta nie mo¿e byæ usuniêta przez inny w¹tek.
   *
   * @sa @ref msg
   */
  class MessageAck {
  public:
    enum enFlags {
      flagFailed  = 0x1, ///< Wyst¹pi³ b³¹d
      flagProcessing = 0x2, ///< W trakcie przetwarzania

      /**
       * Ack nie zostanie rozes³ane do wtyczek #IMT_MESSAGEACK.
       * Przydatne, jeœli chcemy tylko zmieniæ informacjê pokazywan¹ w oknie kolejki.
       */
      flagNoBroadcast = 0x100, 

      flagImportant = 0x10, ///< Komunikat jest istotny, bêdzie pokazywany d³u¿ej
      flagVeryImportant = 0x20 ///< Komunikat jest bardzo istotny.
    };

  public:
    MessageAck() {
      _s_size = sizeof(*this);
    }

  protected:
    unsigned short _s_size;
  public:
    unsigned int id; ///< Identyfikator wiadomoœci któr¹ potwierdzamy.
  private:
    char * _chMsg; 
    char * _chExt; 
  public:
    enFlags flag; ///< Flagi @ref mack_.

    unsigned int structSize() const {
      return _s_size;
    }

    bool isStructV2() const {
      return structSize() >= sizeof(*this);
    }

    /** 
     * Tekst potwierdzenia. 
     */
    Stamina::String getMsg() const {
      return getObsoleteString(this->_msg, this->_chMsg, this->isStructV2());
    }
    void setMsg(const Stamina::StringRef& msg) {
      setObsoleteString(msg, this->_msg, this->_chMsg, this->isStructV2());
    }

    /** 
     * Dodatkowe parametry 
     */
    Stamina::String getExt(bool refresh = false) const {
      return getObsoleteString(this->_ext, this->_chExt, this->isStructV2());
    }
    void setExt(const Stamina::StringRef& ext, bool store = false) {
      setObsoleteString(ext, this->_ext, this->_chExt, this->isStructV2());
    }

    Stamina::String getExtParam(const Stamina::StringRef& name, bool refresh = false) const {
      return ::GetExtParam(getExt(refresh), name);
    }
    void setExtParam(const Stamina::StringRef& name, const Stamina::StringRef& value, bool store = false) {
      setExt( ::SetExtParam(getExt(store), name, value), store );
    }

  public:
    /** 
     * Rozsy³a powiadomienie.
     */
    void broadcastAck();

  protected:
    Stamina::String _msg;
    Stamina::String _ext;

  public:
    /** 
     * Struktura do przesy³ania komunikatów o wiadomoœciach.
     */
    class IM: public sIMessage_base {
    public:
      /** 
       * Obiekt wiadomoœci.
       */
      MessageAck* ack;
      int param2;

      IM(tIMid IMid, Net::tNet net, enIMessageType type, MessageAck* ack, int param2 = 0): sIMessage_base(IMid, net, type), ack(ack), param2(param2) {
        this->s_size = sizeof(*this);
      }

    public:
      static const tIMCid imcSendAck = 107;
      /** 
       * Komunikat docieraj¹cy do wtyczek o potwierdzeniu wiadomoœci (jako sIMessageParam).
       *
       * @param p1 (cMessageAck *) Potwierdzenie. ID jest ustawiony na ID potwierdzanej wiadomoœci (która jeszcze siedzi w kolejce i mo¿na j¹ odczytaæ).
       */
      static const tIMid imReceiveAck = IM_BASE + 102;
    };
  };

  inline MessageAck::enFlags operator | (MessageAck::enFlags a, MessageAck::enFlags b) {
    return (MessageAck::enFlags) ((int) a | (int) b);
  }

  // ------------------------------------------------------------------------------------------------

  /** @} */
  /** 
   * @addtogroup imc_ 
   * @{
   */

  /** 
   * Szuka powiadomienia o nowej wiadomoœci dla danego UIDa w kolejce wiadomoœci.
   * Wynik zapisywany jest w strukturze.
   * 
   * Podajemy w niej net i uid kontaktu i otrzymujemy action i notify s³u¿¹ce
   * do otwarcia tego typu wiadomoœci. Struktura jest przede wszystkim 
   * wykorzystywana przez UI do pokazywania odpowiednich ikonek przychodz¹cych wiadomoœci.
   */ 
  class MessageNotify {
  public:
    MessageNotify() {
      _s_size = sizeof(*this);
      id = 0;
    }

  protected:
    unsigned short _s_size;
  public:
    int net;          ///< Sieæ kontaktu.
  protected:
    char * _chUid;   
  public:
    sUIAction action; ///< Akcja otwieraj¹ca wiadomoœæ.
    int notify;       ///< Ikonka wiadomoœci.
    unsigned int id;  ///< Identyfikator wiadomoœci.

  protected:
    Stamina::String _uid;

  public:
    unsigned int structSize() const {
      return _s_size;
    }

    bool isStructV2() const {
      return structSize() >= sizeof(*this);
    }

    /** 
     * UID kontaktu
     */
    Stamina::String getUid() const {
      return getObsoleteString(this->_uid, this->_chUid, this->isStructV2());
    }
    void setUid(const Stamina::StringRef& uid) {
      setObsoleteString(uid, this->_uid, this->_chUid, this->isStructV2());
    }

  public:
    /** 
     * Struktura do przesy³ania komunikatów o wiadomoœciach.
     */
    class IM: public sIMessage_base {
    public:
      /** 
       * Obiekt wiadomoœci.
       */
      MessageNotify* notify;
      int param2;

      IM(tIMid IMid, MessageNotify* notify, int param2 = 0): sIMessage_base(IMid, Net::core, imtCore), notify(notify), param2(param2) {
        this->s_size = sizeof(*this);
      }

    public:
      static const tIMCid imcMessageNotify = 102;
    };

  public:
    /** 
     * Szuka powiadomienia o nowej wiadomoœci dla danego UIDa w kolejce wiadomoœci.
     * Wynik zapisywany jest w strukturze
     */
    void getNotification();
  };

  /**
   * Handler wiadomoœci
   */
  class iMessageHandler: public Stamina::iSharedObject {
  public:
    enum enMessageQueue {
      mqReceiveSend = 1,
      mqReceiveOpen = 2,
      mqReceive = mqReceiveSend | mqReceiveOpen,
      mqOpen = 4,
      mqSend = 8
    };

  public:
    /** 
     * Struktura do przesy³ania komunikatów o wiadomoœciach.
     */
    class IM: public sIMessage_base {
    public:
      iMessageHandler* handler;
      enPluginPriority priority;

      IM(tIMid IMid, iMessageHandler* handler, enPluginPriority priority): sIMessage_base(IMid, Net::core, imtCore), priority(priority) {
        this->s_size = sizeof(*this);
      }

    public:
      static const tIMCid imcRegisterMessageHandler = 109;
      static const tIMCid imcUnregisterMessageHandler = 110;
    };

  public:
    virtual tMsgResult handleMessage(Message* msg, enMessageQueue queue, enPluginPriority priority) = 0;
    virtual bool handlingMessage(enMessageQueue queue, Message* msg) = 0;

  private:
    virtual void zzPlaceHolder_iMsgHandler1() { }
    virtual void zzPlaceHolder_iMsgHandler2() { }
    virtual void zzPlaceHolder_iMsgHandler3() { }
    virtual void zzPlaceHolder_iMsgHandler4() { }
    virtual void zzPlaceHolder_iMsgHandler5() { }
  };

  class MessageHandler: public Stamina::SharedObject<iMessageHandler> {
  public:
    MessageHandler(enMessageQueue queue, tNet net = Net::all): _queue(queue), _net(net) { }

  public:
    bool registerHandler(enPluginPriority priority);
    bool unregisterHandler(enPluginPriority priority);

  public:
    virtual bool handlingMessage(enMessageQueue queue, Message* msg);

  protected:
    enMessageQueue _queue;
    tNet _net;
  };

  typedef Stamina::SharedPtr<iMessageHandler> oMessageHandler;

  // STAMINA_REGISTER_CLASS_VERSION(MessageHandler);
  // STAMINA_REGISTER_CLASS_VERSION(Message);
};

/** @} */
