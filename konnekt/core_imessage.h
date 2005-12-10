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
        imtNone = 0,

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

	enum enIMessageFlag {

		imfRecalling = 1, /// 
		imfRecalled = 2,

	};

	inline enIMessageFlag operator | (enIMessageFlag& a, enIMessageFlag& b) {
		return (enIMessageFlag)(a | b);
	}


	enum enIMessageError {

		errorNone = 0,
		errorNoResult = 1, ///< Wtyczka nie obs�u�y�a wiadomo�ci.
		errorUnsupportedMsg = 1,
		errorBadSender = 2, ///< Wiadomo�� wstrzymana, pojawi� si� b��d...
		errorBadPlugin = 3, ///< Podana wtyczka nie istnieje.
		errorThreadSafe = 4, ///< Wiadomo�� zosta�a wywo�ana w trybie bezpiecznym (bez oczekiwania na powr�t).
		errorShutdown = 5, ///< Wiadomo�� zosta�a anulowana z powodu zamykania programu.
		errorBadParam = 6, ///< Nieprawid�owe parametry.
		errorBadStruct = 7, ///< Niepoprawna struktura.

	};


/** Struktura u�ywana podczas przesy�ania wiadomo�ci.
    Jest u�ywana jako bazowa dla wi�kszych struktur...
  */
  struct sIMessage_base {
    unsigned short s_size; ///< Rozmiar struktury w bajtach (zazwyczaj ustawiane przez kontruktor)
    unsigned int id;   ///< Identyfikator wiadomo�ci
    enIMessageFlag flag; ///< Flaga wiadomo�ci (na razie powinno by� zawsze r�wne 0)
    tNet net;  ///< Docelowa sie�. 0 - rdze� lub UI
    enIMessageType type; ///< Docelowy typ wtyczek
    tPluginId sender; ///< Identyfikator wtyczki wysy�aj�cej
	sIMessage_base(unsigned int _id, tNet _net, enIMessageType _type)
        :s_size(sizeof(sIMessage_base)),id(_id),net(_net),type(_type),sender(pluginNotFound),flag(0) {}
    sIMessage_base() 
		:s_size(sizeof(sIMessage_base)),id(0),net(Net::none),type(imtNone),sender(pluginNotFound),flag(0) {}
    sIMessage_base(unsigned int _id)
		:s_size(sizeof(sIMessage_base)),id(_id),net(Net::none),type(imtNone),sender(pluginNotFound),flag(0) {}
    sIMessage_base(sIMessage_base * base) {*this = *base;}


  };
  /** Struktura u�ywana podczas przesy�ania wiadomo�ci.
    Mo�e by� struktur� bazow� dla wi�kszych struktur ...
    p1 i p2 mog� by� zast�pione dowolnymi typami, najlepiej o
    rozmiarze po 4 bajty ...
  */
  struct sIMessage_2params: public sIMessage_base {
    IMPARAM p1;   ///< Parametr pierwszy
    IMPARAM p2;   ///< Parametr drugi

    sIMessage_2params(unsigned int _id, tNet _net, enIMessageType _type, IMPARAM _p1, IMPARAM _p2)
        :sIMessage_base(_id , _net, _type), p1(_p1),p2(_p2) {s_size=sizeof(sIMessage_2params);}
    sIMessage_2params()
        :sIMessage_base(), p1(0),p2(0) {s_size=sizeof(sIMessage_2params);}
    sIMessage_2params(unsigned int _id, IMPARAM _p1, IMPARAM _p2) 
        :sIMessage_base(_id), p1(_p1),p2(_p2) {s_size=sizeof(sIMessage_2params);}
    sIMessage_2params(sIMessage_base &base) 
        :sIMessage_base(base.id , base.net , base.type), p1(0),p2(0) 
        {s_size=sizeof(sIMessage_2params);
         this->flag = base.flag;
         this->sender = base.sender;}
  };
  typedef sIMessage_2params sIMessage;
  typedef sIMessage sIMESSAGE;
  #define sIMessage_V1 30 ///< Rozmiar tej struktury w wersji 1 SDK





};