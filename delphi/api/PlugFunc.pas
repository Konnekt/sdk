unit PlugFunc;
{*
 * Konnekt Delphi SDK (Software Development Kit)
 *
 * Nag³ówek: Plugin functions
 * Modyfikowany: 2006-08-31
 * Zgodny z wersj¹: 0.6.22.x
 * Info: Zestaw funkcji pomocniczych.
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
  Plug,
  PlugDefs,
  UI, Windows;

function ACTIONONLY(notify: sUIActionNotify_basePtr): Boolean;
function IconRegister(target: IML_enum; ID: Integer; const URL: PChar): Integer; overload;
function IconRegister(target: IML_enum; ID: Integer; inst: HINSTANCE; icoID: Integer; type_: Integer = 1): Integer; overload;
function IconRegister(target: IML_enum; ID: Integer; image: THandle; type_: Integer = 1): Integer; overload;
function UIActionGet(nfo:sUIActionInfo):Integer;
function UIActionAdd(parent: Integer; id: Integer; status: Integer = 0; const txt: PChar = nil; p1: Integer = 0; w: Smallint = 0; h: Smallint = 0; p2: Integer = 0; param: Integer = 0): Integer;
function UIActionInsert(parent: Integer; id: Integer; pos: Integer; status: Integer = 0; const txt: PChar = nil; p1: Integer = 0; w: Smallint = 0; h: Smallint = 0; p2: Integer = 0; param: Integer = 0): Integer;
function UIActionCfgAdd(parent: Integer; id: Integer; status: Integer = 0; const txt: PChar = nil; p1: Integer = 0; x: Smallint = 0; y: Smallint = 0; w: Smallint = 0; h: Smallint = 0; p2: Integer = 0; param: Integer = 0): Integer;
function UIActionCfgInsert(parent: Integer; id: Integer; pos: Integer; status: Integer = 0; const txt: PChar = nil; p1: Integer = 0; x: Smallint = 0; y: Smallint = 0; w: Smallint = 0; h: Smallint = 0; p2: Integer = 0; param: Integer = 0): Integer;
function UIActionSetStatus(act:sUIAction ;status:integer;mask:integer = -1):integer;
function UIActionGetPos(parent:integer; id:integer):integer;
function UIGroupAdd(parent: Integer; id: Integer; status: Integer = 0; const txt: PChar = nil; p1: Integer = 0; w: Smallint = 0; h: Smallint = 0; p2: Integer = 0; param: Integer = 0): Integer;
function UIGroupInsert(parent: Integer; id: Integer; pos: Integer; status: Integer = 0; const txt: PChar = nil; p1: Integer = 0; w: Smallint = 0; h: Smallint = 0; p2: Integer = 0; param: Integer = 0): Integer;
function UIActionSetText(act:sUIAction ; const txt:pchar): integer; overload;
function UIActionSetText(parent:integer; id:integer; const txt:pchar): integer; overload;
function UIActionCfgSetValue(act: sUIAction; val: PChar; convert: Boolean = True): Integer;
function UIActionCfgGetValue(act: sUIAction; val: PChar; size: Integer; convert: Boolean = True): PChar;
function UIGroupHandle(act:sUIAction):integer;
function CntGetInfoValue(fromWindow:boolean ; cntID:cardinal;colID:cardinal):pchar;
procedure CntSetInfoValue(toWindow:boolean ; cntID:integer; colID:integer ; const value:pchar);
function CntSetStatus(status,cntid:integer;info:pchar):integer;
function PlugStatusChange(status:integer;info:pchar):integer;
function IMessage_msgBox(id:cardinal; msg:pchar=nil ; title:pchar=nil ; flags:integer = 0 ; parent:thandle = 0):integer;
procedure UIActionCfgAddPluginInfoBox2(parent:cardinal; const info:pchar; const about_info:pchar; const ico:pchar = nil; height:integer = 0; const name:pchar = nil; frame:boolean = true);

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

function UIActionGet(nfo:sUIActionInfo):Integer;
begin
  Result := ICMessage(IMI_ACTION_GET, Integer(@nfo), 0);
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

function UIActionGetPos(parent:integer; id:integer):integer;
var
  ai:sUIActionInfo;
begin
  ai.act.parent := parent;
  ai.act.id := id;
  ai.act.cnt := 0;
  ai.mask := UIAIM_POS;
  ICMessage(IMI_ACTION_GET, integer(@ai), 0);
  result := ai.pos;
end;

function UIActionSetStatus(act:sUIAction ;status:integer;mask:integer = -1):integer;
var
  ai:sUIActionInfo;
begin
  ai.act := act;
  ai.mask := UIAIM_STATUS;
  ai.status := status;
  ai.statusMask := mask;
  result := ICMessage(IMI_ACTION_SET, integer(@ai), 0);
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

function UIActionSetText(parent:integer; id:integer; const txt:pchar):integer;
var
  act: sUIAction;
begin
  act := sUIActionB(parent, id);
  result := UIActionSetText(act, txt);
end;

function UIActionSetText(act:sUIAction ; const txt:pchar):integer;
var
  ai:sUIActionInfo;
begin
  ai.act := act;
  ai.mask := UIAIM_TXT;
  ai.txt := txt;
  result := ICMessage(IMI_ACTION_SET, integer(@ai) , 0);
end;

function UIGroupHandle(act:sUIAction):integer;
begin
  Result := ICMessage(IMI_GROUP_GETHANDLE, integer(@act) , 0);
end;

function CntGetInfoValue(fromWindow:boolean; cntID:cardinal; colID:cardinal):pchar;
var
  sui:sUIAction;
  su:sUIAction;
begin
  if (not fromWindow) then
    result:= Ctrl.DTgetStr(DTCNT , cntID , colID, nil, 0)
  else
    begin
    sui.id := colID or IMIB_CNT;
    sui.parent := IMIG_NFO;
    sui.cnt:=0;
    su.id := colID or IMIB_CNT;
    su.parent:=ICMessage(IMI_ACTION_FINDPARENT , integer(@sui),0);
    su.cnt := cntID;
    result := UIActionCfgGetValue(su , nil, 0 , true);
  end;
end;

procedure CntSetInfoValue(toWindow:boolean ; cntID:integer; colID:integer ; const value:pchar);
var
  sui:sUIAction;
  su:sUIAction;
begin
  if (not (toWindow)) then
    begin
    Ctrl.DTsetStr(DTCNT , cntID , colID , value);
    end
  else
    begin
    sui.id := colID or IMIB_CNT;
    sui.parent := IMIG_NFO;
    sui.cnt := 0;
    su.id := colID or IMIB_CNT;
    su.parent := ICMessage(IMI_ACTION_FINDPARENT, integer(@sui),0);
    su.cnt := cntID;
    UIActionCfgSetValue(su, value, true);
    end;
end;

function CntSetStatus(status,cntid:integer;info:pchar):integer;
var
  IMessage_StatusChange: sIMessage_StatusChange;
begin
  IMessage_StatusChange.sm.size := sizeof(IMessage_StatusChange);
  IMessage_StatusChange.sm.id := 234;
  IMessage_StatusChange.sm.flag := 0;
  IMessage_StatusChange.sm.net := 0;
  IMessage_StatusChange.sm.type_ := 0;
  IMessage_StatusChange.sm.sender := 0;
  IMessage_StatusChange.cntID := cntid;
  IMessage_StatusChange.status := status;
  IMessage_StatusChange.info := info;
  result := IMessage(@IMessage_StatusChange);
end;

function PlugStatusChange(status:integer;info:pchar):integer;
var
  IMessage_StatusChange: sIMessage_StatusChange;
begin
  IMessage_StatusChange.sm.size := sizeof(IMessage_StatusChange);
  IMessage_StatusChange.sm.id := IMC_STATUSCHANGE;
  IMessage_StatusChange.sm.flag := 0;
  IMessage_StatusChange.sm.net := 0;
  IMessage_StatusChange.sm.type_ := 0;
  IMessage_StatusChange.sm.sender := 0;
  IMessage_StatusChange.cntID := 0;
  IMessage_StatusChange.status := status;
  IMessage_StatusChange.info := info;
  result := IMessage(@IMessage_StatusChange);
end;

function IMessage_msgBox(id:cardinal; msg:pchar=nil ;title:pchar=nil; flags:integer = 0 ; parent:thandle = 0):integer;
var
  s:sIMessage_msgBox;
begin
  s.sm.flag := 0;
  s.sm.net := 0;
  s.sm.type_ := 0;
  s.sm.sender := 0;
  s.sm.id := id;
  s.sm.size := sizeof(s);
  s.msg := msg;
  s.flags := flags;
  s.title := title;
  s.parent := parent;
  result := IMessage(@s);

  {case id of
  IMI_WARNING:id:=MB_ICONWARNING;
  IMI_ERROR:id:=MB_ICONERROR;
  IMI_CONFIRM:id:=MB_ICONQUESTION;
  IMI_INFORM:id:=MB_ICONINFORMATION;
  end;
  if parent=0 then parent:=GetForeGroundWindow;
  MessageBox(parent,msg,title,id); }
end;

function ParamSpecialChar(ch:byte) :boolean;
begin
  if ((ch < $8 ) or (ch = $1A)) then
    result := true
  else
    result := false;
end;

function ActParamExists(const txt:string; const param:String):boolean;
begin
  if (param = '') then
    begin
    if (length(txt) > 0) then
      begin
      result := not ParamSpecialChar(ord(txt[1]));
      Exit;
      end;
    end
  else
    begin
    result := true;
    Exit;
    end;
  if pos(param,txt) <> 0 then 
    result := true
  else
    result := false;
end;

function SetActParam(const txt:string ; const param:String ;const value:String):string;
var
  start:cardinal;
  endt:integer;
begin
  start := pos(AP_PARAMS,txt);
  if (start =0)then
    start := 1;
  if (param<>'') then
  begin
    start := pos(param,copy(txt,start,length(txt)));
  end;
  endt := start;
  if (param='') then start := 1;
  while ((endt <> 1) and (endt < length(txt)) and (not ParamSpecialChar(ord(txt[endt])))) do
  inc(endt,1);
  result:= copy(txt,1 , start) + param + value+copy(txt,endt,length(txt));
end;


procedure UIActionCfgAddPluginInfoBox2(parent:cardinal; const info:pchar; const about_info:pchar; const ico:pchar = nil; height:integer = 0; const name:pchar = nil; frame:boolean = true);
var
  tip:string;
  txt:String;
  ver:array [0..49] of char;
begin
  if (frame) then
  UIActionAdd(parent , 0 , ACTT_GROUP ,  '');
    if (name<>nil) then
    tip := name
    else
      begin
        tip := Pchar(IMessageDirect(IM_PLUG_NAME, 0, 0, 0));
        ver[0]:=#0;
        ICMessage(IMC_PLUG_VERSION, ICMessage(IMC_PLUGID_POS, ctrl.id, 0),  integer(@ver));
        if (ctrl.getError() <> IMERROR_NORESULT) then
          begin
          tip := tip+' ';
          tip := tip+ver;
          end;
      end;
    if not (tip='')  then tip := '<b>' + tip + '</b><br/>';
    if (about_info<>nil) then tip := tip+ about_info;
    if (ico<>nil) then
      begin
      txt := SetActParam(txt, AP_IMGURL, ico);
      //if (not ActParamExists(txt, AP_ICONSIZE)) then
      txt := SetActParam(txt, AP_ICONSIZE, '32');
      end;
    txt := SetActParam(txt, AP_TIPRICH, tip);
    txt := SetActParam(txt, AP_TIPRICH_WIDTH, '300');
    UIActionAdd(parent , 0 , ACTT_TIPBUTTON or ACTSC_INLINE , pchar(txt) , 0 , 40 , 40);
    UIActionCfgAdd(parent , 0 , ACTT_HTMLINFO or ACTSC_FULLWIDTH , pchar(info) , 0 , 0, 0, 300 , height);
  if (frame) then UIActionAdd(parent , 0 , ACTT_GROUPEND);
end;

end.
