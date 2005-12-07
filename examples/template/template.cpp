/* TEMPLATE.CPP
   Przyk³adowa wtyczka dla programu Konnekt...
   Idealny sposób ¿eby zacz¹æ pisaæ coœ swojego ...

   Powinna zostaæ skompilowana jako Win32DLL z wykorzystaniem
   wielow¹tkowej wersji biblioteki CRT!

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
/* Wszystkie poni¿sze funkcje nie s¹ wymagane (z wyj¹tekim IMEssageProc)...
   ale z nimi wszystko wygl¹da czytelniej :)
*/
int Init() {
  /* Tutaj inicjalizujemy wtyczkê,
       zg³aszamy ¿¹dania po³¹czeñ itp. */
  return 1;
}

int DeInit() {
  /* Najlepsze miejsce ¿eby posprz¹taæ...
  */
  return 1;
}

int IStart() {
  /* Tutaj wtyczkê uruchamiamy */
  return 1;
}
int IEnd() {
  /* Tutaj wtyczkê wy³¹czamy */
  return 1;
}

int ISetCols() {
  /* Tutaj rejestrujemy kolumny w plikach ustawieñ.
     Pamiêtaj o tym ¿e identyfikatory MUSZ¥ byæ UNIKATOWE! */
  return 1;
}

int IPrepare() {
  /* Tutaj rejestrujemy sie w interfejsie */
  return 1;
}

int ActionCfgProc(sUIActionNotify_base * anBase) {
  /* Tutaj obs³ugujemy akcje dla okna konfiguracji */ 
  /* Sytuacja taka sama jak przy ActionProc  */
  sUIActionNotify_2params * an = (anBase->s_size>=sizeof(sUIActionNotify_2params))?static_cast<sUIActionNotify_2params*>(anBase):0;
  switch (anBase->act.id & ~IMIB_CFG) {
    
  }
  return 0;
}

ActionProc(sUIActionNotify_base * anBase) {
  /* Tutaj obs³ugujemy akcje */ 
  /* Poni¿sza linijka s³u¿y TYLKO waszej wygodzie! 
     Wiêkszoœæ (o ile nie wszystkie) powiadomieñ przesy³ana jest jako sUIActionNotify_2params,
     korzystamy wtedy z obiektu an, w przeciwnym razie z anBase, lub castujemy do spodziewanego typu.
  */
  sUIActionNotify_2params * an = (anBase->s_size>=sizeof(sUIActionNotify_2params))?static_cast<sUIActionNotify_2params*>(anBase):0;

  if ((anBase->act.id & IMIB_) == IMIB_CFG) return ActionCfgProc(anBase); 
  switch (anBase->act.id) {
    
  }
  return 0;
}



int __stdcall IMessageProc(sIMessage_base * msgBase) {
    /* Tam gdzie nie u¿ywasz parametrów, najbezpieczniej korzystaæ z msgBase */
    /* Poni¿sza linijka jest dla Twojej wygody... 
     Wiêkszoœæ (o ile nie wszystkie) wiadomoœci przesy³ana jest jako sIMessage_2params,
     korzystamy wtedy z obiektu msg, w przeciwnym razie z msgBase, lub castujemy do spodziewanego typu.
    */
    sIMessage_2params * msg = (msgBase->s_size>=sizeof(sIMessage_2params))?static_cast<sIMessage_2params*>(msgBase):0;
    switch (msgBase->id) {
    /* Wiadomoœci na które TRZEBA odpowiedzieæ */
    case IM_PLUG_NET:        return 0; // Zwracamy wartoœæ NET, która MUSI byæ ró¿na od 0!
    case IM_PLUG_TYPE:       return 0; // Zwracamy jakiego typu jest nasza wtyczka (które wiadomoœci bêdziemy obs³ugiwaæ)
    case IM_PLUG_VERSION:    return (int)"1.0.0.0"; // Wersja wtyczki tekstowo major.minor.release.build ..., lub 0 je¿eli wersja zapisana jest w zasobach DLLa
    case IM_PLUG_SDKVERSION: return KONNEKT_SDK_V;  // Ta linijka jest wymagana!
    case IM_PLUG_SIG:        return (int)""; // Sygnaturka wtyczki (krótka, kilkuliterowa nazwa)
    case IM_PLUG_NAME:       return (int)""; // Pe³na nazwa wtyczki (ale najlepiej nie za d³uga!)
    case IM_PLUG_NETNAME:    return 0; // Nazwa obs³ugiwanej sieci (o ile jak¹œ sieæ obs³uguje)
    case IM_PLUG_INIT:       Plug_Init(msg->p1,msg->p2);return Init();
    case IM_PLUG_DEINIT:     Plug_Deinit(msg->p1,msg->p2);return DeInit();

    case IM_SETCOLS:     return ISetCols();

    case IM_UI_PREPARE:      return IPrepare();
    case IM_START:           return IStart();
    case IM_END:             return IEnd();

    case IM_UIACTION:        return ActionProc((sUIActionNotify_base*)msg->p1);

    /* Tutaj obs³ugujemy wszystkie pozosta³e komunikaty */
	/* Z ka¿dego komunikatu trzeba zwracaæ wartoœæ. W przeciwnym razie, 
	   zostanie ustawiony b³¹d i komunikat zostanie uznany za nie obs³u¿ony */

 }
 if (Ctrl) Ctrl->setError(IMERROR_NORESULT);
 return 0;
}

