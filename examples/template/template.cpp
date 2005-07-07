/* TEMPLATE.CPP
   Przyk�adowa wtyczka dla programu Konnekt...
   Idealny spos�b �eby zacz�� pisa� co� swojego ...

   Powinna zosta� skompilowana jako Win32DLL z wykorzystaniem
   wielow�tkowej wersji biblioteki CRT!

   (c)2002 hao | Stamina
   http://www.stamina.eu.org/konnekt/sdk/
*/ 

#include "konnekt/plug_export.h"
#include "konnekt/ui.h"
#include "konnekt/plug_func.h"
int __stdcall DllMain(void * hinstDLL, unsigned long fdwReason, void * lpvReserved)
{
        return true;
}
//---------------------------------------------------------------------------
/* Wszystkie poni�sze funkcje nie s� wymagane (z wyj�tekim IMEssageProc)...
   ale z nimi wszystko wygl�da czytelniej :)
*/
int Init() {
  /* Tutaj inicjalizujemy wtyczk�,
       zg�aszamy ��dania po��cze� itp. */
  return 1;
}

int DeInit() {
  /* Najlepsze miejsce �eby posprz�ta�...
  */
  return 1;
}

int IStart() {
  /* Tutaj wtyczk� uruchamiamy */
  return 1;
}
int IEnd() {
  /* Tutaj wtyczk� wy��czamy */
  return 1;
}

int ISetCols() {
  /* Tutaj rejestrujemy kolumny w plikach ustawie�.
     Pami�taj o tym �e identyfikatory MUSZ� by� UNIKATOWE! */
  return 1;
}

int IPrepare() {
  /* Tutaj rejestrujemy sie w interfejsie */
  return 1;
}

int ActionCfgProc(sUIActionNotify_base * anBase) {
  /* Tutaj obs�ugujemy akcje dla okna konfiguracji */ 
  /* Sytuacja taka sama jak przy ActionProc  */
  sUIActionNotify_2params * an = (anBase->s_size>=sizeof(sUIActionNotify_2params))?static_cast<sUIActionNotify_2params*>(anBase):0;
  switch (anBase->act.id & ~IMIB_CFG) {
    
  }
  return 0;
}

ActionProc(sUIActionNotify_base * anBase) {
  /* Tutaj obs�ugujemy akcje */ 
  /* Poni�sza linijka s�u�y TYLKO waszej wygodzie! 
     Wi�kszo�� (o ile nie wszystkie) powiadomie� przesy�ana jest jako sUIActionNotify_2params,
     korzystamy wtedy z obiektu an, w przeciwnym razie z anBase, lub castujemy do spodziewanego typu.
  */
  sUIActionNotify_2params * an = (anBase->s_size>=sizeof(sUIActionNotify_2params))?static_cast<sUIActionNotify_2params*>(anBase):0;

  if ((anBase->act.id & IMIB_) == IMIB_CFG) return ActionCfgProc(anBase); 
  switch (anBase->act.id) {
    
  }
  return 0;
}



int __stdcall IMessageProc(sIMessage_base * msgBase) {
    /* Tam gdzie nie u�ywasz parametr�w, najbezpieczniej korzysta� z msgBase */
    /* Poni�sza linijka jest dla Twojej wygody... 
     Wi�kszo�� (o ile nie wszystkie) wiadomo�ci przesy�ana jest jako sIMessage_2params,
     korzystamy wtedy z obiektu msg, w przeciwnym razie z msgBase, lub castujemy do spodziewanego typu.
    */
    sIMessage_2params * msg = (msgBase->s_size>=sizeof(sIMessage_2params))?static_cast<sIMessage_2params*>(msgBase):0;
    switch (msgBase->id) {
    /* Wiadomo�ci na kt�re TRZEBA odpowiedzie� */
    case IM_PLUG_NET:        return 0; // Zwracamy warto�� NET, kt�ra MUSI by� r�na od 0!
    case IM_PLUG_TYPE:       return 0; // Zwracamy jakiego typu jest nasza wtyczka (kt�re wiadomo�ci b�dziemy obs�ugiwa�)
    case IM_PLUG_VERSION:    return (int)"1.0.0.0"; // Wersja wtyczki tekstowo major.minor.release.build ..., lub 0 je�eli wersja zapisana jest w zasobach DLLa
    case IM_PLUG_SDKVERSION: return KONNEKT_SDK_V;  // Ta linijka jest wymagana!
    case IM_PLUG_SIG:        return (int)""; // Sygnaturka wtyczki (kr�tka, kilkuliterowa nazwa)
    case IM_PLUG_NAME:       return (int)""; // Pe�na nazwa wtyczki (ale najlepiej nie za d�uga!)
    case IM_PLUG_NETNAME:    return 0; // Nazwa obs�ugiwanej sieci (o ile jak�� sie� obs�uguje)
    case IM_PLUG_INIT:       Plug_Init(msg->p1,msg->p2);return Init();
    case IM_PLUG_DEINIT:     Plug_Deinit(msg->p1,msg->p2);return DeInit();

    case IM_SETCOLS:     return ISetCols();

    case IM_UI_PREPARE:      return IPrepare();
    case IM_START:           return IStart();
    case IM_END:             return IEnd();

    case IM_UIACTION:        return ActionProc((sUIActionNotify_base*)msg->p1);

    /* Tutaj obs�ugujemy wszystkie pozosta�e komunikaty */
	/* Z ka�dego komunikatu trzeba zwraca� warto��. W przeciwnym razie, 
	   zostanie ustawiony b��d i komunikat zostanie uznany za nie obs�u�ony */

 }
 if (Ctrl) Ctrl->setError(IMERROR_NORESULT);
 return 0;
}

