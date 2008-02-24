#pragma once

#include <Stamina\DataTable\DT.h>
#include <Stamina\ObjectImpl.h>

#include "plug_func.h"
#include "core_tools.h"

#pragma pack(push, 1)

namespace Konnekt {

  /** 
   * @defgroup gr_msg Obs�uga wiadomo�ci tekstowych.
   * @{
   */

  using Stamina::DT::tColId;

  /**
   * Struktura zosta�a ZAST�PIONA przez #Message ! MessageOld jest binarnie zgodne z cMessage, ale nie powinno by� u�ywane
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
   * Klasa s�u��ca do obs�ugi wiadomo�ci tekstowych. Zawiera wszystkie potrzebne deklaracje
   *
   * @attention Obiekt jest tylko kopi� wiadomo�ci w kolejce...
   */
  class Message: protected MessageOld {
  public:
    /**  
     * Typy wiadomo�ci tekstowych
     *
     * Do typu wiadomo�ci mo�na doda� bit #MT_MASK_NOTONLIST oznaczaj�c tym samym, 
     * �e wiadomo�� nie jest zwi�zana z list� kontakt�w.
     * Cz�� typ�w ma ten bit ustawiony domy�lnie...
     */
    enum enType {
      typeAll             = -1,
      typeNone            = 0,
      typeMask_NotOnList  = 0x1000, ///< Oznacza �e ta wiadomosc nie zostanie wy�wietlona na liscie, ani nie zostanie sprawdzone czy docelowy kontakt na li�cie si� znajduje
      typeMask            = 0xFFF,  ///< Maskuje bity odpowiedzialne za sam typ wiadomo�ci.

      typeMessage         = 1,      ///< Zwyk�a wiadomo��.
      typeQuickEvent      = 2,      ///< Kr�tka notka (kasowana automatycznie w kolejce) (np. wiadomo�� nie dosz�a itp.)
      typeCntEvent        = 3,      ///< wydarzenie (np. kto� mnie doda� do swojej listy itp.) zwi�zane z kontaktem na li�cie
      typeEvent           = (typeCntEvent | typeMask_NotOnList),    ///< wydarzenie (np. kto� mnie doda� do swojej listy itp.)
      typeServerEvent     = (4 | typeMask_NotOnList),    ///< Wiadomo�� od serwera.
      typeAuthorize       = 5,      ///< Pro�ba o autoryzacje (ICQ).
      typeConference      = 6,      ///< Wiadomo�� konferencyjna.
      typeFile            = 7,      ///< Przes�anie pliku.
      typeMail            = 8,      ///< Email.
      typeSMS             = 9,      ///< Np. potwierdzenie dotarcia sms'�w.
      typeSound           = 10,     ///< Rozmowa g�osowa.
      typeUrl             = (11 | typeMask_NotOnList),   ///< URL. Jako dodatkowe parametry w ext przyjmuje Width i Heigth

      typeSpecial         = 12,     ///< Nieokreslona wiadomosc.
      typeSpecial_NOL     = (13 | typeMask_NotOnList),   ///< Nieokreslona wiadomosc spoza listy.
      typeImage           = 15,     ///< Obraz, sciezka do pliku w cMessage::ext - #MEX_FILE_PATH
      typeBoard           = 16
    };

    /**
     * Flagi wiadomo�ci tekstowych
     */
    enum enFlags {
      flagNone              = 0,
      flagSend              = 2,      ///< Wiadomo�� przeznaczona do wys�ania
      flagNoEvents          = 4,      ///< #mtQuickEvent maj� nie by� wysy�ane
      flagNoSave            = 8,      ///< Wiadomo�� nie zostanie zapisana na dysk ...
      flagRequestOpen       = 0x10,   ///< #IM_MSG_OPEN / #IM_MSG_SEND zostanie wys�ane z #IMC_MESSSAGEQUEUE tylko gdy zostanie ono wywo�ane dla tego typu i sieci wiadomo�ci.
      flagProcessing        = 0x20,   ///< Flaga wewn�trzna oznaczaj�ca �e wiadomo�� jest w trakcie przetwarzania, Nie powinna by� u�ywana!
      flagOpened            = 0x40,   ///< Wiadomo�� ju� zosta�a otwarta. Teraz czeka w kolejce na usuni�cie. Flaga ta jest czyszczona podczas zamykania.     
      flagHandled           = 0x40,   ///< Wiadomo�� zosta�a w pe�ni obs�u�ona i czeka na usuni�cie (to samo co flagOpened). Tyczy si� r�wnie� wiadomo�ci wysy�anych...
      flagHandledByUI       = 0x80,   ///< Wiadomo�� zostanie obs�u�ona przez UI
      flagAutomated         = 0x100,  ///< Wiadomo�� zosta�a stworzona przez jaki� "automatyczny" proces, wi�c, gdy jeste�my ukryci, nie powinna by� wysy�ana.
      flagHTML              = 0x200,  ///< Tre�� wiadomo�ci zawiera znaczniki HTML, a znaki specjalne s� kodowane (przynajmniej > = &gt; < = &lt; i " = &quot; Html powinien by� sformatowany jak XHTML (<img/>, wszystkie atrybuty w "" itd..)

      /**
       * Interfejs obs�u�y wy�wietlanie wiadomo�ci w menu.
       * Za ikonk� pos�u�y cMessage::notify, nazw� pozycji w menu ustawiamy
       * w Ext jako parametr "ActionTitle". Je�eli ustawiona jest cMessage::action
       * zostanie ona wys�ana po otwarciu wiadomo�ci. W przeciwnym razie zostanie
       * wywo�ane IM_MSG_OPEN.
       * Wtyczka musi w #IM_MSG_RCV zadeklarowa� obs�ug� wiadomo�ci.
       */
      flagMenuByUI          = 0x400, 
      flagLeaveAsIs         = 0x800,    ///< Zabrania wtyczkom zmiany tre�ci, w tym wy�wietlania emotikon
      flagHide              = 0x1000,   ///< Nie wy�wietla wiadomo�ci w interfejsie (w tej chwili w oknie rozmowy)
      flagDontAddToHistory  = 0x2000,   ///< Nie zapisuje w historii
      flagRemoved           = 0x4000,   ///< Wiadomo�� zosta�a usuni�ta, ale jest jeszcze przetwarzana (i wtedy zostanie usuni�ta definitywnie)

      flagLoaded            = 0x8000,   ///< Wiadomo�� zosta�a za�adowana z pliku (po ponownym uruchomieniu aplikacji)

      flag_QE_Normal        = 0x10000,  ///< MT_QUICKEVENT narysuje zwyk�� czcionk�...
      flag_QE_ShowTime      = 0x20000,  ///< MT_QUICKEVENT poka�e czas nadej�cia...
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
     * Identyfikator wiadomo�ci.
     *
     * @attention ustawiany przez "rdze�". 
     */
    unsigned int getId() const {
      return _id;              
    }

    void setId(unsigned int id) {
      _id = id;
    }

    /** 
     * Sie� wtyczek do kt�rych skierowana jest wiadomo��.
     */
    Net::tNet getNet() const {
      return _net;             
    }

    void setNet(Net::tNet net) {
      _net = net;
    }

    /** 
     * Typ wiadomo�ci.
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

    /// UID odbiorcy wiadomo�ci wysy�anej / nadawcy wiadomo�ci przychodz�cej
    Stamina::String getUid() const {
      if (isBeingSent()) {
        return getToUid();
      } else {
        return getFromUid();
      }
    }
    /// UID odbiorcy wiadomo�ci wysy�anej / nadawcy wiadomo�ci przychodz�cej
    void setUid(const Stamina::StringRef& uid) {
      if (isBeingSent()) {
        setToUid(uid);
      } else {
        setFromUid(uid);
      }
    }

    /// Tre�� wiadomo�ci.
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
     * #EXT_PARAM nazwa=warto�� #EXT_PARAM nazwa2=warto��2
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
     * Flagi wiadomo�ci.
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

    /// Akcja powiadomienia dla wiadomo�ci.
    struct sUIAction getAction() const {
      return _action;
    }

    void setAction(struct sUIAction act) {
      _action = act;
    }
    
    /// Akcja i ikonka powiadomienia dla wiadomo�ci.
    unsigned int getNotify() const {
      return _notify;
    }

    void setNotify(unsigned int notify) {
      _notify = notify;
    }

    /// czas odebrania wiadomo�ci w formacie zgodnym z Time64 (zapisane jako __int64).
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
     * Wczytuje wiadomo�� z kolejki.
     */
    bool loadFromQueue(unsigned int msgId);

    /** 
     * Aktualizuje wiadomo�� w kolejce.
     *
     * @warning Tylko dla wiadomo�ci kt�re ju� istniej� w kolejce!
     */
    bool saveToQueue();

    /** 
     * Dodaje wiadomo�� do kolejki.
     *
     * @return ID wiadomosci
     */
    unsigned int addToQueue(bool runQueue, Controler* ctrl = 0);

    /** 
     * Pr�buje przyj�� / rozes�a� t� wiadomo��.
     */
    void runQueue(Controler* ctrl = 0);

    /** 
     * Usuwa wiadomo�� z kolejki
     */
    void removeFromQueue();

    /** 
     * Oznacza wiadomo�� jako przetworzon�.
     *
     * Po sko�czeniu przetwarzania wiadomo�ci, na kt�r� odpowiedzieli�my flag� IM_MSG_processing wysy�amy ten komunikat, by rdze� "odznaczy�" nasz� wiadomo��. 
     * #IMC_MESSAGEPROCESSED wysy�a si� tylko, gdy wiadomo�� nie zosta�a od razu usuni�ta.
     */
    void setAsProcessed(bool setAsRemoved);

  public:
    /**
     * @defgroup mex_ Nazwy warto�ci w polach Message::getExtParam, MessageAck::getExtParam
     * @brief \no
     * @{
     */

    const static char* extAddInfo;
    const static char* extDisplay;
    const static char* extTitle;
    const static char* extNoSound; ///< Nie zostanie odegrany d�wi�k
    const static char* extFile_Path;
    const static char* extFile_Size;
    const static char* extFile_Transfer_Time;
    const static char* extFile_Transfered;
    const static char* extFile_Error;

    /** @} */ // mex_

  public:
    /** 
     * Zwroty z IM_MSG_* 
     * #IM_MSG_RCV, #IM_MSG_SEND i #IM_MSG_OPEN mog� zwr�ci� po��czone takie flagi.  
     */
    enum enMessageResult {
       resultOk     = 1, ///< Flaga zwrotna #resultRCV - Musi by� ustawiona jesli wtyczka zamierza obs�u�y� wiadomo��.
       resultDelete = 2, ///< Wiadomo�� powinna zosta� niezw�ocznie usuni�ta...
       resultUpdate = 4, ///< Zawarto�� wiadomo�ci zosta�a zmieniona i powinna zosta� zaktualizowana jej kopia w kolejce.
       /** 
        * Flaga zwrotna #resultOPEN i #resultSEND - Wiadomo�� jest dalej przetwarzana (np w osobnym w�tku) i zostanie usuni�ta z kolejki poprzez #IMC_MESSAGEREMOVE,
        * lub zako�czy przetwarzanie poprzez #IMC_MESSAGEPROCESSED.
        */
       resultProcessing = 8
    };

    /** 
     * Struktura do przesy�ania komunikat�w o wiadomo�ciach.
     */
    class IM: public sIMessage_base {
    public:
      /** 
       * Obiekt wiadomo�ci.
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
       * Komunikat przy kt�rym wtyczka powinna sprawdzi� czy obs�uguje dany typ wiadomo�ci (MessageIM*).
       * Wtyczki odpytywane s� "od ko�ca". Ostatnia, kt�ra zwr�ci
       * IM_MSG_RCV_ok b�dzie otrzymywa� r�wnie� IM_MSG_OPEN.
       *
       * @return (int) Po��czone flagi @ref im_msg_, lub 0 je�li nie obs�uguje takich wiadomo�ci.
       */
      static const tIMid imReceiveMessage = IM_BASE + 100;

       /** 
        * Wiadomo�� powinna zosta� wys�ana (MessageIM*).
        *
        * @return Je�li si� uda�o powinno zr�ci� enMessageResult.
        */
       static const tIMid imSendMessage = IM_SHARE + 100;
       
       /** 
        * Wiadomo�� powinna zosta� otwarta (MessageIM*).
        *
        * @return Je�li si� uda�o powinno zr�ci� enMessageResult.
        */
       static const tIMid imOpenMessage = IM_SHARE + 101;
    };

  public:
    // Msg
    const static tColId colId            = (unsigned int) 0; ///< #DT_CT_INT ID.
    const static tColId colNet           = 1;   ///< #DT_CT_INT Sie�.
    const static tColId colType          = 2;   ///< #DT_CT_INT Typ.
    const static tColId colFromUid       = 3;   ///< #DT_CT_PCHAR Od UIDa (odebrana).
    const static tColId colToUid         = 4;   ///< #DT_CT_PCHAR Do UIDa (wysy�ana).
    const static tColId colBody          = 5;   ///< #DT_CT_PCHAR Tre��.
    const static tColId colExt           = 6;   ///< #DT_CT_PCHAR Dodatkowe informacje.
    const static tColId colFlag          = 7;   ///< #DT_CT_INT Flaga.
    const static tColId colActionP       = 8;   ///< #DT_CT_INT | #DT_CF_NOSAVE  Grupa akcji.
    const static tColId colActionI       = 12;  ///< #DT_CT_INT | #DT_CF_NOSAVE Akcja.
    const static tColId colNotify        = 9;   ///< #DT_CT_INT | #DT_CF_NOSAVE  Ikonka powiadomienia.
    const static tColId colHandler       = 10;  ///< #DT_CT_INT | #DT_CF_NOSAVE Wtyczka obs�uguj�ca.
    const static tColId colTime          = 11;  ///< #DT_CT_64 Czas jako cTime64 Czas odebrania/wys�ania.
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
   * Klasa do wyszukiwania wiadomo�ci.
   * Metody same wywo�uj� odpowiednie komunikaty
   */
  class MessageSelect {
  private:
    unsigned short _s_size;
  public:
    int net; ///< Sie� kontaktu. Ustaw na #NET_BC aby u�y� wszystkich sieci.
  private:
    char * _chUid; ///< UID kontaktu. Ustaw 0 aby u�y� wszystkich.

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

    Message::enType type;     ///< Typ wiadomo�ci. Ustaw na -1 �eby u�y� wszystkich.
    Message::enFlags wflag;   ///< Tylko wiadomo�ci posiadaj�ce te flagi. 0 �eby u�y� wszystkich.
    Message::enFlags woflag;  ///< Tylko wiadomo�ci nie posiadaj�ce tych flag. 0 �eby u�y� wszystkich.
    int id;                   ///< ID wiadomo�ci, -1 �eby u�y� wszystkich.
    unsigned int position;    ///< Kt�re z kolei przyj�� dopasowanie?

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
     * Struktura do przesy�ania komunikat�w o wiadomo�ciach.
     */
    class IM: public sIMessage_base {
    public:
      /** 
       * Obiekt wiadomo�ci.
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
     * Sprawdza kolejk� wiadomo�ci.
     * Pr�buje przyj��/rozes�a� oczekuj�ce wiadomo�ci wg. podanych kryteri�w.
     */
    void runQueue(Controler* ctrl = 0);

    /** 
     * Podaje ile wiadomo�ci oczekuje w kolejce
     */
    int getCount();

    /** 
     * Usuwa wybrane wiadomo�ci 
     */
    int removeFromQueue(unsigned int limit = -1);

    bool getMessage(Message&);
  };


  /**
   * Struktura do przekazywania informacji o stanie przesy�anych wiadomo�ci.
   * Mo�na ni� podawa� jakie wyst�pi�y problemy, lub co sta�o si� z wiadomo�ci�
   * po wys�aniu (np. czeka na serwerze, lub dosz�a do odbiorcy...)
   * @attention @a id @b musi by� ustawiony na numer potwierdzanej i @b istniej�cej wiadomo�ci.
   * W mi�dzyczasie wiadomo�� ta nie mo�e by� usuni�ta przez inny w�tek.
   *
   * @sa @ref msg
   */
  class MessageAck {
  public:
    enum enFlags {
      flagFailed  = 0x1, ///< Wyst�pi� b��d
      flagProcessing = 0x2, ///< W trakcie przetwarzania

      /**
       * Ack nie zostanie rozes�ane do wtyczek #IMT_MESSAGEACK.
       * Przydatne, je�li chcemy tylko zmieni� informacj� pokazywan� w oknie kolejki.
       */
      flagNoBroadcast = 0x100, 

      flagImportant = 0x10, ///< Komunikat jest istotny, b�dzie pokazywany d�u�ej
      flagVeryImportant = 0x20 ///< Komunikat jest bardzo istotny.
    };

  public:
    MessageAck() {
      _s_size = sizeof(*this);
    }

  protected:
    unsigned short _s_size;
  public:
    unsigned int id; ///< Identyfikator wiadomo�ci kt�r� potwierdzamy.
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
     * Rozsy�a powiadomienie.
     */
    void broadcastAck();

  protected:
    Stamina::String _msg;
    Stamina::String _ext;

  public:
    /** 
     * Struktura do przesy�ania komunikat�w o wiadomo�ciach.
     */
    class IM: public sIMessage_base {
    public:
      /** 
       * Obiekt wiadomo�ci.
       */
      MessageAck* ack;
      int param2;

      IM(tIMid IMid, Net::tNet net, enIMessageType type, MessageAck* ack, int param2 = 0): sIMessage_base(IMid, net, type), ack(ack), param2(param2) {
        this->s_size = sizeof(*this);
      }

    public:
      static const tIMCid imcSendAck = 107;
      /** 
       * Komunikat docieraj�cy do wtyczek o potwierdzeniu wiadomo�ci (jako sIMessageParam).
       *
       * @param p1 (cMessageAck *) Potwierdzenie. ID jest ustawiony na ID potwierdzanej wiadomo�ci (kt�ra jeszcze siedzi w kolejce i mo�na j� odczyta�).
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
   * Szuka powiadomienia o nowej wiadomo�ci dla danego UIDa w kolejce wiadomo�ci.
   * Wynik zapisywany jest w strukturze.
   * 
   * Podajemy w niej net i uid kontaktu i otrzymujemy action i notify s�u��ce
   * do otwarcia tego typu wiadomo�ci. Struktura jest przede wszystkim 
   * wykorzystywana przez UI do pokazywania odpowiednich ikonek przychodz�cych wiadomo�ci.
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
    int net;          ///< Sie� kontaktu.
  protected:
    char * _chUid;   
  public:
    sUIAction action; ///< Akcja otwieraj�ca wiadomo��.
    int notify;       ///< Ikonka wiadomo�ci.
    unsigned int id;  ///< Identyfikator wiadomo�ci.

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
     * Struktura do przesy�ania komunikat�w o wiadomo�ciach.
     */
    class IM: public sIMessage_base {
    public:
      /** 
       * Obiekt wiadomo�ci.
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
     * Szuka powiadomienia o nowej wiadomo�ci dla danego UIDa w kolejce wiadomo�ci.
     * Wynik zapisywany jest w strukturze
     */
    void getNotification();
  };

  /**
   * Handler wiadomo�ci
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
     * Struktura do przesy�ania komunikat�w o wiadomo�ciach.
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
