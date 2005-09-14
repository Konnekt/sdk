library ActCfg;
{  ActCfg.DPR
   Przyk³adowa wtyczka dla programu Konnekt...
   Idealny sposób ¿eby zacz¹æ pisaæ coœ swojego ...

   Przyk³ady:
    -> Wykorzystania tablic ustawieñ
    -> Wykorzystania okien dialogowych
    -> Obs³ugi akcji
    -> Obs³ugi konfiguracji
    -> Obs³ugi akcji kontaktów
    -> Prostego ³adowania ikonek

   Aby zobaczyæ ikonkê, trzeba do skompilowanego projektu dodaæ Resources i do nich
   ikonkê (16px x 16px) o identyfikatorze równym 100.

   (c)2002 hao | Stamina
   (c)2005 Winthux
   http://www.konnekt.info
}

uses
  Windows,
  SysUtils,
  Plug in '..\..\api\Plug.pas',
  PlugDefs in '..\..\api\PlugDefs.pas',
  ui in '..\..\api\ui.pas',
  PlugFunc in '..\..\api\PlugFunc.pas';

{$R *.res}

const
  version: PChar = '0.0.0.0';
  name: PChar = 'Template';
  sig: PChar = 'Ex2';
  core_v: PChar = 'W98';

  CFG_EXAMPLE_VALUE = 5000;  // Pozycja w tablicy konfiguracji
  CFG_EXAMPLE_DEFAULT_VALUE = 'Wartoœæ domyœlna!'; // Wartosc domyslna
  IMIG_CFG_EXAMPLE = 5000;  // Grupa w akcji w konfiguracji
  IMIA_CFG_EXAMPLE_BUTTON = 5001;  // Akcja w konfiguracji
  IMIG_EXAMPLE = 5010;  // Grupa na g³ównym toolbarze
  IMIA_EXAMPLE_BUTTON = 5011;  // Akcja w menu na g³ównym toolbarze
  IMIA_CNT_EXAMPLE = 5020;  // Akcja dla kontaktów
  IM_EX_TEST = 5000; // Identyfikator wiadomoœci do wykorzystania przez inne wtyczki...
  IDI_EXAMPLE = 5000;            // Identyfikator ikonki
  IDI_POINT = 3; // Ta ikonka jest ju¿ zarejestrowana przez UI. Uwierzcie na s³owo :)

  NET_EXAMPLE = 5; // Wartosc net tej wtyczki


//---------------------------------------------------------------------------
{ Wszystkie poni¿sze funkcje nie s¹ wymagane (z wyj¹tekim IMEssageProc)...
   ale z nimi wszystko wygl¹da czytelniej :)
}
function Init(): Integer;
begin
    {  Do inicjalizowania nie mamy nic...  }
  Result := 1;
end;

function DeInit(): Integer;
begin
  {  Do usuwania równie¿...
  }
  Result := 1;
end;

function ISetCols(): Integer;
begin
   { Rejestrujemy kolumnê w konfiguracji (DTCFG).
     Niech bêdzie to wartoœæ tekstowa - czyli DT_CT_STR
         Dla porz¹dku nadamy jej te¿ nazwê...
     }
  SetColumn(DTCFG, CFG_EXAMPLE_VALUE, DT_CT_STR, CFG_EXAMPLE_DEFAULT_VALUE , 'Example/actcfg/exampleValue');
  Result := 1;
end;

function IPrepare(): Integer;
begin
  {  Tutaj rejestrujemy sie w interfejsie.
     Do zarejestrowania mamy 5 akcji i jedn¹ ikonkê.
     Bêdziemy korzystaæ z gotowych funkcji z plug_func.h}
  {  W tej chwili SDK dysponuje tylko jedn¹ wiadomoœci¹ do rejestrowania ikonek.
     W nastêpnej edycji SDK powinny pojawiæ siê wiêksze mo¿liwoœci... }
        IconRegister(IML_16, IDI_EXAMPLE, Ctrl.hDll(), 100, 1);

  { Rejestrujemy akcje które bêd¹ widoczne na toolbarze w oknie g³ównym.

     Najpierw rejestrujemy grupê, któr¹ dodajemy do grupy IMIG_MAINTB.
     W ten sposób tworzymy now¹ ikonkê na toolbarze.
     Wstawiamy j¹ na drug¹ pozycjê od lewej.
  }
   UIGroupInsert(IMIG_MAINTB  // Grupa - matka
       , IMIG_EXAMPLE        // ID nowej grupy
       , 1                   // Pozycja do wstawienia. 0 - pocz¹tek -1 - koniec
       , 0                   // Status akcji. Powinniœmy podaæ ACTS_GROUP, ale UIGroupInsert robi to ju¿ za nas...
       , 'Przyk³ad'          // Treœæ akcji. W tym wypadku zawartoœæ tooltipa
       , IDI_POINT         // jako P1 w menusach podajemy ID ikonki
       ); // Resztê parametrów mo¿emy sobie darowaæ. Wszystkie i tak s¹ równe 0!
      { Dodajemy akcjê }
  UIActionAdd(IMIG_EXAMPLE // Wstawiamy do utworzonej ju¿ grupy
      , IMIA_EXAMPLE_BUTTON
      , 0
      , 'Wciœnij mnie!'
      , IDI_EXAMPLE // Identyfikator naszej ikonki z zasobów wtyczki
      );
  { Dodajemy akcjê do menu kontaktów. Dodatkowo zrobimy tak, aby pojawia³a sie tylko przy
     kontaktach bez sieci!}
  UIActionAdd(IMIG_CNT // Menu kontaktów
      , IMIA_CNT_EXAMPLE // ID akcji
      , 0 //ACTR_INIT nie dzia³a-uleg³o cos zmianie  // Rz¹damy powiadomienia o utworzeniu pozycji w menu
      , 'Jestem spoza sieci!'
      , IDI_EXAMPLE
      );
  { Œwietnie, dodajmy teraz akcje do konfiguracji }
  { Najpierw tworzymy grupê }
  UIGroupAdd(IMIG_CFG  // Grupa - matka
       , IMIG_CFG_EXAMPLE        // ID nowej grupy
       , 0                   // Status akcji. Powinniœmy podaæ ACTS_GROUP, ale UIGroupInsert robi to ju¿ za nas...
       , 'Przyk³ad!'          // Treœæ akcji. W tym wypadku zawartoœæ tooltipa
       , IDI_POINT         // jako P1 w grupach konfiguracji podajemy ID ikonki
       ); // Resztê parametrów mo¿emy sobie darowaæ. Wszystkie i tak s¹ równe 0!
  {  Teraz robi siê ciut ciekawiej. Najpierw dodajmy krótki opis. Nie potrzebujemy do tego
     identyfikatora bo i tak nic z nim nie bêdziemy robiæ.
     Funkcja UIActionCfgAdd przydaje siê TYLKO gdy chcemy przesun¹æ kontrolkê wzglêdem osi x lub y.
     Spokojnie mo¿na u¿yc UIActionAdd ...
     }
  {  Dobr¹ 'manier¹' w konfiguracji jest grupowanie kontrolek... a wiêc }
  UIActionAdd(IMIG_CFG_EXAMPLE , 0 , ACTT_GROUP , 'Przyk³ad z actcfg.cpp');
    UIActionCfgAdd(IMIG_CFG_EXAMPLE  // Grupa - matka
        , 0
        , ACTT_INFO           // Status akcji. Podajemy ACTT_INFO jako typ wstawianej kontrolki...
        , 'Wpisz poni¿ej dowolny tekst.'#13#13'Je¿eli wpiszesz "aa" stanie siê coœ dziwnego!'          // Treœæ informacji.
        , IDI_POINT         // jako P1 w menusach podajemy ID ikonki
        ,0,0  // Przesuniêcie wzglêdem x i y zostawiamy w spokoju...
        ,100  // Szerokoœæ. ACTT_INFO jest rozci¹gany na ca³¹ szerokoœæ. Nie ma znaczenia co tutaj wpiszemy
        ,40   // Wysokoœæ. Niech nasze info ma 40 pixeli wysokoœci...
        ); // Resztê parametrów mo¿emy sobie darowaæ. Wszystkie i tak s¹ równe 0!
   { Teraz dodamy kontrolkê przy pomocy której mo¿emy edytowaæ nasz¹ kolumnê CFG_EXAMPLE_VALUE.
       UI automatycznie zajmuje siê konwersj¹ typów i ³adowaniem/zapisywaniem. My za to
       bêdziemy sprawdzaæ, czy to co jest wpisywane, wpisywane jest poprawnie... }
    UIActionCfgAdd(IMIG_CFG_EXAMPLE  // Grupa - matka
        , IMIB_CFG   { Ustawiaj¹c identyfikator w ten sposób mamy pewnoœæ, ¿e faktycznym identyfikatorem akcji
                        bêdzie IMIB_CFG or P1, gdzie P1 zaraz stanie siê identyfikatorem kolumny.
                     }
        , ACTT_EDIT or ACTSC_INLINE or ACTR_CHECK  { ACTT_EDIT to kontrolka do edycji. Dziêki ACTSC_INLINE nastêpna
                                               kontrolka pojawi siê w tej samej linijce...
                                               Dziêki ACTR_CHECK zostaniemy powiadomieni o zmianach
                                               w tej kontrolce!
                                               }
        , '' + CFGTIP + 'Spróbuj wpisaæ "aa"!'  // Wszystko co jest po CFGTIP pójdzie do ToolTip'a!
        , CFG_EXAMPLE_VALUE // jako P1 w konfiguracji podajemy kolumnê w tablicy CFG przypisan¹ do
                          // do danej kontrolki. Podczas zapisywania, wartoœæ kontrolki zostanie
                          // zapisana w odpowiedniej kolumnie...  
        ,10,0  // Zróbmy ma³e wciêcie...
        ,50  // Szerokoœæ.
        ,0   // Wysokoœci¹ zajmie siê automat...
        ); // Resztê parametrów mo¿emy sobie darowaæ. Wszystkie i tak s¹ równe 0!
  { Mo¿e s³ówko komentarza? }
  UIActionAdd(IMIG_CFG_EXAMPLE , 0 , ACTT_COMMENT , '<- tutaj wpisuj!');
  { Zosta³ nam jeszcze button }
  UIActionAdd(IMIG_CFG_EXAMPLE , IMIA_CFG_EXAMPLE_BUTTON , ACTT_BUTTON , 'Kliknij mnie!',0,120,40);
  { Otwart¹ grupê koniecznie trzeba zamkn¹æ! }
  UIActionAdd(IMIG_CFG_EXAMPLE , 0 , ACTT_GROUPEND);


  Result := 1;
end;

function IStart():Integer;
begin
  { Tutaj wtyczkê uruchamiamy. W tym wypadku Konnekt robi wszystko za nas :) }
  Result := 1;
end;

function IEnd(): Integer;
begin
  { Tutaj wtyczkê wy³¹czamy }
  Result := 1;
end;

const
  value: PChar = 'bb';

function ActionCfgProc(const anBase: sUIActionNotify_basePtr): Integer;
{  Tutaj obs³ugujemy akcje dla okna konfiguracji
   Sytuacja taka sama jak przy ActionProc  }
var
  an: sUIActionNotify_2paramsPtr;
begin
  an := sUIActionNotify_2paramsPtr(anBase);

  case (anBase.act.id and not IMIB_CFG) of
    CFG_EXAMPLE_VALUE:
    begin
       if (anBase.code = ACTN_CHECK) then
       begin
          { Sprawdzamy zawartoœæ kontrolki. Jej aktualna wartoœæ znajduje siê notify1 }
           if (StrComp(PChar(an.notify1), 'aa') = 0) then // sprawdzamy czy wpisaliœmy 'aa'
              an.notify1 := Integer(value); // jak tak - zmieniamy na bb
                   { Ze wzglêdu na pewn¹ "niedoskona³oœæ" któr¹ odkry³em pisz¹c ten
                      kod TRZEBA zmieniæ an->notify1 na inny bufor (który musi byæ
                      wa¿ny równie¿ po opuszczeniu tej funkcji) ¿eby zmieniæ wartoœæ kontrolki.
                      W nastêpnej wersji programu b³¹d bêdzie poprawiony...
                      
                      ACTN_CHECK przysy³any jest w tej chwili TYLKO do kontrolek z polem edycji...*/
               }

        end;
    end;
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
  sde: sDIALOG_enter;
  sdc: sDIALOG_choose;
  buff: array[0..200] of Char;
  t: array[0..4] of PChar;
  ok, desc: Boolean;
  ai: sUIActionInfo;
  sdl: sDIALOG_long;
  i,j: Integer;
  ret: PChar;
begin
  an := sUIActionNotify_2paramsPtr(anBase);

  if ((anBase.act.id and IMIB_) = IMIB_CFG) then
    Result := ActionCfgProc(anBase)
  else
    begin
      case (anBase.act.id) of
        IMIA_CFG_EXAMPLE_BUTTON:
          begin
            if ACTIONONLY(anBase) then   // Dziêki temu obs³u¿ymy tu tylko ACTN_ACTION, czyli naciœniêcie buttona
            begin
              { Wyœwietlimy sobie okno dialogowe do wprowadzania tekstu }
              sde := sDialog_enterB();
              sde.info := 'Wpisz co chcia³byœ ujrzeæ w kontrolce edycji?';
              sde.title := 'actcfg.cpp';
              { jako wartoœæ pocz¹tkow¹ weŸmiemy to, co jest wpisane w pole edycji
                ¯eby tego dokonaæ musimy wywo³aæ odpowiedni¹ f-cjê...
                Jak widaæ jej parametrem jest deskryptor akcji.
                Trzeba w nim podaæ identyfikator grupy i akcji o któr¹ nam chodzi...
              }
              UIActionCfgGetValue(sUIActionB(IMIG_CFG_EXAMPLE, IMIB_CFG or CFG_EXAMPLE_VALUE), buff,200);
              sde.value := buff;
              ICMessage(IMI_DLGENTER , Integer(@sde));
              { Wpisan¹ wartoœæ wrzucamy do kontrolki }
              { Uwaga! Naciœniêcie w okienku na Cancel ustawia value na 0!!! }
              if sde.value <> nil then
                UIActionCfgSetValue(sUIActionB(IMIG_CFG_EXAMPLE, IMIB_CFG or CFG_EXAMPLE_VALUE), sde.value);
            end;
          end;
        IMIA_EXAMPLE_BUTTON:
          begin
            if ACTIONONLY(anBase) then
            begin
              { Pobierzemy sobie wartoœæ naszej kontrolki i j¹ wyœwietlimy
                Najpierw jednak zapytamy u¿ytkownika w jakim oknie chce zobaczyæ wynik... }
              sdc := sDIALOG_chooseB();
              sdc.def := 1;
              sdc.info := 'Wybierz jak przedstawiæ wartoœæ?';
              sdc.title := 'actcfg.cpp';
              sdc.items := 'IMI_INFORM'#10'IMI_ERROR'; { Ka¿da linijka to nowy button }
              StrLCopy(buff, GETSTR(CFG_EXAMPLE_VALUE), 200); // Pobieramy wartoœæ
              case ICMessage(IMI_DLGBUTTONS , Integer(@sdc)) of
                1: Result := ICMessage(IMI_INFORM, Integer(@buff)); // Wybraliœmy opcjê pierwsz¹
                2: Result := ICMessage(IMI_ERROR, Integer(@buff));
              else
               begin
                ret:= 'Nie to nie..';
                Result := ICMessage(IMI_INFORM, Integer(ret)); // Cancel
                end;
              end;
            end;
          end;
        IMIA_CNT_EXAMPLE:  // Akcja w menu kontaktów
          begin
            if anBase.code = ACTN_CREATE then
            begin
              {  Reagujemy na otworzenie menu. Mo¿emy sprawdziæ czy kontakt jest z jakiejœ sieci.
                  an to sUIActionNotify, czyli powiadomienie o zdarzeniu w akcji.
                  ¯eby sprawdziæ z jakim kontaktem powi¹zana jest teraz akcja, trzeba sprawdziæ
                  jej deskryptor, który znajduje siê w an->act...
               }
              ok := GETCNTI(an.act.cnt, CNT_NET) = NET_NONE;
              ai := sUIActionInfoB(); // Zmienimy status kontrolki
              ai.act := an.act;  // Chodzi nam o t¹ sam¹ dla której wywo³ane jest powiadomienie prawda?
              ai.mask := UIAIM_STATUS;  // Zmianiamy status
              if ok then
                ai.status := 0
              else
                ai.status := ACTS_HIDDEN;
              ai.statusMask := ACTS_HIDDEN; // Zmieniamy tylko ten jeden bit statusu
              if (ok) then  // ¯eby by³o œmieszniej bêdziemy zmieniaæ jeszcze opis tekstowy...
              begin
                desc := False;
                ai.mask := ai.mask or UIAIM_TXT; // Zmieniamy jeszcze text
                if desc then
                  ai.txt := 'Ja chcê nale¿eæ do sieeeeciiiii!'
                else
                  ai.txt := 'Jestem bez sieci i jestem z tego dumny!';    // wybieramy tekst...
                desc := not desc;
               end;
               ICMessage(IMI_ACTION_SET , Integer(@ai)); // Gotowe!
            end
            else
              begin
                sdl:= sDIALOG_longB();
                sdl.title := 'actcfg.cpp';
                sdl.info := 'Przy³¹czanie do sieci...';
                t[0] := '£¹czê';
                t[1] := 'Przy³¹czam';
                t[2] := 'za³¹czam';
                t[3] := 'roz³¹czam';
                sdl.flag := DLONG_BLOCKING ;
                { UWAGA! Okaza³o siê ¿e w API jest b³¹d, który przy Blokuj¹cych d³ugich operacjach
                  objawia siê tym, ¿e w oknie z progresem bêdzie nieodœwie¿ony prostok¹t...
                  Postaram siê usun¹æ problem w nowszej wersji... :) }
                ICMessage(IMI_LONGSTART , Integer(@sdl)); // zaczynamy
                for i:=0 to 3 do
                begin
                  for j:=0 to 99 do
                    Sleep(10);
                         // Powtarzam operacjê, poniewa¿ proces odœwie¿ania okienka bêdzie zrywa³ Sleep
                  sdl.progress := sdl.progress + 25;
                  sdl.info := t[i];
                  ICMessage(IMI_LONGSET , Integer(@sdl), DSET_PROGRESS or DSET_INFO);   // koñczymy
                   
                end;
                for j:=0 to 49 do
                  Sleep(10);
                ICMessage(IMI_LONGEND , Integer(@sdl));   // koñczymy
              end;
          end;
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
  m: PChar;

begin
  msg := sIMessage_2paramsPtr(msgBase);
  ret := -1;

  case msgBase.id of
    { Wiadomoœci na które TRZEBA odpowiedzieæ }
    IM_PLUG_NET: ret := NET_EXAMPLE;  // Zwracamy wartoœæ NET, która MUSI byæ ró¿na od 0!
    IM_PLUG_TYPE: ret := IMT_UI or IMT_CONTACT or IMT_CONFIG;   // Zwracamy jakiego typu jest nasza wtyczka (które wiadomoœci bêdziemy obs³ugiwaæ)
    IM_PLUG_VERSION: ret := Integer(version); // Wersja wtyczki tekstowo major.minor.release.build ..., lub 0 je¿eli wersja zapisana jest w zasobach DLLa
    IM_PLUG_SDKVERSION: ret := KONNEKT_SDK_V; // Ta linijka jest wymagana!
    IM_PLUG_SIG: ret :=  Integer(sig); // Sygnaturka wtyczki (krótka, kilkuliterowa nazwa)
    IM_PLUG_CORE_V: ret := Integer(core_v); // Wymagana wersja rdzenia
    IM_PLUG_UI_V: ret :=  0; // Wymagana wersja UI
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

    IM_EX_TEST:
      begin
        m := 'ACTCFG @ IM_EX_TEST';
        ICMessage(IMI_NOTIFY , Integer(m));
        ret := 1;
      end;
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
