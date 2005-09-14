unit Plug;
{*
 * Konnekt Delphi SDK (Software Development Kit)
 * 
 * Nag³ówek: Plug Shared
 * Modyfikowany: 2005-09-13
 * Zgodny z wersj¹: 0.6.18.x
 * Info: Podstawowy nag³ówek.
 * 
 * Œrodowisko: Borland Delphi 7
 *
 * http://www.konnekt.info
 * 
 * (C)2002-2005 Stamina
 * SDK s³u¿y do przygotowywania oprogramowania wspó³pracuj¹cego
 * z programem Konnekt. Autorzy nie ponosz¹ ¿adnej odpowiedzialnoœci
 * za wykorzystanie tego kodu.
 * Kod zawarty w SDK mo¿e byæ u¿ywany tylko w projektach dotycz¹cych
 * programu Konnekt! *}

interface

uses
  SysUtils;

const
  KONNEKT_SDK_V = 2;

{   Struktura u¿ywana podczas przesy³ania wiadomoœci.
    Jest u¿ywana jako bazowa dla wiêkszych struktur...
  }
type
  sIMessage_basePtr = ^sIMessage_base; // wskaŸnik do struktury
  sIMessage_base = packed record
    size: Word;
    id: Cardinal;
    flag: Cardinal;
    net: Integer;
    type_: Cardinal;
    sender: Cardinal;
  end;
{ Funkcje u³atwiaj¹ce uzupe³nianie recordów, pole size zawsze jest ustawiane
  wiêc nie trzeba siê przejmowac ;) }
function sIMessage_baseB(id: Cardinal; net: Integer; _type: Cardinal): sIMessage_base; overload;
function sIMessage_baseB(): sIMessage_base; overload;
function sIMessage_baseB(id: Cardinal): sIMessage_base; overload;
function sIMessage_baseB(base: sIMessage_basePtr): sIMessage_base; overload;


{   Struktura u¿ywana podczas przesy³ania wiadomoœci.
    Mo¿e byæ struktur¹ bazow¹ dla wiêkszych struktur ...
    p1 i p2 mog¹ byæ zast¹pione dowolnymi typami, najlepiej o
    rozmiarze po 4 bajty ...
}
type
  sIMessage_2paramsPtr = ^sIMessage_2params;  // wskaŸnik do struktury
  sIMessage_2params = packed record
    size: Word;
    id: Cardinal;
    flag: Cardinal;
    net: Integer;
    type_: Cardinal;
    sender: Cardinal;     //!! dot¹d odziedziczone z sIMessage_base, ale ¿e delphi nie ma czegos takiego dla recordow wiec trzeba pola powtarzac!!
    p1: Integer;
    p2: Integer;
  end;
{ Funkcje u³atwiaj¹ce uzupe³nianie recordów, pole size zawsze jest ustawiane
  wiêc nie trzeba siê przejmowac ;) }
function sIMessage_2paramsB(id: Cardinal; net: Integer; _type: Cardinal; p1: Integer; p2: Integer): sIMessage_2params; overload;
function sIMessage_2paramsB(): sIMessage_2params; overload;
function sIMessage_2paramsB(id: Cardinal; p1: Integer; p2: Integer): sIMessage_2params; overload;
function sIMessage_2paramsB(base: sIMessage_base): sIMessage_2params; overload;

const
  NET_FIRST = -2;          ///< Wiadomoœæ dotrze do pierwszej wtyczki (dowolnej sieci), która potrafi j¹ obs³u¿yæ.
  NET_BROADCAST = -1;      ///< Wiadomoœæ dotrze do wtyczek wszystkich sieci.
  NET_BC = NET_BROADCAST;  ///< Odpowiednik #NET_BROADCAST.
  NET_NONE = 0;            ///< Wiadomosci do rdzenia.
  NET_NET = 1;             ///< Wtyczki obs³uguj¹ce protokó³ "w³asny".
  NET_INTERNAL = 2;
  NET_SOUND = 3;           ///< DŸwiêk
  NET_UPDATE = 4;           ///< Update
  NET_OTHER = 6;         ///< Wtyczki nie posiadaj¹ce akcji, nie obs³uguj¹ce wiadomoœci itp.
  NET_GG = 10;            ///< Wtyczki obs³uguj¹ce protokó³ GG
  NET_ICQ = 11;            ///< Wtyczki obs³uguj¹ce protokó³ ICQ
  NET_JABBER = 12;            ///< Wtyczki obs³uguj¹ce protokó³ JABBER
  NET_EMAIL = 13;            ///< Wtyczki obs³uguj¹ce EMaile
  NET_SMS = 14;            ///< Wtyczki obs³uguj¹ce SMSy
  NET_KLAN = 15;
  NET_KSTYLE = 16;
  NET_EXPIMP = 17;
  NET_KONNFERENCJA = 20;
  NET_AIM = 60;            ///< Wtyczki obs³uguj¹ce protokó³ AIM
  NET_YAHOO = 61;            ///< Wtyczki obs³uguj¹ce protokó³ YAHOO
  NET_MSN = 62;            ///< Wtyczki obs³uguj¹ce protokó³ MSN
  NET_TLEN = 63;            ///< Wtyczki obs³uguj¹ce protokó³ TLEN
  NET_KTRANSFER = 130; ///< kTransfer

const
  AC_USER = 0;      ///< Akcja jest przypisana do u¿ytkownika.
  AC_NONE = -1;    ///< Akcja nie jest przypisana do ¿adnego kontaktu.
  AC_CURRENT = -2; ///< Ostatnio przypisany kontakt.

type
  sUIActionPtr = ^sUIAction;  // wskaŸnik do struktury
  sUIAction = packed record
    id: Cardinal;
    parent: Cardinal;
    cnt: Integer;
  end;

function sUIActionB(): sUIAction; overload;
function sUIActionB(parent: Cardinal; id: Cardinal; cnt: Integer = AC_CURRENT): sUIAction; overload;

type
  sUIActionNotify_basePtr = ^sUIActionNotify_base;  // wskaŸnik do struktury
  sUIActionNotify_base = packed record
    s_size: Word;
    act: sUIAction;
    code: Cardinal;
    reserved: Integer;
  end;

type
  sUIActionNotify_2paramsPtr = ^sUIActionNotify_2params;
  sUIActionNotify_2params = packed record
    s_size: Word;
    act: sUIAction;
    code: Cardinal;
    reserved: Integer;   //!! dot¹d odzedziczone z sUIActionNotify_base
    notify1: Cardinal;
    notify2: Cardinal;
  end;

{ Identyfikatory tablic. }
type tTable = Shortint;

const
  DTCFG: tTable = 0; ///< Tablica konfiguracji
  DTCNT: tTable = 1; ///< Tablica kontaktów
  DTMSG: tTable = 2; ///< Tablica wiadomoœci
  DTNONE: tTable = -1;

const
  UIAIM_STATUS = 1; ///< sUIActionInfo::status i sUIActionInfo::statusMask s¹ ustawione.
  UIAIM_EXSTYLE = 2; ///< sUIActionInfo::exStyle i sUIActionInfo::exStyleMas s¹ ustawione.
  UIAIM_P1 = 4; ///< sUIActionInfo::p1 jest ustawiony.
  UIAIM_P2 = 8; ///< sUIActionInfo::p2 jest ustawiony.
  UIAIM_PARAM = $10; ///< sUIActionInfo::param jest ustawiony.
  UIAIM_ICO = UIAIM_P1;
  UIAIM_TXT = $40;  ///< sUIActionInfo::txt i sUIActionInfo::txtSize s¹ ustawione.
  UIAIM_COL = UIAIM_P1; ///< \blank
  UIAIM_POS = $100;  ///< \blank
  UIAIM_SIZE = $200;  ///< \blank
  UIAIM_HANDLE = $400;  ///< \blank
  UIAIM_TYPE = $800;  ///< \blank
  UIAIM_VALUE_CONVERT = $10000; ///< Ustawiona wartoœæ akcji powinna zostaæ przekonwertowana (np. z formatu wartoœci akcji do formatu pola w bazie i na odwrót)
  UIAIM_ALL = $35F; ///< Wszystkie powy¿sze.

type
  sUIActionInfoPtr = ^sUIActionInfo;
  sUIActionInfo = packed record
    s_size: Word;
    act: sUIAction;  ///< Identyfikatory.
    pos: Cardinal;  ///<Pozycja na liœcie w grupie. Pos == -1 oznacza "na koñcu" (podczas \ref IMI_ACTION "wstawiania").
                    /// \todo Powinien potrafiæ równie¿ zmieniæ pozycjê.
    type_: Cardinal; ///<Typ kontrolki przypisanej do akcji ( \ref actt_ ).
    handle: THandle;     ///<Uchwyt do kontrolki akcji (np w windowsach uchwyty do HWND lub HMENU)
    reserved: Pointer;
    mask: Cardinal;       { Maska.
                            Oznacza które pola w strukturze s¹
                            ustawione.
                            \attention Pole \a act musi byæ \b zawsze ustawione! <br>
                            \sa \ref uiaim_
                           }
    status: Cardinal;     ///<\ref actm_ "Status".
    statusMask: Cardinal; ///<Oznacza które pola w \a status powinny byæ zmienione.
    exStyle: Cardinal;    { Dodatkowe style . \attention W tej chwili nie s¹ one u¿ywane! }
    exStyleMask: Cardinal;///<Oznacza które pola w \a exStyle powinny byæ zmienione.
    txt: PChar;     ///< Tekst przypisany do akcji.
    txtSize: Cardinal; ///< Rozmiar bufora w txt.
    param: Integer;      ///<Parametr u¿ytkownika.
    p1: Integer;         ///<Dodatkowy parametr uzywany przez typy kontrolek.
    p2: Integer;         ///<Dodatkowy parametr uzywany przez typy kontrolek.
    w,h: Smallint; ///< Wysokoœæ / szerokoœæ kontrolki
  end;

function sUIActionInfoB(): sUIActionInfo; overload;
function sUIActionInfoB(parent: Integer; id: Integer; pos: Integer; status: Integer = 0; txt: PChar = nil; p1: Integer = 0; w: Smallint = 0; h: Smallint = 0; p2: Integer = 0; param: Integer = 0): sUIActionInfo; overload;
function sUIActionInfoB(parent: Integer; id: Integer): sUIActionInfo; overload;
function sUIActionInfoB(a: sUIAction): sUIActionInfo; overload;

type
  sUIActionInfo_cfgPtr = ^sUIActionInfo_cfg;
  sUIActionInfo_cfg = packed record
    s_size: Word;
    act: sUIAction;  ///< Identyfikatory.
    pos: Cardinal;  ///<Pozycja na liœcie w grupie. Pos == -1 oznacza "na koñcu" (podczas \ref IMI_ACTION "wstawiania").
                    /// \todo Powinien potrafiæ równie¿ zmieniæ pozycjê.
    type_: Cardinal; ///<Typ kontrolki przypisanej do akcji ( \ref actt_ ).
    handle: THandle;     ///<Uchwyt do kontrolki akcji (np w windowsach uchwyty do HWND lub HMENU)
    reserved: Pointer;
    mask: Cardinal;       { Maska.
                            Oznacza które pola w strukturze s¹
                            ustawione.
                            \attention Pole \a act musi byæ \b zawsze ustawione! <br>
                            \sa \ref uiaim_
                           }
    status: Cardinal;     ///<\ref actm_ "Status".
    statusMask: Cardinal; ///<Oznacza które pola w \a status powinny byæ zmienione.
    exStyle: Cardinal;    { Dodatkowe style . \attention W tej chwili nie s¹ one u¿ywane! }
    exStyleMask: Cardinal;///<Oznacza które pola w \a exStyle powinny byæ zmienione.
    txt: PChar;     ///< Tekst przypisany do akcji.
    txtSize: Cardinal; ///< Rozmiar bufora w txt.
    param: Integer;      ///<Parametr u¿ytkownika.
    p1: Integer;         ///<Dodatkowy parametr uzywany przez typy kontrolek.
    p2: Integer;         ///<Dodatkowy parametr uzywany przez typy kontrolek.
    w,h: Smallint; ///< Wysokoœæ / szerokoœæ kontrolki
    x,y: Smallint; ///< Przesuniêcie wzglêdem osi x/y
  end;

function sUIActionInfo_cfgB(): sUIActionInfo_cfg; overload;
function sUIActionInfo_cfgB(parent: Integer; id: Integer; pos: Integer = -1; status: Integer = 0; txt: PChar = nil; col: Integer = 0; w: Smallint = 0; h: Smallint = 0; p2: Integer = 0; param: Integer = 0): sUIActionInfo_cfg; overload;
function sUIActionInfo_cfgB(parent: Integer; id: Integer; pos: Integer = -1; status: Integer = 0; txt: PChar = nil; col: Integer = 0; x: Smallint = 0; y: Smallint = 0; w: Smallint = 0; h: Smallint = 0; p2: Integer = 0; param: Integer = 0): sUIActionInfo_cfg; overload;

type HINSTANCE = Longword;

	{ Rodzaj zapisywanej informacji dla cCtrl::IMDEBUG() }
type enDebugLevel = (
    DBG_NONE = 0,
		DBG_NET = 1,
		DBG_TRAFFIC = 2 , 
		DBG_DUMP = 4 , 
		DBG_FUNC = 8 , 
		DBG_MISC = $10 ,
		DBG_ERROR = $20 ,
		DBG_WARN = $40 ,
		DBG_LOG = $100 ,
		DBG_DEBUG = $1000 ,
		DBG_ALL = $0FFF
    );

const
  DT_ROWID_MASK = $40000000;  ///< Bit oznaczaj¹cy, ¿e "numer wiersza", jest identyfikatorem wiersza.
                             /// \sa #ISCNTID #GETCNTID cCtrl::DTgetID()

  { Typy kolumn
    Typ kolumny sk³ada siê z 8 bitowego typu (jak np. #DT_CT_INT) i flag.
  }
const
  DT_CT_INT = 0;    ///< 4 bajty (int)
  DT_CT_PCHAR = 1;  ///< Tekst zakoñczony znakiem '0'.
  DT_CT_STR = DT_CT_PCHAR;
  DT_CT_64 = 3;    ///< 8 bajtów (__int64, double ...)
  DT_CT_UNKNOWN = -1;  ///< dla sDTValue, typ nieznany (zostanie ustawiony).
  DT_CF_NOSAVE = $100;  ///< Kolumna nie zostanie zapisana do pliku.
	DT_CF_SECRET = $400;       ///< Kolumna mo¿e byæ has³em i powinna byæ odpowiednio strze¿ona...
  DT_CF_CXOR = $01000; ///< Kodowanie kolumn poprzez XORing. Dzia³a tylko jako DT_CT_PCHAR|DT_CT_CXOR.

type
  sDTValuePtr = ^sDTValue;
  sDTValue = packed record
    type_: Smallint; ///< Typ przekazywanej wartoœci
    case Integer of
      0: (vInt: Integer);
      1: (vInt64: Int64);
      2: (vChar: PChar; buffSize: Cardinal)
  end;

function sDTValueB(type_: Smallint = DT_CT_UNKNOWN): sDTValue;

type
  sIMessage_setColumnPtr = ^sIMessage_setColumn;
  sIMessage_setColumn = packed record
    size: Word;
    id: Cardinal;
    flag: Cardinal;
    net: Integer;
    type_: Cardinal;
    sender: Cardinal;   //<-- Dot¹d odziedziczone z sIMessage_base
    //__msgID: Integer;
    table: tTable;
    _id: Integer;
    _type: Integer;
    def: Integer; ///< Przechowuje inta, PChar lub PInt64 w zale¿nosci od DT_CT_
    name: PChar;
  end;

function sIMessage_setColumnB(table: tTable; id: Integer; type_: Integer; def: Integer; const name: PChar = nil): sIMessage_setColumn; overload;
function sIMessage_setColumnB(table: tTable; id: Integer; type_: Integer; const def: PChar; const name: PChar = nil): sIMessage_setColumn; overload;
function sIMessage_setColumnB(id: Integer; type_: Integer; def: Integer; const name: PChar = nil): sIMessage_setColumn; overload;
function sIMessage_setColumnB(id: Integer; type_: Integer; const def: PChar; const name: PChar = nil): sIMessage_setColumn; overload;

const
  IMI_BASE = 10000;
  IM_BASE = 20000;
  IM_SHARE = 30000;
  IM_USER = 40000;

  IMI_ACTION = IMI_BASE+101;
  IMI_GROUP = IMI_BASE+102;
  IMI_ACTION_CALL = IMI_BASE+103;
  IMI_ACTION_GET = IMI_BASE+107;
  IMI_ACTION_SET = IMI_BASE+108;
  IMI_ACTION_GETVALUE = IMI_BASE+106;
  IMI_ACTION_SETVALUE = IMI_BASE+110;
  IMI_GROUP_ACTIONSCOUNT = IMI_BASE+111;
  IMI_ACTION_EXISTS = IMI_BASE+112;
  IMI_ACTION_ISGROUP = IMI_BASE+113;
  IMI_ACTION_GETID = IMI_BASE+114;
  IMI_ACTION_REMOVE = IMI_BASE+115;
  IMI_ACTION_GETTYPE = IMI_BASE+116;
  IMI_GROUP_GETHANDLE = IMI_BASE+117;
  IMI_ACTION_FINDPARENT = IMI_BASE+118;
	IMI_GETPLUGINSGROUP = IMI_BASE+119;
  IMI_GROUP_MAKECFG = IMI_BASE+120;
  IMI_ACTION_SETCNT = IMI_BASE+121;
  IMI_ACTION_GETINDEX = IMI_BASE+122;
  IMI_ACTION_GETOWNER = IMI_BASE+123;
  IMI_ICONREGISTER = IMI_BASE+130;
  IMI_ACTION_MAKEPOPUPMENU = IMI_BASE+150;

  IMI_WARNING = IMI_BASE+200;
  IMI_ERROR = IMI_BASE+201;
  IMI_CONFIRM = IMI_BASE+202;
  IMI_INFORM = IMI_BASE+204;

  IM_PLUG_INIT = IM_BASE+1;
  IM_PLUG_DEINIT = IM_BASE+2;
  IM_PLUG_SDKVERSION = IM_BASE+20;

  IM_SETCOLS = IM_BASE+1001;
  
  NOTIFY_AUTO = -2;
  IMI_DLGPASS = IMI_BASE+205;
  IMI_DLGLOGIN = IMI_BASE+206;
  IMI_DLGSETPASS = IMI_BASE+207;
  IMI_DLGENTER = IMI_BASE+208;
  IMI_DLGBUTTONS = IMI_BASE+213;
  IMI_DLGTOKEN = IMI_BASE+214;
  IMI_LONGSTART = IMI_BASE+209;
  IMI_LONGEND = IMI_BASE+210;
  IMI_LONGSET = IMI_BASE+211;
  IMI_DLGPROFILE = IMI_BASE+212;
  IMI_NOTIFY = IMI_BASE+1010;
  IMI_NEWNOTIFY = IMI_BASE+1011;
  IMI_CNT_ACTIVITY = IMI_BASE+1013;
  IMI_CNT_DEACTIVATE = IMI_BASE+1014;
  IMI_CNT_DETAILS = IMI_BASE+1015;
  IMI_CNT_DETAILS_SUMMARIZE = IMI_BASE+1016;
  IMI_CNT_ISCOMPOSING = IMI_BASE+1020;

  IM_MSG_RCV = IM_BASE+100;
  IM_UI_PREPARE = IM_BASE+2000;
  IM_START = IM_BASE+2100;
  IM_END = IM_BASE+2101;
  IM_UIACTION = IM_BASE+2200;

  IM_PLUG_NET = IM_SHARE+10;
  IM_PLUG_TYPE = IM_SHARE+11;
  IM_PLUG_VERSION = IM_SHARE+12;
  IM_PLUG_SIG = IM_SHARE+13;
  IM_PLUG_CORE_V = IM_SHARE+14;
  IM_PLUG_UI_V = IM_SHARE+15;
  IM_PLUG_NAME = IM_SHARE+16;
  IM_PLUG_NETNAME = IM_SHARE+17;

const
  IM_MSG_ok = 1;
  IM_MSG_delete = 2;
  IM_MSG_update = 4;
  IM_MSG_processing = 8;

type
  sDIALOGPtr = ^sDIALOG;
  sDIALOG = packed record
    s_size: Word;
    title: PChar; ///< Tytu³ okienka.
    info: PChar;  ///< Dodatkowa informacja ...
    flag: Integer;     ///< Flaga D*_
    handle: THandle; ///< Uchwyt do okna dialogowego. Przed utworzeniem okna, \a handle trzeba ustawiæ na rodzica okna!
    param: Pointer; ///< Parametr uzytkownika
  end;

type
  sDIALOG_enterPtr = ^sDIALOG_enter;
  sDIALOG_enter = packed record
    s_size: Word;
    title: PChar; ///< Tytu³ okienka.
    info: PChar;  ///< Dodatkowa informacja ...
    flag: Integer;     ///< Flaga D*_
    handle: THandle; ///< Uchwyt do okna dialogowego. Przed utworzeniem okna, \a handle trzeba ustawiæ na rodzica okna!
    param: Pointer; ///< Parametr uzytkownika
    value: PChar;
    id: PChar;
    maxLength: Integer;
  end;
function sDIALOG_enterB(): sDialog_enter;

type
  sDIALOG_choosePtr = ^sDIALOG_choose;
  sDIALOG_choose = packed record
    s_size: Word;
    title: PChar; ///< Tytu³ okienka.
    info: PChar;  ///< Dodatkowa informacja ...
    flag: Integer;     ///< Flaga D*_
    handle: THandle; ///< Uchwyt do okna dialogowego. Przed utworzeniem okna, \a handle trzeba ustawiæ na rodzica okna!
    param: Pointer; ///< Parametr uzytkownika
    items: PChar;
    def: Integer;
    width: Integer;
  end;

function sDIALOG_chooseB(): sDIALOG_choose;

type
  sDIALOG_longPtr = ^sDIALOG_long;
  TcancelProc = function(dialog: sDIALOG_longPtr): Boolean; stdcall;
  TtimeoutProc = function(type_: Integer; dialog: sDIALOG_longPtr): Boolean;
  sDIALOG_long = packed record
    s_size: Word;
    title: PChar; ///< Tytu³ okienka.
    info: PChar;  ///< Dodatkowa informacja ...
    flag: Integer;     ///< Flaga D*_
    handle: THandle; ///< Uchwyt do okna dialogowego. Przed utworzeniem okna, \a handle trzeba ustawiæ na rodzica okna!
    param: Pointer; ///< Parametr uzytkownika
    progress: Integer; ///< Wartoœæ 'postêpu'. Przy tworzeniu okna oznacza max. wartoœæ (liczon¹ od zera) - domyœlnie 100.
    cancel: Boolean;  ///< Czy zosta³o wciœniête [Anuluj]?
    threadId: Integer; ///< Id watku, z ktorego tworzone bylo okno
    cancelProc: TcancelProc; ///< Procedura wywo³ywana po naciœniêciu [Anuluj].
    timeoutProc: TtimeoutProc; ///< Procedura wywo³ywana aby sprawdziæ czy nast¹pi³ timeout.
    timeoutParam: Pointer;  ///< Parametr do wykorzystania przez timeoutProc.
    timeout: Integer;          ///< Czas po jakim zostanie wys³ane TIMEOUTT_TIMEOUT.
    timeoutPassed: Integer;    ///< Iloœæ ms jaka uplynê³a od pierwszego TIMEOUTT_CHECK==0.
    timeoutHandle: THandle;
  end;

function sDIALOG_longB(): sDIALOG_long;

const
  DLONG_MODAL = $01;
  DLONG_CANCEL = $02;
  DLONG_NODLG = $04;
  DLONG_SINGLE = $08;
  DLONG_ONLY = DLONG_SINGLE;
  DLONG_BLOCKING = $10;

const
  DSET_TITLE = $1;    ///< Zosta³ zmieniony tytu³.
  DSET_INFO = $2;    ///< Zosta³o zmienione info.
  DSET_PROGRESS = $4;    ///< Zosta³ zmieniony postêp.
  DSET_BUTTONS = $8;    ///< Zosta³y zmienione flagi dotycz¹ce przycisków.
  DSET_ANIM = $10;   ///< Zosta³a zmieniona animacja.

const
  IMC_LOG  = 1;
  IMC_CONNECTED = 7;
  IMC_PROFILEDIR = 12;
  IMC_NEWMESSAGE = 100;
  IMC_MESSAGEQUEUE = 101;
  IMC_PLUG_COUNT = 240;
  IMC_PLUG_HANDLE = 241;

type
  sMESSAGESELECTPtr = ^sMESSAGESELECT;
  sMESSAGESELECT = packed record
    s_size: Word;
    net: Integer;
    uid: PChar;
    type_: Integer;
    wflag: Cardinal;
    woflag: Cardinal;
    id: Integer;
    position: Cardinal;
  end;

function sMESSAGESELECTB(): sMESSAGESELECT; overload;
function sMESSAGESELECTB(net: Integer; uid: PChar = nil; type_: Cardinal = Cardinal(-1); wflag: Cardinal = Cardinal(-1); woflag: Cardinal = Cardinal(-1)): sMESSAGESELECT; overload;

const
  IMERROR_NORESULT = 1;   ///< Wtyczka nie obs³u¿y³a wiadomoœci.
  IMERROR_UNSUPPORTEDMSG = IMERROR_NORESULT; /// \no
  IMERROR_BADSENDER = 2;  ///< Wiadomoœæ wstrzymana, pojawi³ siê b³¹d...
  IMERROR_BADPLUG = 3;    ///< Podana wtyczka nie istnieje.
  IMERROR_THREADSAFE = 4; ///< Wiadomoœæ zosta³a wywo³ana w trybie bezpiecznym (bez oczekiwania na powrót).
  IMERROR_SHUTDOWN = 5;   ///< Wiadomoœæ zosta³a anulowana z powodu zamykania programu.
  IMERROR_BADPARAM = 6;   ///< Nieprawid³owe parametry.
  IMERROR_BADSTRUCT = 7;   ///< Niepoprawna struktura.

const
  IMT_ALL = $FFFFFFFF;
  IMT_CORE = 0;
  IMT_MESSAGE = 1;
  IMT_PROTOCOL = 2;
  IMT_CONTACT = 4;
  IMT_CONFIG = 8;
  IMT_UI = $10;
  IMT_NET = $20;
  IMT_NETSEARCH = $40;
  IMT_MSGUI = $80;
  IMT_NETUID = $100;
  IMT_ALLMESSAGES = $200;
  IMT_MESSAGEACK = $400;

const
  CNT_UID = 0; ///< #DT_CT_PCHAR UID.
  CNT_NET = 1; ///< #DT_CT_INT Sieæ.
  CNT_STATUS = 2; ///< #DT_CT_INT Status.

type fBeginThread = function(data: Pointer): Cardinal;

type
  cCtrlRPtr = ^cCtrlR;
  VMTPTR = ^VMT;
  TgetLevel = function(ptr: cCtrlRPtr): Integer; stdcall;
  TID = function(ptr: cCtrlRPtr): Cardinal; stdcall;
  ThInst = function(ptr: cCtrlRPtr): HINSTANCE; stdcall;
  ThDll = function(ptr: cCtrlRPtr): HINSTANCE; stdcall;
  TgetError = function(ptr: cCtrlRPtr): Integer; stdcall;
  TsetError = procedure(ptr: cCtrlRPtr; err_code: Integer); stdcall;
  TisRunning = function(ptr: cCtrlRPtr): Boolean; stdcall;
  TIMessage = function(ptr: cCtrlRPtr; msg: sIMessage_basePtr): Integer; stdcall;
  TIMessageDirect = function(ptr: cCtrlRPtr; plug: Cardinal; msg: sIMessage_basePtr): Integer; stdcall;
  TDTgetPos = function(ptr: cCtrlRPtr; db: tTable; row: Cardinal): Integer; stdcall;
  TDTgetID = function(ptr: cCtrlRPtr; db: tTable; row: Cardinal): Integer; stdcall;
  TDTgetOld = function(ptr: cCtrlRPtr; db: tTable; row: Cardinal; col: Cardinal): Integer; stdcall;
  TDTsetOld = function(ptr: cCtrlRPtr; db: tTable; row: Cardinal; col: Cardinal; val: Integer; mask: Integer = 0): Integer; stdcall;
  TDTgetType = function(ptr: cCtrlRPtr; db: tTable; id: Cardinal): Integer; stdcall;
  TDTgetCount = function(ptr: cCtrlRPtr; db: tTable): Integer; stdcall;
  TDTgetNameID = function(ptr: cCtrlRPtr; db: tTable; name: PChar): Integer; stdcall;
  TIs_TUS = function(ptr: cCtrlRPtr; thID: Cardinal): Cardinal; stdcall;
  TRecallTS = function(ptr: cCtrlRPtr; th: THandle = 0; wair: Boolean = True): Integer; stdcall;
  TRecallIMTS = function(ptr: cCtrlRPtr; th: THandle; wait: Boolean; msg: sIMessage_basePtr; plugID: Integer): Integer; stdcall;
  TWMProcess = procedure(ptr: cCtrlRPtr); stdcall;
  TGetTempBuffer = function(ptr: cCtrlRPtr; size: Cardinal): Pointer; stdcall;
  TDTget = function(ptr: cCtrlRPtr; db: tTable; row: Cardinal; col: Cardinal; value: sDTValuePtr): Boolean; stdcall;
  TDTset = function(ptr: cCtrlRPtr; db: tTable; row: Cardinal; col: Cardinal; value: sDTValuePtr): Boolean; stdcall;
  TDTlock = function(ptr: cCtrlRPtr; db: tTable; row: Cardinal; reserved: Integer = 0): Word; stdcall;
  TDTunlock = function(ptr: cCtrlRPtr; db: tTable; row: Cardinal; reserved: Integer = 0): Word; stdcall;
  Tmalloc = function(ptr: cCtrlRPtr; size: Cardinal): Pointer; stdcall;
  Tstrdup = function(ptr: cCtrlRPtr; str: PChar): PChar; stdcall;
  Tfree = procedure(ptr: cCtrlRPtr; buff: Pointer); stdcall;
  TSleep = function(ptr: cCtrlRPtr; time: Cardinal): Integer; stdcall;
  TBeginThread = function(ptr: cCtrlRPtr; security: Pointer; stack_size: Cardinal; start_address: fBeginThread; arglist: Pointer = nil; initflag: Cardinal = 0; thrdaddr: PCardinal = nil): THandle;
  TDebugLevel = function(ptr: cCtrlRPtr; level: enDebugLevel = DBG_ALL): Cardinal; stdcall;
  TQuickShutdown = function(ptr: cCtrlRPtr): Boolean; stdcall;
  TSetDebugLevel = function(ptr: cCtrlRPtr; levelMask: enDebugLevel; level: enDebugLevel = DBG_ALL): Cardinal; stdcall;
  TDTgetName = function(ptr: cCtrlRPtr; db: tTable; col: Cardinal): PChar; stdcall;
  VMT = packed record
    getLevel: TgetLevel;
    ID: TID;
    hInst: ThInst;
    hDll: ThDll;
    getError: TgetError;
    setError: TsetError;
    isRunning: TisRunning;
    IMessage: TIMessage;
    IMessageDirect: TIMessageDirect;
    DTgetPos: TDTgetPos;
    DTgetID: TDTgetID;
    DTgetOld: TDTgetOld;
    DTsetOld: TDTsetOld;
    DTgetType: TDTgetType;
    DTgetCount: TDTgetCount;
    DTgetNameID: TDTgetNameID;
    Is_TUS: TIs_TUS;
    RecallTS: TRecallTS;
    RecallIMTS: TRecallIMTS;
    WMProcess: TWMProcess;
    GetTempBuffer: TGetTempBuffer;
    DTget: TDTget;
    DTset: TDTset;
    DTlock: TDTlock;
    DTunlock: TDTunlock;
    malloc: Tmalloc;
    strdup: Tstrdup;
    free: Tfree;
    Sleep: TSleep;
    BeginThread: TBeginThread;
    DebugLevel: TDebugLevel;
    QuickShutdown: TQuickShutdown;
    SetDebugLevel: TSetDebugLevel;
    DTgetName: TDTgetName;
  end;
  cCtrlR = packed record
    vptr: VMTPTR;
  end;

type
  cCtrlPtr = ^cCtrl;
  cCtrl = class
  private
    CtrlR: cCtrlRPtr;
  public
    constructor Create(p: Integer);
    function getLevel():Integer; stdcall;  ///< Zwraca "poziom" dostepu do rdzenia. W 99% przypadków zwróci 1 ...
    function ID():Cardinal; stdcall;  ///< Zwraca identyfikator wtyczki.
    function hInst():HINSTANCE; stdcall;  ///<  Zwraca uchwyt procesu (HINSTANCE).
    function hDll():HINSTANCE; stdcall;   ///<  Zwraca uchwyt biblioteki wtyczki.

    function getError():Integer; stdcall; ///< Zwraca kod ostatniego b³êdu.
    procedure setError(err_code: Integer); stdcall; ///< Ustawia kod b³êdu.
                                                             ///  Powinien byc ustawiony gdy wystapil blad przy ODBIORZE wiadomosci (np wiadomosc jest nieobslugiwana).
                                                             ///  \sa ImessageProc() imerror_
    function isRunning():Boolean; stdcall; ///< Zwraca 0 jeœli program jest w trakcie zamykania.
                                                    ///  ¯adne d³u¿sze operacje nie powinny byæ wykonywane. Czêœæ IMessages
                                                    ///  w innych modu³ach i tak nie zostanie wykonana...
    {
    Wysy³a wiadomoœæ do wtyczek.
    Aby przes³aæ wiadomoœæ do rdzenia lub ui jako \i net i \i type trzeba podaæ 0
    \param msg Wiadomoœæ do przes³ania
    \sa im_ net_ imt_
    }
    function IMessage(msg: sIMessage_basePtr):Integer; overload; stdcall;
    { Wysy³a wiadomoœæ bezpoœrednio do okreœlonej wtyczki.
     \param msg Wiadomoœæ do przes³ania
     \param plug ID wtyczki
     \sa im_ imc_plug_
    }
    function IMessageDirect(plug: Cardinal; msg: sIMessage_basePtr):Integer; overload; stdcall;
    { Zamienia (lub nie) identyfikator wiersza na jego numer.
    }
    function DTgetPos(db: tTable; row: Cardinal):Integer; stdcall;
    { Zamienia (lub nie) numer wiersza na jego identyfikator.
    }
    function DTgetID(db: tTable; row: Cardinal):Integer; stdcall;
    function DTgetOld(db: tTable; row: Cardinal; col: Cardinal):Integer; stdcall;
    function DTsetOld(db: tTable; row: Cardinal; col: Cardinal; val :Integer; mask: Cardinal=0):Integer; stdcall;
    { Pobieta typ kolumny \a id.
      \param id Identyfikator kolumny
      \return typ kolumny
      \sa \ref cfg dt_ct_
    }
    function DTgetType(db: tTable; id: Cardinal): Integer; stdcall;
    { Pobieta iloœæ wierszy w tablicy.
      \param db Identyfikator tablicy
      \sa \ref cfg dt_ct_
    }
    function DTgetCount(db: tTable): Integer; stdcall;
    { Pobieta identyfikator kolumny o podanej nazwie.
      \param db Identyfikator tablicy
      \param name nazwa kolumny
      \sa \ref cfg dt_ct_
    }
    function DTgetNameID(db: tTable; const name: PChar): Integer; stdcall;

    function Is_TUS(thID: Cardinal): Cardinal; stdcall; ///< Zwraca \a thID jeœli aktualny w¹tek jest ró¿ny od \a thID. Lub 0 gdy s¹ równe. Jako \a thID mo¿na podaæ 0 - zostanie zamienione na g³ówny w¹tek aplikacji.
    function RecallTS(th: THandle = 0; wait: Boolean = true):Integer; stdcall;
    function RecallIMTS(th: THandle; wait: Boolean; msg: sIMessage_basePtr; plugID:Integer):Integer; stdcall;

    procedure WMProcess(); stdcall; ///< Opró¿nienie kolejki wiadomoœci windowsowych.
                                             ///  Powinno byæ wykonywane TYLKO w g³ównym w¹tku, w d³ugich
                                             ///  blokuj¹cych pêtlach (aby odœwie¿yæ wygl¹d okien)
    function GetTempBuffer(size: Cardinal): Pointer; stdcall; ///< Zwraca wskaŸnik do bufora tymczasowego o rozmiarze \a size.
                                                                       /// Bufor alokowany jest w kontekœcie wtyczki i w¹tku.
                                                                       /// \attention Nie mo¿na zwalniaæ tej pamiêci!

    { Pobiera wartosc wiersza z tablicy danych z konwersj¹ typów.
      Konwersja odbywa siê gdy sDTValue::type jest ró¿ny od DT_CT_UNKNOWN. W
      przeciwnym wypadku jako typ przyjmowany jest typ kolumny.
         \param db Identyfikator tabeli
         \param row Identyfikator/numer wiersza
         \param col Identyfikator kolumny
         \param value Struktura z wartoœci¹
         \return wartoœæ (lub adres do wartoœci jeœli typ != DT_CT_INT)
         \attention W #DTMSG mo¿na zapisywaæ tylko w okreœlonych okolicznoœciach!
     }
     function DTget(db: tTable; row: Cardinal; col: Cardinal; value: sDTValuePtr): Boolean; stdcall;
     {  Ustawia wartosc wiersza z tablicy danych z konwersj¹ typów.
         Konwersja odbywa siê gdy sDTValue::type jest ró¿ny od DT_CT_UNKNOWN. W
         przeciwnym wypadku jako typ przyjmowany jest typ kolumny.
         \param db Identyfikator tabeli
         \param row Identyfikator/numer wiersza
         \param col Identyfikator kolumny
         \param value Struktura do której zostanie zapisana wartoœæ.
         \attention Do odczytu danych z #DTMSG przygotowane s¹ inne funkcje!
       }
     function DTset(db: tTable; row: Cardinal; col: Cardinal; value: sDTValuePtr):Boolean; stdcall;
     { Blokuje dostêp do wiersza w tablicy dla innych w¹tków. Zaraz po
       wykorzystaniu zabezpieczonych danych trzeba wywo³aæ cCtrl::DTunlock z tymi
       samymi parametrami!
         \param db Identyfikator tabeli
         \param row Identyfikator/numer wiersza, lub -1 jeœli chcemy zablokowaæ CA£¥ tablicê
         \param reserved Zarezerwowane na póŸniej, musi byæ równe 0.
         \return Iloœæ wczeœniej za³o¿onych blokad.
     }
     function DTlock(db: tTable; row: Cardinal; reserved: Integer = 0): Byte; stdcall;
     { Odblokowuje dostêp do wiersza w tablicy dla innych w¹tków,
       zastrze¿ony wczeœniej przy u¿yciu cCtrk::DTlock.
       \param db Identyfikator tabeli
       \param row Identyfikator/numer wiersza, lub -1 jeœli chcemy zablokowaæ CA£¥ tablicê
       \param reserved Zarezerwowane na póŸniej, musi byæ równe 0.
       \return Iloœæ pozosta³ych blokad.
       \attention Po wykonaniu tej funkcji, wszystkie zwrócone wskaŸniki
       bezpoœrednie mog¹ byæ ju¿ nieaktualne!
     }
     function DTunlock(db: tTable; row: Cardinal; reserved: Integer = 0): Byte; stdcall;
     { Wszystkie bufory wrzucane do API, ¿eby mog³by byæ zwolnione
       w innym module musz¹ byæ zaalokowane poni¿sz¹ funkcj¹. }
     function malloc(size: Cardinal): Pointer; stdcall;
     { Wszystkie bufory tekstowe wrzucane do API, ¿eby mog³by byæ zwolnione
       w innym module musz¹ byæ zaalokowane poni¿sz¹ funkcj¹. }
     function strdup(const str: PChar): PChar; stdcall;
     { Wszystkie bufory zaalokowane przez cCtrl::malloc i cCtrl::strdup
       powinny byæ zwolnione t¹ funkcj¹. }
     procedure free(buff: Pointer); stdcall;

         {   U¿ywanie zwyk³ego Sleep w g³ównym w¹tku najprêdzej doprowadzi
             K do stanu chwilowej nieu¿ywalnoœci, bardzo mo¿liwe równie¿,
             ¿e nast¹pi zupe³ny DeadLock.
             Zamiast tego mo¿na u¿ywaæ tej funkcji, która po prostu zamiast Sleep
             wywo³uje MsgWaitForMultipleObjectsEx. Nie jest wiêc gwarantowane, 
             ¿e podany czas w ogóle minie. Trzeba pamiêtaæ te¿, ¿e nie jest gwarantowane,
			 ¿e aktualny w¹tek nie wykona gdzieœ po drodze innego kodu w wyniku
			 wywo³ania f-cji APC, timer'a czy windowsowej wiadomoœci...
			 Podczas zamykania (w IM_END) nie powinny byæ wywo³ywane procedury APC ani
			 prze³¹czanie w¹tków...
             Generalnie, je¿eli musisz czekaæ na coœ w g³ównym w¹tku, u¿ywaj
             MsgWaitForMultipleObjectsEx w po³¹czeniu z Ctrl->WMProcess, które
             przegl¹da kolejkê oczekuj¹cych wiadomoœci w aktualnym w¹tku.
         }
     function Sleep(time: Cardinal): Integer; stdcall;

		 {
		     BeginThread dzia³a identycznie jak _beginthreadex z wyj¹tkiem
			 tego, ¿e w trybie debug potrafi wychwytywaæ b³êdy w w¹tku
			 i je raportowaæ... U¿ywanie wysoko zalecane!
			 @warn Funkcja zwraca uchwyt w¹tku! Nale¿y go zamkn¹æ przy pomocy CloseHandle()!!!
		 }
		 function BeginThread( security: Pointer;
			stack_size: Integer;
			start_address: fBeginThread;
			arglist: Pointer = nil;
			initflag: Cardinal = 0;
			thrdaddr: PCardinal = nil
		 ): THandle; stdcall;
		{** Tworzy w¹tek i czeka a¿ siê skoñczy.
			Parametry te same co w cCtrl::BeginThread()
		*}
		function BeginThreadAndWait(security: THandle;	stack_size: Cardinal; start_address: fBeginThread; arglist: THandle = 0; initflag: THandle = 0; thrdaddr: THandle = 0): Integer;

		{ Pobiera poziom debugowania dla wtyczki }
		function DebugLevel(level: enDebugLevel = DBG_ALL): Integer; stdcall;

		{ Podaje, czy Konnekt jest zamykany w trybie natychmiastowym (np. podczas zamykania systemu).
			Wtyczki nie powinny w tym czasie wykonywaæ d³ugich operacji, prze³¹czaæ w¹tków (#IMESSAGE_TS),
			ani przetwarzaæ procedur APC (flaga Alertable w funkcjach oczekuj¹cych WinApi).
		 }
    function QuickShutdown(): Boolean; stdcall;

		{ Ustawia poziom debugowania wtyczki.
		 }
		function SetDebugLevel(levelMask: enDebugLevel; level: enDebugLevel = DBG_ALL): Cardinal; stdcall;

    { Pobiera nazwe kolumny o podanym identyfikatorze.
         \param db Identyfikator tablicy
         \param col Identyfikator kolumny
         \sa \ref cfg dt_ct_
     }
    function DTgetName(db: tTable; col: Cardinal): PChar; stdcall;


         // funkcje lokalne, dla ulatwienia
         function DTgetInt(db: tTable; row: Cardinal; col: Cardinal): Integer; overload;
         function DTsetInt(db: tTable; row: Cardinal; col: Cardinal; value: Integer; mask: Integer = -1): Boolean; overload;
         function DTgetStr(db: tTable; row: Cardinal; col: Cardinal; buff: PChar = nil; size: Cardinal = 0): PChar; overload;
         function DTsetStr(db: tTable; row: Cardinal; col: Cardinal; const value: PChar): Boolean; overload;
         function DTgetInt64(db: tTable; row: Cardinal; col: Cardinal): Int64; overload;
         function DTsetInt64(db: tTable; row: Cardinal; col: Cardinal; value: Int64; mask: Int64 = -1): Boolean; overload;

         function DTgetInt(db: tTable; row: Cardinal; const name: PChar): Integer; overload;
         function DTsetInt(db: tTable; row: Cardinal; const name: PChar; value: Integer; mask: Integer = -1): Boolean; overload;
         function DTgetStr(db: tTable; row: Cardinal; const name: PChar; buff: PChar = nil; size: Cardinal = 0): PChar; overload;
         function DTsetStr(db: tTable; row: Cardinal; const name: PChar; const value: PChar): Boolean; overload;
         function DTgetInt64(db: tTable; row: Cardinal; const name: PChar): Int64; overload;
         function DTsetInt64(db: tTable; row: Cardinal; const name: PChar; value: Int64; mask: Int64 = -1): Boolean; overload;


    { Zapisuje sfromatowan¹ informacjê do pliku konnekt.log (i ew. wyœwietla j¹ w oknie @Dev) }
 		procedure IMLOG(const format: string; const arglist: array of const );
		{ Loguje, je¿eli wtyczka ma w³¹czone logowanie na danym "poziomie" }
		procedure IMDEBUG(level: enDebugLevel; const format: string; const arglist: array of const);
 		procedure IMLOG_(level: enDebugLevel; const format: string; const va_list: array of const);

		// ----
		function IMessage(id: Cardinal; net: Integer = 0; type_: Cardinal = Cardinal(-1); p1: Integer = 0; p2: Integer = 0): Integer; overload;
		function ICMessage(id: Cardinal; p1: Integer = 0; p2: Integer = 0): Integer;
		function IMessageDirect(id: Cardinal; plug: Cardinal = 0; p1: Integer = 0; p2: Integer = 0): Integer; overload;

		function UIActionInsert( _parent: Integer; _id: Integer; _pos: Integer; _status: Integer = 0; const _txt: PChar = nil; _p1: Integer = 0;  _w: Shortint = 0; _h: Shortint = 0; _p2: Integer = 0; _param: Integer = 0): Integer;

		function SetColumn(table: tTable; id: Integer; type_: Integer; def: Integer; const name: PChar): Integer; overload;
		function SetColumn(table: tTable; id: Integer; type_: Integer; const def: PChar; const name: PChar = nil):Integer; overload; {
			return this->SetColumn(table , id , type , (int)def , name);
		}
end;

{ Identyfikatory podstawowych akcji w UI tworzacych grupy}
const
  IMIG_MAINWND = 1;   ///< G³ówne okno
  IMIG_BAR = 2;   ///< Belka glowna
  IMIG_MSGWND = 3;   ///< Okno wysy³ania wiadomoœci
  IMIG_MSGBAR = 4;   ///< Belka w wysy³aniu wiadomoœci
  IMIG_MAINTB = 8;   ///< G³ówny toolbar
  IMIG_SHORTCUTTB = 9;   ///< Toolbar ze skrótami
  IMIG_MAIN = 10;  ///< G³ówne Menu
  IMIG_MAIN_OPTIONS = 11;  ///< Menu opcji
  IMIG_MAIN_CNT = 12;     ///< Dodaj kontakt
  IMIG_MAIN_PROFILE = 13;  ///< Profile
  IMIG_HISTORYWND = 14;
  IMIG_PLUGINS = 15;  {< Grupa dla ikonek wtyczek w g³ównym oknie... U¿ytkownik mo¿e wybraæ
										inn¹, wiêc numer aktualnej grupy nale¿y pobraæ przez #IMI_GETPLUGINSGROUP.
									
										}
  IMIG_STATUS = 50;  ///< Toolbar ze statusami
  IMIG_EVENT = 51;  ///< Menu z wiadomoœciami od serwerów.
  IMIG_EVENT_PARENT = IMIG_STATUS;
  IMIG_HIDDEN = 60;

  IMIG_TRAY = 20;  ///< Tray
  IMIG_CNT = 30;  ///< Menu kontaktu
  IMIG_CFGWND = 40;  ///< Okno ustawieñ.
  IMIG_CFG = 41;  ///< Korzeñ drzewka ustawieñ.
  IMIG_CFG_CONNECTION = 42; ///< Opcje po³¹czeñ.
  IMIG_CFG_USER = 43;  ///< Ustawienia u¿ytkownika.
  IMIG_CFG_SETTINGS = 44;  ///< Ustawienia programu.
  IMIG_CFG_UI = 45;  ///< Ustawienia interfejsu.
  IMIG_CFG_PLUGS = 46;  ///< Ustawienia wtyczek.

  IMIG_NFOWND = 70;  ///< Okno informacji o kontakcie
  IMIG_NFO = 71;   ///< Drzewko kontrolek informacji
  IMIG_NFO_BAR = 72;   ///< Belka w oknie informacji o kontakcie
  IMIG_NFO_TB = 73;   ///< G³ówny toolbar w oknie informacji o kontakcie

type
  cMessagePtr = ^cMessage;
  cMessage = packed record
    s_size: Word;
    id: Cardinal;
    net: Cardinal;
    type_: Cardinal;
    fromUid: PChar;
    toUid: PChar;
    body: PChar;
    ext: PChar;
    flag: Cardinal;
    action: sUIAction;
    notify: Cardinal;
    time: Int64;
end;

function cMessageB(): cMessage;

const
  EXT_PARAM = Chr($1A);

const
  MT_MASK_NOTONLIST = $1000;
  MT_MESSAGE = 1;
  MT_QUICKEVENT = 2;
  MT_CNTEVENT = 3;
  MT_EVENT = MT_CNTEVENT or MT_MASK_NOTONLIST;
  MT_SERVEREVENT = 4 or MT_MASK_NOTONLIST;
  MT_AUTHORIZE = 5;
  MT_CONFERENCE = 6;
  MT_FILE = 7;
  MT_MAIL = 8;
  MT_SMS = 9;
  MT_SOUND = 10;
  MT_URL = 11 or MT_MASK_NOTONLIST;
  MT_SPECIAL = 12;
  MT_SPECIAL_NOL =  13 or MT_MASK_NOTONLIST;
  MT_IMAGE = 15;
  MT_BOARD = 16;
  MT_MASK = $FFF;

const
  MF_SEND = 2;
  MF_NOEVENTS = 4;
  MF_NOSAVE = 8;
  MF_REQUESTOPEN = $10;
  MF_PROCESSING = $20;
  MF_OPENED = $40;
  MF_HANDLEDBYUI = $80;
  MF_AUTOMATED = $100;
  MF_HTML = $200;
  MF_MENUBYUI = $400;
  MF_LEAVEASIS = $800;
  MF_HIDE = $1000;
  MF_DONTADDTOHISTORY = $2000;
  MF_QE_NORMAL = $10000;
  MF_QE_SHOWTIME = $20000;

implementation

{ Implementacje funkcji u³atwiaj¹cych wype³nianie struktury sIMessage_setColumn }
function sIMessage_setColumnB(table: tTable; id: Integer; type_: Integer; def: Integer; const name: PChar = nil): sIMessage_setColumn;
var
  col: sIMessage_setColumn;
begin
  col.size := SizeOf(sIMessage_setColumn);
  col.id := 1102;
  col.net := 0;
  col.type_ := 0;
  col.sender := 0;
  col.flag := 0;
  col.table := table;
  col._id := id;
  col._type := type_;
  col.def := def;
  col.name := name;
  Result := col;
end;

function sIMessage_setColumnB(table: tTable; id: Integer; type_: Integer; const def: PChar; const name: PChar = nil): sIMessage_setColumn;
var
  col: sIMessage_setColumn;
begin
  col.size := SizeOf(sIMessage_setColumn);
  col.id := 1102;
  col.net := 0;
  col.type_ := 0;
  col.sender := 0;
  col.flag := 0;
  col.table := table;
  col._id := id;
  col._type := type_;
  col.def := Integer(def);
  col.name := name;
  Result := col;
end;

function sIMessage_setColumnB(id: Integer; type_: Integer; def: Integer; const name: PChar = nil): sIMessage_setColumn;
var
  col: sIMessage_setColumn;
begin
  col.size := SizeOf(sIMessage_setColumn);
  col.id := 1102;
  col.net := 0;
  col.type_ := 0;
  col.sender := 0;
  col.flag := 0;
  col.table := DTCFG;
  col._id := id;
  col._type := type_;
  col.def := def;
  col.name := name;
  Result := col;
end;

function sIMessage_setColumnB(id: Integer; type_: Integer; const def: PChar; const name: PChar = nil): sIMessage_setColumn;
var
  col: sIMessage_setColumn;
begin
  col.size := SizeOf(sIMessage_setColumn);
  col.id := 1102;
  col.net := 0;
  col.type_ := 0;
  col.sender := 0;
  col.flag := 0;
  col.table := DTCFG;
  col._type := type_;
  col.def := Integer(def);
  col.name := name;
  Result := col;
end;

{ Implementacje funkcji u³atwiaj¹cych wype³nianie struktury sIMessage_base }
function sIMessage_baseB(id: Cardinal; net: Integer; _type: Cardinal): sIMessage_base;
var
  msgBase: sIMessage_base;
begin
  msgBase.size := SizeOf(msgBase);
  msgBase.id := id;
  msgBase.net := net;
  msgBase.type_ := _type;
  msgBase.sender := 0;
  msgBase.flag := 0;
  Result := msgBase;
end;

function sIMessage_baseB(): sIMessage_base;
var
  msgBase: sIMessage_base;
begin
  msgBase.size := SizeOf(msgBase);
  msgBase.id := 0;
  msgBase.net := 0;
  msgBase.type_ := 0;
  msgBase.sender := 0;
  msgBase.flag := 0;
  Result := msgBase;
end;

function sIMessage_baseB(id: Cardinal): sIMessage_base;
var
    msgBase: sIMessage_base;
begin
  msgBase.size := SizeOf(msgBase);
  msgBase.id := id;
  msgBase.net := 0;
  msgBase.type_ := 0;
  msgBase.sender := 0;
  msgBase.flag := 0;
  Result := msgBase;
end;

function sIMessage_baseB(base: sIMessage_basePtr): sIMessage_base;
var
  msgBase: sIMessage_base;
begin
  msgBase := base^;
  Result := msgBase;
end;

{ Implementacje funkcji u³atwiaj¹cych wype³nianie struktury sIMessage_2params }
function sIMessage_2paramsB(id: Cardinal; net: Integer; _type: Cardinal; p1: Integer; p2: Integer): sIMessage_2params;
var
  msg: sIMessage_2params;
begin
  msg.size := SizeOf(msg);
  msg.id := id;
  msg.flag := 0;
  msg.sender := 0;
  msg.net := net;
  msg.type_ := _type;
  msg.p1 := p1;
  msg.p2 := p2;
  Result := msg;
end;

function sIMessage_2paramsB(): sIMessage_2params;
var
  msg: sIMessage_2params;
begin
  msg.size := SizeOf(msg);
  msg.id := 0;
  msg.flag := 0;
  msg.sender := 0;
  msg.net := 0;
  msg.type_ := 0;
  msg.p1 := 0;
  msg.p2 := 0;
  Result := msg;
end;

function sIMessage_2paramsB(id: Cardinal; p1: Integer; p2: Integer): sIMessage_2params;
var
  msg: sIMessage_2params;
begin
  msg.size := SizeOf(msg);
  msg.id := id;
  msg.flag := 0;
  msg.sender := 0;
  msg.net := 0;
  msg.type_ := 0;
  msg.p1 := p1;
  msg.p2 := p2;
  Result := msg;
end;

function sIMessage_2paramsB(base: sIMessage_base): sIMessage_2params;
var
  msg: sIMessage_2params;
begin
  msg.size := SizeOf(msg);
  msg.id := base.id;
  msg.flag := base.flag;
  msg.sender := base.sender;
  msg.net := base.net;
  msg.type_ := base.type_;
  msg.p1 := 0;
  msg.p2 := 0;
  Result := msg;
end;

{ Implementacje funkcji u³atwiaj¹cych wype³nianie struktury sIMessage_2params }
function sUIActionInfoB(): sUIActionInfo;
var
  ai: sUIActionInfo;
begin
  ai.s_size := SizeOf(ai);
  ai.mask := 0;
  ai.act.id := 0;
  ai.act.parent := 0;
  ai.pos := 0;
  ai.handle := 0;
  Result := ai;
end;

function sUIActionInfoB(parent: Integer; id: Integer; pos: Integer; status: Integer = 0; txt: PChar = nil; p1: Integer = 0; w: Smallint = 0; h: Smallint = 0; p2: Integer = 0; param: Integer = 0): sUIActionInfo;
var
  ai: sUIActionInfo;
begin
  ai.s_size := SizeOf(ai);
  ai.mask := UIAIM_ALL;
  ai.act := sUIActionB(parent, id);
  ai.pos := pos;
  ai.txt := txt;
  ai.status := status;
  ai.statusMask := Cardinal(-1);
  ai.exStyleMask := 0;
  ai.p1 := p1;
  ai.p2 := p2;
  ai.param := param;
  ai.w := w;
  ai.h := h;
  Result := ai;
end;

function sUIActionInfoB(parent: Integer; id: Integer): sUIActionInfo;
var
  ai: sUIActionInfo;
begin
  ai.s_size := SizeOf(ai);
  ai.mask := 0;
  ai.act.id := id;
  ai.act.parent := parent;
  Result := ai;
end;

function sUIActionInfoB(a: sUIAction): sUIActionInfo;
var
  ai: sUIActionInfo;
begin
  ai.s_size := SizeOf(ai);
  ai.act := a;
  ai.mask := 0;
  Result := ai;
end;

{ Implementacja metod klasy cCtrl }

constructor cCtrl.Create(p: Integer);
begin
  inherited Create();
  self.CtrlR := cCtrlRPtr(p);
end;

function cCtrl.getLevel():Integer;
begin
  Result := CtrlR.vptr.getLevel(CtrlR);
end;

function cCtrl.ID():Cardinal;
begin
  Result := CtrlR.vptr.ID(CtrlR);
end;

function cCtrl.hInst():HINSTANCE;
begin
  Result := CtrlR.vptr.hInst(CtrlR);
end;

function cCtrl.hDll():Cardinal;
begin
  Result := CtrlR.vptr.hDll(CtrlR);
end;

function cCtrl.getError():Integer;
begin
  Result := CtrlR.vptr.getError(CtrlR);
end;

procedure cCtrl.setError(err_code: Integer);
begin
  CtrlR.vptr.setError(CtrlR, err_code);
end;

function cCtrl.isRunning(): Boolean;
begin
  Result := CtrlR.vptr.isRunning(CtrlR);
end;

function cCtrl.IMessage(msg: sIMessage_basePtr): Integer;
begin
  Result := CtrlR.vptr.IMessage(CtrlR, msg);
end;

function cCtrl.IMessageDirect(plug: Cardinal; msg: sIMessage_basePtr):Integer;
begin
  Result := CtrlR.vptr.IMessageDirect(CtrlR, plug, msg);
end;

function cCtrl.DTgetPos(db: tTable; row: Cardinal):Integer;
begin
  Result := CtrlR.vptr.DTgetPos(CtrlR, db, row);
end;

function cCtrl.DTgetID(db: tTable; row: Cardinal): Integer;
begin
  Result := CtrlR.vptr.DTgetID(CtrlR, db, row);
end;

function cCtrl.DTgetOld(db: tTable; row: Cardinal; col: Cardinal): Integer;
begin
  Result := CtrlR.vptr.DTgetOld(CtrlR, db, row, col);
end;

function cCtrl.DTsetOld(db: tTable; row: Cardinal; col: Cardinal; val :Integer; mask: Cardinal=0):Integer;
begin
  Result := CtrlR.vptr.DTsetOld(CtrlR, db, row, col, val, mask);
end;

function cCtrl.DTgetType(db: tTable; id: Cardinal): Integer;
begin
  Result := CtrlR.vptr.DTgetType(CtrlR, db, id);
end;

function cCtrl.DTgetCount(db: tTable): Integer;
begin
  Result := CtrlR.vptr.DTgetCount(CtrlR, db);
end;

function cCtrl.DTgetNameID(db: tTable; const name: PChar): Integer;
begin
  Result := CtrlR.vptr.DTgetNameID(CtrlR, db, name);
end;

function cCtrl.Is_TUS(thID: Cardinal): Cardinal;
begin
  Result := CtrlR.vptr.Is_TUS(CtrlR, thID);
end;

function cCtrl.RecallTS(th: Cardinal = 0; wait: Boolean = True): Integer;
begin
  Result := CtrlR.vptr.RecallTS(CtrlR, th, wait);
end;

function cCtrl.RecallIMTS(th: THandle; wait: Boolean; msg: sIMessage_basePtr; plugID:Integer):Integer;
begin
  Result := CtrlR.vptr.RecallIMTS(CtrlR, th, wait, msg, plugID);
end;

procedure cCtrl.WMProcess();
begin
  CtrlR.vptr.WMProcess(CtrlR);
end;

function cCtrl.GetTempBuffer(size: Cardinal): Pointer;
begin
  Result := CtrlR.vptr.GetTempBuffer(CtrlR, size);
end;

function cCtrl.DTget(db: tTable; row: Cardinal; col: Cardinal; value: sDTValuePtr): Boolean;
begin
  Result := CtrlR.vptr.DTget(CtrlR, db, row, col, value);
end;

function cCtrl.DTset(db: tTable; row: Cardinal; col: Cardinal; value: sDTValuePtr):Boolean;
begin
  Result := CtrlR.vptr.DTset(CtrlR, db, row, col, value);
end;

function cCtrl.DTlock(db: tTable; row: Cardinal; reserved: Integer = 0): Byte;
begin
  Result := CtrlR.vptr.DTlock(CtrlR, db, row, reserved);
end;

function cCtrl.DTunlock(db: tTable; row: Cardinal; reserved: Integer = 0): Byte;
begin
  Result := CtrlR.vptr.DTunlock(CtrlR, db, row, reserved);
end;

function cCtrl.malloc(size: Cardinal): Pointer;
begin
  Result := CtrlR.vptr.malloc(CtrlR, size);
end;

function cCtrl.strdup(const str: PChar): PChar;
begin
  Result := CtrlR.vptr.strdup(CtrlR, str);
end;

procedure cCtrl.free(buff: Pointer);
begin
  CtrlR.vptr.free(CtrlR, buff);
end;

function cCtrl.Sleep(time: Cardinal): Integer;
begin
  Result := CtrlR.vptr.Sleep(CtrlR, time);
end;

function cCtrl.BeginThread( security: Pointer;
			stack_size: Integer;
			start_address: fBeginThread;
			arglist: Pointer = nil;
			initflag: Cardinal = 0;
			thrdaddr: PCardinal = nil
		 ): THandle;
begin
  Result := CtrlR.vptr.BeginThread(CtrlR, security, stack_size, start_address, arglist, initflag, thrdaddr);
end;

function cCtrl.DebugLevel(level: enDebugLevel = DBG_ALL): Integer;
begin
  Result := CtrlR.vptr.DebugLevel(CtrlR, level);
end;

function cCtrl.QuickShutdown(): Boolean;
begin
  Result := CtrlR.vptr.QuickShutdown(CtrlR);
end;

function cCtrl.SetDebugLevel(levelMask: enDebugLevel; level: enDebugLevel = DBG_ALL): Cardinal;
begin
  Result := CtrlR.vptr.SetDebugLevel(CtrlR, levelMask, level);
end;

function cCtrl.DTgetName(db: tTable; col: Cardinal): PChar;
begin
  Result := CtrlR.vptr.DTgetName(CtrlR, db, col);
end;

function cCtrl.SetColumn(table: tTable; id: Integer; type_: Integer; const def: PChar; const name: PChar = nil): Integer;
var
  idef: Integer;
begin
  idef := Integer(def);
  Result := SetColumn( table, id, type_, idef, name );
end;

function cCtrl.BeginThreadAndWait(security: THandle;	stack_size: Cardinal; start_address: fBeginThread; arglist: THandle = 0; initflag: THandle = 0; thrdaddr: THandle = 0): Integer;
begin
  Result:=0;
end;

function cCtrl.DTgetInt(db: tTable; row: Cardinal; col: Cardinal): Integer;
var
  v: sDTValue;
begin
  v.type_ := DT_CT_INT;
  DTget( db, row, col, @v);
  Result := v.vInt;
end;

function cCtrl.DTsetInt(db: tTable; row: Cardinal; col: Cardinal; value: Integer; mask: Integer = -1): Boolean;
var
  v: sDTValue;
begin
  v.type_ := DT_CT_INT;
  if mask <> -1 then // maskowanie
  begin
    DTget( db, row, col, @v);
    v.vInt := ((v.vInt and not mask) or value);
    Result := DTset( db, row, col, @v);
  end
  else
  begin
    v.vInt := value;
    Result := DTset( db, row, col, @v);
  end;
end;

function cCtrl.DTgetStr(db: tTable; row: Cardinal; col: Cardinal; buff: PChar = nil; size: Cardinal = 0): PChar;
var
  v: sDTValue;
begin
  v.type_ := DT_CT_PCHAR;
  v.vChar := buff;
  v.buffSize := size;
  DTget(db, row, col, @v);
  Result := v.vChar;
end;

function cCtrl.DTsetStr(db: tTable; row: Cardinal; col: Cardinal; const value: PChar): Boolean;
var
  v: sDTValue;
begin
  v.type_ := DT_CT_PCHAR;
  v.vChar := value;
  Result := DTset(db, row, col, @v);
end;

function cCtrl.DTgetInt64(db: tTable; row: Cardinal; col: Cardinal): Int64;
var
  v: sDTValue;
begin
  v.type_ := DT_CT_64;
  DTget(db, row, col, @v);
  Result := v.vInt64;
end;

function cCtrl.DTsetInt64(db: tTable; row: Cardinal; col: Cardinal; value: Int64; mask: Int64 = -1): Boolean;
var
  v: sDTValue;
begin
  v.type_ := DT_CT_64;
  if mask <> -1 then  // maskowanie
  begin
    DTget(db, row, col, @v);
    v.vInt64 := ((v.vInt64 and not mask) or value);
    Result := DTset(db, row, col, @v);
  end
  else
  begin
    v.vInt64 := value;
    Result := DTset(db, row, col, @v);
  end;
end;

function cCtrl.DTgetInt(db: tTable; row: Cardinal; const name: PChar): Integer;
begin
  Result := DTgetInt(db, row, DTgetNameID(db, name));
end;

function cCtrl.DTsetInt(db: tTable; row: Cardinal; const name: PChar; value: Integer; mask: Integer = -1): Boolean;
begin
  Result := DTsetInt(db, row, DTgetNameID(db, name), value, mask);
end;

function cCtrl.DTgetStr(db: tTable; row: Cardinal; const name: PChar; buff: PChar = nil; size: Cardinal = 0): PChar;
begin
  Result := DTgetStr(db, row, DTgetNameID(db, name), buff, size);
end;

function cCtrl.DTsetStr(db: tTable; row: Cardinal; const name: PChar; const value: PChar): Boolean;
begin
  Result := DTsetStr(db, row, DTgetNameID(db, name), value);
end;

function cCtrl.DTgetInt64(db: tTable; row: Cardinal; const name: PChar): Int64;
begin
  Result := DTgetInt64(db, row, DTgetNameID(db, name));
end;

function cCtrl.DTsetInt64(db: tTable; row: Cardinal; const name: PChar; value: Int64; mask: Int64 = -1): Boolean;
begin
  Result := DTsetInt64(db, row, DTgetNameID(db, name), value, mask);
end;

procedure cCtrl.IMLOG(const format: string; const arglist: array of const );
begin
  self.IMLOG_(DBG_LOG, format, arglist);
end;

procedure cCtrl.IMDEBUG(level: enDebugLevel; const format: string; const arglist: array of const);
begin
  if self.DebugLevel(level) <> 0 then
  begin
    self.IMLOG_(level, format, arglist);
  end;
end;

procedure cCtrl.IMLOG_(level: enDebugLevel; const format: string; const va_list: array of const);
var
  msg: sIMessage_2params;
  buff: string;
begin
  FmtStr(buff, format, va_list);
  msg := sIMessage_2paramsB(IMC_LOG, Integer(PChar(buff)), Integer(level));
  self.IMessage(@msg);
end;

function cCtrl.IMessage(id: Cardinal; net: Integer = 0; type_: Cardinal = Cardinal(-1); p1: Integer = 0; p2: Integer = 0): Integer;
var
  msg: sIMessage_2params;
begin
  msg := sIMessage_2paramsB(id, net, type_, p1, p2);
  Result := self.IMessage(@msg);
end;

function cCtrl.ICMessage(id: Cardinal; p1: Integer = 0; p2: Integer = 0): Integer;
var
  msg: sIMessage_2params;
begin
  msg := sIMessage_2paramsB(id, 0, 0, p1, p2);
  Result := self.IMessage(@msg);
end;

function cCtrl.IMessageDirect(id: Cardinal; plug: Cardinal = 0; p1: Integer = 0; p2: Integer = 0): Integer;
var
  msg: sIMessage_2params;
begin
  if plug = 0 then
    plug := self.ID();
  msg := sIMessage_2paramsB(id, 0, 0, p1, p2);
  Result := self.IMessageDirect(plug, @msg);
end;

function cCtrl.UIActionInsert( _parent: Integer; _id: Integer; _pos: Integer; _status: Integer = 0; const _txt: PChar = nil; _p1: Integer = 0;  _w: Shortint = 0; _h: Shortint = 0; _p2: Integer = 0; _param: Integer = 0): Integer;
var
 ai: sUIActionInfo;
begin
  ai := sUIActionInfoB(_parent , _id , _pos , _status , _txt , _p1 , _w , _h , _p2 , _param);
  Result := self.ICMessage(IMI_ACTION , Integer(@ai) , 0);
end;

function cCtrl.SetColumn(table: tTable; id: Integer; type_: Integer; def: Integer; const name: PChar): Integer;
var
  sc: sIMessage_setColumn;
begin
  sc := sIMessage_setColumnB(table, id, type_, def, name);
  Result := self.IMessage(@sc);
end;

function sUIActionInfo_cfgB(): sUIActionInfo_cfg;
var
  ai: sUIActionInfo_cfg;
begin
  ai.s_size := SizeOf(ai);
  ai.mask := 0;
  ai.act.id := 0;
  ai.act.parent := 0;
  ai.pos := 0;
  ai.handle := 0;
  ai.x := 0;
  ai.y := 0;
  Result := ai;
end;

function sUIActionInfo_cfgB(parent: Integer; id: Integer; pos: Integer = -1; status: Integer = 0; txt: PChar = nil; col: Integer = 0; w: Smallint = 0; h: Smallint = 0; p2: Integer = 0; param: Integer = 0): sUIActionInfo_cfg;
var
  ai: sUIActionInfo_cfg;
begin
  ai.s_size := SizeOf(ai);
  ai.mask := UIAIM_ALL;
  ai.act.id := id;
  ai.act.parent := parent;
  ai.pos := pos;
  ai.txt := txt;
  ai.status := status;
  ai.statusMask := Cardinal(-1);
  ai.exStyleMask := 0;
  ai.p1 := col;
  ai.p2 := p2;
  ai.param := param;
  ai.w := 0;
  ai.h := 0;
  ai.w := 0;
  ai.h := 0;
  Result := ai;
end;

function sUIActionInfo_cfgB(parent: Integer; id: Integer; pos: Integer = -1; status: Integer = 0; txt: PChar = nil; col: Integer = 0; x: Smallint = 0; y: Smallint = 0; w: Smallint = 0; h: Smallint = 0; p2: Integer = 0; param: Integer = 0): sUIActionInfo_cfg; overload;
var
  ai: sUIActionInfo_cfg;
begin
  ai.s_size := SizeOf(ai);
  ai.mask := UIAIM_ALL;
  ai.act.id := id;
  ai.act.parent := parent;
  ai.pos := pos;
  ai.txt := txt;
  ai.status := status;
  ai.statusMask := Cardinal(-1);
  ai.exStyleMask := 0;
  ai.p1 := col;
  ai.p2 := p2;
  ai.param := param;
  ai.w := w;
  ai.h := h;
  ai.x := x;
  ai.y := y;
  Result := ai;
end;

const
  sd_info = '';

const
  sde_val: PChar = '';
  sde_id: PChar = '';
function sDIALOG_enterB(): sDIALOG_enter;
var
  sde: sDIALOG_enter;
begin
  sde.s_size := SizeOf(sde);
  sde.info := sd_info;
  sde.title := sd_info;
  sde.handle := 0;
  sde.param := nil;
  sde.value := sde_val;
  sde.id := sde_id;
  sde.maxLength := 0;
  Result := sde;
end;

const
  sdc_items: PChar = '';
function sDIALOG_chooseB(): sDIALOG_choose;
var
  sdc: sDIALOG_choose;
begin
  sdc.s_size := SizeOf(sdc);
  sdc.info := sd_info;
  sdc.title := sd_info;
  sdc.handle := 0;
  sdc.param := nil;
  sdc.items := sdc_items;
  sdc.def := 1;
  sdc.width := 0;
  Result := sdc;
end;

function sDIALOG_longB(): sDIALOG_long;
var
  sdl: sDIALOG_long;
begin
  sdl.s_size := SizeOf(sdl);
  sdl.info := sd_info;
  sdl.title := sd_info;
  sdl.handle := 0;
  sdl.param := nil;
  sdl.progress := -1;
  sdl.cancel := False;
  sdl.cancelProc := nil;
  sdl.timeoutProc := nil;
  sdl.timeout := 0;
  sdl.timeoutPassed := 0;
  sdl.timeoutHandle := 0;
  sdl.timeoutParam := nil;
  sdl.threadId := 0;
  Result := sdl;
end;

function sUIActionB(): sUIAction;
var
  act: sUIAction;
begin
  act.parent := 0;
  act.id := 0;
  act.cnt := AC_CURRENT;
  Result := act;
end;

function sUIActionB(parent: Cardinal; id: Cardinal; cnt: Integer = AC_CURRENT): sUIAction;
var
  act: sUIAction;
begin
  act.parent := parent;
  act.id := id;
  act.cnt := cnt;
  Result := act;
end;

function sDTValueB(type_: Smallint = DT_CT_UNKNOWN): sDTValue;
var
  v: sDTValue;
begin
  v.type_ := type_;
  v.vInt64 := 0;
  v.buffSize := 0;
  Result := v;
end;

function cMessageB(): cMessage;
var
  m: cMessage;
begin
  m.s_size := SizeOf(m);
  m.id := 0;
  m.net := 0;
  m.flag := 0;
  m.type_ := 0;
  m.notify := 0;
  m.time := 0;
  m.action := sUIActionB(0,0);
  m.fromUid := '';
  m.toUid := '';
  m.body := '';
  m.ext := '';
  Result := m;
end;

function sMESSAGESELECTB(): sMESSAGESELECT;
var
  s: sMESSAGESELECT;
begin
  s.s_size := SizeOf(s);
  s.net := NET_BC;
  s.uid := nil;
  s.type_ := -1;
  s.wflag := 0;
  s.woflag := 0;
  s.id := -1;
  s.position := 0;
  Result := s;
end;

function sMESSAGESELECTB(net: Integer; uid: PChar = nil; type_: Cardinal = Cardinal(-1); wflag: Cardinal = Cardinal(-1); woflag: Cardinal = Cardinal(-1)): sMESSAGESELECT; overload;
var
  s: sMESSAGESELECT;
begin
  s.s_size := SizeOf(s);
  s.net := net;
  s.uid := uid;
  s.type_ := type_;
  s.wflag := wflag;
  s.woflag := woflag;
  s.id := -1;
  s.position := 0;
  Result := s;
end;


end.
