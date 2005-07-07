/* SIMPLE.CPP
   Przyk³adowa wtyczka dla programu Konnekt...

    -> Wykorzystanie kilku prostych komunikatów


   Powinna zostaæ skompilowana jako Win32DLL z wykorzystaniem
   wielow¹tkowej wersji biblioteki CRT!

   (c)2002 hao | Stamina
   http://www.stamina.eu.org/konnekt/sdk/
*/ 

#include "konnekt/plug_export.h"
#define NET_EXAMPLE 5 // Wartosc net tej wtyczki
int __stdcall DllMain(void * hinstDLL, unsigned long fdwReason, void * lpvReserved)
{
        return true;
}
//---------------------------------------------------------------------------

int IStart() {
  /* Tutaj wtyczkê uruchamiamy 
     ¯eby odebraæ ten komunikat (IM_START) trzeba podaæ jako typ wtyczki
     IMT_UI.
  */
  IMLOG("HELLO!");  // Zapisujemy coœ do konnekt.log
  // Logujemy wartoœæ zwrócon¹ przez IMC_PROFILEDIR
  // IMLOG przyjmuje ten sam format co funkcje z rodziny printf.
  IMLOG("IMC_PROFILE_DIR = %s" , ICMessage(IMC_PROFILEDIR)); 
  // Logujemy wartoœæ zwrócon¹ przez IMC_PLUG_COUNT
  IMLOG("IMC_PLUG_COUNT = %d" , ICMessage(IMC_PLUG_COUNT)); 
  // Dla przyk³adu logujemy coœ z flag¹. Potem bêdzie to mo¿na odfiltrowaæ...
  IMDEBUG(DBG_FUNC , "IStart()"):
  // Pobieramy ID wtyczki interfejsu (zawsze na pozycji 0)
  int UIHandle = ICMessage(IMC_PLUG_HANDLE , 0);
  // Logujemy nazwê wtyczki UI. Pobieramy j¹ wysy³aj¹c komunikat
  // bezpoœrednio do wtyczki.
  IMLOG("UI = \"%s\"" , IMessageDirect(IM_PLUG_NAME , UIHandle));
  // Wyœwietlamy komunikat w zale¿noœci od stanu po³¹czenia...
  if (ICMessage(IMC_CONNECTED)) {
      // Wysy³amy komunikat z net i type = 0 (to samo co ICMessage)
      // Wiadomoœæ dotrze do UI
      // Pojawi siê okno informuj¹ce
      IMessage(IMI_INFORM , 0 , 0 , (int)"Jesteœmy po³¹czeni z inernetem!");
  } else {
      // Pojawi siê okno b³êdu
      IMessage(IMI_ERROR , 0 , 0 , (int)"Nie wykry³em po³¹czenia!");
  }
  IMessage(IMI_INFORM , 0 , 0 , (int) "Zajrzyj do Konnekt.log - zobaczysz wygenerowane t¹ wtyczk¹ linijki!");
  return 1;
}
int IEnd() {
  /* Tutaj wtyczkê wy³¹czamy */
  return 1;
}


int __stdcall IMessageProc(sIMessage_base * msgBase) {
 sIMessage_2params * msg = (msgBase->s_size>=sizeof(sIMessage_2params))?static_cast<sIMessage_2params*>(msgBase):0;
 switch (msgBase->id) {
    /* Wiadomoœci na które TRZEBA odpowiedzieæ */
    case IM_PLUG_NET:        return NET_EXAMPLE; // Zwracamy wartoœæ NET, która MUSI byæ ró¿na od 0 i UNIKATOWA!
    case IM_PLUG_TYPE:       return IMT_UI; // Zwracamy jakiego typu jest nasza wtyczka (które wiadomoœci bêdziemy obs³ugiwaæ)
    case IM_PLUG_VERSION:    return (int)""; // Wersja wtyczki tekstowo ...
    case IM_PLUG_SDKVERSION: return KONNEKT_SDK_V;  // Ta linijka jest wymagana!
    case IM_PLUG_SIG:        return (int)"EX1"; // Sygnaturka wtyczki (krótka, kilkuliterowa nazwa)
    case IM_PLUG_NAME:       return (int)"simple.cpp"; // Pe³na nazwa wtyczki
    case IM_PLUG_NETNAME:    return 0; // Nazwa obs³ugiwanej sieci (o ile jak¹œ sieæ obs³uguje)
    case IM_PLUG_INIT:       Plug_Init(msg->p1,msg->p2);return 1;
    case IM_PLUG_DEINIT:     Plug_Deinit(msg->p1,msg->p2);return 1;

    case IM_START:           return IStart();


    /* Tutaj obs³ugujemy wszystkie pozosta³e wiadomoœci */
 }
	if (Ctrl) Ctrl->setError(IMERROR_NORESULT);
	return 0;
}

