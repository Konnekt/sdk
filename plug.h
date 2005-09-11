/*
  nazwa="Plug Shared"
  ver="0.6.18.x"
  info="Podstawowy nag≥Ûwek."
*/

/**
\file
Deklaracje wymagane do komunikacji pomiÍdzy wtyczkami.
*/

// -----------------------------------------------------------------------------------------------
/**
\defgroup gr_shared Komunikacja pomiÍdzy wtyczkami.

Nag≥Ûwek powinien byÊ do≥πczony do kodu wtyczki poprzez plug_export.h .
\{
*/


  #ifndef PLUGSHAREDH
  #define PLUGSHAREDH

  #define KONNEKT_SDK_V 2 ///< wydanie SDK

  #pragma pack(push, 1)
  #define IMPARAM int
  #define tIMP IMPARAM

#include "plug_defs.h"




using namespace Konnekt;

class cCtrl;

/** Struktura uøywana podczas przesy≥ania wiadomoúci.
    Jest uøywana jako bazowa dla wiÍkszych struktur...
  */
  struct sIMessage_base {
    unsigned short s_size; ///< Rozmiar struktury w bajtach (zazwyczaj ustawiane przez kontruktor)
    unsigned int id;   ///< Identyfikator wiadomoúci
    unsigned int flag; ///< Flaga wiadomoúci (na razie powinno byÊ zawsze rÛwne 0)
    int net;  ///< Docelowa sieÊ. 0 - rdzeÒ lub UI
    unsigned int type; ///< Docelowy typ wtyczek
    unsigned int sender; ///< Identyfikator wtyczki wysy≥ajπcej
    sIMessage_base(unsigned int _id, int _net, unsigned int _type)
        :s_size(sizeof(sIMessage_base)),id(_id),net(_net),type(_type),sender(0),flag(0) {}
    sIMessage_base() 
        :s_size(sizeof(sIMessage_base)),id(0),net(0),type(0),sender(0),flag(0) {}
    sIMessage_base(unsigned int _id)
        :s_size(sizeof(sIMessage_base)),id(_id),net(0),type(0),sender(0),flag(0) {}
    sIMessage_base(sIMessage_base * base) {*this = *base;}


  };
  /** Struktura uøywana podczas przesy≥ania wiadomoúci.
    Moøe byÊ strukturπ bazowπ dla wiÍkszych struktur ...
    p1 i p2 mogπ byÊ zastπpione dowolnymi typami, najlepiej o
    rozmiarze po 4 bajty ...
  */
  struct sIMessage_2params: public sIMessage_base {
    IMPARAM p1;   ///< Parametr pierwszy
    IMPARAM p2;   ///< Parametr drugi

    sIMessage_2params(unsigned int _id, int _net, unsigned int _type, IMPARAM _p1, IMPARAM _p2)
        :sIMessage_base(_id , _net, _type), p1(_p1),p2(_p2) {s_size=sizeof(sIMessage_2params);}
    sIMessage_2params()
        :sIMessage_base(), p1(0),p2(0) {s_size=sizeof(sIMessage_2params);}
    sIMessage_2params(unsigned int _id, IMPARAM _p1, IMPARAM _p2) 
        :sIMessage_base(_id), p1(_p1),p2(_p2) {s_size=sizeof(sIMessage_2params);}
    sIMessage_2params(sIMessage_base &base) 
        :sIMessage_base(base.id , base.net , base.type), p1(0),p2(0) 
        {s_size=sizeof(sIMessage_2params);
         this->flag = base.flag;
         this->sender = base.sender;}
  };
  typedef sIMessage_2params sIMessage;
  typedef sIMessage sIMESSAGE;
  #define sIMessage_V1 30 ///< Rozmiar tej struktury w wersji 1 SDK

  typedef IMPARAM (__stdcall*fIMessageProc)(sIMessage_base * msg);

#ifndef _WINDOWS_
    #define HANDLE void *
    #define HINSTANCE void *
    #define HWND void *
#endif

  /** Identyfikatory tablic. */




#include "core_exception.h"



// -----------------------------------------------------------------------------------------------
  /** \defgroup net_ Sieci wtyczek
      \brief \no

      "SieÊ" (Net) wtyczki oznacza przynaleønoúÊ do pewnej grupy.
      Na przyk≥ad jeden protokÛ≥ moøe byÊ obs≥ugiwany przez kilka niezaleønych
      od siebie wtyczek o tej samej wartoúci \a Net. <br> <br>
      WartoúÊ sieci uøywana jest przede wszystkim podczas komunikacji
      pomiÍdzy wtyczkami. W momencie wys≥ania #IMessage , rdzeÒ
      szuka wtyczki o podanej wartoúci \a Net obs≥ugujπcej typ wysy≥anej
      wiadomoúci. W ten sposÛb , moøna rozsy≥aÊ w systemie wiadomoúci
      do \i wtyczek nawet nie wiedzπc o ich istnieniu (a przede wszystkim
      o ich identyfikatorach) ...<br><br>
      Numery sieci gotowych wtyczek bÍdπ do≥πczane do SDK...

      \attention \a Net jest typu <b>unsigned int</b> , przy czym
              wartoúci definiowane przez Was powinny byÊ wiÍksze od @b 255!
			  Wartoúci od 128-255 powinny byÊ WOLNE
      \sa info imt_ #IM_PLUG_NET
  \{
  */
     #define NET_FIRST -2          ///< WiadomoúÊ dotrze do pierwszej wtyczki (dowolnej sieci), ktÛra potrafi jπ obs≥uøyÊ.
     #define NET_BROADCAST -1      ///< WiadomoúÊ dotrze do wtyczek wszystkich sieci.
     #define NET_BC NET_BROADCAST  ///< Odpowiednik #NET_BROADCAST.
     #define NET_NONE 0            ///< Wiadomosci do rdzenia.
     #define NET_NET 1             ///< Wtyczki obs≥ugujπce protokÛ≥ "w≥asny".
     #define NET_INTERNAL 2
     #define NET_SOUND 3           ///< DüwiÍk
     #define NET_UPDATE 4           ///< Update
     #define NET_OTHER   6         ///< Wtyczki nie posiadajπce akcji, nie obs≥ugujπce wiadomoúci itp.

     #define NET_GG  10            ///< Wtyczki obs≥ugujπce protokÛ≥ GG
     #define NET_ICQ 11            ///< Wtyczki obs≥ugujπce protokÛ≥ ICQ
     #define NET_JABBER 12            ///< Wtyczki obs≥ugujπce protokÛ≥ JABBER
     #define NET_EMAIL 13            ///< Wtyczki obs≥ugujπce EMaile
     #define NET_SMS 14            ///< Wtyczki obs≥ugujπce SMSy
	 #define NET_KLAN 15 
	 #define NET_KSTYLE 16
	 #define NET_EXPIMP 17
	 #define NET_KONNFERENCJA 20

	 #define NET_AIM    60            ///< Wtyczki obs≥ugujπce protokÛ≥ AIM
     #define NET_YAHOO  61            ///< Wtyczki obs≥ugujπce protokÛ≥ YAHOO
     #define NET_MSN    62            ///< Wtyczki obs≥ugujπce protokÛ≥ MSN
     #define NET_TLEN   63            ///< Wtyczki obs≥ugujπce protokÛ≥ TLEN
	 

	// sieci tylko do 19 . ich komunikaty to IM_USER + NET * 1000
    // nastÍpne od net 60, tak øeby komunikaty zaczÍ≥y siÍ jako NET * 1000

	 #define NET_KTRANSFER  130 ///< kTransfer 

  // Inne wtyczki
     #define NET_WAPILOT 756       ///< WApilot.dll
	 #define NET_KEASY  227
	 #define NET_KAWAY  666
  /** \} */  // net_

  // Typy IMessage

// -----------------------------------------------------------------------------------------------
  /** \defgroup imt_ Definicje typÛw IMessage ...
    \brief \no

    Kaøda wtyczka powinna zdefiniowaÊ jakiego typu #IMessage potrafi
    przyjπÊ (konkretniej - za co ma odpowiadaÊ).<br><br>
    Typy moøna ≥πczyÊ poprzez '|' (OR). <br><br>
    IMessage() wywo≥any z \a typem innym od #IMT_ALL zostanie
    wys≥any tylko do wtyczek z zadeklarowanπ obs≥ugπ wybranego \a typu.

    \sa #IM_PLUG_NET IMessage()
    \{
  */
        typedef unsigned int tIMtype;

        /// Wszystkie typy.
        #define IMT_ALL 0xFFFFFFFF
        /// WiadomoúÊ bezpoúrednio do rdzenia (lub UI).
        #define IMT_CORE        0

        /// Wiadomoúci tekstowe.
        #define IMT_MESSAGE     1
        /// ProtokÛ≥ sieciowy.
        #define IMT_PROTOCOL    2
        /// Kontakty.
        #define IMT_CONTACT     4
        /// Konfiguracja.
        #define IMT_CONFIG      8
        /// Interfejs Uøytkownika (uøywanie wtyczki UI).
        #define IMT_UI          0x10
        /** Wtyczka obs≥uguje kontakty ca≥ej swojej sieci.
            \attention Ustawienie tego typu spowoduje dodanie nazwy sieci (#IM_PLUG_NETNAME)
            do list sieci w opcjach kontaktu (np. dodawanie , ignorowanie itp.)<br>
            Tylko \b jedna wtyczka z ca≥ej sieci moøe mieÊ ten typ ustawiony!!!
            \sa #IM_PLUG_NETNAME \ref cnt
            */
        #define IMT_NET         0x20  // Rozpoznaje kontakty danej sieci (podczas dodawania , edycji)
        /** Wtyczka obs≥uguje wyszukiwanie kontaktÛw w swojej sieci.
            \attention Podobnie jak w #IMT_UI Ustawienie tego typu spowoduje dodanie nazwy sieci (#IM_PLUG_NETNAME)
            do list sieci w wyszukiwarce kontaktÛw<br>
            Tylko \b jedna wtyczka z ca≥ej sieci moøe mieÊ ten typ ustawiony!!!
            \sa #IM_PLUG_NETNAME \ref cnt
            */
        #define IMT_NETSEARCH   0x40
        /// Wtyczka wykorzystuje system obs≥ugi wiadomoúci tekstowych zawarty w UI.
        #define IMT_MSGUI       0x80
        /// Kontakty w sieci posiadajπ UID (UserID)
        #define IMT_NETUID      0x100
        /// Otrzyma w IM_MSG_RCV wszystkie wiadomoùci , niezale¨nie od \ref net_ "NET".
        #define IMT_ALLMESSAGES 0x200
        /// BÍdzie otrzymywaÊ IM_MSG_ACK.
        #define IMT_MESSAGEACK 0x400
        /** \} */ // imt_

// -----------------------------------------------------------------------------------------------
  /** \defgroup gr_im Identyfikatory IMessage
    \brief \no

    Identyfikator jest \i nazwπ przesy≥anej #IMessage (wiadomoúci
    wewnÍtrznej).
    \par
    Wiadomoúci dzielπ siÍ na (pod wzglÍdem przeznaczenia):
    - IMC_* \ref imc_ od 0 do 10000 #IMI_BASE
    - IMI_* \ref imi_ od 10000 #IMI_BASE do 20000 #IM_BASE
    - IM_*  \ref im_  od 20000 #IM_BASE do 0xFFFFFFFF
    \attention Wiadomoúci \ref imc_ dotrπ \b tylko do \ref core "rdzenia". (niezaleønie od wybranego \a net i \a type w IMessage())
    \attention Wiadomoúci \ref imi_ dotrπ \b tylko do \ref ui "UI". (niezaleønie od wybranego \a net i \a type w IMessage())
    \attention Wiadomoúci \ref im_ < #IM_SHARE mogπ byÊ wysy≥ane \b tylko przez \ref core "rdzeÒ" i \ref ui "ui".
    \attention Wiadomoúci \ref im_ deklarowane przez uøytkownika powinny byÊ tworzone jako #IM_USER + numer (numer najlepiej jako NET * 1000).
    \attention Parametry podawane sπ w kolejnoúci - P1 , P2.

    Wiadomoúci utworzone na potrzeby powstajπcych wtyczek powinny
    byÊ umieszczane w nazwa_wtyczki_shared.h tak, aby inni mogli
    wykorzystywaÊ API wtyczki.

    \sa IMessageProc()
  \{
  */


     #define IMI_BASE 10000 ///< Od tej granicy zaczynajπ siÍ wiadomoúci do \ref ui "UI".
     #define IM_BASE  20000 ///< Od tej granicy zaczynajπ siÍ wiadomoúci do \ref plug "wtyczek" wysy≥ane tylko przez \ref core "rdzeÒ" i \ref ui "UI".
     #define IM_SHARE 30000 ///< Od tej granicy zaczynajπ siÍ wiadomoúci do \ref plug "wtyczek".
     #define IM_USER  40000 ///< Od tej granicy zaczynajπ siÍ wiadomoúci do \ref plug "wtyczek" zdefiniowane przez uøytkownika.

// -----------------------------------------------------------------------------------------------
     /**
       \defgroup im_ do Wtyczek
       \brief \no

       \{
     */

         // Inicjalizacja DLL'a
         #define IM_PLUG_NET       IM_SHARE+10     ///< Zwraca wartoúÊ NET wtyczki.
         #define IM_PLUG_TYPE      IM_SHARE+11     ///< Zwraca wartoúci IMT_ wtyczki.
         #define IM_PLUG_VERSION   IM_SHARE+12     ///< Zwraca opis wersji wtyczki.
         #define IM_PLUG_SIG       IM_SHARE+13     ///< Zwraca sygnaturÍ wtyczki.
         #define IM_PLUG_CORE_V    IM_SHARE+14     ///< Zwraca wymaganπ sygnaturÍ rdzenia (lub 0).
         #define IM_PLUG_UI_V      IM_SHARE+15     ///< Zwraca wymaganπ sygnaturÍ UI (lub 0).
         #define IM_PLUG_NAME      IM_SHARE+16     ///< Zwraca nazwÍ wtyczki.
         #define IM_PLUG_NETNAME   IM_SHARE+17     ///< Zwraca nazwÍ sieci obs≥ugiwanej przez wtyczkÍ (wyúwietlanπ w oknach dialogowych) (lub 0).
         #define IM_PLUG_NETSHORTNAME   IM_SHARE+25     ///< Zwraca skrÛconπ nazwÍ sieci (jak "ICQ", "GG", "JABBER"), aby umoøliwiÊ uøytkownikowi operowanie krÛtkimi nazwami sieci (np. przy tekstowym opisywaniu UIDÛw w parametrach) (lub 0).
		 #define IM_PLUG_UIDNAME   IM_SHARE+26   ///< Zwraca nazwÍ UIDu typowπ dla obs≥ugiwanej sieci, do wyúwietlania w oknach dialogowych (np "JID", "UIN" itd...) (lub 0)
         #define IM_PLUG_CERT      IM_BASE+18      ///< Zastrzeøone dla wtyczek specjalnych.
         #define IM_PLUG_INFO      IM_BASE+19     ///< Wtyczka moøe zalogowaÊ informacjÍ o swoim "stanie".
         #define IM_PLUG_SDKVERSION IM_BASE+20     ///< Zwraca #KONNEKT_SDK_V.

         #define IM_PLUG_PRIORITY  IM_BASE+21     ///<Wtyczka podaje swÛj priorytet w kolejkach (im wyøszy, tym znajdzie siÍ wczeúniej).
                                                   /// Wszystkie "zwyk≥e" wtyczki mogπ nie obs≥ugiwaÊ tej wiadomoúci, lub po prostu zwracaÊ 0 (ich priorytet zostanie ustawiony na PLUGP_STANDARD.
                                                   /// Dwie wtyczki o tym samym priorytecie ustawiane sπ w kolejnoúci uøytkownika.
                                                   /// Jeøeli twoja wtyczka nie jest uzaleøniona od kolejnoúci, NIE ustawiaj jej!
                                                   /// DziÍki priorytetom wiadomoúci mogπ byÊ obs≥ugiwane w odpowiedniej kolejnoúci.
                                                   /// \return (PLUGP_enum) pozycja
     /** Grupy priorytetÛw dla #IM_PLUG_PRIORITY */
     enum PLUGP_enum {
         PLUGP_LOWEST = 0x10,  /// Koniec listy
         PLUGP_LOW = 0x40,  
         PLUGP_STANDARD = 0x80, /// Zwyk≥e wtyczki
         PLUGP_HIGH = 0xB0,  
         PLUGP_HIGHEST = 0xE0,  /// Poczπtek listy
         PLUGP_NONE = 0x0  /// W efekcie to samo co PLUGP_STANDARD
     };


         #define IM_PLUG_INIT      IM_BASE+1
         /**< Inicjalizacja wtyczki. Pierwszy przes≥any IMessage nakazujπcy wtyczce inicjalizacjÍ kodu.
                 \param cCtrl adres struktury sterujπcej
                 \param ID identyfikator wtyczki
         */

         #define IM_PLUG_DEINIT    IM_BASE+2      ///< Za chwilÍ uchwyt do wtyczki zostanie zwolniony. Najlepszy moment øeby posprzπtaÊ.
         #define IM_PLUG_INITEX    IM_BASE+3      ///< Zastrzeøone dla wtyczek specjalnych.
		 #define IM_PLUG_ARGS      IM_BASE+24	  /**< Podaje wtyczkom argumenty przes≥ane do programu.
Wysy≥ane jest zaraz po uruchomieniu, oraz gdy zostanie uruchomiona kolejna instancja programu na tym samym profilu. W drugim przypadku podawane sπ argumenty przekazane do drugiej instancji...
Argumenty majπ tπ samπ strukturÍ co __argc i __argv.
Komunikat przesy≥any jest przy pomocy @b sIMessage_plugArgs .*/ 
		/** Struktura uøywana w #IM_PLUG_ARGS.*/
		struct sIMessage_plugArgs: public sIMessage_base {
			unsigned int argc;   ///< IloúÊ argumentÛw w argv
			const char * const * argv;   ///< Tablica wskaünikÛw do argumentÛw

			sIMessage_plugArgs(unsigned int argc , const char * const * argv)
				:sIMessage_base(IM_PLUG_ARGS , NET_BC, IMT_ALL), argc(argc),argv(argv) 
			{
				s_size=sizeof(*this);
			}

			const char * getArg(unsigned int i, const char * def = "") {
				return (i < this->argc) ? this->argv[i] : def;
			}
			bool argEq(unsigned int i, const char * cmp);
		};

/** Przekazuje komendÍ wpisanπ w oknie @Dev. Komunikat przesy≥any jest przy pomocy @b sIMessage_debugCommand. 
	@return 0
*/
		#define IM_DEBUG_COMMAND  IM_BASE+25

/** Jeøeli podczas od≥πczania wtyczki z jakiegoú wzglÍdu nie powinno byÊ wywo≥ywane FreeLibrary trzeba obs≥uøyÊ ten komunikat i zwrÛciÊ 1. */
		#define IM_PLUG_DONTFREELIBRARY  IM_BASE+26

/** Wszystkie wtyczki zosta≥y zainicjalizowane...
*/
		#define IM_ALLPLUGINSINITIALIZED IM_BASE + 22 

/** Za chwilÍ wtyczka o podanym ID zostanie od≥πczona.
	@param p1 (int) ID wtyczki
*/
		 #define IM_PLUG_PLUGOUT IM_BASE + 23     
        
/** Ta wersja wtyczki uruchamiana jest w tym profilu po raz pierwszy.
  @param p1 (int) Poprzednia wersja, lub 0. 
  Format wersji to w hexie: MNNRRBBB - Major, miNor, Release, Build.
  W plug_func.h moøna znaleüÊ makra do szybkiego wyciπgania tych wartoúci. 
*/
		#define IM_PLUG_UPDATE    IM_BASE+30     

         #define IM_GET_STATUS     IM_SHARE+31    ///< Jeøeli wtyczka obs≥uguje sieÊ, powinna zwrÛciÊ swÛj aktualny status.
                                                    /// \return (int) status
         #define IM_GET_STATUSINFO IM_SHARE+32    ///< Jeøeli wtyczka obs≥uguje sieÊ, powinna zwrÛciÊ swÛj aktualny opis statusu.
                                                    /// \return (const char *) opis statusu
		 #define IM_GET_UID		   IM_SHARE+33    /**< Jeøeli wtyczka obs≥uguje sieÊ, powinna zwrÛciÊ UID uøytkownika programu w swojej sieci
													    @return (const char *) UID uøytkownika
													*/

         #define IM_NEW_PROFILE    IM_BASE + 40   ///< Oznacza pierwsze uruchomienie danego profilu. Najlepszy moment øeby siÍ przywitaÊ.
         #define IM_CANTQUIT       IM_BASE + 41   ///< ZwrÛcenie \i true spowoduje anulowanie zamykania programu.
         #define IM_PASSWORDCHANGED IM_BASE + 42  ///< Oznacza zmianÍ has≥a dla profilu.

		 #define IM_THREADSTART    IM_BASE + 43 ///< Aktualny wπtek w≥aúnie zosta≥ uruchomiony. Lepiej polegaÊ jednak na DllMain!
	 	 #define IM_THREADEND	   IM_BASE + 44 ///< Aktualny wπtek w≥aúnie siÍ koÒczy. Lepiej polegaÊ jednak na DllMain!

		 #define IM_MSG_RCV       IM_BASE+100
         /**< Wtyczka powinna sprawdziÊ czy obs≥uguje dany typ wiadomoúci.
           Wtyczki odpytywane sπ "od koÒca". Ostatnia, ktÛra zwrÛci
           IM_MSG_RCV_ok bÍdzie otrzymywaÊ rÛwnieø IM_MSG_OPEN.
           \param p1 (cMessage *) wiadomoúÊ.
           \param p2 (bool) \i true - wiadomoúÊ w≥aúnie przysz≥a , \i false - wiadomoúÊ zosta≥a za≥adowana z pliku.
           \return (int) Po≥πczone flagi \ref im_msg_, lub 0 jeúli nie obs≥uguje takich wiadomoúci.
         */
         #define IM_MSG_SEND      IM_SHARE+100 /**< WiadomoúÊ powinna zostaÊ wys≥ana.
           \param p1 (cMessage *) WiadomoúÊ
           \return Jeúli siÍ uda≥o powinno zrÛciÊ \ref im_msg_.
         */
         #define IM_MSG_OPEN      IM_SHARE+101    /**< WiadomoúÊ powinna zostaÊ otwarta.
           \param p1 (cMessage *) WiadomoúÊ
           \return Jeúli siÍ uda≥o powinno zrÛciÊ \ref im_msg_.
         */
         #define IM_MSG_ACK      IM_BASE+102    /**< Potwierdzenie wys≥ania wiadomoúci.
           \param p1 (cMessageAck *) Potwierdzenie. ID jest ustawiony na ID potwierdzanej wiadomoúci (ktÛra jeszcze siedzi w kolejce i moøna jπ odczytaÊ).
         */

         /** @defgroup im_msg_ Zwroty z IM_MSG_* 
             #IM_MSG_RCV , #IM_MSG_SEND i #IM_MSG_OPEN mogπ zwrÛciÊ po≥πczone
             takie flagi.
             @{
            */
            #define IM_MSG_ok     1 ///< Flaga zwrotna #IM_MSG_RCV - Musi byÊ ustawiona jesli wtyczka zamierza obs≥uøyÊ wiadomoúÊ.
            #define IM_MSG_delete 2 ///< WiadomoúÊ powinna zostaÊ niezw≥ocznie usuniÍta...
            #define IM_MSG_update 4 ///< ZawartoúÊ wiadomoúci zosta≥a zmieniona i powinna zostaÊ zaktualizowana jej kopia w kolejce.
            #define IM_MSG_processing 8 ///< Flaga zwrotna #IM_MSG_OPEN i #IM_MSG_SEND - WiadomoúÊ jest dalej przetwarzana (np w osobnym wπtku) i zostanie usuniÍta z kolejki poprzez #IMC_MESSAGEREMOVE,
                                         ///  lub zakoÒczy przetwarzanie poprzez #IMC_MESSAGEPROCESSED.
         /** @} */
         #define IM_MSG_CHARLIMIT IM_BASE+105    ///< Zapytanie o limit znakÛw na wiadomoúÊ
                                            ///  \return Limit iloúci znakÛw na wiadomoúÊ. 0 - bez limitu
         // Config (IMT_CONFIG)
         #define IM_SETCOLS  IM_BASE+1001   ///< W tym momencie wtyczka powinna zadeklarowaÊ wszystkie kolumny w tablicach.

         #define IM_CFG_SAVE      IM_BASE+1010 ///< Ustawienia zaraz zostanπ zapisane do pliku.
         #define IM_CFG_LOAD      IM_BASE+1011 ///< Ustawienia zosta≥y wczytane.
         #define IM_CFG_CHANGED   IM_BASE+1020 ///< Ustawienia zostaly zmienione przez uøytkownika.
         // UI
         #define IM_UI_PREPARE    IM_BASE+2000 ///< Najlepszy moment aby przygotowaÊ interfejs (np zdefiniowaÊ Akcje).

         #define IM_START         IM_BASE+2100 ///< Wtyczka powinna wystartowaÊ.
         #define IM_END           IM_BASE+2101 ///< Wtyczka powinna zakoÒczyÊ dzia≥anie.
												/// @param p1 (bool) I powinna to zrobiÊ jak najszybciej...

         #define IM_BEFOREEND     IM_BASE+2102 ///< Za chwilÍ zostanie rozes≥ane IM_END, ostatnia chwila, kiedy cCtrl::IsRunning() zwraca true.
												/// @param p1 (bool) Zamykanie jest w trybie "natychmiastowym". Naleøy wykonywaÊ jak najmniej operacji...

		 #define IM_UIACTION      IM_BASE+2200 ///< Powiadomienie o zdarzeniu w akcji.
                                               /// \param p1 (cUIActionNotify *) Powiadomienie.

         //  IMT_PROTOCOL
         #define IM_CONNECT       IM_SHARE+3000 /**< Moøna zaczπÊ siÍ ≥πczyÊ.
		 @param p1 (int) Liczba ponowionych prÛb po≥πczenia
		 */
         #define IM_DISCONNECT    IM_SHARE+3001 ///< Trzeba siÍ roz≥πczyÊ.
         #define IM_AWAY          IM_SHARE+3002 ///< Program wchodzi w tryb Auto-Away.
         #define IM_BACK          IM_SHARE+3003 ///< Program powraca z trybu Auto-Away.
         #define IM_NEEDCONNECTION IM_BASE+3004 ///< Wysy≥ana do kontrolek zaraz po w≥πczeniu
                                           ///  automatycznych po≥πczeÒ i na chwilÍ przed
                                           ///  wykonaniem pierwszego testu na istnienie po≥πczenia.
                                           ///  \attention W tej wiadomoúci #IMC_SETCONNECT
                                           ///  powinny wywo≥ywac wtyczki ktÛre ZAWSZE potrzebujπ po≥πczeÒ
                                           ///  (niezaleønie od ustawienia #CFG_AUTOCONNECT).<br>
                                           ///  Pozosta≥e powinny zg≥osiÊ #IMC_SETCONNECT np. w #IM_PREPARE.

        #define  IM_CHANGESTATUS  IM_SHARE+3005  ///< Jeøeli wtyczka obs≥uguje sieÊ, powinna zmieniÊ swÛj status...
                                                 /// \param p1 (int) status (lub -1 jeúli nie zmieniamy)
                                                 /// \param p2 (char*) opis (lub 0 jeúli nie zmieniamy)
        #define  IM_ISCONNECTED   IM_SHARE+3006  ///< Trzeba zwrÛciÊ 1 jeúli jesteúmy po≥πczeni.
         #define IM_PING	       IM_SHARE+3007 ///< Wtyczka zamawia≥a PING'a (na razie nie obs≥ugiwane...)

         #define IM_CNT_UPLOAD    IM_SHARE+4000  /**< Informacje o kontakcie @a p1 zosta≥y zmienione i moga byÊ np. zapisane na serwerze.
                                                  @param p1 (int) ID kontaktu do wys≥ania
                                                  @param p2 (bool) 0 - info powinno byÊ wczytywane bezpoúrednio z tabeli. 
																   1 - info powinno byÊ wczytywane jako wartoúci odpowiednich akcji w oknie z informacjami o kontakcie (uøywajπc UIActionCfgGetValue())
												 */
         #define IM_CNT_DOWNLOAD  IM_SHARE+4001  /**< Informacje o kontakcie \a p1 powinny zostaÊ zaktualizowane (np. pobrane z serwera).
                                                  @param p1 (int) ID kontaktu do pobrania
                                                  @param p2 (bool) 0 - info powinno zostaÊ zapisane bezpoúrednio w tabeli. 
																	1 - info powinno byÊ ustawione jako wartoúci odpowiednich akcji w oknie z informacjami o kontakcie (uøywajπc UIActionCfgSetValue())
												  */


/** Kontakt zaraz zostanie usuniÍty.
	\param p1 (int) ID kontaktu
	\param p2 (bool) true - usuniÍcie zosta≥o potwierdzone przez uzytkownika.*/
		#define IM_CNT_REMOVE    IM_BASE+4002  
/** Kontakt zosta≥ usuniety.
	\param p1 (int) ID kontaktu
	\param p2 (bool) true - usuniÍcie zosta≥o potwierdzone przez uzytkownika.*/
		#define IM_CNT_REMOVED    IM_BASE+4005 
         #define IM_CNT_ADD       IM_BASE+4003  ///< Kontakt zosta≥ dodany
                                                 ///  \param p1 (int) ID kontaktu
         #define IM_CNT_ADDING    IM_BASE+4004  ///< Kontakt jest w trakcie tworzenia (ktÛre moøe zostaÊ ew. przerwane)
                                                 ///  Parametry kontaktu nie sπ jeszcze ustalone.
                                                 ///  \param p1 (int) ID kontaktu
/** Øπdanie szukania kontaktu (np. w katalogu sieci)
	\param p1 (sCNTSEARCH *) parametry wyszukiwania
	*/
		#define IM_CNT_SEARCH    IM_BASE+4010  
/** KtÛraú z cech kontaktu (np. UID) zosta≥a zmieniona. Przesy≥ane przy pomocy sIMessage_CntChanged. Jeøeli przecastujesz to na sIMessage_2params to \a p1 jest ID kontaktu.
*/
		#define IM_CNT_CHANGED   IM_BASE+4006  

         /** Struktura do przesy≥ania #IM_CNT_CHANGED.*/
            struct sIMessage_CntChanged:public sIMessage_base {
                unsigned int _cntID; ///< ID kontaktu
				union {
					///< Oznacza co zosta≥o zmienione. 
					struct {
						unsigned net : 1;
						unsigned uid : 1;
						unsigned group : 1;
					} _changed; 
					unsigned int _changed_bitmap;
				};
                unsigned int _oldNet; ///< Poprzednia wartoúÊ net tego kontaktu
                const char * _oldUID; ///< Poprzednia wartoúÊ UID
                sIMessage_CntChanged(int msgID , int cntID):sIMessage_base(msgID),_cntID(cntID),_changed_bitmap(0),_oldNet(NET_NONE),_oldUID(0){s_size=sizeof(*this);}
                sIMessage_CntChanged(const sIMessage_base * base){
                    if (base->s_size == sizeof(*this)) {
                        *this = *(const sIMessage_CntChanged*)(base);
                    } else if (base->s_size >= sizeof(sIMessage_2params)) {
                        this->flag = base->flag;
                        this->id = base->id;
                        this->net = base->net;
                        this->sender = base->sender;
                        this->type = base->type;
                        this->s_size = sizeof(*this);
                        this->_cntID = ((const sIMessage_2params*)(base))->p1;
                        this->_changed_bitmap = ((const sIMessage_2params*)(base))->p2;
						this->_oldNet = NET_NONE;
						this->_oldUID = 0;
                    } else throw 0;
                }
            };

         #define IM_CNT_STATUSCHANGE IM_BASE+4011 ///< Status kontaktu zaraz ulegnie zmianie.
                                             ///  sIMessage_StatusChange *

         #define IM_CNT_COMPOSING IM_SHARE+4030 /**< Uøytkownik pisze wiadomoúÊ do wskazanego kontaktu.
											      Wys≥ane do interfejsu spowoduje rozes≥anie #IM_CNT_COMPOSING do wszystkich wtyczek
												  i jeøeli w przeciπgu kilkunastu sekund nie zostanie wys≥ane ponownie rozeúle
												  #IM_CNT_COMPOSING_STOP.
                                                  @param p1 (int) ID kontaktu
											     */
         #define IM_CNT_COMPOSING_STOP IM_SHARE+4031 /**< Uøytkownik przesta≥ pisaÊ do wskazanego kontaktu.
												 Wys≥ane do interfejsu spowoduje rozes≥anie do wtyczek #IM_CNT_COMPOSING_STOP jeøeli
												 w przeciπgu ostatnich kilkunastu sekund wystπpi≥o zdarzenie #IM_CNT_COMPOSING z tym samym kontaktem.
                                                     @param p1 (int) ID kontaktu
												     */


         #define IM_STATUSCHANGE IM_BASE+4012 ///< Status wtyczki zaraz ulegnie zmianie.
                                             ///  sIMessage_StatusChange *

         /** Struktura do przesy≥ania #IM_CNT_STATUSCHANGE i #IM_STATUSCHANGE.*/
            struct sIMessage_StatusChange:public sIMessage_base {
                union {
                    unsigned int cntID; ///< ID kontaktu
                    unsigned int plugID; ///< ID wtyczki zmieniajπcej status.
                };
                unsigned int status; ///< Nowy status, ktÛry zaraz zostanie ustawiony. -1 oznacza brak zmiany.
                const char * info; ///< Nowy opis statusu, ktÛry zaraz zostanie ustawiony. 0 oznacza brak zmiany.

                sIMessage_StatusChange(int msgID , int cntID , unsigned int status, const char * info):sIMessage_base(msgID),cntID(cntID),status(status),info(info){s_size=sizeof(*this);}
                sIMessage_StatusChange(const sIMessage_base * base) {
                    if (base->s_size < sizeof(*this)) throw cKException_Msg(0 , base);
                    *this = *(sIMessage_StatusChange*)base;
                    s_size=sizeof(*this);
                }
            };


         #define IM_GRP_CHANGED   IM_BASE+4020 ///< Lista grup uleg≥a zmianie.
         #define IM_IGN_CHANGED   IM_BASE+4021 ///< Lista ignorowanych kontaktÛw uleg≥a zmianie.
                                                /// \param p1 (int) sieÊ >0 - kontakt zosta≥ dodany, <0 - usuniÍty
                                                /// \param p2 (char*) 

    
         /** Parametry wyszukiwania/wyniki wyszukiwania.
            Struktura wykorzystywana zarÛwno podczas wysy≥ania zapytania, jak i zwracania wynikÛw.
         */
         struct sCNTSEARCH {
            unsigned short s_size; ///< Musi zawieraÊ rozmiar struktury. Ustawiany przez kontruktor.
            int status;   ///< Podczas szukania - 1 - szukaj tylko online. Podczas zwracania - status kontaktu.
            char uid      [256] /// UID
                ,name     [101] /// ImiÍ
                ,surname  [101] /// Nazwisko
                ,nick     [101] /// Ksywa
                ,city     [51] /// Miasto
                ,email    [101]/// Email
                ,phone    [51] /// Telefon
                ,other    [256] /// Inne (tylko w odpowiedzi)
                ;
            int gender; ///< P≥eÊ 0 - nieznana , 1 - kobieta , 2 - mÍøczyzna
            int born_min; ///< Urodzony, OD roku
            int born_max; ///< Urodzony, DO roku
            int net;    ///< Numer sieci.
            int start;  ///< Od jakiej pozycji pokazywaÊ dalej.
                        /// Przy zwracaniu, ostatni znaleziony kontakt powinien mieÊ ustawiony \start
                        /// na pozycjÍ od ktÛrej moøna wznowiÊ wyszukiwanie.
            HANDLE handle; ///< Uchwyt do okna wyszukiwania
            sCNTSEARCH() {s_size=sizeof(sCNTSEARCH);start=0;handle=0;net=0;gender=0;born_min=born_max=0;
                uid[0]=0;
                name[0]=0;
                surname[0]=0;
                nick[0]=0;
                city[0]=0;
                email[0]=0;
                phone[0]=0;
                other[0]=0;
            }
         };
         #define sCNTSEARCH_V1 496
  /** \} */  // Wiadomoúci do WTYCZEK

// -----------------------------------------------------------------------------------------------
  /**
    \defgroup imc_ do Rdzenia
    \brief \no

    \{
  */
        #define IMC_LOG              1 ///< Jeøeli program jest debugowany , zapisuje tekst w konnekt.log . WiadomoúÊ nie jest rozpoznawana przez Core (wiec ustawi blad!)
                                        ///  \param p1 (char*) tekst.
        #define IMC_GETPROFILE       2 ///< Zwraca nazwÍ profilu.
                                        ///  \return (char *)

        #define IMC_DEBUG            3 ///< Otwiera okno developera
        #define IMC_ISDEBUG          4 ///< Zwraca true gdy jest w trybie developera.
        #define IMC_ISBETA           9 ///< Zwraca true gdy jest w trybie beta.
        #define IMC_BETA             40 ///< Otwiera okno beta-testera
        #define IMC_REPORT           41 ///< Otwiera okno raportowania
        #define IMC_PLUGS            42 ///< Otwiera okno wtyczek
        #define IMC_NET_TYPE         43 ///< Pobiera ≥πcznπ wartoúÊ flag typÛw (#IM_PLUG_TYPE) ze wszystkich wtyczek danej sieci.
                                         ///  \param p1 (int) sieÊ
		#define IMC_SESSION_ID		 44 /**< Zwraca identyfikator sesji profilu Konnekta.
Przy jego pomocy moøna odrÛøniÊ dwie instancje korzystajπce z rÛønych profili...
@return (const char*) identyfikator sesji (MD5 úcieøki katalogu profilu)
										 */
		#define IMC_GET_HINTERNET	 45 /**< Zwraca globalny uchwyt sesji WinInet otwartej przez InternetOpen (z ustawionym Proxy wg. konfiguracji). 
										 @return (HINTERNET) uchwyt, NIE moøna go zamykaÊ!*/
		#define IMC_HINTERNET_OPEN	 46 /**< Tworzy i zwraca uchwyt sesji WinInet otwartej przez InternetOpen (z ustawionym Proxy wg. konfiguracji). 
										 @param p1 (const char*) UserAgent
										 @return (HINTERNET) uchwyt, trzeba go zamykaÊ!*/
		#define IMC_GET_MAINTHREAD   47 /**< Zwraca uchwyt do g≥Ûwnego wπtku.
										 @return (HANDLE)
										 */
		#define IMC_DEBUG_COMMAND 48

		struct sIMessage_debugCommand: public sIMessage_plugArgs {
			enum enAsync {
				synchronous = 0,
				duringAsynchronous = 1,
				asynchronous = 2,
			} async;
			sIMessage_debugCommand(unsigned int argc, const char * const * argv, enAsync async = synchronous)
				:sIMessage_plugArgs(argc, argv), async(async) {
					id = IMC_DEBUG_COMMAND;
					net = 0;
					type = 0;
					s_size=sizeof(*this);
				}
		};


		#define IMC_ARGC             5 ///< Zwraca liczbÍ parametrÛw przekazanych do programu.
        #define IMC_ARGV             6 ///  Zwraca parametr \a p1. 
								        ///  \param p1 (int) numer parametru
								        ///  \return (char*) 

        #define IMC_ISWINXP          60 ///< Zwraca 1, jeúli korzystamy z ComCtl6 na winXP.
        #define IMC_ISNEWPROFILE     61 ///< Zwraca 1, gdy jest to pierwsze uruchomienie na tym profilu.  
        #define IMC_ISNEWVERSION     62 ///< Zwraca 1, gdy jest to pierwsze uruchomienie na nowej wersji.
                                         ///  \warning Wynik jest ma≥o miarodajny i moøe byÊ fa≥szywy! Wiarygodne wyniki
                                         ///  zostanπ przes≥ane w IM_PLUG_UPDATE
        #define IMC_CONNECTED        7 ///< Zwraca true, jeúli jesteúmy pod≥πczeni do internetu.
        #define IMC_VERSION          8 ///< Zwraca wersjÍ rdzenia.
								        ///  \param p1 (char *) Wskaünik do ciπgu znakÛw do zapisania wersji tekstowo, lub NULL.
                                        ///  \return (int) #VERSION_TO_NUM


        #define IMC_SHUTDOWN        10 ///< Zamyka program.
										/// @param p1 (bool) Czy zamknπÊ go natychmiastowo?
        #define IMC_DISCONNECT      11 ///< Roz≥πcza wszystkie wtyczki z sieci.
        #define IMC_RESTART         17 ///< Restartuje program.
        #define IMC_PROFILESDIR     23 ///< åcieøka do katalogu z profilami.
                                        ///  \return (const char *)
        #define IMC_PROFILEDIR      12 ///< åcieøka do katalogu z profilem.
                                        ///  \return (const char *)
        #define IMC_RESTORECURDIR   24 ///< Przywrca aktywnπ úcieøkÍ na katalog programu i jπ zwraca.
									   ///  @return (const char *) katalog z programem		
        #define IMC_KONNEKTDIR      IMC_RESTORECURDIR ///< Przywraca aktywnπ úcieøkÍ na katalog programu i jπ zwraca.
        #define IMC_GETBETALOGIN    25 
        #define IMC_GETBETAPASSMD5  27 
        #define IMC_GETBETAANONYMOUS 31
/** Zwraca "numer seryjny" instalacji Konnekta, losowa liczba uøywana najczÍúciej do rozrÛøniania kopii programu w statystykach */
		#define IMC_GETSERIALNUMBER       33 
		#define IMC_LOGDIR			29 ///< Zwraca úcieøkÍ do katalogu z log'ami.
										/// @return (char*) úcieøka zakoÒczona '\\'
		#define IMC_TEMPDIR			32 ///< Zwraca úcieøkÍ do katalogu tymczasowego.
										/// @return (char*) úcieøka zakoÒczona '\\'
        #define IMC_PROFILECHANGE   13 ///< Zmienia/tworzy profil.
                                        ///  \param p1 (char*) nazwa
                                        ///  \param p2 (bool) true jeúli profil ma byÊ utworzony
                                        ///  \return true jeúli siÍ uda≥o
        #define IMC_PROFILEREMOVE   14 ///< Usuwa aktualnie uøywany profil.
        #define IMC_PROFILEPASS     15 ///< Otwiera okno do ustawiania has≥a.
        #define IMC_GETMD5DIGEST    16 ///< Zwraca has≥o profilu jako MD5Digest.
                                        ///  \param p1 (unsigned char [16]) bufor do zapisania.

        #define IMC_SAVE_CFG        20 ///< Zapisuje ustawienia na dysk.
        #define IMC_SAVE_CNT        21 ///< Zapisuje kontakty na dysk.
        #define IMC_SAVE_MSG        22 ///< Zapisuje kolejkÍ wiadomoúci na dysk.
		#define IMC_CFG_CHANGED	28

        #define IMC_SETCONNECT      30 ///< Ustawia wtyczkÍ na liúcie "rzπdanych po≥πczeÒ".
                                        ///  W chwili wykrycia po≥πczenia z internetem, 
                                        ///  lub gdy jest po≥πczenie po kilkudziesiÍciu sekundach
                                        ///  zostanie wys≥any do wtyczki komunikat #IM_CONNECT.
                                        /// \param p1 (bool) stan - 1 ≥πcz , 0 - przestaÒ prÛbowaÊ

        #define IMC_THREADSTART     50 // WiadomoúÊ wykorzystywana TYLKO przez UI
        #define IMC_THREADEND	   51   // WiadomoúÊ wykorzystywana TYLKO przez UI

        #define IMC_NEWMESSAGE     100 ///< Dodaje wiadomoúÊ do kolejki.
                                        ///  \attention ZawartoúÊ struktury moøe ulec zmianie! Jeøeli tworzymy bufory tekstowe, zwalniaÊ trzeba je przez
                                        ///  lokalne kopie adresÛw, a nie wskaüniki w strukturze!!!
                                        ///  \param p1 (cMessage*) wiadomoúÊ.
                                        ///  \return (int) id wiadomosci

        //       #define NMF_SEND      1   // Flagi wiadomosci

        #define IMC_MESSAGEQUEUE   101 ///< Sprawdza kolejkÍ wiadomoúci.
                                        ///  PrÛbuje przyjπÊ/rozes≥aÊ oczekujπce wiadomoúci.
                                        ///  \param p1 (sMESSAGESELECT*) ktÛre wiadomoúci  maja zostaÊ sprawdzone.
        #define IMC_MESSAGENOTIFY  102 ///< Szuka powiadomienia o nowej wiadomoúci dla danego UIDa w kolejce wiadomoúci.
                                        ///  \param p1 (sMESSAGENOTIFY*) struktura podajπca czego szukaÊ i przyjmujπca wynik.
        #define IMC_MESSAGEWAITING 103 ///< Podaje ile wiadomoúci oczekuje w kolejce
                                        ///  \param p1 (sMESSAGESELECT*) ktÛre wiadomoúci majπ zostaÊ uwzglÍdnione
                                        ///  \return (int) liczba wiadomoúci spe≥niajπcych kryteria
        #define IMC_MESSAGEREMOVE  104 ///< Usuwa wiadomoúci z kolejki.
                                        ///  \param p1 (sMESSAGESELECT*) Rodzaj wiadomoúci do usuniÍcia
                                        ///  \param p2 (int) Ile maxymalnie usunπÊ
                                        ///  \return false gdy siÍ nie powiedzie
        #define IMC_MESSAGEGET     106 ///< Pobiera pierwszπ wiadomoúÊ ktÛra spe≥nia kryteria.
                                        ///  \param p1 (sMESSAGESELECT*) Rodzaj wiadomoúci do pobrania.
                                        ///  \param p2 (cMessage*) Struktura do ktÛrej zostanie zapisana wiadomoúÊ.
                                        ///  \retrun 1 - jeúli siÍ powiod≥o
        #define IMC_MESSAGEACK     107 ///< Potwierdzenie wys≥ania wiadomoúci.
                                        ///  W cMessageAck::id \b musimy podaÊ ID potwierdzanej wiadomoúci.
                                        ///  Ustawienie msg i ext jest opcjonalne.
                                        ///  \param p1 (cMessageAck*) Struktura z potwierdzeniem.
        #define IMC_MESSAGEPROCESSED 108 ///< ZakoÒczenie przetwarzania.
                                          /// Po skoÒczeniu przetwarzania wiadomoúci, na ktÛrπ odpowiedzieliúmy flagπ IM_MSG_processing
                                          /// wysy≥amy ten komunikat, by rdzeÒ "odznaczy≥" naszπ wiadomoúÊ. 
                                          /// #IMC_MESSAGEPROCESSED wysy≥a siÍ tylko, gdy wiadomoúÊ nie zosta≥a od razu usuniÍta.
                                          /// \param p1 (int) ID wiadomoúci.
                                          /// \param p2 (bool) true - wiadomoúÊ moøe zostaÊ usuniÍta

        /** Struktura s≥uøπca do wybierania wiadomoúci.
            \sa #IMC_MESSAGEREMOVE #IMC_MESSAGEWAITING #IMC_MESSAGEGET #IMC_MESSAGEQUEUE*/
        typedef  struct sMESSAGESELECT {
            unsigned short s_size;
            int net; ///< SieÊ kontaktu. Ustaw na #NET_BC aby uøyÊ wszystkich sieci.
            const char * uid;  ///< UID kontaktu. Ustaw 0 aby uøyÊ wszystkich.
            int type; ///< Typ wiadomoúci. Ustaw na -1 øeby uøyÊ wszystkich.
            unsigned int wflag; ///< Tylko wiadomoúci posiadajπce te flagi. 0 øeby uøyÊ wszystkich.
            unsigned int woflag; ///< Tylko wiadomoúci nie posiadajπce tych flag. 0 øeby uøyÊ wszystkich.
            int id; ///< ID wiadomoúci, -1 øeby uøyÊ wszystkich.
			unsigned int position; ///< KtÛre z kolei przyjπÊ dopasowanie?
            sMESSAGESELECT() {s_size=sizeof(sMESSAGESELECT);net=NET_BC;uid=0;type=-1;wflag=0;woflag=0;id=-1;position=0;}
            sMESSAGESELECT(int _net , const char * _uid=0 , unsigned int _type = -1 , unsigned int _wflag=0 , unsigned int _woflag=0) {
                s_size=sizeof(sMESSAGESELECT);
                net=_net;
                uid=_uid;
                type=_type;
                wflag=_wflag;
                woflag=_woflag;
                id=-1;
				position = 0;
            }

        } sMESSAGEPOP , sMESSAGEWAITING;
        #define sMESSAGEWAITING_V1 22

/** Zwraca ID kontaktu.
Jeøeli @a net bÍdzie ustawiony na NET_NONE w UID moøna przekazaÊ (tekstem) ID kontaktu. Jeøeli kontakt o danym ID istnieje, ID zostanie zwrÛcone. FunkcjonalnoúÊ ta moøe s≥uøyÊ g≥Ûwnie do "przemycania" bezpoúrednich identyfikatorÛw kontaktÛw do f-cji ktÛre przyjmujπ tylko wartoúci net i uid.

@param p1 (int) net
@param p2 (char*) UID
@return (int) ID
*/
		#define IMC_FINDCONTACT    200 
        #define IMC_PLUG_COUNT    240 ///< Zwraca liczbÍ wtyczek.
        #define IMC_PLUG_HANDLE    241 ///< Zwraca windowsowy uchwyt do wtyczki.
                                        ///  \param p1 (int) pozycja na liúcie wtyczek.
                                        ///  \return (int) HINSTANCE
        #define IMC_PLUG_ID        243 ///< Zwraca ID wtyczki.
                                        ///  \param p1 (int) pozycja na liúcie wtyczek.
                                        ///  \return (int) ID
        #define IMC_PLUG_FILE     242  ///< Zwraca úcieøkÍ do pliku dll wtyczki.
                                        ///  \param p1 (int) pozycja na liúcie wtyczek.
                                        ///  \return (char*) úcieøka
        #define IMC_PLUGID_HANDLE  244 ///< Zwraca windowsowy uchwyt do wtyczki.
                                        ///  \param p1 (int) ID wtyczki.
                                        ///  \return (HINSTANCE) uchwyt
        #define IMC_PLUGID_POS     245 ///< Zwraca pozycjÍ wtyczki.
                                        ///  \param p1 (int) ID wtyczki.
                                        ///  \return (int) pozycja
        #define IMC_FINDPLUG       247 ///< Zwraca ID wtyczki.
                                        ///  \param p1 (int) NET wtyczki.
                                        ///  \param p2 (int) Szukane flagi IMT_.
                                        ///  \return (int) ID
        #define IMC_FINDPLUG_BYSIG    248 ///< Zwraca ID wtyczki.
                                        ///  \param p1 (char*) SIG.
                                        ///  \return (int) ID
        #define IMC_FINDPLUG_BYNAME    249 ///< Zwraca ID wtyczki.
                                        ///  \param p1 (char*) name.
                                        ///  \return (int) ID
        #define IMC_PLUG_VERSION    26 ///< Zwraca wersjÍ wtyczki.
                                        ///  \param p1 (int) Pozycja wtyczki na liúcie, lub -1 aby sprawdziÊ wersjÍ rdzenia.
								        ///  \param p2 (char *) Wskaünik do ciπgu znakÛw do zapisania wersji tekstowo, lub NULL.
                                        ///  \return (int) #VERSION_TO_NUM

		/** Od≥πcza wtyczkÍ o podanym identyfikatorze podajπc opowiednie uzasadnienie.
		    
		*/
		struct sIMessage_plugOut:public sIMessage_base {
			const static int __msgID = 250;
			int _plugID;
			const char * _reason;
			enum enRestart {
				erNo = 0 , erAsk = 1 , erYes = 2 , erAskShut = 3 , erShut = 4

			} _restart; ///< Czy restartowaÊ program?
			enum enUnload{
				  euNow=1 /// Nie powinno byÊ ustawiane pÛüniej niø w #IMI_ALLPLUGSINITIALIZED
				, euNextStart=2
				, euNowAndOnNextStart=3
			} _unload; ///< Kiedy jπ od≥πczyÊ?
            sIMessage_plugOut(int plugID , const char * reason , enRestart restart = erAsk , enUnload unload = euNextStart):sIMessage_base(__msgID)
				,_plugID(plugID),_reason(reason),_restart(restart),_unload(unload){s_size=sizeof(*this);}
        };


        #define IMC_STATUSCHANGE   246 ///< Informuje rdzeÒ, øe za chwilÍ nastπpi zmiana statusu wtyczki.
                                        ///  RdzeÒ rozsy≥a IM_STATUSCHANGE.
                                        ///  \warning Ten komunikat trzeba wys≥aÊ PRZED zmianπ statusu, nie trzeba podawaÊ
                                        ///  \a plugID. Jako \a status i \a info trzeba podaÊ dane, ktÛre zaraz zostanπ ustawione.
                                        ///  sIMessage_StatusChange


        #define IMC_CNT_IGNORED    310 ///< Sprawdza czy kontakt jest ignorowany.
                                        ///  \param p1 (int) net
                                        ///  \param p2 (char*) UID
                                        ///  \return true jeúli jest.
        #define IMC_CNT_FIND       IMC_FINDCONTACT ///< \no

/**Sprawdza czy kontakt o podanym ID istnieje.
@param p1 (int) ID.*/
		#define IMC_CNT_IDEXISTS   233 

/** Dodaje kontakt.
Po ustawieniu parametrÛw kontaktu, lub od razu po #IMC_CNT_ADD trzeba wys≥aÊ #IMC_CNT_CHANGED
@param p1 (int) sieÊ
@param p2 (int) UID
@return (int) ID nowego kontaktu
*/
		#define IMC_CNT_ADD        230 

/**Usuwa kontakt
@param p1 (int) ID
@param p2 (bool) true - uøytkownik zostanie zapytany o zgodÍ.
*/
		#define IMC_CNT_REMOVE     231 

/**Zwraca iloúÊ kontaktÛw.
@return (int) liczba kontaktÛw.
*/
		#define IMC_CNT_COUNT      201 

/** Sprawdza czy podany kontakt znajduje sie w grupie.
@param p1 (int) ID kontaktu.
@param p2 (char*) - grupa do sprawdzenia (jeúli == 0 sprawdzi w grupie aktywnej)
@return (bool) true jeúli znajduje siÍ...
*/
		#define IMC_CNT_INGROUP    305 


/** Kontakt zosta≥ zmieniony.
Komunikat powinien byÊ wysy≥any \b tylko w sytuacji zmiany #CNT_UID, #CNT_NET, lub zaraz po dodaniu!
Do wszystkich wtyczek z typem #IMT_CONTACT zostanie rozes≥ane #IM_CNT_CHANGED, lub #IM_CNT_ADD.
Nie ma juø potrzeby wysy≥ania #IMI_REFRESH_CNT
@param p1 ID kontaktu.
*/
		#define IMC_CNT_CHANGED     232 
        #define IMC_CNT_SETSTATUS  234 ///< Zmienia status kontaktu.
                                        ///  sIMessage_StatusChange


        #define IMC_IGN_FIND       IMC_CNT_IGNORED
        #define IMC_IGN_ADD        311 /**< Dodaje kontakt do listy ignorowanych.
                                         \param p1 (int) sieÊ
                                         \param p2 (char*) UID
										 */
        #define IMC_IGN_DEL        312 /**< Usuwa kontakt z listy ignorowanych.
                                          \param p1 (int) sieÊ
                                          \param p2 (char*) UID
										  */

        #define IMC_GRP_FIND       300 /**< Sprawdza czy grupa istnieje.
                                          \param p1 (char*) nazwa grupy.
                                          \return (bool) true jeúli istnieje.
										  */
        #define IMC_GRP_ADD        301 /**< Dodaje grupÍ.
                                          \param p1 (char*) nazwa grupy.
										  */
        #define IMC_GRP_DEL        302 /**< Usuwa grupÍ.
                                          \param p1 (char*) nazwa grupy.
										  */
        #define IMC_GRP_RENAME     303 /**< Zmienia nazwÍ grupy.
                                          \param p1 (char*) stara nazwa grupy.
                                          \param p2 (char*) nowa nazwa grupy.
										  */


        /** Komunikat do rejestrowania kolumn w tablicach.
            \attention Moøe byÊ wysy≥ane TYLKO PODCZAS przetwarzania komunikatu #IM_SETCOLS.
		*/
		class sIMessage_setColumn: public sIMessage_base {
		public:
			const static int __msgID = 1102;
			tTable _table; ///< Tablica w ktÛrej ustawiamy kolumnÍ
			int _id; ///< ID kolumny.
			int _type; ///< typ kolumny (patrz \ref dt_ct_).
			union {
			   int _def; ///< WartoúÊ domyúlna.
			   const char * _def_ch; ///< WartoúÊ domyúlna dla kolumn #DT_CT_PCHAR (musi byÊ ciπgle w pamiÍci!)
			   __int64 * _def_p64; ///< WartoúÊ domyúlna dla kolumn #DT_CT_64 (musi byÊ ciπgle w pamiÍci!)
			};
			const char * _name;
			sIMessage_setColumn(tTable table , int id , int type , int def , const char * name = 0):sIMessage_base(__msgID){
				init(table , id , type , def , name);
			}
			sIMessage_setColumn(tTable table , int id , int type , const char * def , const char * name = 0):sIMessage_base(__msgID){
				init(table , id , type , (int)def , name);
			}
			sIMessage_setColumn(int id , int type , int def , const char * name = 0):sIMessage_base(__msgID){
				init(0 , id , type , (int)def , name);
			}
			sIMessage_setColumn(int id , int type , const char * def , const char * name = 0):sIMessage_base(__msgID){
				init(0 , id , type , (int)def , name);
			}
		private:
			void init(tTable table , int id , int type , int def , const char * name){
				_table = table;
				_id = id;
				_type = type;
				_def = def;
				_name = name;
				s_size = sizeof(*this);
			}
		};
		
        #define IMC_CFG_SAVE     1010  ///< Wszystkie ustawienia zostanπ zapisane.

        // W32
        #define IMC_GETINSTANCE    2000 ///< Zwraca HINSTANCE aplikacji.

        // internal use only.
        #define IMC_GETMSGCOLDESC  3000

        /** @defgroup imc_mru_ MRU.
            Obs≥uga listy ostatnio uøywanych.
            @{
        */
        #define MRU_SET_LOADFIRST  0x1 ///< ZawartoúÊ listy zostanie najpierw za≥adowana (dzia≥ajπ teø flagi dla MRU_GET_ !)
        #define MRU_GET_ONEBUFF    0x10 ///< sMRU::buffer jest wskaünikiem do bufora (o rozmiarze sMRU::buffSize), ktÛry zostanie uøyty do wszystkich operacji
        #define MRU_GET_USETEMP    0x20 ///< zostanie uøyty tymczasowy bufor wewnÍtrzny rdzenia.
            /** Struktura uøywana przez IMC_MRU_* */
            struct sMRU {
                int flags; ///< Flagi
                const char * name; ///< Nazwa zestawu
                int count; ///< Rozmiar zestawu
                int buffSize; ///< Rozmiar buforÛw dla #IMC_MRU_GET
                const char * current; ///< Przy #IMC_MRU_SET i #IMC_MRU_UPDATE podajemy dodawanπ wartoúÊ.
                union {
                    char ** values; ///< Tablica \a count buforÛw. Przy #IMC_MRU_GET muszπ mieÊ rozmiar podany w \a buffSize.
                                    /// Jeøeli jest mniej buforÛw niø w count, ostatnia pozycja musi byÊ rÛwna 0.
                    char * buffer; ///< Wskaünik do pojedyÒczego bufora trzymajπcego wszystkie informacje
                };
                const char * removed; /// #IMC_MRU_UPDATE zapisze tu element, ktÛry zosta≥ odrzucony.
                sMRU():flags(0),count(0),buffSize(0),name(0),current(0),values(0){}
            };
            #define IMC_MRU_SET  400 ///< (sIMessage_MRU*) Ustawia listÍ MRU. 
            #define IMC_MRU_GET  401 ///< (sIMessage_MRU*) Pobiera listÍ MRU. 
            #define IMC_MRU_UPDATE  402 ///< (sIMessage_MRU*) Aktualizuje listÍ MRU. 

            /** Struktura do przesy≥ania #IMC_MRU_GET, #IMC_MRU_SET i #IMC_MRU_UPDATE.*/
            struct sIMessage_MRU:public sIMessage_base {
                sMRU * MRU; ///< \brief \no
                sIMessage_MRU(int id , sMRU * MRU):sIMessage_base(id),MRU(MRU){s_size=sizeof(*this);}
            };
        /** @} */


  /** \} */  // Wiadomoúci do rdzenia

        
// -----------------------------------------------------------------------------------------------
  // Wiadomosci do UI.dll
  /**
    \defgroup imi_ do UI
    \brief \no

    \{
  */



        #define IMI_PREPARE   IMI_BASE+0   // Tylko dla Rdzenia 
        #define IMI_DEBUG     IMI_BASE+1   ///< Otwiera okno debugowania interfejsu.
                                            ///  DostÍpne tylko w wersjach Debug i Beta.
		#define IMI_SET_SHOWBITS IMI_BASE+10 ///< Otwiera okno ustawiania ShowBits
		#define IMI_SET_PLUGINS IMI_BASE+11 ///< Otwiera okno wyboru wtyczek
        //  #define IMI_UIINVALIDATE IMI_BASE+100 // (0,0)  -  odnawia listy akcji
// -----------------------------------------------------------------------------------------------
        /**\defgroup imi_action_ Obs≥uga akcji.
		  System akcji w interfejsie odpowiada za obs≥ugÍ np. kontrolek
		  w konfiguracji, menusÛw czy przyciskÛw na toolbarach.
		  @warning Akcje dla kontaktÛw korzystajπ tylko z jednego obiektu akcji, ktÛry jest "prze≥πczany" na aktualnie øπdany kontakt. Nie powinno siÍ wiÍc ustawiaÊ parametrÛw akcji zaleønie od kontaktu!

           \{
        */
// -----------------------------------------------------------------------------------------------
            /** @defgroup ac_ Numery kontaktÛw akcji. 
                @{ */
                #define AC_USER 0      ///< Akcja jest przypisana do uøytkownika.
                #define AC_NONE -1L    ///< Akcja nie jest przypisana do øadnego kontaktu.
                #define AC_CURRENT -2L ///< Ostatnio przypisany kontakt.
            /** @} */

            #define IMI_ACTION    IMI_BASE+101  /**< Wstawia akcjÍ.
                                                    \param p1 (#sUIActionInfo*) Ustawienia akcji. MUSZ• byÊ ustawione \a parent i \a id.
                                                    */
            #define IMI_GROUP     IMI_BASE+102  /**< Wstawia grupÍ.
                                                    Dzia≥a tak samo jak #IMI_ACTION z #ACTS_GROUP ustawionym w \a status.
                                                    \param p1 (#sUIActionInfo*) Ustawienia akcji. MUSZ• byÊ ustawione \a parent i \a id.
                                                    \attention Identyfikatory grup \b muszπ byÊ niepowtarzalne!
                                                    */
            #define IMI_ACTION_CALL  IMI_BASE+103 /**< Wywo≥uje akcjÍ (w innej wtyczce).
                                                        \param p1 (sUIActionNotify_base*) Powiadomienie o zdarzeniu do wys≥ania.
                                                    */
            #define IMI_ACTION_GET   IMI_BASE+107 /**< Pobiera w≥aúciwoúci akcji.
                                                        \param p1 (sUIActionInfo *). Musi mieÊ ustawiony \a parent , \a id , oraz \a mask (jeøeli \a mask == 0 pobiera wszystko).

                                                        \attention Przy pobieraniu \a txt trzeba ustawiÊ \a txt na bufor \b char * i \a txtSize na rozmiar tego bufora.
                                                                    Jeøeli \a txt == 0 zostanie ono ustawione na 2 kilobajtowy bufor wewnÍtrzny.
                                                                    <br><Br>
                                                                    Zawsze ustawia \a pos , \a handle i \a type .
                                                    */
            #define IMI_ACTION_SET   IMI_BASE+108 /**< Ustawia w≥aúciwoúci akcji.
                                                        \param p1  (sUIActionInfo *). Musi mieÊ ustawiony \a parent , \a id , oraz \a mask (jeøeli \a mask == 0 ustawia wszystko).
                                                        \attention Moøna zmieniaÊ tylko: \a status , \a exStyle , \a p1 , \a p2 , \a param , \a ico i \a txt.
                                                        */
            #define IMI_ACTION_GETVALUE IMI_BASE+106 /**< Pobiera wartoúÊ kontrolki w konfiguracji.
                                                        \param p1  (sUIActionInfo *). WartoúÊ zostanie ustawiona w \a txt.
                                                        \return (char *) (to samo co w \a txt), lub 0 jeúli wystπpi b≥πd.
                                                    */
            #define IMI_ACTION_SETVALUE IMI_BASE+110 /**< Ustawia wartoúÊ kontrolki w konfiguracji.
                                                        \param p1  (sUIActionInfo *). WartoúÊ musi znajdowaÊ siÍ w \a txt.
                                                        \return (char *) (to samo co w \a txt), lub 0 jeúli wystπpi b≥πd.
                                                    */
            #define IMI_GROUP_ACTIONSCOUNT IMI_BASE+111 /**< Zwraca iloúÊ akcji naleøπcych do podanej grupy.
                                                        \param p1 (sUIAction*)
                                                        \return (int)
                                                    */
            #define IMI_ACTION_EXISTS  IMI_BASE+112 /**< Sprawdza czy akcja istnieje.
                                                        \param p1 (sUIAction*)
                                                        \return (bool)
                                                        */
            #define IMI_ACTION_ISGROUP  IMI_BASE+113 /**< Sprawdza czy akcja jest grupπ.
                                                        \param p1 (int) parent
                                                        \return (bool)
                                                        */
            #define IMI_ACTION_GETID  IMI_BASE+114 /**< Zwraca identyfikator akcji na podanej pozycji w grupie.
                                                        \param p1 (int) parent
                                                        \param p2 (int) pozycja
                                                        \return (int) ID
                                                        */
            #define IMI_ACTION_REMOVE IMI_BASE+115 /**< Usuwa akcjÍ.
                                                        \warning Moøe zostaÊ wywo≥ane TYLKO gdy akcja nie jest utworzona!
                                                        \param p1 (sUIAction*) akcja do usuniÍcia
                                                        \return (bool)
                                                        */
            #define IMI_ACTION_GETTYPE IMI_BASE+116/**< Pobiera typ akcji (\ref act_).
                                                        \param p1 (sUIAction*) Akcja
                                                        \return (int)
                                                        */
            #define IMI_GROUP_GETHANDLE IMI_BASE+117/**< Pobiera uchwyt grupy (np. uchwyt g≥Ûwnego okna)
                                                        \param p1 (sUIAction*) Akcja
                                                        \return (HANDLE)
                                                        */
            #define IMI_ACTION_FINDPARENT  IMI_BASE+118/**< Znajduje rodzica akcji o identykatorze sUIAction::id, zaczynajπc
                                                             szukanie w sUIAction::parent. Jeøeli p2 jest rÛwne 1, 
                                                             znaleziony identyfikator zostanie usatwiony w strukturze przekazanej
                                                             w polu p1.
                                                        \param p1 (sUIAction*) Akcja. 
                                                        \param p2 (bool) Czy zapisaÊ wynik w p1?
                                                        \return (int)
                                                        */
			#define IMI_GETPLUGINSGROUP IMI_BASE+119 /**< Pobiera identyfikator grupy, ktÛrπ uøytkownik
														   wskaza≥ jako grupÍ dla menu wtyczek. 
														   @return (int) ID grupy*/
			#define IMI_GROUP_MAKECFG IMI_BASE+120   /**< Jeøeli grupa jest grupπ konfiguracji i okno konfiguracji jest otwarte upewnia siÍ, czy wszystkie kontrolki grupy sπ utworzone.
														   @param p1 (sUIAction*) Akcja.
														   @return (bool) uda≥o siÍ, lub nie
														   */
			#define IMI_ACTION_SETCNT IMI_BASE+121   /**< Przypisuje kontrolkÍ do kontaktu (podanego w sUIAction).
														   @param p1 (sUIAction*) Akcja.
														   @param p2 (bool) Czy ustawiaÊ rekurencyjnie?
														   */
			#define IMI_ACTION_GETINDEX IMI_BASE+122   /**< Pobiera indeks kontrolki (numer przypisywany w WinApi oknom, przyciskom na toolbarach itd).
														   @param p1 (sUIAction*) Akcja.
														   @return (int) indeks
														   */
			#define IMI_ACTION_GETOWNER IMI_BASE+123   /**< Pobiera identyfikator wtyczki, ktÛra utworzy≥a akcjÍ i obs≥uguje jej komunikaty
														   @param p1 (sUIAction*) Akcja.
														   @return (int) ID wtyczki
														   */
			#define IMI_ACTION_MAKEPOPUPMENU IMI_BASE+150 /**< Uruchamia i obs≥uguje menu utworzone ze wskazanej grupy akcji
														   Komunikat wysy≥amy jako (sIMessage_UIMakePopup*)
														   W akcji naleøy podaÊ identyfikator kontaktu (lub 0) do ktÛrego menu ma byÊ przypisane...
														   */

/** Identyfikacja akcji.
            */
            struct sUIAction {
                unsigned int id;     ///< Identyfikator akcji.
                unsigned int parent; ///< Identyfikator grupy.
                int cnt;    ///< Identyfikator kontaktu dla ktÛrego zmieniamy/pobieramy parametry akcji
                                    ///  , #AC_NONE, lub #AC_CURRENT ...
                sUIAction() {parent = id = 0;cnt=AC_CURRENT;}
                /**\brief \no

                */
                sUIAction(unsigned int _parent , unsigned int _id,unsigned int _cnt=AC_CURRENT) {
                parent = _parent;
                id = _id;
                cnt = _cnt;
                }
            };
            typedef sUIAction sUIACTION;
// -----------------------------------------------------------------------------------------------
            /** \defgroup uiaim_ Maski dla sUIActionInfo.
            \{
            */
                #define UIAIM_STATUS   1 ///< sUIActionInfo::status i sUIActionInfo::statusMask sπ ustawione.
                #define UIAIM_EXSTYLE  2 ///< sUIActionInfo::exStyle i sUIActionInfo::exStyleMas sπ ustawione.
                #define UIAIM_P1       4 ///< sUIActionInfo::p1 jest ustawiony.
                #define UIAIM_P2       8 ///< sUIActionInfo::p2 jest ustawiony.
                #define UIAIM_PARAM 0x10 ///< sUIActionInfo::param jest ustawiony.
                #define UIAIM_ICO   UIAIM_P1
                #define UIAIM_TXT  0x40  ///< sUIActionInfo::txt i sUIActionInfo::txtSize sπ ustawione.

                #define UIAIM_COL   UIAIM_P1 ///< \blank
                #define UIAIM_POS   0x100  ///< \blank
                #define UIAIM_SIZE  0x200  ///< \blank
                #define UIAIM_HANDLE 0x400  ///< \blank
                #define UIAIM_TYPE  0x800  ///< \blank

				#define UIAIM_VALUE_CONVERT 0x10000 ///< Ustawiona wartoúÊ akcji powinna zostaÊ przekonwertowana (np. z formatu wartoúci akcji do formatu pola w bazie i na odwrÛt)

                #define UIAIM_ALL   0x35F ///< Wszystkie powyøsze.
                
            // uiaim_
            /** @} */


            /** W≥aúciwoúci akcji.
            \sa #IMI_ACTION_GET #IMI_ACTION_SET
            */
            struct sUIActionInfo {
                unsigned short s_size;
                sUIAction act;  ///< Identyfikatory.
                unsigned int pos;  ///<Pozycja na liúcie w grupie. Pos == -1 oznacza "na koÒcu" (podczas \ref IMI_ACTION "wstawiania").
                                /// \todo Powinien potrafiÊ rÛwnieø zmieniÊ pozycjÍ.
                unsigned int type; ///<Typ kontrolki przypisanej do akcji ( \ref actt_ ).
                void * handle;     ///<Uchwyt do kontrolki akcji (np w windowsach uchwyty do HWND lub HMENU)
                void * reserved;
                unsigned int mask;       /**< Maska.
                                    Oznacza ktÛre pola w strukturze sπ
                                    ustawione.
                                    \attention Pole \a act musi byÊ \b zawsze ustawione! <br>
                                    \sa \ref uiaim_
                                    */
                unsigned int status;     ///<\ref actm_ "Status".
                unsigned int statusMask; ///<Oznacza ktÛre pola w \a status powinny byÊ zmienione.
                unsigned int exStyle;    /**<Dodatkowe style . \attention W tej chwili nie sπ one uøywane! */
                unsigned int exStyleMask;///<Oznacza ktÛre pola w \a exStyle powinny byÊ zmienione.
                char * txt;     ///< Tekst przypisany do akcji.
                unsigned int    txtSize; ///< Rozmiar bufora w txt.
                int param;      ///<Parametr uøytkownika.
                int p1;         ///<Dodatkowy parametr uzywany przez typy kontrolek.
                int p2;         ///<Dodatkowy parametr uzywany przez typy kontrolek.
                short w,h; ///< WysokoúÊ / szerokoúÊ kontrolki

                /**
                \blank
                */
                sUIActionInfo() {s_size=sizeof(sUIActionInfo);mask = act.parent = act.id = pos = 0;handle = 0;}
                /**
                \blank
                */
                sUIActionInfo(int _parent , int _id , int _pos , int _status=0 , char * _txt = 0 , int _p1=0 , short _w=0 , short _h=0 , int _p2=0 , int _param = 0) {
                    s_size=sizeof(sUIActionInfo);
                    mask = UIAIM_ALL;
                    act.parent=_parent;
                    act.id=_id;
                    pos=_pos;
                    txt=_txt;
                    status=_status;
                    statusMask=-1;
                    exStyleMask=0;
                    p1=_p1;
                    p2=_p2;
                    param=_param;
                    w=_w;
                    h=_h;
                }

                /**
                \blank
                */
                sUIActionInfo(int _parent , int _id) {
                    s_size=sizeof(sUIActionInfo);
                    act.parent = _parent;
                    act.id = _id;
                    mask = 0;

                }
                /**
                \blank
                */
                sUIActionInfo(sUIAction a) {
                    s_size=sizeof(sUIActionInfo);
                    act = a;
                    mask = 0;
                }
            };

                /**
                W≥aúciwoúci akcji do konfiguracji.
                */
            struct sUIActionInfo_cfg: sUIActionInfo {
                short x,y; ///< PrzesuniÍcie wzglÍdem osi x/y
                /**
                \blank
                */
                sUIActionInfo_cfg():sUIActionInfo(){s_size = sizeof(sUIActionInfo_cfg);x=y=0;}
                /**
                \blank
                */
                sUIActionInfo_cfg(int _parent , int _id , int _pos=-1 , int _status=0 , char * _txt = 0 , int _col=0 , short _w=0 , short _h=0 , int _p2=0 , int _param = 0)
                : sUIActionInfo(_parent , _id , _pos , _status , _txt , _col, _p2 , _param){
                    s_size = sizeof(sUIActionInfo_cfg);
                    x=y=w=h=0;
                }
                /**
                \blank
                */
                sUIActionInfo_cfg(int _parent , int _id , int _pos=-1 , int _status=0 , char * _txt = 0 , int _col=0 , short _x=0 , short _y=0 , short _w=0 , short _h=0 , int _p2=0 , int _param = 0)
                : sUIActionInfo(_parent , _id , _pos , _status , _txt , _col, _w , _h , _p2 , _param)
                {
                    s_size = sizeof(sUIActionInfo_cfg);
                    x=_x;
                    y=_y;
                }
            };
            #define sUIActionInfo_V1 sizeof(sUIActionInfo)
            /**Powiadomienie.
            Struktura podstawowa wysy≥ana razem z IM_ACTION.

            \sa actn_
            */
            struct sUIActionNotify_base {
                unsigned short s_size;
                sUIAction act;  ///< Identyfikator akcji.
                unsigned int code;  ///< Numer powiadomienia.
                int reserved;   ///< Pozycja zarezerwowana . Musi byÊ rÛwna 0.
                sUIActionNotify_base(sUIAction _act , unsigned int _code)
                    :s_size(sizeof(sUIActionNotify_base)) , act(_act) , code(_code) , reserved(0) {}
                sUIActionNotify_base(unsigned int _code=0) 
                    :s_size(sizeof(sUIActionNotify_base)) , act(sUIAction()) , code(_code) , reserved(0) {}
            };

            struct sUIActionNotify_2params:public sUIActionNotify_base {
                unsigned int notify1;    ///< Parametr 1.
                unsigned int notify2;    ///< Parametr 2.

                /**
                \blank
                */
                sUIActionNotify_2params(sUIAction _act , unsigned int _code , int _not1 , int _not2 ) 
                    :sUIActionNotify_base(_act , _code) , notify1(_not1) , notify2(_not2)
                    {  s_size=sizeof(sUIActionNotify_2params);}
                sUIActionNotify_2params(unsigned int _code , int _not1 , int _not2 ) 
                    :sUIActionNotify_base(_code) , notify1(_not1) , notify2(_not2)
                    {  s_size=sizeof(sUIActionNotify_2params);}
                sUIActionNotify_2params()
                    :sUIActionNotify_base() , notify1(0) , notify2(0)
                    {  s_size=sizeof(sUIActionNotify_2params);}
                sUIActionNotify_2params(sUIActionNotify_base &base)
                    :sUIActionNotify_base(base.act , base.code) , notify1(0) , notify2(0)
                    {  s_size=sizeof(sUIActionNotify_2params);
                       this->reserved = base.reserved;
                    }
            };
            typedef sUIActionNotify_2params sUIActionNotify;

            struct sUIActionNotify_buff:public sUIActionNotify_base {
                char * buff;
                unsigned int buffSize;
                sUIActionNotify_buff()
                    :sUIActionNotify_base() , buff(0) , buffSize(0)
                    {s_size=sizeof(*this);}
            };


         /** Struktura do przesy≥ania #IMI_ACTION_MAKEPOPUPMENU.*/
            struct sIMessage_UIMakePopup:public sIMessage_base {
                sUIAction _action; ///< Identyfikator akcji-grupy z ktÛrej ma byÊ utworzone menu, razem z identyfikatorem przypisanego do niego kontaktu.
                int _uFlags; ///< Flagi. Atrybut przekazywany do f-cji WinApi - TrackPopupMenu()
				int _x; ///< Pozycja X
				int _y; ///< Pozycja Y
				int _nReserved; ///< Atrybut przekazywany do f-cji WinApi - TrackPopupMenu()
				int _startFrom; ///< Pierwsza akcja (od 0) do uwzglÍdnienia w menu (uøywane na przyk≥ad w tzw. chevronach)
				void * _hWnd; ///< Okno - w≥aúciciel (Aby uniknπÊ problemÛw z ikonkami najlepiej podaÊ 0 lub uchwyty do okien g≥Ûwnego/rozmowy/wiÍcej). Atrybut przekazywany do f-cji WinApi - TrackPopupMenu()
				const void * _prcRect; ///< Atrybut przekazywany do f-cji WinApi - TrackPopupMenu()
                sIMessage_UIMakePopup(sUIAction & action , int uFlags, int x, int y, int nReserved, void * hWnd, const void *prcRect = 0 , int startFrom = 0)
					:sIMessage_base(IMI_ACTION_MAKEPOPUPMENU),_action(action),_uFlags(uFlags),_x(x),_y(y),_nReserved(nReserved),_hWnd(hWnd),_prcRect(prcRect),_startFrom(startFrom) 
					{s_size=sizeof(*this);}

            };


        // imi_action_
        /** @} */

        #define IMI_ICONRES    IMI_BASE+109  ///< Wstawia ikonkÍ z zasobÛw wtyczki do listy ikonek UI.
                                                /// \deprecated O wiele lepiej uøywaÊ #IMI_ICONREGISTER i funkcji pomocniczych.
                                                /// \param p1 (int) Identyfikator ikonki na liúcie (patrz #UIIcon). 
                                                /// \param p2 (int) Identyfikator ikonki w zasobach wtyczki.
        #define IMI_ICONREGISTER IMI_BASE+130 /**<Rejestruje ikonkÍ/bitmapÍ w UI.
                                                @warning Przy zastÍpowaniu bitmap na listach poprzednie kopie NIE sπ usuwane!
                                                   Najlepiej podmieniaÊ ikonki jak najrzadziej siÍ da... Zostanie to zmienione
                                                   w nastÍpnych wersjach...
                                                
                                                @todo ZastÍpowanie bitmap na listach.
                                                @param p1 (sUIIconRegister*) Informacja o wstawianej ikonce.
                                                @return (bool)

                                               */
        #define IMI_ICONEXISTS IMI_BASE+131 ///< Sprawdza czy ikonka istnieje.
                                             /// @param p1 (int) ID ikonki
                                             /// @param p2 (IML_enum) lista ktÛrπ sprawdziÊ.
                                             /// @return (bool)
        #define IMI_ICONREGISTERLIST IMI_BASE+132 /**< Dodaje ca≥y zestaw ikon.
                                                @warning Przy zastÍpowaniu bitmap na listach poprzednie kopie NIE sπ usuwane!
                                                   Najlepiej podmieniaÊ ikonki jak najrzadziej siÍ da... Zostanie to zmienione
                                                   w nastÍpnych wersjach...
                                                @param p1 (sUIIconRegisterList*) Informacja co zarejestrowaÊ
                                               */
        #define IMI_GETICONINDEX  IMI_BASE+133 ///< Zwraca index ikonki na wybranej liúcie
                                                ///  \param p1 (int) ID ikonki
                                                ///  \param p2 (IML_enum) lista ktÛrπ sprawdziÊ
                                                ///  @return (int) pozycja
        #define IMI_GETICONLIST   IMI_BASE+134 ///< Zwraca uchwyt typu HIMAGELIST do wybranej listy.
                                                ///  @warning ZwrÛcona lista jest TYLKO do ODCZYTU! Kaøda modyfikacja dokonana poza UI moøe powaønie zak≥ÛciÊ wyúwietlanie ikon!
                                                ///  @param p1 (IML_enum) lista ktÛrπ zwrÛciÊ
                                                ///  @return (HIMAGELIST)
		#define IMI_ICONUNREGISTER IMI_BASE+135 /**< Usuwa ikonkÍ z wybranej listy...
													@warning Przy usuwaniu z list IML_16 i IML_32 ikony NIE sπ usuwane z pamiÍci i pÛüniejsza ich podmiana moøe wymagaÊ nawet restartu Konnekta!
													@param p1 (int) ID ikonki
													@param p2 (IML_enum) lista
													@return (bool)
												*/
		#define IMI_ICONGET	    IMI_BASE+136   /**< Zwraca uchwyt ikonki z wybranej listy.
												    @warning Przy pobieraniu z IML_16 i IML_32 sπ to nowo utworzone uchwyty i naleøy je ZWOLNI∆!
													@param p1 (int) ID ikonki
													@param p2 (IML_enum) lista
													@return (HICON/HBITMAP) uchwyt
												*/
        #define IMI_WARNING     IMI_BASE+200   ///< Wyúwietla okno z ostrzeøeniem.
                                                /// \param p1 (char*) treúÊ.
                                                /// \param p2 (int) dodatkowe flagi, te same co przy MessageBox w WinApi.
                                                /// \return (int) To samo co zwraca MessageBox z WinApi.
        #define IMI_ERROR       IMI_BASE+201  ///< Wyúwietla okno z b≥Ídem.
                                                /// \param p1 (char*) treúÊ.
                                                /// \param p2 (int) dodatkowe flagi, te same co przy MessageBox w WinApi.
                                                /// \return (int) To samo co zwraca MessageBox z WinApi.
        #define IMI_CONFIRM     IMI_BASE+202  ///< Wyúwietla okno z zapytaniem.
                                                /// \param p1 (char*) treúÊ.
                                                /// \param p2 (int) dodatkowe flagi, te same co przy MessageBox w WinApi.
                                                /// \return (int) Jeúli p2==0 to true/false, lub to samo co zwraca MessageBox z WinApi.
        #define IMI_INFORM      IMI_BASE+204  ///< Wyúwietla okno z informacjπ.
                                                /// \param p1 (char*) treúÊ.
                                                /// \param p2 (int) dodatkowe flagi, te same co przy MessageBox w WinApi.
                                                /// \return (int) To samo co zwraca MessageBox z WinApi.

        struct sIMessage_msgBox: public sIMessage_base {
            const char * msg;
            unsigned int flags;
            const char * title;
            HANDLE parent;  
            sIMessage_msgBox(unsigned int id , const char * msg="" , const char * title=0 , int _flags = 0 , HANDLE parent = 0):sIMessage_base(id , 0 , 0) 
                {this->s_size = sizeof(*this);
                 this->parent = parent;
                 this->msg = msg;
                 this->flags = _flags;
                 this->title = title;
                }
        };


        #define IMI_DLGPASS     IMI_BASE+205  ///< Okienko podawania has≥a.
                                                /// \param (sDIALOG_access*) Parametry okna.
                                                /// \param (bool) Gdy == 1 automatycznie do≥πcza do flag DFLAG_SAVE.
                                                /// \return true/false
        #define IMI_DLGLOGIN    IMI_BASE+206  ///< Okienko podawania loginu i has≥a.
                                                /// \param (sDIALOG_access*) Parametry okna.
                                                /// \param (bool) Gdy == 1 automatycznie do≥πcza do flag DFLAG_SAVE.
                                                /// \return true/false
        #define IMI_DLGSETPASS  IMI_BASE+207  ///< Okienko ustawiania has≥a.
                                                /// \param (sDIALOG_access*) Parametry okna.
                                                /// \param (bool) Gdy == 1 automatycznie do≥πcza do flag DFLAG_SAVE.
                                                /// \return true/false
        #define IMI_DLGENTER    IMI_BASE+208   ///< Okno wprowadzania tekstu
                                                ///  \param p1 (sDIALOG_enter*) Parametry okna.
                                                /// \return true/false
        #define IMI_DLGBUTTONS  IMI_BASE+213  ///< Okno wyboru (kaøda opcja to jeden przycisk).
                                                /// \param p1 (sDIALOG_choose *)
                                                /// \return (int) numer przycisku (1-...) lub 0 gdy øaden nie zosta≥ wybrany. 
        #define IMI_DLGTOKEN  IMI_BASE+214  ///< Pobieranie tokenu (wpisywanie wartoúci widocznej na obrazku).
                                                /// \param p1 (sDIALOG_token *)
                                                /// \return true/false 

        #define IMI_LONGSTART   IMI_BASE+209   ///< Tworzy okno oczekiwania na zakoÒczenie d≥uøszej operacji.
                                                ///  \param p1 (sDIALOG_long *) Parametry okna. Struktura musi byÊ zachowana aø do wywo≥ania #IMI_LONGEND!
        #define IMI_LONGEND     IMI_BASE+210   ///< Zamyka okno utworzone przez #IMI_LONGSTART.
                                                /// \param p1 (sDIALOG_long *) ta sama struktura uøyta przy #IMI_LONGSTART.
        #define IMI_LONGSET     IMI_BASE+211   ///< Zmienia okno utworzone przez #IMI_LONGSTART.
                                                /// \param p1 (sDIALOG_long *) ta sama struktura uøyta przy #IMI_LONGSTART.
                                                /// \param p2 (int) wartoúÊ (\ref dset_) oznaczajπca co ma zostaÊ zaktualizowane (wartoúÊ musi najpierw zostaÊ zmieniona w strukturze sDIALOG_long).

        #define IMI_DLGPROFILE  IMI_BASE+212

        /**
        Klasa podstawowa uøywana przez wszystkie wiadomoúci obs≥ugujπce
        okna dialogowe... 
        */
        struct sDIALOG {
            unsigned short s_size;
            const char * title; ///< Tytu≥ okienka.
            const char * info;  ///< Dodatkowa informacja ...
	        int flag;     ///< Flaga D*_
	        void * handle; ///< Uchwyt do okna dialogowego. Przed utworzeniem okna, \a handle trzeba ustawiÊ na rodzica okna!
            void * param; ///< Parametr uzytkownika
            sDIALOG() {s_size=sizeof(sDIALOG);
                        info=title="";
                        handle=0;
                        param = 0;
				        flag=0;}
        };
        /** Struktura uøywana przez okno pobierania tokenu.
            
            \attention Wszystkie zwrÛcone bufory muszπ zostaÊ od razu skopiowane! */
        struct sDIALOG_token:sDIALOG {
            const char * imageURL; ///< URL do obrazka (@ref sUIIconRegister)
            char * token; ///< Token.
	        sDIALOG_token():sDIALOG() {
				s_size=sizeof(sDIALOG_token);
				imageURL="";
				token = "";
			}
        };

		/** Struktura uøywana przez okna obs≥ugi hase≥ i loginÛw.
            
            \attention Wszystkie zwrÛcone bufory muszπ zostaÊ od razu skopiowane! */
        struct sDIALOG_access:sDIALOG {
            char * pass; ///< Has≥o.
            char * login; ///< Login.
            bool save; ///< Stan checkbox'a "czy zapisywaÊ".
	        sDIALOG_access():sDIALOG() {s_size=sizeof(sDIALOG_access);pass=login="";save = false;}
        };
        /** Struktura uøywana przez #IMI_DLGENTER.
            \attention Wszystkie zwrÛcone bufory muszπ zostaÊ od razu skopiowane! */
        struct sDIALOG_enter:sDIALOG {
            char * value;  ///< Wprowadzona wartoúÊ.
            char * id;     ///< Identyfikator pola tekstowego. 
                            ///  Podanie identyfikatora uaktywni historiÍ wpisÛw.
            int maxLength; ///< Maksymalna d≥ugoúÊ wprowadzonego tekstu.
            sDIALOG_enter():sDIALOG() {s_size=sizeof(sDIALOG_enter);value="";id="";maxLength=0;}
        };
        /** Struktura uøywana przez #IMI_DLGBUTTONS.
            \attention Wszystkie zwrÛcone bufory muszπ zostaÊ od razu skopiowane! */
        struct sDIALOG_choose:sDIALOG {
            char * items; ///<Spis elementÛw. Elementy rozdzielane sπ znakiem '\n'
            int  def;     ///<Domyúlnie zaznaczona opcja (liczone od zera)
            int  width;   ///<SzerokoúÊ przyciskÛw.
            sDIALOG_choose():sDIALOG() {s_size=sizeof(sDIALOG_choose);items="";def=1;width=0;}
        };

        struct sDIALOG_profile:sDIALOG {
            char * profile;
            char * pass;
            bool newOne; 
            sDIALOG_profile():sDIALOG() {s_size=sizeof(sDIALOG_profile);pass=profile="";newOne = false;}
        };
        /** Struktura uøywana przez #IMI_LONGSTART , #IMI_LONGSET i #IMI_LONGEND.
            */
        struct sDIALOG_long:sDIALOG {
            int progress; ///< WartoúÊ 'postÍpu'. Przy tworzeniu okna oznacza max. wartoúÊ (liczonπ od zera) - domyúlnie 100.
            bool cancel;  ///< Czy zosta≥o wciúniÍte [Anuluj]?
            int threadId; ///< Id watku, z ktorego tworzone bylo okno
            bool (__stdcall*cancelProc)(sDIALOG_long *); ///< Procedura wywo≥ywana po naciúniÍciu [Anuluj].
            bool (__stdcall*timeoutProc)(int type , sDIALOG_long *); ///< Procedura wywo≥ywana aby sprawdziÊ czy nastπpi≥ timeout.
                                                                    /// \param type Rodzaj wywo≥ania (Patrz \ref timeoutt_)
                                                                    /// \return 0/1 w zaleønoúci od typu wywo≥ania.
                /** @defgroup timeoutt_ Typy dla sDIALOG_long::timeoutProc
                    @{*/
                    #define TIMEOUTT_START 0x10  ///< Dobry moment øeby coú zaalokowaÊ.
                    #define TIMEOUTT_END   0x11  ///< Dobry moment øeby coú zwolniÊ.
                    #define TIMEOUTT_CHECK 1     ///< Sprawdzamy stan. Gdy zwrÛcimy 1, timeoutPassed zostanie zwiÍkszony. A gdy 0, zostanie wyzerowany. 
                                                  ///  Gdy timeoutPassed > timeout, nastπpi przekroczenie limitu czasu i zostanie wywo≥any #TIMEOUTT_TIMEOUT.
                    #define TIMEOUTT_TIMEOUT 2   ///< Nastπpi≥o przekroczenie czasu, moøna napisaÊ coú mπdrego.
                /** @} */
            void * timeoutParam;  ///< Parametr do wykorzystania przez timeoutProc.
            int timeout;          ///< Czas po jakim zostanie wys≥ane TIMEOUTT_TIMEOUT.
            int timeoutPassed;    ///< IloúÊ ms jaka uplynÍ≥a od pierwszego TIMEOUTT_CHECK==0.
            HANDLE timeoutHandle; 
            sDIALOG_long():sDIALOG() {s_size=sizeof(sDIALOG_long);progress=-1; cancel = false; cancelProc = 0;
                            timeoutProc=0;timeout=timeoutPassed=0;timeoutHandle=timeoutParam=0;
                            #ifdef _WINBASE_
                            threadId = GetCurrentThreadId();
                            #else
                            threadId = 0;
                            #endif
                            }
        };
// -----------------------------------------------------------------------------------------------
        /** @defgroup dlong_ Flagi dla sDIALOG_long.
            @{
        */

            #define DLONG_MODAL   0x01  ///< Blokuje okna
            #define DLONG_CANCEL  0x02  ///< Mozliwosc anulowania
            #define DLONG_NODLG   0x04  ///< Nie wyswietla okienka ...
            #define DLONG_SINGLE  0x08  ///< Jedyne wyswietlane okienko
            #define DLONG_ONLY    DLONG_SINGLE
            #define DLONG_BLOCKING  0x10 ///< Akcja wykonywana w glownym watku i moze go blokowac.
                                            ///  Akcja musi doúÊ czÍsto wywo≥ywaÊ SleepEx(1) aby pozwoliÊ
                                            ///  na wywo≥ywanie f-cji uaktualniajπcych g≥Ûwny wπtek.
                                            ///  \warning Jeøeli akcja moøe blokowaÊ na d≥uøej koniecznie uøyj OSOBNEGO
                                            ///  wπtku .
            #define DLONG_ANONE  0x100   ///< Bez animacji
            #define DLONG_ARECV  0x200   ///< Animacja "odbieram"
            #define DLONG_ASEND  0x400   ///< Animacja "wysy≥am"
            #define DLONG_AINET  0x800   ///< Animacja "komunikacja"

        /** @} */
// -----------------------------------------------------------------------------------------------
        /** @defgroup dset_ Flagi dla IMI_LONGSET.
            @{
        */
            #define DSET_TITLE    0x1    ///< Zosta≥ zmieniony tytu≥.
            #define DSET_INFO     0x2    ///< Zosta≥o zmienione info.
            #define DSET_PROGRESS 0x4    ///< Zosta≥ zmieniony postÍp.
            #define DSET_BUTTONS  0x8    ///< Zosta≥y zmienione flagi dotyczπce przyciskÛw.
            #define DSET_ANIM     0x10   ///< Zosta≥a zmieniona animacja.
        /** @} */
// -----------------------------------------------------------------------------------------------
        /** \defgroup dflag_ Flagi dla sDIALOG.
            \{
        */
            #define DFLAG_SAVE  0x1 ///< W sDIALOG_access zostanie pokazany checkbox 'czy zapisaÊ'.
            #define DFLAG_PASS2 0x4 ///< W #IMI_DLGSETPASS zostanie sprawdzona zgodnoúÊ obu hase≥.
            #define DFLAG_CANCEL 0x8 ///< Przycisk [Anuluj] ma byÊ widoczny.
        /** @} */

        #define NOTIFY_AUTO    -2              ///< Do ustawienia w #CNT_NOTIFY. 
                                                ///#IMI_NOTIFY znajdzie \a notify wg. kolejki wiadomoúci.
                                                ///Jeøeli zostanie podane jako \a p1 do #IMI_NOTIFY, zostanπ sprawdzone wszystkie powiadomienia i ustawione powiadomienie w tray'u.
        #define IMI_NOTIFY      IMI_BASE+1010 ///< Kontakt moøe mieÊ nowe powiadomienie. Sprawdzana jest kolejka wiadomoúci.
                                                ///  \param p1 Numer kontaktu.
        #define IMI_NEWNOTIFY   IMI_BASE+1011 /**< Ustawia nowe powiadomienie dla kontaktu lub uøytkownika (np nowa wiadomoúÊ).
                                                    \param p1 (sNOTIFY *) powiadomienie. */
        #define IMI_CNT_ACTIVITY  IMI_BASE+1013 ///< Kontakt wykazuje aktywnoúÊ.
                                                ///  \param p1 (int) id kontaktu
        #define IMI_CNT_DEACTIVATE  IMI_BASE+1014 ///< Wyzerowanie aktywnoúci kontaktu.
                                                ///  \param p1 (int) id kontaktu
        #define IMI_CNT_DETAILS   IMI_BASE+1015 ///< Otwarcie okna informacji o kontakcie.
                                                ///  \param p1 (int) id kontaktu
        #define IMI_CNT_DETAILS_SUMMARIZE   IMI_BASE+1016 ///< Odúwieøa podsumowanie dla kontaktu w oknie informacji (tylko gdy jest otwarte)
                                                ///  @param p1 (int) id kontaktu
        #define IMI_CNT_ISCOMPOSING   IMI_BASE+1020 ///< Czy uøyrkownik pisze coú do podanego kontaktu?
													/// @param p1 (int) id kontaktu
        /**
            Struktura przesy≥ana w #IMI_NEWNOTIFY
        */
        struct sNOTIFY {
            unsigned short s_size;
            int cnt;    ///< ID kontaktu ktÛrego notify dotyczy.
            sUIAction action;  ///< Akcja ktÛra ma byÊ wywo≥ana.
            int notify; ///< Ikona powiadomienia #UIIcon.
            char * info; ///< Informacja.
            int flag; ///< Flaga (w tej chwili flag nie ma :).
            #define NOTIFY_IMPORTANT 1
            /** Wype≥nia strukturÍ dla kontaktu na liúcie.
                \param _action Identyfikator akcji.
                \param _notify Identyfikator ikonki powiadomienia.
                \param _cnt Pozycja kontaktu.
            */
            sNOTIFY(sUIAction _action , int _notify , int _cnt = -1) {s_size=sizeof(sNOTIFY);cnt = _cnt; action = _action; notify = _notify;info = (char*)-1;}
            /** Wype≥nia strukturÍ dla uøytkownika.
                \param _action Identyfikator akcji.
                \param _notify Identyfikator ikonki powiadomienia.
                \param _info Tekst powiadomienia (pokazywany w Tray'u). Moøe przyjπÊ wartoúci:
                    - adres do ciπgu znakÛw z tekstem.
                    - 0 - tekst nie zostanie zmieniony.
                    - -1 - tekst zostanie zmieniony na domyúlny.
            */
            sNOTIFY(sUIAction _action , int _notify , char * _info = 0) {s_size=sizeof(sNOTIFY);cnt = -1; action = _action; notify = _notify;info = _info;}
        };

        #define IMI_REFRESH_CNT IMI_BASE+2000 ///< UI powinien odúwieøyÊ kontakt.
                                                /// Wysy≥ane po zmianie statusu kontaktu, lub ktÛrejú z informacji tekstowych.
                                                /// \param p1 (int) ID kontaktu
                                                /// \param p2 (bool) jeúli true - dane zostanπ odúwieøone rÛwnieø w oknie z informacjami o kontakcie!
        #define IMI_REFRESH_LST IMI_BASE+2001 /**< Ca≥a lista kontaktÛw powinna byÊ odúwieøona.
                                                 \param p1 (bool) Czy lista ma zostaÊ od nowa wype≥niona (raczej nie uøywane)?
                                                 \attention Ten komunikat powinien byÊ uøywany TYLKO po dokonaniu duøych zmian na liúcie kontaktÛw 
                                                  (bez wywo≥ywania #IMI_REFRESH_CNT).
												  */
        #define IMI_CONFIG      IMI_BASE+2010 /**< Otwiera konfiguracjÍ.
                                                 \param p1 (int) ID grupy na ktÛrej ma zostaÊ otwarte.
												 */
        #define IMI_CONFIGOPENED IMI_BASE+2011 ///< Zwraca true jeúli konfiguracja jest otwarta.

        #define IMI_LST_SELCOUNT IMI_BASE+2020 ///< Zwraca ile kontaktÛw jest zaznaczonych na liúcie.
        #define IMI_LST_GETSELPOS  IMI_BASE+2021   ///< Zwraca ID zaznaczonego kontaktu.
                                                    ///  \param p1 (int) numer zaznaczenia poczynajπc od 0 do #IMI_LST_SELCOUNT.
        /*
        #define IMI_MSG_INFO    IMI_BASE+3000  //
           #define IMI_MSG_INFO_undelivered 0
           #define IMI_MSG_INFO_delivered 1
        */
        #define IMI_MSG_OPEN    IMI_BASE+3001  // (cMessage*)    internal usage
        #define IMI_MSG_NOTINLIST IMI_BASE+3002 // (cMessage *)  internal usage
        #define IMI_MSG_WINDOWSTATE IMI_BASE+3003 ///< Zwraca stan okna wiadomoúci dla kontaktu.
                                                    ///  \p1 Numer kontaktu.
                                                    ///  \return 0 - okno zamkniÍte.
                                                    ///  \return 1 - okno otwarte , aktywne.
                                                    ///  \return -1 - okno otwarte , nieaktywne.
                                                    ///  \return -2 - okno zminimalizowane.
/** Zwraca adres do procedury okna wpisywania wiadomoúci.
Procedura daje obs≥ugÍ skrÛtÛw wysy≥ania (Ctrl+enter, Alt+s), wykrywanie
pisania i historiÍ ostatnio wpisanych wiadomoúci...
Obs≥uguje komunikaty WM_KEYDOWN i WM_SYSKEYDOWN
*/
		#define IMI_MSG_EDITCTRL_WNDPROC IMI_BASE+3005  
                                                /// \param p1 (sHISTORYADD*)
        #define IMI_HISTORY_ADD IMI_BASE+3004  ///< Dodaje wpis do historii
                                                /// \param p1 (sHISTORYADD*)
		/** Struktura uøywana przez #IMI_HISTORY_ADD. */
        struct sHISTORYADD {
            unsigned short s_size;
            struct cMessage * m; ///< WiadomoúÊ do dodania
            const char * dir; ///< podkatalog w "history/"
            unsigned int cnt; ///< Identyfikator kontaktu jeúli ma byÊ automatycznie utworzona nazwa
            const char * name; ///< Nazwa pliku (jeúli cnt==0)
            int session; ///< Oznaczenie sesji.
                        ///  0 - osobna wiadomoúÊ, lub poczπtek sesji
                        ///  1 - wiadomoúÊ naleøy do sesji
            sHISTORYADD():s_size(sizeof(sHISTORYADD)) {m=0;dir="";cnt=0;name=0;session=0;}
        };
        #define IMI_CNT_SEARCH_FOUND IMI_BASE+4000  ///< Dodaje kontakt do listy znalezionych w odpowiedzi na wyszukiwanie.
                                                    /// \param p1 (sCNTSEARCH*) Informacje o kontakcie.

  /** @} */  // do UI.dll
  /** @} */  // IMESSAGE
// -----------------------------------------------------------------------------------------------
  /**
    \defgroup imerror_ Kody b≥edu
    \brief \no

    \{
  */

  #define IMERROR_NORESULT 1   ///< Wtyczka nie obs≥uøy≥a wiadomoúci.
  #define IMERROR_UNSUPPORTEDMSG IMERROR_NORESULT /// \no
  #define IMERROR_BADSENDER 2  ///< WiadomoúÊ wstrzymana, pojawi≥ siÍ b≥πd...
  #define IMERROR_BADPLUG 3    ///< Podana wtyczka nie istnieje.
  #define IMERROR_THREADSAFE 4 ///< WiadomoúÊ zosta≥a wywo≥ana w trybie bezpiecznym (bez oczekiwania na powrÛt).
  #define IMERROR_SHUTDOWN 5   ///< WiadomoúÊ zosta≥a anulowana z powodu zamykania programu.
  #define IMERROR_BADPARAM 6   ///< Nieprawid≥owe parametry.
  #define IMERROR_BADSTRUCT 7   ///< Niepoprawna struktura.

  /** @} */ // imerror_

/** @} */  // Komunikacja pomiedzy wtyczkami

// ------------------------------------------------------------------------------------------------
  /**
    \defgroup imig_ idnetyfikatory Grup i Akcji
    \brief \no
    \{
  */
        // Identyfikatory podstawowych akcji w UI tworzacych grupy
        #define IMIG_MAINWND       1   ///< G≥Ûwne okno
        #define IMIG_BAR           2   ///< Belka glowna
        #define IMIG_MSGWND        3   ///< Okno wysy≥ania wiadomoúci
        #define IMIG_MSGBAR        4   ///< Belka w wysy≥aniu wiadomoúci
        #define IMIG_MAINTB        8   ///< G≥Ûwny toolbar
        #define IMIG_SHORTCUTTB    9   ///< Toolbar ze skrÛtami
        #define IMIG_MAIN          10  ///< G≥Ûwne Menu
        #define IMIG_MAIN_OPTIONS  11  ///< Menu opcji
        #define IMIG_MAIN_CNT   12     ///< Dodaj kontakt
        #define IMIG_MAIN_PROFILE  13  ///< Profile
        #define IMIG_HISTORYWND    14
		#define IMIG_PLUGINS       15  /**< Grupa dla ikonek wtyczek w g≥Ûwnym oknie... Uøytkownik moøe wybraÊ
										innπ, wiÍc numer aktualnej grupy naleøy pobraÊ przez #IMI_GETPLUGINSGROUP.
									
										*/
        #define IMIG_STATUS          50  ///< Toolbar ze statusami
        #define IMIG_EVENT           51  ///< Menu z wiadomoúciami od serwerÛw.
        #define IMIG_EVENT_PARENT    IMIG_STATUS
        #define IMIG_HIDDEN          60  

        #define IMIG_TRAY          20  ///< Tray
        #define IMIG_CNT           30  ///< Menu kontaktu
        #define IMIG_CFGWND        40  ///< Okno ustawieÒ.
        #define IMIG_CFG           41  ///< KorzeÒ drzewka ustawieÒ.
        #define IMIG_CFG_CONNECTION 42 ///< Opcje po≥πczeÒ.
        #define IMIG_CFG_USER      43  ///< Ustawienia uøytkownika.
        #define IMIG_CFG_SETTINGS  44  ///< Ustawienia programu.
        #define IMIG_CFG_UI        45  ///< Ustawienia interfejsu.
        #define IMIG_CFG_PLUGS     46  ///< Ustawienia wtyczek.

        #define IMIG_NFOWND        70  ///< Okno informacji o kontakcie
        #define IMIG_NFO           71   ///< Drzewko kontrolek informacji
        #define IMIG_NFO_BAR       72   ///< Belka w oknie informacji o kontakcie
        #define IMIG_NFO_TB        73   ///< G≥Ûwny toolbar w oknie informacji o kontakcie
  /** @} */ // imig_

// ------------------------------------------------------------------------------------------------
  /**
    \defgroup st_ Numery statusÛw
        Status sk≥ada siÍ z rodzaju statusu (0-0xFF) i flag (0x001-0xFFFFFF00).

    \{
  */

        // STATUS
        /** 
        */
        typedef unsigned int tStatus;
        #define ST_OFFLINE  0  ///< NiedostÍpny.
        #define ST_BLOCKING 1 ///< Blokujπcy (GG)

#define ST_SEMIONLINE 0x20 ///< Od tej granicy zaczynajπ siÍ "mniejsze" online'y
        #define ST_NA     0x21       ///< Bardzo away (not-available).
        #define ST_DND    0x22      ///< Nie przeszkadzaÊ.
        #define ST_OCCUPIED 0x22     ///< ZajÍty (ICQ)

        #define ST_ONLINE 0x40   ///< DostÍpny.
        #define ST_AWAY   0x41     ///< Away.
        #define ST_AUTOAWAY   0x44     ///< Automatyczny away.
        #define ST_HIDDEN 0x42   ///< Ukryty.
        #define ST_CHAT 0x43  ///< FreeForChat (ICQ)

#define ST_SPECIAL 0x60 ///< Od tej granicy zaczynajπ siÍ statusy specjalne...

        #define ST_CONNECTING 0xF1  ///< W trakcie ≥πczenia, tylko dla kontaktu uøytkownika.

        // flagi
        #define ST_NOTINLIST 0x100 ///< Chwilowo na liúcie, zostanie usuniÍty po zamkniÍciu programu.
        #define ST_HIDESHISSTATUS 0x200 ///< Kontakt nie podaje nam swojego statusu
        #define ST_IGNORED 0x400        ///< Ignorowany
        #define ST_COMPOSING 0x800  ///< Kontakt pisze do nas wiadomoúÊ
        #define ST_HIDEMYSTATUS 0x1000  ///< Ukrywanie statusu przed kontaktem
		#define ST_HIDEBOTH (ST_HIDEMYSTATUS | ST_HIDESHISSTATUS)

        // maski
        #define ST_MASK        0xFF  ///< Maska statusu.

  /** @} */ // st_
// ------------------------------------------------------------------------------------------------
  /** @defgroup gr_msg Obs≥uga wiadomoúci tekstowych.
      @brief @no
      @{
      */

        #define EXT_PARAM "\x1A" /**< Znak parametru.
                    W cMessage i cMessageAck moøemy podawaÊ listÍ dodatkowych parametrÛw.
                    Kaødy parametr sk≥ada siÍ z po≥πczonych: #EXT_PARAM nazwy '=' wartoúci
                    DziÍki zastosowaniu "nietypowego znaku, unikamy potrzeby escape'owania znakÛw.
                    Nazwa moøe byÊ dowolnym ciπgiem znakÛw z wyjπtkiem znakÛw #EXT_PARAM, '=' i \0.
                    WartoúÊ moøe byÊ dowolnym ciπgiem znakÛw z wyjπtkiem znakÛw #EXT_PARAM i \0.
                    Nazwa jest case-sensitive.

                    Najlepiej uøywaÊ gotowych f-cji zadeklarowanych w plug_func.h:
                    GetExtParam i SetExtParam .
                    */
        #define EXT_PARAM_CHAR char(0x1A)
        /**
        Struktura do przekazywania wiadomoúci tekstowych .
        \attention ZawartoúÊ struktury jest tylko tymczasowπ \i kopiπ wiadomoúci z \i kolejki.
        \sa \ref msg
        */
        struct cMessage{
            unsigned short s_size;
            unsigned int id;              /**< Identyfikator wiadomoúci.
                                    \attention ustawiany przez "rdzeÒ". */
            unsigned int net;             /**< SieÊ wtyczek do ktÛrych skierowana jest wiadomoúÊ.
                                    \sa net_ */
            unsigned int type;            /**< Typ wiadomoúci.
                                    \sa mt_ */
            char * fromUid;      ///< UID odbiorcy.
            char * toUid;        ///< UID nadawcy.
            char * body;         ///< TreúÊ wiadomoúci.
            char * ext;          ///< Informacje rozszerzone.
                                  /**  Zapisane jako 
                                        \code 
                                        #EXT_PARAM nazwa=wartoúÊ #EXT_PARAM nazwa2=wartoúÊ2
                                        ...
                                        \endcode
                                        patrz: #EXT_PARAM .
                                  */
            unsigned int flag;            ///< Flaga.
                                    ///< \sa mf_
            struct sUIAction action;    ///< Akcja powiadomienia dla wiadomoúci.
            unsigned int notify;          ///< Akcja i ikonka powiadomienia dla wiadomoúci.
                                ///< \sa \ref action \ref msg
            __int64 time;        ///< czas odebrania wiadomoúci w formacie zgodnym z cTime64 (zapisane jako __int64).

            cMessage() {s_size=sizeof(cMessage);id=net=type=flag=notify=0; action = sUIAction(0,0); fromUid=toUid=body=ext="";time=0;}
        };
        /**
        Struktura do przekazywania informacji o stanie przesy≥anych wiadomoúci.
        Moøna niπ podawaÊ jakie wystπpi≥y problemy, lub co sta≥o siÍ z wiadomoúciπ
        po wys≥aniu (np. czeka na serwerze, lub dosz≥a do odbiorcy...)
        \attention \a id \b musi byÊ ustawiony na numer potwierdzanej i \b istniejπcej wiadomoúci.
        W miÍdzyczasie wiadomoúÊ ta nie moøe byÊ usuniÍta przez inny wπtek.

        \sa \ref msg
        */
        struct cMessageAck {
            unsigned short s_size;
            unsigned int id;   /**< Identyfikator wiadomoúci ktÛrπ potwierdzamy.
                                    */
            char * msg; /**< Tekst potwierdzenia. */
            char * ext; /**< Dodatkowe parametry. */
            unsigned int flag; ///< Flagi \ref mack_.
            cMessageAck() {s_size=sizeof(cMessageAck);}

        };

    /**  
        \defgroup mt_ Typy wiadomoúci tekstowych
		Do typu wiadomoúci moøna dodaÊ bit #MT_MASK_NOTONLIST oznaczajπc tym samym, 
		øe wiadomoúÊ nie jest zwiπzana z listπ kontaktÛw.
		CzÍúÊ typÛw ma ten bit ustawiony domyúlnie...
        \{
    */
            typedef unsigned int tMsgType;
            #define MT_MESSAGE      1    ///< Zwyk≥a wiadomoúÊ.
            #define MT_QUICKEVENT   2    ///< KrÛtka notka (kasowana automatycznie w kolejce) (np. wiadomoúÊ nie dosz≥a itp.)
            #define MT_CNTEVENT     3    ///< wydarzenie (np. ktoú mnie doda≥ do swojej listy itp.) zwiπzane z kontaktem na liúcie
            #define MT_EVENT        (MT_CNTEVENT|MT_MASK_NOTONLIST)    ///< wydarzenie (np. ktoú mnie doda≥ do swojej listy itp.)
            #define MT_SERVEREVENT  (4|MT_MASK_NOTONLIST)    ///< WiadomoúÊ od serwera.
            #define MT_AUTHORIZE    5    ///< Proúba o autoryzacje (ICQ).
            #define MT_CONFERENCE   6    ///< WiadomoúÊ konferencyjna.
            #define MT_FILE         7 ///< Przes≥anie pliku.
            #define MT_MAIL         8 ///< Email.
            #define MT_SMS          9 ///< Np. potwierdzenie dotarcia sms'Ûw.
            #define MT_SOUND        10 ///< Rozmowa g≥osowa.
            #define MT_URL         (11|MT_MASK_NOTONLIST)    ///< URL. 
                                                                /// Jako dodatkowe parametry w ext przyjmuje Width i Heigth
            #define MT_SPECIAL      12 ///< Nieokreslona wiadomosc.
            #define MT_SPECIAL_NOL (13|MT_MASK_NOTONLIST) ///< Nieokreslona wiadomosc spoza listy.
			#define MT_IMAGE		15 ///< Obraz, sciezka do pliku w cMessage::ext - #MEX_FILE_PATH

			#define MT_BOARD        16 ///< 

            #define MT_MASK_NOTONLIST 0x1000  ///< Oznacza øe ta wiadomosc nie zostanie
                                            ///  wyúwietlona na liscie, ani nie zostanie
                                            ///  sprawdzone czy docelowy kontakt na liúcie
                                            ///  siÍ znajduje
			#define MT_MASK 0xFFF ///< Maskuje bity odpowiedzialne za sam typ wiadomoúci.
    /** @} */ // mt_
    // ------------------------------------------------------------------------------------------------
    /**
        \defgroup mf_ flagi wiadomoúci tekstowych
        \brief \no
        @{
    */
            #define MF_SEND         2 ///< WiadomoúÊ przeznaczona do wys≥ania
            #define MF_NOEVENTS     4 ///< #MT_QUICKEVENT majπ nie byÊ wysy≥ane
            #define MF_NOSAVE       8 ///< WiadomoúÊ nie zostanie zapisana na dysk ...
            #define MF_REQUESTOPEN  0x10 ///< \brief #IM_MSG_OPEN / #IM_MSG_SEND zostanie wys≥ane z #IMC_MESSSAGEQUEUE tylko
                                        ///  gdy zostanie ono wywo≥ane dla tego typu i sieci wiadomoúci.
            #define MF_PROCESSING   0x20 ///< Flaga wewnÍtrzna oznaczajπca øe wiadomoúÊ jest w trakcie przetwarzania, Nie powinna byÊ uøywana!
            #define MF_OPENED       0x40   ///< WiadomoúÊ juø zosta≥a otwarta. Teraz czeka w kolejce na usuniÍcie.
                                            ///  Flaga ta jest czyszczona podczas zamykania. 
            #define MF_HANDLEDBYUI  0x80 ///< WiadomoúÊ zostanie obs≥uøona przez UI
            #define MF_AUTOMATED    0x100   ///< WiadomoúÊ zosta≥a stworzona przez jakiú "automatyczny"
                                            /// proces, wiÍc, gdy jesteúmy ukryci, nie powinna byÊ
                                            /// wysy≥ana.
            #define MF_HTML    0x200     ///< TreúÊ wiadomoúci zawiera znaczniki HTML, a znaki specjalne sπ kodowane (przynajmniej > = &gt; < = &lt; i " = &quot;
										 ///  Html powinien byÊ sformatowany jak XHTML (<img/>, wszystkie atrybuty w "" itd..)
			#define MF_MENUBYUI     0x400 /**< Interfejs obs≥uøy wyúwietlanie wiadomoúci w menu.
											Za ikonkÍ pos≥uøy cMessage::notify, nazwÍ pozycji w menu ustawiamy
											w Ext jako parametr "ActionTitle". Jeøeli ustawiona jest cMessage::action
											zostanie ona wys≥ana po otwarciu wiadomoúci. W przeciwnym razie zostanie
											wywo≥ane IM_MSG_OPEN.
											Wtyczka musi w #IM_MSG_RCV zadeklarowaÊ obs≥ugÍ wiadomoúci.
										  */
			#define MF_LEAVEASIS 0x800 /**< Zabrania wtyczkom zmiany treúci, w tym wyúwietlania emotikon */
			#define MF_HIDE 0x1000 /**< Nie wyúwietla wiadomoúci w interfejsie (w tej chwili w oknie rozmowy) */
			#define MF_DONTADDTOHISTORY 0x2000 /**< Nie zapisuje w historii */

            #define MF_QE_NORMAL    0x10000 ///< MT_QUICKEVENT narysuje zwyk≥π czcionkπ...
            #define MF_QE_SHOWTIME  0x20000 ///< MT_QUICKEVENT pokaøe czas nadejúcia...

            
    /** @} */ // mf_
    /**
        \defgroup mex_ Nazwy wartoúci w polach cMessage::ext
        \brief \no
        @{
    */
            #define MEX_ADDINFO "AddInfo"
            #define MEX_DISPLAY "Display"
			#define MEX_TITLE   "Title"
			#define MEX_NOSOUND "NoSound" ///< Nie zostanie odegrany düwiÍk
			#define MEX_FILE_PATH "FilePath"
			#define MEX_FILE_SIZE "FileSize"
			#define MEX_FILE_TRANSFER_TIME "FileTransferTime"
			#define MEX_FILE_TRANSFERED "FileTransfered"
            #define MEX_FILE_ERROR "FileError"

            
    /** @} */ // mf_
    /**
        \defgroup mack_ Flagi potwierdzeÒ wiadomoúci (#IMC_MESSAGEACK i #IM_MSG_ACK)
        \brief \no
        \{
    */
            #define MACK_FAILED  0x1 ///< Wystπpi≥ b≥πd
            #define MACK_PROCESSING 0x2 ///< W trakcie przetwarzania

            #define MACK_NOBROADCAST 0x100 /**< Ack nie zostanie rozes≥ane do wtyczek #IMT_MESSAGEACK.
                                                 Przydatne, jeúli chcemy tylko zmieniÊ informacjÍ pokazywanπ w oknie
                                                 kolejki.
                                                 */

            #define MACK_IMPORTANT 0x10 ///< Komunikat jest istotny, bÍdzie pokazywany d≥uøej
            #define MACK_VERYIMPORTANT 0x20 ///< Komunikat jest bardzo istotny.
    /** @} */ // mack_

/** @} */
/** @addtogroup imc_ 
    @{*/
    /** Struktura wykorzystywana przez #IMC_MESSAGENOTIFY.
        Podajemy w niej net i uid kontaktu i otrzymujemy action i notify s≥uøπce
        do otwarcia tego typu wiadomoúci. Struktura jest przede wszystkim 
        wykorzystywana przez UI do pokazywania odpowiednich ikonek przychodzπcych wiadomoúci.*/ 
    struct sMESSAGENOTIFY {
        unsigned short s_size;
        int net;       ///< SieÊ kontaktu.
        char * uid;   ///< UID kontaktu.
        sUIAction action;  ///< Akcja otwierajπca wiadomoúÊ.
        int notify;       ///< Ikonka wiadomoúci.
        unsigned int id; ///< Identyfikator wiadomoúci.
        sMESSAGENOTIFY() {s_size=sizeof(sMESSAGENOTIFY);id = 0;}
    };

/**@}*/

//-------------------------------------------------------------------------------------------------
  /**
    \defgroup gr_cfg Kolumny konfiguracji
    Zanim zaczniemy korzystaÊ z tablic konfiguracji trzeba zarejestrowaÊ typy kolumn
    wysy≥ajπc sIMessage_setColumn w odpowiedzi na #IM_SETCOLS.

    Odczyt i zapis odbywa siÍ poprzez makra zdefiniowane w \ref gr_cfg.
    Dodatkowo rdzeÒ, UI i wtyczki majπ zadeklarowane swoje kolumny.

    Kolumny typu #DT_CT_PCHAR zazwyczaj majπ teø flagÍ #DT_CF_CXOR.

    \{
  */
//-------------------------------------------------------------------------------------------------


        /**
            \defgroup msg_ tabela wiadomoúci tekstowych
            W tej chwili nie ma bezpoúredniego dostÍpu do tablicy wiadomoúci!

            \{
        */
            // Msg
            #define MSG_ID             ((unsigned int)0) ///< #DT_CT_INT ID.
            #define MSG_NET            1 ///< #DT_CT_INT SieÊ.
            #define MSG_TYPE           2 ///< #DT_CT_INT Typ.
            #define MSG_FROMUID        3 ///< #DT_CT_PCHAR Od UIDa (odebrana).
            #define MSG_TOUID          4 ///< #DT_CT_PCHAR Do UIDa (wysy≥ana).
            #define MSG_BODY           5 ///< #DT_CT_PCHAR TreúÊ.
            #define MSG_EXT            6 ///< #DT_CT_PCHAR Dodatkowe informacje.
            #define MSG_FLAG           7 ///< #DT_CT_INT Flaga.
            #define MSG_ACTIONP        8 ///< #DT_CT_INT | #DT_CF_NOSAVE  Grupa akcji.
            #define MSG_ACTIONI        12 ///< #DT_CT_INT | #DT_CF_NOSAVE Akcja.
            #define MSG_NOTIFY         9 ///< #DT_CT_INT | #DT_CF_NOSAVE  Ikonka powiadomienia.
            #define MSG_HANDLER        10 ///< #DT_CT_INT | #DT_CF_NOSAVE Wtyczka obs≥ugujπca.
            #define MSG_TIME           11 ///< #DT_CT_64 Czas jako cTime64 Czas odebrania/wys≥ania.

//            #define C_MSG_COLCOUNT     13 // ostatni

        /**
            @}
            @defgroup cfg_ tabela Konfiguracji
            \brief \no
            NiektÛre kolumny sπ w tej chwili nie uøywane (by≥y w poprzednich wersjach)...
            Nied≥ugo najprawdopodobniej zostanπ wykorzystane.
            @{
        */
            // Cfg - CORE'a
            #define CFG_0              ((int)0) ///< nieuøywany.
            #define CFG_VERSIONS       1 ///< Wersje ostatnio uøywanych pluginÛw.
            #define CFG_APPFILE        2 ///< #DT_CT_PCHAR | #DT_CF_NOSAVE åcieøka do pliku konnekt.exe.
            #define CFG_APPDIR         3 ///< #DT_CT_PCHAR | #DT_CF_NOSAVE åcieøka do katalogu z programem.
            #define CFG_PROXY          4 ///< #DT_CT_INT Czy proxy ma byÊ uøywane?
            #define CFG_PROXY_AUTO     15 ///< #DT_CT_INT Pobieranie ustawieÒ z IE
            #define CFG_PROXY_VERSION  5 ///< #DT_CT_PCHAR Rodzaj proxy (w tej chwili tylko "")
            #define CFG_PROXY_AUTH     6 ///< #DT_CT_INT Czy uøywaÊ logowania?
            #define CFG_PROXY_LOGIN    7 ///< #DT_CT_PCHAR Login do proxy.
            #define CFG_PROXY_PASS     8 ///< #DT_CT_PCHAR Has≥o do proxy.
            #define CFG_PROXY_HOST     9 ///< #DT_CT_PCHAR Adres proxy.
            #define CFG_PROXY_PORT     10 ///< #DT_CT_INT  Port proxy.
            #define CFG_PROXY_HTTP_ONLY 21 ///< #DT_CT_INT Proxy tylko dla http.
            #define CFG_AUTO_CONNECT   11 ///< #DT_CT_INT  £πczenie automatyczne.
            #define CFG_12             12 ///< nieuøywany
            #define CFG_13             13 ///< nieuøywany
            #define CFG_14             14 ///< nieuøywany
            #define CFG_IGNORE         16 ///< #DT_CT_PCHAR Lista ignorowanych.
            #define CFG_GROUPS         17 ///< #DT_CT_PCHAR Lista grup kontaktÛw.
            #define CFG_CURGROUP       18 ///< #DT_CT_PCHAR Aktualna grupa kontaktÛw.
            #define CFG_DIALUP         19 ///< #DT_CT_INT Po≥πczenie przez modem
            #define CFG_RETRY          20 ///< #DT_CT_INT Wznawianie po≥πczeÒ
            #define CFG_LOGHISTORY     22 ///< #DT_CT_INT Zapisywanie historii
			#define CFG_TIMEOUT_RETRY  23
			#define CFG_TIMEOUT		   24
			#define CFG_SHOWBITS       25 /**< #DT_CT_INT Okreúla jak ma byÊ budowany interfejs. 
						Na przyk≥ad ktÛre elementy powinny byÊ ukryte, a ktÛre w≥πczone.
						Do obs≥ugi uøywamy tylko i wy≥πcznie funkcji w Konnekt::ShowBits !
						*/
			#define CFG_SHOWBITS_BYHAND 26 /**< #DT_CT_INT Okreúla ktÛre bity w CFG_SHOWBITS by≥y ustawiane rÍcznie.

            //#define C_CFG_COLCOUNT     26// ostatni
        /**
            @}

            @defgroup cnt_ tabela KontaktÛw
            \brief \no

            @{
        */
        // Cnt
            #define CNT_UID            ((unsigned int)0) ///< #DT_CT_PCHAR UID.
            #define CNT_NET            1 ///< #DT_CT_INT SieÊ.
            #define CNT_STATUS         2 ///< #DT_CT_INT Status.
            #define CNT_STATUSINFO     18 ///< #DT_CT_PCHAR Opis statusu.
            #define CNT_NOTIFY         3 ///< #DT_CT_INT | #DT_CF_NOSAVE Ikonka powiadomienia.
            #define CNT_HOST           4 ///< #DT_CT_PCHAR | #DT_CF_NOSAVE IP.
            #define CNT_PORT           5 ///< #DT_CT_INT | #DT_CF_NOSAVE Port.
            #define CNT_NAME           6 ///< #DT_CT_PCHAR ImiÍ.
            #define CNT_SURNAME        7 ///< #DT_CT_PCHAR Nazwisko.
            #define CNT_NICK           17 ///< #DT_CT_PCHAR Pseudo.
            #define CNT_DISPLAY        8 ///< #DT_CT_PCHAR Nazwa wyúwietlana.
            #define CNT_CELLPHONE      9 ///< #DT_CT_PCHAR KomÛrka.
            #define CNT_PHONE          10 ///< #DT_CT_PCHAR Stacjonarny.
            #define CNT_EMAIL          11 ///< #DT_CT_PCHAR Email.
            #define CNT_INFO           12 ///< #DT_CT_PCHAR Info.
            #define CNT_LOCALITY       13 ///< #DT_CT_PCHAR MiejscowoúÊ.
            #define CNT_CITY	       CNT_LOCALITY
            #define CNT_COUNTRY        14 ///< #DT_CT_PCHAR Kraj
            #define CNT_BORN           19 ///< #DT_CT_INT Urodzony YYYYMMDD (w hexie)
            #define CNT_GENDER         20 ///< #DT_CT_INT P≥eÊ \ref gender_
            #define CNT_CLIENT         15 ///< #DT_CT_PCHAR Nazwa i wersja uøywanego softu.
            #define CNT_CLIENTVERSION  28 ///< #DT_CT_INT Wersja Softu
            #define CNT_LASTMSG        16 ///< #DT_CT_INT | #DT_CF_NOSAVE ID ostatniej wiadomoúci.
            #define CNT_GROUP          21 ///< #DT_CT_PCHAR Grupa do ktÛrej naleøy.
            #define CNT_ACT_PARENT     22 ///< #DT_CT_INT | #DT_CF_NOSAVE Parent akcji powiadomienia.
            #define CNT_ACT_ID         23 ///< #DT_CT_INT | #DT_CF_NOSAVE ID akcji powiadomienia.
            #define CNT_INTERNAL       24 // Dla rdzenia.
            #define CNT_STREET         25 ///< #DT_CT_PCHAR - ulica.
            #define CNT_POSTALCODE     26 ///< #DT_CT_PCHAR - kod pocztowy.
            #define CNT_NOTIFY_MSG     27 ///< #DT_CT_INT | #DT_CF_NOSAVE ID wiadomoúci powiadomienia.
            #define CNT_LASTACTIVITY   29 ///< #DT_CT_64 Czas ostatniej aktywnoúci.
            #define CNT_STATUS_ICON    30 ///< #DT_CT_INT Identyfikator ikonki, ktÛra ma zastπpiÊ ikonÍ statusu.



			#define CNT_MIDDLENAME		31
			#define CNT_EMAIL_MORE		32
			#define CNT_PHONE_MORE		33
			#define CNT_DESCRIPTION		34
			#define CNT_FAX				35
			#define CNT_URL				36
			#define CNT_ADDRESS_MORE	37
			#define CNT_REGION			38
			#define CNT_POBOX			39

			#define CNT_WORK_ORGANIZATION	50
			#define CNT_WORK_ORG_UNIT		51
			#define CNT_WORK_TITLE			52
			#define CNT_WORK_ROLE			53
			#define CNT_WORK_EMAIL			54
			#define CNT_WORK_URL			55
			#define CNT_WORK_PHONE			56
			#define CNT_WORK_FAX			57
			#define CNT_WORK_STREET			58
			#define CNT_WORK_ADDRESS_MORE	59
			#define CNT_WORK_POBOX			60
			#define CNT_WORK_POSTALCODE		61
			#define CNT_WORK_LOCALITY		62
			#define CNT_WORK_REGION			63
			#define CNT_WORK_COUNTRY		64
			#define CNT_WORK_MORE			65

//          40 / 66    // ostatni

            #define CNTM_STATUS    ST_MASK
            #define CNTM_FLAG      0xFFFFFF00
        /** @} */ // cnt_
    /** @} */ // gr_cfg
    /** @defgroup gender_ Oznaczenie p≥ci
        @{ */
        #define GENDER_UNKNOWN 0 ///< Nieznana
        #define GENDER_FEMALE  1 ///< Kobieta
        #define GENDER_MALE    2 ///< MÍøczyzna
    /** @} */

// gr_shared
/** @} */



#include "core_ctrl.h"

 #pragma pack(pop)

#endif
