#pragma once


//#ifndef KONNEKT_SDK_SUPPRES_OBSOLETE_NOTICE
//#pragma message("Prosze przerobic kod tak, zeby NIE uzywac obsolete_defines.h !!!")
//#endif

/** @addgroup gr_shared 
@{ */

/** @addgroup net_
@{ */


#define NET_FIRST Net::first          ///< Wiadomo�� dotrze do pierwszej wtyczki (dowolnej sieci), kt�ra potrafi j� obs�u�y�.
#define NET_BROADCAST Net::broadcast      ///< Wiadomo�� dotrze do wtyczek wszystkich sieci.
     #define NET_BC NET_BROADCAST  ///< Odpowiednik #NET_BROADCAST.
#define NET_NONE Net::none            ///< Wiadomosci do rdzenia.

#define NET_SOUND Net::sound           ///< D�wi�k
     #define NET_UPDATE Net::update           ///< Update
     #define NET_OTHER   Net::other         ///< Wtyczki nie posiadaj�ce akcji, nie obs�uguj�ce wiadomo�ci itp.

     #define NET_GG  Net::gg            ///< Wtyczki obs�uguj�ce protok� GG
     #define NET_ICQ Net::icq            ///< Wtyczki obs�uguj�ce protok� ICQ
     #define NET_JABBER Net::jabber            ///< Wtyczki obs�uguj�ce protok� JABBER
     #define NET_EMAIL Net::email            ///< Wtyczki obs�uguj�ce EMaile
     #define NET_SMS Net::sms            ///< Wtyczki obs�uguj�ce SMSy
	 #define NET_KLAN Net::klan 
	 #define NET_KSTYLE Net::kstyle
	 #define NET_EXPIMP Net::expimp
	 #define NET_KONNFERENCJA Net::konnferencja

	 #define NET_AIM    Net::aim            ///< Wtyczki obs�uguj�ce protok� AIM
     #define NET_YAHOO  Net::yahoo            ///< Wtyczki obs�uguj�ce protok� YAHOO
     #define NET_MSN    Net::msn            ///< Wtyczki obs�uguj�ce protok� MSN
     #define NET_TLEN   Net::tlen            ///< Wtyczki obs�uguj�ce protok� TLEN
	 

	// sieci tylko do 19 . ich komunikaty to IM_USER + NET * 1000
    // nast�pne od net 60, tak �eby komunikaty zacz�y si� jako NET * 1000

	 #define NET_KTRANSFER  130 ///< kTransfer 

  // Inne wtyczki
     #define NET_WAPILOT 756       ///< WApilot.dll
	 #define NET_KEASY  227
	 #define NET_KAWAY  666

/** @} */



  // Typy IMessage

// -----------------------------------------------------------------------------------------------
  /** \defgroup imt_ Definicje typ�w IMessage ...
    \brief \no

    Ka�da wtyczka powinna zdefiniowa� jakiego typu #IMessage potrafi
    przyj�� (konkretniej - za co ma odpowiada�).<br><br>
    Typy mo�na ��czy� poprzez '|' (OR). <br><br>
    IMessage() wywo�any z \a typem innym od #IMT_ALL zostanie
    wys�any tylko do wtyczek z zadeklarowan� obs�ug� wybranego \a typu.

    \sa #IM_PLUG_NET IMessage()
    \{
  */
        typedef unsigned int tIMtype;

        /// Wszystkie typy.
		#define IMT_ALL Konnekt::imtAll
        /// Wiadomo�� bezpo�rednio do rdzenia (lub UI).
        #define IMT_CORE        Konnekt::imtCore

        /// Wiadomo�ci tekstowe.
        #define IMT_MESSAGE     Konnekt::imtMessage
        /// Protok� sieciowy.
        #define IMT_PROTOCOL    Konnekt::imtProtocol
        /// Kontakty.
        #define IMT_CONTACT     Konnekt::imtContact
        /// Konfiguracja.
        #define IMT_CONFIG      Konnekt::imtConfig
        /// Interfejs U�ytkownika (u�ywanie wtyczki UI).
        #define IMT_UI          Konnekt::imtUI
        /** Wtyczka obs�uguje kontakty ca�ej swojej sieci.
            \attention Ustawienie tego typu spowoduje dodanie nazwy sieci (#IM_PLUG_NETNAME)
            do list sieci w opcjach kontaktu (np. dodawanie , ignorowanie itp.)<br>
            Tylko \b jedna wtyczka z ca�ej sieci mo�e mie� ten typ ustawiony!!!
            \sa #IM_PLUG_NETNAME \ref cnt
            */
        #define IMT_NET         Konnekt::imtNet  // Rozpoznaje kontakty danej sieci (podczas dodawania , edycji)
        /** Wtyczka obs�uguje wyszukiwanie kontakt�w w swojej sieci.
            \attention Podobnie jak w #IMT_UI Ustawienie tego typu spowoduje dodanie nazwy sieci (#IM_PLUG_NETNAME)
            do list sieci w wyszukiwarce kontakt�w<br>
            Tylko \b jedna wtyczka z ca�ej sieci mo�e mie� ten typ ustawiony!!!
            \sa #IM_PLUG_NETNAME \ref cnt
            */
        #define IMT_NETSEARCH   Konnekt::imtNetSearch
        /// Wtyczka wykorzystuje system obs�ugi wiadomo�ci tekstowych zawarty w UI.
        #define IMT_MSGUI       Konnekt::imtMsgUI
        /// Kontakty w sieci posiadaj� UID (UserID)
        #define IMT_NETUID      Konnekt::imtNetUID
        /// Otrzyma w IM_MSG_RCV wszystkie wiadomo�ci , niezale�nie od \ref net_ "NET".
        #define IMT_ALLMESSAGES Konnekt::imtAllMessages
        /// B�dzie otrzymywa� IM_MSG_ACK.
        #define IMT_MESSAGEACK Konnekt::imtMessageAck
        /** \} */ // imt_


	typedef enPluginPriority PLUGP_enum;

    /** Grupy priorytet�w dla #IM_PLUG_PRIORITY */
	const PLUGP_enum PLUGP_LOWEST = Konnekt::priorityLowest;
    const PLUGP_enum PLUGP_LOW = Konnekt::priorityLow;
	const PLUGP_enum PLUGP_STANDARD = Konnekt::priorityStandard;
	const PLUGP_enum PLUGP_HIGH = Konnekt::priorityHigh;
	const PLUGP_enum PLUGP_HIGHEST = Konnekt::priorityHighest;
    const PLUGP_enum PLUGP_NONE = Konnekt::priorityNone;



  /**
    \defgroup imerror_ Kody b�edu
    \brief \no

    \{
  */

#define IMERROR_NORESULT Konnekt::errorNoResult   ///< Wtyczka nie obs�u�y�a wiadomo�ci.
  #define IMERROR_UNSUPPORTEDMSG IMERROR_NORESULT /// \no
  #define IMERROR_BADSENDER Konnekt::errorBadSender  ///< Wiadomo�� wstrzymana, pojawi� si� b��d...
  #define IMERROR_BADPLUG Konnekt::errorBadPlugin    ///< Podana wtyczka nie istnieje.
  #define IMERROR_THREADSAFE Konnekt::errorThreadSafe ///< Wiadomo�� zosta�a wywo�ana w trybie bezpiecznym (bez oczekiwania na powr�t).
  #define IMERROR_SHUTDOWN Konnekt::errorShutdown   ///< Wiadomo�� zosta�a anulowana z powodu zamykania programu.
  #define IMERROR_BADPARAM Konnekt::errorBadParam   ///< Nieprawid�owe parametry.
  #define IMERROR_BADSTRUCT Konnekt::errorBadStruct   ///< Niepoprawna struktura.

  /** @} */ // imerror_


/*
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
	*/

#ifdef KONNEKT_OBSOLETE_ALL

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

#endif

/** @} */



#define IMC_NEWMESSAGE     Message::imcNewMessage

#define IMC_MESSAGEQUEUE   imcMessageQueue 
        #define IMC_MESSAGENOTIFY  
        #define IMC_MESSAGEWAITING 103 ///< 
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


         /** Wtyczka powinna sprawdzi� czy obs�uguje dany typ wiadomo�ci.
           Wtyczki odpytywane s� "od ko�ca". Ostatnia, kt�ra zwr�ci
           IM_MSG_RCV_ok b�dzie otrzymywa� r�wnie� IM_MSG_OPEN.
           \param p1 (cMessage *) wiadomo��.
           \param p2 (bool) \i true - wiadomo�� w�a�nie przysz�a , \i false - wiadomo�� zosta�a za�adowana z pliku.
           \return (int) Po��czone flagi \ref im_msg_, lub 0 je�li nie obs�uguje takich wiadomo�ci.
         */
		 #define IM_MSG_RCV       IM_BASE+100

		 /** Wiadomo�� powinna zosta� wys�ana.
           \param p1 (cMessage *) Wiadomo��
           \return Je�li si� uda�o powinno zr�ci� \ref im_msg_.
         */
		 #define IM_MSG_SEND      IM_SHARE+100 
		 
		 /** Wiadomo�� powinna zosta� otwarta.
           \param p1 (cMessage *) Wiadomo��
           \return Je�li si� uda�o powinno zr�ci� \ref im_msg_.
         */
		 #define IM_MSG_OPEN      IM_SHARE+101  