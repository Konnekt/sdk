#pragma once

namespace Konnekt {

	/** 
	Ka�da wtyczka powinna zdefiniowa� jakiego typu #IMessage potrafi
    przyj�� (konkretniej - za co ma odpowiada�).<br><br>
    Typy mo�na ��czy� poprzez '|' (OR). <br><br>
    IMessage() wywo�any z \a typem innym od #IMT_ALL zostanie
    wys�any tylko do wtyczek z zadeklarowan� obs�ug� wybranego \a typu.

    \sa #IM_PLUG_NET IMessage()

	@todo zaktualizowa� :)
	*/
	enum enIMessageType {
		
        imtAll = 0xFFFFFFFF,

        /// Wiadomo�� bezpo�rednio do rdzenia (lub UI).
        imtCore = 0,

        /// Wiadomo�ci tekstowe.
        imtMessage = 1,
        /// Protok� sieciowy.
        imtProtocol = 2,
        /// Kontakty.
        imtContact = 4,
        /// Konfiguracja.
        imtConfig = 8,
        /// Interfejs U�ytkownika (u�ywanie wtyczki UI).
        imtUI = 0x10,
        /** Wtyczka obs�uguje kontakty ca�ej swojej sieci.
            \attention Ustawienie tego typu spowoduje dodanie nazwy sieci (#IM_PLUG_NETNAME)
            do list sieci w opcjach kontaktu (np. dodawanie , ignorowanie itp.)<br>
            Tylko \b jedna wtyczka z ca�ej sieci mo�e mie� ten typ ustawiony!!!
            \sa #IM_PLUG_NETNAME \ref cnt
            */
        imtNet = 0x20,  // Rozpoznaje kontakty danej sieci (podczas dodawania , edycji)
        /** Wtyczka obs�uguje wyszukiwanie kontakt�w w swojej sieci.
            \attention Podobnie jak w #IMT_UI Ustawienie tego typu spowoduje dodanie nazwy sieci (#IM_PLUG_NETNAME)
            do list sieci w wyszukiwarce kontakt�w<br>
            Tylko \b jedna wtyczka z ca�ej sieci mo�e mie� ten typ ustawiony!!!
            \sa #IM_PLUG_NETNAME \ref cnt
            */
        imtNetSearch = 0x40,
        /// Wtyczka wykorzystuje system obs�ugi wiadomo�ci tekstowych zawarty w UI.
        imtMsgUI = 0x80,
        /// Kontakty w sieci posiadaj� UID (UserID)
        imtNetUID = 0x100,
        /// Otrzyma w IM_MSG_RCV wszystkie wiadomo�ci , niezale�nie od \ref net_ "NET".
        imtAllMessages = 0x200,
        /// B�dzie otrzymywa� IM_MSG_ACK.
        imtMessageAck = 0x400


	};


	inline enIMessageType operator | (enIMessageType& a, enIMessageType& b) {
		return (enIMessageType)(a | b);
	}


};