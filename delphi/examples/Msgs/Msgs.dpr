library Msgs;

{  MSGS.CPP
   Przyk³adowa wtyczka dla programu Konnekt...
   Idealny sposób ¿eby zacz¹æ pisaæ coœ swojego ...

   Przyk³ady:
    -> wprowadzanie wiadomoœci do kolejki
    -> obs³uga wiadomoœci
    -> sprawdzanie kolejki wiadomoœci

   Jest to bardzo prosty przyk³ad wykorzystania kolejki wiadomoœci...
   Byæ mo¿e w nastêpnych edycjach SDK zostanie on rozszerzony...

   Powinna zostaæ skompilowana jako Win32DLL z wykorzystaniem
   wielow¹tkowej wersji biblioteki CRT!

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
  IM_EX_TEST = 5000; // Identyfikator wiadomoœci który wyœlemy do actcfg.cpp
  MT_EXAMPLE = 500;
  NET_EXAMPLE = 5; // Wartosc net tej wtyczki

const
  version: PChar = '';
  name: PChar = 'Msgs.dpr';
  sig: PChar = 'EX3';


function IPrepare(): Integer;
begin
  { Tutaj rejestrujemy sie w interfejsie }
  { Mowa by³a ju¿ o tym w actcfg.cpp wiêc nie bêdê siê powtarza³... Tym razem stworzymy sobie osobny toolbar!}
  UIGroupAdd(IMIG_BAR , IMIG_EXAMPLE, 0, 'msgs.dpr');
  UIActionAdd(IMIG_EXAMPLE , IMIA_EXAMPLE_MSG , 0 , 'MSG', UIIcon(IT_MESSAGE,0,MT_SERVEREVENT,0),40,40); // Ta akcja wstawi do kolejki "nasz¹" wiadomoœæ...
  UIActionAdd(IMIG_EXAMPLE , IMIA_EXAMPLE_MGG , 0 , 'GG', UIIcon(IT_MESSAGE,0,MT_MESSAGE,0),40,40); // a ta wrzuci wiadomoœæ od kontaktu z UID 1 na GG
  // pamiêtaj ¿eby w³¹czyæ przyjmowanie wiadomoœci od osób spoza listy!
  Result := 1;
end;

function ActionProc(const anBase: sUIActionNotify_basePtr): Integer;
{ Tutaj obs³ugujemy akcje }
  {  Poni¿sza linijka s³u¿y TYLKO waszej wygodzie!
     Wiêkszoœæ (o ile nie wszystkie) powiadomieñ przesy³ana jest jako sUIActionNotify_2params,
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
          m.flag := MF_HANDLEDBYUI; // Wiadomoœæ zostanie obs³u¿ona w ca³oœci przez UI
          m.fromUid := '1';
          m.toUid := ''; // Wiadomoœæ ma przyjœæ, czyli jest do nas, czyli nie wpisujemy nic...
          m.net := NET_GG;
          m.time := 0; // Czas podajemy w formacie cTime64 - jest to mój w³asny format  i udostêpnie
              // obs³uguj¹c¹ go bibliotekê razem z nastêpnym SDK...
              // Format jest podobny jak tm co do iloœci pól, tyle ¿e upycha je wszystkie w 64 bitach...
              // Nie zastosowa³em zwyk³ego time_t bo jest dosyæ "krótki" , a time64_t obs³uguje tylko MSVC ...
          m.type_ := MT_MESSAGE;
          m.body := 'HELLO WORLD!'; // Treœæ
          m.ext := ''; // Dodatkowe info... na razie pusto
          ms := sMESSAGESELECTB();
          ms.id := ICMessage(IMC_NEWMESSAGE , Integer(@m));
          // w ms.id dostaliœmy ID dodanej wiadomoœci...
          // po dodaniu wiadomoœci ZAWSZE trzeba przejrzeæ kolejkê...
          // w sMESSAGESELECT podajemy jakie wiadomoœci dosz³y...
          // ustawiaj¹c tylko ms.id MessageQueue zostanie sprawdzone pod k¹tem tylko tej jednej
          // wiadomoœci... Trzeba jednak sprawdziæ czy wiadomoœæ zosta³a w ogóle dodana do
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
          m.flag := 0; // Wiadomoœæ zostanie obs³u¿ona w ca³oœci przez UI
          m.fromUid := 'msgs.cpp';
          m.toUid := ''; // Wiadomoœæ ma przyjœæ, czyli jest do nas, czyli nie wpisujemy nic...
          m.net := NET_EXAMPLE;
          m.time := 0;
          m.type_ := MT_EXAMPLE or MT_MASK_NOTONLIST; // Nasz typ wiadomoœci... MT_MASK_NOTONLIST oznacza, ¿e rdzeñ nie sprawdzi od kogo przysz³a wiadomoœæ...
          m.body := 'HELLO WORLD!'; // Treœæ
          m.ext := ''; // Dodatkowe info... na razie pusto
          ICMessage(IMC_NEWMESSAGE, Integer(@m));
          {   Teraz zostanie wywo³ane IM_MSG_RCV na który zwrócimy IM_MSG_delete...
              Wywo³ywanie IMC_MESSAGEQUEUE nie ma wiêc sensu...

              Pe³na obs³uga wiadomoœci, ³¹cznie z oczekiwaniem na odbiór wymaga³aby
              zwrócenia IM_MSG_ok przy zapytaniu IM_MSG_RCV, co przydzieli³oby wiadomoœæ
              do naszej wtyczki, a nastêpnie obs³ugi IM_MSG_OPEN którego mechanizm
              najlepiej rozwi¹zaæ w sposób taki:
                (Dla uproszczenia za³ó¿my ¿e wiadomoœæ jest wiadomoœci¹ "od serwera", czyli
                 ¿e nie pojawi siê na liœcie kontaktów...)
                - w IM_MSG_OPEN sprawdzamy czy jest utworzone okno, w którym ma pojawiæ siê wiadomoœæ
                   tak -> wypisujemy wiadomoœæ w oknie i zwracamy IM_MSG_delete
                   nie -> zwracamy 0...
                - w odpowiedzi na nasz¹ akcjê np. "odbierz wiadomoœæ" tak na prawdê tworzymy tylko
                  okno i wywo³ujemy IMC_MESSAGEQUEUE ... Mo¿na oczywiœcie te¿ przejrzeæ listê rêcznie...
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
    { Wiadomoœci na które TRZEBA odpowiedzieæ }
    IM_PLUG_NET: ret := NET_EXAMPLE;  // Zwracamy wartoœæ NET, która MUSI byæ ró¿na od 0!
    IM_PLUG_TYPE: ret := IMT_UI or IMT_MESSAGE or IMT_MSGUI;   // Zwracamy jakiego typu jest nasza wtyczka (które wiadomoœci bêdziemy obs³ugiwaæ)
    IM_PLUG_VERSION: ret := Integer(version); // Wersja wtyczki tekstowo major.minor.release.build ..., lub 0 je¿eli wersja zapisana jest w zasobach DLLa
    IM_PLUG_SDKVERSION: ret := KONNEKT_SDK_V; // Ta linijka jest wymagana!
    IM_PLUG_SIG: ret :=  Integer(sig); // Sygnaturka wtyczki (krótka, kilkuliterowa nazwa)
    IM_PLUG_NAME: ret := Integer(name); // Pe³na nazwa wtyczki (ale najlepiej nie za d³uga!)
    IM_PLUG_NETNAME: ret := 0; // Nazwa obs³ugiwanej sieci (o ile jak¹œ sieæ obs³uguje)
    IM_PLUG_INIT: ret := Plug_Init(msg.p1, msg.p2);
    IM_PLUG_DEINIT: Plug_Deinit(msg.p1, msg.p2);

    IM_UI_PREPARE: ret := IPrepare();

    IM_UIACTION: ret := ActionProc(sUIActionNotify_basePtr(msg.p1));
    IM_MSG_RCV:
      begin
        m := cMessagePtr(msg.p1);
        { Bierzemy tylko wiadomoœæ "naszego" typu }
        if (m.type_ = (MT_EXAMPLE or MT_MASK_NOTONLIST)) then
        begin
          FmtStr(buff, 'Dosta³em wiadomoœæ od %s:'#10#10'%s', [m.fromUid, m.body]);
          ICMessage(IMI_INFORM , Integer(PChar(buff)));
          ret := IM_MSG_delete;
        end
        else
          ret := 0;
        end;
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
