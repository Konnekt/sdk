#pragma once

namespace Konnekt {

	/**
      "Sie�" (Net) wtyczki oznacza przynale�no�� do pewnej grupy.
      Na przyk�ad jeden protok� mo�e by� obs�ugiwany przez kilka niezale�nych
      od siebie wtyczek o tej samej warto�ci \a Net. <br> <br>
      Warto�� sieci u�ywana jest przede wszystkim podczas komunikacji
      pomi�dzy wtyczkami. W momencie wys�ania #IMessage , rdze�
      szuka wtyczki o podanej warto�ci \a Net obs�uguj�cej typ wysy�anej
      wiadomo�ci. W ten spos�b , mo�na rozsy�a� w systemie wiadomo�ci
      do \i wtyczek nawet nie wiedz�c o ich istnieniu (a przede wszystkim
      o ich identyfikatorach) ...<br><br>
      Numery sieci gotowych wtyczek b�d� do��czane do SDK...

      \attention \a Net jest typu <b>unsigned int</b> , przy czym
              warto�ci definiowane przez Was powinny by� wi�ksze od @b 255!
			  Warto�ci od 128-255 powinny by� WOLNE
      \sa info imt_ #IM_PLUG_NET
	
@todo Zaktualizowa� :)

	*/
	namespace Net {

		enum tNet {

			first = -2,		///< Komunikat dotrze do pierwszej wtyczki (dowolnej sieci), kt�ra potrafi j� obs�u�y�.
			broadcast = -1, ///< Komunikat dotrze do wtyczek wszystkich sieci.
		    none = 0,       ///< Wiadomosci do rdzenia.
			//net = 1,  
			//internal = 2,
			sound = 3,      ///< D�wi�k
			update = 4,     ///< Update
			other = 6,      ///< Wtyczki nie posiadaj�ce akcji, nie obs�uguj�ce wiadomo�ci itp.

			gg = 10,        ///< Wtyczki obs�uguj�ce protok� GG
			icq = 11,       ///< Wtyczki obs�uguj�ce protok� ICQ
			jabber = 12,    ///< Wtyczki obs�uguj�ce protok� JABBER
			email = 13,     ///< Wtyczki obs�uguj�ce EMaile
			sms = 14,       ///< Wtyczki obs�uguj�ce SMSy
			klan = 15,
			kstyle = 16,
			expimp = 17,
			konnferencja = 20,

			aim = 60,       ///< Wtyczki obs�uguj�ce protok� AIM
			yahoo = 61,     ///< Wtyczki obs�uguj�ce protok� YAHOO
			msn = 62,       ///< Wtyczki obs�uguj�ce protok� MSN
			tlen = 63,      ///< Wtyczki obs�uguj�ce protok� TLEN
	 

			ktransfer = 130,///< kTransfer 
		};
	};

	using Net::tNet;

};


