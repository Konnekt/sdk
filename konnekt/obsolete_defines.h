#pragma once


//#ifndef KONNEKT_SDK_SUPPRES_OBSOLETE_NOTICE
//#pragma message("Prosze przerobic kod tak, zeby NIE uzywac obsolete_defines.h !!!")
//#endif

/** @addgroup gr_shared 
@{ */

/** @addgroup net_
@{ */


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


	typedef enPlugPriority PLUGP_enum;

     /** Grupy priorytetÛw dla #IM_PLUG_PRIORITY */
	const PLUGP_enum PLUGP_LOWEST = Konnekt::priorityLowest;
     const PLUGP_enum PLUGP_LOW = Konnekt::priorityLow;
	 const PLUGP_enum PLUGP_STANDARD = Konnekt::priorityStandard;
	 const PLUGP_enum PLUGP_HIGH = Konnekt::priorityHigh;
	 const PLUGP_enum PLUGP_HIGHEST = Konnekt::priorityHighest;
     const PLUGP_enum PLUGP_NONE = Konnekt::priorityNone;


/** @} */
