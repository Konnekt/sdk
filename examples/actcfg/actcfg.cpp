/* ACTCFG.CPP
   Przyk�adowa wtyczka dla programu Konnekt...
   Idealny spos�b �eby zacz�� pisa� co� swojego ...

   Przyk�ady:
    -> Wykorzystania tablic ustawie�
    -> Wykorzystania okien dialogowych
    -> Obs�ugi akcji
    -> Obs�ugi konfiguracji
    -> Obs�ugi akcji kontakt�w
    -> Prostego �adowania ikonek

   Powinna zosta� skompilowana jako Win32DLL z wykorzystaniem
   wielow�tkowej wersji biblioteki CRT!
   Aby zobaczy� ikonk�, trzeba do skompilowanego projektu doda� Resources i do nich
   ikonk� (16px x 16px) o identyfikatorze r�wnym 100.

   (c)2002 hao | Stamina
   http://www.stamina.eu.org/konnekt/sdk/
*/ 


#include <string.h>
#include <windows.h>
#include "konnekt/plug_export.h"
#include "konnekt/ui.h"
#include "konnekt/plug_func.h"

/*   Definiujemy sobie kilka identyfikator�w z kt�rych b�dziemy korzysta�
   Jako �e korzystamy z warto�ci sieci r�wnej 5, wszystkie identyfikatory
   powinny sk�ada� si� z 5*1000+warto��.
   Najlepiej wszystkie identyfikatory trzyma� w osobnym pliku nag��wkowym
   np. actcfg_shared.h
   Identyfikatory nie mog� si� powtarza� w swoich "grupach"
*/

#define CFG_EXAMPLE_VALUE 5000  // Pozycja w tablicy konfiguracji
#define IMIG_CFG_EXAMPLE  5000  // Grupa w akcji w konfiguracji
#define IMIA_CFG_EXAMPLE_BUTTON   5001  // Akcja w konfiguracji
#define IMIG_EXAMPLE 5010  // Grupa na g��wnym toolbarze
#define IMIA_EXAMPLE_BUTTON  5011  // Akcja w menu na g��wnym toolbarze
#define IMIA_CNT_EXAMPLE   5020  // Akcja dla kontakt�w
#define IM_EX_TEST 5000 // Identyfikator wiadomo�ci do wykorzystania przez inne wtyczki...
#define IDI_EXAMPLE  5000            // Identyfikator ikonki
#define IDI_POINT 3 // Ta ikonka jest ju� zarejestrowana przez UI. Uwierzcie na s�owo :)

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
  /* Do usuwania r�wnie�...
  */
  return 1;
}

int ISetCols() {
  /* Rejestrujemy kolumn� w konfiguracji (DTCFG). 
     Niech b�dzie to warto�� tekstowa - czyli DT_CT_STR
	 Dla porz�dku nadamy jej te� nazw�...
     */
    SetColumn(DTCFG , CFG_EXAMPLE_VALUE , DT_CT_STR , "Warto�� domy�lna!" , "Example/actcfg/exampleValue");

  return 1;
}

int IPrepare() {
  /* Tutaj rejestrujemy sie w interfejsie.
     Do zarejestrowania mamy 5 akcji i jedn� ikonk�. 
     B�dziemy korzysta� z gotowych funkcji z plug_func.h*/
  /* W tej chwili SDK dysponuje tylko jedn� wiadomo�ci� do rejestrowania ikonek.
     W nast�pnej edycji SDK powinny pojawi� si� wi�ksze mo�liwo�ci... */
	IconRegister(IML_16 , IDI_EXAMPLE // ID rejestrowanej ikonki
		, Ctrl->hDll() // uchwyt do wtyczki
		, 100 // Identyfikator tej ikonki w zasobach wtyczki...
		);

  /* Rejestrujemy akcje kt�re b�d� widoczne na toolbarze w oknie g��wnym.

     Najpierw rejestrujemy grup�, kt�r� dodajemy do grupy IMIG_MAINTB.
     W ten spos�b tworzymy now� ikonk� na toolbarze.
     Wstawiamy j� na drug� pozycj� od lewej.
  */
  UIGroupInsert(IMIG_MAINTB  // Grupa - matka
       , IMIG_EXAMPLE        // ID nowej grupy
       , 1                   // Pozycja do wstawienia. 0 - pocz�tek -1 - koniec
       , 0                   // Status akcji. Powinni�my poda� ACTS_GROUP, ale UIGroupInsert robi to ju� za nas...
       , "Przyk�ad"          // Tre�� akcji. W tym wypadku zawarto�� tooltipa
       , IDI_POINT         // jako P1 w menusach podajemy ID ikonki
       ); // Reszt� parametr�w mo�emy sobie darowa�. Wszystkie i tak s� r�wne 0!
  /* Dodajemy akcj� */
  UIActionAdd(IMIG_EXAMPLE // Wstawiamy do utworzonej ju� grupy
      , IMIA_EXAMPLE_BUTTON
      , 0
      , "Wci�nij mnie!"
      , IDI_EXAMPLE // Identyfikator naszej ikonki z zasob�w wtyczki
      );
  /* Dodajemy akcj� do menu kontakt�w. Dodatkowo zrobimy tak, aby pojawia�a sie tylko przy
     kontaktach bez sieci!*/
  UIActionAdd(IMIG_CNT // Menu kontakt�w
      , IMIA_CNT_EXAMPLE // ID akcji
      , ACTR_INIT              // Rz�damy powiadomienia o utworzeniu pozycji w menu
      , "Jestem spoza sieci!"
      , IDI_EXAMPLE
      );
  /* �wietnie, dodajmy teraz akcje do konfiguracji */
  /* Najpierw tworzymy grup� */
  UIGroupAdd(IMIG_CFG  // Grupa - matka
       , IMIG_CFG_EXAMPLE        // ID nowej grupy
       , 0                   // Status akcji. Powinni�my poda� ACTS_GROUP, ale UIGroupInsert robi to ju� za nas...
       , "Przyk�ad!"          // Tre�� akcji. W tym wypadku zawarto�� tooltipa
       , IDI_POINT         // jako P1 w grupach konfiguracji podajemy ID ikonki
       ); // Reszt� parametr�w mo�emy sobie darowa�. Wszystkie i tak s� r�wne 0!
  /* Teraz robi si� ciut ciekawiej. Najpierw dodajmy kr�tki opis. Nie potrzebujemy do tego
     identyfikatora bo i tak nic z nim nie b�dziemy robi�.
     Funkcja UIActionCfgAdd przydaje si� TYLKO gdy chcemy przesun�� kontrolk� wzgl�dem osi x lub y.
     Spokojnie mo�na u�yc UIActionAdd ...
     */
  /* Dobr� 'manier�' w konfiguracji jest grupowanie kontrolek... a wi�c */
  UIActionAdd(IMIG_CFG_EXAMPLE , 0 , ACTT_GROUP , "Przyk�ad z actcfg.cpp");
    UIActionCfgAdd(IMIG_CFG_EXAMPLE  // Grupa - matka
        , 0        
        , ACTT_INFO           // Status akcji. Podajemy ACTT_INFO jako typ wstawianej kontrolki...
        , "Wpisz poni�ej dowolny tekst.\n\nJe�eli wpiszesz \"aa\" stanie si� co� dziwnego!"          // Tre�� informacji.
        , IDI_POINT         // jako P1 w menusach podajemy ID ikonki
        ,0,0  // Przesuni�cie wzgl�dem x i y zostawiamy w spokoju...
        ,100  // Szeroko��. ACTT_INFO jest rozci�gany na ca�� szeroko��. Nie ma znaczenia co tutaj wpiszemy
        ,40   // Wysoko��. Niech nasze info ma 40 pixeli wysoko�ci... 
        ); // Reszt� parametr�w mo�emy sobie darowa�. Wszystkie i tak s� r�wne 0!
    /* Teraz dodamy kontrolk� przy pomocy kt�rej mo�emy edytowa� nasz� kolumn� CFG_EXAMPLE_VALUE.
       UI automatycznie zajmuje si� konwersj� typ�w i �adowaniem/zapisywaniem. My za to
       b�dziemy sprawdza�, czy to co jest wpisywane, wpisywane jest poprawnie... */
    UIActionCfgAdd(IMIG_CFG_EXAMPLE  // Grupa - matka
        , IMIB_CFG   /* Ustawiaj�c identyfikator w ten spos�b mamy pewno��, �e faktycznym identyfikatorem akcji 
                        b�dzie IMIB_CFG|P1, gdzie P1 zaraz stanie si� identyfikatorem kolumny.
                     */
        , ACTT_EDIT|ACTSC_INLINE|ACTR_CHECK  /* ACTT_EDIT to kontrolka do edycji. Dzi�ki ACTSC_INLINE nast�pna
                                               kontrolka pojawi si� w tej samej linijce...
                                               Dzi�ki ACTR_CHECK zostaniemy powiadomieni o zmianach
                                               w tej kontrolce!
                                               */
        , "" CFGTIP "Spr�buj wpisa� 'aa'!"  // Wszystko co jest po CFGTIP p�jdzie do ToolTip'a!
        , CFG_EXAMPLE_VALUE // jako P1 w konfiguracji podajemy kolumn� w tablicy CFG przypisan� do
                          // do danej kontrolki. Podczas zapisywania, warto�� kontrolki zostanie
                          // zapisana w odpowiedniej kolumnie...  
        ,10,0  // Zr�bmy ma�e wci�cie...
        ,50  // Szeroko��.
        ,0   // Wysoko�ci� zajmie si� automat...
        ); // Reszt� parametr�w mo�emy sobie darowa�. Wszystkie i tak s� r�wne 0!
  /* Mo�e s��wko komentarza? */
  UIActionAdd(IMIG_CFG_EXAMPLE , 0 , ACTT_COMMENT , "<- tutaj wpisuj!");
  /* Zosta� nam jeszcze button */
  UIActionAdd(IMIG_CFG_EXAMPLE , IMIA_CFG_EXAMPLE_BUTTON , ACTT_BUTTON , "Kliknij mnie!",0,120,40);
  /* Otwart� grup� koniecznie trzeba zamkn��! */
  UIActionAdd(IMIG_CFG_EXAMPLE , 0 , ACTT_GROUPEND);

  return 1;
}

int IStart() {
  /* Tutaj wtyczk� uruchamiamy. W tym wypadku Konnekt robi wszystko za nas :) */

  return 1;
}
int IEnd() {
  /* Tutaj wtyczk� wy��czamy */
  return 1;
}


int ActionCfgProc(sUIActionNotify_base * anBase) {
  sUIActionNotify_2params * an = (anBase->s_size>=sizeof(sUIActionNotify_2params))?static_cast<sUIActionNotify_2params*>(anBase):0;
  /* Tutaj obs�ugujemy akcje dla okna konfiguracji */ 
  switch (anBase->act.id & ~IMIB_CFG) {
       case CFG_EXAMPLE_VALUE:
           if (anBase->code == ACTN_CHECK) {
               /* Sprawdzamy zawarto�� kontrolki. Jej aktualna warto�� znajduje si� notify1 */
               static char value [3] = "bb";
               if (!strcmp((char*)an->notify1 , "aa")) { // sprawdzamy czy wpisali�my 'aa'
                   an->notify1 = (int)value; // jak tak - zmieniamy na bb
                   /* Ze wzgl�du na pewn� "niedoskona�o��" kt�r� odkry�em pisz�c ten
                      kod TRZEBA zmieni� an->notify1 na inny bufor (kt�ry musi by�
                      wa�ny r�wnie� po opuszczeniu tej funkcji) �eby zmieni� warto�� kontrolki.
                      W nast�pnej wersji programu b��d b�dzie poprawiony...
                      
                      ACTN_CHECK przysy�any jest w tej chwili TYLKO do kontrolek z polem edycji...*/
               }

           }
           break;
  }
  return 0;
}

ActionProc(sUIActionNotify_base * anBase) {
  sUIActionNotify_2params * an = (anBase->s_size>=sizeof(sUIActionNotify_2params))?static_cast<sUIActionNotify_2params*>(anBase):0;
  /* Tutaj obs�ugujemy akcje */ 
  if ((anBase->act.id & IMIB_) == IMIB_CFG) return ActionCfgProc(anBase); 
  switch (anBase->act.id) {
       case IMIA_CFG_EXAMPLE_BUTTON: {
           ACTIONONLY(anBase); // Dzi�ki temu obs�u�ymy tu tylko ACTN_ACTION, czyli naci�ni�cie buttona
           /* Wy�wietlimy sobie okno dialogowe do wprowadzania tekstu */
           sDIALOG_enter sde;
           sde.info = "Wpisz co chcia�by� ujrze� w kontrolce edycji?";
           sde.title = "actcfg.cpp";
           /* jako warto�� pocz�tkow� we�miemy to, co jest wpisane w pole edycji
              �eby tego dokona� musimy wywo�a� odpowiedni� f-cj�...
              Jak wida� jej parametrem jest deskryptor akcji.
              Trzeba w nim poda� identyfikator grupy i akcji o kt�r� nam chodzi...
           */
           char buff [200];
           buff[199]=0;
           UIActionCfgGetValue(sUIAction(IMIG_CFG_EXAMPLE , IMIB_CFG|CFG_EXAMPLE_VALUE),buff,200);
           sde.value = buff;
           ICMessage(IMI_DLGENTER , (int)&sde);
           /* Wpisan� warto�� wrzucamy do kontrolki */
           /* Uwaga! Naci�ni�cie w okienku na Cancel ustawia value na 0!!! */
           if (sde.value) UIActionCfgSetValue(sUIAction(IMIG_CFG_EXAMPLE , IMIB_CFG|CFG_EXAMPLE_VALUE),sde.value);
           break;}
       case IMIA_EXAMPLE_BUTTON: {
           ACTIONONLY(anBase);
           /* Pobierzemy sobie warto�� naszej kontrolki i j� wy�wietlimy
              Najpierw jednak zapytamy u�ytkownika w jakim oknie chce zobaczy� wynik... */
           sDIALOG_choose sdc;
           sdc.def = 1;
           sdc.info = "Wybierz jak przedstawi� warto��?";
           sdc.title = "actcfg.cpp";
           sdc.items = "IMI_INFORM\nIMI_ERROR"; /* Ka�da linijka to nowy button */
           char buff [200];
           strncpy(buff , GETSTR(CFG_EXAMPLE_VALUE) , 200); // Pobieramy warto��
           switch (ICMessage(IMI_DLGBUTTONS , (int)&sdc)) {
               case 1: return ICMessage(IMI_INFORM , (int)buff); // Wybrali�my opcj� pierwsz�
               case 2: return ICMessage(IMI_ERROR , (int)buff);
               default: return ICMessage(IMI_INFORM , (int)"Nie to nie..."); // Cancel
           }
           break;}
       case IMIA_CNT_EXAMPLE: {  // Akcja w menu kontakt�w
           if (anBase->code == ACTN_CREATE) {
               /* Reagujemy na otworzenie menu. Mo�emy sprawdzi� czy kontakt jest z jakiej� sieci.
                  an to sUIActionNotify, czyli powiadomienie o zdarzeniu w akcji.
                  �eby sprawdzi� z jakim kontaktem powi�zana jest teraz akcja, trzeba sprawdzi�
                  jej deskryptor, kt�ry znajduje si� w an->act...
               */
               bool ok = GETCNTI(an->act.cnt , CNT_NET) == NET_NONE;
               sUIActionInfo ai;   // Zmienimy status kontrolki
               ai.act = an->act;  // Chodzi nam o t� sam� dla kt�rej wywo�ane jest powiadomienie prawda?
               ai.mask = UIAIM_STATUS;      // Zmianiamy status
               ai.status = ok?0:ACTS_HIDDEN;
               ai.statusMask = ACTS_HIDDEN; // Zmieniamy tylko ten jeden bit statusu
               if (ok) { // �eby by�o �mieszniej b�dziemy zmienia� jeszcze opis tekstowy...
                   bool desc = false;
                   char * d1 = "Jestem bez sieci i jestem z tego dumny!";
                   char * d2 = "Ja chc� nale�e� do sieeeeciiiii!";
                   ai.mask |= UIAIM_TXT; // Zmieniamy jeszcze text
                   ai.txt = desc?d2:d1;    // wybieramy tekst...
                   desc=!desc;
               }
               ICMessage(IMI_ACTION_SET , (int)&ai); // Gotowe!
           } else if (anBase->code == ACTN_ACTION) {
               /* Na koniec zasymulujemy d�ug� operacj�... */
               sDIALOG_long sdl;
               sdl.title = "actcfg.cpp";
               sdl.info = "Przy��czanie do sieci...";
               char * t [4]={"��cz�","przy��czam","za��czam","roz��czam"};
               sdl.flag = DLONG_BLOCKING ;
               /* UWAGA! Okaza�o si� �e w API jest b��d, kt�ry przy Blokuj�cych d�ugich operacjach
               objawia si� tym, �e w oknie z progresem b�dzie nieod�wie�ony prostok�t...
               Postaram si� usun�� problem w nowszej wersji... :) */
               ICMessage(IMI_LONGSTART , (int)&sdl); // zaczynamy
               for (int i=0; i<4; i++) {
                   for (int j=0; j<100; j++)
                     SleepEx(10,TRUE); // ZAWSZE u�ywamy komend czekaj�cych z EX je�li jeste�my w g��wnym w�tku!
                                        // Powtarzam operacj�, poniewa� proces od�wie�ania okienka b�dzie zrywa� SleepEx
                   sdl.progress += 25;
                   sdl.info = t[i];
                   ICMessage(IMI_LONGSET , (int)&sdl, DSET_PROGRESS|DSET_INFO);   // ko�czymy
                   
               }
                   for (int j=0; j<50;j++)
                     SleepEx(10,TRUE); 
               ICMessage(IMI_LONGEND , (int)&sdl);   // ko�czymy

           }
           break;}
  }
  return 0;
}



int __stdcall IMessageProc(sIMessage_base * msgBase) {
 sIMessage_2params * msg = (msgBase->s_size>=sizeof(sIMessage_2params))?static_cast<sIMessage_2params*>(msgBase):0;
 switch (msgBase->id) {    /* Wiadomo�ci na kt�re TRZEBA odpowiedzie� */
    case IM_PLUG_NET:        return NET_EXAMPLE; // Zwracamy warto�� sieci jako NET_EXAMPLE
    case IM_PLUG_TYPE:       return IMT_UI|IMT_CONTACT|IMT_CONFIG; // Ta wtyczka obs�uguje UI, kontakty i Config...
    case IM_PLUG_VERSION:    return (int)""; // 
    case IM_PLUG_SDKVERSION: return KONNEKT_SDK_V;  // Ta linijka jest wymagana!
    case IM_PLUG_SIG:        return (int)"EX2"; // Sygnaturka wtyczki (kr�tka, kilkuliterowa nazwa)
    case IM_PLUG_CORE_V:     return (int)"W98"; // Wymagana wersja rdzenia
    case IM_PLUG_UI_V:       return 0; // Wymagana wersja UI
    case IM_PLUG_NAME:       return (int)"actcfg.cpp"; // Pe�na nazwa wtyczki
    case IM_PLUG_NETNAME:    return 0; // Nazwa obs�ugiwanej sieci (o ile jak�� sie� obs�uguje)
    case IM_PLUG_INIT:       Plug_Init(msg->p1,msg->p2);return Init();
    case IM_PLUG_DEINIT:     Plug_Deinit(msg->p1,msg->p2);return DeInit();

    case IM_SETCOLS:     return ISetCols();

    case IM_UI_PREPARE:      return IPrepare();
    case IM_START:           return IStart();
    case IM_END:             return IEnd();

    /* Obs�u�ymy jeszcze IM_EX_TEST. Je�li u�yjemy wtyczki msgs.cpp razem z t�
       powini�my zobaczy� efekt ich wsp�pracy :) */
    case IM_EX_TEST:         ICMessage(IMI_NOTIFY , (int)"ACTCFG @ IM_EX_TEST");return 1;
    case IM_UIACTION:        return ActionProc((sUIActionNotify_base*)msg->p1);

    /* Tutaj obs�ugujemy wszystkie pozosta�e wiadomo�ci */


 }
    if (Ctrl) Ctrl->setError(IMERROR_NORESULT);
    return 0;
}


/*

  To wszystko z nowo�ci... Jak widzicie, po usuni�ciu komentarzy a� tak du�o nie jest, 
  a my�l� �e jest dosy� prosto...

  Zapraszam do nast�pnego tutoriala :)

*/
