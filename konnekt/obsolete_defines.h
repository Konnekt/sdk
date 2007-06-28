#pragma once


//#ifndef KONNEKT_SDK_SUPPRES_OBSOLETE_NOTICE
//#pragma message("Prosze przerobic kod tak, zeby NIE uzywac obsolete_defines.h !!!")
//#endif

/** @addgroup gr_shared 
@{ */

/** @addgroup net_
@{ */


#define NET_FIRST Net::first          ///< WiadomoúÊ dotrze do pierwszej wtyczki (dowolnej sieci), ktÛra potrafi jπ obs≥uøyÊ.
#define NET_BROADCAST Net::broadcast      ///< WiadomoúÊ dotrze do wtyczek wszystkich sieci.
     #define NET_BC NET_BROADCAST  ///< Odpowiednik #NET_BROADCAST.
#define NET_NONE Net::none            ///< Wiadomosci do rdzenia.

#define NET_SOUND Net::sound           ///< DüwiÍk
     #define NET_UPDATE Net::update           ///< Update
     #define NET_OTHER   Net::other         ///< Wtyczki nie posiadajπce akcji, nie obs≥ugujπce wiadomoúci itp.

     #define NET_GG  Net::gg            ///< Wtyczki obs≥ugujπce protokÛ≥ GG
     #define NET_ICQ Net::icq            ///< Wtyczki obs≥ugujπce protokÛ≥ ICQ
     #define NET_JABBER Net::jabber            ///< Wtyczki obs≥ugujπce protokÛ≥ JABBER
     #define NET_EMAIL Net::email            ///< Wtyczki obs≥ugujπce EMaile
     #define NET_SMS Net::sms            ///< Wtyczki obs≥ugujπce SMSy
	 #define NET_KLAN Net::klan 
	 #define NET_KSTYLE Net::kstyle
	 #define NET_EXPIMP Net::expimp
	 #define NET_KONNFERENCJA Net::konnferencja

	 #define NET_AIM    Net::aim            ///< Wtyczki obs≥ugujπce protokÛ≥ AIM
     #define NET_YAHOO  Net::yahoo            ///< Wtyczki obs≥ugujπce protokÛ≥ YAHOO
     #define NET_MSN    Net::msn            ///< Wtyczki obs≥ugujπce protokÛ≥ MSN
     #define NET_TLEN   Net::tlen            ///< Wtyczki obs≥ugujπce protokÛ≥ TLEN
	 

	// sieci tylko do 19 . ich komunikaty to IM_USER + NET * 1000
    // nastÍpne od net 60, tak øeby komunikaty zaczÍ≥y siÍ jako NET * 1000

	 #define NET_KTRANSFER  130 ///< kTransfer 

  // Inne wtyczki
     #define NET_WAPILOT 756       ///< WApilot.dll
	 #define NET_KEASY  227
	 #define NET_KAWAY  666

/** @} */



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
		#define IMT_ALL Konnekt::imtAll
        /// WiadomoúÊ bezpoúrednio do rdzenia (lub UI).
        #define IMT_CORE        Konnekt::imtCore

        /// Wiadomoúci tekstowe.
        #define IMT_MESSAGE     Konnekt::imtMessage
        /// ProtokÛ≥ sieciowy.
        #define IMT_PROTOCOL    Konnekt::imtProtocol
        /// Kontakty.
        #define IMT_CONTACT     Konnekt::imtContact
        /// Konfiguracja.
        #define IMT_CONFIG      Konnekt::imtConfig
        /// Interfejs Uøytkownika (uøywanie wtyczki UI).
        #define IMT_UI          Konnekt::imtUI
        /** Wtyczka obs≥uguje kontakty ca≥ej swojej sieci.
            \attention Ustawienie tego typu spowoduje dodanie nazwy sieci (#IM_PLUG_NETNAME)
            do list sieci w opcjach kontaktu (np. dodawanie , ignorowanie itp.)<br>
            Tylko \b jedna wtyczka z ca≥ej sieci moøe mieÊ ten typ ustawiony!!!
            \sa #IM_PLUG_NETNAME \ref cnt
            */
        #define IMT_NET         Konnekt::imtNet  // Rozpoznaje kontakty danej sieci (podczas dodawania , edycji)
        /** Wtyczka obs≥uguje wyszukiwanie kontaktÛw w swojej sieci.
            \attention Podobnie jak w #IMT_UI Ustawienie tego typu spowoduje dodanie nazwy sieci (#IM_PLUG_NETNAME)
            do list sieci w wyszukiwarce kontaktÛw<br>
            Tylko \b jedna wtyczka z ca≥ej sieci moøe mieÊ ten typ ustawiony!!!
            \sa #IM_PLUG_NETNAME \ref cnt
            */
        #define IMT_NETSEARCH   Konnekt::imtNetSearch
        /// Wtyczka wykorzystuje system obs≥ugi wiadomoúci tekstowych zawarty w UI.
        #define IMT_MSGUI       Konnekt::imtMsgUI
        /// Kontakty w sieci posiadajπ UID (UserID)
        #define IMT_NETUID      Konnekt::imtNetUID
        /// Otrzyma w IM_MSG_RCV wszystkie wiadomoùci , niezale¨nie od \ref net_ "NET".
        #define IMT_ALLMESSAGES Konnekt::imtAllMessages
        /// BÍdzie otrzymywaÊ IM_MSG_ACK.
        #define IMT_MESSAGEACK Konnekt::imtMessageAck
        /** \} */ // imt_


	typedef enPluginPriority PLUGP_enum;

    /** Grupy priorytetÛw dla #IM_PLUG_PRIORITY */
	const PLUGP_enum PLUGP_LOWEST = Konnekt::priorityLowest;
    const PLUGP_enum PLUGP_LOW = Konnekt::priorityLow;
	const PLUGP_enum PLUGP_STANDARD = Konnekt::priorityStandard;
	const PLUGP_enum PLUGP_HIGH = Konnekt::priorityHigh;
	const PLUGP_enum PLUGP_HIGHEST = Konnekt::priorityHighest;
    const PLUGP_enum PLUGP_NONE = Konnekt::priorityNone;



  /**
    \defgroup imerror_ Kody b≥edu
    \brief \no

    \{
  */

#define IMERROR_NORESULT Konnekt::errorNoResult   ///< Wtyczka nie obs≥uøy≥a wiadomoúci.
  #define IMERROR_UNSUPPORTEDMSG IMERROR_NORESULT /// \no
  #define IMERROR_BADSENDER Konnekt::errorBadSender  ///< WiadomoúÊ wstrzymana, pojawi≥ siÍ b≥πd...
  #define IMERROR_BADPLUG Konnekt::errorBadPlugin    ///< Podana wtyczka nie istnieje.
  #define IMERROR_THREADSAFE Konnekt::errorThreadSafe ///< WiadomoúÊ zosta≥a wywo≥ana w trybie bezpiecznym (bez oczekiwania na powrÛt).
  #define IMERROR_SHUTDOWN Konnekt::errorShutdown   ///< WiadomoúÊ zosta≥a anulowana z powodu zamykania programu.
  #define IMERROR_BADPARAM Konnekt::errorBadParam   ///< Nieprawid≥owe parametry.
  #define IMERROR_BADSTRUCT Konnekt::errorBadStruct   ///< Niepoprawna struktura.

  /** @} */ // imerror_


/*
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
	*/

#ifdef KONNEKT_OBSOLETE_ALL

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

#endif

/** @} */



#define IMC_NEWMESSAGE     Message::imcNewMessage

#define IMC_MESSAGEQUEUE   imcMessageQueue 
        #define IMC_MESSAGENOTIFY  
        #define IMC_MESSAGEWAITING 103 ///< 
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


         /** Wtyczka powinna sprawdziÊ czy obs≥uguje dany typ wiadomoúci.
           Wtyczki odpytywane sπ "od koÒca". Ostatnia, ktÛra zwrÛci
           IM_MSG_RCV_ok bÍdzie otrzymywaÊ rÛwnieø IM_MSG_OPEN.
           \param p1 (cMessage *) wiadomoúÊ.
           \param p2 (bool) \i true - wiadomoúÊ w≥aúnie przysz≥a , \i false - wiadomoúÊ zosta≥a za≥adowana z pliku.
           \return (int) Po≥πczone flagi \ref im_msg_, lub 0 jeúli nie obs≥uguje takich wiadomoúci.
         */
		 #define IM_MSG_RCV       IM_BASE+100

		 /** WiadomoúÊ powinna zostaÊ wys≥ana.
           \param p1 (cMessage *) WiadomoúÊ
           \return Jeúli siÍ uda≥o powinno zrÛciÊ \ref im_msg_.
         */
		 #define IM_MSG_SEND      IM_SHARE+100 
		 
		 /** WiadomoúÊ powinna zostaÊ otwarta.
           \param p1 (cMessage *) WiadomoúÊ
           \return Jeúli siÍ uda≥o powinno zrÛciÊ \ref im_msg_.
         */
		 #define IM_MSG_OPEN      IM_SHARE+101  