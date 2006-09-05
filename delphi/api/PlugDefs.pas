unit PlugDefs;
{*
 * Konnekt Delphi SDK (Software Development Kit)
 *
 * Nag³ówek: Plugin Functions Definitions
 * Modyfikowany: 2006-08-31
 * Zgodny z wersj¹: 0.6.22.x
 * Info: Cia³a f-cji.
 *
 * Œrodowisko: Borland Delphi 7
 *
 * http://www.konnekt.info/
 *
 * (C) 2002-2006 Stamina
 * SDK s³u¿y do przygotowywania oprogramowania wspó³pracuj¹cego
 * z programem Konnekt. Autorzy nie ponosz¹ ¿adnej odpowiedzialnoœci
 * za wykorzystanie tego kodu.
 * Kod zawarty w SDK mo¿e byæ u¿ywany tylko w projektach dotycz¹cych
 * programu Konnekt! 
 *}

interface

uses
  Plug, UI, StrUtils;

{ Funkcje pomocnicze }
procedure IMLOG(const format: string; const Args: array of const);
function IMessage(id: Cardinal; net: Integer = 0; type_: Cardinal = 4294967295; p1: Integer = 0; p2: Integer = 0): Integer; overload;
function IMessage(msg: sIMessage_basePtr): Integer; overload;
function ICMessage(id: Cardinal; p1: Integer = 0; p2: Integer = 0): Integer; overload;
function IMessageDirect(id: Cardinal; plug: Cardinal; p1: Integer = 0; p2: Integer = 0): Integer; overload;
function IMessageDirect(plug: Cardinal; msg: sIMessage_basePtr): Integer; overload;
procedure WMProcess();
procedure IMDEBUG(level: enDebugLevel; const format: PChar; const args: array of const);
function SetColumn(table: tTable; id: Integer; type_: Integer; def: Integer; const name: PChar): Integer; overload;
function SetColumn(table: tTable; id: Integer; type_: Integer; def: PChar; const name: PChar): Integer; overload;

function GETSTR(id: Integer; buff: PChar = nil; size: Cardinal = 0): PChar;
function GETINT(id:integer):integer;
function SETINT(id:integer;val:integer;mask:integer = -1):boolean;
function SETCNTI(row:integer;id:integer;val:integer;mask:integer = -1):boolean;
function SETCNTC(row:integer;id:integer;const val:pchar):boolean;

function SETSTR(id:integer; buff:Pchar=nil):boolean;
function GETSTRA(id: Integer): PChar;
function GETCNTI(row: Integer; id:Integer): Integer;
function GETCNTC(row:integer; id:integer; buff:pchar=nil ; size:cardinal=0):Pchar;
function Plug_Init(p1: Integer; p2: Integer): Integer;
procedure Plug_Deinit(p1: Integer; p2: Integer);
function SetExtParam(const ext:String;const name:String;const value:String):String;
function GetExtParam(const ext :String; const name:String):String;

var
  Ctrl: cCtrl;

implementation

procedure IMLOG(const format: string; const Args: array of const);
begin
  Ctrl.IMLOG(format, Args);
end;

function IMessage(id: Cardinal; net: Integer = 0; type_: Cardinal = 4294967295; p1: Integer = 0; p2: Integer = 0): Integer;
begin
  Result := Ctrl.IMessage(id, net, type_, p1, p2);
end;

function IMessage(msg: sIMessage_basePtr): Integer;
begin
  Result := Ctrl.IMessage(msg);
end;

function ICMessage(id: Cardinal; p1: Integer = 0; p2: Integer = 0): Integer;
begin
  Result := Ctrl.ICMessage(id , p1 , p2);
end;

function IMessageDirect(id: Cardinal; plug: Cardinal; p1: Integer = 0; p2: Integer = 0): Integer;
begin
  Result := Ctrl.IMessageDirect(id , plug , p1 , p2);
end;

function IMessageDirect(plug: Cardinal; msg: sIMessage_basePtr): Integer;
begin
  Result := Ctrl.IMessageDirect(plug , msg);
end;

procedure WMProcess();
begin
  Ctrl.WMProcess();
end;

procedure IMDEBUG(level: enDebugLevel; const format: PChar; const args: array of const);
begin
  if Ctrl.DebugLevel(level) <> 0 then
    Ctrl.IMLOG_(level, format, args);
end;

function SetColumn(table: tTable; id: Integer; type_: Integer; def: Integer; const name: PChar): Integer;
begin
  Result := Ctrl.SetColumn(table, id, type_, def, name);
end;

function SetColumn(table: tTable; id: Integer; type_: Integer; def: PChar; const name: PChar): Integer;
begin
  Result := Ctrl.SetColumn(table, id, type_, def, name);
end;

function Plug_Init(p1: Integer; p2: Integer): Integer;
begin
  Ctrl := cCtrl.Create(p1);
  Result := 1;
end;

procedure Plug_Deinit(p1: Integer; p2: Integer);
begin
  Ctrl.Destroy();
  Ctrl := nil;
end;

function GETCNTI(row: Integer; id:Integer): Integer;
var
  v: sDTValue;
begin
  v := sDTValueB(DT_CT_INT);
  Ctrl.DTget(DTCNT, row, id, @v);
  Result := v.vInt;
end;

function GETSTR(id: Integer; buff: PChar = nil; size: Cardinal = 0): PChar;
var
  v: sDTValue;
begin
  v := sDTValueB(DT_CT_STR);
  v.vChar := buff;
  v.buffSize := size;
  Ctrl.DTget(DTCFG, 0, id, @v);
  Result := v.vChar;
end;

function GETCNTC(row:integer; id:integer; buff:pchar=nil; size:cardinal=0):Pchar;
var
  v: sDTValue;
begin
  v := sDTValueB(DT_CT_STR);
  v.vChar := buff;
  v.buffSize := size;
  Ctrl.DTget(DTCNT, row, id, @v);
  Result := v.vChar;
end;

function GETINT(id:integer):integer;
var
  v: sDTValue;
begin
  v := sDTValueb(DT_CT_INT);
  v.buffSize := 4;
  Ctrl.DTget(DTCFG, 0, id, @v);
  Result := v.vInt;
end;

function GETSTRA(id: Integer): PChar;
begin
  Result := GETSTR(id, nil, 4294967295);
end;

function SETINT(id:integer;val:integer;mask:integer = -1):boolean;
var
  v: sDTValue;
begin
  v := sDTValueb(DT_CT_INT);
  if (mask <> -1) then
    begin
    Ctrl.DTget(DTCFG, 0, id, @v);
    v.vInt:=(v.vInt and (not mask)) or val;
    result:=Ctrl.DTset(DTCFG , 0 , id, @v);
    end
  else
    begin
    v.vInt:= val;
    result:= Ctrl.DTset(DTCFG , 0 , id, @v);
    end;
end;

function SETCNTI(row:integer;id:integer;val:integer;mask:integer = -1):boolean;
var
  v: sDTValue;
begin
  v := sDTValueb(DT_CT_INT);
  if (mask <> -1) then
    begin
    Ctrl.DTget(DTCNT, row, id, @v);
    v.vInt:=(v.vInt and (not mask)) or val;
    result:=Ctrl.DTset(DTCNT, row, id, @v);
    end
  else
    begin
    v.vInt:= val;
    result:= Ctrl.DTset(DTCNT, row, id, @v);
    end;
end;

function SETCNTC(row:integer;id:integer;const val:pchar):boolean;
var
  v: sDTValue;
begin
  v := sDTValueb(DT_CT_PCHAR);
  v.vChar := val;
  result := Ctrl.DTset(DTCNT, row, id, @v);
end;

function SETSTR(id:integer;buff:Pchar=nil):boolean;
var
  v: sDTValue;
begin
  v := sDTValueb(DT_CT_STR);
  v.vChar := buff;
  v.buffSize := sizeof(buff);
  result := Ctrl.DTset(DTCFG, 0, id, @v);
end;

function GetExtParam(const ext :String; const name:String):String;
var
  Start:Integer;
  End_ :Integer;
begin
  Result := '';
  if name = '' then Exit;
  start := Pos(EXT_PARAM_CHAR + name + '=', ext);
  if (start = 0) then Exit;
  Inc(Start, Length(name) + 2);
  end_ :=  PosEx(EXT_PARAM_CHAR , ext, start);
  if end_ = 0 then
    end_ := Length(Ext) - (start -1)
  else
    end_ := end_ - start;
  Result := Copy(ext, start, end_);
end;

function SetExtParam(const ext:String;const name:String;const value:String):String;
var
  Start:Integer;
  End_ :Integer;
begin
  Result := Ext;
  if name = ''  then
    Exit;
  Start := Pos(EXT_PARAM_CHAR + name + '=', ext);
  if start = 0 then
    End_ := 0
  else
    End_ := PosEx(EXT_PARAM_CHAR, ext , start + 1);
  if Start = 0 then
    Start := Length(ext);
  Result := Copy(ext, 1, start) + EXT_PARAM_CHAR + name + '=' + value;
  if End_ <> 0 then
    Result := Result + Copy(Ext, End_, Length(Ext));
end;

end.
