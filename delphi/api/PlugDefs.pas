unit PlugDefs;
{*
 * Konnekt Delphi SDK (Software Development Kit)
 * 
 * Nag³ówek: plug Functions Definitions
 * Modyfikowany: 2005-09-13
 * Zgodny z wersj¹: 0.6.16.x
 * Info: Cia³a f-cji.
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
function GETSTRA(id: Integer): PChar;
function GETCNTI(row: Integer; id:Integer): Integer;

function Plug_Init(p1: Integer; p2: Integer): Integer;
procedure Plug_Deinit(p1: Integer; p2: Integer);

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

function GETSTRA(id: Integer): PChar;
begin
  Result := GETSTR(id, nil, 4294967295);
end;


end.
 