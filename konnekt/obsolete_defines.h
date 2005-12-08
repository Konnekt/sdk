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
        #define IMT_ALL 0xFFFFFFFF
        /// Wiadomo�� bezpo�rednio do rdzenia (lub UI).
        #define IMT_CORE        0

        /// Wiadomo�ci tekstowe.
        #define IMT_MESSAGE     1
        /// Protok� sieciowy.
        #define IMT_PROTOCOL    2
        /// Kontakty.
        #define IMT_CONTACT     4
        /// Konfiguracja.
        #define IMT_CONFIG      8
        /// Interfejs U�ytkownika (u�ywanie wtyczki UI).
        #define IMT_UI          0x10
        /** Wtyczka obs�uguje kontakty ca�ej swojej sieci.
            \attention Ustawienie tego typu spowoduje dodanie nazwy sieci (#IM_PLUG_NETNAME)
            do list sieci w opcjach kontaktu (np. dodawanie , ignorowanie itp.)<br>
            Tylko \b jedna wtyczka z ca�ej sieci mo�e mie� ten typ ustawiony!!!
            \sa #IM_PLUG_NETNAME \ref cnt
            */
        #define IMT_NET         0x20  // Rozpoznaje kontakty danej sieci (podczas dodawania , edycji)
        /** Wtyczka obs�uguje wyszukiwanie kontakt�w w swojej sieci.
            \attention Podobnie jak w #IMT_UI Ustawienie tego typu spowoduje dodanie nazwy sieci (#IM_PLUG_NETNAME)
            do list sieci w wyszukiwarce kontakt�w<br>
            Tylko \b jedna wtyczka z ca�ej sieci mo�e mie� ten typ ustawiony!!!
            \sa #IM_PLUG_NETNAME \ref cnt
            */
        #define IMT_NETSEARCH   0x40
        /// Wtyczka wykorzystuje system obs�ugi wiadomo�ci tekstowych zawarty w UI.
        #define IMT_MSGUI       0x80
        /// Kontakty w sieci posiadaj� UID (UserID)
        #define IMT_NETUID      0x100
        /// Otrzyma w IM_MSG_RCV wszystkie wiadomo�ci , niezale�nie od \ref net_ "NET".
        #define IMT_ALLMESSAGES 0x200
        /// B�dzie otrzymywa� IM_MSG_ACK.
        #define IMT_MESSAGEACK 0x400
        /** \} */ // imt_


	typedef enPluginPriority PLUGP_enum;

    /** Grupy priorytet�w dla #IM_PLUG_PRIORITY */
	const PLUGP_enum PLUGP_LOWEST = Konnekt::priorityLowest;
    const PLUGP_enum PLUGP_LOW = Konnekt::priorityLow;
	const PLUGP_enum PLUGP_STANDARD = Konnekt::priorityStandard;
	const PLUGP_enum PLUGP_HIGH = Konnekt::priorityHigh;
	const PLUGP_enum PLUGP_HIGHEST = Konnekt::priorityHighest;
    const PLUGP_enum PLUGP_NONE = Konnekt::priorityNone;


/** @} */
