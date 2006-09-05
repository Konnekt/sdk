library Simple;
{  SIMPLE.DPR
   Przyk�adowa wtyczka dla programu Konnekt...

    -> Wykorzystanie kilku prostych komunikat�w

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
  { Tutaj wtyczk� uruchamiamy }
  {�eby odebra� ten komunikat (IM_START) trzeba poda� jako typ wtyczki
     IMT_UI.}
  IMLOG('HELLO!', [0]);  // Zapisujemy co� do konnekt.log
  // Logujemy warto�� zwr�con� przez IMC_PROFILEDIR
  // IMLOG przyjmuje ten sam format co funkcje z rodziny printf.
  IMLOG('IMC_PROFILE_DIR = %s' , [PChar(ICMessage(IMC_PROFILEDIR))]);
  // Logujemy warto�� zwr�con� przez IMC_PLUG_COUNT
  IMLOG('IMC_PLUG_COUNT = %d' , [ICMessage(IMC_PLUG_COUNT)]);
  // Dla przyk�adu logujemy co� z flag�. Potem b�dzie to mo�na odfiltrowa�...
  IMDEBUG(DBG_FUNC, 'IStart()', [0]);
  // Pobieramy ID wtyczki interfejsu (zawsze na pozycji 0)
  UIHandle := ICMessage(IMC_PLUG_HANDLE , 0);
  // Logujemy nazw� wtyczki UI. Pobieramy j� wysy�aj�c komunikat
  // bezpo�rednio do wtyczki.
  {
    Poni�sze nie dzia�a, pewnie zmieni�o si� cos w K od powstania tego przykladu
    Delphi natomiast nie jest tak sprytne jak c i rzuca wyj�tkiem zamiast wydrukowac
    null lub 0 ;)
  IMLOG('UI = "%s"' , [PChar(IMessageDirect(IM_PLUG_NAME , UIHandle))]);
  }
  // Wy�wietlamy komunikat w zale�no�ci od stanu po��czenia...
  if ICMessage(IMC_CONNECTED) <> 0 then
  begin
      // Wysy�amy komunikat z net i type = 0 (to samo co ICMessage)
      // Wiadomo�� dotrze do UI
      // Pojawi si� okno informuj�ce
      IMessage(IMI_INFORM , 0 , 0 , Integer(PChar('Jeste�my po��czeni z inernetem!')));
  end
  else
  begin
      // Pojawi si� okno b��du
      IMessage(IMI_ERROR , 0 , 0 , Integer(PChar('Nie wykry�em po��czenia!')));
  end;
  IMessage(IMI_INFORM , 0 , 0 , Integer(PChar('Zajrzyj do Konnekt.log - zobaczysz wygenerowane t� wtyczk� linijki!')));
  Result := 1;
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
    IM_PLUG_NET: ret := NET_EXAMPLE;  // Zwracamy warto�� NET, kt�ra MUSI by� r�na od 0!
    IM_PLUG_TYPE: ret := IMT_UI;   // Zwracamy jakiego typu jest nasza wtyczka (kt�re wiadomo�ci b�dziemy obs�ugiwa�)
    IM_PLUG_VERSION: ret := Integer(version); // Wersja wtyczki tekstowo major.minor.release.build ..., lub 0 je�eli wersja zapisana jest w zasobach DLLa
    IM_PLUG_SDKVERSION: ret := KONNEKT_SDK_V; // Ta linijka jest wymagana!
    IM_PLUG_SIG: ret :=  Integer(sig); // Sygnaturka wtyczki (kr�tka, kilkuliterowa nazwa)
    IM_PLUG_NAME: ret := Integer(name); // Pe�na nazwa wtyczki (ale najlepiej nie za d�uga!)
    IM_PLUG_NETNAME: ret := 0; // Nazwa obs�ugiwanej sieci (o ile jak�� sie� obs�uguje)
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
 