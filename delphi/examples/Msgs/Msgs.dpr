library Msgs;

{  MSGS.CPP
   Przyk�adowa wtyczka dla programu Konnekt...
   Idealny spos�b �eby zacz�� pisa� co� swojego ...

   Przyk�ady:
    -> wprowadzanie wiadomo�ci do kolejki
    -> obs�uga wiadomo�ci
    -> sprawdzanie kolejki wiadomo�ci

   Jest to bardzo prosty przyk�ad wykorzystania kolejki wiadomo�ci...
   By� mo�e w nast�pnych edycjach SDK zostanie on rozszerzony...

   Powinna zosta� skompilowana jako Win32DLL z wykorzystaniem
   wielow�tkowej wersji biblioteki CRT!

   (c)2002 hao | Stamina
   (c)2005 Winthux
   http://www.konnekt.info
}



uses
  Plug in '..\..\api\plug.pas',
  PlugDefs in '..\..\api\plugdefs.pas',
  ui in '..\..\api\ui.pas',
  PlugFunc in '..\..\api\plugfunc.pas',
  SysUtils;

{$R *.res}

const
  IMIG_EXAMPLE = 5100;
  IMIA_EXAMPLE_MGG = 5101;
  IMIA_EXAMPLE_MSG = 5102;
  IM_EX_TEST = 5000; // Identyfikator wiadomo�ci kt�ry wy�lemy do actcfg.cpp
  MT_EXAMPLE = 500;
  NET_EXAMPLE = 5; // Wartosc net tej wtyczki

const
  version: PChar = '';
  name: PChar = 'Msgs.dpr';
  sig: PChar = 'EX3';


function IPrepare(): Integer;
begin
  { Tutaj rejestrujemy sie w interfejsie }
  { Mowa by�a ju� o tym w actcfg.cpp wi�c nie b�d� si� powtarza�... Tym razem stworzymy sobie osobny toolbar!}
  UIGroupAdd(IMIG_BAR , IMIG_EXAMPLE, 0, 'msgs.dpr');
  UIActionAdd(IMIG_EXAMPLE , IMIA_EXAMPLE_MSG , 0 , 'MSG', UIIcon(IT_MESSAGE,0,MT_SERVEREVENT,0),40,40); // Ta akcja wstawi do kolejki "nasz�" wiadomo��...
  UIActionAdd(IMIG_EXAMPLE , IMIA_EXAMPLE_MGG , 0 , 'GG', UIIcon(IT_MESSAGE,0,MT_MESSAGE,0),40,40); // a ta wrzuci wiadomo�� od kontaktu z UID 1 na GG
  // pami�taj �eby w��czy� przyjmowanie wiadomo�ci od os�b spoza listy!
  Result := 1;
end;

function ActionProc(const anBase: sUIActionNotify_basePtr): Integer;
{ Tutaj obs�ugujemy akcje }
  {  Poni�sza linijka s�u�y TYLKO waszej wygodzie!
     Wi�kszo�� (o ile nie wszystkie) powiadomie� przesy�ana jest jako sUIActionNotify_2params,
     korzystamy wtedy z obiektu an, w przeciwnym razie z anBase, lub castujemy do spodziewanego typu.
  }
var
  an: sUIActionNotify_2paramsPtr;
  m: cMessage;
  ms: sMESSAGESELECT;
begin
  an := sUIActionNotify_2paramsPtr(anBase);

  case (anBase.act.id) of
    IMIA_EXAMPLE_MGG:
      begin
        if ACTIONONLY(anBase) then
        begin
          m := cMessageB();
          m.flag := MF_HANDLEDBYUI; // Wiadomo�� zostanie obs�u�ona w ca�o�ci przez UI
          m.fromUid := '1';
          m.toUid := ''; // Wiadomo�� ma przyj��, czyli jest do nas, czyli nie wpisujemy nic...
          m.net := NET_GG;
          m.time := 0; // Czas podajemy w formacie cTime64 - jest to m�j w�asny format  i udost�pnie
              // obs�uguj�c� go bibliotek� razem z nast�pnym SDK...
              // Format jest podobny jak tm co do ilo�ci p�l, tyle �e upycha je wszystkie w 64 bitach...
              // Nie zastosowa�em zwyk�ego time_t bo jest dosy� "kr�tki" , a time64_t obs�uguje tylko MSVC ...
          m.type_ := MT_MESSAGE;
          m.body := 'HELLO WORLD!'; // Tre��
          m.ext := ''; // Dodatkowe info... na razie pusto
          ms := sMESSAGESELECTB();
          ms.id := ICMessage(IMC_NEWMESSAGE , Integer(@m));
          // w ms.id dostali�my ID dodanej wiadomo�ci...
          // po dodaniu wiadomo�ci ZAWSZE trzeba przejrze� kolejk�...
          // w sMESSAGESELECT podajemy jakie wiadomo�ci dosz�y...
          // ustawiaj�c tylko ms.id MessageQueue zostanie sprawdzone pod k�tem tylko tej jednej
          // wiadomo�ci... Trzeba jednak sprawdzi� czy wiadomo�� zosta�a w og�le dodana do
          // kolejki...
          if (ms.id <> 0) then
            ICMessage(IMC_MESSAGEQUEUE, Integer(@ms));
        end;
      end;
    IMIA_EXAMPLE_MSG:
      begin
        if ACTIONONLY(anBase) then
        begin
          m := cMessageB();
          m.flag := 0; // Wiadomo�� zostanie obs�u�ona w ca�o�ci przez UI
          m.fromUid := 'msgs.cpp';
          m.toUid := ''; // Wiadomo�� ma przyj��, czyli jest do nas, czyli nie wpisujemy nic...
          m.net := NET_EXAMPLE;
          m.time := 0;
          m.type_ := MT_EXAMPLE or MT_MASK_NOTONLIST; // Nasz typ wiadomo�ci... MT_MASK_NOTONLIST oznacza, �e rdze� nie sprawdzi od kogo przysz�a wiadomo��...
          m.body := 'HELLO WORLD!'; // Tre��
          m.ext := ''; // Dodatkowe info... na razie pusto
          ICMessage(IMC_NEWMESSAGE, Integer(@m));
          {   Teraz zostanie wywo�ane IM_MSG_RCV na kt�ry zwr�cimy IM_MSG_delete...
              Wywo�ywanie IMC_MESSAGEQUEUE nie ma wi�c sensu...

              Pe�na obs�uga wiadomo�ci, ��cznie z oczekiwaniem na odbi�r wymaga�aby
              zwr�cenia IM_MSG_ok przy zapytaniu IM_MSG_RCV, co przydzieli�oby wiadomo��
              do naszej wtyczki, a nast�pnie obs�ugi IM_MSG_OPEN kt�rego mechanizm
              najlepiej rozwi�za� w spos�b taki:
                (Dla uproszczenia za��my �e wiadomo�� jest wiadomo�ci� "od serwera", czyli
                 �e nie pojawi si� na li�cie kontakt�w...)
                - w IM_MSG_OPEN sprawdzamy czy jest utworzone okno, w kt�rym ma pojawi� si� wiadomo��
                   tak -> wypisujemy wiadomo�� w oknie i zwracamy IM_MSG_delete
                   nie -> zwracamy 0...
                - w odpowiedzi na nasz� akcj� np. "odbierz wiadomo��" tak na prawd� tworzymy tylko
                  okno i wywo�ujemy IMC_MESSAGEQUEUE ... Mo�na oczywi�cie te� przejrze� list� r�cznie...
                  jak kto woli...
              }
        end;
      end;
  end;
  Result := 0;
end;

function IMessageProc(const msgBase: sIMessage_basePtr): Integer; stdcall;
var
  msg: sIMessage_2paramsPtr;
  ret: Integer;
  m: cMessagePtr;
  buff: string;

begin
  msg := sIMessage_2paramsPtr(msgBase);
  ret := -1;

  case msgBase.id of
    { Wiadomo�ci na kt�re TRZEBA odpowiedzie� }
    IM_PLUG_NET: ret := NET_EXAMPLE;  // Zwracamy warto�� NET, kt�ra MUSI by� r�na od 0!
    IM_PLUG_TYPE: ret := IMT_UI or IMT_MESSAGE or IMT_MSGUI;   // Zwracamy jakiego typu jest nasza wtyczka (kt�re wiadomo�ci b�dziemy obs�ugiwa�)
    IM_PLUG_VERSION: ret := Integer(version); // Wersja wtyczki tekstowo major.minor.release.build ..., lub 0 je�eli wersja zapisana jest w zasobach DLLa
    IM_PLUG_SDKVERSION: ret := KONNEKT_SDK_V; // Ta linijka jest wymagana!
    IM_PLUG_SIG: ret :=  Integer(sig); // Sygnaturka wtyczki (kr�tka, kilkuliterowa nazwa)
    IM_PLUG_NAME: ret := Integer(name); // Pe�na nazwa wtyczki (ale najlepiej nie za d�uga!)
    IM_PLUG_NETNAME: ret := 0; // Nazwa obs�ugiwanej sieci (o ile jak�� sie� obs�uguje)
    IM_PLUG_INIT: ret := Plug_Init(msg.p1, msg.p2);
    IM_PLUG_DEINIT: Plug_Deinit(msg.p1, msg.p2);

    IM_UI_PREPARE: ret := IPrepare();

    IM_UIACTION: ret := ActionProc(sUIActionNotify_basePtr(msg.p1));
    IM_MSG_RCV:
      begin
        m := cMessagePtr(msg.p1);
        { Bierzemy tylko wiadomo�� "naszego" typu }
        if (m.type_ = (MT_EXAMPLE or MT_MASK_NOTONLIST)) then
        begin
          FmtStr(buff, 'Dosta�em wiadomo�� od %s:'#10#10'%s', [m.fromUid, m.body]);
          ICMessage(IMI_INFORM , Integer(PChar(buff)));
          ret := IM_MSG_delete;
        end
        else
          ret := 0;
        end;
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
