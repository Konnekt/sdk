/*
  nazwa="Plug Shared"
  ver="0.6.18.x"
  info="Podstawowy nag��wek."
*/

/**
\file
Deklaracje wymagane do komunikacji pomi�dzy wtyczkami.
*/

// -----------------------------------------------------------------------------------------------
/**
\defgroup gr_shared Komunikacja pomi�dzy wtyczkami.

Nag��wek powinien by� do��czony do kodu wtyczki poprzez plug_export.h .
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

#include "core_net.h"
#include "core_plugin.h"
#include "core_imessage.h"


  typedef IMPARAM (__stdcall*fIMessageProc)(sIMessage_base * msg);

#ifndef _WINDOWS_
    #define HANDLE void *
    #define HINSTANCE void *
    #define HWND void *
#endif

  /** Identyfikatory tablic. */




#include "core_exception.h"





// -----------------------------------------------------------------------------------------------
  /** \defgroup gr_im Identyfikatory IMessage
    \brief \no

    Identyfikator jest \i nazw� przesy�anej #IMessage (wiadomo�ci
    wewn�trznej).
    \par
    Wiadomo�ci dziel� si� na (pod wzgl�dem przeznaczenia):
    - IMC_* \ref imc_ od 0 do 10000 #IMI_BASE
    - IMI_* \ref imi_ od 10000 #IMI_BASE do 20000 #IM_BASE
    - IM_*  \ref im_  od 20000 #IM_BASE do 0xFFFFFFFF
    \attention Wiadomo�ci \ref imc_ dotr� \b tylko do \ref core "rdzenia". (niezale�nie od wybranego \a net i \a type w IMessage())
    \attention Wiadomo�ci \ref imi_ dotr� \b tylko do \ref ui "UI". (niezale�nie od wybranego \a net i \a type w IMessage())
    \attention Wiadomo�ci \ref im_ < #IM_SHARE mog� by� wysy�ane \b tylko przez \ref core "rdze�" i \ref ui "ui".
    \attention Wiadomo�ci \ref im_ deklarowane przez u�ytkownika powinny by� tworzone jako #IM_USER + numer (numer najlepiej jako NET * 1000).
    \attention Parametry podawane s� w kolejno�ci - P1 , P2.

    Wiadomo�ci utworzone na potrzeby powstaj�cych wtyczek powinny
    by� umieszczane w nazwa_wtyczki_shared.h tak, aby inni mogli
    wykorzystywa� API wtyczki.

    \sa IMessageProc()
  \{
  */


     #define IMI_BASE 10000 ///< Od tej granicy zaczynaj� si� wiadomo�ci do \ref ui "UI".
     #define IM_BASE  20000 ///< Od tej granicy zaczynaj� si� wiadomo�ci do \ref plug "wtyczek" wysy�ane tylko przez \ref core "rdze�" i \ref ui "UI".
     #define IM_SHARE 30000 ///< Od tej granicy zaczynaj� si� wiadomo�ci do \ref plug "wtyczek".
     #define IM_USER  40000 ///< Od tej granicy zaczynaj� si� wiadomo�ci do \ref plug "wtyczek" zdefiniowane przez u�ytkownika.

// -----------------------------------------------------------------------------------------------
     /**
       \defgroup im_ do Wtyczek
       \brief \no

       \{
     */

         // Inicjalizacja DLL'a
         #define IM_PLUG_NET       IM_SHARE+10     ///< Zwraca warto�� NET wtyczki.
         #define IM_PLUG_TYPE      IM_SHARE+11     ///< Zwraca warto�ci IMT_ wtyczki.
         #define IM_PLUG_VERSION   IM_SHARE+12     ///< Zwraca opis wersji wtyczki.
         #define IM_PLUG_SIG       IM_SHARE+13     ///< Zwraca sygnatur� wtyczki.
         #define IM_PLUG_CORE_V    IM_SHARE+14     ///< Zwraca wymagan� sygnatur� rdzenia (lub 0).
         #define IM_PLUG_UI_V      IM_SHARE+15     ///< Zwraca wymagan� sygnatur� UI (lub 0).
         #define IM_PLUG_NAME      IM_SHARE+16     ///< Zwraca nazw� wtyczki.
         #define IM_PLUG_NETNAME   IM_SHARE+17     ///< Zwraca nazw� sieci obs�ugiwanej przez wtyczk� (wy�wietlan� w oknach dialogowych) (lub 0).
         #define IM_PLUG_NETSHORTNAME   IM_SHARE+25     ///< Zwraca skr�con� nazw� sieci (jak "ICQ", "GG", "JABBER"), aby umo�liwi� u�ytkownikowi operowanie kr�tkimi nazwami sieci (np. przy tekstowym opisywaniu UID�w w parametrach) (lub 0).
		 #define IM_PLUG_UIDNAME   IM_SHARE+26   ///< Zwraca nazw� UIDu typow� dla obs�ugiwanej sieci, do wy�wietlania w oknach dialogowych (np "JID", "UIN" itd...) (lub 0)
         #define IM_PLUG_CERT      IM_BASE+18      ///< Zastrze�one dla wtyczek specjalnych.
         #define IM_PLUG_INFO      IM_BASE+19     ///< Wtyczka mo�e zalogowa� informacj� o swoim "stanie".
         #define IM_PLUG_SDKVERSION IM_BASE+20     ///< Zwraca #KONNEKT_SDK_V.

         #define IM_PLUG_PRIORITY  IM_BASE+21     ///<Wtyczka podaje sw�j priorytet w kolejkach (im wy�szy, tym znajdzie si� wcze�niej).
                                                   /// Wszystkie "zwyk�e" wtyczki mog� nie obs�ugiwa� tej wiadomo�ci, lub po prostu zwraca� 0 (ich priorytet zostanie ustawiony na PLUGP_STANDARD.
                                                   /// Dwie wtyczki o tym samym priorytecie ustawiane s� w kolejno�ci u�ytkownika.
                                                   /// Je�eli twoja wtyczka nie jest uzale�niona od kolejno�ci, NIE ustawiaj jej!
                                                   /// Dzi�ki priorytetom wiadomo�ci mog� by� obs�ugiwane w odpowiedniej kolejno�ci.
                                                   /// \return (PLUGP_enum) pozycja


         #define IM_PLUG_INIT      IM_BASE+1
         /**< Inicjalizacja wtyczki. Pierwszy przes�any IMessage nakazuj�cy wtyczce inicjalizacj� kodu.
                 \param cCtrl adres struktury steruj�cej
                 \param ID identyfikator wtyczki
         */

         #define IM_PLUG_DEINIT    IM_BASE+2      ///< Za chwil� uchwyt do wtyczki zostanie zwolniony. Najlepszy moment �eby posprz�ta�.
         #define IM_PLUG_INITEX    IM_BASE+3      ///< Zastrze�one dla wtyczek specjalnych.
		 #define IM_PLUG_ARGS      IM_BASE+24	  /**< Podaje wtyczkom argumenty przes�ane do programu.
Wysy�ane jest zaraz po uruchomieniu, oraz gdy zostanie uruchomiona kolejna instancja programu na tym samym profilu. W drugim przypadku podawane s� argumenty przekazane do drugiej instancji...
Argumenty maj� t� sam� struktur� co __argc i __argv.
Komunikat przesy�any jest przy pomocy @b sIMessage_plugArgs .*/ 
		/** Struktura u�ywana w #IM_PLUG_ARGS.*/
		struct sIMessage_plugArgs: public sIMessage_base {
			unsigned int argc;   ///< Ilo�� argument�w w argv
			const char * const * argv;   ///< Tablica wska�nik�w do argument�w

			sIMessage_plugArgs(unsigned int argc , const char * const * argv)
				:sIMessage_base(IM_PLUG_ARGS , Net::broadcast, imtAll), argc(argc),argv(argv) 
			{
				s_size=sizeof(*this);
			}

			const char * getArg(unsigned int i, const char * def = "") {
				return (i < this->argc) ? this->argv[i] : def;
			}
			bool argEq(unsigned int i, const char * cmp);
		};

/** Przekazuje komend� wpisan� w oknie @Dev. Komunikat przesy�any jest przy pomocy @b sIMessage_debugCommand. 
	@return 0
*/
		#define IM_DEBUG_COMMAND  IM_BASE+25

/** Je�eli podczas od��czania wtyczki z jakiego� wzgl�du nie powinno by� wywo�ywane FreeLibrary trzeba obs�u�y� ten komunikat i zwr�ci� 1. */
		#define IM_PLUG_DONTFREELIBRARY  IM_BASE+26

/** Wszystkie wtyczki zosta�y zainicjalizowane...
*/
		#define IM_ALLPLUGINSINITIALIZED IM_BASE + 22 

/** Za chwil� wtyczka o podanym ID zostanie od��czona.
	@param p1 (int) ID wtyczki
*/
		 #define IM_PLUG_PLUGOUT IM_BASE + 23     
        
/** Ta wersja wtyczki uruchamiana jest w tym profilu po raz pierwszy.
  @param p1 (int) Poprzednia wersja, lub 0. 
  Format wersji to w hexie: MNNRRBBB - Major, miNor, Release, Build.
  W plug_func.h mo�na znale�� makra do szybkiego wyci�gania tych warto�ci. 
*/
		#define IM_PLUG_UPDATE    IM_BASE+30     

         #define IM_GET_STATUS     IM_SHARE+31    ///< Je�eli wtyczka obs�uguje sie�, powinna zwr�ci� sw�j aktualny status.
                                                    /// \return (int) status
         #define IM_GET_STATUSINFO IM_SHARE+32    ///< Je�eli wtyczka obs�uguje sie�, powinna zwr�ci� sw�j aktualny opis statusu.
                                                    /// \return (const char *) opis statusu
		 #define IM_GET_UID		   IM_SHARE+33    /**< Je�eli wtyczka obs�uguje sie�, powinna zwr�ci� UID u�ytkownika programu w swojej sieci
													    @return (const char *) UID u�ytkownika
													*/

         #define IM_NEW_PROFILE    IM_BASE + 40   ///< Oznacza pierwsze uruchomienie danego profilu. Najlepszy moment �eby si� przywita�.
         #define IM_CANTQUIT       IM_BASE + 41   ///< Zwr�cenie \i true spowoduje anulowanie zamykania programu.
         #define IM_PASSWORDCHANGED IM_BASE + 42  ///< Oznacza zmian� has�a dla profilu.

		 #define IM_THREADSTART    IM_BASE + 43 ///< Aktualny w�tek w�a�nie zosta� uruchomiony. Lepiej polega� jednak na DllMain!
	 	 #define IM_THREADEND	   IM_BASE + 44 ///< Aktualny w�tek w�a�nie si� ko�czy. Lepiej polega� jednak na DllMain!

		 #define IM_MSG_RCV       IM_BASE+100
         /**< Wtyczka powinna sprawdzi� czy obs�uguje dany typ wiadomo�ci.
           Wtyczki odpytywane s� "od ko�ca". Ostatnia, kt�ra zwr�ci
           IM_MSG_RCV_ok b�dzie otrzymywa� r�wnie� IM_MSG_OPEN.
           \param p1 (cMessage *) wiadomo��.
           \param p2 (bool) \i true - wiadomo�� w�a�nie przysz�a , \i false - wiadomo�� zosta�a za�adowana z pliku.
           \return (int) Po��czone flagi \ref im_msg_, lub 0 je�li nie obs�uguje takich wiadomo�ci.
         */
         #define IM_MSG_SEND      IM_SHARE+100 /**< Wiadomo�� powinna zosta� wys�ana.
           \param p1 (cMessage *) Wiadomo��
           \return Je�li si� uda�o powinno zr�ci� \ref im_msg_.
         */
         #define IM_MSG_OPEN      IM_SHARE+101    /**< Wiadomo�� powinna zosta� otwarta.
           \param p1 (cMessage *) Wiadomo��
           \return Je�li si� uda�o powinno zr�ci� \ref im_msg_.
         */
         #define IM_MSG_ACK      IM_BASE+102    /**< Potwierdzenie wys�ania wiadomo�ci.
           \param p1 (cMessageAck *) Potwierdzenie. ID jest ustawiony na ID potwierdzanej wiadomo�ci (kt�ra jeszcze siedzi w kolejce i mo�na j� odczyta�).
         */

         /** @defgroup im_msg_ Zwroty z IM_MSG_* 
             #IM_MSG_RCV , #IM_MSG_SEND i #IM_MSG_OPEN mog� zwr�ci� po��czone
             takie flagi.
             @{
            */
            #define IM_MSG_ok     1 ///< Flaga zwrotna #IM_MSG_RCV - Musi by� ustawiona jesli wtyczka zamierza obs�u�y� wiadomo��.
            #define IM_MSG_delete 2 ///< Wiadomo�� powinna zosta� niezw�ocznie usuni�ta...
            #define IM_MSG_update 4 ///< Zawarto�� wiadomo�ci zosta�a zmieniona i powinna zosta� zaktualizowana jej kopia w kolejce.
            #define IM_MSG_processing 8 ///< Flaga zwrotna #IM_MSG_OPEN i #IM_MSG_SEND - Wiadomo�� jest dalej przetwarzana (np w osobnym w�tku) i zostanie usuni�ta z kolejki poprzez #IMC_MESSAGEREMOVE,
                                         ///  lub zako�czy przetwarzanie poprzez #IMC_MESSAGEPROCESSED.
         /** @} */
         #define IM_MSG_CHARLIMIT IM_BASE+105    ///< Zapytanie o limit znak�w na wiadomo��
                                            ///  \return Limit ilo�ci znak�w na wiadomo��. 0 - bez limitu
         // Config (IMT_CONFIG)
         #define IM_SETCOLS  IM_BASE+1001   ///< W tym momencie wtyczka powinna zadeklarowa� wszystkie kolumny w tablicach.

         #define IM_CFG_SAVE      IM_BASE+1010 ///< Ustawienia zaraz zostan� zapisane do pliku.
         #define IM_CFG_LOAD      IM_BASE+1011 ///< Ustawienia zosta�y wczytane.
         #define IM_CFG_CHANGED   IM_BASE+1020 ///< Ustawienia zostaly zmienione przez u�ytkownika.
         // UI
         #define IM_UI_PREPARE    IM_BASE+2000 ///< Najlepszy moment aby przygotowa� interfejs (np zdefiniowa� Akcje).

         #define IM_START         IM_BASE+2100 ///< Wtyczka powinna wystartowa�.
         #define IM_END           IM_BASE+2101 ///< Wtyczka powinna zako�czy� dzia�anie.
												/// @param p1 (bool) I powinna to zrobi� jak najszybciej...

         #define IM_BEFOREEND     IM_BASE+2102 ///< Za chwil� zostanie rozes�ane IM_END, ostatnia chwila, kiedy cCtrl::IsRunning() zwraca true.
												/// @param p1 (bool) Zamykanie jest w trybie "natychmiastowym". Nale�y wykonywa� jak najmniej operacji...

		 #define IM_UIACTION      IM_BASE+2200 ///< Powiadomienie o zdarzeniu w akcji.
                                               /// \param p1 (cUIActionNotify *) Powiadomienie.

         //  IMT_PROTOCOL
         #define IM_CONNECT       IM_SHARE+3000 /**< Mo�na zacz�� si� ��czy�.
		 @param p1 (int) Liczba ponowionych pr�b po��czenia
		 */
         #define IM_DISCONNECT    IM_SHARE+3001 ///< Trzeba si� roz��czy�.
         #define IM_AWAY          IM_SHARE+3002 ///< Program wchodzi w tryb Auto-Away.
         #define IM_BACK          IM_SHARE+3003 ///< Program powraca z trybu Auto-Away.
         #define IM_NEEDCONNECTION IM_BASE+3004 ///< Wysy�ana do kontrolek zaraz po w��czeniu
                                           ///  automatycznych po��cze� i na chwil� przed
                                           ///  wykonaniem pierwszego testu na istnienie po��czenia.
                                           ///  \attention W tej wiadomo�ci #IMC_SETCONNECT
                                           ///  powinny wywo�ywac wtyczki kt�re ZAWSZE potrzebuj� po��cze�
                                           ///  (niezale�nie od ustawienia #CFG_AUTOCONNECT).<br>
                                           ///  Pozosta�e powinny zg�osi� #IMC_SETCONNECT np. w #IM_PREPARE.

        #define  IM_CHANGESTATUS  IM_SHARE+3005  ///< Je�eli wtyczka obs�uguje sie�, powinna zmieni� sw�j status...
                                                 /// \param p1 (int) status (lub -1 je�li nie zmieniamy)
                                                 /// \param p2 (char*) opis (lub 0 je�li nie zmieniamy)
        #define  IM_ISCONNECTED   IM_SHARE+3006  ///< Trzeba zwr�ci� 1 je�li jeste�my po��czeni.
         #define IM_PING	       IM_SHARE+3007 ///< Wtyczka zamawia�a PING'a (na razie nie obs�ugiwane...)

         #define IM_CNT_UPLOAD    IM_SHARE+4000  /**< Informacje o kontakcie @a p1 zosta�y zmienione i moga by� np. zapisane na serwerze.
                                                  @param p1 (int) ID kontaktu do wys�ania
                                                  @param p2 (bool) 0 - info powinno by� wczytywane bezpo�rednio z tabeli. 
																   1 - info powinno by� wczytywane jako warto�ci odpowiednich akcji w oknie z informacjami o kontakcie (u�ywaj�c UIActionCfgGetValue())
												 */
         #define IM_CNT_DOWNLOAD  IM_SHARE+4001  /**< Informacje o kontakcie \a p1 powinny zosta� zaktualizowane (np. pobrane z serwera).
                                                  @param p1 (int) ID kontaktu do pobrania
                                                  @param p2 (bool) 0 - info powinno zosta� zapisane bezpo�rednio w tabeli. 
																	1 - info powinno by� ustawione jako warto�ci odpowiednich akcji w oknie z informacjami o kontakcie (u�ywaj�c UIActionCfgSetValue())
												  */


/** Kontakt zaraz zostanie usuni�ty.
	\param p1 (int) ID kontaktu
	\param p2 (bool) true - usuni�cie zosta�o potwierdzone przez uzytkownika.*/
		#define IM_CNT_REMOVE    IM_BASE+4002  
/** Kontakt zosta� usuniety.
	\param p1 (int) ID kontaktu
	\param p2 (bool) true - usuni�cie zosta�o potwierdzone przez uzytkownika.*/
		#define IM_CNT_REMOVED    IM_BASE+4005 
         #define IM_CNT_ADD       IM_BASE+4003  ///< Kontakt zosta� dodany
                                                 ///  \param p1 (int) ID kontaktu
         #define IM_CNT_ADDING    IM_BASE+4004  ///< Kontakt jest w trakcie tworzenia (kt�re mo�e zosta� ew. przerwane)
                                                 ///  Parametry kontaktu nie s� jeszcze ustalone.
                                                 ///  \param p1 (int) ID kontaktu
/** ��danie szukania kontaktu (np. w katalogu sieci)
	\param p1 (sCNTSEARCH *) parametry wyszukiwania
	*/
		#define IM_CNT_SEARCH    IM_BASE+4010  
/** Kt�ra� z cech kontaktu (np. UID) zosta�a zmieniona. Przesy�ane przy pomocy sIMessage_CntChanged. Je�eli przecastujesz to na sIMessage_2params to \a p1 jest ID kontaktu.
*/
		#define IM_CNT_CHANGED   IM_BASE+4006  

         /** Struktura do przesy�ania #IM_CNT_CHANGED.*/
            struct sIMessage_CntChanged:public sIMessage_base {
                unsigned int _cntID; ///< ID kontaktu
				union {
					///< Oznacza co zosta�o zmienione. 
					struct {
						unsigned net : 1;
						unsigned uid : 1;
						unsigned group : 1;
					} _changed; 
					unsigned int _changed_bitmap;
				};
                unsigned int _oldNet; ///< Poprzednia warto�� net tego kontaktu
                const char * _oldUID; ///< Poprzednia warto�� UID
				sIMessage_CntChanged(int msgID , int cntID):sIMessage_base(msgID),_cntID(cntID),_changed_bitmap(0),_oldNet(Net::none),_oldUID(0){s_size=sizeof(*this);}
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
						this->_oldNet = Net::none;
						this->_oldUID = 0;
                    } else throw 0;
                }
            };

         #define IM_CNT_STATUSCHANGE IM_BASE+4011 ///< Status kontaktu zaraz ulegnie zmianie.
                                             ///  sIMessage_StatusChange *

         #define IM_CNT_COMPOSING IM_SHARE+4030 /**< U�ytkownik pisze wiadomo�� do wskazanego kontaktu.
											      Wys�ane do interfejsu spowoduje rozes�anie #IM_CNT_COMPOSING do wszystkich wtyczek
												  i je�eli w przeci�gu kilkunastu sekund nie zostanie wys�ane ponownie roze�le
												  #IM_CNT_COMPOSING_STOP.
                                                  @param p1 (int) ID kontaktu
											     */
         #define IM_CNT_COMPOSING_STOP IM_SHARE+4031 /**< U�ytkownik przesta� pisa� do wskazanego kontaktu.
												 Wys�ane do interfejsu spowoduje rozes�anie do wtyczek #IM_CNT_COMPOSING_STOP je�eli
												 w przeci�gu ostatnich kilkunastu sekund wyst�pi�o zdarzenie #IM_CNT_COMPOSING z tym samym kontaktem.
                                                     @param p1 (int) ID kontaktu
												     */


         #define IM_STATUSCHANGE IM_BASE+4012 ///< Status wtyczki zaraz ulegnie zmianie.
                                             ///  sIMessage_StatusChange *

         /** Struktura do przesy�ania #IM_CNT_STATUSCHANGE i #IM_STATUSCHANGE.*/
            struct sIMessage_StatusChange:public sIMessage_base {
                union {
                    unsigned int cntID; ///< ID kontaktu
                    unsigned int plugID; ///< ID wtyczki zmieniaj�cej status.
                };
                unsigned int status; ///< Nowy status, kt�ry zaraz zostanie ustawiony. -1 oznacza brak zmiany.
                const char * info; ///< Nowy opis statusu, kt�ry zaraz zostanie ustawiony. 0 oznacza brak zmiany.

                sIMessage_StatusChange(int msgID , int cntID , unsigned int status, const char * info):sIMessage_base(msgID),cntID(cntID),status(status),info(info){s_size=sizeof(*this);}
                sIMessage_StatusChange(const sIMessage_base * base) {
                    if (base->s_size < sizeof(*this)) throw cKException_Msg(0 , base);
                    *this = *(sIMessage_StatusChange*)base;
                    s_size=sizeof(*this);
                }
            };


         #define IM_GRP_CHANGED   IM_BASE+4020 ///< Lista grup uleg�a zmianie.
         #define IM_IGN_CHANGED   IM_BASE+4021 ///< Lista ignorowanych kontakt�w uleg�a zmianie.
                                                /// \param p1 (int) sie� >0 - kontakt zosta� dodany, <0 - usuni�ty
                                                /// \param p2 (char*) 

    
         /** Parametry wyszukiwania/wyniki wyszukiwania.
            Struktura wykorzystywana zar�wno podczas wysy�ania zapytania, jak i zwracania wynik�w.
         */
         struct sCNTSEARCH {
            unsigned short s_size; ///< Musi zawiera� rozmiar struktury. Ustawiany przez kontruktor.
            int status;   ///< Podczas szukania - 1 - szukaj tylko online. Podczas zwracania - status kontaktu.
            char uid      [256] /// UID
                ,name     [101] /// Imi�
                ,surname  [101] /// Nazwisko
                ,nick     [101] /// Ksywa
                ,city     [51] /// Miasto
                ,email    [101]/// Email
                ,phone    [51] /// Telefon
                ,other    [256] /// Inne (tylko w odpowiedzi)
                ;
            int gender; ///< P�e� 0 - nieznana , 1 - kobieta , 2 - m�czyzna
            int born_min; ///< Urodzony, OD roku
            int born_max; ///< Urodzony, DO roku
            int net;    ///< Numer sieci.
            int start;  ///< Od jakiej pozycji pokazywa� dalej.
                        /// Przy zwracaniu, ostatni znaleziony kontakt powinien mie� ustawiony \start
                        /// na pozycj� od kt�rej mo�na wznowi� wyszukiwanie.
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
  /** \} */  // Wiadomo�ci do WTYCZEK

// -----------------------------------------------------------------------------------------------
  /**
    \defgroup imc_ do Rdzenia
    \brief \no

    \{
  */
        #define IMC_LOG              1 ///< Je�eli program jest debugowany , zapisuje tekst w konnekt.log . Wiadomo�� nie jest rozpoznawana przez Core (wiec ustawi blad!)
                                        ///  \param p1 (char*) tekst.
        #define IMC_GETPROFILE       2 ///< Zwraca nazw� profilu.
                                        ///  \return (char *)

        #define IMC_DEBUG            3 ///< Otwiera okno developera
        #define IMC_ISDEBUG          4 ///< Zwraca true gdy jest w trybie developera.
        #define IMC_ISBETA           9 ///< Zwraca true gdy jest w trybie beta.
        #define IMC_BETA             40 ///< Otwiera okno beta-testera
        #define IMC_REPORT           41 ///< Otwiera okno raportowania
        #define IMC_PLUGS            42 ///< Otwiera okno wtyczek
        #define IMC_NET_TYPE         43 ///< Pobiera ��czn� warto�� flag typ�w (#IM_PLUG_TYPE) ze wszystkich wtyczek danej sieci.
                                         ///  \param p1 (int) sie�
		#define IMC_SESSION_ID		 44 /**< Zwraca identyfikator sesji profilu Konnekta.
Przy jego pomocy mo�na odr�ni� dwie instancje korzystaj�ce z r�nych profili...
@return (const char*) identyfikator sesji (MD5 �cie�ki katalogu profilu)
										 */
		#define IMC_GET_HINTERNET	 45 /**< Zwraca globalny uchwyt sesji WinInet otwartej przez InternetOpen (z ustawionym Proxy wg. konfiguracji). 
										 @return (HINTERNET) uchwyt, NIE mo�na go zamyka�!*/
		#define IMC_HINTERNET_OPEN	 46 /**< Tworzy i zwraca uchwyt sesji WinInet otwartej przez InternetOpen (z ustawionym Proxy wg. konfiguracji). 
										 @param p1 (const char*) UserAgent
										 @return (HINTERNET) uchwyt, trzeba go zamyka�!*/
		#define IMC_GET_MAINTHREAD   47 /**< Zwraca uchwyt do g��wnego w�tku.
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
					net = Net::none;
					type = imtNone;
					s_size=sizeof(*this);
				}
		};


		#define IMC_ARGC             5 ///< Zwraca liczb� parametr�w przekazanych do programu.
        #define IMC_ARGV             6 ///  Zwraca parametr \a p1. 
								        ///  \param p1 (int) numer parametru
								        ///  \return (char*) 

        #define IMC_ISWINXP          60 ///< Zwraca 1, je�li korzystamy z ComCtl6 na winXP.
        #define IMC_ISNEWPROFILE     61 ///< Zwraca 1, gdy jest to pierwsze uruchomienie na tym profilu.  
        #define IMC_ISNEWVERSION     62 ///< Zwraca 1, gdy jest to pierwsze uruchomienie na nowej wersji.
                                         ///  \warning Wynik jest ma�o miarodajny i mo�e by� fa�szywy! Wiarygodne wyniki
                                         ///  zostan� przes�ane w IM_PLUG_UPDATE
        #define IMC_CONNECTED        7 ///< Zwraca true, je�li jeste�my pod��czeni do internetu.
        #define IMC_VERSION          8 ///< Zwraca wersj� rdzenia.
								        ///  \param p1 (char *) Wska�nik do ci�gu znak�w do zapisania wersji tekstowo, lub NULL.
                                        ///  \return (int) #VERSION_TO_NUM


        #define IMC_SHUTDOWN        10 ///< Zamyka program.
										/// @param p1 (bool) Czy zamkn�� go natychmiastowo?
        #define IMC_DISCONNECT      11 ///< Roz��cza wszystkie wtyczki z sieci.
        #define IMC_RESTART         17 ///< Restartuje program.
        #define IMC_PROFILESDIR     23 ///< �cie�ka do katalogu z profilami.
                                        ///  \return (const char *)
        #define IMC_PROFILEDIR      12 ///< �cie�ka do katalogu z profilem.
                                        ///  \return (const char *)
        #define IMC_RESTORECURDIR   24 ///< Przywrca aktywn� �cie�k� na katalog programu i j� zwraca.
									   ///  @return (const char *) katalog z programem		
        #define IMC_KONNEKTDIR      IMC_RESTORECURDIR ///< Przywraca aktywn� �cie�k� na katalog programu i j� zwraca.
        #define IMC_GETBETALOGIN    25 
        #define IMC_GETBETAPASSMD5  27 
        #define IMC_GETBETAANONYMOUS 31
/** Zwraca "numer seryjny" instalacji Konnekta, losowa liczba u�ywana najcz�ciej do rozr�niania kopii programu w statystykach */
		#define IMC_GETSERIALNUMBER       33 
		#define IMC_LOGDIR			29 ///< Zwraca �cie�k� do katalogu z log'ami.
										/// @return (char*) �cie�ka zako�czona '\\'
		#define IMC_TEMPDIR			32 ///< Zwraca �cie�k� do katalogu tymczasowego.
										/// @return (char*) �cie�ka zako�czona '\\'
        #define IMC_PROFILECHANGE   13 ///< Zmienia/tworzy profil.
                                        ///  \param p1 (char*) nazwa
                                        ///  \param p2 (bool) true je�li profil ma by� utworzony
                                        ///  \return true je�li si� uda�o
        #define IMC_PROFILEREMOVE   14 ///< Usuwa aktualnie u�ywany profil.
        #define IMC_PROFILEPASS     15 ///< Otwiera okno do ustawiania has�a.
        #define IMC_GETMD5DIGEST    16 ///< Zwraca has�o profilu jako MD5Digest.
                                        ///  \param p1 (unsigned char [16]) bufor do zapisania.

        #define IMC_SAVE_CFG        20 ///< Zapisuje ustawienia na dysk.
        #define IMC_SAVE_CNT        21 ///< Zapisuje kontakty na dysk.
        #define IMC_SAVE_MSG        22 ///< Zapisuje kolejk� wiadomo�ci na dysk.
		#define IMC_CFG_CHANGED	28

        #define IMC_SETCONNECT      30 ///< Ustawia wtyczk� na li�cie "rz�danych po��cze�".
                                        ///  W chwili wykrycia po��czenia z internetem, 
                                        ///  lub gdy jest po��czenie po kilkudziesi�ciu sekundach
                                        ///  zostanie wys�any do wtyczki komunikat #IM_CONNECT.
                                        /// \param p1 (bool) stan - 1 ��cz , 0 - przesta� pr�bowa�

        #define IMC_THREADSTART     50 // Wiadomo�� wykorzystywana TYLKO przez UI
        #define IMC_THREADEND	   51   // Wiadomo�� wykorzystywana TYLKO przez UI

        #define IMC_NEWMESSAGE     100 ///< Dodaje wiadomo�� do kolejki.
                                        ///  \attention Zawarto�� struktury mo�e ulec zmianie! Je�eli tworzymy bufory tekstowe, zwalnia� trzeba je przez
                                        ///  lokalne kopie adres�w, a nie wska�niki w strukturze!!!
                                        ///  \param p1 (cMessage*) wiadomo��.
                                        ///  \return (int) id wiadomosci

        //       #define NMF_SEND      1   // Flagi wiadomosci

        #define IMC_MESSAGEQUEUE   101 ///< Sprawdza kolejk� wiadomo�ci.
                                        ///  Pr�buje przyj��/rozes�a� oczekuj�ce wiadomo�ci.
                                        ///  \param p1 (sMESSAGESELECT*) kt�re wiadomo�ci  maja zosta� sprawdzone.
        #define IMC_MESSAGENOTIFY  102 ///< Szuka powiadomienia o nowej wiadomo�ci dla danego UIDa w kolejce wiadomo�ci.
                                        ///  \param p1 (sMESSAGENOTIFY*) struktura podaj�ca czego szuka� i przyjmuj�ca wynik.
        #define IMC_MESSAGEWAITING 103 ///< Podaje ile wiadomo�ci oczekuje w kolejce
                                        ///  \param p1 (sMESSAGESELECT*) kt�re wiadomo�ci maj� zosta� uwzgl�dnione
                                        ///  \return (int) liczba wiadomo�ci spe�niaj�cych kryteria
        #define IMC_MESSAGEREMOVE  104 ///< Usuwa wiadomo�ci z kolejki.
                                        ///  \param p1 (sMESSAGESELECT*) Rodzaj wiadomo�ci do usuni�cia
                                        ///  \param p2 (int) Ile maxymalnie usun��
                                        ///  \return false gdy si� nie powiedzie
        #define IMC_MESSAGEGET     106 ///< Pobiera pierwsz� wiadomo�� kt�ra spe�nia kryteria.
                                        ///  \param p1 (sMESSAGESELECT*) Rodzaj wiadomo�ci do pobrania.
                                        ///  \param p2 (cMessage*) Struktura do kt�rej zostanie zapisana wiadomo��.
                                        ///  \retrun 1 - je�li si� powiod�o
        #define IMC_MESSAGEACK     107 ///< Potwierdzenie wys�ania wiadomo�ci.
                                        ///  W cMessageAck::id \b musimy poda� ID potwierdzanej wiadomo�ci.
                                        ///  Ustawienie msg i ext jest opcjonalne.
                                        ///  \param p1 (cMessageAck*) Struktura z potwierdzeniem.
        #define IMC_MESSAGEPROCESSED 108 ///< Zako�czenie przetwarzania.
                                          /// Po sko�czeniu przetwarzania wiadomo�ci, na kt�r� odpowiedzieli�my flag� IM_MSG_processing
                                          /// wysy�amy ten komunikat, by rdze� "odznaczy�" nasz� wiadomo��. 
                                          /// #IMC_MESSAGEPROCESSED wysy�a si� tylko, gdy wiadomo�� nie zosta�a od razu usuni�ta.
                                          /// \param p1 (int) ID wiadomo�ci.
                                          /// \param p2 (bool) true - wiadomo�� mo�e zosta� usuni�ta

        /** Struktura s�u��ca do wybierania wiadomo�ci.
            \sa #IMC_MESSAGEREMOVE #IMC_MESSAGEWAITING #IMC_MESSAGEGET #IMC_MESSAGEQUEUE*/
        typedef  struct sMESSAGESELECT {
            unsigned short s_size;
            int net; ///< Sie� kontaktu. Ustaw na #NET_BC aby u�y� wszystkich sieci.
            const char * uid;  ///< UID kontaktu. Ustaw 0 aby u�y� wszystkich.
            int type; ///< Typ wiadomo�ci. Ustaw na -1 �eby u�y� wszystkich.
            unsigned int wflag; ///< Tylko wiadomo�ci posiadaj�ce te flagi. 0 �eby u�y� wszystkich.
            unsigned int woflag; ///< Tylko wiadomo�ci nie posiadaj�ce tych flag. 0 �eby u�y� wszystkich.
            int id; ///< ID wiadomo�ci, -1 �eby u�y� wszystkich.
			unsigned int position; ///< Kt�re z kolei przyj�� dopasowanie?
			sMESSAGESELECT() {s_size=sizeof(sMESSAGESELECT);net=Net::broadcast;uid=0;type=-1;wflag=0;woflag=0;id=-1;position=0;}
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
Je�eli @a net b�dzie ustawiony na NET_NONE w UID mo�na przekaza� (tekstem) ID kontaktu. Je�eli kontakt o danym ID istnieje, ID zostanie zwr�cone. Funkcjonalno�� ta mo�e s�u�y� g��wnie do "przemycania" bezpo�rednich identyfikator�w kontakt�w do f-cji kt�re przyjmuj� tylko warto�ci net i uid.

@param p1 (int) net
@param p2 (char*) UID
@return (int) ID
*/
		#define IMC_FINDCONTACT    200 
        #define IMC_PLUG_COUNT    240 ///< Zwraca liczb� wtyczek.
        #define IMC_PLUG_HANDLE    241 ///< Zwraca windowsowy uchwyt do wtyczki.
                                        ///  \param p1 (int) pozycja na li�cie wtyczek.
                                        ///  \return (int) HINSTANCE
        #define IMC_PLUG_ID        243 ///< Zwraca ID wtyczki.
                                        ///  \param p1 (int) pozycja na li�cie wtyczek.
                                        ///  \return (int) ID
        #define IMC_PLUG_FILE     242  ///< Zwraca �cie�k� do pliku dll wtyczki.
                                        ///  \param p1 (int) pozycja na li�cie wtyczek.
                                        ///  \return (char*) �cie�ka
        #define IMC_PLUGID_HANDLE  244 ///< Zwraca windowsowy uchwyt do wtyczki.
                                        ///  \param p1 (int) ID wtyczki.
                                        ///  \return (HINSTANCE) uchwyt
        #define IMC_PLUGID_POS     245 ///< Zwraca pozycj� wtyczki.
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
        #define IMC_PLUG_VERSION    26 ///< Zwraca wersj� wtyczki.
                                        ///  \param p1 (int) Pozycja wtyczki na li�cie, lub -1 aby sprawdzi� wersj� rdzenia.
								        ///  \param p2 (char *) Wska�nik do ci�gu znak�w do zapisania wersji tekstowo, lub NULL.
                                        ///  \return (int) #VERSION_TO_NUM

		/** Od��cza wtyczk� o podanym identyfikatorze podaj�c opowiednie uzasadnienie.
		    
		*/
		struct sIMessage_plugOut:public sIMessage_base {
			const static int __msgID = 250;
			int _plugID;
			const char * _reason;
			enum enRestart {
				erNo = 0 , erAsk = 1 , erYes = 2 , erAskShut = 3 , erShut = 4

			} _restart; ///< Czy restartowa� program?
			enum enUnload{
				  euNow=1 /// Nie powinno by� ustawiane p�niej ni� w #IMI_ALLPLUGSINITIALIZED
				, euNextStart=2
				, euNowAndOnNextStart=3
			} _unload; ///< Kiedy j� od��czy�?
            sIMessage_plugOut(int plugID , const char * reason , enRestart restart = erAsk , enUnload unload = euNextStart):sIMessage_base(__msgID)
				,_plugID(plugID),_reason(reason),_restart(restart),_unload(unload){s_size=sizeof(*this);}
        };


        #define IMC_STATUSCHANGE   246 ///< Informuje rdze�, �e za chwil� nast�pi zmiana statusu wtyczki.
                                        ///  Rdze� rozsy�a IM_STATUSCHANGE.
                                        ///  \warning Ten komunikat trzeba wys�a� PRZED zmian� statusu, nie trzeba podawa�
                                        ///  \a plugID. Jako \a status i \a info trzeba poda� dane, kt�re zaraz zostan� ustawione.
                                        ///  sIMessage_StatusChange


        #define IMC_CNT_IGNORED    310 ///< Sprawdza czy kontakt jest ignorowany.
                                        ///  \param p1 (int) net
                                        ///  \param p2 (char*) UID
                                        ///  \return true je�li jest.
        #define IMC_CNT_FIND       IMC_FINDCONTACT ///< \no

/**Sprawdza czy kontakt o podanym ID istnieje.
@param p1 (int) ID.*/
		#define IMC_CNT_IDEXISTS   233 

/** Dodaje kontakt.
Po ustawieniu parametr�w kontaktu, lub od razu po #IMC_CNT_ADD trzeba wys�a� #IMC_CNT_CHANGED
@param p1 (int) sie�
@param p2 (int) UID
@return (int) ID nowego kontaktu
*/
		#define IMC_CNT_ADD        230 

/**Usuwa kontakt
@param p1 (int) ID
@param p2 (bool) true - u�ytkownik zostanie zapytany o zgod�.
*/
		#define IMC_CNT_REMOVE     231 

/**Zwraca ilo�� kontakt�w.
@return (int) liczba kontakt�w.
*/
		#define IMC_CNT_COUNT      201 

/** Sprawdza czy podany kontakt znajduje sie w grupie.
@param p1 (int) ID kontaktu.
@param p2 (char*) - grupa do sprawdzenia (je�li == 0 sprawdzi w grupie aktywnej)
@return (bool) true je�li znajduje si�...
*/
		#define IMC_CNT_INGROUP    305 


/** Kontakt zosta� zmieniony.
Komunikat powinien by� wysy�any \b tylko w sytuacji zmiany #CNT_UID, #CNT_NET, lub zaraz po dodaniu!
Do wszystkich wtyczek z typem #IMT_CONTACT zostanie rozes�ane #IM_CNT_CHANGED, lub #IM_CNT_ADD.
Nie ma ju� potrzeby wysy�ania #IMI_REFRESH_CNT
@param p1 ID kontaktu.
*/
		#define IMC_CNT_CHANGED     232 
        #define IMC_CNT_SETSTATUS  234 ///< Zmienia status kontaktu.
                                        ///  sIMessage_StatusChange


        #define IMC_IGN_FIND       IMC_CNT_IGNORED
        #define IMC_IGN_ADD        311 /**< Dodaje kontakt do listy ignorowanych.
                                         \param p1 (int) sie�
                                         \param p2 (char*) UID
										 */
        #define IMC_IGN_DEL        312 /**< Usuwa kontakt z listy ignorowanych.
                                          \param p1 (int) sie�
                                          \param p2 (char*) UID
										  */

        #define IMC_GRP_FIND       300 /**< Sprawdza czy grupa istnieje.
                                          \param p1 (char*) nazwa grupy.
                                          \return (bool) true je�li istnieje.
										  */
        #define IMC_GRP_ADD        301 /**< Dodaje grup�.
                                          \param p1 (char*) nazwa grupy.
										  */
        #define IMC_GRP_DEL        302 /**< Usuwa grup�.
                                          \param p1 (char*) nazwa grupy.
										  */
        #define IMC_GRP_RENAME     303 /**< Zmienia nazw� grupy.
                                          \param p1 (char*) stara nazwa grupy.
                                          \param p2 (char*) nowa nazwa grupy.
										  */


        /** Komunikat do rejestrowania kolumn w tablicach.
            \attention Mo�e by� wysy�ane TYLKO PODCZAS przetwarzania komunikatu #IM_SETCOLS.
		*/
		class sIMessage_setColumn: public sIMessage_base {
		public:
			const static int __msgID = 1102;
			tTable _table; ///< Tablica w kt�rej ustawiamy kolumn�
			int _id; ///< ID kolumny.
			int _type; ///< typ kolumny (patrz \ref dt_ct_).
			union {
			   int _def; ///< Warto�� domy�lna.
			   const char * _def_ch; ///< Warto�� domy�lna dla kolumn #DT_CT_PCHAR (musi by� ci�gle w pami�ci!)
			   __int64 * _def_p64; ///< Warto�� domy�lna dla kolumn #DT_CT_64 (musi by� ci�gle w pami�ci!)
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
		
        #define IMC_CFG_SAVE     1010  ///< Wszystkie ustawienia zostan� zapisane.

        // W32
        #define IMC_GETINSTANCE    2000 ///< Zwraca HINSTANCE aplikacji.

        // internal use only.
        #define IMC_GETMSGCOLDESC  3000

        /** @defgroup imc_mru_ MRU.
            Obs�uga listy ostatnio u�ywanych.
            @{
        */
        #define MRU_SET_LOADFIRST  0x1 ///< Zawarto�� listy zostanie najpierw za�adowana (dzia�aj� te� flagi dla MRU_GET_ !)
        #define MRU_GET_ONEBUFF    0x10 ///< sMRU::buffer jest wska�nikiem do bufora (o rozmiarze sMRU::buffSize), kt�ry zostanie u�yty do wszystkich operacji
        #define MRU_GET_USETEMP    0x20 ///< zostanie u�yty tymczasowy bufor wewn�trzny rdzenia.
            /** Struktura u�ywana przez IMC_MRU_* */
            struct sMRU {
                int flags; ///< Flagi
                const char * name; ///< Nazwa zestawu
                int count; ///< Rozmiar zestawu
                int buffSize; ///< Rozmiar bufor�w dla #IMC_MRU_GET
                const char * current; ///< Przy #IMC_MRU_SET i #IMC_MRU_UPDATE podajemy dodawan� warto��.
                union {
                    char ** values; ///< Tablica \a count bufor�w. Przy #IMC_MRU_GET musz� mie� rozmiar podany w \a buffSize.
                                    /// Je�eli jest mniej bufor�w ni� w count, ostatnia pozycja musi by� r�wna 0.
                    char * buffer; ///< Wska�nik do pojedy�czego bufora trzymaj�cego wszystkie informacje
                };
                const char * removed; /// #IMC_MRU_UPDATE zapisze tu element, kt�ry zosta� odrzucony.
                sMRU():flags(0),count(0),buffSize(0),name(0),current(0),values(0){}
            };
            #define IMC_MRU_SET  400 ///< (sIMessage_MRU*) Ustawia list� MRU. 
            #define IMC_MRU_GET  401 ///< (sIMessage_MRU*) Pobiera list� MRU. 
            #define IMC_MRU_UPDATE  402 ///< (sIMessage_MRU*) Aktualizuje list� MRU. 

            /** Struktura do przesy�ania #IMC_MRU_GET, #IMC_MRU_SET i #IMC_MRU_UPDATE.*/
            struct sIMessage_MRU:public sIMessage_base {
                sMRU * MRU; ///< \brief \no
                sIMessage_MRU(int id , sMRU * MRU):sIMessage_base(id),MRU(MRU){s_size=sizeof(*this);}
            };
        /** @} */


  /** \} */  // Wiadomo�ci do rdzenia

        
// -----------------------------------------------------------------------------------------------
  // Wiadomosci do UI.dll
  /**
    \defgroup imi_ do UI
    \brief \no

    \{
  */



        #define IMI_PREPARE   IMI_BASE+0   // Tylko dla Rdzenia 
        #define IMI_DEBUG     IMI_BASE+1   ///< Otwiera okno debugowania interfejsu.
                                            ///  Dost�pne tylko w wersjach Debug i Beta.
		#define IMI_SET_SHOWBITS IMI_BASE+10 ///< Otwiera okno ustawiania ShowBits
		#define IMI_SET_PLUGINS IMI_BASE+11 ///< Otwiera okno wyboru wtyczek
        //  #define IMI_UIINVALIDATE IMI_BASE+100 // (0,0)  -  odnawia listy akcji
// -----------------------------------------------------------------------------------------------
        /**\defgroup imi_action_ Obs�uga akcji.
		  System akcji w interfejsie odpowiada za obs�ug� np. kontrolek
		  w konfiguracji, menus�w czy przycisk�w na toolbarach.
		  @warning Akcje dla kontakt�w korzystaj� tylko z jednego obiektu akcji, kt�ry jest "prze��czany" na aktualnie ��dany kontakt. Nie powinno si� wi�c ustawia� parametr�w akcji zale�nie od kontaktu!

           \{
        */
// -----------------------------------------------------------------------------------------------
            /** @defgroup ac_ Numery kontakt�w akcji. 
                @{ */
                #define AC_USER 0      ///< Akcja jest przypisana do u�ytkownika.
                #define AC_NONE -1L    ///< Akcja nie jest przypisana do �adnego kontaktu.
                #define AC_CURRENT -2L ///< Ostatnio przypisany kontakt.
            /** @} */

            #define IMI_ACTION    IMI_BASE+101  /**< Wstawia akcj�.
                                                    \param p1 (#sUIActionInfo*) Ustawienia akcji. MUSZ� by� ustawione \a parent i \a id.
                                                    */
            #define IMI_GROUP     IMI_BASE+102  /**< Wstawia grup�.
                                                    Dzia�a tak samo jak #IMI_ACTION z #ACTS_GROUP ustawionym w \a status.
                                                    \param p1 (#sUIActionInfo*) Ustawienia akcji. MUSZ� by� ustawione \a parent i \a id.
                                                    \attention Identyfikatory grup \b musz� by� niepowtarzalne!
                                                    */
            #define IMI_ACTION_CALL  IMI_BASE+103 /**< Wywo�uje akcj� (w innej wtyczce).
                                                        \param p1 (sUIActionNotify_base*) Powiadomienie o zdarzeniu do wys�ania.
                                                    */
            #define IMI_ACTION_GET   IMI_BASE+107 /**< Pobiera w�a�ciwo�ci akcji.
                                                        \param p1 (sUIActionInfo *). Musi mie� ustawiony \a parent , \a id , oraz \a mask (je�eli \a mask == 0 pobiera wszystko).

                                                        \attention Przy pobieraniu \a txt trzeba ustawi� \a txt na bufor \b char * i \a txtSize na rozmiar tego bufora.
                                                                    Je�eli \a txt == 0 zostanie ono ustawione na 2 kilobajtowy bufor wewn�trzny.
                                                                    <br><Br>
                                                                    Zawsze ustawia \a pos , \a handle i \a type .
                                                    */
            #define IMI_ACTION_SET   IMI_BASE+108 /**< Ustawia w�a�ciwo�ci akcji.
                                                        \param p1  (sUIActionInfo *). Musi mie� ustawiony \a parent , \a id , oraz \a mask (je�eli \a mask == 0 ustawia wszystko).
                                                        \attention Mo�na zmienia� tylko: \a status , \a exStyle , \a p1 , \a p2 , \a param , \a ico i \a txt.
                                                        */
            #define IMI_ACTION_GETVALUE IMI_BASE+106 /**< Pobiera warto�� kontrolki w konfiguracji.
                                                        \param p1  (sUIActionInfo *). Warto�� zostanie ustawiona w \a txt.
                                                        \return (char *) (to samo co w \a txt), lub 0 je�li wyst�pi b��d.
                                                    */
            #define IMI_ACTION_SETVALUE IMI_BASE+110 /**< Ustawia warto�� kontrolki w konfiguracji.
                                                        \param p1  (sUIActionInfo *). Warto�� musi znajdowa� si� w \a txt.
                                                        \return (char *) (to samo co w \a txt), lub 0 je�li wyst�pi b��d.
                                                    */
            #define IMI_GROUP_ACTIONSCOUNT IMI_BASE+111 /**< Zwraca ilo�� akcji nale��cych do podanej grupy.
                                                        \param p1 (sUIAction*)
                                                        \return (int)
                                                    */
            #define IMI_ACTION_EXISTS  IMI_BASE+112 /**< Sprawdza czy akcja istnieje.
                                                        \param p1 (sUIAction*)
                                                        \return (bool)
                                                        */
            #define IMI_ACTION_ISGROUP  IMI_BASE+113 /**< Sprawdza czy akcja jest grup�.
                                                        \param p1 (int) parent
                                                        \return (bool)
                                                        */
            #define IMI_ACTION_GETID  IMI_BASE+114 /**< Zwraca identyfikator akcji na podanej pozycji w grupie.
                                                        \param p1 (int) parent
                                                        \param p2 (int) pozycja
                                                        \return (int) ID
                                                        */
            #define IMI_ACTION_REMOVE IMI_BASE+115 /**< Usuwa akcj�.
                                                        \warning Mo�e zosta� wywo�ane TYLKO gdy akcja nie jest utworzona!
                                                        \param p1 (sUIAction*) akcja do usuni�cia
                                                        \return (bool)
                                                        */
            #define IMI_ACTION_GETTYPE IMI_BASE+116/**< Pobiera typ akcji (\ref act_).
                                                        \param p1 (sUIAction*) Akcja
                                                        \return (int)
                                                        */
            #define IMI_GROUP_GETHANDLE IMI_BASE+117/**< Pobiera uchwyt grupy (np. uchwyt g��wnego okna)
                                                        \param p1 (sUIAction*) Akcja
                                                        \return (HANDLE)
                                                        */
            #define IMI_ACTION_FINDPARENT  IMI_BASE+118/**< Znajduje rodzica akcji o identykatorze sUIAction::id, zaczynaj�c
                                                             szukanie w sUIAction::parent. Je�eli p2 jest r�wne 1, 
                                                             znaleziony identyfikator zostanie usatwiony w strukturze przekazanej
                                                             w polu p1.
                                                        \param p1 (sUIAction*) Akcja. 
                                                        \param p2 (bool) Czy zapisa� wynik w p1?
                                                        \return (int)
                                                        */
			#define IMI_GETPLUGINSGROUP IMI_BASE+119 /**< Pobiera identyfikator grupy, kt�r� u�ytkownik
														   wskaza� jako grup� dla menu wtyczek. 
														   @return (int) ID grupy*/
			#define IMI_GROUP_MAKECFG IMI_BASE+120   /**< Je�eli grupa jest grup� konfiguracji i okno konfiguracji jest otwarte upewnia si�, czy wszystkie kontrolki grupy s� utworzone.
														   @param p1 (sUIAction*) Akcja.
														   @return (bool) uda�o si�, lub nie
														   */
			#define IMI_ACTION_SETCNT IMI_BASE+121   /**< Przypisuje kontrolk� do kontaktu (podanego w sUIAction).
														   @param p1 (sUIAction*) Akcja.
														   @param p2 (bool) Czy ustawia� rekurencyjnie?
														   */
			#define IMI_ACTION_GETINDEX IMI_BASE+122   /**< Pobiera indeks kontrolki (numer przypisywany w WinApi oknom, przyciskom na toolbarach itd).
														   @param p1 (sUIAction*) Akcja.
														   @return (int) indeks
														   */
			#define IMI_ACTION_GETOWNER IMI_BASE+123   /**< Pobiera identyfikator wtyczki, kt�ra utworzy�a akcj� i obs�uguje jej komunikaty
														   @param p1 (sUIAction*) Akcja.
														   @return (int) ID wtyczki
														   */
			#define IMI_ACTION_MAKEPOPUPMENU IMI_BASE+150 /**< Uruchamia i obs�uguje menu utworzone ze wskazanej grupy akcji
														   Komunikat wysy�amy jako (sIMessage_UIMakePopup*)
														   W akcji nale�y poda� identyfikator kontaktu (lub 0) do kt�rego menu ma by� przypisane...
														   */

/** Identyfikacja akcji.
            */
            struct sUIAction {
                unsigned int id;     ///< Identyfikator akcji.
                unsigned int parent; ///< Identyfikator grupy.
                int cnt;    ///< Identyfikator kontaktu dla kt�rego zmieniamy/pobieramy parametry akcji
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
                #define UIAIM_STATUS   1 ///< sUIActionInfo::status i sUIActionInfo::statusMask s� ustawione.
                #define UIAIM_EXSTYLE  2 ///< sUIActionInfo::exStyle i sUIActionInfo::exStyleMas s� ustawione.
                #define UIAIM_P1       4 ///< sUIActionInfo::p1 jest ustawiony.
                #define UIAIM_P2       8 ///< sUIActionInfo::p2 jest ustawiony.
                #define UIAIM_PARAM 0x10 ///< sUIActionInfo::param jest ustawiony.
                #define UIAIM_ICO   UIAIM_P1
                #define UIAIM_TXT  0x40  ///< sUIActionInfo::txt i sUIActionInfo::txtSize s� ustawione.

                #define UIAIM_COL   UIAIM_P1 ///< \blank
                #define UIAIM_POS   0x100  ///< \blank
                #define UIAIM_SIZE  0x200  ///< \blank
                #define UIAIM_HANDLE 0x400  ///< \blank
                #define UIAIM_TYPE  0x800  ///< \blank

				#define UIAIM_VALUE_CONVERT 0x10000 ///< Ustawiona warto�� akcji powinna zosta� przekonwertowana (np. z formatu warto�ci akcji do formatu pola w bazie i na odwr�t)

                #define UIAIM_ALL   0x35F ///< Wszystkie powy�sze.
                
            // uiaim_
            /** @} */


            /** W�a�ciwo�ci akcji.
            \sa #IMI_ACTION_GET #IMI_ACTION_SET
            */
            struct sUIActionInfo {
                unsigned short s_size;
                sUIAction act;  ///< Identyfikatory.
                unsigned int pos;  ///<Pozycja na li�cie w grupie. Pos == -1 oznacza "na ko�cu" (podczas \ref IMI_ACTION "wstawiania").
                                /// \todo Powinien potrafi� r�wnie� zmieni� pozycj�.
                unsigned int type; ///<Typ kontrolki przypisanej do akcji ( \ref actt_ ).
                void * handle;     ///<Uchwyt do kontrolki akcji (np w windowsach uchwyty do HWND lub HMENU)
                void * reserved;
                unsigned int mask;       /**< Maska.
                                    Oznacza kt�re pola w strukturze s�
                                    ustawione.
                                    \attention Pole \a act musi by� \b zawsze ustawione! <br>
                                    \sa \ref uiaim_
                                    */
                unsigned int status;     ///<\ref actm_ "Status".
                unsigned int statusMask; ///<Oznacza kt�re pola w \a status powinny by� zmienione.
                unsigned int exStyle;    /**<Dodatkowe style . \attention W tej chwili nie s� one u�ywane! */
                unsigned int exStyleMask;///<Oznacza kt�re pola w \a exStyle powinny by� zmienione.
                char * txt;     ///< Tekst przypisany do akcji.
                unsigned int    txtSize; ///< Rozmiar bufora w txt.
                int param;      ///<Parametr u�ytkownika.
                int p1;         ///<Dodatkowy parametr uzywany przez typy kontrolek.
                int p2;         ///<Dodatkowy parametr uzywany przez typy kontrolek.
                short w,h; ///< Wysoko�� / szeroko�� kontrolki

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
                W�a�ciwo�ci akcji do konfiguracji.
                */
            struct sUIActionInfo_cfg: sUIActionInfo {
                short x,y; ///< Przesuni�cie wzgl�dem osi x/y
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
            Struktura podstawowa wysy�ana razem z IM_ACTION.

            \sa actn_
            */
            struct sUIActionNotify_base {
                unsigned short s_size;
                sUIAction act;  ///< Identyfikator akcji.
                unsigned int code;  ///< Numer powiadomienia.
                int reserved;   ///< Pozycja zarezerwowana . Musi by� r�wna 0.
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


         /** Struktura do przesy�ania #IMI_ACTION_MAKEPOPUPMENU.*/
            struct sIMessage_UIMakePopup:public sIMessage_base {
                sUIAction _action; ///< Identyfikator akcji-grupy z kt�rej ma by� utworzone menu, razem z identyfikatorem przypisanego do niego kontaktu.
                int _uFlags; ///< Flagi. Atrybut przekazywany do f-cji WinApi - TrackPopupMenu()
				int _x; ///< Pozycja X
				int _y; ///< Pozycja Y
				int _nReserved; ///< Atrybut przekazywany do f-cji WinApi - TrackPopupMenu()
				int _startFrom; ///< Pierwsza akcja (od 0) do uwzgl�dnienia w menu (u�ywane na przyk�ad w tzw. chevronach)
				void * _hWnd; ///< Okno - w�a�ciciel (Aby unikn�� problem�w z ikonkami najlepiej poda� 0 lub uchwyty do okien g��wnego/rozmowy/wi�cej). Atrybut przekazywany do f-cji WinApi - TrackPopupMenu()
				const void * _prcRect; ///< Atrybut przekazywany do f-cji WinApi - TrackPopupMenu()
                sIMessage_UIMakePopup(sUIAction & action , int uFlags, int x, int y, int nReserved, void * hWnd, const void *prcRect = 0 , int startFrom = 0)
					:sIMessage_base(IMI_ACTION_MAKEPOPUPMENU),_action(action),_uFlags(uFlags),_x(x),_y(y),_nReserved(nReserved),_hWnd(hWnd),_prcRect(prcRect),_startFrom(startFrom) 
					{s_size=sizeof(*this);}

            };


        // imi_action_
        /** @} */

        #define IMI_ICONRES    IMI_BASE+109  ///< Wstawia ikonk� z zasob�w wtyczki do listy ikonek UI.
                                                /// \deprecated O wiele lepiej u�ywa� #IMI_ICONREGISTER i funkcji pomocniczych.
                                                /// \param p1 (int) Identyfikator ikonki na li�cie (patrz #UIIcon). 
                                                /// \param p2 (int) Identyfikator ikonki w zasobach wtyczki.
        #define IMI_ICONREGISTER IMI_BASE+130 /**<Rejestruje ikonk�/bitmap� w UI.
                                                @warning Przy zast�powaniu bitmap na listach poprzednie kopie NIE s� usuwane!
                                                   Najlepiej podmienia� ikonki jak najrzadziej si� da... Zostanie to zmienione
                                                   w nast�pnych wersjach...
                                                
                                                @todo Zast�powanie bitmap na listach.
                                                @param p1 (sUIIconRegister*) Informacja o wstawianej ikonce.
                                                @return (bool)

                                               */
        #define IMI_ICONEXISTS IMI_BASE+131 ///< Sprawdza czy ikonka istnieje.
                                             /// @param p1 (int) ID ikonki
                                             /// @param p2 (IML_enum) lista kt�r� sprawdzi�.
                                             /// @return (bool)
        #define IMI_ICONREGISTERLIST IMI_BASE+132 /**< Dodaje ca�y zestaw ikon.
                                                @warning Przy zast�powaniu bitmap na listach poprzednie kopie NIE s� usuwane!
                                                   Najlepiej podmienia� ikonki jak najrzadziej si� da... Zostanie to zmienione
                                                   w nast�pnych wersjach...
                                                @param p1 (sUIIconRegisterList*) Informacja co zarejestrowa�
                                               */
        #define IMI_GETICONINDEX  IMI_BASE+133 ///< Zwraca index ikonki na wybranej li�cie
                                                ///  \param p1 (int) ID ikonki
                                                ///  \param p2 (IML_enum) lista kt�r� sprawdzi�
                                                ///  @return (int) pozycja
        #define IMI_GETICONLIST   IMI_BASE+134 ///< Zwraca uchwyt typu HIMAGELIST do wybranej listy.
                                                ///  @warning Zwr�cona lista jest TYLKO do ODCZYTU! Ka�da modyfikacja dokonana poza UI mo�e powa�nie zak��ci� wy�wietlanie ikon!
                                                ///  @param p1 (IML_enum) lista kt�r� zwr�ci�
                                                ///  @return (HIMAGELIST)
		#define IMI_ICONUNREGISTER IMI_BASE+135 /**< Usuwa ikonk� z wybranej listy...
													@warning Przy usuwaniu z list IML_16 i IML_32 ikony NIE s� usuwane z pami�ci i p�niejsza ich podmiana mo�e wymaga� nawet restartu Konnekta!
													@param p1 (int) ID ikonki
													@param p2 (IML_enum) lista
													@return (bool)
												*/
		#define IMI_ICONGET	    IMI_BASE+136   /**< Zwraca uchwyt ikonki z wybranej listy.
												    @warning Przy pobieraniu z IML_16 i IML_32 s� to nowo utworzone uchwyty i nale�y je ZWOLNI�!
													@param p1 (int) ID ikonki
													@param p2 (IML_enum) lista
													@return (HICON/HBITMAP) uchwyt
												*/
        #define IMI_WARNING     IMI_BASE+200   ///< Wy�wietla okno z ostrze�eniem.
                                                /// \param p1 (char*) tre��.
                                                /// \param p2 (int) dodatkowe flagi, te same co przy MessageBox w WinApi.
                                                /// \return (int) To samo co zwraca MessageBox z WinApi.
        #define IMI_ERROR       IMI_BASE+201  ///< Wy�wietla okno z b��dem.
                                                /// \param p1 (char*) tre��.
                                                /// \param p2 (int) dodatkowe flagi, te same co przy MessageBox w WinApi.
                                                /// \return (int) To samo co zwraca MessageBox z WinApi.
        #define IMI_CONFIRM     IMI_BASE+202  ///< Wy�wietla okno z zapytaniem.
                                                /// \param p1 (char*) tre��.
                                                /// \param p2 (int) dodatkowe flagi, te same co przy MessageBox w WinApi.
                                                /// \return (int) Je�li p2==0 to true/false, lub to samo co zwraca MessageBox z WinApi.
        #define IMI_INFORM      IMI_BASE+204  ///< Wy�wietla okno z informacj�.
                                                /// \param p1 (char*) tre��.
                                                /// \param p2 (int) dodatkowe flagi, te same co przy MessageBox w WinApi.
                                                /// \return (int) To samo co zwraca MessageBox z WinApi.

        struct sIMessage_msgBox: public sIMessage_base {
            const char * msg;
            unsigned int flags;
            const char * title;
            HANDLE parent;  
			sIMessage_msgBox(unsigned int id , const char * msg="" , const char * title=0 , int _flags = 0 , HANDLE parent = 0):sIMessage_base(id , Net::none , imtNone) 
                {this->s_size = sizeof(*this);
                 this->parent = parent;
                 this->msg = msg;
                 this->flags = _flags;
                 this->title = title;
                }
        };


        #define IMI_DLGPASS     IMI_BASE+205  ///< Okienko podawania has�a.
                                                /// \param (sDIALOG_access*) Parametry okna.
                                                /// \param (bool) Gdy == 1 automatycznie do��cza do flag DFLAG_SAVE.
                                                /// \return true/false
        #define IMI_DLGLOGIN    IMI_BASE+206  ///< Okienko podawania loginu i has�a.
                                                /// \param (sDIALOG_access*) Parametry okna.
                                                /// \param (bool) Gdy == 1 automatycznie do��cza do flag DFLAG_SAVE.
                                                /// \return true/false
        #define IMI_DLGSETPASS  IMI_BASE+207  ///< Okienko ustawiania has�a.
                                                /// \param (sDIALOG_access*) Parametry okna.
                                                /// \param (bool) Gdy == 1 automatycznie do��cza do flag DFLAG_SAVE.
                                                /// \return true/false
        #define IMI_DLGENTER    IMI_BASE+208   ///< Okno wprowadzania tekstu
                                                ///  \param p1 (sDIALOG_enter*) Parametry okna.
                                                /// \return true/false
        #define IMI_DLGBUTTONS  IMI_BASE+213  ///< Okno wyboru (ka�da opcja to jeden przycisk).
                                                /// \param p1 (sDIALOG_choose *)
                                                /// \return (int) numer przycisku (1-...) lub 0 gdy �aden nie zosta� wybrany. 
        #define IMI_DLGTOKEN  IMI_BASE+214  ///< Pobieranie tokenu (wpisywanie warto�ci widocznej na obrazku).
                                                /// \param p1 (sDIALOG_token *)
                                                /// \return true/false 

        #define IMI_LONGSTART   IMI_BASE+209   ///< Tworzy okno oczekiwania na zako�czenie d�u�szej operacji.
                                                ///  \param p1 (sDIALOG_long *) Parametry okna. Struktura musi by� zachowana a� do wywo�ania #IMI_LONGEND!
        #define IMI_LONGEND     IMI_BASE+210   ///< Zamyka okno utworzone przez #IMI_LONGSTART.
                                                /// \param p1 (sDIALOG_long *) ta sama struktura u�yta przy #IMI_LONGSTART.
        #define IMI_LONGSET     IMI_BASE+211   ///< Zmienia okno utworzone przez #IMI_LONGSTART.
                                                /// \param p1 (sDIALOG_long *) ta sama struktura u�yta przy #IMI_LONGSTART.
                                                /// \param p2 (int) warto�� (\ref dset_) oznaczaj�ca co ma zosta� zaktualizowane (warto�� musi najpierw zosta� zmieniona w strukturze sDIALOG_long).

        #define IMI_DLGPROFILE  IMI_BASE+212

        /**
        Klasa podstawowa u�ywana przez wszystkie wiadomo�ci obs�uguj�ce
        okna dialogowe... 
        */
        struct sDIALOG {
            unsigned short s_size;
            const char * title; ///< Tytu� okienka.
            const char * info;  ///< Dodatkowa informacja ...
	        int flag;     ///< Flaga D*_
	        void * handle; ///< Uchwyt do okna dialogowego. Przed utworzeniem okna, \a handle trzeba ustawi� na rodzica okna!
            void * param; ///< Parametr uzytkownika
            sDIALOG() {s_size=sizeof(sDIALOG);
                        info=title="";
                        handle=0;
                        param = 0;
				        flag=0;}
        };
        /** Struktura u�ywana przez okno pobierania tokenu.
            
            \attention Wszystkie zwr�cone bufory musz� zosta� od razu skopiowane! */
        struct sDIALOG_token:sDIALOG {
            const char * imageURL; ///< URL do obrazka (@ref sUIIconRegister)
            char * token; ///< Token.
	        sDIALOG_token():sDIALOG() {
				s_size=sizeof(sDIALOG_token);
				imageURL="";
				token = "";
			}
        };

		/** Struktura u�ywana przez okna obs�ugi hase� i login�w.
            
            \attention Wszystkie zwr�cone bufory musz� zosta� od razu skopiowane! */
        struct sDIALOG_access:sDIALOG {
            char * pass; ///< Has�o.
            char * login; ///< Login.
            bool save; ///< Stan checkbox'a "czy zapisywa�".
	        sDIALOG_access():sDIALOG() {s_size=sizeof(sDIALOG_access);pass=login="";save = false;}
        };
        /** Struktura u�ywana przez #IMI_DLGENTER.
            \attention Wszystkie zwr�cone bufory musz� zosta� od razu skopiowane! */
        struct sDIALOG_enter:sDIALOG {
            char * value;  ///< Wprowadzona warto��.
            char * id;     ///< Identyfikator pola tekstowego. 
                            ///  Podanie identyfikatora uaktywni histori� wpis�w.
            int maxLength; ///< Maksymalna d�ugo�� wprowadzonego tekstu.
            sDIALOG_enter():sDIALOG() {s_size=sizeof(sDIALOG_enter);value="";id="";maxLength=0;}
        };
        /** Struktura u�ywana przez #IMI_DLGBUTTONS.
            \attention Wszystkie zwr�cone bufory musz� zosta� od razu skopiowane! */
        struct sDIALOG_choose:sDIALOG {
            char * items; ///<Spis element�w. Elementy rozdzielane s� znakiem '\n'
            int  def;     ///<Domy�lnie zaznaczona opcja (liczone od zera)
            int  width;   ///<Szeroko�� przycisk�w.
            sDIALOG_choose():sDIALOG() {s_size=sizeof(sDIALOG_choose);items="";def=1;width=0;}
        };

        struct sDIALOG_profile:sDIALOG {
            char * profile;
            char * pass;
            bool newOne; 
            sDIALOG_profile():sDIALOG() {s_size=sizeof(sDIALOG_profile);pass=profile="";newOne = false;}
        };
        /** Struktura u�ywana przez #IMI_LONGSTART , #IMI_LONGSET i #IMI_LONGEND.
            */
        struct sDIALOG_long:sDIALOG {
            int progress; ///< Warto�� 'post�pu'. Przy tworzeniu okna oznacza max. warto�� (liczon� od zera) - domy�lnie 100.
            bool cancel;  ///< Czy zosta�o wci�ni�te [Anuluj]?
            int threadId; ///< Id watku, z ktorego tworzone bylo okno
            bool (__stdcall*cancelProc)(sDIALOG_long *); ///< Procedura wywo�ywana po naci�ni�ciu [Anuluj].
            bool (__stdcall*timeoutProc)(int type , sDIALOG_long *); ///< Procedura wywo�ywana aby sprawdzi� czy nast�pi� timeout.
                                                                    /// \param type Rodzaj wywo�ania (Patrz \ref timeoutt_)
                                                                    /// \return 0/1 w zale�no�ci od typu wywo�ania.
                /** @defgroup timeoutt_ Typy dla sDIALOG_long::timeoutProc
                    @{*/
                    #define TIMEOUTT_START 0x10  ///< Dobry moment �eby co� zaalokowa�.
                    #define TIMEOUTT_END   0x11  ///< Dobry moment �eby co� zwolni�.
                    #define TIMEOUTT_CHECK 1     ///< Sprawdzamy stan. Gdy zwr�cimy 1, timeoutPassed zostanie zwi�kszony. A gdy 0, zostanie wyzerowany. 
                                                  ///  Gdy timeoutPassed > timeout, nast�pi przekroczenie limitu czasu i zostanie wywo�any #TIMEOUTT_TIMEOUT.
                    #define TIMEOUTT_TIMEOUT 2   ///< Nast�pi�o przekroczenie czasu, mo�na napisa� co� m�drego.
                /** @} */
            void * timeoutParam;  ///< Parametr do wykorzystania przez timeoutProc.
            int timeout;          ///< Czas po jakim zostanie wys�ane TIMEOUTT_TIMEOUT.
            int timeoutPassed;    ///< Ilo�� ms jaka uplyn�a od pierwszego TIMEOUTT_CHECK==0.
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
                                            ///  Akcja musi do�� cz�sto wywo�ywa� SleepEx(1) aby pozwoli�
                                            ///  na wywo�ywanie f-cji uaktualniaj�cych g��wny w�tek.
                                            ///  \warning Je�eli akcja mo�e blokowa� na d�u�ej koniecznie u�yj OSOBNEGO
                                            ///  w�tku .
            #define DLONG_ANONE  0x100   ///< Bez animacji
            #define DLONG_ARECV  0x200   ///< Animacja "odbieram"
            #define DLONG_ASEND  0x400   ///< Animacja "wysy�am"
            #define DLONG_AINET  0x800   ///< Animacja "komunikacja"

        /** @} */
// -----------------------------------------------------------------------------------------------
        /** @defgroup dset_ Flagi dla IMI_LONGSET.
            @{
        */
            #define DSET_TITLE    0x1    ///< Zosta� zmieniony tytu�.
            #define DSET_INFO     0x2    ///< Zosta�o zmienione info.
            #define DSET_PROGRESS 0x4    ///< Zosta� zmieniony post�p.
            #define DSET_BUTTONS  0x8    ///< Zosta�y zmienione flagi dotycz�ce przycisk�w.
            #define DSET_ANIM     0x10   ///< Zosta�a zmieniona animacja.
        /** @} */
// -----------------------------------------------------------------------------------------------
        /** \defgroup dflag_ Flagi dla sDIALOG.
            \{
        */
            #define DFLAG_SAVE  0x1 ///< W sDIALOG_access zostanie pokazany checkbox 'czy zapisa�'.
            #define DFLAG_PASS2 0x4 ///< W #IMI_DLGSETPASS zostanie sprawdzona zgodno�� obu hase�.
            #define DFLAG_CANCEL 0x8 ///< Przycisk [Anuluj] ma by� widoczny.
        /** @} */

        #define NOTIFY_AUTO    -2              ///< Do ustawienia w #CNT_NOTIFY. 
                                                ///#IMI_NOTIFY znajdzie \a notify wg. kolejki wiadomo�ci.
                                                ///Je�eli zostanie podane jako \a p1 do #IMI_NOTIFY, zostan� sprawdzone wszystkie powiadomienia i ustawione powiadomienie w tray'u.
        #define IMI_NOTIFY      IMI_BASE+1010 ///< Kontakt mo�e mie� nowe powiadomienie. Sprawdzana jest kolejka wiadomo�ci.
                                                ///  \param p1 Numer kontaktu.
        #define IMI_NEWNOTIFY   IMI_BASE+1011 /**< Ustawia nowe powiadomienie dla kontaktu lub u�ytkownika (np nowa wiadomo��).
                                                    \param p1 (sNOTIFY *) powiadomienie. */
        #define IMI_CNT_ACTIVITY  IMI_BASE+1013 ///< Kontakt wykazuje aktywno��.
                                                ///  \param p1 (int) id kontaktu
        #define IMI_CNT_DEACTIVATE  IMI_BASE+1014 ///< Wyzerowanie aktywno�ci kontaktu.
                                                ///  \param p1 (int) id kontaktu
        #define IMI_CNT_DETAILS   IMI_BASE+1015 ///< Otwarcie okna informacji o kontakcie.
                                                ///  \param p1 (int) id kontaktu
        #define IMI_CNT_DETAILS_SUMMARIZE   IMI_BASE+1016 ///< Od�wie�a podsumowanie dla kontaktu w oknie informacji (tylko gdy jest otwarte)
                                                ///  @param p1 (int) id kontaktu
        #define IMI_CNT_ISCOMPOSING   IMI_BASE+1020 ///< Czy u�yrkownik pisze co� do podanego kontaktu?
													/// @param p1 (int) id kontaktu
        /**
            Struktura przesy�ana w #IMI_NEWNOTIFY
        */
        struct sNOTIFY {
            unsigned short s_size;
            int cnt;    ///< ID kontaktu kt�rego notify dotyczy.
            sUIAction action;  ///< Akcja kt�ra ma by� wywo�ana.
            int notify; ///< Ikona powiadomienia #UIIcon.
            char * info; ///< Informacja.
            int flag; ///< Flaga (w tej chwili flag nie ma :).
            #define NOTIFY_IMPORTANT 1
            /** Wype�nia struktur� dla kontaktu na li�cie.
                \param _action Identyfikator akcji.
                \param _notify Identyfikator ikonki powiadomienia.
                \param _cnt Pozycja kontaktu.
            */
            sNOTIFY(sUIAction _action , int _notify , int _cnt = -1) {s_size=sizeof(sNOTIFY);cnt = _cnt; action = _action; notify = _notify;info = (char*)-1;}
            /** Wype�nia struktur� dla u�ytkownika.
                \param _action Identyfikator akcji.
                \param _notify Identyfikator ikonki powiadomienia.
                \param _info Tekst powiadomienia (pokazywany w Tray'u). Mo�e przyj�� warto�ci:
                    - adres do ci�gu znak�w z tekstem.
                    - 0 - tekst nie zostanie zmieniony.
                    - -1 - tekst zostanie zmieniony na domy�lny.
            */
            sNOTIFY(sUIAction _action , int _notify , char * _info = 0) {s_size=sizeof(sNOTIFY);cnt = -1; action = _action; notify = _notify;info = _info;}
        };

        #define IMI_REFRESH_CNT IMI_BASE+2000 ///< UI powinien od�wie�y� kontakt.
                                                /// Wysy�ane po zmianie statusu kontaktu, lub kt�rej� z informacji tekstowych.
                                                /// \param p1 (int) ID kontaktu
                                                /// \param p2 (bool) je�li true - dane zostan� od�wie�one r�wnie� w oknie z informacjami o kontakcie!
        #define IMI_REFRESH_LST IMI_BASE+2001 /**< Ca�a lista kontakt�w powinna by� od�wie�ona.
                                                 \param p1 (bool) Czy lista ma zosta� od nowa wype�niona (raczej nie u�ywane)?
                                                 \attention Ten komunikat powinien by� u�ywany TYLKO po dokonaniu du�ych zmian na li�cie kontakt�w 
                                                  (bez wywo�ywania #IMI_REFRESH_CNT).
												  */
        #define IMI_CONFIG      IMI_BASE+2010 /**< Otwiera konfiguracj�.
                                                 \param p1 (int) ID grupy na kt�rej ma zosta� otwarte.
												 */
        #define IMI_CONFIGOPENED IMI_BASE+2011 ///< Zwraca true je�li konfiguracja jest otwarta.

        #define IMI_LST_SELCOUNT IMI_BASE+2020 ///< Zwraca ile kontakt�w jest zaznaczonych na li�cie.
        #define IMI_LST_GETSELPOS  IMI_BASE+2021   ///< Zwraca ID zaznaczonego kontaktu.
                                                    ///  \param p1 (int) numer zaznaczenia poczynaj�c od 0 do #IMI_LST_SELCOUNT.
        /*
        #define IMI_MSG_INFO    IMI_BASE+3000  //
           #define IMI_MSG_INFO_undelivered 0
           #define IMI_MSG_INFO_delivered 1
        */
        #define IMI_MSG_OPEN    IMI_BASE+3001  // (cMessage*)    internal usage
        #define IMI_MSG_NOTINLIST IMI_BASE+3002 // (cMessage *)  internal usage
        #define IMI_MSG_WINDOWSTATE IMI_BASE+3003 ///< Zwraca stan okna wiadomo�ci dla kontaktu.
                                                    ///  \p1 Numer kontaktu.
                                                    ///  \return 0 - okno zamkni�te.
                                                    ///  \return 1 - okno otwarte , aktywne.
                                                    ///  \return -1 - okno otwarte , nieaktywne.
                                                    ///  \return -2 - okno zminimalizowane.
/** Zwraca adres do procedury okna wpisywania wiadomo�ci.
Procedura daje obs�ug� skr�t�w wysy�ania (Ctrl+enter, Alt+s), wykrywanie
pisania i histori� ostatnio wpisanych wiadomo�ci...
Obs�uguje komunikaty WM_KEYDOWN i WM_SYSKEYDOWN
*/
		#define IMI_MSG_EDITCTRL_WNDPROC IMI_BASE+3005  
                                                /// \param p1 (sHISTORYADD*)
        #define IMI_HISTORY_ADD IMI_BASE+3004  ///< Dodaje wpis do historii
                                                /// \param p1 (sHISTORYADD*)
		/** Struktura u�ywana przez #IMI_HISTORY_ADD. */
        struct sHISTORYADD {
            unsigned short s_size;
            struct cMessage * m; ///< Wiadomo�� do dodania
            const char * dir; ///< podkatalog w "history/"
            unsigned int cnt; ///< Identyfikator kontaktu je�li ma by� automatycznie utworzona nazwa
            const char * name; ///< Nazwa pliku (je�li cnt==0)
            int session; ///< Oznaczenie sesji.
                        ///  0 - osobna wiadomo��, lub pocz�tek sesji
                        ///  1 - wiadomo�� nale�y do sesji
            sHISTORYADD():s_size(sizeof(sHISTORYADD)) {m=0;dir="";cnt=0;name=0;session=0;}
        };
        #define IMI_CNT_SEARCH_FOUND IMI_BASE+4000  ///< Dodaje kontakt do listy znalezionych w odpowiedzi na wyszukiwanie.
                                                    /// \param p1 (sCNTSEARCH*) Informacje o kontakcie.

  /** @} */  // do UI.dll
  /** @} */  // IMESSAGE
// -----------------------------------------------------------------------------------------------
  /**
    \defgroup imerror_ Kody b�edu
    \brief \no

    \{
  */

  #define IMERROR_NORESULT 1   ///< Wtyczka nie obs�u�y�a wiadomo�ci.
  #define IMERROR_UNSUPPORTEDMSG IMERROR_NORESULT /// \no
  #define IMERROR_BADSENDER 2  ///< Wiadomo�� wstrzymana, pojawi� si� b��d...
  #define IMERROR_BADPLUG 3    ///< Podana wtyczka nie istnieje.
  #define IMERROR_THREADSAFE 4 ///< Wiadomo�� zosta�a wywo�ana w trybie bezpiecznym (bez oczekiwania na powr�t).
  #define IMERROR_SHUTDOWN 5   ///< Wiadomo�� zosta�a anulowana z powodu zamykania programu.
  #define IMERROR_BADPARAM 6   ///< Nieprawid�owe parametry.
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
        #define IMIG_MAINWND       1   ///< G��wne okno
        #define IMIG_BAR           2   ///< Belka glowna
        #define IMIG_MSGWND        3   ///< Okno wysy�ania wiadomo�ci
        #define IMIG_MSGBAR        4   ///< Belka w wysy�aniu wiadomo�ci
        #define IMIG_MAINTB        8   ///< G��wny toolbar
        #define IMIG_SHORTCUTTB    9   ///< Toolbar ze skr�tami
        #define IMIG_MAIN          10  ///< G��wne Menu
        #define IMIG_MAIN_OPTIONS  11  ///< Menu opcji
        #define IMIG_MAIN_CNT   12     ///< Dodaj kontakt
        #define IMIG_MAIN_PROFILE  13  ///< Profile
        #define IMIG_HISTORYWND    14
		#define IMIG_PLUGINS       15  /**< Grupa dla ikonek wtyczek w g��wnym oknie... U�ytkownik mo�e wybra�
										inn�, wi�c numer aktualnej grupy nale�y pobra� przez #IMI_GETPLUGINSGROUP.
									
										*/
        #define IMIG_STATUS          50  ///< Toolbar ze statusami
        #define IMIG_EVENT           51  ///< Menu z wiadomo�ciami od serwer�w.
        #define IMIG_EVENT_PARENT    IMIG_STATUS
        #define IMIG_HIDDEN          60  

        #define IMIG_TRAY          20  ///< Tray
        #define IMIG_CNT           30  ///< Menu kontaktu
        #define IMIG_CFGWND        40  ///< Okno ustawie�.
        #define IMIG_CFG           41  ///< Korze� drzewka ustawie�.
        #define IMIG_CFG_CONNECTION 42 ///< Opcje po��cze�.
        #define IMIG_CFG_USER      43  ///< Ustawienia u�ytkownika.
        #define IMIG_CFG_SETTINGS  44  ///< Ustawienia programu.
        #define IMIG_CFG_UI        45  ///< Ustawienia interfejsu.
        #define IMIG_CFG_PLUGS     46  ///< Ustawienia wtyczek.

        #define IMIG_NFOWND        70  ///< Okno informacji o kontakcie
        #define IMIG_NFO           71   ///< Drzewko kontrolek informacji
        #define IMIG_NFO_BAR       72   ///< Belka w oknie informacji o kontakcie
        #define IMIG_NFO_TB        73   ///< G��wny toolbar w oknie informacji o kontakcie
  /** @} */ // imig_

// ------------------------------------------------------------------------------------------------
  /**
    \defgroup st_ Numery status�w
        Status sk�ada si� z rodzaju statusu (0-0xFF) i flag (0x001-0xFFFFFF00).

    \{
  */

        // STATUS
        /** 
        */
        typedef unsigned int tStatus;
        #define ST_OFFLINE  0  ///< Niedost�pny.
        #define ST_BLOCKING 1 ///< Blokuj�cy (GG)

#define ST_SEMIONLINE 0x20 ///< Od tej granicy zaczynaj� si� "mniejsze" online'y
        #define ST_NA     0x21       ///< Bardzo away (not-available).
        #define ST_DND    0x22      ///< Nie przeszkadza�.
        #define ST_OCCUPIED 0x22     ///< Zaj�ty (ICQ)

        #define ST_ONLINE 0x40   ///< Dost�pny.
        #define ST_AWAY   0x41     ///< Away.
        #define ST_AUTOAWAY   0x44     ///< Automatyczny away.
        #define ST_HIDDEN 0x42   ///< Ukryty.
        #define ST_CHAT 0x43  ///< FreeForChat (ICQ)

#define ST_SPECIAL 0x60 ///< Od tej granicy zaczynaj� si� statusy specjalne...

        #define ST_CONNECTING 0xF1  ///< W trakcie ��czenia, tylko dla kontaktu u�ytkownika.

        // flagi
        #define ST_NOTINLIST 0x100 ///< Chwilowo na li�cie, zostanie usuni�ty po zamkni�ciu programu.
        #define ST_HIDESHISSTATUS 0x200 ///< Kontakt nie podaje nam swojego statusu
        #define ST_IGNORED 0x400        ///< Ignorowany
        #define ST_COMPOSING 0x800  ///< Kontakt pisze do nas wiadomo��
        #define ST_HIDEMYSTATUS 0x1000  ///< Ukrywanie statusu przed kontaktem
		#define ST_HIDEBOTH (ST_HIDEMYSTATUS | ST_HIDESHISSTATUS)

        // maski
        #define ST_MASK        0xFF  ///< Maska statusu.

  /** @} */ // st_
// ------------------------------------------------------------------------------------------------
  /** @defgroup gr_msg Obs�uga wiadomo�ci tekstowych.
      @brief @no
      @{
      */

        #define EXT_PARAM "\x1A" /**< Znak parametru.
                    W cMessage i cMessageAck mo�emy podawa� list� dodatkowych parametr�w.
                    Ka�dy parametr sk�ada si� z po��czonych: #EXT_PARAM nazwy '=' warto�ci
                    Dzi�ki zastosowaniu "nietypowego znaku, unikamy potrzeby escape'owania znak�w.
                    Nazwa mo�e by� dowolnym ci�giem znak�w z wyj�tkiem znak�w #EXT_PARAM, '=' i \0.
                    Warto�� mo�e by� dowolnym ci�giem znak�w z wyj�tkiem znak�w #EXT_PARAM i \0.
                    Nazwa jest case-sensitive.

                    Najlepiej u�ywa� gotowych f-cji zadeklarowanych w plug_func.h:
                    GetExtParam i SetExtParam .
                    */
        #define EXT_PARAM_CHAR char(0x1A)
        /**
        Struktura do przekazywania wiadomo�ci tekstowych .
        \attention Zawarto�� struktury jest tylko tymczasow� \i kopi� wiadomo�ci z \i kolejki.
        \sa \ref msg
        */
        struct cMessage{
            unsigned short s_size;
            unsigned int id;              /**< Identyfikator wiadomo�ci.
                                    \attention ustawiany przez "rdze�". */
            unsigned int net;             /**< Sie� wtyczek do kt�rych skierowana jest wiadomo��.
                                    \sa net_ */
            unsigned int type;            /**< Typ wiadomo�ci.
                                    \sa mt_ */
            char * fromUid;      ///< UID odbiorcy.
            char * toUid;        ///< UID nadawcy.
            char * body;         ///< Tre�� wiadomo�ci.
            char * ext;          ///< Informacje rozszerzone.
                                  /**  Zapisane jako 
                                        \code 
                                        #EXT_PARAM nazwa=warto�� #EXT_PARAM nazwa2=warto��2
                                        ...
                                        \endcode
                                        patrz: #EXT_PARAM .
                                  */
            unsigned int flag;            ///< Flaga.
                                    ///< \sa mf_
            struct sUIAction action;    ///< Akcja powiadomienia dla wiadomo�ci.
            unsigned int notify;          ///< Akcja i ikonka powiadomienia dla wiadomo�ci.
                                ///< \sa \ref action \ref msg
            __int64 time;        ///< czas odebrania wiadomo�ci w formacie zgodnym z cTime64 (zapisane jako __int64).

            cMessage() {s_size=sizeof(cMessage);id=net=type=flag=notify=0; action = sUIAction(0,0); fromUid=toUid=body=ext="";time=0;}
        };
        /**
        Struktura do przekazywania informacji o stanie przesy�anych wiadomo�ci.
        Mo�na ni� podawa� jakie wyst�pi�y problemy, lub co sta�o si� z wiadomo�ci�
        po wys�aniu (np. czeka na serwerze, lub dosz�a do odbiorcy...)
        \attention \a id \b musi by� ustawiony na numer potwierdzanej i \b istniej�cej wiadomo�ci.
        W mi�dzyczasie wiadomo�� ta nie mo�e by� usuni�ta przez inny w�tek.

        \sa \ref msg
        */
        struct cMessageAck {
            unsigned short s_size;
            unsigned int id;   /**< Identyfikator wiadomo�ci kt�r� potwierdzamy.
                                    */
            char * msg; /**< Tekst potwierdzenia. */
            char * ext; /**< Dodatkowe parametry. */
            unsigned int flag; ///< Flagi \ref mack_.
            cMessageAck() {s_size=sizeof(cMessageAck);}

        };

    /**  
        \defgroup mt_ Typy wiadomo�ci tekstowych
		Do typu wiadomo�ci mo�na doda� bit #MT_MASK_NOTONLIST oznaczaj�c tym samym, 
		�e wiadomo�� nie jest zwi�zana z list� kontakt�w.
		Cz�� typ�w ma ten bit ustawiony domy�lnie...
        \{
    */
            typedef unsigned int tMsgType;
            #define MT_MESSAGE      1    ///< Zwyk�a wiadomo��.
            #define MT_QUICKEVENT   2    ///< Kr�tka notka (kasowana automatycznie w kolejce) (np. wiadomo�� nie dosz�a itp.)
            #define MT_CNTEVENT     3    ///< wydarzenie (np. kto� mnie doda� do swojej listy itp.) zwi�zane z kontaktem na li�cie
            #define MT_EVENT        (MT_CNTEVENT|MT_MASK_NOTONLIST)    ///< wydarzenie (np. kto� mnie doda� do swojej listy itp.)
            #define MT_SERVEREVENT  (4|MT_MASK_NOTONLIST)    ///< Wiadomo�� od serwera.
            #define MT_AUTHORIZE    5    ///< Pro�ba o autoryzacje (ICQ).
            #define MT_CONFERENCE   6    ///< Wiadomo�� konferencyjna.
            #define MT_FILE         7 ///< Przes�anie pliku.
            #define MT_MAIL         8 ///< Email.
            #define MT_SMS          9 ///< Np. potwierdzenie dotarcia sms'�w.
            #define MT_SOUND        10 ///< Rozmowa g�osowa.
            #define MT_URL         (11|MT_MASK_NOTONLIST)    ///< URL. 
                                                                /// Jako dodatkowe parametry w ext przyjmuje Width i Heigth
            #define MT_SPECIAL      12 ///< Nieokreslona wiadomosc.
            #define MT_SPECIAL_NOL (13|MT_MASK_NOTONLIST) ///< Nieokreslona wiadomosc spoza listy.
			#define MT_IMAGE		15 ///< Obraz, sciezka do pliku w cMessage::ext - #MEX_FILE_PATH

			#define MT_BOARD        16 ///< 

            #define MT_MASK_NOTONLIST 0x1000  ///< Oznacza �e ta wiadomosc nie zostanie
                                            ///  wy�wietlona na liscie, ani nie zostanie
                                            ///  sprawdzone czy docelowy kontakt na li�cie
                                            ///  si� znajduje
			#define MT_MASK 0xFFF ///< Maskuje bity odpowiedzialne za sam typ wiadomo�ci.
    /** @} */ // mt_
    // ------------------------------------------------------------------------------------------------
    /**
        \defgroup mf_ flagi wiadomo�ci tekstowych
        \brief \no
        @{
    */
            #define MF_SEND         2 ///< Wiadomo�� przeznaczona do wys�ania
            #define MF_NOEVENTS     4 ///< #MT_QUICKEVENT maj� nie by� wysy�ane
            #define MF_NOSAVE       8 ///< Wiadomo�� nie zostanie zapisana na dysk ...
            #define MF_REQUESTOPEN  0x10 ///< \brief #IM_MSG_OPEN / #IM_MSG_SEND zostanie wys�ane z #IMC_MESSSAGEQUEUE tylko
                                        ///  gdy zostanie ono wywo�ane dla tego typu i sieci wiadomo�ci.
            #define MF_PROCESSING   0x20 ///< Flaga wewn�trzna oznaczaj�ca �e wiadomo�� jest w trakcie przetwarzania, Nie powinna by� u�ywana!
            #define MF_OPENED       0x40   ///< Wiadomo�� ju� zosta�a otwarta. Teraz czeka w kolejce na usuni�cie.
                                            ///  Flaga ta jest czyszczona podczas zamykania. 
            #define MF_HANDLEDBYUI  0x80 ///< Wiadomo�� zostanie obs�u�ona przez UI
            #define MF_AUTOMATED    0x100   ///< Wiadomo�� zosta�a stworzona przez jaki� "automatyczny"
                                            /// proces, wi�c, gdy jeste�my ukryci, nie powinna by�
                                            /// wysy�ana.
            #define MF_HTML    0x200     ///< Tre�� wiadomo�ci zawiera znaczniki HTML, a znaki specjalne s� kodowane (przynajmniej > = &gt; < = &lt; i " = &quot;
										 ///  Html powinien by� sformatowany jak XHTML (<img/>, wszystkie atrybuty w "" itd..)
			#define MF_MENUBYUI     0x400 /**< Interfejs obs�u�y wy�wietlanie wiadomo�ci w menu.
											Za ikonk� pos�u�y cMessage::notify, nazw� pozycji w menu ustawiamy
											w Ext jako parametr "ActionTitle". Je�eli ustawiona jest cMessage::action
											zostanie ona wys�ana po otwarciu wiadomo�ci. W przeciwnym razie zostanie
											wywo�ane IM_MSG_OPEN.
											Wtyczka musi w #IM_MSG_RCV zadeklarowa� obs�ug� wiadomo�ci.
										  */
			#define MF_LEAVEASIS 0x800 /**< Zabrania wtyczkom zmiany tre�ci, w tym wy�wietlania emotikon */
			#define MF_HIDE 0x1000 /**< Nie wy�wietla wiadomo�ci w interfejsie (w tej chwili w oknie rozmowy) */
			#define MF_DONTADDTOHISTORY 0x2000 /**< Nie zapisuje w historii */

            #define MF_QE_NORMAL    0x10000 ///< MT_QUICKEVENT narysuje zwyk�� czcionk�...
            #define MF_QE_SHOWTIME  0x20000 ///< MT_QUICKEVENT poka�e czas nadej�cia...

            
    /** @} */ // mf_
    /**
        \defgroup mex_ Nazwy warto�ci w polach cMessage::ext
        \brief \no
        @{
    */
            #define MEX_ADDINFO "AddInfo"
            #define MEX_DISPLAY "Display"
			#define MEX_TITLE   "Title"
			#define MEX_NOSOUND "NoSound" ///< Nie zostanie odegrany d�wi�k
			#define MEX_FILE_PATH "FilePath"
			#define MEX_FILE_SIZE "FileSize"
			#define MEX_FILE_TRANSFER_TIME "FileTransferTime"
			#define MEX_FILE_TRANSFERED "FileTransfered"
            #define MEX_FILE_ERROR "FileError"

            
    /** @} */ // mf_
    /**
        \defgroup mack_ Flagi potwierdze� wiadomo�ci (#IMC_MESSAGEACK i #IM_MSG_ACK)
        \brief \no
        \{
    */
            #define MACK_FAILED  0x1 ///< Wyst�pi� b��d
            #define MACK_PROCESSING 0x2 ///< W trakcie przetwarzania

            #define MACK_NOBROADCAST 0x100 /**< Ack nie zostanie rozes�ane do wtyczek #IMT_MESSAGEACK.
                                                 Przydatne, je�li chcemy tylko zmieni� informacj� pokazywan� w oknie
                                                 kolejki.
                                                 */

            #define MACK_IMPORTANT 0x10 ///< Komunikat jest istotny, b�dzie pokazywany d�u�ej
            #define MACK_VERYIMPORTANT 0x20 ///< Komunikat jest bardzo istotny.
    /** @} */ // mack_

/** @} */
/** @addtogroup imc_ 
    @{*/
    /** Struktura wykorzystywana przez #IMC_MESSAGENOTIFY.
        Podajemy w niej net i uid kontaktu i otrzymujemy action i notify s�u��ce
        do otwarcia tego typu wiadomo�ci. Struktura jest przede wszystkim 
        wykorzystywana przez UI do pokazywania odpowiednich ikonek przychodz�cych wiadomo�ci.*/ 
    struct sMESSAGENOTIFY {
        unsigned short s_size;
        int net;       ///< Sie� kontaktu.
        char * uid;   ///< UID kontaktu.
        sUIAction action;  ///< Akcja otwieraj�ca wiadomo��.
        int notify;       ///< Ikonka wiadomo�ci.
        unsigned int id; ///< Identyfikator wiadomo�ci.
        sMESSAGENOTIFY() {s_size=sizeof(sMESSAGENOTIFY);id = 0;}
    };

/**@}*/

//-------------------------------------------------------------------------------------------------
  /**
    \defgroup gr_cfg Kolumny konfiguracji
    Zanim zaczniemy korzysta� z tablic konfiguracji trzeba zarejestrowa� typy kolumn
    wysy�aj�c sIMessage_setColumn w odpowiedzi na #IM_SETCOLS.

    Odczyt i zapis odbywa si� poprzez makra zdefiniowane w \ref gr_cfg.
    Dodatkowo rdze�, UI i wtyczki maj� zadeklarowane swoje kolumny.

    Kolumny typu #DT_CT_PCHAR zazwyczaj maj� te� flag� #DT_CF_CXOR.

    \{
  */
//-------------------------------------------------------------------------------------------------


        /**
            \defgroup msg_ tabela wiadomo�ci tekstowych
            W tej chwili nie ma bezpo�redniego dost�pu do tablicy wiadomo�ci!

            \{
        */
            // Msg
            #define MSG_ID             ((unsigned int)0) ///< #DT_CT_INT ID.
            #define MSG_NET            1 ///< #DT_CT_INT Sie�.
            #define MSG_TYPE           2 ///< #DT_CT_INT Typ.
            #define MSG_FROMUID        3 ///< #DT_CT_PCHAR Od UIDa (odebrana).
            #define MSG_TOUID          4 ///< #DT_CT_PCHAR Do UIDa (wysy�ana).
            #define MSG_BODY           5 ///< #DT_CT_PCHAR Tre��.
            #define MSG_EXT            6 ///< #DT_CT_PCHAR Dodatkowe informacje.
            #define MSG_FLAG           7 ///< #DT_CT_INT Flaga.
            #define MSG_ACTIONP        8 ///< #DT_CT_INT | #DT_CF_NOSAVE  Grupa akcji.
            #define MSG_ACTIONI        12 ///< #DT_CT_INT | #DT_CF_NOSAVE Akcja.
            #define MSG_NOTIFY         9 ///< #DT_CT_INT | #DT_CF_NOSAVE  Ikonka powiadomienia.
            #define MSG_HANDLER        10 ///< #DT_CT_INT | #DT_CF_NOSAVE Wtyczka obs�uguj�ca.
            #define MSG_TIME           11 ///< #DT_CT_64 Czas jako cTime64 Czas odebrania/wys�ania.

//            #define C_MSG_COLCOUNT     13 // ostatni

        /**
            @}
            @defgroup cfg_ tabela Konfiguracji
            \brief \no
            Niekt�re kolumny s� w tej chwili nie u�ywane (by�y w poprzednich wersjach)...
            Nied�ugo najprawdopodobniej zostan� wykorzystane.
            @{
        */
            // Cfg - CORE'a
            #define CFG_0              ((int)0) ///< nieu�ywany.
            #define CFG_VERSIONS       1 ///< Wersje ostatnio u�ywanych plugin�w.
            #define CFG_APPFILE        2 ///< #DT_CT_PCHAR | #DT_CF_NOSAVE �cie�ka do pliku konnekt.exe.
            #define CFG_APPDIR         3 ///< #DT_CT_PCHAR | #DT_CF_NOSAVE �cie�ka do katalogu z programem.
            #define CFG_PROXY          4 ///< #DT_CT_INT Czy proxy ma by� u�ywane?
            #define CFG_PROXY_AUTO     15 ///< #DT_CT_INT Pobieranie ustawie� z IE
            #define CFG_PROXY_VERSION  5 ///< #DT_CT_PCHAR Rodzaj proxy (w tej chwili tylko "")
            #define CFG_PROXY_AUTH     6 ///< #DT_CT_INT Czy u�ywa� logowania?
            #define CFG_PROXY_LOGIN    7 ///< #DT_CT_PCHAR Login do proxy.
            #define CFG_PROXY_PASS     8 ///< #DT_CT_PCHAR Has�o do proxy.
            #define CFG_PROXY_HOST     9 ///< #DT_CT_PCHAR Adres proxy.
            #define CFG_PROXY_PORT     10 ///< #DT_CT_INT  Port proxy.
            #define CFG_PROXY_HTTP_ONLY 21 ///< #DT_CT_INT Proxy tylko dla http.
            #define CFG_AUTO_CONNECT   11 ///< #DT_CT_INT  ��czenie automatyczne.
            #define CFG_12             12 ///< nieu�ywany
            #define CFG_13             13 ///< nieu�ywany
            #define CFG_14             14 ///< nieu�ywany
            #define CFG_IGNORE         16 ///< #DT_CT_PCHAR Lista ignorowanych.
            #define CFG_GROUPS         17 ///< #DT_CT_PCHAR Lista grup kontakt�w.
            #define CFG_CURGROUP       18 ///< #DT_CT_PCHAR Aktualna grupa kontakt�w.
            #define CFG_DIALUP         19 ///< #DT_CT_INT Po��czenie przez modem
            #define CFG_RETRY          20 ///< #DT_CT_INT Wznawianie po��cze�
            #define CFG_LOGHISTORY     22 ///< #DT_CT_INT Zapisywanie historii
			#define CFG_TIMEOUT_RETRY  23
			#define CFG_TIMEOUT		   24
			#define CFG_SHOWBITS       25 /**< #DT_CT_INT Okre�la jak ma by� budowany interfejs. 
						Na przyk�ad kt�re elementy powinny by� ukryte, a kt�re w��czone.
						Do obs�ugi u�ywamy tylko i wy��cznie funkcji w Konnekt::ShowBits !
						*/
			#define CFG_SHOWBITS_BYHAND 26 /**< #DT_CT_INT Okre�la kt�re bity w CFG_SHOWBITS by�y ustawiane r�cznie.

            //#define C_CFG_COLCOUNT     26// ostatni
        /**
            @}

            @defgroup cnt_ tabela Kontakt�w
            \brief \no

            @{
        */
        // Cnt
            #define CNT_UID            ((unsigned int)0) ///< #DT_CT_PCHAR UID.
            #define CNT_NET            1 ///< #DT_CT_INT Sie�.
            #define CNT_STATUS         2 ///< #DT_CT_INT Status.
            #define CNT_STATUSINFO     18 ///< #DT_CT_PCHAR Opis statusu.
            #define CNT_NOTIFY         3 ///< #DT_CT_INT | #DT_CF_NOSAVE Ikonka powiadomienia.
            #define CNT_HOST           4 ///< #DT_CT_PCHAR | #DT_CF_NOSAVE IP.
            #define CNT_PORT           5 ///< #DT_CT_INT | #DT_CF_NOSAVE Port.
            #define CNT_NAME           6 ///< #DT_CT_PCHAR Imi�.
            #define CNT_SURNAME        7 ///< #DT_CT_PCHAR Nazwisko.
            #define CNT_NICK           17 ///< #DT_CT_PCHAR Pseudo.
            #define CNT_DISPLAY        8 ///< #DT_CT_PCHAR Nazwa wy�wietlana.
            #define CNT_CELLPHONE      9 ///< #DT_CT_PCHAR Kom�rka.
            #define CNT_PHONE          10 ///< #DT_CT_PCHAR Stacjonarny.
            #define CNT_EMAIL          11 ///< #DT_CT_PCHAR Email.
            #define CNT_INFO           12 ///< #DT_CT_PCHAR Info.
            #define CNT_LOCALITY       13 ///< #DT_CT_PCHAR Miejscowo��.
            #define CNT_CITY	       CNT_LOCALITY
            #define CNT_COUNTRY        14 ///< #DT_CT_PCHAR Kraj
            #define CNT_BORN           19 ///< #DT_CT_INT Urodzony YYYYMMDD (w hexie)
            #define CNT_GENDER         20 ///< #DT_CT_INT P�e� \ref gender_
            #define CNT_CLIENT         15 ///< #DT_CT_PCHAR Nazwa i wersja u�ywanego softu.
            #define CNT_CLIENTVERSION  28 ///< #DT_CT_INT Wersja Softu
            #define CNT_LASTMSG        16 ///< #DT_CT_INT | #DT_CF_NOSAVE ID ostatniej wiadomo�ci.
            #define CNT_GROUP          21 ///< #DT_CT_PCHAR Grupa do kt�rej nale�y.
            #define CNT_ACT_PARENT     22 ///< #DT_CT_INT | #DT_CF_NOSAVE Parent akcji powiadomienia.
            #define CNT_ACT_ID         23 ///< #DT_CT_INT | #DT_CF_NOSAVE ID akcji powiadomienia.
            #define CNT_INTERNAL       24 // Dla rdzenia.
            #define CNT_STREET         25 ///< #DT_CT_PCHAR - ulica.
            #define CNT_POSTALCODE     26 ///< #DT_CT_PCHAR - kod pocztowy.
            #define CNT_NOTIFY_MSG     27 ///< #DT_CT_INT | #DT_CF_NOSAVE ID wiadomo�ci powiadomienia.
            #define CNT_LASTACTIVITY   29 ///< #DT_CT_64 Czas ostatniej aktywno�ci.
            #define CNT_STATUS_ICON    30 ///< #DT_CT_INT Identyfikator ikonki, kt�ra ma zast�pi� ikon� statusu.



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
    /** @defgroup gender_ Oznaczenie p�ci
        @{ */
        #define GENDER_UNKNOWN 0 ///< Nieznana
        #define GENDER_FEMALE  1 ///< Kobieta
        #define GENDER_MALE    2 ///< M�czyzna
    /** @} */

// gr_shared
/** @} */



#include "core_ctrl.h"

#include "obsolete_defines.h"


 #pragma pack(pop)

#endif
