library template;
{  TEMPLATE.DPR
   Przyk³adowa wtyczka dla programu Konnekt...
   Idealny sposób ¿eby zacz¹æ pisaæ coœ swojego ...

   (c)2002 hao | Stamina
   (c)2005 Winthux
   http://www.konnekt.info
}

uses
  Plug in '..\..\api\plug.pas',
  PlugDefs in '..\..\api\plugdefs.pas',
  ui in '..\..\api\ui.pas';

{$R *.res}
const
  version: PChar = '0.0.0.0';
  name: PChar = 'Template';
  sig: PChar = 'tpl';

//---------------------------------------------------------------------------
{ Wszystkie poni¿sze funkcje nie s¹ wymagane (z wyj¹tekim IMEssageProc)...
   ale z nimi wszystko wygl¹da czytelniej :)
}
function Init(): Integer;
begin
    {  Tutaj inicjalizujemy wtyczkê,
       zg³aszamy ¿¹dania po³¹czeñ itp. }
  Result := 1;
end;

function DeInit(): Integer;
begin
  {  Najlepsze miejsce ¿eby posprz¹taæ...
  }
  Result := 1;
end;

function IStart(): Integer;
begin
  { Tutaj wtyczkê uruchamiamy }
  Result := 1;
end;

function IEnd(): Integer;
begin
  { Tutaj wtyczkê wy³¹czamy }
  Result := 1;
end;

function ISetCols(): Integer;
begin
  {  Tutaj rejestrujemy kolumny w plikach ustawieñ.
     Pamiêtaj o tym ¿e identyfikatory MUSZ¥ byæ UNIKATOWE! }
  Result := 1;
end;

function IPrepare(): Integer;
begin
  { Tutaj rejestrujemy sie w interfejsie }
  Result := 1;
end;

function ActionCfgProc(const anBase: sUIActionNotify_basePtr): Integer;
{  Tutaj obs³ugujemy akcje dla okna konfiguracji
   Sytuacja taka sama jak przy ActionProc  }
var
  an: sUIActionNotify_2paramsPtr;
begin
  an := sUIActionNotify_2paramsPtr(anBase);

  case (anBase.act.id and not IMIB_CFG) of
    IMIB_CFG:;     // cos musi byc, nie da sie tak jak w c/c++ pusty switch
  end;

  Result := 0;
end;

function ActionProc(const anBase: sUIActionNotify_basePtr): Integer;
{ Tutaj obs³ugujemy akcje }
  {  Poni¿sza linijka s³u¿y TYLKO waszej wygodzie!
     Wiêkszoœæ (o ile nie wszystkie) powiadomieñ przesy³ana jest jako sUIActionNotify_2params,
     korzystamy wtedy z obiektu an, w przeciwnym razie z anBase, lub castujemy do spodziewanego typu.
  }
var
  an: sUIActionNotify_2paramsPtr;
begin
  an := sUIActionNotify_2paramsPtr(anBase);

  if ((anBase.act.id and IMIB_) = IMIB_CFG) then
    Result := ActionCfgProc(anBase)
  else
    begin
      case (anBase.act.id) of
        IMIB_:;       // cos musi byc w case of, inaczej blad kompilator wywala
      end;
      Result := 0;
    end;
end;

function IMessageProc(const msgBase: sIMessage_basePtr): Integer; stdcall;
 { Tam gdzie nie u¿ywasz parametrów, najbezpieczniej korzystaæ z msgBase }
    {Wiêkszoœæ (o ile nie wszystkie) wiadomoœci przesy³ana jest jako sIMessage_2params,
     korzystamy wtedy z obiektu msg, w przeciwnym razie z msgBase, lub castujemy do spodziewanego typu.
    }
var
  msg: sIMessage_2paramsPtr;
  ret: Integer;

begin
  msg := sIMessage_2paramsPtr(msgBase);
  ret := -1;

  case msgBase.id of
    { Wiadomoœci na które TRZEBA odpowiedzieæ }
    IM_PLUG_NET: ret := 0;  // Zwracamy wartoœæ NET, która MUSI byæ ró¿na od 0!
    IM_PLUG_TYPE: ret := 0;   // Zwracamy jakiego typu jest nasza wtyczka (które wiadomoœci bêdziemy obs³ugiwaæ)
    IM_PLUG_VERSION: ret := Integer(version); // Wersja wtyczki tekstowo major.minor.release.build ..., lub 0 je¿eli wersja zapisana jest w zasobach DLLa
    IM_PLUG_SDKVERSION: ret := KONNEKT_SDK_V; // Ta linijka jest wymagana!
    IM_PLUG_SIG: ret :=  Integer(sig); // Sygnaturka wtyczki (krótka, kilkuliterowa nazwa)
    IM_PLUG_NAME: ret := Integer(name); // Pe³na nazwa wtyczki (ale najlepiej nie za d³uga!)
    IM_PLUG_NETNAME: ret := 0; // Nazwa obs³ugiwanej sieci (o ile jak¹œ sieæ obs³uguje)
    IM_PLUG_INIT:
      begin
        Plug_Init(msg.p1, msg.p2);
        ret := Init();
      end;
    IM_PLUG_DEINIT:
      begin
        Plug_Deinit(msg.p1, msg.p2);
        ret := DeInit();
      end;

    IM_SETCOLS: ret:= ISetCols();

    IM_UI_PREPARE: ret := IPrepare();
    IM_START: ret := IStart();
    IM_END: ret := IEnd();

    IM_UIACTION: ret := ActionProc(sUIActionNotify_basePtr(msg.p1));
  end;

  { Tutaj obs³ugujemy wszystkie pozosta³e komunikaty }
  { Z ka¿dego komunikatu trzeba zwracaæ wartoœæ wiêksz¹ od 0. W przeciwnym razie,
    zostanie ustawiony b³¹d i komunikat zostanie uznany za nie obs³u¿ony }


  if Assigned(Ctrl) and (ret < 0) then
  begin
    Ctrl.setError(IMERROR_NORESULT);
    ret := 0;
  end;

  Result := ret;
end;

exports
  IMessageProc;

begin
end.
