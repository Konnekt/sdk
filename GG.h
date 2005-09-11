/*
  nazwa="GG API"
  data="2003-04-25"
  ver="1.1"
  info="Nag³ówek wtyczki GG."
*/


/** @file Nag³ówek wtyczki GG.DLL 


*/
/** @defgroup GG_shared_h Wtyczka GG.dll.

W API od wersji 1.1 znajduje siê obs³uga zdarzeñ w libgadu. 
Potrzebne bêd¹ równie¿ przynajmniej nag³ówki libgadu, które dostêpne jest do pobrania
na stronie domowej SDK.

Poni¿szy przyk³ad powinien wszystko wyjaœniæ...
@code
    #include "gg_shared.h"
    // (...)
	// Gdzieœ w kodzie "rejestrujemy" nasz¹ wtyczkê. Np. w #IM_START
	IMessage(IM_GG_REGISTERHANDLER,NET_GG,IMT_PROTOCOL,GGER_LOGIN|GGER_EVENT);
	// Dziêki GGER_LOGIN bêdziemy mogli zmieniæ parametry logowania do 
	// poszczególnych serwerów, a GGER_EVENT przyœle ka¿d¹ odpowiedŸ serwera.
	// Mo¿liwoœci jest jeszcze kilka...

	// W IMessageProc musimy jeszcze obs³u¿yæ #IM_GG_EVENT
	case IM_GG_EVENT: {
		sIMessage_GGEvent * me = static_cast<sIMessage_GGEvent*>(msgBase);
		// W zale¿noœci od typu zdarzenia wykonujemy ró¿ne operacje
		switch (me->event_type) {
		    // (...)
		}
		break;}
	// Je¿eli bêdziemy chcieli gdzieœ w kodzie skorzystaæ z sesji libgadu to:
	gg_session * sess = IMessage(IM_GG_GETSESSION,NET_GG,IMT_PROTOCOL); // Pobieramy sesjê
	if (sess) {
		// (...) operacje na sesji z wykorzystaniem libgaduw32.dll
		// Ka¿d¹ pobran¹ sesjê TRZEBA zwolniæ, ale TYLKO gdy zwrócona sesja jest != 0
		IMessage(IM_GG_RELEASESESSION,NET_GG,IMT_PROTOCOL);
	}
@endcode    
@{
*/

#pragma pack(push, 1)

/** Zwraca wskaŸnik do sesji libgadu (gg_session) lub 0
    gdy nie ma ustanowionego po³¹czenia. Po zakoñczeniu
	operowania na sesji trzeba wywo³aæ #IM_GG_RELEASESESSION.
	
	Do samego sprawdzania istnienia po³¹czenia najlepiej pos³u¿y
	#IM_ISCONNECTED.

	@return (gg_session*) WskaŸnik sesji.
	*/
#define IM_GG_GETSESSION IM_USER+10001 
/** Zwalnia pobrany wczeœniej wskaŸnik sesji... */
#define IM_GG_RELEASESESSION IM_USER+10002

/** Wtyczka bêdzie otrzymywa³a powiadomienia przy wybranych
    zdarzeniach w libgadu.

	@param (int) po³¹czone flagi GGER_ oznaczaj¹ce o jakich zdarzeniach wtyczka powinna byæ powiadamiana.
*/
#define IM_GG_REGISTERHANDLER IM_USER+10003

enum GGER_enum {
   GGER_LOGIN = 1, ///< Zaraz przed nawi¹zaniem po³¹czenia. Mo¿na je anulowaæ przez GGERF_ABORT
   GGER_LOGGEDIN = 2, ///< Udane logowanie
   GGER_LOGOUT = 4, ///< Zakoñczenie po³¹czenia
   GGER_EVENT = 8, ///< Zdarzenie sieciowe
   GGER_FIRSTLOOP = 0x10, ///< Po zalogowaniu i przes³aniu wszystkich informacji (lista kontaktów, status itp.)
   GGER_BEFORELOGIN = 0x20, ///< Zaraz przed rozpoczêciem procedury logowania (i przed okreœleniem IP serwera)
   GGER_BEFORELOGOUT = 0x40, ///< Zaraz przed zakoñczeniem po³¹czenia (nie zostanie wywo³ane w razie zerwania po³¹czenia)
};

#define GGERF_ABORT 1  ///< Przerwanie obs³ugiwania Eventu...
/** Wtyczka, która zarejestrowa³a siê jako handler otrzyma
    ten komunikat w razie wyst¹pienia któregoœ z "zamówionych"
	zdarzeñ. Komunikat bêdzie typu sIMessage_GGEvent.

	@return Po³¹czone flagi GGERF_ , lub 0.
*/
#define IM_GG_EVENT IM_USER+10100

/** Struktura do przesy³ania IM_GG_EVENT */
struct sIMessage_GGEvent: public sIMessage_base {
	GGER_enum eventType;   ///< Typ zdarzenia - jedna z flag GGER_
	/** W zale¿noœci od typu zdarzenia w data
	    przekazywana jest odpowiednia strukturka, lub 0.
		Wiêkszoœæ przekazywanych struktur mo¿na modyfikowaæ.
		Zdarzenia najczêœciej wywo³ywane s¹ PRZED wykonaniem
		samej operacji...
		*/
	union {
       struct gg_login_params * login_params; ///< Parametry logowania [GGER_LOGIN , GGER_BEFORELOGIN]
	   struct gg_event * event; ///< Zdarzenie sieciowe [GGER_EVENT]
	   void * pointer;
	} data;
	sIMessage_GGEvent()
		:sIMessage_base() {s_size=sizeof(sIMessage_GGEvent);}
};


#define CFG_GG_LOGIN    1053
#define CFG_GG_PASS     1054
#define CFG_GG_STATUS   1055 //INT 
#define CFG_GG_STARTSTATUS 1056 //INT
#define CFG_GG_DESCR   1057 //INT
#define CFG_GG_SERVER  1059  
#define CFG_GG_SERVERCHOSEN  1060
#define CFG_GG_TRAYMENU 1061

#define CFG_GG_FRIENDSONLY 1058  //INT
#define CFG_GG_USESSL  1063
#define CFG_GG_DONTRESUMEDISCONNECTED 1064

#define IMIA_GGSTATUS_OFFLINE 1001
#define IMIA_GGSTATUS_ONLINE 1002
#define IMIA_GGSTATUS_AWAY 1003
#define IMIA_GGSTATUS_HIDDEN 1004
#define IMIA_GGSTATUS_DESC   1005

#define IMIG_GGSTATUS_SERVER 1020

#define IMIG_MAIN_OPTIONS_LIST_GG 1010
#define IMIA_LIST_GG_IMPORT 1011
#define IMIA_LIST_GG_EXPORT 1012
#define IMIA_LIST_GG_CLEAR  1013
#define IMIA_LIST_GG_REFRESH 1014

#define IMIA_GGHIDESTATUS 1015

#define IMIA_NFO_GGSAVE   1022
#define IMIA_NFO_GGREFRESH   1021


#define IMIG_GGSTATUS 1000

#define IMIG_GGCFG_USER 1050
#define IMIC_GG_ACCOUNT  1051
#define IMIC_GG_NEWPASS  1052
#define IMIC_GG_REMINDPASS 1053
#define IMIC_GG_DEFSERVERS 1054
#define IMIC_GG_REMOVEACCOUNT  1055
#define IMIC_GG_SERVERSSSLONLY 1056
//#define IMIC_GG_PORT  1052
//#define IMIC_GG_LOGIN  1053
//#define IMIC_GG_PASS  1054

#pragma pack(pop)

/**@}*/