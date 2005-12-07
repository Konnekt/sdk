/* MSGS.CPP
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
   http://www.stamina.eu.org/konnekt/sdk/
*/ 

#include <memory.h>
#include <stdio.h>
#include "konnekt/plug_export.h"
#include "konnekt/ui.h"
#include "konnekt/plug_func.h"


#define IMIG_EXAMPLE 5100
#define IMIA_EXAMPLE_MGG 5101
#define IMIA_EXAMPLE_MSG 5102
#define IM_EX_TEST 5000 // Identyfikator wiadomoœci który wyœlemy do actcfg.cpp
#define MT_EXAMPLE 500
#define NET_EXAMPLE 5 // Wartosc net tej wtyczki
int __stdcall DllMain(void * hinstDLL, unsigned long fdwReason, void * lpvReserved)
{
        return true;
}
//---------------------------------------------------------------------------
/* Wszystkie poni¿sze funkcje nie s¹ wymagane (z wyj¹tekim IMEssageProc)...
   ale z nimi wszystko wygl¹da czytelniej :)
*/

int IPrepare() {
  /* Tutaj rejestrujemy sie w interfejsie */
  /*Mowa by³a ju¿ o tym w actcfg.cpp wiêc nie bêdê siê powtarza³... Tym razem stworzymy sobie osobny toolbar!*/
  UIGroupAdd(IMIG_BAR , IMIG_EXAMPLE , 0,"msgs.cpp");
  UIActionAdd(IMIG_EXAMPLE , IMIA_EXAMPLE_MSG , 0 , "MSG",UIIcon(IT_MESSAGE,0,MT_SERVEREVENT,0),40,40); // Ta akcja wstawi do kolejki "nasz¹" wiadomoœæ...
  UIActionAdd(IMIG_EXAMPLE , IMIA_EXAMPLE_MGG , 0 , "GG",UIIcon(IT_MESSAGE,0,MT_MESSAGE,0),40,40); // a ta wrzuci wiadomoœæ od kontaktu z UID 1 na GG 
                                 // pamiêtaj ¿eby w³¹czyæ przyjmowanie wiadomoœci od osób spoza listy!
  return 1;
}

ActionProc(sUIActionNotify_base * anBase) {
  sUIActionNotify_2params * an = (anBase->s_size>=sizeof(sUIActionNotify_2params))?static_cast<sUIActionNotify_2params*>(anBase):0;
  /* Tutaj obs³ugujemy akcje */ 
  switch (anBase->act.id) {
       case IMIA_EXAMPLE_MGG:{
           ACTIONONLY(anBase);
           cMessage m;
           memset(&m , 0 , sizeof(m));
           m.flag = MF_HANDLEDBYUI; // Wiadomoœæ zostanie obs³u¿ona w ca³oœci przez UI
           m.fromUid = "1";
           m.toUid = ""; // Wiadomoœæ ma przyjœæ, czyli jest do nas, czyli nie wpisujemy nic...
           m.net = NET_GG;
           m.time = 0; // Czas podajemy w formacie cTime64 - jest to mój w³asny format  i udostêpnie
              // obs³uguj¹c¹ go bibliotekê razem z nastêpnym SDK...
              // Format jest podobny jak tm co do iloœci pól, tyle ¿e upycha je wszystkie w 64 bitach...
              // Nie zastosowa³em zwyk³ego time_t bo jest dosyæ "krótki" , a time64_t obs³uguje tylko MSVC ...
           m.type = MT_MESSAGE;
           m.body = "HELLO WORLD!"; // Treœæ
           m.ext = ""; // Dodatkowe info... na razie pusto
           sMESSAGESELECT ms;
           ms.id = ICMessage(IMC_NEWMESSAGE , (int)&m);
           // w ms.id dostaliœmy ID dodanej wiadomoœci...
           // po dodaniu wiadomoœci ZAWSZE trzeba przejrzeæ kolejkê...
           // w sMESSAGESELECT podajemy jakie wiadomoœci dosz³y...
           // ustawiaj¹c tylko ms.id MessageQueue zostanie sprawdzone pod k¹tem tylko tej jednej
           // wiadomoœci... Trzeba jednak sprawdziæ czy wiadomoœæ zosta³a w ogóle dodana do
					 // kolejki...
           if (ms.id) ICMessage(IMC_MESSAGEQUEUE , (int)&ms);
           break;}
       case IMIA_EXAMPLE_MSG:{
           ACTIONONLY(anBase);
           cMessage m;
           memset(&m , 0 , sizeof(m));
           m.flag = 0; // Wiadomoœæ zostanie obs³u¿ona w ca³oœci przez UI
           m.fromUid = "msgs.cpp";
           m.toUid = ""; // Wiadomoœæ ma przyjœæ, czyli jest do nas, czyli nie wpisujemy nic...
           m.net = NET_EXAMPLE;
           m.time = 0; 
           m.type = MT_EXAMPLE | MT_MASK_NOTONLIST; // Nasz typ wiadomoœci... MT_MASK_NOTONLIST oznacza, ¿e rdzeñ nie sprawdzi od kogo przysz³a wiadomoœæ...
           m.body = "HELLO WORLD!"; // Treœæ
           m.ext = ""; // Dodatkowe info... na razie pusto
           ICMessage(IMC_NEWMESSAGE , (int)&m);
           /* Teraz zostanie wywo³ane IM_MSG_RCV na który zwrócimy IM_MSG_delete...
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
              */

           break;}
  }
  return 0;
}



int __stdcall IMessageProc(sIMessage_base * msgBase) {
 sIMessage_2params * msg = (msgBase->s_size>=sizeof(sIMessage_2params))?static_cast<sIMessage_2params*>(msgBase):0;
 switch (msgBase->id) {
    /* Wiadomoœci na które TRZEBA odpowiedzieæ */
    case IM_PLUG_NET:        return NET_EXAMPLE; // Zwracamy wartoœæ NET, która MUSI byæ ró¿na od 0 i UNIKATOWA!
    case IM_PLUG_TYPE:       return IMT_UI|IMT_MESSAGE|IMT_MSGUI; // Zwracamy jakiego typu jest nasza wtyczka (które wiadomoœci bêdziemy obs³ugiwaæ)
    case IM_PLUG_VERSION:    return (int)""; // Wersja wtyczki tekstowo ...
    case IM_PLUG_SDKVERSION: return KONNEKT_SDK_V;  // Ta linijka jest wymagana!
    case IM_PLUG_SIG:        return (int)"EX3"; // Sygnaturka wtyczki (krótka, kilkuliterowa nazwa)
    case IM_PLUG_NAME:       return (int)"msgs.cpp"; // Pe³na nazwa wtyczki
    case IM_PLUG_NETNAME:    return 0; // Nazwa obs³ugiwanej sieci (o ile jak¹œ sieæ obs³uguje)
    case IM_PLUG_INIT:       Plug_Init(msg->p1,msg->p2);return 1; // Zawsze musi zwróciæ 1!
    case IM_PLUG_DEINIT:     Plug_Deinit(msg->p1,msg->p2);return 1;


    case IM_UI_PREPARE:      return IPrepare();

    case IM_UIACTION:        return ActionProc((sUIActionNotify_base*)msg->p1);

    /* Rdzeñ odpytuje kolejne wtyczki czy bêd¹ obs³ugiwa³y dan¹ wiadomoœæ...
       Je¿eli nie zamierzamy - zwracamy 0...
       Mo¿emy równie¿ otworzyæ j¹ od razu i skasowaæ zwracaj¹ IM_MSG_delete co
       w³aœnie tutaj robimy...*/
    case IM_MSG_RCV:{
        cMessage * m = (cMessage*)msg->p1;
        /* Bierzemy tylko wiadomoœæ "naszego" typu */
        if (m->type == (MT_EXAMPLE | MT_MASK_NOTONLIST)) {
            char buff [200];
            sprintf(buff , "Dosta³em wiadomoœæ od %s:\n\n%s" , m->fromUid , m->body);
            ICMessage(IMI_INFORM , (int)buff);
            return IM_MSG_delete;
        }
        return 0;}

    /* Tutaj obs³ugujemy wszystkie pozosta³e wiadomoœci */


 }
    if (Ctrl) Ctrl->setError(IMERROR_NORESULT);
    return 0;
}

