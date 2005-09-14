unit PlugFunc;
{*
 * Konnekt Delphi SDK (Software Development Kit)
 *
 * Nag³ówek: plug Functions
 * Modyfikowany: 2005-09-13
 * Zgodny z wersj¹: 0.6.16.x
 * Info: Zestaw funkcji pomocniczych.
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
  Plug,
  PlugDefs,
  ui;

function ACTIONONLY(notify: sUIActionNotify_basePtr): Boolean;

function IconRegister(target: IML_enum; ID: Integer; const URL: PChar): Integer; overload;
function IconRegister(target: IML_enum; ID: Integer; inst: HINSTANCE; icoID: Integer; type_: Integer = 1): Integer; overload;
function IconRegister(target: IML_enum; ID: Integer; image: THandle; type_: Integer = 1): Integer; overload;

function UIActionAdd(parent: Integer; id: Integer; status: Integer = 0; const txt: PChar = nil; p1: Integer = 0; w: Smallint = 0; h: Smallint = 0; p2: Integer = 0; param: Integer = 0): Integer;
function UIActionInsert(parent: Integer; id: Integer; pos: Integer; status: Integer = 0; const txt: PChar = nil; p1: Integer = 0; w: Smallint = 0; h: Smallint = 0; p2: Integer = 0; param: Integer = 0): Integer;
function UIActionCfgAdd(parent: Integer; id: Integer; status: Integer = 0; const txt: PChar = nil; p1: Integer = 0; x: Smallint = 0; y: Smallint = 0; w: Smallint = 0; h: Smallint = 0; p2: Integer = 0; param: Integer = 0): Integer;
function UIActionCfgInsert(parent: Integer; id: Integer; pos: Integer; status: Integer = 0; const txt: PChar = nil; p1: Integer = 0; x: Smallint = 0; y: Smallint = 0; w: Smallint = 0; h: Smallint = 0; p2: Integer = 0; param: Integer = 0): Integer;
function UIGroupAdd(parent: Integer; id: Integer; status: Integer = 0; const txt: PChar = nil; p1: Integer = 0; w: Smallint = 0; h: Smallint = 0; p2: Integer = 0; param: Integer = 0): Integer;
function UIGroupInsert(parent: Integer; id: Integer; pos: Integer; status: Integer = 0; const txt: PChar = nil; p1: Integer = 0; w: Smallint = 0; h: Smallint = 0; p2: Integer = 0; param: Integer = 0): Integer;

function UIActionCfgSetValue(act: sUIAction; val: PChar; convert: Boolean = True): Integer;
function UIActionCfgGetValue(act: sUIAction; val: PChar; size: Integer; convert: Boolean = True): PChar;

implementation

function ACTIONONLY(notify: sUIActionNotify_basePtr): Boolean;
begin
  if (notify.code <> ACTN_ACTION) then
    Result := False
  else
    Result := True;
end;

function IconRegister(target: IML_enum; ID: Integer; const URL: PChar): Integer;
var
  ir: sUIIconRegister;
begin
  ir := sUIIconRegisterB();
  ir.URL := URL;
  ir.ID := ID;
  ir.target := target;
  ICMessage(IMI_ICONREGISTER , Integer(@ir) , 0);
  Result := ID;
end;

function IconRegister(target: IML_enum; ID: Integer; inst: HINSTANCE; icoID: Integer; type_: Integer = 1): Integer;
var
  ir: sUIIconRegister;
begin
  ir := sUIIconRegisterB();
  ir.ID := ID;
  ir.target := target;
  ir.imgInst := inst;
  ir.imgId := icoID;
  ir.imgType := type_;
  ICMessage(IMI_ICONREGISTER , Integer(@ir) , 0);
  Result := ID;
end;

function IconRegister(target: IML_enum; ID: Integer; image: THandle; type_: Integer = 1): Integer;
var
  ir: sUIIconRegister;
begin
  ir := sUIIconRegisterB();
  ir.ID := ID;
  ir.target := target;
  ir.imgHandle := image;
  ir.imgType := type_;
  ICMessage(IMI_ICONREGISTER , Integer(@ir) , 0);
  Result := ID;
end;

function UIActionAdd(parent: Integer; id: Integer; status: Integer = 0; const txt: PChar = nil; p1: Integer = 0; w: Smallint = 0; h: Smallint = 0; p2: Integer = 0; param: Integer = 0): Integer;
var
  ai: sUIActionInfo;
begin
  ai := sUIActionInfoB(parent, id, -1, status, txt, p1, w, h, p2, param);
  Result := ICMessage(IMI_ACTION, Integer(@ai), 0);
end;

function UIActionInsert(parent: Integer; id: Integer; pos: Integer; status: Integer = 0; const txt: PChar = nil; p1: Integer = 0; w: Smallint = 0; h: Smallint = 0; p2: Integer = 0; param: Integer = 0): Integer;
begin
  Result := Ctrl.UIActionInsert(parent, id, pos, status, txt, p1, w, h, p2, param);
end;

function UIActionCfgAdd(parent: Integer; id: Integer; status: Integer = 0; const txt: PChar = nil; p1: Integer = 0; x: Smallint = 0; y: Smallint = 0; w: Smallint = 0; h: Smallint = 0; p2: Integer = 0; param: Integer = 0): Integer;
var
  ai: sUIActionInfo_cfg;
begin
  ai := sUIActionInfo_cfgB(parent, id, -1, status, txt, p1, x, y, w, h, p2, param);
  Result := ICMessage(IMI_ACTION, Integer(@ai), 0);
end;

function UIActionCfgInsert(parent: Integer; id: Integer; pos: Integer; status: Integer = 0; const txt: PChar = nil; p1: Integer = 0; x: Smallint = 0; y: Smallint = 0; w: Smallint = 0; h: Smallint = 0; p2: Integer = 0; param: Integer = 0): Integer;
var
  ai: sUIActionInfo_cfg;
begin
  ai := sUIActionInfo_cfgB(parent, id, pos, status, txt, p1, x, y, w, h, p2, param);
  Result := ICMessage(IMI_ACTION, Integer(@ai), 0);
end;

function UIGroupAdd(parent: Integer; id: Integer; status: Integer = 0; const txt: PChar = nil; p1: Integer = 0; w: Smallint = 0; h: Smallint = 0; p2: Integer = 0; param: Integer = 0): Integer;
begin
  Result := UIActionAdd(parent, id, status or ACTS_GROUP, txt, p1, w, h, p2, param);
end;

function UIGroupInsert(parent: Integer; id: Integer; pos: Integer; status: Integer = 0; const txt: PChar = nil; p1: Integer = 0; w: Smallint = 0; h: Smallint = 0; p2: Integer = 0; param: Integer = 0): Integer;
begin
  Result := UIActionInsert(parent, id, pos, status or ACTS_GROUP, txt, p1, w, h, p2, param);
end;

function UIActionCfgGetValue(act: sUIAction; val: PChar; size: Integer; convert: Boolean = True): PChar;
var
  ai: sUIActionInfo;
begin
  ai.act := act;
  ai.mask := UIAIM_TXT;
  if (convert) then
    ai.mask := ai.mask or UIAIM_VALUE_CONVERT;
  ai.txt := val;
  ai.txtSize := size;
  ai.txt := PChar(ICMessage(IMI_ACTION_GETVALUE , Integer(@ai) , 0));
  Result := ai.txt;
end;

function UIActionCfgSetValue(act: sUIAction; val: PChar; convert: Boolean = True): Integer;
var
  ai: sUIActionInfo;
begin
  ai.act := act;
  ai.mask := UIAIM_TXT;
  if (convert) then
    ai.mask := ai.mask or UIAIM_VALUE_CONVERT;
  ai.txt := val;
  Result := ICMessage(IMI_ACTION_SETVALUE , Integer(@ai) , 0);
end;


end.
