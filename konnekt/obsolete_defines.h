#pragma once


//#ifndef KONNEKT_SDK_SUPPRES_OBSOLETE_NOTICE
//#pragma message("Prosze przerobic kod tak, zeby NIE uzywac obsolete_defines.h !!!")
//#endif

/** @addgroup gr_shared 
@{ */

/** @addgroup net_
@{ */


     #define NET_FIRST -2          ///< Wiadomo�� dotrze do pierwszej wtyczki (dowolnej sieci), kt�ra potrafi j� obs�u�y�.
     #define NET_BROADCAST -1      ///< Wiadomo�� dotrze do wtyczek wszystkich sieci.
     #define NET_BC NET_BROADCAST  ///< Odpowiednik #NET_BROADCAST.
     #define NET_NONE 0            ///< Wiadomosci do rdzenia.
     #define NET_NET 1             ///< Wtyczki obs�uguj�ce protok� "w�asny".
     #define NET_INTERNAL 2
     #define NET_SOUND 3           ///< D�wi�k
     #define NET_UPDATE 4           ///< Update
     #define NET_OTHER   6         ///< Wtyczki nie posiadaj�ce akcji, nie obs�uguj�ce wiadomo�ci itp.

     #define NET_GG  10            ///< Wtyczki obs�uguj�ce protok� GG
     #define NET_ICQ 11            ///< Wtyczki obs�uguj�ce protok� ICQ
     #define NET_JABBER 12            ///< Wtyczki obs�uguj�ce protok� JABBER
     #define NET_EMAIL 13            ///< Wtyczki obs�uguj�ce EMaile
     #define NET_SMS 14            ///< Wtyczki obs�uguj�ce SMSy
	 #define NET_KLAN 15 
	 #define NET_KSTYLE 16
	 #define NET_EXPIMP 17
	 #define NET_KONNFERENCJA 20

	 #define NET_AIM    60            ///< Wtyczki obs�uguj�ce protok� AIM
     #define NET_YAHOO  61            ///< Wtyczki obs�uguj�ce protok� YAHOO
     #define NET_MSN    62            ///< Wtyczki obs�uguj�ce protok� MSN
     #define NET_TLEN   63            ///< Wtyczki obs�uguj�ce protok� TLEN
	 

	// sieci tylko do 19 . ich komunikaty to IM_USER + NET * 1000
    // nast�pne od net 60, tak �eby komunikaty zacz�y si� jako NET * 1000

	 #define NET_KTRANSFER  130 ///< kTransfer 

  // Inne wtyczki
     #define NET_WAPILOT 756       ///< WApilot.dll
	 #define NET_KEASY  227
	 #define NET_KAWAY  666

/** @} */

/** @} */
