/**
 * @file
 * Deklaracje wymagane do komunikacji pomiêdzy wtyczkami.
 */

/**
 * @defgroup gr_shared Komunikacja pomiêdzy wtyczkami.
 * 
 * Nag³ówek powinien byæ do³¹czony do kodu wtyczki poprzez plug_export.h.
 * @{
 */

#ifndef PLUGSHAREDH
#define PLUGSHAREDH

#define KONNEKT_SDK_V 2 ///< wydanie SDK

#pragma pack(push, 1)


#include "plug_defs.h"

#include "core_plugin.h"
#include "core_imessage.h"


using namespace Konnekt;


#ifndef _WINDOWS_
  #define HANDLE void *
  #define HINSTANCE void *
  #define HWND void *
#endif


#include "core_exception.h"


namespace Konnekt {
  class Message;
}


/** 
 * @defgroup gr_im Identyfikatory IMessage
 * 
 * Identyfikator jest @e nazw¹ przesy³anej #IMessage (wiadomoœci wewnêtrznej).
 * @par
 * Wiadomoœci dziel¹ siê na (pod wzglêdem przeznaczenia):
 *   - IMC_* @ref imc_ od 0 do 10000 #IMI_BASE
 *   - IMI_* @ref imi_ od 10000 #IMI_BASE do 20000 #IM_BASE
 *   - IM_*  @ref im_  od 20000 #IM_BASE do 0xFFFFFFFF
 *
 * @attention Wiadomoœci @ref imc_ dotr¹ @b tylko do @ref core "rdzenia". (niezale¿nie od wybranego @a net i @a type w IMessage())
 * @attention Wiadomoœci @ref imi_ dotr¹ @b tylko do @ref ui "UI". (niezale¿nie od wybranego @a net i @a type w IMessage())
 * @attention Wiadomoœci @ref im_ < #IM_SHARE mog¹ byæ wysy³ane @b tylko przez @ref core "rdzeñ" i @ref ui "ui".
 * @attention Wiadomoœci @ref im_ deklarowane przez u¿ytkownika powinny byæ tworzone jako #IM_USER + numer (numer najlepiej jako NET * 1000).
 * @attention Parametry podawane s¹ w kolejnoœci - P1, P2.
 * 
 * Wiadomoœci utworzone na potrzeby powstaj¹cych wtyczek powinny
 * byæ umieszczane w nazwa_wtyczki_shared.h tak, aby inni mogli
 * wykorzystywaæ API wtyczki.
 * 
 * @sa IMessageProc()
 * @{
*/

#define IMI_BASE 10000 ///< Od tej granicy zaczynaj¹ siê wiadomoœci do @ref ui "UI".
#define IM_BASE  20000 ///< Od tej granicy zaczynaj¹ siê wiadomoœci do @ref plug "wtyczek" wysy³ane tylko przez @ref core "rdzeñ" i @ref ui "UI".
#define IM_SHARE 30000 ///< Od tej granicy zaczynaj¹ siê wiadomoœci do @ref plug "wtyczek".
#define IM_USER  40000 ///< Od tej granicy zaczynaj¹ siê wiadomoœci do @ref plug "wtyczek" zdefiniowane przez u¿ytkownika.

/**
 * @defgroup im_ do Wtyczek
 * @{
*/

// Inicjalizacja DLL'a
#define IM_PLUG_NET           IM_SHARE + 10   ///< Zwraca wartoœæ NET wtyczki.
#define IM_PLUG_TYPE          IM_SHARE + 11   ///< Zwraca wartoœci IMT_ wtyczki.
#define IM_PLUG_VERSION       IM_SHARE + 12   ///< Zwraca opis wersji wtyczki.
#define IM_PLUG_SIG           IM_SHARE + 13   ///< Zwraca sygnaturê wtyczki.
#define IM_PLUG_CORE_V        IM_SHARE + 14   ///< Zwraca wymagan¹ sygnaturê rdzenia (lub 0).
#define IM_PLUG_UI_V          IM_SHARE + 15   ///< Zwraca wymagan¹ sygnaturê UI (lub 0).
#define IM_PLUG_NAME          IM_SHARE + 16   ///< Zwraca nazwê wtyczki.
#define IM_PLUG_NETNAME       IM_SHARE + 17   ///< Zwraca nazwê sieci obs³ugiwanej przez wtyczkê (wyœwietlan¹ w oknach dialogowych) (lub 0).
#define IM_PLUG_NETSHORTNAME  IM_SHARE + 25   ///< Zwraca skrócon¹ nazwê sieci (jak "ICQ", "GG", "JABBER"), aby umo¿liwiæ u¿ytkownikowi operowanie krótkimi nazwami sieci (np. przy tekstowym opisywaniu UIDów w parametrach) (lub 0).
#define IM_PLUG_UIDNAME       IM_SHARE + 26   ///< Zwraca nazwê UIDu typow¹ dla obs³ugiwanej sieci, do wyœwietlania w oknach dialogowych (np "JID", "UIN" itd...) (lub 0)
#define IM_PLUG_CERT          IM_BASE + 18    ///< Zastrze¿one dla wtyczek specjalnych.
#define IM_PLUG_INFO          IM_BASE + 19    ///< Wtyczka mo¿e zalogowaæ informacjê o swoim "stanie".
#define IM_PLUG_SDKVERSION    IM_BASE + 20    ///< Zwraca #KONNEKT_SDK_V.

/**
 * Wtyczka podaje swój priorytet w kolejkach (im wy¿szy, tym znajdzie siê wczeœniej).
 * Wszystkie "zwyk³e" wtyczki mog¹ nie obs³ugiwaæ tej wiadomoœci, lub po prostu zwracaæ 0 (ich priorytet zostanie ustawiony na #priorityStandard.
 * Dwie wtyczki o tym samym priorytecie ustawiane s¹ w kolejnoœci u¿ytkownika.
 * Je¿eli twoja wtyczka nie jest uzale¿niona od kolejnoœci, NIE ustawiaj jej!
 * Dziêki priorytetom wiadomoœci mog¹ byæ obs³ugiwane w odpowiedniej kolejnoœci.
 *
 * @return (enPluginPriority) pozycja
 */
#define IM_PLUG_PRIORITY  IM_BASE + 21

/**
 * Inicjalizacja wtyczki. Pierwszy przes³any IMessage nakazuj¹cy wtyczce inicjalizacjê kodu.
 * 
 * @param Controler adres struktury steruj¹cej
 * @param ID identyfikator wtyczki
 */
#define IM_PLUG_INIT      IM_BASE + 1

#define IM_PLUG_DEINIT    IM_BASE + 2      ///< Za chwilê uchwyt do wtyczki zostanie zwolniony. Najlepszy moment ¿eby posprz¹taæ.
#define IM_PLUG_INITEX    IM_BASE + 3      ///< Zastrze¿one dla wtyczek specjalnych.

/**
 * Podaje wtyczkom argumenty przes³ane do programu.
 * Wysy³ane jest zaraz po uruchomieniu, oraz gdy zostanie uruchomiona kolejna instancja programu na tym samym profilu. 
 * W drugim przypadku podawane s¹ argumenty przekazane do drugiej instancji...
 * Argumenty maj¹ t¹ sam¹ strukturê co __argc i __argv.
 * Komunikat przesy³any jest przy pomocy @b sIMessage_plugArgs.
 */ 
#define IM_PLUG_ARGS      IM_BASE + 24

/** 
 * Struktura u¿ywana w #IM_PLUG_ARGS.
 */
struct sIMessage_plugArgs: public sIMessage_base {
  unsigned int argc;          ///< Iloœæ argumentów w argv
  const char * const * argv;  ///< Tablica wskaŸników do argumentów

  sIMessage_plugArgs(unsigned int argc, const char * const * argv)
    :sIMessage_base(IM_PLUG_ARGS, Net::broadcast, imtAll), argc(argc), argv(argv) 
  {
    s_size = sizeof(*this);
  }

  const char * getArg(unsigned int i, const char * def = "") {
    return (i < this->argc) ? this->argv[i] : def;
  }
  bool argEq(unsigned int i, const char * cmp);
};

/** 
 * Przekazuje komendê wpisan¹ w oknie \@Dev. Komunikat przesy³any jest przy pomocy @b sIMessage_debugCommand. 
 * @return 0
 */
#define IM_DEBUG_COMMAND  IM_BASE + 25

/** 
 * Je¿eli podczas od³¹czania wtyczki z jakiegoœ wzglêdu nie powinno byæ wywo³ywane FreeLibrary trzeba obs³u¿yæ ten komunikat i zwróciæ 1.
 */
#define IM_PLUG_DONTFREELIBRARY   IM_BASE + 26

/** 
 * Wszystkie wtyczki zosta³y zainicjalizowane...
 */
#define IM_ALLPLUGINSINITIALIZED  IM_BASE + 22 

/** 
 * Za chwilê wtyczka o podanym ID zostanie od³¹czona.
 * @param p1 (int) ID wtyczki
 */
#define IM_PLUG_PLUGOUT     IM_BASE + 23     

/** 
 * Ta wersja wtyczki uruchamiana jest w tym profilu po raz pierwszy.
 *
 * @param p1 (int) Poprzednia wersja, lub 0. 
 *
 * @note Format wersji to w hexie: MNNRRBBB - Major, miNor, Release, Build.
 * W plug_func.h mo¿na znaleŸæ makra do szybkiego wyci¹gania tych wartoœci. 
 */
#define IM_PLUG_UPDATE      IM_BASE + 30     

/**
 * Je¿eli wtyczka obs³uguje sieæ, powinna zwróciæ swój aktualny status.
 *
 * @return (int) status
 */
#define IM_GET_STATUS       IM_SHARE + 31

/**
 * Je¿eli wtyczka obs³uguje sieæ, powinna zwróciæ swój aktualny opis statusu.
 * 
 * @return (const char *) opis statusu
 */
#define IM_GET_STATUSINFO   IM_SHARE + 32

/**
 * Je¿eli wtyczka obs³uguje sieæ, powinna zwróciæ UID u¿ytkownika programu w swojej sieci
 * 
 * @return (const char *) UID u¿ytkownika
 */
#define IM_GET_UID          IM_SHARE + 33

#define IM_NEW_PROFILE      IM_BASE + 40    ///< Oznacza pierwsze uruchomienie danego profilu. Najlepszy moment ¿eby siê przywitaæ.
#define IM_CANTQUIT         IM_BASE + 41    ///< Zwrócenie @e true spowoduje anulowanie zamykania programu.
#define IM_PASSWORDCHANGED  IM_BASE + 42    ///< Oznacza zmianê has³a dla profilu.

#define IM_THREADSTART      IM_BASE + 43    ///< Aktualny w¹tek w³aœnie zosta³ uruchomiony. Lepiej polegaæ jednak na DllMain!
#define IM_THREADEND        IM_BASE + 44    ///< Aktualny w¹tek w³aœnie siê koñczy. Lepiej polegaæ jednak na DllMain!

/**
 * Zapytanie o limit znaków na wiadomoœæ
 * 
 * @return Limit iloœci znaków na wiadomoœæ. 0 - bez limitu
 */
#define IM_MSG_CHARLIMIT    IM_BASE + 105

/*
 * --- Config (IMT_CONFIG) ---
 */

#define IM_SETCOLS          IM_BASE + 1001  ///< W tym momencie wtyczka powinna zadeklarowaæ wszystkie kolumny w tablicach.

#define IM_CFG_SAVE         IM_BASE + 1010  ///< Ustawienia zaraz zostan¹ zapisane do pliku.
#define IM_CFG_LOAD         IM_BASE + 1011  ///< Ustawienia zosta³y wczytane.
#define IM_CFG_CHANGED      IM_BASE + 1020  ///< Ustawienia zostaly zmienione przez u¿ytkownika.

/*
 * --- UI ---
 */
#define IM_UI_PREPARE       IM_BASE + 2000  ///< Najlepszy moment aby przygotowaæ interfejs (np zdefiniowaæ Akcje).
#define IM_START            IM_BASE + 2100  ///< Wtyczka powinna wystartowaæ.

/**
 * Wtyczka powinna zakoñczyæ dzia³anie.
 * @param p1 (bool) I powinna to zrobiæ jak najszybciej...
 */
#define IM_END              IM_BASE + 2101

/**
 * Za chwilê zostanie rozes³ane IM_END, ostatnia chwila, kiedy Controler::IsRunning() zwraca true.
 * @param p1 (bool) Zamykanie jest w trybie "natychmiastowym". Nale¿y wykonywaæ jak najmniej operacji...
 */
#define IM_BEFOREEND        IM_BASE + 2102

/**
 * Powiadomienie o zdarzeniu w akcji.
 * @param p1 (cUIActionNotify *) Powiadomienie.
 */
#define IM_UIACTION         IM_BASE + 2200

/*
 * --- IMT_PROTOCOL ---
 */

/**
 * Mo¿na zacz¹æ siê ³¹czyæ.
 * @param p1 (int) Liczba ponowionych prób po³¹czenia
 */
#define IM_CONNECT          IM_SHARE + 3000
#define IM_DISCONNECT       IM_SHARE + 3001   ///< Trzeba siê roz³¹czyæ.
#define IM_AWAY             IM_SHARE + 3002   ///< Program wchodzi w tryb Auto-Away.
#define IM_BACK             IM_SHARE + 3003   ///< Program powraca z trybu Auto-Away.

/**
 * Wysy³ana do kontrolek zaraz po w³¹czeniu
 * automatycznych po³¹czeñ i na chwilê przed
 * wykonaniem pierwszego testu na istnienie po³¹czenia.
 *
 * @attention W tej wiadomoœci #IMC_SETCONNECT
 * powinny wywo³ywac wtyczki które ZAWSZE potrzebuj¹ po³¹czeñ
 * (niezale¿nie od ustawienia #CFG_AUTOCONNECT).
 * Pozosta³e powinny zg³osiæ #IMC_SETCONNECT np. w #IM_PREPARE.
 */
#define IM_NEEDCONNECTION   IM_BASE + 3004

/**
 * Je¿eli wtyczka obs³uguje sieæ, powinna zmieniæ swój status...
 * 
 * @param p1 (int) status (lub -1 jeœli nie zmieniamy)
 * @param p2 (char*) opis (lub 0 jeœli nie zmieniamy)
 */
#define IM_CHANGESTATUS     IM_SHARE + 3005

#define IM_ISCONNECTED      IM_SHARE + 3006   ///< Trzeba zwróciæ 1 jeœli jesteœmy po³¹czeni.
#define IM_PING             IM_SHARE + 3007   ///< Wtyczka zamawia³a PING'a (na razie nie obs³ugiwane...)

/**
 * Informacje o kontakcie @a p1 zosta³y zmienione i moga byæ np. zapisane na serwerze.
 *
 * @param p1 (int) ID kontaktu do wys³ania
 * @param p2 (bool) 
 *   - 0 - info powinno byæ wczytywane bezpoœrednio z tabeli.
 *   - 1 - info powinno byæ ustawione jako wartoœci odpowiednich akcji w oknie z informacjami o kontakcie (u¿ywaj¹c UIActionCfgSetValue())
 */
#define IM_CNT_UPLOAD       IM_SHARE + 4000

/**
 * Informacje o kontakcie @a p1 powinny zostaæ zaktualizowane (np. pobrane z serwera).
 * 
 * @param p1 (int) ID kontaktu do pobrania
 * @param p2 (bool) 0 - info powinno zostaæ zapisane bezpoœrednio w tabeli. 
 */
#define IM_CNT_DOWNLOAD     IM_SHARE + 4001

/**
 * Kontakt zaraz zostanie usuniêty.
 *
 * @param p1 (int) ID kontaktu
 * @param p2 (bool) true - usuniêcie zosta³o potwierdzone przez uzytkownika.
 */
 #define IM_CNT_REMOVE      IM_BASE + 4002
 
/** 
 * Kontakt zosta³ usuniety.
 *
 * @param p1 (int) ID kontaktu
 * @param p2 (bool) true - usuniêcie zosta³o potwierdzone przez uzytkownika.
 */
#define IM_CNT_REMOVED      IM_BASE + 4005 

/**
 * Kontakt zosta³ dodany
 * @param p1 (int) ID kontaktu
 */
#define IM_CNT_ADD          IM_BASE + 4003

/**
 * Kontakt jest w trakcie tworzenia (które mo¿e zostaæ ew. przerwane)
 * Parametry kontaktu nie s¹ jeszcze ustalone.
 * @param p1 (int) ID kontaktu
 */
#define IM_CNT_ADDING       IM_BASE + 4004

/** 
 * ¯¹danie szukania kontaktu (np. w katalogu sieci)
 * @param p1 (sCNTSEARCH *) parametry wyszukiwania
 */
#define IM_CNT_SEARCH       IM_BASE + 4010

/** 
 * Któraœ z cech kontaktu (np. UID) zosta³a zmieniona. Przesy³ane przy pomocy sIMessage_CntChanged. 
 * Je¿eli przecastujesz to na sIMessage_2params to @a p1 jest ID kontaktu.
 */
#define IM_CNT_CHANGED      IM_BASE + 4006  

/** 
 * Struktura do przesy³ania #IM_CNT_CHANGED.
 */
struct sIMessage_CntChanged: public sIMessage_base {
  unsigned int _cntID; ///< ID kontaktu
  union {
    ///< Oznacza co zosta³o zmienione. 
    struct {
    unsigned net : 1;
    unsigned uid : 1;
    unsigned group : 1;
    } _changed; 
    unsigned int _changed_bitmap;
  };
  unsigned int _oldNet; ///< Poprzednia wartoœæ net tego kontaktu
  const char * _oldUID; ///< Poprzednia wartoœæ UID

  sIMessage_CntChanged(int msgID, int cntID): sIMessage_base(msgID), _cntID(cntID), _changed_bitmap(0), _oldNet(Net::none), _oldUID(0) {
    s_size = sizeof(*this);
  }
  sIMessage_CntChanged(const sIMessage_base * base) {
    if (base->s_size == sizeof(*this)) {
      *this = *(const sIMessage_CntChanged*) (base);
    } else if (base->s_size >= sizeof(sIMessage_2params)) {
      this->flag = base->flag;
      this->id = base->id;
      this->net = base->net;
      this->sender = base->sender;
      this->type = base->type;
      this->s_size = sizeof(*this);
      this->_cntID = ((const sIMessage_2params*) (base))->p1;
      this->_changed_bitmap = ((const sIMessage_2params*) (base))->p2;
      this->_oldNet = Net::none;
      this->_oldUID = 0;
    } else throw 0;
  }
};

/**
 * Status kontaktu zaraz ulegnie zmianie.
 * @return (sIMessage_StatusChange*)
 */
#define IM_CNT_STATUSCHANGE     IM_BASE + 4011

/** 
 * U¿ytkownik pisze wiadomoœæ do wskazanego kontaktu. Wys³ane do interfejsu spowoduje 
 * rozes³anie #IM_CNT_COMPOSING do wszystkich wtyczek i je¿eli w przeci¹gu kilkunastu 
 * sekund nie zostanie wys³ane ponownie, rozeœle #IM_CNT_COMPOSING_STOP.
 * 
 * @param p1 (int) ID kontaktu
 */
#define IM_CNT_COMPOSING        IM_SHARE + 4030

/** 
 * U¿ytkownik przesta³ pisaæ do wskazanego kontaktu.
 * Wys³ane do interfejsu spowoduje rozes³anie do wtyczek #IM_CNT_COMPOSING_STOP je¿eli w przeci¹gu
 * ostatnich kilkunastu sekund wyst¹pi³o zdarzenie #IM_CNT_COMPOSING z tym samym kontaktem.
 *
 * @param p1 (int) ID kontaktu
 */
#define IM_CNT_COMPOSING_STOP   IM_SHARE + 4031 

/**
 * Status wtyczki zaraz ulegnie zmianie.
 * @return (sIMessage_StatusChange*)
 */
#define IM_STATUSCHANGE         IM_BASE + 4012

/** 
 * Struktura do przesy³ania #IM_CNT_STATUSCHANGE i #IM_STATUSCHANGE.
 */
struct sIMessage_StatusChange: public sIMessage_base {
  union {
    unsigned int cntID; ///< ID kontaktu
    tPluginId plugID;   ///< ID wtyczki zmieniaj¹cej status.
  };
  unsigned int status;  ///< Nowy status, który zaraz zostanie ustawiony. -1 oznacza brak zmiany.
  const char * info;    ///< Nowy opis statusu, który zaraz zostanie ustawiony. 0 oznacza brak zmiany.

  sIMessage_StatusChange(int msgID, int cntID, unsigned int status, const char * info): sIMessage_base(msgID), cntID(cntID), status(status), info(info) {
    s_size = sizeof(*this);
  }
  sIMessage_StatusChange(const sIMessage_base * base) {
    if (base->s_size < sizeof(*this)) {
      throw KException_IM(base);
    }
    *this = *(sIMessage_StatusChange*) base;
    s_size = sizeof(*this);
  }
};


#define IM_GRP_CHANGED          IM_BASE + 4020  ///< Lista grup uleg³a zmianie.
/**
 * Lista ignorowanych kontaktów uleg³a zmianie.
 * 
 * @param p1 (int) sieæ > 0 - kontakt zosta³ dodany, < 0 - usuniêty
 * @param p2 (char*) 
 */
#define IM_IGN_CHANGED          IM_BASE + 4021

/**
 * Wtyczka sieciowa musi utworzyæ now¹ instancje obs³ugi protoko³u.
 * 
 * @param p1 (tAccountId) Identyfikator konta.
 */
#define IM_ACCOUNTINSTANCE_RUN          IM_BASE + 2050

/**
 * Wtyczka sieciowa musi zamkn¹æ instancjê obs³ugi protoko³u.
 * 
 * @param p1 (tAccountId) Identyfikator konta.
 */
#define IM_ACCOUNTINSTANCE_STOP         IM_BASE + 2060

/** 
 * Parametry wyszukiwania/wyniki wyszukiwania.
 * Struktura wykorzystywana zarówno podczas wysy³ania zapytania, jak i zwracania wyników.
 */
struct sCNTSEARCH {
  unsigned short s_size;  ///< Musi zawieraæ rozmiar struktury. Ustawiany przez kontruktor.
  int status;             ///< Podczas szukania - 1 - szukaj tylko online. Podczas zwracania - status kontaktu.
  char uid      [256]     ///< UID
     , name     [101]     ///< Imiê
     , surname  [101]     ///< Nazwisko
     , nick     [101]     ///< Ksywa
     , city     [51]      ///< Miasto
     , email    [101]     ///< Email
     , phone    [51]      ///< Telefon
     , other    [256]     ///< Inne (tylko w odpowiedzi)
  ;
  int gender;     ///< P³eæ 0 - nieznana, 1 - kobieta, 2 - mê¿czyzna
  int born_min;   ///< Urodzony, OD roku
  int born_max;   ///< Urodzony, DO roku
  int net;        ///< Numer sieci.
  /**
   * Od jakiej pozycji pokazywaæ dalej.
   * Przy zwracaniu, ostatni znaleziony kontakt powinien mieæ ustawiony @start
   * na pozycjê od której mo¿na wznowiæ wyszukiwanie.
   */
  int start;
  HANDLE handle;  ///< Uchwyt do okna wyszukiwania

  sCNTSEARCH() {
    s_size = sizeof(sCNTSEARCH);
    start = 0; handle = 0; net = 0; gender = 0; born_min = born_max = 0;
    uid[0] = 0;
    name[0] = 0;
    surname[0] = 0;
    nick[0] = 0;
    city[0] = 0;
    email[0] = 0;
    phone[0] = 0;
    other[0] = 0;
  }
};

#define sCNTSEARCH_V1           496

/** @} */  // Wiadomoœci do WTYCZEK

/**
 * @defgroup imc_ do Rdzenia
 * @{
 */

/**
 * Je¿eli program jest debugowany, zapisuje tekst w konnekt.log. 
 * Wiadomoœæ nie jest rozpoznawana przez Core (wiec ustawi blad!)
 *
 * @param p1 (char*) tekst.
 */
#define IMC_LOG                 1

/**
 * Zwraca nazwê profilu.
 * @return (char *)
 */
#define IMC_GETPROFILE          2

#define IMC_DEBUG               3     ///< Otwiera okno developera
#define IMC_ISDEBUG             4     ///< Zwraca true gdy jest w trybie developera.
#define IMC_ISBETA              9     ///< Zwraca true gdy jest w trybie beta.
#define IMC_BETA                40    ///< Otwiera okno beta-testera
#define IMC_REPORT              41    ///< Otwiera okno raportowania
#define IMC_PLUGS               42    ///< Otwiera okno wtyczek

/**
 * Pobiera ³¹czn¹ wartoœæ flag typów (#IM_PLUG_TYPE) ze wszystkich wtyczek danej sieci.
 * @param p1 (int) sieæ
 */
#define IMC_NET_TYPE            43

/** 
 * Zwraca identyfikator sesji profilu Konnekta.
 * Przy jego pomocy mo¿na odró¿niæ dwie instancje korzystaj¹ce z ró¿nych profili...
 * @return (const char*) identyfikator sesji (MD5 œcie¿ki katalogu profilu)
 */
#define IMC_SESSION_ID          44

/** 
 * Zwraca globalny uchwyt sesji WinInet otwartej przez InternetOpen (z ustawionym Proxy wg. konfiguracji). 
 * @return (HINTERNET) uchwyt, NIE mo¿na go zamykaæ!
 */
#define IMC_GET_HINTERNET       45

/**
 * Tworzy i zwraca uchwyt sesji WinInet otwartej przez InternetOpen (z ustawionym Proxy wg. konfiguracji).
 *
 * @param p1 (const char*) UserAgent
 * @return (HINTERNET) uchwyt, trzeba go zamykaæ!
 */
#define IMC_HINTERNET_OPEN      46

/**
 * Zwraca uchwyt do g³ównego w¹tku.
 * @return (HANDLE)
 */
#define IMC_GET_MAINTHREAD      47 
#define IMC_DEBUG_COMMAND       48

struct sIMessage_debugCommand: public sIMessage_plugArgs {
  enum enAsync {
    synchronous = 0,
    duringAsynchronous = 1,
    asynchronous = 2
  } async;

  sIMessage_debugCommand(unsigned int argc, const char * const * argv, enAsync async = synchronous)
    : sIMessage_plugArgs(argc, argv), async(async) 
  {
    id = IMC_DEBUG_COMMAND;
    net = Net::none;
    type = imtNone;
    s_size = sizeof(*this);
  }
};


/**
 * Zwraca liczbê parametrów przekazanych do programu.
 */
#define IMC_ARGC                5

/**
 * Zwraca parametr @a p1.
 * 
 * @param p1 (int) numer parametru
 * @return (char*) 
 */
#define IMC_ARGV                6

#define IMC_ISWINXP             60    ///< Zwraca 1, jeœli korzystamy z ComCtl6 na winXP.
#define IMC_ISNEWPROFILE        61    ///< Zwraca 1, gdy jest to pierwsze uruchomienie na tym profilu.  

/**
 * Zwraca 1, gdy jest to pierwsze uruchomienie na nowej wersji.
 *
 * @warning Wynik jest ma³o miarodajny i mo¿e byæ fa³szywy! Wiarygodne wyniki
 * zostan¹ przes³ane w IM_PLUG_UPDATE
 */
#define IMC_ISNEWVERSION        62
#define IMC_CONNECTED           7     ///< Zwraca true, jeœli jesteœmy pod³¹czeni do internetu.

/**
 * Zwraca wersjê rdzenia.
 * 
 * @param p1 (char *) WskaŸnik do ci¹gu znaków do zapisania wersji tekstowo, lub NULL.
 * @return (int) #VERSION_TO_NUM
 */
#define IMC_VERSION             8

/**
 * Zamyka program.
 * @param p1 (bool) Czy zamkn¹æ go natychmiastowo?
 */
#define IMC_SHUTDOWN            10

#define IMC_DISCONNECT          11    ///< Roz³¹cza wszystkie wtyczki z sieci.
#define IMC_RESTART             17    ///< Restartuje program.

/**
 * Œcie¿ka do katalogu z profilami.
 * @return (const char *)
 */
#define IMC_PROFILESDIR         23

/**
 * Œcie¿ka do katalogu z profilem.
 * @return (const char *)
 */
#define IMC_PROFILEDIR          12

/**
 * Przywrca aktywn¹ œcie¿kê na katalog programu i j¹ zwraca.
 * @return (const char *) katalog z programem    
 */
#define IMC_RESTORECURDIR       24
/**
 * @sa #IMC_RESTORECURDIR
 */
#define IMC_KONNEKTDIR          IMC_RESTORECURDIR
#define IMC_GETBETALOGIN        25 
#define IMC_GETBETAPASSMD5      27 
#define IMC_GETBETAANONYMOUS    31

/** 
 * Zwraca "numer seryjny" instalacji Konnekta, losowa liczba u¿ywana 
 * najczêœciej do rozró¿niania kopii programu w statystykach.
 */
#define IMC_GETSERIALNUMBER     33

/**
 * Zwraca œcie¿kê do katalogu z logami.
 * @return (char*) œcie¿ka zakoñczona '\\'
 */
#define IMC_LOGDIR              29

/**
 * Zwraca œcie¿kê do katalogu tymczasowego.
 * @return (char*) œcie¿ka zakoñczona '\\'
 */
#define IMC_TEMPDIR             32

/**
 * Zmienia/tworzy profil.
 *
 * @param p1 (char*) nazwa
 * @param p2 (bool) true jeœli profil ma byæ utworzony
 *
 * @return true jeœli siê uda³o
 */
#define IMC_PROFILECHANGE       13
#define IMC_PROFILEREMOVE       14    ///< Usuwa aktualnie u¿ywany profil.
#define IMC_PROFILEPASS         15    ///< Otwiera okno do ustawiania has³a.

/**
 * Zwraca has³o profilu jako MD5Digest.
 * @param p1 (unsigned char [16]) bufor do zapisania.
 */
#define IMC_GETMD5DIGEST        16

#define IMC_SAVE_CFG            20    ///< Zapisuje ustawienia na dysk.
#define IMC_SAVE_CNT            21    ///< Zapisuje kontakty na dysk.
#define IMC_SAVE_MSG            22    ///< Zapisuje kolejkê wiadomoœci na dysk.
#define IMC_CFG_CHANGED         28

/**
 * Ustawia wtyczkê na liœcie "rz¹danych po³¹czeñ".
 * W chwili wykrycia po³¹czenia z internetem, 
 * lub gdy jest po³¹czenie po kilkudziesiêciu sekundach
 * zostanie wys³any do wtyczki komunikat #IM_CONNECT.
 *
 * @param p1 (bool) stan
 *   - 1 - ³¹cz
 *   - 0 - przestañ próbowaæ
 */
#define IMC_SETCONNECT          30

#define IMC_THREADSTART         50    ///< Wiadomoœæ wykorzystywana TYLKO przez UI
#define IMC_THREADEND           51    ///< Wiadomoœæ wykorzystywana TYLKO przez UI

/** 
 * Znak parametru.
 * W Message i MessageAck mo¿emy podawaæ listê dodatkowych parametrów.
 * Ka¿dy parametr sk³ada siê z po³¹czonych: #EXT_PARAM nazwy '=' wartoœci
 * Dziêki zastosowaniu nietypowego znaku, unikamy potrzeby escape'owania znaków.
 * Nazwa mo¿e byæ dowolnym ci¹giem znaków z wyj¹tkiem znaków #EXT_PARAM, '=' i \\0.
 * Wartoœæ mo¿e byæ dowolnym ci¹giem znaków z wyj¹tkiem znaków #EXT_PARAM i \\0.
 * Nazwa jest case-sensitive.
 * 
 * Najlepiej u¿ywaæ gotowych f-cji zadeklarowanych w plug_func.h:
 * GetExtParam() i SetExtParam().
 */
#define EXT_PARAM               "\x1A" 
#define EXT_PARAM_CHAR          char(0x1A)


/** 
 * Zwraca ID kontaktu.
 * Je¿eli @a net bêdzie ustawiony na NET_NONE w UID mo¿na przekazaæ (tekstem) ID kontaktu. 
 * Je¿eli kontakt o danym ID istnieje, ID zostanie zwrócone. Funkcjonalnoœæ ta mo¿e s³u¿yæ g³ównie do 
 * "przemycania" bezpoœrednich identyfikatorów kontaktów do f-cji które przyjmuj¹ tylko wartoœci net i uid.
 * 
 * @param p1 (int) net
 * @param p2 (char*) UID
 * @return (int) ID
 */
#define IMC_FINDCONTACT         200 
#define IMC_PLUG_COUNT          240   ///< Zwraca liczbê wtyczek.

/**
 * Zwraca windowsowy uchwyt do wtyczki.
 * 
 * @param p1 (int) pozycja na liœcie wtyczek.
 * @return (int) HINSTANCE
 */
#define IMC_PLUG_HANDLE         241

/**
 * Zwraca ID wtyczki.
 * 
 * @param p1 (int) pozycja na liœcie wtyczek.
 * @return (int) ID
 */
#define IMC_PLUG_ID             243

/**
 * Zwraca œcie¿kê do pliku dll wtyczki.
 * 
 * @param p1 (int) pozycja na liœcie wtyczek.
 * @return (char*) œcie¿ka
 */ 
#define IMC_PLUG_FILE           242

/**
 * Zwraca windowsowy uchwyt do wtyczki.
 * 
 * @param p1 (int) ID wtyczki.
 * @return (HINSTANCE) uchwyt
 */
#define IMC_PLUGID_HANDLE       244

/**
 * Zwraca pozycjê wtyczki.
 * 
 * @param p1 (int) ID wtyczki.
 * @return (int) pozycja
 */
#define IMC_PLUGID_POS          245

/**
 * Zwraca ID wtyczki.
 * 
 * @param p1 (int) NET wtyczki.
 * @param p2 (int) Szukane flagi IMT_.
 * 
 * @return (int) ID
 */
#define IMC_FINDPLUG            247

/**
 * Zwraca ID wtyczki.
 * 
 * @param p1 (char*) SIG.
 * @return (int) ID
 */
#define IMC_FINDPLUG_BYSIG      248

/**
 * Zwraca ID wtyczki.
 * 
 * @param p1 (char*) name.
 * @return (int) ID
 */
#define IMC_FINDPLUG_BYNAME     249

/**
 * Zwraca wersjê wtyczki.
 * 
 * @param p1 (int) Pozycja wtyczki na liœcie, lub -1 aby sprawdziæ wersjê rdzenia.
 * @param p2 (char *) WskaŸnik do ci¹gu znaków do zapisania wersji tekstowo, lub NULL.
 * 
 * @return (int) #VERSION_TO_NUM
 */
#define IMC_PLUG_VERSION        26

/**
 * Dodaje wirtualn¹ wtyczkê.
 */
struct sIMessage_plugVirtualAdd : public sIMessage_base {
  const static int __msgID = 253;

  void* _object;
  void* _proc;
  tPluginId _plugId;

  sIMessage_plugVirtualAdd(void* object, void* proc, tPluginId plugId = pluginNotFound) : 
    sIMessage_base(__msgID), _object(object), _proc(proc), _plugId(plugId) 
  {
    s_size = sizeof(*this);
  }
};

/** 
 * Od³¹cza wtyczkê o podanym identyfikatorze podaj¹c opowiednie uzasadnienie.
 */
struct sIMessage_plugOut : public sIMessage_base {
  const static int __msgID = 250;

  tPluginId _plugId;
  const char * _reason;

  enum enRestart {
    erNo,
    erAsk,
    erYes,
    erAskShut,
    erShut
  } _restart;   ///< Czy restartowaæ program?

  enum enUnload {
    euNow = 1,  /// Nie powinno byæ ustawiane póŸniej ni¿ w #IMI_ALLPLUGSINITIALIZED
    euNextStart,
    euNowAndOnNextStart
  } _unload;    ///< Kiedy j¹ od³¹czyæ?

  sIMessage_plugOut(unsigned int plugId, const char* reason, enRestart restart = erAsk, enUnload unload = euNextStart) : 
    sIMessage_base(__msgID), _plugId((tPluginId) plugId), _reason(reason), _restart(restart), _unload(unload) 
  {
    s_size = sizeof(*this);
  }
};


/**
 * Informuje rdzeñ, ¿e za chwilê nast¹pi zmiana statusu wtyczki.
 * Rdzeñ rozsy³a #IM_STATUSCHANGE.
 * 
 * @warning Ten komunikat trzeba wys³aæ PRZED zmian¹ statusu, nie trzeba podawaæ
 * @a plugID. Jako @a status i @a info trzeba podaæ dane, które zaraz zostan¹ ustawione.
 * 
 * @sa sIMessage_StatusChange
 */
#define IMC_STATUSCHANGE        246

/**
 * Sprawdza czy kontakt jest ignorowany.
 * 
 * @param p1 (int) net
 * @param p2 (char*) UID
 * 
 * @return true jeœli jest.
 */
#define IMC_CNT_IGNORED         310

/**
 * @sa #IMC_FINDCONTACT
 */
#define IMC_CNT_FIND            IMC_FINDCONTACT

/**
 * Sprawdza czy kontakt o podanym ID istnieje.
 * @param p1 (int) ID.
 */
#define IMC_CNT_IDEXISTS        233 

/** 
 * Dodaje kontakt.
 * Po ustawieniu parametrów kontaktu, lub od razu po #IMC_CNT_ADD trzeba wys³aæ #IMC_CNT_CHANGED
 * 
 * @param p1 (int) sieæ
 * @param p2 (int) UID
 * 
 * @return (int) ID nowego kontaktu
 */
#define IMC_CNT_ADD             230 

/**
 * Usuwa kontakt
 * 
 * @param p1 (int) ID
 * @param p2 (bool) true - u¿ytkownik zostanie zapytany o zgodê.
 */
#define IMC_CNT_REMOVE          231 

/**
 * Zwraca iloœæ kontaktów.
 * @return (int) liczba kontaktów.
 */
#define IMC_CNT_COUNT           201 

/** 
 * Sprawdza czy podany kontakt znajduje sie w grupie.
 * 
 * @param p1 (int) ID kontaktu.
 * @param p2 (char*) - grupa do sprawdzenia (jeœli == 0 sprawdzi w grupie aktywnej)
 * 
 * @return (bool) true jeœli znajduje siê...
 */
#define IMC_CNT_INGROUP         305 


/** 
 * Kontakt zosta³ zmieniony.
 * Komunikat powinien byæ wysy³any @b tylko w sytuacji zmiany #CNT_UID, #CNT_NET, lub zaraz po dodaniu!
 * Do wszystkich wtyczek z typem #IMT_CONTACT zostanie rozes³ane #IM_CNT_CHANGED, lub #IM_CNT_ADD.
 * Nie ma ju¿ potrzeby wysy³ania #IMI_REFRESH_CNT
 * 
 * @param p1 ID kontaktu.
 */
#define IMC_CNT_CHANGED         232 

/**
 * Zmienia status kontaktu.
 * @sa sIMessage_StatusChange
 */
#define IMC_CNT_SETSTATUS       234  

/**
 * @sa #IMC_CNT_IGNORED
 */
#define IMC_IGN_FIND            IMC_CNT_IGNORED

/**
 * Dodaje kontakt do listy ignorowanych.
 * 
 * @param p1 (int) sieæ
 * @param p2 (char*) UID
 */
#define IMC_IGN_ADD             311

/**
 * Usuwa kontakt z listy ignorowanych.
 * 
 * @param p1 (int) sieæ
 * @param p2 (char*) UID
 */
#define IMC_IGN_DEL             312 

/**
 * Sprawdza czy grupa istnieje.
 * 
 * @param p1 (char*) nazwa grupy.
 * @return (bool) true jeœli istnieje.
 */
#define IMC_GRP_FIND            300

/**
 * Dodaje grupê.
 * @param p1 (char*) nazwa grupy.
 */
#define IMC_GRP_ADD             301

/**
 * Usuwa grupê.
 * @param p1 (char*) nazwa grupy.
 */
#define IMC_GRP_DEL             302

/**
 * Zmienia nazwê grupy.
 * 
 * @param p1 (char*) stara nazwa grupy.
 * @param p2 (char*) nowa nazwa grupy.
 */
#define IMC_GRP_RENAME          303 


/** 
 * Komunikat do rejestrowania kolumn w tablicach.
 *
 * @attention Mo¿e byæ wysy³ane TYLKO PODCZAS przetwarzania komunikatu #IM_SETCOLS.
 */
class sIMessage_setColumn: public sIMessage_base {
public:
  const static int __msgID = 1102;
  tTable _table;            ///< Tablica w której ustawiamy kolumnê
  int _id;                  ///< ID kolumny.
  int _type;                ///< typ kolumny (patrz @ref dt_ct_).
  union {
    int _def;               ///< Wartoœæ domyœlna.
    const char * _def_ch;   ///< Wartoœæ domyœlna dla kolumn #ctypeString (musi byæ ci¹gle w pamiêci!)
    __int64 * _def_p64;     ///< Wartoœæ domyœlna dla kolumn #ctypeInt64 (musi byæ ci¹gle w pamiêci!)
  };
  const char * _name;

  sIMessage_setColumn(tTable table, int id, int type, int def, const char * name = 0): sIMessage_base(__msgID) {
    init(table, id, type, def, name);
  }
  sIMessage_setColumn(tTable table, int id, int type, const char * def, const char * name = 0): sIMessage_base(__msgID) {
    init(table, id, type, (int) def, name);
  }
  sIMessage_setColumn(int id, int type, int def, const char * name = 0): sIMessage_base(__msgID) {
    init(0, id, type, (int) def, name);
  }
  sIMessage_setColumn(int id, int type, const char * def, const char * name = 0): sIMessage_base(__msgID) {
    init(0, id, type, (int) def, name);
  }

private:
  void init(tTable table, int id, int type, int def, const char * name) {
    _table = table;
    _id = id;
    _type = type;
    _def = def;
    _name = name;
    s_size = sizeof(*this);
  }
};

#define IMC_CFG_SAVE            1010  ///< Wszystkie ustawienia zostan¹ zapisane.

// W32
#define IMC_GETINSTANCE         2000  ///< Zwraca HINSTANCE aplikacji.
#define IMC_GETMSGCOLDESC       3000  ///< @internal

/**
 * @defgroup imc_mru_ MRU.
 * Obs³uga listy ostatnio u¿ywanych.
 * @{
 */
#define MRU_SET_LOADFIRST       0x1   ///< Zawartoœæ listy zostanie najpierw za³adowana (dzia³aj¹ te¿ flagi dla MRU_GET_ !)
#define MRU_GET_ONEBUFF         0x10  ///< sMRU::buffer jest wskaŸnikiem do bufora (o rozmiarze sMRU::buffSize), który zostanie u¿yty do wszystkich operacji
#define MRU_GET_USETEMP         0x20  ///< zostanie u¿yty tymczasowy bufor wewnêtrzny rdzenia.

/**
 * Struktura u¿ywana przez IMC_MRU_*
 */
struct sMRU {
  int flags;            ///< Flagi
  const char * name;    ///< Nazwa zestawu
  int count;            ///< Rozmiar zestawu
  int buffSize;         ///< Rozmiar buforów dla #IMC_MRU_GET
  const char * current; ///< Przy #IMC_MRU_SET i #IMC_MRU_UPDATE podajemy dodawan¹ wartoœæ.
  union {
    /**
     * Tablica @a count buforów. Przy #IMC_MRU_GET musz¹ mieæ rozmiar podany w @a buffSize.
     * Je¿eli jest mniej buforów ni¿ w count, ostatnia pozycja musi byæ równa 0.
     */
    char ** values;
    char * buffer;      ///< WskaŸnik do pojedyñczego bufora trzymaj¹cego wszystkie informacje
  };
  const char * removed; ///< #IMC_MRU_UPDATE zapisze tu element, który zosta³ odrzucony.

  sMRU(): flags(0), count(0), buffSize(0), name(0), current(0), values(0) { }
};

#define IMC_MRU_SET             400   ///< (sIMessage_MRU*) Ustawia listê MRU. 
#define IMC_MRU_GET             401   ///< (sIMessage_MRU*) Pobiera listê MRU. 
#define IMC_MRU_UPDATE          402   ///< (sIMessage_MRU*) Aktualizuje listê MRU. 

/** 
 * Struktura do przesy³ania #IMC_MRU_GET, #IMC_MRU_SET i #IMC_MRU_UPDATE.
 */
struct sIMessage_MRU: public sIMessage_base {
  sMRU * MRU;

  sIMessage_MRU(int id, sMRU * MRU): sIMessage_base(id), MRU(MRU) {
    s_size = sizeof(*this);
  }
};

/** @} */
/** @} */  // Wiadomoœci do rdzenia

/**
 * @defgroup imi_ do UI
 * @{
 */

#define IMI_PREPARE             IMI_BASE + 0    ///< Tylko dla Rdzenia

/**
 * Otwiera okno debugowania interfejsu.
 * Dostêpne tylko w wersjach Debug i Beta.
 */
#define IMI_DEBUG               IMI_BASE + 1
#define IMI_SET_SHOWBITS        IMI_BASE + 10   ///< Otwiera okno ustawiania ShowBits
#define IMI_SET_PLUGINS         IMI_BASE + 11   ///< Otwiera okno wyboru wtyczek
// #define IMI_UIINVALIDATE        IMI_BASE + 100  ///< (0,0) - odnawia listy akcji


/**
 * @defgroup imi_action_ Obs³uga akcji.
 * System akcji w interfejsie odpowiada za obs³ugê np. kontrolek
 * w konfiguracji, menusów czy przycisków na toolbarach.
 * 
 * @warning Akcje dla kontaktów korzystaj¹ tylko z jednego obiektu akcji, który jest "prze³¹czany" 
 * na aktualnie ¿¹dany kontakt. Nie powinno siê wiêc ustawiaæ parametrów akcji zale¿nie od kontaktu!
 * 
 * @{
 */
 
/** 
 * @defgroup ac_ Numery kontaktów akcji. 
 * @{ 
 */

#define AC_USER                 0     ///< Akcja jest przypisana do u¿ytkownika.
#define AC_NONE                 -1L   ///< Akcja nie jest przypisana do ¿adnego kontaktu.
#define AC_CURRENT              -2L   ///< Ostatnio przypisany kontakt.

/** @} */

/**
 * Wstawia akcjê.
 * @param p1 (#sUIActionInfo*) Ustawienia akcji. MUSZ¥ byæ ustawione @a parent i @a id.
 */
#define IMI_ACTION              IMI_BASE + 101

/**
 * Wstawia grupê.
 * Dzia³a tak samo jak #IMI_ACTION z #ACTS_GROUP ustawionym w @a status.
 * 
 * @param p1 (#sUIActionInfo*) Ustawienia akcji. MUSZ¥ byæ ustawione @a parent i @a id.
 * @attention Identyfikatory grup @b musz¹ byæ niepowtarzalne!
 */
#define IMI_GROUP               IMI_BASE + 102

/**
 * Wywo³uje akcjê (w innej wtyczce).
 * @param p1 (sUIActionNotify_base*) Powiadomienie o zdarzeniu do wys³ania.
 */
#define IMI_ACTION_CALL         IMI_BASE + 103

/**
 * Pobiera w³aœciwoœci akcji.
 * Zawsze ustawia @a pos, @a handle i @a type.
 *
 * @param p1 (sUIActionInfo *). Musi mieæ ustawiony @a parent, @a id, oraz @a mask (je¿eli @a mask == 0 pobiera wszystko).
 * 
 * @attention Przy pobieraniu @a txt trzeba ustawiæ @a txt na bufor @b char * i @a txtSize na rozmiar tego bufora.
 * Je¿eli @a txt == 0 zostanie ono ustawione na 2 kilobajtowy bufor wewnêtrzny.
 */
#define IMI_ACTION_GET          IMI_BASE + 107

/**
 * Ustawia w³aœciwoœci akcji.
 *
 * @param p1  (sUIActionInfo *). Musi mieæ ustawiony @a parent, @a id, oraz @a mask (je¿eli @a mask == 0 ustawia wszystko).
 * @attention Mo¿na zmieniaæ tylko: @a status, @a exStyle, @a p1, @a p2, @a param, @a ico i @a txt.
 */
#define IMI_ACTION_SET          IMI_BASE + 108

/**
 * Pobiera wartoœæ kontrolki w konfiguracji.
 * 
 * @param p1  (sUIActionInfo *). Wartoœæ zostanie ustawiona w @a txt.
 * @return (char *) (to samo co w @a txt), lub 0 jeœli wyst¹pi b³¹d.
 */
#define IMI_ACTION_GETVALUE     IMI_BASE + 106

/**
 * Ustawia wartoœæ kontrolki w konfiguracji.
 * 
 * @param p1  (sUIActionInfo *). Wartoœæ musi znajdowaæ siê w @a txt.
 * @return (char *) (to samo co w @a txt), lub 0 jeœli wyst¹pi b³¹d.
 */
#define IMI_ACTION_SETVALUE     IMI_BASE + 110 

/**
 * Zwraca iloœæ akcji nale¿¹cych do podanej grupy.
 * 
 * @param p1 (sUIAction*)
 * @return (int)
 */
#define IMI_GROUP_ACTIONSCOUNT  IMI_BASE + 111

/**
 * Sprawdza czy akcja istnieje.
 * 
 * @param p1 (sUIAction*)
 * @return (bool)
 */
#define IMI_ACTION_EXISTS       IMI_BASE + 112

/**
 * Sprawdza czy akcja jest grup¹.
 * 
 * @param p1 (int) parent
 * @return (bool)
 */
#define IMI_ACTION_ISGROUP      IMI_BASE + 113

/**
 * Zwraca identyfikator akcji na podanej pozycji w grupie.
 * 
 * @param p1 (int) parent
 * @param p2 (int) pozycja
 * 
 * @return (int) ID
 */
#define IMI_ACTION_GETID        IMI_BASE + 114

/**
 * Usuwa akcjê.
 *
 * @warning Mo¿e zostaæ wywo³ane TYLKO gdy akcja nie jest utworzona!
 * @param p1 (sUIAction*) akcja do usuniêcia
 * @return (bool)
 */
#define IMI_ACTION_REMOVE       IMI_BASE + 115

/**
 * Pobiera typ akcji (@ref act_).
 *
 * @param p1 (sUIAction*) Akcja
 * @return (int)
 */
#define IMI_ACTION_GETTYPE      IMI_BASE + 116

/**
 * Pobiera uchwyt grupy (np. uchwyt g³ównego okna)
 *
 * @param p1 (sUIAction*) Akcja
 * @return (HANDLE)
 */
#define IMI_GROUP_GETHANDLE     IMI_BASE + 117

/**
 * Znajduje rodzica akcji o identykatorze sUIAction::id, zaczynaj¹c
 * szukanie w sUIAction::parent. Je¿eli p2 jest równe 1, 
 * znaleziony identyfikator zostanie usatwiony w strukturze przekazanej w polu p1.
 * 
 * @param p1 (sUIAction*) Akcja. 
 * @param p2 (bool) Czy zapisaæ wynik w p1?
 * 
 * @return (int)
 */
#define IMI_ACTION_FINDPARENT   IMI_BASE + 118

/**
 * Pobiera identyfikator grupy, któr¹ u¿ytkownik wskaza³ jako grupê dla menu wtyczek. 
 * @return (int) ID grupy
 */
#define IMI_GETPLUGINSGROUP     IMI_BASE + 119

/**
 * Je¿eli grupa jest grup¹ konfiguracji i okno konfiguracji jest otwarte upewnia siê, czy wszystkie kontrolki grupy s¹ utworzone.
 * 
 * @param p1 (sUIAction*) Akcja.
 * @return (bool) uda³o siê, lub nie
 */
#define IMI_GROUP_MAKECFG       IMI_BASE + 120

/**
 * Przypisuje kontrolkê do kontaktu (podanego w sUIAction).
 * 
 * @param p1 (sUIAction*) Akcja.
 * @param p2 (bool) Czy ustawiaæ rekurencyjnie?
 */
#define IMI_ACTION_SETCNT       IMI_BASE + 121

/**
 * Pobiera indeks kontrolki (numer przypisywany w WinApi oknom, przyciskom na toolbarach itd).
 * 
 * @param p1 (sUIAction*) Akcja.
 * @return (int) indeks
 */
#define IMI_ACTION_GETINDEX     IMI_BASE + 122

/**
 * Pobiera identyfikator wtyczki, która utworzy³a akcjê i obs³uguje jej komunikaty
 *
 * @param p1 (sUIAction*) Akcja.
 * @return (int) ID wtyczki
 */
#define IMI_ACTION_GETOWNER     IMI_BASE + 123

/**
 * Uruchamia i obs³uguje menu utworzone ze wskazanej grupy akcji
 * Komunikat wysy³amy jako (sIMessage_UIMakePopup*)
 * W akcji nale¿y podaæ identyfikator kontaktu (lub 0) do którego menu ma byæ przypisane...
 */
#define IMI_ACTION_MAKEPOPUPMENU  IMI_BASE + 150

/**
 * Identyfikacja akcji.
 */
struct sUIAction {
  unsigned int id;      ///< Identyfikator akcji.
  unsigned int parent;  ///< Identyfikator grupy.
  /**
   * Identyfikator kontaktu dla którego zmieniamy/pobieramy parametry akcji
   * #AC_NONE, lub #AC_CURRENT ...
   */
  int cnt;

  sUIAction(unsigned int _parent, unsigned int _id, unsigned int _cnt = AC_CURRENT): parent(_parent), id(_id), cnt(_cnt) { }
  sUIAction(): parent(0), id(0), cnt(AC_CURRENT) { }
};

typedef sUIAction sUIACTION;


/** 
 * @defgroup uiaim_ Maski dla sUIActionInfo.
 * @{
 */
#define UIAIM_STATUS        1     ///< sUIActionInfo::status i sUIActionInfo::statusMask s¹ ustawione.
#define UIAIM_EXSTYLE       2     ///< sUIActionInfo::exStyle i sUIActionInfo::exStyleMas s¹ ustawione.
#define UIAIM_P1            4     ///< sUIActionInfo::p1 jest ustawiony.
#define UIAIM_P2            8     ///< sUIActionInfo::p2 jest ustawiony.
#define UIAIM_PARAM         0x10  ///< sUIActionInfo::param jest ustawiony.
#define UIAIM_ICO           UIAIM_P1
#define UIAIM_TXT           0x40  ///< sUIActionInfo::txt i sUIActionInfo::txtSize s¹ ustawione.

#define UIAIM_COL           UIAIM_P1
#define UIAIM_POS           0x100
#define UIAIM_SIZE          0x200
#define UIAIM_HANDLE        0x400
#define UIAIM_TYPE          0x800

/**
 * Ustawiona wartoœæ akcji powinna zostaæ przekonwertowana (np. z formatu wartoœci akcji do formatu pola w bazie i na odwrót)
 */
#define UIAIM_VALUE_CONVERT 0x10000

/**
 * Wszystkie powy¿sze.
 */
#define UIAIM_ALL           0x35F

/** @} */ // uiaim_


/**
 * W³aœciwoœci akcji.
 *
 * @sa #IMI_ACTION_GET #IMI_ACTION_SET
 */
struct sUIActionInfo {
  unsigned short s_size;
  sUIAction act;            ///< Identyfikatory.
  /**
   * Pozycja na liœcie w grupie. Pos == -1 oznacza "na koñcu" (podczas @ref IMI_ACTION "wstawiania").
   *
   * @todo Powinien potrafiæ równie¿ zmieniæ pozycjê.
   */
  unsigned int pos;
  unsigned int type;        ///< Typ kontrolki przypisanej do akcji ( @ref actt_ ).
  void * handle;            ///< Uchwyt do kontrolki akcji (np w windowsach uchwyty do HWND lub HMENU)
  void * reserved;
  
  /**
   * Maska. Oznacza które pola w strukturze s¹ ustawione.
   *
   * @attention Pole @a act musi byæ @b zawsze ustawione! 
   * @sa @ref uiaim_
   */
  unsigned int mask;       
  unsigned int status;      ///< @ref actm_ "Status".
  unsigned int statusMask;  ///< Oznacza które pola w @a status powinny byæ zmienione.
  unsigned int exStyle;     ///< Dodatkowe style. @attention W tej chwili nie s¹ one u¿ywane!
  unsigned int exStyleMask; ///< Oznacza które pola w @a exStyle powinny byæ zmienione.
  char * txt;               ///< Tekst przypisany do akcji.
  unsigned int txtSize;     ///< Rozmiar bufora w txt.
  int param;                ///< Parametr u¿ytkownika.
  int p1;                   ///< Dodatkowy parametr uzywany przez typy kontrolek.
  int p2;                   ///< Dodatkowy parametr uzywany przez typy kontrolek.
  short w, h;               ///< Wysokoœæ / szerokoœæ kontrolki

  sUIActionInfo() {
    s_size = sizeof(sUIActionInfo);
    mask = act.parent = act.id = pos = 0;
    handle = 0;
  }
  sUIActionInfo(int _parent, int _id, int _pos, int _status = 0, char * _txt = 0, int _p1 = 0, short _w = 0, short _h = 0, int _p2 = 0, int _param = 0) {
    s_size = sizeof(sUIActionInfo);
    mask = UIAIM_ALL;
    act.parent = _parent;
    act.id = _id;
    pos = _pos;
    txt = _txt;
    status = _status;
    statusMask = -1;
    exStyleMask = 0;
    p1 = _p1;
    p2 = _p2;
    param = _param;
    w = _w;
    h = _h;
  }
  sUIActionInfo(int _parent, int _id) {
    s_size = sizeof(sUIActionInfo);
    act.parent = _parent;
    act.id = _id;
    mask = 0;
  }
  sUIActionInfo(const sUIAction& a) {
    s_size = sizeof(sUIActionInfo);
    act = a;
    mask = 0;
  }
};

/**
 * W³aœciwoœci akcji do konfiguracji.
 */
struct sUIActionInfo_cfg: sUIActionInfo {
  short x, y;   ///< Przesuniêcie wzglêdem osi x/y

  sUIActionInfo_cfg(): sUIActionInfo() {
    s_size = sizeof(sUIActionInfo_cfg);
    x = y = 0;
  }
  sUIActionInfo_cfg(int _parent, int _id, int _pos = -1, int _status = 0, char * _txt = 0, int _col = 0, short _w = 0, short _h = 0, int _p2 = 0, int _param = 0)
    : sUIActionInfo(_parent, _id, _pos, _status, _txt, _col, _p2, _param)
  {
    s_size = sizeof(sUIActionInfo_cfg);
    x = y = w = h = 0;
  }
  sUIActionInfo_cfg(int _parent, int _id, int _pos = -1, int _status = 0, char * _txt = 0, int _col = 0, short _x = 0, short _y = 0, short _w = 0, short _h = 0, int _p2 = 0, int _param = 0)
    : sUIActionInfo(_parent, _id, _pos, _status, _txt, _col, _w, _h, _p2, _param)
  {
    s_size = sizeof(sUIActionInfo_cfg);
    x = _x;
    y = _y;
  }
};

#define sUIActionInfo_V1    sizeof(sUIActionInfo)

/**
 * Powiadomienie.
 * Struktura podstawowa wysy³ana razem z IM_ACTION.
 * 
 * @sa actn_
 */
struct sUIActionNotify_base {
  unsigned short s_size;
  sUIAction act;      ///< Identyfikator akcji.
  unsigned int code;  ///< Numer powiadomienia.
  int reserved;       ///< Pozycja zarezerwowana. Musi byæ równa 0.

  sUIActionNotify_base(sUIAction _act, unsigned int _code)
    : s_size(sizeof(sUIActionNotify_base)), act(_act), code(_code), reserved(0) { }
  sUIActionNotify_base(unsigned int _code = 0) 
    : s_size(sizeof(sUIActionNotify_base)), act(sUIAction()), code(_code), reserved(0) { }
};

struct sUIActionNotify_2params: public sUIActionNotify_base {
  unsigned int notify1;    ///< Parametr 1.
  unsigned int notify2;    ///< Parametr 2.

  sUIActionNotify_2params(sUIAction _act, unsigned int _code, int _not1, int _not2) 
    : sUIActionNotify_base(_act, _code), notify1(_not1), notify2(_not2)
  {
    s_size = sizeof(sUIActionNotify_2params);
  }
  sUIActionNotify_2params(unsigned int _code, int _not1, int _not2) 
    : sUIActionNotify_base(_code), notify1(_not1), notify2(_not2)
  {
    s_size = sizeof(sUIActionNotify_2params);
  }
  sUIActionNotify_2params()
    : sUIActionNotify_base(), notify1(0), notify2(0)
  {
    s_size = sizeof(sUIActionNotify_2params);
  }
  sUIActionNotify_2params(sUIActionNotify_base &base)
    : sUIActionNotify_base(base.act, base.code), notify1(0), notify2(0)
  {
    s_size = sizeof(sUIActionNotify_2params);
    this->reserved = base.reserved;
  }
};

typedef sUIActionNotify_2params sUIActionNotify;

struct sUIActionNotify_buff: public sUIActionNotify_base {
  char * buff;
  unsigned int buffSize;

  sUIActionNotify_buff() :sUIActionNotify_base(), buff(0), buffSize(0) {
    s_size = sizeof(*this);
  }
};

/**
 * Struktura do przesy³ania #IMI_ACTION_MAKEPOPUPMENU.
 */
struct sIMessage_UIMakePopup: public sIMessage_base {
  sUIAction _action;      ///< Identyfikator akcji-grupy z której ma byæ utworzone menu, razem z identyfikatorem przypisanego do niego kontaktu.
  int _uFlags;            ///< Flagi. Atrybut przekazywany do f-cji WinApi - TrackPopupMenu()
  int _x;                 ///< Pozycja X
  int _y;                 ///< Pozycja Y
  int _nReserved;         ///< Atrybut przekazywany do f-cji WinApi - TrackPopupMenu()
  int _startFrom;         ///< Pierwsza akcja (od 0) do uwzglêdnienia w menu (u¿ywane na przyk³ad w tzw. chevronach)
  void * _hWnd;           ///< Okno - w³aœciciel (Aby unikn¹æ problemów z ikonkami najlepiej podaæ 0 lub uchwyty do okien g³ównego/rozmowy/wiêcej). Atrybut przekazywany do f-cji WinApi - TrackPopupMenu()
  const void * _prcRect;  ///< Atrybut przekazywany do f-cji WinApi - TrackPopupMenu()

  sIMessage_UIMakePopup(sUIAction & action, int uFlags, int x, int y, int nReserved, void * hWnd, const void *prcRect = 0, int startFrom = 0)
    : sIMessage_base(IMI_ACTION_MAKEPOPUPMENU), _action(action), _uFlags(uFlags), _x(x), _y(y), _nReserved(nReserved), _hWnd(hWnd), _prcRect(prcRect), _startFrom(startFrom) 
  {
    s_size = sizeof(*this);
  }
};

/** @} */ // imi_action_

/**
 * Wstawia ikonkê z zasobów wtyczki do listy ikonek UI.
 * @deprecated O wiele lepiej u¿ywaæ #IMI_ICONREGISTER i funkcji pomocniczych.
 * 
 * @param p1 (int) Identyfikator ikonki na liœcie (patrz #UIIcon). 
 * @param p2 (int) Identyfikator ikonki w zasobach wtyczki.
 */
#define IMI_ICONRES         IMI_BASE + 109

/**
 * Rejestruje ikonkê/bitmapê w UI.
 * 
 * @param p1 (sUIIconRegister*) Informacja o wstawianej ikonce.
 * @return (bool)
 *
 * @warning Przy zastêpowaniu bitmap na listach poprzednie kopie NIE s¹ usuwane!
 * Najlepiej podmieniaæ ikonki jak najrzadziej siê da... Zostanie to zmienione w nastêpnych wersjach...
 * @todo Zastêpowanie bitmap na listach.
 */
#define IMI_ICONREGISTER    IMI_BASE + 130

/**
 * Sprawdza czy ikonka istnieje.
 * 
 * @param p1 (int) ID ikonki
 * @param p2 (IML_enum) lista któr¹ sprawdziæ.
 * @return (bool)
 */
#define IMI_ICONEXISTS      IMI_BASE + 131

/**
 * Dodaje ca³y zestaw ikon.
 * 
 * @param p1 (sUIIconRegisterList*) Informacja co zarejestrowaæ
 *
 * @warning Przy zastêpowaniu bitmap na listach poprzednie kopie NIE s¹ usuwane!
 * Najlepiej podmieniaæ ikonki jak najrzadziej siê da... Zostanie to zmienione w nastêpnych wersjach...
 */
#define IMI_ICONREGISTERLIST  IMI_BASE + 132 

/**
 * Zwraca index ikonki na wybranej liœcie
 * 
 * @param p1 (int) ID ikonki
 * @param p2 (IML_enum) lista któr¹ sprawdziæ
 * @return (int) pozycja
 */
#define IMI_GETICONINDEX    IMI_BASE + 133

/**
 * Zwraca uchwyt typu HIMAGELIST do wybranej listy.
 * 
 * @param p1 (IML_enum) lista któr¹ zwróciæ
 * @return (HIMAGELIST)
 * 
 * @warning Zwrócona lista jest TYLKO do ODCZYTU! Ka¿da modyfikacja dokonana poza UI mo¿e powa¿nie zak³óciæ wyœwietlanie ikon!
 */
#define IMI_GETICONLIST     IMI_BASE + 134

/**
 * Usuwa ikonkê z wybranej listy...
 *
 * @param p1 (int) ID ikonki
 * @param p2 (IML_enum) lista
 * @return (bool)
 *
 * @warning Przy usuwaniu z list IML_16 i IML_32 ikony NIE s¹ usuwane z pamiêci i póŸniejsza ich podmiana mo¿e wymagaæ nawet restartu Konnekta!
 */
#define IMI_ICONUNREGISTER  IMI_BASE + 135

/**
 * Zwraca uchwyt ikonki z wybranej listy.
 *
 * @param p1 (int) ID ikonki
 * @param p2 (IML_enum) lista
 * @return (HICON/HBITMAP) uchwyt
 *
 * @warning Przy pobieraniu z IML_16 i IML_32 s¹ to nowo utworzone uchwyty i nale¿y je ZWOLNIÆ!
 */
#define IMI_ICONGET         IMI_BASE + 136

/**
 * Wyœwietla okno z ostrze¿eniem.
 * 
 * @param p1 (char*) treœæ.
 * @param p2 (int) dodatkowe flagi, te same co przy MessageBox w WinApi.
 * @return (int) To samo co zwraca MessageBox z WinApi.
 */
#define IMI_WARNING         IMI_BASE + 200

/**
 * Wyœwietla okno z b³êdem.
 * 
 * @param p1 (char*) treœæ.
 * @param p2 (int) dodatkowe flagi, te same co przy MessageBox w WinApi.
 * @return (int) To samo co zwraca MessageBox z WinApi.
 */
#define IMI_ERROR           IMI_BASE + 201

/**
 * Wyœwietla okno z zapytaniem.
 * 
 * @param p1 (char*) treœæ.
 * @param p2 (int) dodatkowe flagi, te same co przy MessageBox w WinApi.
 * @return (int) Jeœli p2 == 0 to true/false, lub to samo co zwraca MessageBox z WinApi.
 */
#define IMI_CONFIRM         IMI_BASE + 202

/**
 * Wyœwietla okno z informacj¹.
 * 
 * @param p1 (char*) treœæ.
 * @param p2 (int) dodatkowe flagi, te same co przy MessageBox w WinApi.
 * @return (int) To samo co zwraca MessageBox z WinApi.
 */
#define IMI_INFORM          IMI_BASE + 204

struct sIMessage_msgBox: public sIMessage_base {
  const char * msg;
  unsigned int flags;
  const char * title;
  HANDLE parent;

  sIMessage_msgBox(unsigned int id, const char * msg = "", const char * title = 0, int _flags = 0, HANDLE parent = 0)
    : sIMessage_base(id, Net::none, imtNone)
  {
    this->s_size = sizeof(*this);
    this->parent = parent;
    this->msg = msg;
    this->flags = _flags;
    this->title = title;
  }
};

/**
 * Okienko podawania has³a.
 * 
 * @param (sDIALOG_access*) Parametry okna.
 * @param (bool) Gdy == 1 automatycznie do³¹cza do flag DFLAG_SAVE.
 * @return (bool)
 */
#define IMI_DLGPASS         IMI_BASE + 205

/**
 * Okienko podawania loginu i has³a.
 * 
 * @param (sDIALOG_access*) Parametry okna.
 * @param (bool) Gdy == 1 automatycznie do³¹cza do flag DFLAG_SAVE.
 * @return (bool)
 */
#define IMI_DLGLOGIN        IMI_BASE + 206

/**
 * Okienko ustawiania has³a.
 * 
 * @param (sDIALOG_access*) Parametry okna.
 * @param (bool) Gdy == 1 automatycznie do³¹cza do flag DFLAG_SAVE.
 * @return (bool)
 */
#define IMI_DLGSETPASS      IMI_BASE + 207

/**
 * Okno wprowadzania tekstu
 * 
 * @param p1 (sDIALOG_enter*) Parametry okna.
 * @return (bool)
 */
#define IMI_DLGENTER        IMI_BASE + 208

/**
 * Okno wyboru (ka¿da opcja to jeden przycisk).
 * 
 * @param p1 (sDIALOG_choose *)
 * @return (int) numer przycisku (1 - ...) lub 0 gdy ¿aden nie zosta³ wybrany. 
 */
#define IMI_DLGBUTTONS      IMI_BASE + 213

/**
 * Pobieranie tokenu (wpisywanie wartoœci widocznej na obrazku).
 * 
 * @param p1 (sDIALOG_token *)
 * @return (bool)
 */
#define IMI_DLGTOKEN        IMI_BASE + 214

/**
 * Tworzy okno oczekiwania na zakoñczenie d³u¿szej operacji.
 * @param p1 (sDIALOG_long *) Parametry okna. Struktura musi byæ zachowana a¿ do wywo³ania #IMI_LONGEND!
 */
#define IMI_LONGSTART       IMI_BASE + 209

/**
 * Zamyka okno utworzone przez #IMI_LONGSTART.
 * @param p1 (sDIALOG_long *) ta sama struktura u¿yta przy #IMI_LONGSTART.
 */  
#define IMI_LONGEND         IMI_BASE + 210

/**
 * Zmienia okno utworzone przez #IMI_LONGSTART.
 * 
 * @param p1 (sDIALOG_long *) ta sama struktura u¿yta przy #IMI_LONGSTART.
 * @param p2 (int) wartoœæ (@ref dset_) oznaczaj¹ca co ma zostaæ zaktualizowane
 * (wartoœæ musi najpierw zostaæ zmieniona w strukturze sDIALOG_long).
 */
#define IMI_LONGSET         IMI_BASE + 211

#define IMI_DLGPROFILE      IMI_BASE + 212

/**
 * Klasa podstawowa u¿ywana przez wszystkie wiadomoœci obs³uguj¹ce okna dialogowe... 
 */
struct sDIALOG {
  unsigned short s_size;
  const char * title; ///< Tytu³ okienka.
  const char * info;  ///< Dodatkowa informacja ...
  int flag;           ///< Flaga D*_
  void * handle;      ///< Uchwyt do okna dialogowego. Przed utworzeniem okna, @a handle trzeba ustawiæ na rodzica okna!
  void * param;       ///< Parametr uzytkownika

  sDIALOG() {
    s_size = sizeof(sDIALOG);
    info = title = "";
    handle = 0;
    param = 0;
    flag = 0;
  }
};

/**
 * Struktura u¿ywana przez okno pobierania tokenu.
 * 
 * @attention Wszystkie zwrócone bufory musz¹ zostaæ od razu skopiowane!
 */
struct sDIALOG_token: public sDIALOG {
  const char * imageURL;  ///< URL do obrazka (@ref sUIIconRegister)
  char * token;           ///< Token.

  sDIALOG_token(): sDIALOG() {
    s_size = sizeof(sDIALOG_token);
    imageURL = "";
    token = "";
  }
};

/** 
 * Struktura u¿ywana przez okna obs³ugi hase³ i loginów.
 * 
 * @attention Wszystkie zwrócone bufory musz¹ zostaæ od razu skopiowane!
 */
struct sDIALOG_access: public sDIALOG {
  char * pass;    ///< Has³o.
  char * login;   ///< Login.
  bool save;      ///< Stan checkbox'a "czy zapisywaæ".

  sDIALOG_access(): sDIALOG() {
    s_size = sizeof(sDIALOG_access);
    pass = login = "";
    save = false;
  }
};

/**
 * Struktura u¿ywana przez #IMI_DLGENTER.
 *
 * @attention Wszystkie zwrócone bufory musz¹ zostaæ od razu skopiowane!
 */
struct sDIALOG_enter: public sDIALOG {
  char * value;  ///< Wprowadzona wartoœæ.
  /**
   * Identyfikator pola tekstowego. 
   * Podanie identyfikatora uaktywni historiê wpisów.
   */
  char * id;
  int maxLength; ///< Maksymalna d³ugoœæ wprowadzonego tekstu.

  sDIALOG_enter(): sDIALOG() {
    s_size = sizeof(sDIALOG_enter);
    value = id = "";
    maxLength = 0;
  }
};

/** 
 * Struktura u¿ywana przez #IMI_DLGBUTTONS.
 *
 * @attention Wszystkie zwrócone bufory musz¹ zostaæ od razu skopiowane! 
 */
struct sDIALOG_choose: public sDIALOG {
  char * items; ///< Spis elementów. Elementy rozdzielane s¹ znakiem '\n'
  int def;      ///< Domyœlnie zaznaczona opcja (liczone od zera)
  int width;    ///< Szerokoœæ przycisków.

  sDIALOG_choose(): sDIALOG() {
    s_size = sizeof(sDIALOG_choose);
    items = "";
    def = 1;
    width = 0;
  }
};

struct sDIALOG_profile: public sDIALOG {
  char * profile;
  char * pass;
  bool newOne;

  sDIALOG_profile(): sDIALOG() {
    s_size = sizeof(sDIALOG_profile);
    pass = profile = "";
    newOne = false;
  }
};

/** 
 * @defgroup timeoutt_ Typy dla sDIALOG_long::timeoutProc
 * @{
 */
#define TIMEOUTT_START      0x10  ///< Dobry moment ¿eby coœ zaalokowaæ.
#define TIMEOUTT_END        0x11  ///< Dobry moment ¿eby coœ zwolniæ.
/**
 * Sprawdzamy stan. Gdy zwrócimy 1, timeoutPassed zostanie zwiêkszony. A gdy 0, zostanie wyzerowany. 
 * Gdy timeoutPassed > timeout, nast¹pi przekroczenie limitu czasu i zostanie wywo³any #TIMEOUTT_TIMEOUT.
 */
#define TIMEOUTT_CHECK      1
#define TIMEOUTT_TIMEOUT    2     ///< Nast¹pi³o przekroczenie czasu, mo¿na napisaæ coœ m¹drego.

/** @} */

/** 
 * Struktura u¿ywana przez #IMI_LONGSTART, #IMI_LONGSET i #IMI_LONGEND.
 */
struct sDIALOG_long: public sDIALOG {
  int progress;   ///< Wartoœæ 'postêpu'. Przy tworzeniu okna oznacza max. wartoœæ (liczon¹ od zera) - domyœlnie 100.
  bool cancel;    ///< Czy zosta³o wciœniête [Anuluj]?
  int threadId;   ///< Id watku, z ktorego tworzone bylo okno
  /**
   * Procedura wywo³ywana po naciœniêciu [Anuluj].
   */
  bool (__stdcall *cancelProc)(sDIALOG_long *);
  /**
   * Procedura wywo³ywana aby sprawdziæ czy nast¹pi³ timeout.
   * 
   * @param type Rodzaj wywo³ania (Patrz @ref timeoutt_)
   * @return 0/1 w zale¿noœci od typu wywo³ania.
   */
  bool (__stdcall *timeoutProc)(int type, sDIALOG_long *);

  void * timeoutParam;  ///< Parametr do wykorzystania przez timeoutProc.
  int timeout;          ///< Czas po jakim zostanie wys³ane TIMEOUTT_TIMEOUT.
  int timeoutPassed;    ///< Iloœæ ms jaka uplynê³a od pierwszego TIMEOUTT_CHECK == 0.
  HANDLE timeoutHandle; 
 
  sDIALOG_long(): sDIALOG() {
    s_size = sizeof(sDIALOG_long);
    progress = -1;
    cancel = false;
    cancelProc = 0;
    timeoutProc = 0;
    timeout = timeoutPassed = 0;
    timeoutHandle = timeoutParam = 0;

    #ifdef _WINBASE_
      threadId = GetCurrentThreadId();
    #else
      threadId = 0;
    #endif
  }
};

/**
 * @defgroup dlong_ Flagi dla sDIALOG_long.
 * @{
 */

#define DLONG_MODAL         0x01    ///< Blokuje okna
#define DLONG_CANCEL        0x02    ///< Mozliwosc anulowania
#define DLONG_NODLG         0x04    ///< Nie wyswietla okienka ...
#define DLONG_SINGLE        0x08    ///< Jedyne wyswietlane okienko

/**
 * @sa #DLONG_SINGLE
 */
#define DLONG_ONLY          DLONG_SINGLE

/**
 * Akcja wykonywana w glownym watku i moze go blokowac.
 * Akcja musi doœæ czêsto wywo³ywaæ SleepEx(1) aby pozwoliæ
 * na wywo³ywanie f-cji uaktualniaj¹cych g³ówny w¹tek.
 *
 * @warning Je¿eli akcja mo¿e blokowaæ na d³u¿ej koniecznie u¿yj OSOBNEGO w¹tku.
 */
#define DLONG_BLOCKING      0x10
#define DLONG_ANONE         0x100   ///< Bez animacji
#define DLONG_ARECV         0x200   ///< Animacja "odbieram"
#define DLONG_ASEND         0x400   ///< Animacja "wysy³am"
#define DLONG_AINET         0x800   ///< Animacja "komunikacja"

/** @} */

/**
 * @defgroup dset_ Flagi dla #IMI_LONGSET.
 * @{
 */

#define DSET_TITLE          0x1     ///< Zosta³ zmieniony tytu³.
#define DSET_INFO           0x2     ///< Zosta³o zmienione info.
#define DSET_PROGRESS       0x4     ///< Zosta³ zmieniony postêp.
#define DSET_BUTTONS        0x8     ///< Zosta³y zmienione flagi dotycz¹ce przycisków.
#define DSET_ANIM           0x10    ///< Zosta³a zmieniona animacja.

/** @} */

/** 
 * @defgroup dflag_ Flagi dla sDIALOG.
 * @{
 */
 
#define DFLAG_SAVE          0x1     ///< W sDIALOG_access zostanie pokazany checkbox 'czy zapisaæ'.
#define DFLAG_PASS2         0x4     ///< W #IMI_DLGSETPASS zostanie sprawdzona zgodnoœæ obu hase³.
#define DFLAG_CANCEL        0x8     ///< Przycisk [Anuluj] ma byæ widoczny.

/** @} */

/**
 * Do ustawienia w #CNT_NOTIFY.
 * #IMI_NOTIFY znajdzie @a notify wg. kolejki wiadomoœci.
 * Je¿eli zostanie podane jako @a p1 do #IMI_NOTIFY, zostan¹ sprawdzone wszystkie powiadomienia i ustawione powiadomienie w tray'u.
 */
#define NOTIFY_AUTO         -2
#define NOTIFY_IMPORTANT    1

/**
 * Kontakt mo¿e mieæ nowe powiadomienie. Sprawdzana jest kolejka wiadomoœci.
 * @param p1 Numer kontaktu.
 */
#define IMI_NOTIFY          IMI_BASE + 1010

/**
 * Ustawia nowe powiadomienie dla kontaktu lub u¿ytkownika (np nowa wiadomoœæ).
 * @param p1 (sNOTIFY *) powiadomienie.
 */
#define IMI_NEWNOTIFY       IMI_BASE + 1011

/**
 * Kontakt wykazuje aktywnoœæ.
 * @param p1 (int) id kontaktu
 */
#define IMI_CNT_ACTIVITY    IMI_BASE + 1013

/**
 * Wyzerowanie aktywnoœci kontaktu.
 * @param p1 (int) id kontaktu
 */
#define IMI_CNT_DEACTIVATE  IMI_BASE + 1014

/**
 * Otwarcie okna informacji o kontakcie.
 * @param p1 (int) id kontaktu
 */
#define IMI_CNT_DETAILS     IMI_BASE + 1015

/**
 * Odœwie¿a podsumowanie dla kontaktu w oknie informacji (tylko gdy jest otwarte).
 * @param p1 (int) id kontaktu
 */
#define IMI_CNT_DETAILS_SUMMARIZE   IMI_BASE + 1016

/**
 * Czy u¿ytkownik pisze coœ do podanego kontaktu?
 * @param p1 (int) id kontaktu
 */
#define IMI_CNT_ISCOMPOSING         IMI_BASE + 1020

/**
 * Struktura przesy³ana w #IMI_NEWNOTIFY
 */
struct sNOTIFY {
  unsigned short s_size;
  int cnt;            ///< ID kontaktu którego notify dotyczy.
  sUIAction action;   ///< Akcja która ma byæ wywo³ana.
  int notify;         ///< Ikona powiadomienia #UIIcon.
  char * info;        ///< Informacja.
  int flag;           ///< Flaga (w tej chwili flag nie ma :).

  /**
   * Wype³nia strukturê dla kontaktu na liœcie.
   *
   * @param _action Identyfikator akcji.
   * @param _notify Identyfikator ikonki powiadomienia.
   * @param _cnt Pozycja kontaktu.
   */
  sNOTIFY(sUIAction _action, int _notify, int _cnt = -1) {
    s_size = sizeof(sNOTIFY);
    cnt = _cnt;
    action = _action;
    notify = _notify;
    info = (char*) -1;
  }
  /** 
   * Wype³nia strukturê dla u¿ytkownika.
   *
   * @param _action Identyfikator akcji.
   * @param _notify Identyfikator ikonki powiadomienia.
   * @param _info Tekst powiadomienia (pokazywany w Tray'u). Mo¿e przyj¹æ wartoœci:
   *   - adres do ci¹gu znaków z tekstem.
   *   - 0 - tekst nie zostanie zmieniony.
   *   - -1 - tekst zostanie zmieniony na domyœlny.
   */
  sNOTIFY(sUIAction _action, int _notify, char * _info = 0) {
    s_size = sizeof(sNOTIFY);
    cnt = -1;
    action = _action;
    notify = _notify;
    info = _info;
  }
};

/**
 * UI powinien odœwie¿yæ kontakt.
 * Wysy³ane po zmianie statusu kontaktu, lub którejœ z informacji tekstowych.
 * 
 * @param p1 (int) ID kontaktu
 * @param p2 (bool) jeœli true - dane zostan¹ odœwie¿one równie¿ w oknie z informacjami o kontakcie!
 */
#define IMI_REFRESH_CNT     IMI_BASE + 2000

/**
 * Ca³a lista kontaktów powinna byæ odœwie¿ona.
 *
 * @param p1 (bool) Czy lista ma zostaæ od nowa wype³niona (raczej nie u¿ywane)?
 * @attention Ten komunikat powinien byæ u¿ywany TYLKO po dokonaniu du¿ych zmian na liœcie kontaktów (bez wywo³ywania #IMI_REFRESH_CNT).
 */
#define IMI_REFRESH_LST     IMI_BASE + 2001

/**
 * Otwiera konfiguracjê.
 * @param p1 (int) ID grupy na której ma zostaæ otwarte.
 */
#define IMI_CONFIG          IMI_BASE + 2010 
#define IMI_CONFIGOPENED    IMI_BASE + 2011   ///< Zwraca true jeœli konfiguracja jest otwarta.

#define IMI_LST_SELCOUNT    IMI_BASE + 2020   ///< Zwraca ile kontaktów jest zaznaczonych na liœcie.

/**
 * Zwraca ID zaznaczonego kontaktu.
 * @param p1 (int) numer zaznaczenia poczynaj¹c od 0 do #IMI_LST_SELCOUNT.
 */
#define IMI_LST_GETSELPOS   IMI_BASE + 2021

/*
#define IMI_MSG_INFO        IMI_BASE + 3000
#define IMI_MSG_INFO_undelivered  0
#define IMI_MSG_INFO_delivered    1
*/

#define IMI_MSG_OPEN        IMI_BASE + 3001 ///< (Message*) internal usage
#define IMI_MSG_NOTINLIST   IMI_BASE + 3002 ///< (Message*) internal usage

/**
 * Zwraca stan okna wiadomoœci dla kontaktu.
 * 
 * @param p1 Numer kontaktu.
 *
 * @return 0 - okno zamkniête.
 * @return 1 - okno otwarte, aktywne.
 * @return -1 - okno otwarte, nieaktywne.
 * @return -2 - okno zminimalizowane.
 */
#define IMI_MSG_WINDOWSTATE IMI_BASE + 3003

/**
 * Zwraca adres do procedury okna wpisywania wiadomoœci.
 * Procedura daje obs³ugê skrótów wysy³ania (Ctrl + enter, Alt + s), wykrywanie
 * pisania i historiê ostatnio wpisanych wiadomoœci...
 * Obs³uguje komunikaty WM_KEYDOWN i WM_SYSKEYDOWN.
 */
#define IMI_MSG_EDITCTRL_WNDPROC  IMI_BASE + 3005

/**
 * Dodaje wpis do historii
 * @param p1 (sHISTORYADD*)
 */
#define IMI_HISTORY_ADD     IMI_BASE + 3004

/**
 * Struktura u¿ywana przez #IMI_HISTORY_ADD.
 */
struct sHISTORYADD {
  unsigned short s_size;
  Message * m;  ///< Wiadomoœæ do dodania
  const char * dir;   ///< podkatalog w "history/"
  unsigned int cnt;   ///< Identyfikator kontaktu jeœli ma byæ automatycznie utworzona nazwa
  const char * name;  ///< Nazwa pliku (jeœli cnt == 0)
  /**
   * Oznaczenie sesji.
   *   - @a 0 - osobna wiadomoœæ, lub pocz¹tek sesji
   *   - @a 1 - wiadomoœæ nale¿y do sesji
   */
  int session;

  sHISTORYADD(): s_size(sizeof(sHISTORYADD)) {
    m = 0;
    dir = "";
    cnt = 0;
    name = 0;
    session = 0;
  }
};

/**
 * Dodaje kontakt do listy znalezionych w odpowiedzi na wyszukiwanie.
 * @param p1 (sCNTSEARCH*) Informacje o kontakcie.
 */
#define IMI_CNT_SEARCH_FOUND  IMI_BASE + 4000

/** @} */  // do UI.dll
/** @} */  // IMessage
/** @} */  // Komunikacja pomiedzy wtyczkami

/**
 * @defgroup imig_ Identyfikatory Grup i Akcji
 * @{
 */
 
// Identyfikatory podstawowych akcji w UI tworzacych grupy
#define IMIG_MAINWND        1   ///< G³ówne okno
#define IMIG_BAR            2   ///< Belka glowna
#define IMIG_MSGWND         3   ///< Okno wysy³ania wiadomoœci
#define IMIG_MSGBAR         4   ///< Belka w wysy³aniu wiadomoœci
#define IMIG_MAINTB         8   ///< G³ówny toolbar
#define IMIG_SHORTCUTTB     9   ///< Toolbar ze skrótami
#define IMIG_MAIN           10  ///< G³ówne Menu
#define IMIG_MAIN_OPTIONS   11  ///< Menu opcji
#define IMIG_MAIN_CNT       12  ///< Dodaj kontakt
#define IMIG_MAIN_PROFILE   13  ///< Profile
#define IMIG_HISTORYWND     14

/**
 * Grupa dla ikonek wtyczek w g³ównym oknie... U¿ytkownik mo¿e wybraæ
 * inn¹, wiêc numer aktualnej grupy nale¿y pobraæ przez #IMI_GETPLUGINSGROUP.
 */
#define IMIG_PLUGINS        15
#define IMIG_STATUS         50  ///< Toolbar ze statusami
#define IMIG_EVENT          51  ///< Menu z wiadomoœciami od serwerów.
#define IMIG_EVENT_PARENT   IMIG_STATUS
#define IMIG_HIDDEN         60

#define IMIG_TRAY           20  ///< Tray
#define IMIG_CNT            30  ///< Menu kontaktu
#define IMIG_CFGWND         40  ///< Okno ustawieñ.
#define IMIG_CFG            41  ///< Korzeñ drzewka ustawieñ.
#define IMIG_CFG_CONNECTION 42  ///< Opcje po³¹czeñ.
#define IMIG_CFG_USER       43  ///< Ustawienia u¿ytkownika.
#define IMIG_CFG_SETTINGS   44  ///< Ustawienia programu.
#define IMIG_CFG_UI         45  ///< Ustawienia interfejsu.
#define IMIG_CFG_PLUGS      46  ///< Ustawienia wtyczek.

#define IMIG_NFOWND         70  ///< Okno informacji o kontakcie
#define IMIG_NFO            71  ///< Drzewko kontrolek informacji
#define IMIG_NFO_BAR        72  ///< Belka w oknie informacji o kontakcie
#define IMIG_NFO_TB         73  ///< G³ówny toolbar w oknie informacji o kontakcie

/** @} */ // imig_

/**
 * @defgroup st_ Numery statusów
 * Status sk³ada siê z rodzaju statusu (0 - 0xFF) i flag (0x001 - 0xFFFFFF00).
 * 
 * @{
 */

typedef unsigned int tStatus;

#define ST_OFFLINE          0       ///< Niedostêpny.
#define ST_BLOCKING         1       ///< Blokuj¹cy (GG)

#define ST_SEMIONLINE       0x20    ///< Od tej granicy zaczynaj¹ siê "mniejsze" online'y
#define ST_NA               0x21    ///< Bardzo away (not-available).
#define ST_DND              0x22    ///< Nie przeszkadzaæ.
#define ST_OCCUPIED         0x22    ///< Zajêty (ICQ)

#define ST_ONLINE           0x40    ///< Dostêpny.
#define ST_AWAY             0x41    ///< Away.
#define ST_AUTOAWAY         0x44    ///< Automatyczny away.
#define ST_HIDDEN           0x42    ///< Ukryty.
#define ST_CHAT             0x43    ///< FreeForChat (ICQ)

#define ST_SPECIAL          0x60    ///< Od tej granicy zaczynaj¹ siê statusy specjalne...

#define ST_CONNECTING       0xF1    ///< W trakcie ³¹czenia, tylko dla kontaktu u¿ytkownika.

// flagi
#define ST_NOTINLIST        0x100   ///< Chwilowo na liœcie, zostanie usuniêty po zamkniêciu programu.
#define ST_HIDESHISSTATUS   0x200   ///< Kontakt nie podaje nam swojego statusu
#define ST_IGNORED          0x400   ///< Ignorowany
#define ST_COMPOSING        0x800   ///< Kontakt pisze do nas wiadomoœæ
#define ST_HIDEMYSTATUS     0x1000  ///< Ukrywanie statusu przed kontaktem
#define ST_HIDEBOTH (ST_HIDEMYSTATUS | ST_HIDESHISSTATUS)

// maski
#define ST_MASK             0xFF    ///< Maska statusu.

/** @} */ // st_

/**
 * @defgroup gr_cfg Kolumny konfiguracji
 * Zanim zaczniemy korzystaæ z tablic konfiguracji trzeba zarejestrowaæ typy kolumn
 * wysy³aj¹c sIMessage_setColumn w odpowiedzi na #IM_SETCOLS.
 * 
 * Odczyt i zapis odbywa siê poprzez makra zdefiniowane w @ref gr_cfg.
 * Dodatkowo rdzeñ, UI i wtyczki maj¹ zadeklarowane swoje kolumny.
 * 
 * Kolumny typu #ctypeString zazwyczaj maj¹ te¿ flagê #cflagXor.
 * 
 * @{
 */


/**
 * @defgroup cfg_ Tabela Konfiguracji
 * Niektóre kolumny s¹ w tej chwili nie u¿ywane (by³y w poprzednich wersjach)...
 * Nied³ugo najprawdopodobniej zostan¹ wykorzystane.
 * 
 * @{
 */

#define CFG_0               ((int) 0) ///< nieu¿ywany.
#define CFG_VERSIONS        1         ///< Wersje ostatnio u¿ywanych pluginów.
#define CFG_APPFILE         2         ///< #ctypeString | #cflagNoSave Œcie¿ka do pliku konnekt.exe.
#define CFG_APPDIR          3         ///< #ctypeString | #cflagNoSave Œcie¿ka do katalogu z programem.
#define CFG_PROXY           4         ///< #ctypeInt Czy proxy ma byæ u¿ywane?
#define CFG_PROXY_AUTO      15        ///< #ctypeInt Pobieranie ustawieñ z IE
#define CFG_PROXY_VERSION   5         ///< #ctypeString Rodzaj proxy (w tej chwili tylko "")
#define CFG_PROXY_AUTH      6         ///< #ctypeInt Czy u¿ywaæ logowania?
#define CFG_PROXY_LOGIN     7         ///< #ctypeString Login do proxy.
#define CFG_PROXY_PASS      8         ///< #ctypeString Has³o do proxy.
#define CFG_PROXY_HOST      9         ///< #ctypeString Adres proxy.
#define CFG_PROXY_PORT      10        ///< #ctypeInt  Port proxy.
#define CFG_PROXY_HTTP_ONLY 21        ///< #ctypeInt Proxy tylko dla http.
#define CFG_AUTO_CONNECT    11        ///< #ctypeInt  £¹czenie automatyczne.
#define CFG_12              12        ///< nieu¿ywany
#define CFG_13              13        ///< nieu¿ywany
#define CFG_14              14        ///< nieu¿ywany
#define CFG_IGNORE          16        ///< #ctypeString Lista ignorowanych.
#define CFG_GROUPS          17        ///< #ctypeString Lista grup kontaktów.
#define CFG_CURGROUP        18        ///< #ctypeString Aktualna grupa kontaktów.
#define CFG_DIALUP          19        ///< #ctypeInt Po³¹czenie przez modem
#define CFG_RETRY           20        ///< #ctypeInt Wznawianie po³¹czeñ
#define CFG_LOGHISTORY      22        ///< #ctypeInt Zapisywanie historii
#define CFG_TIMEOUT_RETRY   23
#define CFG_TIMEOUT         24

/**
 * #ctypeInt Okreœla jak ma byæ budowany interfejs. 
 * Na przyk³ad które elementy powinny byæ ukryte, a które w³¹czone.
 * Do obs³ugi u¿ywamy tylko i wy³¹cznie funkcji w Konnekt::ShowBits !
 */
#define CFG_SHOWBITS        25
#define CFG_SHOWBITS_BYHAND 26        ///< #ctypeInt Okreœla które bity w CFG_SHOWBITS by³y ustawiane rêcznie.

// #define C_CFG_COLCOUNT      26        ///< ostatni

/** @} */ // cfg_

/**
 * @defgroup cnt_ Tabela Kontaktów
 * @{
 */

#define CNT_UID             ((unsigned int) 0)  ///< #ctypeString UID.
#define CNT_NET             1                   ///< #ctypeInt Sieæ.
#define CNT_STATUS          2                   ///< #ctypeInt Status.
#define CNT_STATUSINFO      18                  ///< #ctypeString Opis statusu.
#define CNT_NOTIFY          3                   ///< #ctypeInt | #cflagNoSave Ikonka powiadomienia.
#define CNT_HOST            4                   ///< #ctypeString | #cflagNoSave IP.
#define CNT_PORT            5                   ///< #ctypeInt | #cflagNoSave Port.
#define CNT_NAME            6                   ///< #ctypeString Imiê.
#define CNT_SURNAME         7                   ///< #ctypeString Nazwisko.
#define CNT_NICK            17                  ///< #ctypeString Pseudo.
#define CNT_DISPLAY         8                   ///< #ctypeString Nazwa wyœwietlana.
#define CNT_CELLPHONE       9                   ///< #ctypeString Komórka.
#define CNT_PHONE           10                  ///< #ctypeString Stacjonarny.
#define CNT_EMAIL           11                  ///< #ctypeString Email.
#define CNT_INFO            12                  ///< #ctypeString Info.
#define CNT_LOCALITY        13                  ///< #ctypeString Miejscowoœæ.
#define CNT_CITY            CNT_LOCALITY
#define CNT_COUNTRY         14                  ///< #ctypeString Kraj
#define CNT_BORN            19                  ///< #ctypeInt Urodzony YYYYMMDD (w hexie)
#define CNT_GENDER          20                  ///< #ctypeInt P³eæ @ref gender_
#define CNT_CLIENT          15                  ///< #ctypeString Nazwa i wersja u¿ywanego softu.
#define CNT_CLIENTVERSION   28                  ///< #ctypeInt Wersja Softu
#define CNT_LASTMSG         16                  ///< #ctypeInt | #cflagNoSave ID ostatniej wiadomoœci.
#define CNT_GROUP           21                  ///< #ctypeString Grupa do której nale¿y.
#define CNT_ACT_PARENT      22                  ///< #ctypeInt | #cflagNoSave Parent akcji powiadomienia.
#define CNT_ACT_ID          23                  ///< #ctypeInt | #cflagNoSave ID akcji powiadomienia.
#define CNT_INTERNAL        24                  ///< @internal
#define CNT_STREET          25                  ///< #ctypeString - ulica.
#define CNT_POSTALCODE      26                  ///< #ctypeString - kod pocztowy.
#define CNT_NOTIFY_MSG      27                  ///< #ctypeInt | #cflagNoSave ID wiadomoœci powiadomienia.
#define CNT_LASTACTIVITY    29                  ///< #ctypeInt64 Czas ostatniej aktywnoœci.
#define CNT_STATUS_ICON     30                  ///< #ctypeInt Identyfikator ikonki, która ma zast¹piæ ikonê statusu.


#define CNT_MIDDLENAME      31
#define CNT_EMAIL_MORE      32
#define CNT_PHONE_MORE      33
#define CNT_DESCRIPTION     34
#define CNT_FAX             35
#define CNT_URL             36
#define CNT_ADDRESS_MORE    37
#define CNT_REGION          38
#define CNT_POBOX           39

#define CNT_WORK_ORGANIZATION 50
#define CNT_WORK_ORG_UNIT     51
#define CNT_WORK_TITLE        52
#define CNT_WORK_ROLE         53
#define CNT_WORK_EMAIL        54
#define CNT_WORK_URL          55
#define CNT_WORK_PHONE        56
#define CNT_WORK_FAX          57
#define CNT_WORK_STREET       58
#define CNT_WORK_ADDRESS_MORE 59
#define CNT_WORK_POBOX        60
#define CNT_WORK_POSTALCODE   61
#define CNT_WORK_LOCALITY     62
#define CNT_WORK_REGION       63
#define CNT_WORK_COUNTRY      64
#define CNT_WORK_MORE         65

// 40 / 66 // ostatni

#define CNTM_STATUS     ST_MASK
#define CNTM_FLAG       0xFFFFFF00

/** @} */ // cnt_
/** @} */ // gr_cfg

/** 
 * @defgroup gender_ Oznaczenie p³ci
 * @{
 */
 
#define GENDER_UNKNOWN  0 ///< Nieznana
#define GENDER_FEMALE   1 ///< Kobieta
#define GENDER_MALE     2 ///< Mê¿czyzna

/** @} */ // gender_
/** @} */ // gr_shared


#include "core_message.h"
#include "core_ctrl.h"

// #include "obsolete_defines.h"


#pragma pack(pop)
#endif
