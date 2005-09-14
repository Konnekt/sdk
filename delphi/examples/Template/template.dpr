library template;
{  TEMPLATE.DPR
   Przyk�adowa wtyczka dla programu Konnekt...
   Idealny spos�b �eby zacz�� pisa� co� swojego ...

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
{ Wszystkie poni�sze funkcje nie s� wymagane (z wyj�tekim IMEssageProc)...
   ale z nimi wszystko wygl�da czytelniej :)
}
function Init(): Integer;
begin
    {  Tutaj inicjalizujemy wtyczk�,
       zg�aszamy ��dania po��cze� itp. }
  Result := 1;
end;

function DeInit(): Integer;
begin
  {  Najlepsze miejsce �eby posprz�ta�...
  }
  Result := 1;
end;

function IStart(): Integer;
begin
  { Tutaj wtyczk� uruchamiamy }
  Result := 1;
end;

function IEnd(): Integer;
begin
  { Tutaj wtyczk� wy��czamy }
  Result := 1;
end;

function ISetCols(): Integer;
begin
  {  Tutaj rejestrujemy kolumny w plikach ustawie�.
     Pami�taj o tym �e identyfikatory MUSZ� by� UNIKATOWE! }
  Result := 1;
end;

function IPrepare(): Integer;
begin
  { Tutaj rejestrujemy sie w interfejsie }
  Result := 1;
end;

function ActionCfgProc(const anBase: sUIActionNotify_basePtr): Integer;
{  Tutaj obs�ugujemy akcje dla okna konfiguracji
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
{ Tutaj obs�ugujemy akcje }
  {  Poni�sza linijka s�u�y TYLKO waszej wygodzie!
     Wi�kszo�� (o ile nie wszystkie) powiadomie� przesy�ana jest jako sUIActionNotify_2params,
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
 { Tam gdzie nie u�ywasz parametr�w, najbezpieczniej korzysta� z msgBase }
    {Wi�kszo�� (o ile nie wszystkie) wiadomo�ci przesy�ana jest jako sIMessage_2params,
     korzystamy wtedy z obiektu msg, w przeciwnym razie z msgBase, lub castujemy do spodziewanego typu.
    }
var
  msg: sIMessage_2paramsPtr;
  ret: Integer;

begin
  msg := sIMessage_2paramsPtr(msgBase);
  ret := -1;

  case msgBase.id of
    { Wiadomo�ci na kt�re TRZEBA odpowiedzie� }
    IM_PLUG_NET: ret := 0;  // Zwracamy warto�� NET, kt�ra MUSI by� r�na od 0!
    IM_PLUG_TYPE: ret := 0;   // Zwracamy jakiego typu jest nasza wtyczka (kt�re wiadomo�ci b�dziemy obs�ugiwa�)
    IM_PLUG_VERSION: ret := Integer(version); // Wersja wtyczki tekstowo major.minor.release.build ..., lub 0 je�eli wersja zapisana jest w zasobach DLLa
    IM_PLUG_SDKVERSION: ret := KONNEKT_SDK_V; // Ta linijka jest wymagana!
    IM_PLUG_SIG: ret :=  Integer(sig); // Sygnaturka wtyczki (kr�tka, kilkuliterowa nazwa)
    IM_PLUG_NAME: ret := Integer(name); // Pe�na nazwa wtyczki (ale najlepiej nie za d�uga!)
    IM_PLUG_NETNAME: ret := 0; // Nazwa obs�ugiwanej sieci (o ile jak�� sie� obs�uguje)
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

  { Tutaj obs�ugujemy wszystkie pozosta�e komunikaty }
  { Z ka�dego komunikatu trzeba zwraca� warto�� wi�ksz� od 0. W przeciwnym razie,
    zostanie ustawiony b��d i komunikat zostanie uznany za nie obs�u�ony }


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
