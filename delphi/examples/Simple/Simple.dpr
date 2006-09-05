library Simple;
{  SIMPLE.DPR
   Przyk³adowa wtyczka dla programu Konnekt...

    -> Wykorzystanie kilku prostych komunikatów

   (c)2002 hao | Stamina
   (c)2005 Winthux
   http://www.konnekt.info
}

uses
  SysUtils,
  Plug in '..\..\api\plug.pas',
  PlugDefs in '..\..\api\plugdefs.pas',
  ui in '..\..\api\ui.pas';

{$R *.res}
const
  NET_EXAMPLE = 5;
  version: PChar = '0.0.0.1';
  name: PChar = 'Simple';
  sig: PChar = 'Ex1';

//---------------------------------------------------------------------------

function IStart(): Integer;
var
  UIHandle: Integer;
  msg: PChar;
begin
  { Tutaj wtyczkê uruchamiamy }
  {¯eby odebraæ ten komunikat (IM_START) trzeba podaæ jako typ wtyczki
     IMT_UI.}
  IMLOG('HELLO!', [0]);  // Zapisujemy coœ do konnekt.log
  // Logujemy wartoœæ zwrócon¹ przez IMC_PROFILEDIR
  // IMLOG przyjmuje ten sam format co funkcje z rodziny printf.
  IMLOG('IMC_PROFILE_DIR = %s' , [PChar(ICMessage(IMC_PROFILEDIR))]);
  // Logujemy wartoœæ zwrócon¹ przez IMC_PLUG_COUNT
  IMLOG('IMC_PLUG_COUNT = %d' , [ICMessage(IMC_PLUG_COUNT)]);
  // Dla przyk³adu logujemy coœ z flag¹. Potem bêdzie to mo¿na odfiltrowaæ...
  IMDEBUG(DBG_FUNC, 'IStart()', [0]);
  // Pobieramy ID wtyczki interfejsu (zawsze na pozycji 0)
  UIHandle := ICMessage(IMC_PLUG_HANDLE , 0);
  // Logujemy nazwê wtyczki UI. Pobieramy j¹ wysy³aj¹c komunikat
  // bezpoœrednio do wtyczki.
  {
    Poni¿sze nie dzia³a, pewnie zmieni³o siê cos w K od powstania tego przykladu
    Delphi natomiast nie jest tak sprytne jak c i rzuca wyj¹tkiem zamiast wydrukowac
    null lub 0 ;)
  IMLOG('UI = "%s"' , [PChar(IMessageDirect(IM_PLUG_NAME , UIHandle))]);
  }
  // Wyœwietlamy komunikat w zale¿noœci od stanu po³¹czenia...
  if ICMessage(IMC_CONNECTED) <> 0 then
  begin
      // Wysy³amy komunikat z net i type = 0 (to samo co ICMessage)
      // Wiadomoœæ dotrze do UI
      // Pojawi siê okno informuj¹ce
      IMessage(IMI_INFORM , 0 , 0 , Integer(PChar('Jesteœmy po³¹czeni z inernetem!')));
  end
  else
  begin
      // Pojawi siê okno b³êdu
      IMessage(IMI_ERROR , 0 , 0 , Integer(PChar('Nie wykry³em po³¹czenia!')));
  end;
  IMessage(IMI_INFORM , 0 , 0 , Integer(PChar('Zajrzyj do Konnekt.log - zobaczysz wygenerowane t¹ wtyczk¹ linijki!')));
  Result := 1;
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
    IM_PLUG_NET: ret := NET_EXAMPLE;  // Zwracamy wartoœæ NET, która MUSI byæ ró¿na od 0!
    IM_PLUG_TYPE: ret := IMT_UI;   // Zwracamy jakiego typu jest nasza wtyczka (które wiadomoœci bêdziemy obs³ugiwaæ)
    IM_PLUG_VERSION: ret := Integer(version); // Wersja wtyczki tekstowo major.minor.release.build ..., lub 0 je¿eli wersja zapisana jest w zasobach DLLa
    IM_PLUG_SDKVERSION: ret := KONNEKT_SDK_V; // Ta linijka jest wymagana!
    IM_PLUG_SIG: ret :=  Integer(sig); // Sygnaturka wtyczki (krótka, kilkuliterowa nazwa)
    IM_PLUG_NAME: ret := Integer(name); // Pe³na nazwa wtyczki (ale najlepiej nie za d³uga!)
    IM_PLUG_NETNAME: ret := 0; // Nazwa obs³ugiwanej sieci (o ile jak¹œ sieæ obs³uguje)
    IM_PLUG_INIT:
      begin
        Plug_Init(msg.p1, msg.p2);
        ret := 1;
      end;
    IM_PLUG_DEINIT:
      begin
        Plug_Deinit(msg.p1, msg.p2);
        ret := 1;
      end;

    IM_START: ret := IStart();

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
 