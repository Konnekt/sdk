/*
  nazwa="GG API"
  data="2003-04-25"
  ver="1.1"
  info="Nag��wek wtyczki GG."
*/


/** @file Nag��wek wtyczki GG.DLL 


*/
/** @defgroup GG_shared_h Wtyczka GG.dll.

W API od wersji 1.1 znajduje si� obs�uga zdarze� w libgadu. 
Potrzebne b�d� r�wnie� przynajmniej nag��wki libgadu, kt�re dost�pne jest do pobrania
na stronie domowej SDK.

Poni�szy przyk�ad powinien wszystko wyja�ni�...
@code
    #include "gg_shared.h"
    // (...)
	// Gdzie� w kodzie "rejestrujemy" nasz� wtyczk�. Np. w #IM_START
	IMessage(IM_GG_REGISTERHANDLER,NET_GG,IMT_PROTOCOL,GGER_LOGIN|GGER_EVENT);
	// Dzi�ki GGER_LOGIN b�dziemy mogli zmieni� parametry logowania do 
	// poszczeg�lnych serwer�w, a GGER_EVENT przy�le ka�d� odpowied� serwera.
	// Mo�liwo�ci jest jeszcze kilka...

	// W IMessageProc musimy jeszcze obs�u�y� #IM_GG_EVENT
	case IM_GG_EVENT: {
		sIMessage_GGEvent * me = static_cast<sIMessage_GGEvent*>(msgBase);
		// W zale�no�ci od typu zdarzenia wykonujemy r�ne operacje
		switch (me->event_type) {
		    // (...)
		}
		break;}
	// Je�eli b�dziemy chcieli gdzie� w kodzie skorzysta� z sesji libgadu to:
	gg_session * sess = IMessage(IM_GG_GETSESSION,NET_GG,IMT_PROTOCOL); // Pobieramy sesj�
	if (sess) {
		// (...) operacje na sesji z wykorzystaniem libgaduw32.dll
		// Ka�d� pobran� sesj� TRZEBA zwolni�, ale TYLKO gdy zwr�cona sesja jest != 0
		IMessage(IM_GG_RELEASESESSION,NET_GG,IMT_PROTOCOL);
	}
@endcode    
@{
*/

#pragma pack(push, 1)

/** Zwraca wska�nik do sesji libgadu (gg_session) lub 0
    gdy nie ma ustanowionego po��czenia. Po zako�czeniu
	operowania na sesji trzeba wywo�a� #IM_GG_RELEASESESSION.
	
	Do samego sprawdzania istnienia po��czenia najlepiej pos�u�y
	#IM_ISCONNECTED.

	@return (gg_session*) Wska�nik sesji.
	*/
#define IM_GG_GETSESSION IM_USER+10001 
/** Zwalnia pobrany wcze�niej wska�nik sesji... */
#define IM_GG_RELEASESESSION IM_USER+10002

/** Wtyczka b�dzie otrzymywa�a powiadomienia przy wybranych
    zdarzeniach w libgadu.

	@param (int) po��czone flagi GGER_ oznaczaj�ce o jakich zdarzeniach wtyczka powinna by� powiadamiana.
*/
#define IM_GG_REGISTERHANDLER IM_USER+10003

enum GGER_enum {
   GGER_LOGIN = 1, ///< Zaraz przed nawi�zaniem po��czenia. Mo�na je anulowa� przez GGERF_ABORT
   GGER_LOGGEDIN = 2, ///< Udane logowanie
   GGER_LOGOUT = 4, ///< Zako�czenie po��czenia
   GGER_EVENT = 8, ///< Zdarzenie sieciowe
   GGER_FIRSTLOOP = 0x10, ///< Po zalogowaniu i przes�aniu wszystkich informacji (lista kontakt�w, status itp.)
   GGER_BEFORELOGIN = 0x20, ///< Zaraz przed rozpocz�ciem procedury logowania (i przed okre�leniem IP serwera)
   GGER_BEFORELOGOUT = 0x40, ///< Zaraz przed zako�czeniem po��czenia (nie zostanie wywo�ane w razie zerwania po��czenia)
};

#define GGERF_ABORT 1  ///< Przerwanie obs�ugiwania Eventu...
/** Wtyczka, kt�ra zarejestrowa�a si� jako handler otrzyma
    ten komunikat w razie wyst�pienia kt�rego� z "zam�wionych"
	zdarze�. Komunikat b�dzie typu sIMessage_GGEvent.

	@return Po��czone flagi GGERF_ , lub 0.
*/
#define IM_GG_EVENT IM_USER+10100

/** Struktura do przesy�ania IM_GG_EVENT */
struct sIMessage_GGEvent: public sIMessage_base {
	GGER_enum eventType;   ///< Typ zdarzenia - jedna z flag GGER_
	/** W zale�no�ci od typu zdarzenia w data
	    przekazywana jest odpowiednia strukturka, lub 0.
		Wi�kszo�� przekazywanych struktur mo�na modyfikowa�.
		Zdarzenia najcz�ciej wywo�ywane s� PRZED wykonaniem
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