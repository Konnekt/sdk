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
        imtNone = 0,

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

	enum enIMessageFlag {

		imfRecalling = 1, /// 
		imfRecalled = 2,

	};

	inline enIMessageFlag operator | (enIMessageFlag& a, enIMessageFlag& b) {
		return (enIMessageFlag)(a | b);
	}


	enum enIMessageError {

		errorNone = 0,
		errorNoResult = 1, ///< Wtyczka nie obs≥uøy≥a wiadomoúci.
		errorUnsupportedMsg = 1,
		errorBadSender = 2, ///< WiadomoúÊ wstrzymana, pojawi≥ siÍ b≥πd...
		errorBadPlugin = 3, ///< Podana wtyczka nie istnieje.
		errorThreadSafe = 4, ///< WiadomoúÊ zosta≥a wywo≥ana w trybie bezpiecznym (bez oczekiwania na powrÛt).
		errorShutdown = 5, ///< WiadomoúÊ zosta≥a anulowana z powodu zamykania programu.
		errorBadParam = 6, ///< Nieprawid≥owe parametry.
		errorBadStruct = 7, ///< Niepoprawna struktura.

	};


/** Struktura uøywana podczas przesy≥ania wiadomoúci.
    Jest uøywana jako bazowa dla wiÍkszych struktur...
  */
  struct sIMessage_base {
    unsigned short s_size; ///< Rozmiar struktury w bajtach (zazwyczaj ustawiane przez kontruktor)
    unsigned int id;   ///< Identyfikator wiadomoúci
    enIMessageFlag flag; ///< Flaga wiadomoúci (na razie powinno byÊ zawsze rÛwne 0)
    tNet net;  ///< Docelowa sieÊ. 0 - rdzeÒ lub UI
    enIMessageType type; ///< Docelowy typ wtyczek
    tPluginId sender; ///< Identyfikator wtyczki wysy≥ajπcej
	sIMessage_base(unsigned int _id, tNet _net, enIMessageType _type)
        :s_size(sizeof(sIMessage_base)),id(_id),net(_net),type(_type),sender(pluginNotFound),flag(0) {}
    sIMessage_base() 
		:s_size(sizeof(sIMessage_base)),id(0),net(Net::none),type(imtNone),sender(pluginNotFound),flag(0) {}
    sIMessage_base(unsigned int _id)
		:s_size(sizeof(sIMessage_base)),id(_id),net(Net::none),type(imtNone),sender(pluginNotFound),flag(0) {}
    sIMessage_base(sIMessage_base * base) {*this = *base;}


  };
  /** Struktura uøywana podczas przesy≥ania wiadomoúci.
    Moøe byÊ strukturπ bazowπ dla wiÍkszych struktur ...
    p1 i p2 mogπ byÊ zastπpione dowolnymi typami, najlepiej o
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