/* ACTCFG.CPP
   Przyk³adowa wtyczka dla programu Konnekt...
   Idealny sposób ¿eby zacz¹æ pisaæ coœ swojego ...

   Przyk³ady:
    -> Wykorzystania tablic ustawieñ
    -> Wykorzystania okien dialogowych
    -> Obs³ugi akcji
    -> Obs³ugi konfiguracji
    -> Obs³ugi akcji kontaktów
    -> Prostego ³adowania ikonek

   Powinna zostaæ skompilowana jako Win32DLL z wykorzystaniem
   wielow¹tkowej wersji biblioteki CRT!
   Aby zobaczyæ ikonkê, trzeba do skompilowanego projektu dodaæ Resources i do nich
   ikonkê (16px x 16px) o identyfikatorze równym 100.

   (c)2002 hao | Stamina
   http://www.stamina.eu.org/konnekt/sdk/
*/ 


#include <string.h>
#include <windows.h>
#include "konnekt/plug_export.h"
#include "konnekt/ui.h"
#include "konnekt/plug_func.h"

/*   Definiujemy sobie kilka identyfikatorów z których bêdziemy korzystaæ
   Jako ¿e korzystamy z wartoœci sieci równej 5, wszystkie identyfikatory
   powinny sk³adaæ siê z 5*1000+wartoœæ.
   Najlepiej wszystkie identyfikatory trzymaæ w osobnym pliku nag³ówkowym
   np. actcfg_shared.h
   Identyfikatory nie mog¹ siê powtarzaæ w swoich "grupach"
*/

#define CFG_EXAMPLE_VALUE 5000  // Pozycja w tablicy konfiguracji
#define IMIG_CFG_EXAMPLE  5000  // Grupa w akcji w konfiguracji
#define IMIA_CFG_EXAMPLE_BUTTON   5001  // Akcja w konfiguracji
#define IMIG_EXAMPLE 5010  // Grupa na g³ównym toolbarze
#define IMIA_EXAMPLE_BUTTON  5011  // Akcja w menu na g³ównym toolbarze
#define IMIA_CNT_EXAMPLE   5020  // Akcja dla kontaktów
#define IM_EX_TEST 5000 // Identyfikator wiadomoœci do wykorzystania przez inne wtyczki...
#define IDI_EXAMPLE  5000            // Identyfikator ikonki
#define IDI_POINT 3 // Ta ikonka jest ju¿ zarejestrowana przez UI. Uwierzcie na s³owo :)

#define NET_EXAMPLE 5 // Wartosc net tej wtyczki


int __stdcall DllMain(void * hinstDLL, unsigned long fdwReason, void * lpvReserved)
{
        return true;
}
//---------------------------------------------------------------------------
int Init() {
  /* Do inicjalizowania nie mamy nic... */
  return 1;
}

int DeInit() {
  /* Do usuwania równie¿...
  */
  return 1;
}

int ISetCols() {
  /* Rejestrujemy kolumnê w konfiguracji (DTCFG). 
     Niech bêdzie to wartoœæ tekstowa - czyli DT_CT_STR
	 Dla porz¹dku nadamy jej te¿ nazwê...
     */
    SetColumn(DTCFG , CFG_EXAMPLE_VALUE , DT_CT_STR , "Wartoœæ domyœlna!" , "Example/actcfg/exampleValue");

  return 1;
}

int IPrepare() {
  /* Tutaj rejestrujemy sie w interfejsie.
     Do zarejestrowania mamy 5 akcji i jedn¹ ikonkê. 
     Bêdziemy korzystaæ z gotowych funkcji z plug_func.h*/
  /* W tej chwili SDK dysponuje tylko jedn¹ wiadomoœci¹ do rejestrowania ikonek.
     W nastêpnej edycji SDK powinny pojawiæ siê wiêksze mo¿liwoœci... */
	IconRegister(IML_16 , IDI_EXAMPLE // ID rejestrowanej ikonki
		, Ctrl->hDll() // uchwyt do wtyczki
		, 100 // Identyfikator tej ikonki w zasobach wtyczki...
		);

  /* Rejestrujemy akcje które bêd¹ widoczne na toolbarze w oknie g³ównym.

     Najpierw rejestrujemy grupê, któr¹ dodajemy do grupy IMIG_MAINTB.
     W ten sposób tworzymy now¹ ikonkê na toolbarze.
     Wstawiamy j¹ na drug¹ pozycjê od lewej.
  */
  UIGroupInsert(IMIG_MAINTB  // Grupa - matka
       , IMIG_EXAMPLE        // ID nowej grupy
       , 1                   // Pozycja do wstawienia. 0 - pocz¹tek -1 - koniec
       , 0                   // Status akcji. Powinniœmy podaæ ACTS_GROUP, ale UIGroupInsert robi to ju¿ za nas...
       , "Przyk³ad"          // Treœæ akcji. W tym wypadku zawartoœæ tooltipa
       , IDI_POINT         // jako P1 w menusach podajemy ID ikonki
       ); // Resztê parametrów mo¿emy sobie darowaæ. Wszystkie i tak s¹ równe 0!
  /* Dodajemy akcjê */
  UIActionAdd(IMIG_EXAMPLE // Wstawiamy do utworzonej ju¿ grupy
      , IMIA_EXAMPLE_BUTTON
      , 0
      , "Wciœnij mnie!"
      , IDI_EXAMPLE // Identyfikator naszej ikonki z zasobów wtyczki
      );
  /* Dodajemy akcjê do menu kontaktów. Dodatkowo zrobimy tak, aby pojawia³a sie tylko przy
     kontaktach bez sieci!*/
  UIActionAdd(IMIG_CNT // Menu kontaktów
      , IMIA_CNT_EXAMPLE // ID akcji
      , ACTR_INIT              // Rz¹damy powiadomienia o utworzeniu pozycji w menu
      , "Jestem spoza sieci!"
      , IDI_EXAMPLE
      );
  /* Œwietnie, dodajmy teraz akcje do konfiguracji */
  /* Najpierw tworzymy grupê */
  UIGroupAdd(IMIG_CFG  // Grupa - matka
       , IMIG_CFG_EXAMPLE        // ID nowej grupy
       , 0                   // Status akcji. Powinniœmy podaæ ACTS_GROUP, ale UIGroupInsert robi to ju¿ za nas...
       , "Przyk³ad!"          // Treœæ akcji. W tym wypadku zawartoœæ tooltipa
       , IDI_POINT         // jako P1 w grupach konfiguracji podajemy ID ikonki
       ); // Resztê parametrów mo¿emy sobie darowaæ. Wszystkie i tak s¹ równe 0!
  /* Teraz robi siê ciut ciekawiej. Najpierw dodajmy krótki opis. Nie potrzebujemy do tego
     identyfikatora bo i tak nic z nim nie bêdziemy robiæ.
     Funkcja UIActionCfgAdd przydaje siê TYLKO gdy chcemy przesun¹æ kontrolkê wzglêdem osi x lub y.
     Spokojnie mo¿na u¿yc UIActionAdd ...
     */
  /* Dobr¹ 'manier¹' w konfiguracji jest grupowanie kontrolek... a wiêc */
  UIActionAdd(IMIG_CFG_EXAMPLE , 0 , ACTT_GROUP , "Przyk³ad z actcfg.cpp");
    UIActionCfgAdd(IMIG_CFG_EXAMPLE  // Grupa - matka
        , 0        
        , ACTT_INFO           // Status akcji. Podajemy ACTT_INFO jako typ wstawianej kontrolki...
        , "Wpisz poni¿ej dowolny tekst.\n\nJe¿eli wpiszesz \"aa\" stanie siê coœ dziwnego!"          // Treœæ informacji.
        , IDI_POINT         // jako P1 w menusach podajemy ID ikonki
        ,0,0  // Przesuniêcie wzglêdem x i y zostawiamy w spokoju...
        ,100  // Szerokoœæ. ACTT_INFO jest rozci¹gany na ca³¹ szerokoœæ. Nie ma znaczenia co tutaj wpiszemy
        ,40   // Wysokoœæ. Niech nasze info ma 40 pixeli wysokoœci... 
        ); // Resztê parametrów mo¿emy sobie darowaæ. Wszystkie i tak s¹ równe 0!
    /* Teraz dodamy kontrolkê przy pomocy której mo¿emy edytowaæ nasz¹ kolumnê CFG_EXAMPLE_VALUE.
       UI automatycznie zajmuje siê konwersj¹ typów i ³adowaniem/zapisywaniem. My za to
       bêdziemy sprawdzaæ, czy to co jest wpisywane, wpisywane jest poprawnie... */
    UIActionCfgAdd(IMIG_CFG_EXAMPLE  // Grupa - matka
        , IMIB_CFG   /* Ustawiaj¹c identyfikator w ten sposób mamy pewnoœæ, ¿e faktycznym identyfikatorem akcji 
                        bêdzie IMIB_CFG|P1, gdzie P1 zaraz stanie siê identyfikatorem kolumny.
                     */
        , ACTT_EDIT|ACTSC_INLINE|ACTR_CHECK  /* ACTT_EDIT to kontrolka do edycji. Dziêki ACTSC_INLINE nastêpna
                                               kontrolka pojawi siê w tej samej linijce...
                                               Dziêki ACTR_CHECK zostaniemy powiadomieni o zmianach
                                               w tej kontrolce!
                                               */
        , "" CFGTIP "Spróbuj wpisaæ 'aa'!"  // Wszystko co jest po CFGTIP pójdzie do ToolTip'a!
        , CFG_EXAMPLE_VALUE // jako P1 w konfiguracji podajemy kolumnê w tablicy CFG przypisan¹ do
                          // do danej kontrolki. Podczas zapisywania, wartoœæ kontrolki zostanie
                          // zapisana w odpowiedniej kolumnie...  
        ,10,0  // Zróbmy ma³e wciêcie...
        ,50  // Szerokoœæ.
        ,0   // Wysokoœci¹ zajmie siê automat...
        ); // Resztê parametrów mo¿emy sobie darowaæ. Wszystkie i tak s¹ równe 0!
  /* Mo¿e s³ówko komentarza? */
  UIActionAdd(IMIG_CFG_EXAMPLE , 0 , ACTT_COMMENT , "<- tutaj wpisuj!");
  /* Zosta³ nam jeszcze button */
  UIActionAdd(IMIG_CFG_EXAMPLE , IMIA_CFG_EXAMPLE_BUTTON , ACTT_BUTTON , "Kliknij mnie!",0,120,40);
  /* Otwart¹ grupê koniecznie trzeba zamkn¹æ! */
  UIActionAdd(IMIG_CFG_EXAMPLE , 0 , ACTT_GROUPEND);

  return 1;
}

int IStart() {
  /* Tutaj wtyczkê uruchamiamy. W tym wypadku Konnekt robi wszystko za nas :) */

  return 1;
}
int IEnd() {
  /* Tutaj wtyczkê wy³¹czamy */
  return 1;
}


int ActionCfgProc(sUIActionNotify_base * anBase) {
  sUIActionNotify_2params * an = (anBase->s_size>=sizeof(sUIActionNotify_2params))?static_cast<sUIActionNotify_2params*>(anBase):0;
  /* Tutaj obs³ugujemy akcje dla okna konfiguracji */ 
  switch (anBase->act.id & ~IMIB_CFG) {
       case CFG_EXAMPLE_VALUE:
           if (anBase->code == ACTN_CHECK) {
               /* Sprawdzamy zawartoœæ kontrolki. Jej aktualna wartoœæ znajduje siê notify1 */
               static char value [3] = "bb";
               if (!strcmp((char*)an->notify1 , "aa")) { // sprawdzamy czy wpisaliœmy 'aa'
                   an->notify1 = (int)value; // jak tak - zmieniamy na bb
                   /* Ze wzglêdu na pewn¹ "niedoskona³oœæ" któr¹ odkry³em pisz¹c ten
                      kod TRZEBA zmieniæ an->notify1 na inny bufor (który musi byæ
                      wa¿ny równie¿ po opuszczeniu tej funkcji) ¿eby zmieniæ wartoœæ kontrolki.
                      W nastêpnej wersji programu b³¹d bêdzie poprawiony...
                      
                      ACTN_CHECK przysy³any jest w tej chwili TYLKO do kontrolek z polem edycji...*/
               }

           }
           break;
  }
  return 0;
}

ActionProc(sUIActionNotify_base * anBase) {
  sUIActionNotify_2params * an = (anBase->s_size>=sizeof(sUIActionNotify_2params))?static_cast<sUIActionNotify_2params*>(anBase):0;
  /* Tutaj obs³ugujemy akcje */ 
  if ((anBase->act.id & IMIB_) == IMIB_CFG) return ActionCfgProc(anBase); 
  switch (anBase->act.id) {
       case IMIA_CFG_EXAMPLE_BUTTON: {
           ACTIONONLY(anBase); // Dziêki temu obs³u¿ymy tu tylko ACTN_ACTION, czyli naciœniêcie buttona
           /* Wyœwietlimy sobie okno dialogowe do wprowadzania tekstu */
           sDIALOG_enter sde;
           sde.info = "Wpisz co chcia³byœ ujrzeæ w kontrolce edycji?";
           sde.title = "actcfg.cpp";
           /* jako wartoœæ pocz¹tkow¹ weŸmiemy to, co jest wpisane w pole edycji
              ¯eby tego dokonaæ musimy wywo³aæ odpowiedni¹ f-cjê...
              Jak widaæ jej parametrem jest deskryptor akcji.
              Trzeba w nim podaæ identyfikator grupy i akcji o któr¹ nam chodzi...
           */
           char buff [200];
           buff[199]=0;
           UIActionCfgGetValue(sUIAction(IMIG_CFG_EXAMPLE , IMIB_CFG|CFG_EXAMPLE_VALUE),buff,200);
           sde.value = buff;
           ICMessage(IMI_DLGENTER , (int)&sde);
           /* Wpisan¹ wartoœæ wrzucamy do kontrolki */
           /* Uwaga! Naciœniêcie w okienku na Cancel ustawia value na 0!!! */
           if (sde.value) UIActionCfgSetValue(sUIAction(IMIG_CFG_EXAMPLE , IMIB_CFG|CFG_EXAMPLE_VALUE),sde.value);
           break;}
       case IMIA_EXAMPLE_BUTTON: {
           ACTIONONLY(anBase);
           /* Pobierzemy sobie wartoœæ naszej kontrolki i j¹ wyœwietlimy
              Najpierw jednak zapytamy u¿ytkownika w jakim oknie chce zobaczyæ wynik... */
           sDIALOG_choose sdc;
           sdc.def = 1;
           sdc.info = "Wybierz jak przedstawiæ wartoœæ?";
           sdc.title = "actcfg.cpp";
           sdc.items = "IMI_INFORM\nIMI_ERROR"; /* Ka¿da linijka to nowy button */
           char buff [200];
           strncpy(buff , GETSTR(CFG_EXAMPLE_VALUE) , 200); // Pobieramy wartoœæ
           switch (ICMessage(IMI_DLGBUTTONS , (int)&sdc)) {
               case 1: return ICMessage(IMI_INFORM , (int)buff); // Wybraliœmy opcjê pierwsz¹
               case 2: return ICMessage(IMI_ERROR , (int)buff);
               default: return ICMessage(IMI_INFORM , (int)"Nie to nie..."); // Cancel
           }
           break;}
       case IMIA_CNT_EXAMPLE: {  // Akcja w menu kontaktów
           if (anBase->code == ACTN_CREATE) {
               /* Reagujemy na otworzenie menu. Mo¿emy sprawdziæ czy kontakt jest z jakiejœ sieci.
                  an to sUIActionNotify, czyli powiadomienie o zdarzeniu w akcji.
                  ¯eby sprawdziæ z jakim kontaktem powi¹zana jest teraz akcja, trzeba sprawdziæ
                  jej deskryptor, który znajduje siê w an->act...
               */
               bool ok = GETCNTI(an->act.cnt , CNT_NET) == NET_NONE;
               sUIActionInfo ai;   // Zmienimy status kontrolki
               ai.act = an->act;  // Chodzi nam o t¹ sam¹ dla której wywo³ane jest powiadomienie prawda?
               ai.mask = UIAIM_STATUS;      // Zmianiamy status
               ai.status = ok?0:ACTS_HIDDEN;
               ai.statusMask = ACTS_HIDDEN; // Zmieniamy tylko ten jeden bit statusu
               if (ok) { // ¯eby by³o œmieszniej bêdziemy zmieniaæ jeszcze opis tekstowy...
                   bool desc = false;
                   char * d1 = "Jestem bez sieci i jestem z tego dumny!";
                   char * d2 = "Ja chcê nale¿eæ do sieeeeciiiii!";
                   ai.mask |= UIAIM_TXT; // Zmieniamy jeszcze text
                   ai.txt = desc?d2:d1;    // wybieramy tekst...
                   desc=!desc;
               }
               ICMessage(IMI_ACTION_SET , (int)&ai); // Gotowe!
           } else if (anBase->code == ACTN_ACTION) {
               /* Na koniec zasymulujemy d³ug¹ operacjê... */
               sDIALOG_long sdl;
               sdl.title = "actcfg.cpp";
               sdl.info = "Przy³¹czanie do sieci...";
               char * t [4]={"£¹czê","przy³¹czam","za³¹czam","roz³¹czam"};
               sdl.flag = DLONG_BLOCKING ;
               /* UWAGA! Okaza³o siê ¿e w API jest b³¹d, który przy Blokuj¹cych d³ugich operacjach
               objawia siê tym, ¿e w oknie z progresem bêdzie nieodœwie¿ony prostok¹t...
               Postaram siê usun¹æ problem w nowszej wersji... :) */
               ICMessage(IMI_LONGSTART , (int)&sdl); // zaczynamy
               for (int i=0; i<4; i++) {
                   for (int j=0; j<100; j++)
                     SleepEx(10,TRUE); // ZAWSZE u¿ywamy komend czekaj¹cych z EX jeœli jesteœmy w g³ównym w¹tku!
                                        // Powtarzam operacjê, poniewa¿ proces odœwie¿ania okienka bêdzie zrywa³ SleepEx
                   sdl.progress += 25;
                   sdl.info = t[i];
                   ICMessage(IMI_LONGSET , (int)&sdl, DSET_PROGRESS|DSET_INFO);   // koñczymy
                   
               }
                   for (int j=0; j<50;j++)
                     SleepEx(10,TRUE); 
               ICMessage(IMI_LONGEND , (int)&sdl);   // koñczymy

           }
           break;}
  }
  return 0;
}



int __stdcall IMessageProc(sIMessage_base * msgBase) {
 sIMessage_2params * msg = (msgBase->s_size>=sizeof(sIMessage_2params))?static_cast<sIMessage_2params*>(msgBase):0;
 switch (msgBase->id) {    /* Wiadomoœci na które TRZEBA odpowiedzieæ */
    case IM_PLUG_NET:        return NET_EXAMPLE; // Zwracamy wartoœæ sieci jako NET_EXAMPLE
    case IM_PLUG_TYPE:       return IMT_UI|IMT_CONTACT|IMT_CONFIG; // Ta wtyczka obs³uguje UI, kontakty i Config...
    case IM_PLUG_VERSION:    return (int)""; // 
    case IM_PLUG_SDKVERSION: return KONNEKT_SDK_V;  // Ta linijka jest wymagana!
    case IM_PLUG_SIG:        return (int)"EX2"; // Sygnaturka wtyczki (krótka, kilkuliterowa nazwa)
    case IM_PLUG_CORE_V:     return (int)"W98"; // Wymagana wersja rdzenia
    case IM_PLUG_UI_V:       return 0; // Wymagana wersja UI
    case IM_PLUG_NAME:       return (int)"actcfg.cpp"; // Pe³na nazwa wtyczki
    case IM_PLUG_NETNAME:    return 0; // Nazwa obs³ugiwanej sieci (o ile jak¹œ sieæ obs³uguje)
    case IM_PLUG_INIT:       Plug_Init(msg->p1,msg->p2);return Init();
    case IM_PLUG_DEINIT:     Plug_Deinit(msg->p1,msg->p2);return DeInit();

    case IM_SETCOLS:     return ISetCols();

    case IM_UI_PREPARE:      return IPrepare();
    case IM_START:           return IStart();
    case IM_END:             return IEnd();

    /* Obs³u¿ymy jeszcze IM_EX_TEST. Jeœli u¿yjemy wtyczki msgs.cpp razem z t¹
       powiniœmy zobaczyæ efekt ich wspó³pracy :) */
    case IM_EX_TEST:         ICMessage(IMI_NOTIFY , (int)"ACTCFG @ IM_EX_TEST");return 1;
    case IM_UIACTION:        return ActionProc((sUIActionNotify_base*)msg->p1);

    /* Tutaj obs³ugujemy wszystkie pozosta³e wiadomoœci */


 }
    if (Ctrl) Ctrl->setError(IMERROR_NORESULT);
    return 0;
}


/*

  To wszystko z nowoœci... Jak widzicie, po usuniêciu komentarzy a¿ tak du¿o nie jest, 
  a myœlê ¿e jest dosyæ prosto...

  Zapraszam do nastêpnego tutoriala :)

*/
