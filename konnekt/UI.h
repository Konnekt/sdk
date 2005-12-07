/*
  nazwa="UI shared"
  data="2002-10-31"
  ver="0.6.15.x"
  info="nag��wek potrzebny przy korzystaniu z interfejsu dla Windowsa"
*/
/** \file
    Deklaracje do korzystania z \ref ui "UI" (interfejsu u�ytkownika)
*/
#ifndef UISHAREDH
#define UISHAREDH

#define KONNEKT_SDKUI_V 1 ///< Wersja SDK_UI

#define HISTORY_IGNORED_DIR "deleted"
#define HISTORY_IGNORED_NAME "ignorowani"

#define ID_TRAY 1000
namespace Konnekt {
	namespace UI {
	};
};

/** @defgroup gr_icon Ikonki w UI.
    \brief \no
    @{
    */

    /** Makro tworz�ce identyfikator ikonki.
        Identyfikatory zwracane przez #UIIcon u�ywane s� przez interfejs do pokazywania
        status�w sieci, ikonek powiadomie� o wiadomo�ciach itp.
        Zwyczajne ikony powinny mie� identyfikatory od 1 do 0x00FFFFFF.
        \param type Typ ikonki (IT_*)
        \param net Sie� wtyczek (0-255)
        \param id Identyfikator (0-255)
        \param frame Klatka - zazwyczaj 0.
    */
//    #define UIIcon(type,net,id,frame) (((char)(frame)) | (((char)(id))<<8) | (((char)(net))<<16) | (((char)(type))<<24))
    #define UIIcon(type,net,id,frame) (((frame)&0xF) | (((id)&0xFFFF)<<4) | (((net)&0xFF)<<20) | (((type)&0xF)<<28))
    // typ - 4b | net - 8b | id - 16b | frame - 4b 
#define UIIcon_type(id) ((id)>>28)
/*  #define UINotify(n,i) ((BYTE)(i) | (((BYTE)n)<<8)
    #define UINotify_net(i) i>>16
    #define UINotify_id(i) i & 0xFFFF
    #define UIIcon_Notify(i,f) (f | ((i)<<8) | 0x5000000)
*/
    #define ICON_BLANK 0xF
    #define ISICON_BLANK(id) ((!id)||((id)&IT_BLANK_MASK))

    #define IT_LOGO     2 ///< Logo sieci (\a i = 0)
    #define IT_OVERLAY  3 ///< Nak�adka na status na li�cie kontakt�w (\a n=0, \a f=0, \a i=OVR_*)
    #define IT_STATUS   4 ///< Status kontaktu (\a i=status).
    #define IT_MESSAGE  5 ///< Ikonka wiadomo�ci (\a i = typ wiadomo�ci \ref mt_)
    #define IT_BLANK_MASK 0x80000000


    #define OVR_NETLOGO 0 ///< Ikonka sieci.
    #define OVR_MAIL    1 ///< Symbol emaila.
    #define OVR_SMS     2 ///< Symbol kom�rki.
    #define OVR_NOTINLIST  3 ///< Spoza listy.
    #define OVR_IGNORE    4  ///< Ignorowany.
    #define OVR_HIDEBOTHSTATUS    5 ///< Ukrywany statusy (oba).
    #define OVR_ACTIVE    6 ///< Aktywny.
    #define OVR_INFO    7 ///< Opis statusu.
    #define OVR_HIDEMYSTATUS    8 ///< Ukrywany nasz status.
    #define OVR_HIDESHISSTATUS    9 ///< Kontakt ukrywa sw�j status.

	#define ICON_POINT	  3
	#define ICON_INFO     10
	#define ICON_HELP	  11
	#define ICON_WARNING  12
	#define ICON_ERROR	  13
	#define ICON_WIZARD	  14
	#define ICON_SHOWBITS 15

	#define ICONCH_INFO "10"
	#define ICONCH_HELP "11"
	#define ICONCH_WARNING "12"
	#define ICONCH_ERROR "13"

	#define ICON_YES 20
	#define ICON_NO	 116
	#define ICON_REFRESH 22
	#define ICON_NEXT  23
	#define ICON_PREVIOUS 24
	#define ICON_APPLY 25
	#define ICON_DEFAULT 26
	#define ICON_IMPORT 27
	#define ICON_EXPORT 28

	#define ICON_USER  30
	#define ICON_GROUP 31
	#define ICON_STATUSINFO 32
	#define ICON_ACCOUNTCREATE 33
	#define ICON_ACCOUNTREMOVE 34
	#define ICON_CHANGEPASSWORD	35
	#define ICON_REMINDPASSWORD	36

	#define ICON_SECURE 40
	#define ICON_UNSECURE 41
	#define ICON_SEARCH	42
	#define ICON_PLUGIN	43
	#define ICON_URL 44
	#define ICON_BETA 45

	#define ICON_CANCEL 46

	#define ICON_OPTIONS 47
	#define ICON_HISTORY 1000
	#define ICON_KONNEKT 49
	#define ICON_DELETE 50



    /** Przy dodawaniu ikonek poprzez #IMI_ICONREGISTER (#IMI_ICONADD) trzeba poda�
        do kt�rego zestawu obraz�w, ikonka/bitmapa ma zosta� dodana.
        Generalnie ikonki dodaje si� do list #IML_16 i #IML_32, a bitmapy do IML_BMP.
        UI wykorzystuje ikonki spoza list tylko w wyj�tkowych sytuacjach (np. 
        do narysowania ikonki w tray'u, ustawienia ikony okna, czy wstawieniu bitmapy
        w menu).
        UI automatycznie wybiera z zasob�w ikonk� o najlepszym rozmiarze i ilo�ci kolor�w
        pasuj�cej do ustawie� ekranu.
        UI nie zawsze doda ikonk� tam, gdzie sobie za�yczymy, np. nie doda bitmapy do IML_ICO
        i generalnie na razie nie dodaje do IML_ICO2 (tylko automatycznie 16 kolorowe ikony
        dla traya).
    */
    enum IML_enum {
        IML_NONE =0x0,
        IML_16   =0x1, ///< lista 16x16
        IML_32   =0x2, ///< lista 32x32
        IML_ICO  =0x100,  ///< samodzielna ikonka (u�ywana rzadko)
        IML_ICO2 =0x200, ///< samodzielna ikonka 2 (u�ywana bardzo rzadko)
        IML_BMP  =0x1000, ///< samodzielna bitmapa (u�ywana rzadko)

		IML_16_32 = IML_16 | IML_32,

    };

    /** Struktura u�ywana razem z #IMI_ICONREGISTER.
     Aby doda� ikonk� trzeba poda� jej \a ID , \a target i jeden z "zestaw�w":
      - URL jako:
	    Plik:
          file://sciezka.typ
		Zasoby biblioteki:
          res://HINSTANCE/id.typ  (dla typ�w ico i bmp; HINSTANCE == 0 -> ui.dll   dll -> dll wywo�uj�cy; id - nazwa elementu w zasobach) 
          res://HINSTANCE/rodzaj/id.typ  (dla dowolnych typ�w; HINSTANCE, id jw., rodzaj - nazwa ga��zi w zasobach) 
		Bezpo�redni uchwyt:
          handle://HANDLE.typ   (typ ico/bmp)
		Ikonka za�adowana do UI:
		  reg://lista/id (lista IML16|IML32 , id - identyfikator ikonki na li�cie)
      - uchwyt biblioteki (\a imgInst ), identyfikator ( \a imgId ) i typ ( \a imgType ) obrazu do pobrania z zasob�w,
      - uchwyt do obrazu ( \a imgHandle ) i jego typ ( \a imgType )
    */
    struct sUIIconRegister{
        unsigned short s_size;
        int ID; ///< ID dodawanej ikonki.
        IML_enum target;  ///< Listy do kt�rych zostanie przydzielona ikonka.
        const char * URL; ///< URL kieruj�cy do pliku/zasobu.
        int imgType; ///< Typ obrazu - 0 - bitmapa, 1 - ikonka
        HINSTANCE imgInst; ///< Biblioteka z kt�rej chcemy wczyta� obraz
        int imgId;   ///< Identyfikator obrazu
        HANDLE imgHandle; ///< Uchwyt obrazu.
		typedef struct tIconParams {
				short size;
				char bits;
		};
        union {
            HANDLE maskHandle; ///< Uchwyt maski, je�li w imgHandle jest Bitmapa.
			tIconParams iconParams;
        };

        sUIIconRegister() {s_size=sizeof(sUIIconRegister);
           target=IML_NONE;URL=0;
           imgHandle = maskHandle = 0;
           imgInst = 0;
           imgId = imgType = 0;
        }
    };

    /** Struktura u�ywana razem z #IMI_ICONREGISTERLIST.
     Przy jej pomocy mo�na dodawa� bitmapy sk�adaj�ce si� z zestawu obrazk�w o identycznych
     rozmiarach. Aby doda� zestaw, trzeba dostarczy� list� kolejnych identyfikator�w, kt�re
     zostan� przyporz�dkowane kolejnym obrazko w bitmapie. Podanie jako identyfikator zera
     spowoduje pomini�cie obrazka na danej pozycji.
     Mo�na poda� drug� bitmap�, tych samych rozmiar�w z mask� p�przezroczysto�ci.
     Zamiast przekazywa� bitmapy, mo�na r�wnie� poda� uchwyt do obiektu ImageList (winAPI).
    */
    struct sUIIconRegisterList{
        unsigned short s_size;
        IML_enum target;  ///< Listy do kt�rych zostan� przydzielone ikonki.
        int count; ///< Liczba obrazk�w do dodania.
        int * idList; ///< Lista identyfikator�w kolejnych obrazk�w.
        int w; ///< Szeroko�� pojedy�czego obrazka, 0 oznacza, �e obrazki s� kwadratami.
        HANDLE imgBmp;  ///< Bitmapa z obrazkami.
        HANDLE maskBmp; ///< Bitmapa z maskami przezroczysto�ci.
        HANDLE ImageList; ///< Uchwyt do obiektu ImageList.
        sUIIconRegisterList() {s_size=sizeof(sUIIconRegisterList);
           target=IML_NONE;
           imgBmp = maskBmp = ImageList = 0;
           count = w = 0;
           idList = 0;
        }
    };


/** @} */

/* \defgroup gr_act Obs�uga Akcji
    \brief \no
    \{
*/
/**@addtogroup imi_action_ 
   @{
*/


  /** \defgroup actm_ Maski styli
      Maski bitowe do pobierania warto�ci ze statusu akcji.
      W zmiennej sUIAction::status przechowywane s� praktycznie wszystkie
      flagi potrzebne do prawid�owego utworzenia akcji. <br><Br>
      Podczas deklarowania nowej akcji , status tworzy si� poprzez
      ��czenie (| - OR) flag \ref acts_ , \ref acts_ i \ref actr_.<br><Br>
      Maski s�u�� do "wy�awiania" konkretnych warto�ci ze statusu... Oznaczaj�
      r�wnie� przedzia�y w jakich mog� si� znale�� poszczeg�lne warto�ci.<Br>
      Np. �eby sprawdzi� czy kontrolka jest separatorem:
      \code
        bool czy_jest = (status & ACTM_TYPE) == ACTT_SEP;
      \endcode
      albo czy jest zaznaczona:
      \code
        bool checked = (status & ACTS_CHECKED);
      \endcode


  \{
  */
  #define ACTM_STATE  0x0000000F /**< Stan , np ukryty , wci�ni�ty (<i>bitmapa</i> - 4 bity). \sa \ref acts_ */
  #define ACTM_STYLE  0x0000FFF0 /**< Style kontrolki (<i>bitmapa</i> - 12 bit�w).              \sa \ref acts_ */
  #define ACTM_TYPE   0x00FF0000 /**< Typ kontrolki (<i>warto��</i> - (0 - 255) << 32).                \sa \ref actt_ */
  #define ACTM_NOTIFY 0xFF000000 /**< Rz�dane powiadomienia
                                      (<i>bitmapa</i> - 8 bit�w).                              \sa \ref actr_ */

  /** @} */

  /** \defgroup act_ Typy akcji
      \brief \no

      Warto�� ustawiana jest w polu sUIActionInfo::type i przeznaczona
      jest tylko do odczytu. Mo�na sprawdzi� rodzaj kontrolki przypisanej
      do akcji, jej ga��� (menu/przyciski , czy kontrolki w opcjach)
  \{
  */
    #define ACT_MENU 0x1   /**< Pozycja w menu.              \sa \ref act_menu */
    #define ACT_CFG  0x2   /**< Pozycja w konfiguracji.      \sa \ref act_cfg */

    #define ACT_BAR  0x3   ///< Kontrolka REBAR (grupa).
                           ///  Ka�da akcja w tej grupie to osobna belka.
                           ///  Je�eli podakcja nie ma podanego typu i gdy jest grup� ,
                           ///  dodawany jest toolbar, gdy nie , dowany jest HWND.
                           ///  \sa \ref act_bar
    #define ACT_BAND 0x4   /**< belka w REBAR.               \sa \ref act_band*/
    #define ACT_TB   0x5   /**< toolbar jako belka.
                             \warning Nie powinno si� sprawdza� typ�w przycisk�w na toolbarze!
                             Przyciski rozwijane i te kt�re znalaz�y si� w menu Chevrona
                             (przycisk pokazuj�cy si� gdy nie wszystkie przyciski s� widoczne)
                             b�d� mia�y np. typ #ACTT_MENU
                             \sa \ref act_tb
                             */
    #define ACT_TBB   0x7  /**< Przycisk na toolbarze.
                             \sa \ref act_tb
                             */
    #define ACT_WND  0x6   ///< okno HWND
    #define ACT_MASK 0xFF  ///< maska typu. Typy mog� by� z przedzia�u od 0 do #ACTT_MASK
    #define ACT_MENUBRANCH  0x100  ///< Nale�y do interfejsu (menu/toolbary)
    #define ACT_CFGBRANCH   0x200  ///< Nale�y do ustawie� (programu/kontaktu)
    #define ACT_BRANCHMASK  0xF00
    #define ACT_WNDMAIN    0x1000
    #define ACT_WNDMSG     0x2000
    #define ACT_WNDNFO     0x3000
    #define ACT_WNDCFG     0x4000       
    #define ACT_WNDHISTORY 0x5000
    #define ACT_WNDMASK    0xF000 ///< Okno do kt�rego nale�y kontrolka

    #define ACT_ISGROUP  0x100000  ///< Jest grup�.
    #define ACT_FORCNT   0x200000  ///< Jest akcj� zale�n� od kontakt�w.

  /** @} */

  /** @defgroup ap_ Parametry dodatkowe akcji
	Przy operacjach na akcjach mo�na podawa� dodatkowe parametry. Przekazywane s� razem z tekstem opisuj�cym kontrolk� w sUIAction_info::txt.
	Parametry mo�na ustawia� tak:
	  @code
		UIActionAdd(... , ... , ... , "Nazwa kontrolki" AP_TIP "Tre�� podpowiedzi" AP_MINIMUM "100", ...);
	  @endcode
	Lub u�ywaj�c funkcji SetActParam().
	
	Parametry mo�na "ustawia�" r�wnie� pojedynczym elementow (np. dla ACTT_COMBO). W takim przypadku przeczytaj o #AP_PARAMS

	Nie wszystkie parametry dzia�aj� ze wszystkimi typami akcji. Zobacz opis konkretnego typu.
	Standardowo na wszystkich akcjach dzia�aj� parametry podpowiedzi #AP_TIP.
    
	@{
  */



    #define AP_VALUE "\2" /**< Warto�� */
    #define AP_ICO "\3" /**< Identyfikator ikonki z listy IML_16  */
	/** Rozdziela tekst akcji/list� element�w od parametr�w akcji...
	    Je�eli ustawiamy akcj�, kt�ra przyjmuje list� element�w (np. ACTT_COMBO), a chcemy przes�a�
		parametr dotycz�cy ca�ej akcji oddzielamy list� element�w od listy parametr�w akcji przy pomocy #AP_PARAMS.
        Mo�emy go r�wnie� u�y� w przypadku zwyk�ych akcji...						 
		@code
		UIActionAdd(... , ... , ACTT_COMBO , "Element1" CFGVALUE "1" "\nElementn" CFGVALUE "n" CFGPARAMS CFGTIP "Tre�� podpowiedzi", ...);
		@endcode
	*/
	#define AP_PARAMS "\4" 
    #define AP_RADIOGRP EXT_PARAM "grp=" /**< Wyznacza grup� akcji */
/** Warto�� minimalna */
    #define AP_MINIMUM EXT_PARAM "min="
/** Warto�� maxymalna */
    #define AP_MAXIMUM EXT_PARAM "max="
/** Skok (np. przy zmianie/wy�wietlaniu warto�ci) */
    #define AP_STEP EXT_PARAM "step="

	#define AP_TIP_OBSOLETE "\1" /**< @obsolete */
/** Tre�� dymka z podpowiedzi�, bez formatowania (@sa #AP_TIPRICH).
	Parametry #AP_TIP, #AP_TIPTITLE, #AP_TIPIMAGEURL i #AP_TIPICON mo�na
	ze sob� dowolnie ��czy�...
*/
	#define AP_TIP			EXT_PARAM "tip=" 
	#define AP_TIP_WIDTH	EXT_PARAM "tipWidth=" 
/** Tre�� dymka z podpowiedzi�, formatowana prostym HTMLem (@sa #ACTT_HTML, #AP_TIP).
*/
	#define AP_TIPRICH		EXT_PARAM "tipRich=" 
	#define AP_TIPRICH_WIDTH AP_TIP_WIDTH 
/** Tytu� dymka z podpowiedzi� */
	#define AP_TIPTITLE EXT_PARAM "tipTitle=" 
/** URL do obrazka wy�wietlanego w dymku z podpowiedzi� (@sa sUIIconRegister) */
	#define AP_TIPIMAGEURL EXT_PARAM "tipImg="
/** Ikonka wy�wietlana obok dymka z podpowiedzi�.
Wyklucza u�ycie #AP_TIPICONURL
*/
	#define AP_TIPICON EXT_PARAM "tipIco="
/** URL do ikonki wy�wietlanej obok dymka z podpowiedzi�. */
	#define AP_TIPICONURL EXT_PARAM "tipIcoUrl="

/** �cie�ka do obrazu 
	@sa sUIIconRegister
*/
    #define AP_IMGURL EXT_PARAM "imgurl="
/** Porz�dany rozmiar �adowanej ikonki */
	#define AP_ICONSIZE EXT_PARAM "iconsize="
/** Porz�dana ilo�� bit�w na pixel ikonki */
	#define AP_ICONDEPTH EXT_PARAM "icondepth="

/**  */
#define AP_MINWIDTH EXT_PARAM "minWidth="
#define AP_MINHEIGHT EXT_PARAM "minHeigt="
#define AP_MAXWIDTH EXT_PARAM "maxWidth="
#define AP_MAXHEIGHT EXT_PARAM "maxHeight="
#define AP_BESTWIDTH EXT_PARAM "best-Width="
#define AP_BESTHEIGHT EXT_PARAM "bestHeight="

#define CFGVALUE AP_VALUE
#define CFGICO AP_ICO
#define CFGTIP AP_TIP


/** @} */



  /** \defgroup actt_ Typy kontrolek
  \{
  */
    #define ACTT_SEP   0x10000      /**< Separator.
                                      \sa \ref act_menu , \ref act_tb , \ref act_cfg
									  */
    #define ACTT_SEPARATOR ACTT_SEP /**< #ACTT_SEP.*/
    #define ACTT_BREAK 0x20000      ///< Przerwa (przeniesienie do nast�pnej kolumny).
                                    ///  \sa \ref act_menu
    #define ACTT_BARBREAK 0x30000   ///< To samo co #ACTT_BREAK , ale z kresk�.
                                    ///  \sa \ref act_menu
    #define ACTT_BAND   0x40000     ///< Boczna banda (jak napis 'Windows' w menu Start).
                                    ///  \sa \ref act_menu
    #define ACTT_HWND   0x50000     /**< Okno HWND.
                                      Okno tworzone jest w momencie otrzymania #ACTN_CREATEWINDOW, a
                                      niszczone po odebraniu #ACTN_DESTROYWINDOW, przynajmniej pierwsze
                                      okno MUSI zosta� obs�u�one.
                                      \sa \ref act_cfg \ref act_tb \ref act_bar
                                    */
    #define ACTT_CHECK     0x60000  ///< CheckBox (lub prze��cznik).
                                    ///  \todo Automatyczne checkBoxy w menu.
                                    ///  \sa \ref act_tb \sa \ref act_cfg
    #define ACTT_CHECKGROUP 0x70000 ///< Grupa prze��cznik�w.
                                    ///  \sa \ref act_tb
    #define ACTT_INFO    0x80000    ///< Informacja tekstowa (kilkolinijkowa).
                                    ///  \sa \ref act_cfg
    #define ACTT_COMMENT 0x90000    ///< Komentarz (Opis na jedn� linijk�).
                                    ///  \sa \ref act_cfg
    #define ACTT_HOLDER  0xA0000    ///<  UI nie podejmuje �adnych dzia�a�. Wysy�a tylko zam�wione
                                    ///   powiadomienia.
                                    ///  \sa \ref act_cfg
    #define ACTT_EDIT    0xB0000    ///< Pole wprowadzanie (jedna linijka).
                                    ///  \sa \ref act_cfg
    #define ACTT_TEXT    0xC0000    ///< Pole wpisywania tekstu (wi�cej linijek).
                                    ///  \sa \ref act_cfg
    #define ACTT_PASSWORD 0xD0000   ///< Pole wpisywania has�a.
                                    ///  \sa \ref act_cfg
    #define ACTT_BUTTON  0xE0000    /**< Przycisk.
									Przyjmuje parametry: #AP_ICO, #AP_IMGURL, #AP_ICONSIZE, #AP_ICONSDEPTH
									*/
    #define ACTT_GROUP  0xF0000     ///< Grupa (ramka z opisem)
                                    ///  \sa \ref act_cfg
    #define ACTT_GROUPEND  0x100000 ///< Koniec grupy (zmniejsza wci�cie i zmienia rozmiar ostatniej grupy)
                                    ///  \sa \ref act_cfg
    #define ACTT_IMAGE     0x110000 /**< Grafika.
                                     W txt akcji podana musi by� �cie�ka...
										file://sciezka.typ
										res://inst/id.typ   inst==0 (ui.dll)  inst==dll (dll)
										handle://handle.typ
										reg://lista/id.typ  lista = IML16|IML32
                                      \sa \ref act_cfg */
    #define ACTT_FILE      0x120000 ///< Plik
                                    ///  \sa \ref act_cfg
    #define ACTT_DIR       0x130000 ///< Katalog
                                    ///  \sa \ref act_cfg
    #define ACTT_COLOR     0x140000 ///< Kolor
                                    ///  \sa \ref act_cfg
    #define ACTT_FONT      0x150000 ///< Font
                                    ///  Podgl�d czcionki ustawiony jest w txt...
                                    ///  \sa \ref act_cfg
    #define ACTT_COMBO      0x160000 /**< ComboBox
                                      Pozycje listy ustawione s� w txt (rozdzielone \\n)...
                                      \sa \ref act_cfg*/
    #define ACTT_TIME      0x170000 ///< Data/Godzina.
                                    ///  Format ustawiony jest w txt. Kontrolka przyjmuje i zwraca warto�ci w #cTime64 i #cDate64.
                                    ///  \sa \ref act_cfg
    #define ACTT_HTMLINFO    0x180000    /**< Informacja tekstowa (kilkolinijkowa) formatowana uproszczonym HTMLem.
Obs�ugiwane s� znaczniki (i atrybuty) - b i u p (align) br div (align) font (face, size, color) span sub sup
Kod musi by� zgodny ze standardem XHTML pod wzgl�dem formatowania znacznik�w (np. <br/> a nie <br>)

Dodatkowo, ka�dy znacznik mo�e posiada� atrybut class o warto�ciach:
title - pogrubiona, wi�ksza czcionka - wy�rodkowane
copy - informacja o prawach autorskich - mniejsza, przyszarzona, po prawej
warn - wi�ksze, pogrubione, czerwone
info - ciut wi�ksza czcionka, justowane
note - lekko wyszarzone, justowane
name - nazwa zmiennej
value - warto�� zmiennej - pogrubione
under_dot - podkre�lone kropkowan� lini�
									*/
	/**  */

	/**Przycisk typu "radio".
	List� przycisk�w tworz� kolejne akcje typu ACTT_RADIO.
	Ostatnia akcja z listy musi mie� ustawiony status #ACTSRADIO_LAST.
	Akcje grupowane s� wg. atrybutu @a p1 , lub parametru #AP_RADIOGRP przekazanego w @a txt.
	Warto�� (wczytywana/zapisywana do bazy) jest dla grupy akcji ta sama i r�wna
	warto�ci przypisanej do zaznaczonej akcji z grupy. Warto�� akcji pobierana jest z parametru #AP_VALUE, lub
	z kolejno�ci akcji w grupy gdy ustawiony jest status #ACTSRADIO_BYPOS
	*/
    #define ACTT_RADIO      0x190000  
	/**Spinner - pole edycji liczb z przyciskami g�ra/d�.
	Przyjmuje dodatkowe parametry: #AP_MINIMUM i #AP_MAXIMUM
	*/
    #define ACTT_SPINNER    0x1A0000 
	/**Suwak.
	Je�eli chcemy opisa� oba ko�ce suwaka, opisy rodzielamy znakiem nowej linii '\n'
	Przyjmuje dodatkowe parametry: #AP_MINIMUM, #AP_MAXIMUM, #AP_STEP
	*/
    #define ACTT_SLIDER     0x1B0000 
	/**Przycisk otwieraj�cy podpowied�...
	Zachowuje si� identycznie jak #ACTT_BUTTON z t� r�nic�, �e po klikni�ciu i wywo�aniu #ACTN_ACTION
	wy�wietla "dymek" podpowiedziedzi (@sa #AP_TIP)
	*/
	#define ACTT_TIPBUTTON  0x1C0000

    #define ACTT_LINK		0x1D0000   /**< Przycisk - link (bez obramowania) .
	Zachowuje si� identycznie jak #ACTT_BUTTON.
	*/


  /** @} */

  /** \defgroup acts_ Statusy akcji
  \{
  */
    #define ACTS_SHOW     0
    #define ACTS_HIDDEN   1          ///< Ukryty.
                                     ///  \sa \ref act_menu \ref act_tb \ref act_band \ref act_cfg
    #define ACTS_DISABLED 2          ///< Wy��czony (niedost�pny).
                                     ///  \sa \ref act_menu \ref act_tb \ref act_cfg
    #define ACTS_CHECKED  4          ///< Zaznaczony.
                                     ///  \sa \ref act_menu \ref act_tb \ref act_cfg
    #define ACTS_SELECTED 8          ///< Wybrany.
                                     ///  

    #define ACTS_GROUP         0x10  /**< Akcja jest grup� (ma pod-akcje). \sa \ref act*/


    #define ACTSMENU_NOTRANS      0x40  /**< Grafika bez prze�roczysto�ci     \sa \ref act_menu */
    #define ACTSMENU_CHECKSPACE   0x8000  /**< Zostawia odst�p na checkboxa (tylko dla grup)     \sa \ref act_menu */
    #define ACTSMENU_BOLD        0x100  /**< Pozycja grub� czcionk�     \sa \ref act_menu */

    #define ACTSBAR_BOTTOM        0x20  ///< Wyr�wnany do do�u.
                                     ///  \sa \ref act_bar
    #define ACTSBAR_NOALIGN       0x40  ///< Bez wyr�wnania
                                     ///  \sa \ref act_bar
    #define ACTSBAR_VERT          0x80 ///< W pionie.
                                     ///  \sa \ref act_bar
    #define ACTSBAR_LOCKED        0x100 ///< Zablokowane.
                                     ///  \sa \ref act_bar

                                     ///  \sa \ref act_tb
    #define ACTSBAND_FULL         0x100  ///< Belka zawsze w ca�o�ci.
                                     ///  \sa \ref act_band
    #define ACTSBAND_WRAP         0x400  ///< Zawija do nast�pnej linijki.
                                     ///  \sa \ref act_band

    #define ACTSTB_DARROWS       0x20  ///< Strza�ki na przyciskach z menu.
                                     ///  \sa \ref act_tb
    #define ACTSTB_MIXED         0x40  ///< Przyciski zar�wno z opisem jak i bez.
                                     ///  \sa \ref act_tb
    #define ACTSTB_LIST          0x80  ///< Przyciski jak lista (opisy po prawej).

    #define ACTSTB_SHOWTEXT     0x1000  ///< Zawsze pokazuje opis.
                                     ///  \sa \ref act_tb
    #define ACTSTB_WHOLEDROPDOWN 0x200  ///< Ca�y przycisk otwiera menu.
                                     ///  \sa \ref act_tb
    #define ACTSTB_WRAP         ACTSBAND_WRAP  ///< Zawija do nast�pnej linijki.
                                     ///  \sa \ref act_tb
    #define ACTSTB_OPAQUE       0x800  ///< Wypuk�e przyciski.
                                     ///  \sa \ref act_tb

    #define ACTSC_INT           0x20  ///< Kontrolka przyjmuje tylko liczby.
                                     ///  \sa \ref act_cfg
    #define ACTSC_INLINE        0x40  ///< Nast�pna kontrolka znajdzie si� w tym samym rz�dzie.
                                     ///  \sa \ref act_cfg
    #define ACTSC_FULLWIDTH     0x80  ///< Rozci�ga na pe�n� d�ugo��
    #define ACTSC_BOLD         0x100 ///< Kontrolka pisana jest grub� czcionk�.
                                     ///  \sa \ref act_cfg
    #define ACTSC_NEEDRESTART  0x200 ///< Zmiany w tej kontrolce wymagaj� restartu.
                                     ///  \sa \ref act_cfg

    #define ACTSCOMBO_LIST       0x1000 ///< Bez mo�liwo�ci edycji (#ACTT_COMBO). 
    #define ACTSCOMBO_SORT       0x2000 ///< Lista sortowana (#ACTT_COMBO). 
    #define ACTSCOMBO_BYPOS      0x4000 ///< Warto�ci� jest pozycja (#ACTT_COMBO). 
    #define ACTSCOMBO_NOICON     0x8000 ///< Bez miejsca na ikonk�... (#ACTT_COMBO)

    #define ACTSRADIO_BYPOS      0x1000 ///< Warto�ci� jest pozycja (#ACTT_RADIO). 
    #define ACTSRADIO_LAST       0x2000 ///< Oznacza ostatni element grupy. Musi by� ustawiony. (#ACTT_RADIO). 


    #define ACTSTIME_SHOWNONE   0x1000 ///< Wstawia checkbox (#ACTT_TIME)
    #define ACTSTIME_UPDOWN     0x2000 ///< Wstawia kontrolki do edycji (#ACTT_TIME)  

    #define ACTSFONT_CHECKBOX    0x4000 ///< Font mo�e by� wy��czony (#ACTT_FONT)
    #define ACTSFONT_NOCOLOR     0x8000 ///< Font nie ma koloru czcionki (#ACTT_FONT)
    #define ACTSFONT_NOBGCOLOR   0x400 ///< Font nie ma kolotu tla (#ACTT_FONT)
    #define ACTSFONT_NOSIZE      0x800 ///< Font nie ma ustawianego rozmiaru (#ACTT_FONT)
    #define ACTSFONT_NOFACE     0x1000 ///< Font nie ma ustawianej czcionki (#ACTT_FONT)
    #define ACTSFONT_NOSTYLE    0x2000 ///< Font nie ma ustawianego efektu (pogrubiony itp.) (#ACTT_FONT)

    #define ACTSCOLOR_CHECKBOX   0x1000 ///< Kolor mo�e by� wy��czony
     
    #define ACTSINFO_CENTER      0x1000 ///< Tekst jest wy�rodkowany.

	#define ACTSBUTTON_ALIGNRIGHT 0x1000

    #define ACTSEDIT_READONLY  0x1000 /**< Kontrolka jest tylko do odczytu. */


/** @} */

  /** \defgroup actr_ Rz�dania powiadomie�
      \brief \no
      
      Poprzez te flagi mo�na wybra� kt�re grupy powiadomie� (\ref actn_)
      b�d� wysy�ane do wtyczki zarz�dzaj�cej akcj�.
    \{
  */

 // CFG
    #define ACTR_INIT    0x1000000  /**< Wysy�a #ACTN_CREATE (dla grup r�wnie� #ACTN_CREATEITEM) i #ACTN_DESTROY.
                                        \attention W \ref cfg "konfiguracji" przy Create <br>
                                        \sa \ref act
                                        */
    #define ACTR_SHOW    0x2000000  /**< Wysyla #ACTN_SHOW i #HIDE.
                                        \sa \ref act_cfg \ref act_menu
                                        */
    #define ACTR_SAVE    0x4000000  /**< Wysy�a #ACTN_SAVE.
                                        \sa \ref act_cfg
                                        */
    #define ACTR_CHECK   0x8000000  /**< Wysyla #ACTN_CHECK.
                                        \sa \ref act_cfg
                                        */
    #define ACTR_RESIZE 0x10000000  /**< Wysy�a #ACTN_RESISZE.
                                        \sa \ref act_cfg \ref act_tb
                                        */
    #define ACTR_STATUS 0x20000000  /**< Wysy�a #ACTN_STATUS. (przy zmianie statusu)
                                        \sa \ref act_cfg \ref act_tb
                                        */
    #define ACTR_SETCNT 0x20000000  /**< Wysy�a #ACTN_SETCNT. (przy zmianie kontaktu przypisanego do kontrolki)
                                        \sa \ref act_cfg \ref act_tb
                                        */
    #define ACTR_CONVERT 0x40000000  /**< Wysyla #ACTN_GET , #ACTN_SET , #ACTN_CONVERT_FROM , #ACTN_CONVERT_TO.
                                        \sa \ref act_cfg
                                        */
	#define ACTR_GETSET ACTR_CONVERT
    #define ACTR_NODATASTORE 0x80000000  /**< Blokuje pobieranie/ustawianie warto�ci do/z bazy.
                                        \sa \ref act_cfg
                                        */

  /** @} */

  /** \defgroup actn_ Powiadomienia
      \brief \no

      Parametry powiadomie� trzymane s� w zmiennych sUIAction::notify1 i sUIAction::notify2 .

  \{
  */

    #define ACTN_ACTION   1   /** Akcja zosta�a uruchomiona \sa \ref act*/
    #define ACTN_GROUP    2   /** Grupa zosta�a uruchomiona \sa \ref act*/
    #define ACTN_CREATE   10  /**< Akcja jest wysy�ana (zaraz \b przed utworzeniem).
                                   W \ref menu "menu" <br>
                                   - \param notify1 (HANDLE) uchwyt do rodzica (okna,menu).
                                   \sa \ref act
                                   */
	#define ACTN_CREATEGROUP 19 /**< Tak samo jako @ref #ACTN_CREATE, tyle �e, gdy tworzona jest grupa*/
#define ACTN_DESTROY  11  /**< Akcja jest usuwana (zaraz \b przed usuni�ciem).
                                   \sa \ref act
                                   */
    #define ACTN_SHOW     12  /**< Akcja jest pokazywana (\b przed).
                                   \sa \ref act_cfg \ref act_menu
                                   */
    #define ACTN_HIDE     13  /**< Akcja jest ukrywana (\b przed).
                                   \sa \ref act_cfg \ref act_menu
                                   */
    #define ACTN_SAVE     14  /**< Konfiguracja jest zapisywana.
                                   \sa \ref act_cfg
                                   */
    #define ACTN_RESIZE   15  /**< Kontrolka powinna zmieni� rozmiar.
                                   - \a notify1 = \i 0xHHHHWWWW (gdzie \b WWWW to proponowana \a szeroko�� a \b HHHH to proponowana \a wysoko��).
                                   - \a notify2 = uchwyt okna zawieraj�cego kontrolk� (ParentWindow()).
                                   \attention W tej chwili zmiana \a notify1 \b nie powoduje zmiany rozmiaru kontrolki!
                                   \todo Zmiana wielko�ci kontrolek.
                                   \sa \ref act_cfg
                                   */
    #define ACTN_STATUS   16  /**< zmiana statusu (enabled/disabled)
                                   \param p1 Nowy status.
                                   \param p2 Stary status.
                              */
    #define ACTN_DEFAULT 17   /**< UI sprawdza, czy wtyczka uwa�a si� za domy�ln� na li�cie.
                                    \return zwr�cenie true spowoduje wywo�anie tej akcji.*/
    #define ACTN_SETCNT 18   /**< Zosta� zmieniony kontakt przypisany do kontrolki. 
									Akcja powinna podj�� w�asne dzia�ania i ustawi� nowy cUIActionInfo::handle w @a notify2.
									@notify1 Poprzedni przypisany kontakt
									@notify2 Poprzedni uchwyt. Nale�y ustawi� nowy!
                                    @return aktualny uchwyt (handle) kontrolki*/

    #define ACTN_CHECK    100 /**< Kontrolka zmieni�a warto��. Mo�liwe jest jej sprawdzenie i
                                   ewentualna zmiana.
                                   - \a p1 = wska�nik do bufora \b char * z warto�ci�.
                                   - \a p2 = 0
                                   \sa \ref act_cfg
                                   */
    #define ACTN_GET      101 /**< W \a p1 trzeba ustawi� warto�� (tekstow�) akcji (warto�� zostanie np wpisana do kontrolki).
                                   Ten Notify u�ywany jest gdy akcja nie ma ustawionego #ACTS_AUTO.
                                   - \a p1 = wka�nik do bufora \b char *.
                                   - \a p2 = rozmiar bufora
                                   \attention
                                   \sa \ref act_cfg
                                   */
    #define ACTN_SET      102 /**< Warto�� (\a p1) powinna by� zapisana
                                   Ten Notify u�ywany jest gdy akcja nie ma ustawionego #ACTS_AUTO.
                                   - \a p1 = wska�nik do bufora \b char * z warto�ci�.
                                   - \a p2 = 0
                                   \sa \ref act_cfg
                                   */
    #define ACTN_CONVERT_TO      103 /**< W @a notify1 znajduje si� warto��, kt�r� nale�y przekonwertowa� na form� zrozumia�� dla akcji.
                                   To zdarzenie u�ywane jest gdy akcja posiada w�asn� obs�ug� zapisu/odczytu danych (#ACTN_GET , #ACTN_SET) i
								   dane ustawiane przez np. UIActionCfgSetValue s� w innej postaci, ni� spodziewa�aby si� tego kontrolka akcji.
								   Przyk�adem mo�e by� obs�uga ustawienia kontaktu #CNT_BORN: 
								     Akcja jako warto�� przyjmuje liczby 64-bitowe (zgodne z __time64_t).
									 W tablicy u�ytkownika data urodzenia zapisywana jest jednak jako liczba 32bitowa (RRRRMMDD).
									 Odczyt i zapis pomi�dzy akcj� a tablic� obs�ugiwany jest przez #ACTN_GET i #ACTN_SET.
									 Aby teraz m�c ustawi� warto�� akcji na warto�� pobran� bezpo�rednio z bazy danych - musi nast�pi� konwersja. Wywo�uj�c UIActionCfgSetValue z @a convert = true z warto�ci� pobran� z bazy, przeka�emy j� do #ACTN_CONVERT_TO, kt�ra zmieni format 32-bitowy na 64-bitowy i nowa warto�� zostanie ustawiona w akcji...
								   Podczas wczytywania konfiguracji wywo�ywane jest zaraz @b po ewentualnym #ACTN_GET
								   Zostanie wywo�ane tylko dla akcji z flag� #ACTR_CONVERT
								   @b sUIActionNotify_buff *
                                   - @a buff  wka�nik do bufora
                                   - @a buffSize rozmiar bufora
                                   @sa @ref act_cfg
                                   */
    #define ACTN_CONVERT_FROM    104 /**< W @a notify1 znajduje si� warto�� akcji, kt�r� nale�y przekonwertowa� na form� zrozumia�� dla zamawiaj�cego.
								   @sa #ACTN_CONVERT_TO
								   Podczas zapisywania konfiguracji wywo�ywane jest zaraz @b przed ewentualnym #ACTN_SET
								   Zostanie wywo�ane tylko dla akcji z flag� #ACTR_CONVERT
								   @b sUIActionNotify_buff *
                                   - @a buff  wka�nik do bufora
                                   - @a buffSize rozmiar bufora
                                   @sa @ref act_cfg
                                   */
    #define ACTN_FILEOPEN 201/**< Wysy�ane przed wy�wietleniem okna wybierania pliku (ACTT_FILE).
                                   \param p1 - wska�nik do windowsowej struktury OPENFILENAME
                               */
    #define ACTN_FILEOPENED 202/**< Wysy�ane po wy�wietleniu okna wybierania pliku (ACTT_FILE).
                                   \param p1 - wska�nik do windowsowej struktury OPENFILENAME
                               */
    #define ACTN_DROP 210/**< Wysy�ane przed wy�wietleniem listy combo (#ACTT_COMBO).*/

    #define ACTN_CREATEWINDOW 220 /**< Wysy�ane, gdy trzeba utworzy� kontrolk� #ACTT_HWND jako sUIActionNotify_createWindow. */
    #define ACTN_DESTROYWINDOW 221 /**< Wysy�ane, gdy trzeba zniszczy� kontrolk� #ACTT_HWND jako sUIActionNotify_destroyWindow. */


#ifdef _WINDOWS_
/** #ACTN_CREATEWINDOW przesy�any jest jako ta struktura */
struct sUIActionNotify_createWindow: public sUIActionNotify_base {
        HWND hwnd;  ///< Tutaj MUSIMY ustawi� uchwyt do naszego okna.
        HWND hwndParent; ///< Uchwyt okna, do kt�rego mamy si� pod��czy�.
        int x   ///< Pozycja X na kt�rej trzeba wstawi� okno. TRZEBA t� warto�� zwi�kszy� o szeroko�� utworzonego okna!
            , y;///< Pozycja Y na kt�rej trzeba wstawi� okno. TRZEBA t� warto�� zwi�kszy� o wysoko�� utworzonego okna!
        unsigned int status; ///< Kopia warto�ci \a status akcji
        const char * txt; ///< Kopia warto�ci \a txt akcji
        unsigned int flags; ///< Flagi - Na razie 0.
        HFONT font;     ///< Domy�lna czcionka u�ywana przez konnekta.
        HFONT fontBold; ///< Ta sama czcionka, tyle �e pogrubiona.
        int w   ///< Sugerowana szeroko�� okna
            , h;///< Sugerowana wysoko�� okna
        sUIActionNotify_createWindow()
            :sUIActionNotify_base(), hwnd(0) , flags(0)
            {  s_size=sizeof(*this); code=ACTN_CREATEWINDOW;}
};
/** #ACTN_DESTROYWINDOW przesy�any jest jako ta struktura */
struct sUIActionNotify_destroyWindow: public sUIActionNotify_base {
        HWND hwnd;  ///< Uchwyt okna do usuni�cia.
        unsigned int flags; ///< Flagi - Na razie 0.
        sUIActionNotify_destroyWindow()
            :sUIActionNotify_base(), hwnd(0) , flags(0)
            {  s_size=sizeof(*this); code=ACTN_DESTROYWINDOW;}
};
#endif
  /** @} */




  /** @defgroup imib_ Identyfikatory akcji.
    \brief \no
    Jest mo�liwo�� wygodnego maskowania akcji, tak aby w procedurze obs�uguj�cej
    #IM_ACTION m�c rozr�ni� akcje. Mask� IMIB_ nak�ada si� na zwyk�y identyfikator
    (i tworz� one ca�o��. Odwo�ywa� si� do takiej akcji mo�na TYLKO w tej samej postaci
     - z identyfikatorem!).
    G��wnym u�atwieniem jest #IMIB_CFG i #IMIB_CNT, dzi�ki kt�remu tworz�c akcje do ustawie� mo�na
    jako identyfikator poda� #IMIB_CFG/#IMIB_CNT i jako parametr \a p1 standardowo poda� kolumn�
    kt�rej dotyczy akcja. UI automatycznie utworzy identyfikator akcji jako #IMIB_ | p1.
    Nie musimy wi�c dwukrotnie wpisywa� tego samego identyfikatora, ani tworzy� nowych.
    @{
  */
    // Znacznik
    #define IMIB_         0xFF000000
    #define IMIB_CFG      0x11000000 ///< Maska dla ustawie� programu.
    #define IMIB_CNT      0x13000000 ///< Maska dla ustawie� kontaktu.
    #define IMIB_PROFILE  0x12000000
  /** @} */

/** @} */ // imi_action_

/** @addtogroup imig_ 
    @{
*/
    // Akcje i Grupy
    #define IMIA_MAIN_SEP1 100
    #define IMIA_MAIN_SEP2 101

	#define IMIG_MAIN_DEBUG 170
    #define IMIA_MAIN_DEBUG 171
    #define IMIA_MAIN_DEBUG_ICO 172
    #define IMIA_MAIN_DEBUG_UI 173
    #define IMIA_MAIN_BETA 106
    #define IMIA_MAIN_REPORT 109

    //#define IMIA_MAIN_LOG   106
    #define IMIA_MAIN_ABOUT 107
    #define IMIA_MAIN_WWW   108
    #define IMIA_MAIN_HELP   116
	#define IMIA_MAIN_FORUM 118
	#define IMIA_MAIN_DOWNLOADINFO 119

    #define IMIA_CNTTIP 117

    #define IMIA_MAIN_OPTIONS_CFG 110
    #define IMIA_MAIN_OPTIONS_PLUG 115
    #define IMIA_MAIN_OPTIONS_PROFILE_DEL 111
    #define IMIA_MAIN_OPTIONS_PROFILE_NEW 112
    #define IMIA_MAIN_OPTIONS_PROFILE_PASS 114
    #define IMIG_MAIN_OPTIONS_LIST 113

    #define IMIA_MAIN_CNT_ADD  120
    #define IMIA_MAIN_CNT_SEARCH 121
    #define IMIA_MAIN_CNT_IGNORE 122
    #define IMIA_MAIN_CNT_GROUPS 123
    #define IMIA_MAIN_HISTORY  124

    #define IMIG_MAIN_FILTERS 150

	#define IMIA_EVENT_SERVER  140
    #define IMIA_EVENT_URL  141
	#define IMIA_EVENT_EVENT 142
	#define IMIA_EVENT_OPENANYMESSAGE 143

    #define IMIA_CNT_MSG 130
    #define IMIA_CNT_SEP 131
    #define IMIA_CNT_INFO 132
    #define IMIA_CNT_HISTORY 133
    #define IMIA_CNT_DEL 134
    #define IMIA_CNT_IGNORE 135
//    #define IMIA_CNT_UNIGNORE 137
    #define IMIA_CNT_ADD 136
    #define IMIA_CNT_SENDEMAIL 139
    #define IMIA_CNT_OPENANYMESSAGE 143 // to samo co IMIA_EVENT_OPENANYMESSAGE

    #define IMIA_CNT_MSGOPEN 138

    #define IMIG_CFG_CONNECTION_PROXY 300
    #define IMIA_CFG_CONNECTION_PROXY_ON 301 | IMIB_CFG
    #define IMIA_CFG_CONNECTION_PROXY_AUTO 302 | IMIB_CFG

    #define IMIG_CFG_USER_STATUS 320

    #define IMIG_CFG_STARTUP 330
    #define IMIA_CFG_STARTUP_CLEANUP 331


    #define IMIG_CFG_UI_CNT     310
    #define IMIG_CFG_UI_CNT_IC     315
    #define IMIG_CFG_UI_CNT_TIP     321
    #define IMIG_CFG_UI_MSG     311
    #define IMIG_CFG_UI_MSG_NOTINLIST 312
	#define IMIG_CFG_UI_MSG_HISTORY 317
    #define IMIG_CFG_UI_APPRNC     316
    #define IMIG_CFG_UI_FORMAT     318
    #define IMIG_CFG_UI_DOCK     322
    #define IMIG_CFG_UI_NOTIFY     323
    #define IMIG_CFG_UI_GROUPS     324

    #define IMIA_CFG_UIM_MSG_NIL_PASS 313
    #define IMIA_CFG_UIM_MSG_NIL_REPLY 314

    #define IMIA_CFG_SHOWBITS 319

    #define IMIA_CFG_UICLIP_INFO 0x1000
    #define IMIA_CFG_UICLIP_EMAIL 0x1001
    #define IMIA_CFG_UICLIP_PHONE 0x1002

    #define IMIG_MSGTB   200      // glwony toolbar
    #define IMIA_MSG_SEND 201
    #define IMIA_MSG_INFO 202
    #define IMIA_MSG_HISTORY 203
	#define IMIA_MSG_BYENTER 204

    #define IMIG_MSGSENDTB    220
    #define IMIA_MSG_SENDMAIL 221



    // Tray

    #define IMIA_TRAY_SHUTDOWN 151
    #define IMIA_TRAY_SHOW 152
    #define IMIA_TRAY_STATUS 153

    // Alpha-blending
    #define IMIA_MAINALPHA 160


    // Info o kontakcie
    #define IMIG_NFO_SAVE  400
    #define IMIA_NFO_SAVE_ALL  IMIG_NFO_SAVE
    #define IMIA_NFO_SAVE_LOCAL  404
    #define IMIA_NFO_CANCEL  401
    #define IMIG_NFO_REFRESH  402
    #define IMIA_NFO_REFRESH_ALL  IMIG_NFO_REFRESH
    #define IMIA_NFO_ADDTOLIST 403
    #define IMIA_NFO_NOTONLIST 405

    #define IMIG_NFO_SUMMARY  413
        #define IMIA_NFO_SUM 420
    #define IMIG_NFO_DETAILS  410
    #define IMIG_NFO_CONTACT  411
    #define IMIG_NFO_INFO  412
    #define IMIG_NFO_WORK  414
    // Z IMIB_CNT
    #define IMIA_NFO_DETAILS_NET 200

/** @} */


/** @addtogroup cfg_
    @{ */

    #define CFG_UIAUTOSTART  		100  ///< \b UI - #DT_CT_INT - autostart (2 - automatyczny)
    #define CFG_UIAUTOSTARTAPPLIESTO 210  ///< \b UI - #DT_CT_INT - autostart (0 - ostatnia instancja, 1 - aktualna instancja, 2 - aktualny profil)
    #define CFG_UIAUTOSTARTASKFORPROFILE 211  ///< \b UI - #DT_CT_INT - autostart (0 - ostatnia instancja, 1 - aktualna instancja, 2 - aktualny profil)
    #define CFG_UIHIDDENSTART		101  ///< \b UI - #DT_CT_INT - 
    #define CFG_UIAUTOHIDE			102  ///< \b UI - #DT_CT_INT - 
    #define CFG_UIHIDDENAUTOSTART	103  ///< \b UI - #DT_CT_INT - 
    #define CFG_UITRAY		104          ///< \b UI - #DT_CT_INT - 
    #define CFG_UICANDOCK		105      ///< \b UI - #DT_CT_INT - 
    #define CFG_UISNAP		106          ///< \b UI - #DT_CT_INT - 
    #define CFG_UIMSGFROMOTHER	107      ///< \b UI - #DT_CT_INT - 
    #define CFG_UIAUTOADDCNT	108      ///< \b UI - #DT_CT_INT - 
    #define CFG_UICNTONLINENOTIFY	109  ///< \b UI - #DT_CT_INT - 
    #define CFG_UICNTONLINEONLIST	133  ///< \b UI - #DT_CT_INT - 
    #define CFG_UIANIMCNT		110      ///< \b UI - #DT_CT_INT - 
    #define CFG_UIANIM		111          ///< \b UI - #DT_CT_INT - 
    #define CFG_UIMSGPOPUP		112      ///< \b UI - #DT_CT_INT -  0 wy��czony, 1 zminimalizowane, 2 wyskakuj�ce , 3 wyskakuj�ce na wierzchu (Konnekt::UI::CFG::enMsgPopup)
    #define CFG_UIMSGFLASH		113      ///< \b UI - #DT_CT_INT - 
    #define CFG_UISORTBYMSG		114  ///< \b UI - #DT_CT_INT - 
    #define CFG_UISTATUSINTRAY	115      ///< \b UI - #DT_CT_INT - 0 - wy��czony, 1 - status pierwszej sieci, -1 - status ostatnio zmienione, pozosta�e - net sieci
    #define CFG_UISAMECNTSTATUS	116  ///< \b UI - #DT_CT_INT -  Wszystkie kontakty maja te same ikonki...
    #define CFG_UIONTOP             118 ///< \b UI - #DT_CT_INT - 
    #define CFG_UIDOCKHIDE		119      ///< \b UI - #DT_CT_INT - 
    #define CFG_UIINFOTIP		135      ///< \b UI - #DT_CT_INT - 
    #define CFG_UIALLGROUPSDESC     136  ///< \b UI - #DT_CT_PCHAR -  Opis zak�adki z wszystkimi grupami
    #define CFG_UIALLGROUPS_NOGROUP 200  ///< \b UI - #DT_CT_INT - zak�adka "wszystkie" zawiera kontakty BEZ grupy...
    #define CFG_UIMSGBYENTER        137  ///< \b UI - #DT_CT_INT -  Wysy�a wiadomo�� przez Enter
	#define CFG_UITRAYTOOLTIPSHOWSTATUS   213 ///< 0 - stary 1 - nowy

    #define CFG_DESCR_AWAY          125  ///< \b UI - #DT_CT_PCHAR - 
    #define CFG_DESCR_AAWAY         126  ///< \b UI - #DT_CT_PCHAR - opis auto-away'a
    #define CFG_DESCR_DND           127  ///< \b UI - #DT_CT_PCHAR - 
    #define CFG_DESCR_HIDDEN        128  ///< \b UI - #DT_CT_PCHAR - 
    #define CFG_DESCR_ONLINE        130  ///< \b UI - #DT_CT_PCHAR - 
    #define CFG_DESCR_OFFLINE       131  ///< \b UI - #DT_CT_PCHAR - 
    //#define CFG_DESCR               139
    #define CFG_DESCR_USEMANUAL     141 ///< \b UI - #DT_CT_INT - 
    #define CFG_DESCR_CLEARMANUAL 169 ///< \b UI - #DT_CT_INT
    //#define CFG_DESCR_CURRENT       142

    //#define CFG_FRIENDSONLY         129
    #define CFG_AUTOAWAY            132   ///< \b UI - #DT_CT_INT - 

//    #define CFG_UIMSGFONTSIZE       134   ///< \b UI - #DT_CT_INT - 

    #define CFG_UIPOS_X	        120    ///< \b UI - #DT_CT_INT - 
    #define CFG_UIPOS_Y	        121    ///< \b UI - #DT_CT_INT - 
    #define CFG_UIPOS_W	        122    ///< \b UI - #DT_CT_INT - 
    #define CFG_UIPOS_H	        123    ///< \b UI - #DT_CT_INT - 
    #define CFG_UIPOS_DOCKED	124        ///< \b UI - #DT_CT_INT - 

    // Czcionki okna wiadomosci
    #define CFG_UIF_MSG             156
    #define CFG_UIF_MSGCNT          150 // nazwa kontaktu
    #define CFG_UIF_MSGSEND         151 // wysylane
    #define CFG_UIF_MSGRCV          152 // odbierane
    #define CFG_UIF_MSGINFO         153 // specjalne
    #define CFG_UIF_MSGMARK         198 // pod�wietlone

    // Czcionka listy kontaktow
    #define CFG_UIF_CLIST           154
    #define CFG_UIF_CLISTSEL        155
	#define CFG_UIF_CLISTINFO		202
    // Na razie nie wazne!
    #define CFG_UIF_MSGTXTS         157

    #define CFG_ISAUTOAWAY          138
    #define CFG_UIONECLICKTRAY      140
    #define CFG_UITIPDELAY          143
    #define CFG_UILASTACTIVITY      144
    #define CFG_UIMSGFROMOTHERREPLY 145
    #define CFG_UIMSGHOLDNOTIFY     146
    #define CFG_UIMSGFROMOTHERPASS  147
    #define CFG_UIREMEMBERMSGWND    148
    #define CFG_UIEDITONLIST        160
    #define CFG_UISORTACTIVE        161
    #define CFG_UIONLINEBOLD        163
    #define CFG_UISHOWIP            164
    #define CFG_UIMAINTITLE         165 ///< \b UI - #DT_CT_PCHAR

    #define CFG_UIGRPTABS_MULTILINE 166 ///< \b UI - #DT_CT_INT - 
    #define CFG_UIGRPTABS_VERTICAL  167 ///< \b UI - #DT_CT_INT - 
    #define CFG_UILIST_FLATSB       168 ///< \b UI - #DT_CT_INT

    #define CFG_UIMSGTITLE          170 ///< \b UI - #DT_CT_PCHAR
    #define CFG_UITRAYTITLE         171 ///< \b UI - #DT_CT_PCHAR
    #define CFG_UITRAYTITLEEVENT    172 ///< \b UI - #DT_CT_PCHAR
    #define CFG_UIDOCKSPACE         173 ///< \b UI - #DT_CT_INT
    #define CFG_UIDOCKEDALPHA       174 ///< \b UI - #DT_CT_INT
    #define CFG_UIDOCKWAIT          187
    #define CFG_UIDOCKSTRETCH       193
	#define CFG_UICNT_CREATEDISPLAY_FORMAT 206

    #define CFG_UICNTTIPDOCKED      175
    #define CFG_UICNTTIPFONT        176
    #define CFG_UICNTTIPICONS       177
    #define CFG_UICNTTIPHEADER      178
	#define CFG_UICNTTIPINFO		204
	#define CFG_UICNTTIP_SHOWDEFAULT 207

    #define CFG_UICL_ICONSON        117 ///< \b UI - #DT_CT_INT - 
    #define CFG_UICL_ICONSONRIGHT   162
    #define CFG_UICL_ICONSOFFSET   179 //miejsce naokolo
    #define CFG_UICL_ICONS   180 //rozmieszczenie
    #define CFG_UIMESSAGEHISTORY   181 ///< Historia wpisanych wiadomo�ci (Konnekt::UI::CFG::enMessageHistory)
    #define CFG_UIMSGSHOWSTATUS   182 ///< Informuje o zmianach statusu
    #define CFG_UICL_BUFFEREDPAINT   183 ///< Buforowane wy�wietlanie
    #define CFG_UISPLASHSCREEN   184 ///< Splash Screen
	#define CFG_UICL_INFO  201 ///< enCntListInfo
	#define CFG_UICL_INFO_FORMAT  203
	#define CFG_UICL_DISPLAY_FORMAT 205

    #define CFG_ACK_SHOWQUEUED   185
    #define CFG_ACK_SHOWFAILED   186
	
	#define CFG_UIPLUGINSGROUP   188

	#define CFG_UIHISTORY_XMLHEADER 214
	#define CFG_UIHISTORY_XMLXSL 215
	#define CFG_UIHISTORY_XMLPRINTXSL 216
	#define CFG_UIHISTORY_XMLFULL 190
	#define CFG_UIHISTORY_MARKFOUND 199

	#define CFG_UIMSGVIEW_COPY 191

    #define CFG_UIMAINALPHA          192
    #define CFG_UIUSEMAINALPHA          212
    #define CFG_UIFILTERACTION       196 // enGroupType 
    #define CFG_UIMAINTASKBAR        197 /// 

	#define CFG_UIFILTERS 194


    #define CFG_UI_COUNT (38 + 8)  // cfg+colors
    // 217  <- nastepny
/** @} */

namespace Konnekt {

	/**@addtogroup imi_action_
	   @{
	*/
	/**
	ShowBits odpowiada za stopie� "skomplikowania" interfejsu Konnekta.
	U�ytkownik przy pomocy suwaka okre�la sw�j poziom zaawansowania,
	kt�ry z kolei przek�ada si� na zestawy bit�w ShowBits.

	Podczas konstruowania interfejsu autorzy wtyczek powinni sprawdza�,
	czy dodawana akcja mie�ci si� w wybranym poziomie zaawansowania
	(funkcjami checkLevel(), lub getLevel())...

	Z poziomem zaawansowania zwi�zana jest r�wnie� szczeg�owo�� opis�w,
	ilo�� u�ywanych wizard�w i informacyjnych okien dialogowych.
	S� one odwrotnie proporcjonalne do wybranej trudno�ci. Pocz�tkuj�cy
	u�ytkownik potrzebuje wi�cej opis�w ustawie�, kt�re mo�e zmieni�.
	Zaawansowanemu mog� one ju� jednak przeszkadza�...
	

	*/
	namespace ShowBits {
		/** Poziomy zaawansowania.
		Ka�dy kolejny poziom zawiera w sobie poprzednie. 
		Dlatego �eby dowiedzie� si� jaki poziom jest aktualnie wybrany - u�ywamy getLevel().
		Najcz�ciej jednak wystarczy sprawdzi�, czy poziom zawiera si� w aktualnie wybranym. Od tego jest funkcja checkLevel().
		*/
		enum enLevel {
			/// Poziom dla pocz�tkuj�cych, tylko @b najbardziej niezb�dne elementy
			levelBeginner =  1,
			levelIntermediate = 3,
			/// Poziom standardowy, ukryte bardziej zaawansowane opcje
			levelNormal = 7,
			/// Poziom zaawansowany, dost�pna wi�kszo�� opcji
			levelAdvanced = 0xF,
			/// Poziom praktycznie najwy�szy
			levelPro = 0x1F,
			levelFull = 0x7F,
		};
		/** Bity wy�wietlania.
		Okre�laj� jakiego rodzaju informacje mo�na wy�wietla�.

		Szczeg�owo�� informacji (showTooltips, showInfo i showWizards)
		stopniowana jest odwrotnie jak w przypadku enLevel. Okre�la dla
		jakich element�w informacje maj� by� wy�wietlane. 

		Na przyk�ad	podczas dobierania tooltipa dla ustawienia podstawowego jak "numerek JID"
		sprawdzamy showTooltipsBeginner. U�ytkownik mniej zaawansowany powinien
		zobaczy� opis ustawienia, ten bardziej - ju� nie. 
		Natomiast przy ustawieniu bardziej zaawansowanym jak "Zas�b/priorytet"
		sprawdzamy showTooltipsNormal. I ukrywamy tip'a tylko przed tymi 
		najbardziej zaawansowanymi (bo showTooltipsNormal zawiera w sobie showTooltipsBeginner, ale nie showTooltipsAdvanced).

		Poziomy	"prostsze" zawieraj� w sobie poziomy bardziej zaawansowane.
		*/
		enum enShowBits {
			showLevel = 0x7F,

			showTooltipsAdvanced = 0x100,
			showTooltipsNormal = 0x300,
			showTooltipsBeginner = 0x700,
			/// Wy�wietlanie tooltip�w (podpowiedzi)
			showTooltips = 0x700,

			showInfoAdvanced = 0x1000,
			showInfoNormal = 0x3000,
			showInfoBeginner = 0x7000,
			/// Wy�wietlanie opis�w (zar�wno opcji jak i okien dialogowych), ich szczeg�owo��
			showInfo = 0x7000,

			showWizardsAdvanced = 0x10000,
			showWizardsNormal = 0x30000,
			showWizardsBeginner = 0x70000,
			/// Cz�stotliwo�� u�ywania wizard�w
			showWizards = 0x70000,

			/// Funkcjonalno�� beta
			showBeta = 0x100000,
		};
		/** Sprawdza czy bit(y) s� ustawione.
		@sa enShowBits*/
		bool checkBits(enShowBits show); 
		/** Zwraca ustawione bity wg. maski.
		@sa enShowBits*/
		enShowBits getBits(int bits);
		/** Sprawdza czy poziom zawiera si� w aktualnie ustawionym.
		@sa enLevel*/
		bool checkLevel(enLevel level);
		/** Zwraca aktualny poziom.
		@sa enLevel*/
		enLevel getLevel();
		unsigned int getAllBits();

		//static int defaultBits = levelBeginner
	}
	/**@}*/

	namespace UI {	
	namespace CFG {
	enum enMsgPopup {
		mpNone = 0,
		mpMinimized = 1,
		mpBackground = 2,
		mpFocused = 3
	};
	enum enMessageHistory {
		mhistDisabled = 0,
		mhistWithCtrl = 1, 
		mhistEnabled = 2
	};
	enum enGroupType {
		gtypeHidden = 0,
		gtypeMenu = 1,
		gtypeToolbar = 2,
	};
	enum enCntListInfo {
		clinfoOff = 0, 
		clinfoInline = 1,
		clinfoMultiline = 2,
		clinfoMultilineWrap = 3
	};
	enum enApplyAutostart {
		autostartLast = 0,
		autostartCurrent = 1,
		autostartCurrentProfile = 2
	};
};
};};

#endif
