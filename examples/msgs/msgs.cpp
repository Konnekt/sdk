/* MSGS.CPP
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
#define IM_EX_TEST 5000 // Identyfikator wiadomo�ci kt�ry wy�lemy do actcfg.cpp
#define MT_EXAMPLE 500
#define NET_EXAMPLE 5 // Wartosc net tej wtyczki
int __stdcall DllMain(void * hinstDLL, unsigned long fdwReason, void * lpvReserved)
{
        return true;
}
//---------------------------------------------------------------------------
/* Wszystkie poni�sze funkcje nie s� wymagane (z wyj�tekim IMEssageProc)...
   ale z nimi wszystko wygl�da czytelniej :)
*/

int IPrepare() {
  /* Tutaj rejestrujemy sie w interfejsie */
  /*Mowa by�a ju� o tym w actcfg.cpp wi�c nie b�d� si� powtarza�... Tym razem stworzymy sobie osobny toolbar!*/
  UIGroupAdd(IMIG_BAR , IMIG_EXAMPLE , 0,"msgs.cpp");
  UIActionAdd(IMIG_EXAMPLE , IMIA_EXAMPLE_MSG , 0 , "MSG",UIIcon(IT_MESSAGE,0,MT_SERVEREVENT,0),40,40); // Ta akcja wstawi do kolejki "nasz�" wiadomo��...
  UIActionAdd(IMIG_EXAMPLE , IMIA_EXAMPLE_MGG , 0 , "GG",UIIcon(IT_MESSAGE,0,MT_MESSAGE,0),40,40); // a ta wrzuci wiadomo�� od kontaktu z UID 1 na GG 
                                 // pami�taj �eby w��czy� przyjmowanie wiadomo�ci od os�b spoza listy!
  return 1;
}

ActionProc(sUIActionNotify_base * anBase) {
  sUIActionNotify_2params * an = (anBase->s_size>=sizeof(sUIActionNotify_2params))?static_cast<sUIActionNotify_2params*>(anBase):0;
  /* Tutaj obs�ugujemy akcje */ 
  switch (anBase->act.id) {
       case IMIA_EXAMPLE_MGG:{
           ACTIONONLY(anBase);
           cMessage m;
           memset(&m , 0 , sizeof(m));
           m.flag = MF_HANDLEDBYUI; // Wiadomo�� zostanie obs�u�ona w ca�o�ci przez UI
           m.fromUid = "1";
           m.toUid = ""; // Wiadomo�� ma przyj��, czyli jest do nas, czyli nie wpisujemy nic...
           m.net = NET_GG;
           m.time = 0; // Czas podajemy w formacie cTime64 - jest to m�j w�asny format  i udost�pnie
              // obs�uguj�c� go bibliotek� razem z nast�pnym SDK...
              // Format jest podobny jak tm co do ilo�ci p�l, tyle �e upycha je wszystkie w 64 bitach...
              // Nie zastosowa�em zwyk�ego time_t bo jest dosy� "kr�tki" , a time64_t obs�uguje tylko MSVC ...
           m.type = MT_MESSAGE;
           m.body = "HELLO WORLD!"; // Tre��
           m.ext = ""; // Dodatkowe info... na razie pusto
           sMESSAGESELECT ms;
           ms.id = ICMessage(IMC_NEWMESSAGE , (int)&m);
           // w ms.id dostali�my ID dodanej wiadomo�ci...
           // po dodaniu wiadomo�ci ZAWSZE trzeba przejrze� kolejk�...
           // w sMESSAGESELECT podajemy jakie wiadomo�ci dosz�y...
           // ustawiaj�c tylko ms.id MessageQueue zostanie sprawdzone pod k�tem tylko tej jednej
           // wiadomo�ci... Trzeba jednak sprawdzi� czy wiadomo�� zosta�a w og�le dodana do
					 // kolejki...
           if (ms.id) ICMessage(IMC_MESSAGEQUEUE , (int)&ms);
           break;}
       case IMIA_EXAMPLE_MSG:{
           ACTIONONLY(anBase);
           cMessage m;
           memset(&m , 0 , sizeof(m));
           m.flag = 0; // Wiadomo�� zostanie obs�u�ona w ca�o�ci przez UI
           m.fromUid = "msgs.cpp";
           m.toUid = ""; // Wiadomo�� ma przyj��, czyli jest do nas, czyli nie wpisujemy nic...
           m.net = NET_EXAMPLE;
           m.time = 0; 
           m.type = MT_EXAMPLE | MT_MASK_NOTONLIST; // Nasz typ wiadomo�ci... MT_MASK_NOTONLIST oznacza, �e rdze� nie sprawdzi od kogo przysz�a wiadomo��...
           m.body = "HELLO WORLD!"; // Tre��
           m.ext = ""; // Dodatkowe info... na razie pusto
           ICMessage(IMC_NEWMESSAGE , (int)&m);
           /* Teraz zostanie wywo�ane IM_MSG_RCV na kt�ry zwr�cimy IM_MSG_delete...
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
              */

           break;}
  }
  return 0;
}



int __stdcall IMessageProc(sIMessage_base * msgBase) {
 sIMessage_2params * msg = (msgBase->s_size>=sizeof(sIMessage_2params))?static_cast<sIMessage_2params*>(msgBase):0;
 switch (msgBase->id) {
    /* Wiadomo�ci na kt�re TRZEBA odpowiedzie� */
    case IM_PLUG_NET:        return NET_EXAMPLE; // Zwracamy warto�� NET, kt�ra MUSI by� r�na od 0 i UNIKATOWA!
    case IM_PLUG_TYPE:       return IMT_UI|IMT_MESSAGE|IMT_MSGUI; // Zwracamy jakiego typu jest nasza wtyczka (kt�re wiadomo�ci b�dziemy obs�ugiwa�)
    case IM_PLUG_VERSION:    return (int)""; // Wersja wtyczki tekstowo ...
    case IM_PLUG_SDKVERSION: return KONNEKT_SDK_V;  // Ta linijka jest wymagana!
    case IM_PLUG_SIG:        return (int)"EX3"; // Sygnaturka wtyczki (kr�tka, kilkuliterowa nazwa)
    case IM_PLUG_NAME:       return (int)"msgs.cpp"; // Pe�na nazwa wtyczki
    case IM_PLUG_NETNAME:    return 0; // Nazwa obs�ugiwanej sieci (o ile jak�� sie� obs�uguje)
    case IM_PLUG_INIT:       Plug_Init(msg->p1,msg->p2);return 1; // Zawsze musi zwr�ci� 1!
    case IM_PLUG_DEINIT:     Plug_Deinit(msg->p1,msg->p2);return 1;


    case IM_UI_PREPARE:      return IPrepare();

    case IM_UIACTION:        return ActionProc((sUIActionNotify_base*)msg->p1);

    /* Rdze� odpytuje kolejne wtyczki czy b�d� obs�ugiwa�y dan� wiadomo��...
       Je�eli nie zamierzamy - zwracamy 0...
       Mo�emy r�wnie� otworzy� j� od razu i skasowa� zwracaj� IM_MSG_delete co
       w�a�nie tutaj robimy...*/
    case IM_MSG_RCV:{
        cMessage * m = (cMessage*)msg->p1;
        /* Bierzemy tylko wiadomo�� "naszego" typu */
        if (m->type == (MT_EXAMPLE | MT_MASK_NOTONLIST)) {
            char buff [200];
            sprintf(buff , "Dosta�em wiadomo�� od %s:\n\n%s" , m->fromUid , m->body);
            ICMessage(IMI_INFORM , (int)buff);
            return IM_MSG_delete;
        }
        return 0;}

    /* Tutaj obs�ugujemy wszystkie pozosta�e wiadomo�ci */


 }
    if (Ctrl) Ctrl->setError(IMERROR_NORESULT);
    return 0;
}

