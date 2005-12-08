#pragma once

namespace Konnekt {

	/**
      "Sieæ" (Net) wtyczki oznacza przynale¿noœæ do pewnej grupy.
      Na przyk³ad jeden protokó³ mo¿e byæ obs³ugiwany przez kilka niezale¿nych
      od siebie wtyczek o tej samej wartoœci \a Net. <br> <br>
      Wartoœæ sieci u¿ywana jest przede wszystkim podczas komunikacji
      pomiêdzy wtyczkami. W momencie wys³ania #IMessage , rdzeñ
      szuka wtyczki o podanej wartoœci \a Net obs³uguj¹cej typ wysy³anej
      wiadomoœci. W ten sposób , mo¿na rozsy³aæ w systemie wiadomoœci
      do \i wtyczek nawet nie wiedz¹c o ich istnieniu (a przede wszystkim
      o ich identyfikatorach) ...<br><br>
      Numery sieci gotowych wtyczek bêd¹ do³¹czane do SDK...

      \attention \a Net jest typu <b>unsigned int</b> , przy czym
              wartoœci definiowane przez Was powinny byæ wiêksze od @b 255!
			  Wartoœci od 128-255 powinny byæ WOLNE
      \sa info imt_ #IM_PLUG_NET
	
@todo Zaktualizowaæ :)

	*/
	namespace Net {

		enum tNet {

			first = -2,		///< Komunikat dotrze do pierwszej wtyczki (dowolnej sieci), która potrafi j¹ obs³u¿yæ.
			broadcast = -1, ///< Komunikat dotrze do wtyczek wszystkich sieci.
		    none = 0,       ///< Wiadomosci do rdzenia.
			//net = 1,  
			//internal = 2,
			sound = 3,      ///< DŸwiêk
			update = 4,     ///< Update
			other = 6,      ///< Wtyczki nie posiadaj¹ce akcji, nie obs³uguj¹ce wiadomoœci itp.

			gg = 10,        ///< Wtyczki obs³uguj¹ce protokó³ GG
			icq = 11,       ///< Wtyczki obs³uguj¹ce protokó³ ICQ
			jabber = 12,    ///< Wtyczki obs³uguj¹ce protokó³ JABBER
			email = 13,     ///< Wtyczki obs³uguj¹ce EMaile
			sms = 14,       ///< Wtyczki obs³uguj¹ce SMSy
			klan = 15,
			kstyle = 16,
			expimp = 17,
			konnferencja = 20,

			aim = 60,       ///< Wtyczki obs³uguj¹ce protokó³ AIM
			yahoo = 61,     ///< Wtyczki obs³uguj¹ce protokó³ YAHOO
			msn = 62,       ///< Wtyczki obs³uguj¹ce protokó³ MSN
			tlen = 63,      ///< Wtyczki obs³uguj¹ce protokó³ TLEN
	 

			ktransfer = 130,///< kTransfer 
		};
	};

	using Net::tNet;

};


