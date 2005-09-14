unit ui;
{*
 * Konnekt Delphi SDK (Software Development Kit)
 *
 * Nag³ówek: UI shared
 * Modyfikowany: 2005-09-13
 * Zgodny z wersj¹: 0.6.16.x
 * Info: nag³ówek potrzebny przy korzystaniu z interfejsu dla Windowsa
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
  Plug;

function UIIcon(type_: Integer; net: Integer; id: Integer; frame: Integer): Integer;
    // typ - 4b | net - 8b | id - 16b | frame - 4b

const
  ICON_BLANK = $F;
  IT_LOGO = 2;
  IT_OVERLAY = 3;
  IT_STATUS = 4;
  IT_MESSAGE = 5;
  IT_BLANK_MASK = $80000000;

const
   IMIB_        = $FF000000;
   IMIB_CFG     = $11000000; ///< Maska dla ustawieñ programu.
   IMIB_CNT     = $13000000; ///< Maska dla ustawieñ kontaktu.
   IMIB_PROFILE = $12000000;

type IML_enum = (
  IML_NONE = $0,
  IML_16 = $1, ///< lista 16x16
  IML_32 = $2, ///< lista 32x32
  IML_ICO = $100,  ///< samodzielna ikonka (u¿ywana rzadko)
  IML_ICO2 = $200, ///< samodzielna ikonka 2 (u¿ywana bardzo rzadko)
  IML_BMP = $1000, ///< samodzielna bitmapa (u¿ywana rzadko)
  IML_16_32 = IML_16 or IML_32
  );

type
  tIconParams = packed record
    size: Smallint;
    bits: Shortint;
  end;

type
  sUIIconRegisterPrt = ^sUIIconRegister;
  sUIIconRegister = packed record
    s_size: Word;
    ID: Integer; ///< ID dodawanej ikonki.
    target: IML_enum;  ///< Listy do których zostanie przydzielona ikonka.
    URL: PChar; ///< URL kieruj¹cy do pliku/zasobu.
    imgType: Integer; ///< Typ obrazu - 0 - bitmapa, 1 - ikonka
    imgInst: Longword; ///< Biblioteka z której chcemy wczytaæ obraz
    imgId: Integer;   ///< Identyfikator obrazu
    imgHandle: THandle; ///< Uchwyt obrazu.
    case Integer of
      1: (maskHandle: THandle); ///< Uchwyt maski, jeœli w imgHandle jest Bitmapa.
      2: (iconParams: tIconParams);
  end;

function sUIIconRegisterB(): sUIIconRegister;

const
  ACTS_SHOW = 0;
  ACTS_HIDDEN = 1;
  ACTS_DISABLED = 2;
  ACTS_CHECKED = 4;
  ACTS_SELECTED = 8;
  ACTS_GROUP = $10;
  ACTSMENU_NOTRANS = $40;
  ACTSMENU_CHECKSPACE = $8000;
  ACTSMENU_BOLD = $100;
  ACTSBAR_BOTTOM = $20;
  ACTSBAR_NOALIGN = $40;
  ACTSBAR_VERT = $80;
  ACTSBAR_LOCKED = $100;
  ACTSBAND_FULL = $100;
  ACTSBAND_WRAP = $400;
  ACTSTB_DARROWS = $20;
  ACTSTB_MIXED = $40;
  ACTSTB_LIST = $80;
  ACTSTB_SHOWTEXT = $1000;
  ACTSTB_WHOLEDROPDOWN = $200;
  ACTSTB_WRAP = ACTSBAND_WRAP;
  ACTSTB_OPAQUE = $800;
  ACTSC_INT = $20;
  ACTSC_INLINE = $40;
  ACTSC_FULLWIDTH = $80;
  ACTSC_BOLD = $100;
  ACTSC_NEEDRESTART = $200;
  ACTSCOMBO_LIST = $1000;
  ACTSCOMBO_SORT = $2000;
  ACTSCOMBO_BYPOS = $4000;
  ACTSCOMBO_NOICON = $8000;
  ACTSRADIO_BYPOS = $1000;
  ACTSRADIO_LAST = $2000;
  ACTSTIME_SHOWNONE = $1000;
  ACTSTIME_UPDOWN = $2000;
  ACTSFONT_CHECKBOX = $4000;
  ACTSFONT_NOCOLOR = $8000;
  ACTSFONT_NOBGCOLOR = $400;
  ACTSFONT_NOSIZE = $800;
  ACTSFONT_NOFACE = $1000;
  ACTSFONT_NOSTYLE = $2000;
  ACTSCOLOR_CHECKBOX = $1000;
  ACTSINFO_CENTER = $1000;
  ACTSBUTTON_ALIGNRIGHT = $1000;

const
  ACTT_SEP = $10000;
  ACTT_SEPARATOR = ACTT_SEP;
  ACTT_BREAK = $20000;
  ACTT_BARBREAK = $30000;
  ACTT_BAND = $40000;
  ACTT_HWND = $50000;
  ACTT_CHECK = $60000;
  ACTT_CHECKGROUP = $70000;
  ACTT_INFO = $80000;
  ACTT_COMMENT = $90000;
  ACTT_HOLDER = $A0000;
  ACTT_EDIT = $B0000;
  ACTT_TEXT = $C0000;
  ACTT_PASSWORD = $D0000;
  ACTT_BUTTON = $E0000;
  ACTT_GROUP = $F0000;
  ACTT_GROUPEND = $100000;
  ACTT_IMAGE = $110000;
  ACTT_FILE = $120000;
  ACTT_DIR = $130000;
  ACTT_COLOR = $140000;
  ACTT_FONT = $150000;
  ACTT_COMBO = $160000;
  ACTT_TIME = $170000;
  ACTT_HTMLINFO = $180000;
  ACTT_RADIO = $190000;
	ACTT_SPINNER = $1A0000;
  ACTT_SLIDER = $1B0000;
	ACTT_TIPBUTTON = $1C0000;

const
  ACTR_INIT = $1000000;
  ACTR_SHOW = $2000000;
  ACTR_SAVE = $4000000;
  ACTR_CHECK = $8000000;
  ACTR_RESIZE = $10000000;
  ACTR_STATUS = $20000000;
  ACTR_SETCNT = $20000000;
  ACTR_CONVERT = $40000000;
  ACTR_GETSET = ACTR_CONVERT;
  ACTR_NODATASTORE = $80000000;

const
  ACTN_ACTION = 1;
  ACTN_GROUP = 2;
  ACTN_CREATE = 10;
  ACTN_CREATEGROUP = 19;
  ACTN_DESTROY = 11;
  ACTN_SHOW = 12;
  ACTN_HIDE = 13;
  ACTN_SAVE = 14;
  ACTN_RESIZE = 15;
  ACTN_STATUS = 16;
  ACTN_DEFAULT = 17;
  ACTN_SETCNT = 18;
  ACTN_CHECK = 100;
  ACTN_GET = 101;
  ACTN_SET = 102;
  ACTN_CONVERT_TO = 103;
  ACTN_CONVERT_FROM = 104;
  ACTN_FILEOPEN = 201;
  ACTN_FILEOPENED = 202;
  ACTN_DROP = 210;
  ACTN_CREATEWINDOW = 220;
  ACTN_DESTROYWINDOW = 221;
  
const
  AP_VALUE = Chr(2);
  AP_ICO = Chr(3);
  AP_PARAMS = Chr(4);
  AP_RADIOGRP = EXT_PARAM + 'grp=';
  AP_MINIMUM = EXT_PARAM + 'min=';
  AP_MAXIMUM = EXT_PARAM + 'max=';
  AP_STEP = EXT_PARAM + 'step=';
  AP_TIP_OBSOLETE = Chr(1);
  AP_TIP = EXT_PARAM + 'tip=';
  AP_TIP_WIDTH = EXT_PARAM + 'tipWidth=';
  AP_TIPRICH = EXT_PARAM + 'tipRich=';
	AP_TIPRICH_WIDTH = AP_TIP_WIDTH;
  AP_TIPTITLE = EXT_PARAM + 'tipTitle=';
  AP_TIPIMAGEURL = EXT_PARAM + 'tipImg=';
  AP_TIPICON = EXT_PARAM + 'tipIco=';
  AP_TIPICONURL = EXT_PARAM + 'tipIcoUrl=';
  AP_IMGURL = EXT_PARAM + 'imgurl=';
  AP_ICONSIZE = EXT_PARAM + 'iconsize=';
  AP_ICONDEPTH = EXT_PARAM + 'icondepth=';
  AP_MINWIDTH = EXT_PARAM + 'minWidth=';
  AP_MINHEIGHT = EXT_PARAM + 'minHeigt=';
  AP_MAXWIDTH = EXT_PARAM + 'maxWidth=';
  AP_MAXHEIGHT = EXT_PARAM + 'maxHeight=';
  AP_BESTWIDTH = EXT_PARAM + 'best-Width=';
  AP_BESTHEIGHT = EXT_PARAM + 'bestHeight=';
  CFGVALUE = AP_VALUE;
  CFGICO = AP_ICO;
  CFGTIP = AP_TIP;


implementation

function UIIcon(type_: Integer; net: Integer; id: Integer; frame: Integer): Integer;
begin
  Result := (((frame)and $F) or (((id) and $FFFF) shl 4) or (((net) and $FF) shl 20) or (((type_) and $F) shl 28));
end;

function sUIIconRegisterB(): sUIIconRegister;
var
  ir: sUIIconRegister;
begin
  ir.s_size := SizeOf(ir);
  ir.target := IML_NONE;
  ir.URL := nil;
  ir.imgHandle := 0;
  ir.maskHandle := 0;
  ir.imgInst := 0;
  ir.imgId := 0;
  ir.imgType := 0;
  Result := ir;
end;

end.
