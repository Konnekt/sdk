library ActCfg;
{  ActCfg.DPR
   Przyk�adowa wtyczka dla programu Konnekt...
   Idealny spos�b �eby zacz�� pisa� co� swojego ...

   Przyk�ady:
    -> Wykorzystania tablic ustawie�
    -> Wykorzystania okien dialogowych
    -> Obs�ugi akcji
    -> Obs�ugi konfiguracji
    -> Obs�ugi akcji kontakt�w
    -> Prostego �adowania ikonek

   Aby zobaczy� ikonk�, trzeba do skompilowanego projektu doda� Resources i do nich
   ikonk� (16px x 16px) o identyfikatorze r�wnym 100.

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
  CFG_EXAMPLE_DEFAULT_VALUE = 'Warto�� domy�lna!'; // Wartosc domyslna
  IMIG_CFG_EXAMPLE = 5000;  // Grupa w akcji w konfiguracji
  IMIA_CFG_EXAMPLE_BUTTON = 5001;  // Akcja w konfiguracji
  IMIG_EXAMPLE = 5010;  // Grupa na g��wnym toolbarze
  IMIA_EXAMPLE_BUTTON = 5011;  // Akcja w menu na g��wnym toolbarze
  IMIA_CNT_EXAMPLE = 5020;  // Akcja dla kontakt�w
  IM_EX_TEST = 5000; // Identyfikator wiadomo�ci do wykorzystania przez inne wtyczki...
  IDI_EXAMPLE = 5000;            // Identyfikator ikonki
  IDI_POINT = 3; // Ta ikonka jest ju� zarejestrowana przez UI. Uwierzcie na s�owo :)

  NET_EXAMPLE = 5; // Wartosc net tej wtyczki


//---------------------------------------------------------------------------
{ Wszystkie poni�sze funkcje nie s� wymagane (z wyj�tekim IMEssageProc)...
   ale z nimi wszystko wygl�da czytelniej :)
}
function Init(): Integer;
begin
    {  Do inicjalizowania nie mamy nic...  }
  Result := 1;
end;

function DeInit(): Integer;
begin
  {  Do usuwania r�wnie�...
  }
  Result := 1;
end;

function ISetCols(): Integer;
begin
   { Rejestrujemy kolumn� w konfiguracji (DTCFG).
     Niech b�dzie to warto�� tekstowa - czyli DT_CT_STR
         Dla porz�dku nadamy jej te� nazw�...
     }
  SetColumn(DTCFG, CFG_EXAMPLE_VALUE, DT_CT_STR, CFG_EXAMPLE_DEFAULT_VALUE , 'Example/actcfg/exampleValue');
  Result := 1;
end;

function IPrepare(): Integer;
begin
  {  Tutaj rejestrujemy sie w interfejsie.
     Do zarejestrowania mamy 5 akcji i jedn� ikonk�.
     B�dziemy korzysta� z gotowych funkcji z plug_func.h}
  {  W tej chwili SDK dysponuje tylko jedn� wiadomo�ci� do rejestrowania ikonek.
     W nast�pnej edycji SDK powinny pojawi� si� wi�ksze mo�liwo�ci... }
        IconRegister(IML_16, IDI_EXAMPLE, Ctrl.hDll(), 100, 1);

  { Rejestrujemy akcje kt�re b�d� widoczne na toolbarze w oknie g��wnym.

     Najpierw rejestrujemy grup�, kt�r� dodajemy do grupy IMIG_MAINTB.
     W ten spos�b tworzymy now� ikonk� na toolbarze.
     Wstawiamy j� na drug� pozycj� od lewej.
  }
   UIGroupInsert(IMIG_MAINTB  // Grupa - matka
       , IMIG_EXAMPLE        // ID nowej grupy
       , 1                   // Pozycja do wstawienia. 0 - pocz�tek -1 - koniec
       , 0                   // Status akcji. Powinni�my poda� ACTS_GROUP, ale UIGroupInsert robi to ju� za nas...
       , 'Przyk�ad'          // Tre�� akcji. W tym wypadku zawarto�� tooltipa
       , IDI_POINT         // jako P1 w menusach podajemy ID ikonki
       ); // Reszt� parametr�w mo�emy sobie darowa�. Wszystkie i tak s� r�wne 0!
      { Dodajemy akcj� }
  UIActionAdd(IMIG_EXAMPLE // Wstawiamy do utworzonej ju� grupy
      , IMIA_EXAMPLE_BUTTON
      , 0
      , 'Wci�nij mnie!'
      , IDI_EXAMPLE // Identyfikator naszej ikonki z zasob�w wtyczki
      );
  { Dodajemy akcj� do menu kontakt�w. Dodatkowo zrobimy tak, aby pojawia�a sie tylko przy
     kontaktach bez sieci!}
  UIActionAdd(IMIG_CNT // Menu kontakt�w
      , IMIA_CNT_EXAMPLE // ID akcji
      , 0 //ACTR_INIT nie dzia�a-uleg�o cos zmianie  // Rz�damy powiadomienia o utworzeniu pozycji w menu
      , 'Jestem spoza sieci!'
      , IDI_EXAMPLE
      );
  { �wietnie, dodajmy teraz akcje do konfiguracji }
  { Najpierw tworzymy grup� }
  UIGroupAdd(IMIG_CFG  // Grupa - matka
       , IMIG_CFG_EXAMPLE        // ID nowej grupy
       , 0                   // Status akcji. Powinni�my poda� ACTS_GROUP, ale UIGroupInsert robi to ju� za nas...
       , 'Przyk�ad!'          // Tre�� akcji. W tym wypadku zawarto�� tooltipa
       , IDI_POINT         // jako P1 w grupach konfiguracji podajemy ID ikonki
       ); // Reszt� parametr�w mo�emy sobie darowa�. Wszystkie i tak s� r�wne 0!
  {  Teraz robi si� ciut ciekawiej. Najpierw dodajmy kr�tki opis. Nie potrzebujemy do tego
     identyfikatora bo i tak nic z nim nie b�dziemy robi�.
     Funkcja UIActionCfgAdd przydaje si� TYLKO gdy chcemy przesun�� kontrolk� wzgl�dem osi x lub y.
     Spokojnie mo�na u�yc UIActionAdd ...
     }
  {  Dobr� 'manier�' w konfiguracji jest grupowanie kontrolek... a wi�c }
  UIActionAdd(IMIG_CFG_EXAMPLE , 0 , ACTT_GROUP , 'Przyk�ad z actcfg.cpp');
    UIActionCfgAdd(IMIG_CFG_EXAMPLE  // Grupa - matka
        , 0
        , ACTT_INFO           // Status akcji. Podajemy ACTT_INFO jako typ wstawianej kontrolki...
        , 'Wpisz poni�ej dowolny tekst.'#13#13'Je�eli wpiszesz "aa" stanie si� co� dziwnego!'          // Tre�� informacji.
        , IDI_POINT         // jako P1 w menusach podajemy ID ikonki
        ,0,0  // Przesuni�cie wzgl�dem x i y zostawiamy w spokoju...
        ,100  // Szeroko��. ACTT_INFO jest rozci�gany na ca�� szeroko��. Nie ma znaczenia co tutaj wpiszemy
        ,40   // Wysoko��. Niech nasze info ma 40 pixeli wysoko�ci...
        ); // Reszt� parametr�w mo�emy sobie darowa�. Wszystkie i tak s� r�wne 0!
   { Teraz dodamy kontrolk� przy pomocy kt�rej mo�emy edytowa� nasz� kolumn� CFG_EXAMPLE_VALUE.
       UI automatycznie zajmuje si� konwersj� typ�w i �adowaniem/zapisywaniem. My za to
       b�dziemy sprawdza�, czy to co jest wpisywane, wpisywane jest poprawnie... }
    UIActionCfgAdd(IMIG_CFG_EXAMPLE  // Grupa - matka
        , IMIB_CFG   { Ustawiaj�c identyfikator w ten spos�b mamy pewno��, �e faktycznym identyfikatorem akcji
                        b�dzie IMIB_CFG or P1, gdzie P1 zaraz stanie si� identyfikatorem kolumny.
                     }
        , ACTT_EDIT or ACTSC_INLINE or ACTR_CHECK  { ACTT_EDIT to kontrolka do edycji. Dzi�ki ACTSC_INLINE nast�pna
                                               kontrolka pojawi si� w tej samej linijce...
                                               Dzi�ki ACTR_CHECK zostaniemy powiadomieni o zmianach
                                               w tej kontrolce!
                                               }
        , '' + CFGTIP + 'Spr�buj wpisa� "aa"!'  // Wszystko co jest po CFGTIP p�jdzie do ToolTip'a!
        , CFG_EXAMPLE_VALUE // jako P1 w konfiguracji podajemy kolumn� w tablicy CFG przypisan� do
                          // do danej kontrolki. Podczas zapisywania, warto�� kontrolki zostanie
                          // zapisana w odpowiedniej kolumnie...  
        ,10,0  // Zr�bmy ma�e wci�cie...
        ,50  // Szeroko��.
        ,0   // Wysoko�ci� zajmie si� automat...
        ); // Reszt� parametr�w mo�emy sobie darowa�. Wszystkie i tak s� r�wne 0!
  { Mo�e s��wko komentarza? }
  UIActionAdd(IMIG_CFG_EXAMPLE , 0 , ACTT_COMMENT , '<- tutaj wpisuj!');
  { Zosta� nam jeszcze button }
  UIActionAdd(IMIG_CFG_EXAMPLE , IMIA_CFG_EXAMPLE_BUTTON , ACTT_BUTTON , 'Kliknij mnie!',0,120,40);
  { Otwart� grup� koniecznie trzeba zamkn��! }
  UIActionAdd(IMIG_CFG_EXAMPLE , 0 , ACTT_GROUPEND);


  Result := 1;
end;

function IStart():Integer;
begin
  { Tutaj wtyczk� uruchamiamy. W tym wypadku Konnekt robi wszystko za nas :) }
  Result := 1;
end;

function IEnd(): Integer;
begin
  { Tutaj wtyczk� wy��czamy }
  Result := 1;
end;

const
  value: PChar = 'bb';

function ActionCfgProc(const anBase: sUIActionNotify_basePtr): Integer;
{  Tutaj obs�ugujemy akcje dla okna konfiguracji
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
          { Sprawdzamy zawarto�� kontrolki. Jej aktualna warto�� znajduje si� notify1 }
           if (StrComp(PChar(an.notify1), 'aa') = 0) then // sprawdzamy czy wpisali�my 'aa'
              an.notify1 := Integer(value); // jak tak - zmieniamy na bb
                   { Ze wzgl�du na pewn� "niedoskona�o��" kt�r� odkry�em pisz�c ten
                      kod TRZEBA zmieni� an->notify1 na inny bufor (kt�ry musi by�
                      wa�ny r�wnie� po opuszczeniu tej funkcji) �eby zmieni� warto�� kontrolki.
                      W nast�pnej wersji programu b��d b�dzie poprawiony...
                      
                      ACTN_CHECK przysy�any jest w tej chwili TYLKO do kontrolek z polem edycji...*/
               }

        end;
    end;
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
            if ACTIONONLY(anBase) then   // Dzi�ki temu obs�u�ymy tu tylko ACTN_ACTION, czyli naci�ni�cie buttona
            begin
              { Wy�wietlimy sobie okno dialogowe do wprowadzania tekstu }
              sde := sDialog_enterB();
              sde.info := 'Wpisz co chcia�by� ujrze� w kontrolce edycji?';
              sde.title := 'actcfg.cpp';
              { jako warto�� pocz�tkow� we�miemy to, co jest wpisane w pole edycji
                �eby tego dokona� musimy wywo�a� odpowiedni� f-cj�...
                Jak wida� jej parametrem jest deskryptor akcji.
                Trzeba w nim poda� identyfikator grupy i akcji o kt�r� nam chodzi...
              }
              UIActionCfgGetValue(sUIActionB(IMIG_CFG_EXAMPLE, IMIB_CFG or CFG_EXAMPLE_VALUE), buff,200);
              sde.value := buff;
              ICMessage(IMI_DLGENTER , Integer(@sde));
              { Wpisan� warto�� wrzucamy do kontrolki }
              { Uwaga! Naci�ni�cie w okienku na Cancel ustawia value na 0!!! }
              if sde.value <> nil then
                UIActionCfgSetValue(sUIActionB(IMIG_CFG_EXAMPLE, IMIB_CFG or CFG_EXAMPLE_VALUE), sde.value);
            end;
          end;
        IMIA_EXAMPLE_BUTTON:
          begin
            if ACTIONONLY(anBase) then
            begin
              { Pobierzemy sobie warto�� naszej kontrolki i j� wy�wietlimy
                Najpierw jednak zapytamy u�ytkownika w jakim oknie chce zobaczy� wynik... }
              sdc := sDIALOG_chooseB();
              sdc.def := 1;
              sdc.info := 'Wybierz jak przedstawi� warto��?';
              sdc.title := 'actcfg.cpp';
              sdc.items := 'IMI_INFORM'#10'IMI_ERROR'; { Ka�da linijka to nowy button }
              StrLCopy(buff, GETSTR(CFG_EXAMPLE_VALUE), 200); // Pobieramy warto��
              case ICMessage(IMI_DLGBUTTONS , Integer(@sdc)) of
                1: Result := ICMessage(IMI_INFORM, Integer(@buff)); // Wybrali�my opcj� pierwsz�
                2: Result := ICMessage(IMI_ERROR, Integer(@buff));
              else
               begin
                ret:= 'Nie to nie..';
                Result := ICMessage(IMI_INFORM, Integer(ret)); // Cancel
                end;
              end;
            end;
          end;
        IMIA_CNT_EXAMPLE:  // Akcja w menu kontakt�w
          begin
            if anBase.code = ACTN_CREATE then
            begin
              {  Reagujemy na otworzenie menu. Mo�emy sprawdzi� czy kontakt jest z jakiej� sieci.
                  an to sUIActionNotify, czyli powiadomienie o zdarzeniu w akcji.
                  �eby sprawdzi� z jakim kontaktem powi�zana jest teraz akcja, trzeba sprawdzi�
                  jej deskryptor, kt�ry znajduje si� w an->act...
               }
              ok := GETCNTI(an.act.cnt, CNT_NET) = NET_NONE;
              ai := sUIActionInfoB(); // Zmienimy status kontrolki
              ai.act := an.act;  // Chodzi nam o t� sam� dla kt�rej wywo�ane jest powiadomienie prawda?
              ai.mask := UIAIM_STATUS;  // Zmianiamy status
              if ok then
                ai.status := 0
              else
                ai.status := ACTS_HIDDEN;
              ai.statusMask := ACTS_HIDDEN; // Zmieniamy tylko ten jeden bit statusu
              if (ok) then  // �eby by�o �mieszniej b�dziemy zmienia� jeszcze opis tekstowy...
              begin
                desc := False;
                ai.mask := ai.mask or UIAIM_TXT; // Zmieniamy jeszcze text
                if desc then
                  ai.txt := 'Ja chc� nale�e� do sieeeeciiiii!'
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
                sdl.info := 'Przy��czanie do sieci...';
                t[0] := '��cz�';
                t[1] := 'Przy��czam';
                t[2] := 'za��czam';
                t[3] := 'roz��czam';
                sdl.flag := DLONG_BLOCKING ;
                { UWAGA! Okaza�o si� �e w API jest b��d, kt�ry przy Blokuj�cych d�ugich operacjach
                  objawia si� tym, �e w oknie z progresem b�dzie nieod�wie�ony prostok�t...
                  Postaram si� usun�� problem w nowszej wersji... :) }
                ICMessage(IMI_LONGSTART , Integer(@sdl)); // zaczynamy
                for i:=0 to 3 do
                begin
                  for j:=0 to 99 do
                    Sleep(10);
                         // Powtarzam operacj�, poniewa� proces od�wie�ania okienka b�dzie zrywa� Sleep
                  sdl.progress := sdl.progress + 25;
                  sdl.info := t[i];
                  ICMessage(IMI_LONGSET , Integer(@sdl), DSET_PROGRESS or DSET_INFO);   // ko�czymy
                   
                end;
                for j:=0 to 49 do
                  Sleep(10);
                ICMessage(IMI_LONGEND , Integer(@sdl));   // ko�czymy
              end;
          end;
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
  m: PChar;

begin
  msg := sIMessage_2paramsPtr(msgBase);
  ret := -1;

  case msgBase.id of
    { Wiadomo�ci na kt�re TRZEBA odpowiedzie� }
    IM_PLUG_NET: ret := NET_EXAMPLE;  // Zwracamy warto�� NET, kt�ra MUSI by� r�na od 0!
    IM_PLUG_TYPE: ret := IMT_UI or IMT_CONTACT or IMT_CONFIG;   // Zwracamy jakiego typu jest nasza wtyczka (kt�re wiadomo�ci b�dziemy obs�ugiwa�)
    IM_PLUG_VERSION: ret := Integer(version); // Wersja wtyczki tekstowo major.minor.release.build ..., lub 0 je�eli wersja zapisana jest w zasobach DLLa
    IM_PLUG_SDKVERSION: ret := KONNEKT_SDK_V; // Ta linijka jest wymagana!
    IM_PLUG_SIG: ret :=  Integer(sig); // Sygnaturka wtyczki (kr�tka, kilkuliterowa nazwa)
    IM_PLUG_CORE_V: ret := Integer(core_v); // Wymagana wersja rdzenia
    IM_PLUG_UI_V: ret :=  0; // Wymagana wersja UI
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

    IM_EX_TEST:
      begin
        m := 'ACTCFG @ IM_EX_TEST';
        ICMessage(IMI_NOTIFY , Integer(m));
        ret := 1;
      end;
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
