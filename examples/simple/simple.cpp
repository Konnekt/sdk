/* SIMPLE.CPP
   Przyk�adowa wtyczka dla programu Konnekt...

    -> Wykorzystanie kilku prostych komunikat�w


   Powinna zosta� skompilowana jako Win32DLL z wykorzystaniem
   wielow�tkowej wersji biblioteki CRT!

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
  /* Tutaj wtyczk� uruchamiamy 
     �eby odebra� ten komunikat (IM_START) trzeba poda� jako typ wtyczki
     IMT_UI.
  */
  IMLOG("HELLO!");  // Zapisujemy co� do konnekt.log
  // Logujemy warto�� zwr�con� przez IMC_PROFILEDIR
  // IMLOG przyjmuje ten sam format co funkcje z rodziny printf.
  IMLOG("IMC_PROFILE_DIR = %s" , ICMessage(IMC_PROFILEDIR)); 
  // Logujemy warto�� zwr�con� przez IMC_PLUG_COUNT
  IMLOG("IMC_PLUG_COUNT = %d" , ICMessage(IMC_PLUG_COUNT)); 
  // Dla przyk�adu logujemy co� z flag�. Potem b�dzie to mo�na odfiltrowa�...
  IMDEBUG(DBG_FUNC , "IStart()"):
  // Pobieramy ID wtyczki interfejsu (zawsze na pozycji 0)
  int UIHandle = ICMessage(IMC_PLUG_HANDLE , 0);
  // Logujemy nazw� wtyczki UI. Pobieramy j� wysy�aj�c komunikat
  // bezpo�rednio do wtyczki.
  IMLOG("UI = \"%s\"" , IMessageDirect(IM_PLUG_NAME , UIHandle));
  // Wy�wietlamy komunikat w zale�no�ci od stanu po��czenia...
  if (ICMessage(IMC_CONNECTED)) {
      // Wysy�amy komunikat z net i type = 0 (to samo co ICMessage)
      // Wiadomo�� dotrze do UI
      // Pojawi si� okno informuj�ce
      IMessage(IMI_INFORM , 0 , 0 , (int)"Jeste�my po��czeni z inernetem!");
  } else {
      // Pojawi si� okno b��du
      IMessage(IMI_ERROR , 0 , 0 , (int)"Nie wykry�em po��czenia!");
  }
  IMessage(IMI_INFORM , 0 , 0 , (int) "Zajrzyj do Konnekt.log - zobaczysz wygenerowane t� wtyczk� linijki!");
  return 1;
}
int IEnd() {
  /* Tutaj wtyczk� wy��czamy */
  return 1;
}


int __stdcall IMessageProc(sIMessage_base * msgBase) {
 sIMessage_2params * msg = (msgBase->s_size>=sizeof(sIMessage_2params))?static_cast<sIMessage_2params*>(msgBase):0;
 switch (msgBase->id) {
    /* Wiadomo�ci na kt�re TRZEBA odpowiedzie� */
    case IM_PLUG_NET:        return NET_EXAMPLE; // Zwracamy warto�� NET, kt�ra MUSI by� r�na od 0 i UNIKATOWA!
    case IM_PLUG_TYPE:       return IMT_UI; // Zwracamy jakiego typu jest nasza wtyczka (kt�re wiadomo�ci b�dziemy obs�ugiwa�)
    case IM_PLUG_VERSION:    return (int)""; // Wersja wtyczki tekstowo ...
    case IM_PLUG_SDKVERSION: return KONNEKT_SDK_V;  // Ta linijka jest wymagana!
    case IM_PLUG_SIG:        return (int)"EX1"; // Sygnaturka wtyczki (kr�tka, kilkuliterowa nazwa)
    case IM_PLUG_NAME:       return (int)"simple.cpp"; // Pe�na nazwa wtyczki
    case IM_PLUG_NETNAME:    return 0; // Nazwa obs�ugiwanej sieci (o ile jak�� sie� obs�uguje)
    case IM_PLUG_INIT:       Plug_Init(msg->p1,msg->p2);return 1;
    case IM_PLUG_DEINIT:     Plug_Deinit(msg->p1,msg->p2);return 1;

    case IM_START:           return IStart();


    /* Tutaj obs�ugujemy wszystkie pozosta�e wiadomo�ci */
 }
	if (Ctrl) Ctrl->setError(IMERROR_NORESULT);
	return 0;
}

