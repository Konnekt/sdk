#pragma once

namespace Konnekt {

	/** 
	Kaøda wtyczka powinna zdefiniowaÊ jakiego typu #IMessage potrafi
    przyjπÊ (konkretniej - za co ma odpowiadaÊ).<br><br>
    Typy moøna ≥πczyÊ poprzez '|' (OR). <br><br>
    IMessage() wywo≥any z \a typem innym od #IMT_ALL zostanie
    wys≥any tylko do wtyczek z zadeklarowanπ obs≥ugπ wybranego \a typu.

    \sa #IM_PLUG_NET IMessage()

	@todo zaktualizowaÊ :)
	*/
	enum enIMessageType {
		
        imtAll = 0xFFFFFFFF,

        /// WiadomoúÊ bezpoúrednio do rdzenia (lub UI).
        imtCore = 0,

        /// Wiadomoúci tekstowe.
        imtMessage = 1,
        /// ProtokÛ≥ sieciowy.
        imtProtocol = 2,
        /// Kontakty.
        imtContact = 4,
        /// Konfiguracja.
        imtConfig = 8,
        /// Interfejs Uøytkownika (uøywanie wtyczki UI).
        imtUI = 0x10,
        /** Wtyczka obs≥uguje kontakty ca≥ej swojej sieci.
            \attention Ustawienie tego typu spowoduje dodanie nazwy sieci (#IM_PLUG_NETNAME)
            do list sieci w opcjach kontaktu (np. dodawanie , ignorowanie itp.)<br>
            Tylko \b jedna wtyczka z ca≥ej sieci moøe mieÊ ten typ ustawiony!!!
            \sa #IM_PLUG_NETNAME \ref cnt
            */
        imtNet = 0x20,  // Rozpoznaje kontakty danej sieci (podczas dodawania , edycji)
        /** Wtyczka obs≥uguje wyszukiwanie kontaktÛw w swojej sieci.
            \attention Podobnie jak w #IMT_UI Ustawienie tego typu spowoduje dodanie nazwy sieci (#IM_PLUG_NETNAME)
            do list sieci w wyszukiwarce kontaktÛw<br>
            Tylko \b jedna wtyczka z ca≥ej sieci moøe mieÊ ten typ ustawiony!!!
            \sa #IM_PLUG_NETNAME \ref cnt
            */
        imtNetSearch = 0x40,
        /// Wtyczka wykorzystuje system obs≥ugi wiadomoúci tekstowych zawarty w UI.
        imtMsgUI = 0x80,
        /// Kontakty w sieci posiadajπ UID (UserID)
        imtNetUID = 0x100,
        /// Otrzyma w IM_MSG_RCV wszystkie wiadomoùci , niezale¨nie od \ref net_ "NET".
        imtAllMessages = 0x200,
        /// BÍdzie otrzymywaÊ IM_MSG_ACK.
        imtMessageAck = 0x400


	};


	inline enIMessageType operator | (enIMessageType& a, enIMessageType& b) {
		return (enIMessageType)(a | b);
	}


};