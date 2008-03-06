#ifndef PLUGFUNCH
#define PLUGFUNCH

/**
 * @file
 * Zestaw makr i funkcji pomocniczych.
 * Musi byæ include'owany po plug_export.h.  
 */

using ::Stamina::StringRef;
using ::Stamina::String;

#include "ui.h"

/**
 * @addtogroup imi_action_
 * @{
 */

/**
 * @defgroup action_makra Funkcje pomocnicze.
 * @{
 */

/** 
 * Do wstawienia w switch'u akcji. Jeœli akcja nie zosta³a wywo³ana z kodem #ACTN_ACTION - wychodzi.
 */
#define ACTIONONLY(notify) if (notify->code != ACTN_ACTION) return 0;

/**
 * Pusta akcja.
 */
#define NOACTION sUIAction(0,0)

/**
 * Sprawdza czy Controler::isRunning() zwraca true, jeœli nie, wychodzi.
 */
#define ISRUNNING() if (!Ctrl->isRunning()) { Ctrl->setError(IMERROR_SHUTDOWN); return 0; }

/**
 * Dodaje akcjê.
 */
int UIActionAdd(int _parent, int _id, int _status = 0, const char * _txt = 0, int _p1 = 0, short _w = 0, short _h = 0, int _p2 = 0, int _param = 0);

/**
 * Wstawia akcjê.
 */
int UIActionInsert(int _parent, int _id, int _pos, int _status = 0, const char * _txt = 0, int _p1 = 0, short _w = 0, short _h = 0, int _p2 = 0, int _param = 0);

/**
 * Dodaje akcjê do konfiguracji.
 */
int UIActionCfgAdd(int _parent, int _id, int _status = 0, const char * _txt = 0, int _p1 = 0, short _x = 0, short _y = 0, short _w = 0, short _h = 0, int _p2 = 0, int _param = 0);

/**
 * Wstawia akcjê do konfiguracji.
 */
int UIActionCfgInsert(int _parent, int _id, int _pos, int _status = 0, const char * _txt = 0, int _p1 = 0, short _x = 0, short _y = 0, short _w = 0, short _h = 0, int _p2 = 0, int _param = 0);


/**
 * Dodaje grupê.
 */
int UIGroupAdd(int _parent, int _id, int _status = 0, const char * _txt = 0, int _p1 = 0, short _w = 0, short _h = 0, int _p2 = 0, int _param = 0);
/**
 * Wstawia grupê.
 */
int UIGroupInsert(int _parent, int _id, int _pos, int _status = 0, const char * _txt = 0, int _p1 = 0, short _w = 0, short _h = 0, int _p2 = 0, int _param = 0);
/**
 * Zwraca pozycjê w grupie.
 */
int UIActionGetPos(int _parent, int _id);

/**
 * Pobiera akcje.
 */
int UIActionSet(sUIActionInfo & nfo);
/**
 * Ustawia akcje.
 */
int UIActionGet(sUIActionInfo & nfo);


/**
 * Ustawia status.
 */
int UIActionSetStatus(sUIAction act, int status, int mask = -1);
int UIActionGetStatus(sUIAction act);

/**
 * Zwraca uchwyt grupy
 */
void * UIGroupHandle(sUIAction act);
/**
 * Zwraca uchwyt akcji
 */
void * UIActionHandle(sUIAction act);
/** 
 * Zwraca uchwyt akcji dla kontrolek z ACTR_SETCNT
 * W niektórych przypadkach pozwala na pobranie uchwytu
 * bez zmieniania kontaktu przypisanego do akcji...
 */
void * UIActionHandleDirect(sUIAction act);

int UIActionCall(sUIActionNotify_base * an);

/**
 * Ustawia status.
 */
int UIActionSetStatus(int parent, int id, int status, int mask = -1);

/**
 * Ustawia text.
 */
int UIActionSetText(sUIAction act, const char * txt);
int UIActionSetText(int parent, int id, const char * txt);

/**
 * Ustawia wartoœæ kontrolki w konfiguracji.
 */
int UIActionCfgSetValue(sUIAction act, const char * val, bool convert = true);
/**
 * Pobiera wartoœæ kontrolki z konfiguracji.
 */
const char * UIActionCfgGetValue(sUIAction act, char * val, int size, bool convert = true);

/** @} */

/** 
 * Dodaje standardowy zestaw akcji z boxem informacyjnym.
 *
 * @param parent Identyfikator akcji-rodzica
 * @param title Tytu³ boxa
 * @param info Treœæ informacji (html)
 * @param ico URL ikonki/obrazka
 * @param height Wysokoœæ treœci (Najlepiej podaæ ujemn¹ liczbê wierszy przy minimalnej szerokoœci...)
 * @param icoWidth Szerokoœæ ikonki (domyœlnie 32)
 * @param icoHeight Wysokoœæ ikonki (domyœlnie taka sama jak szerokoœæ)
 */
void UIActionCfgAddInfoBox(unsigned int parent, const char * title, const char * info, const char * ico, int height = 0, int icoWidth = 0, int icoHeight = 0);
/** 
 * Dodaje standardowy zestaw akcji z boxem informacyjnym.
 *
 * @param parent Identyfikator akcji-rodzica
 * @param title Tytu³ boxa
 * @param info Treœæ informacji (html)
 * @param ico identyfikator ikonki na liœcie IML_16, lub IML_32
 * @param height Wysokoœæ treœci (Najlepiej podaæ ujemn¹ liczbê wierszy przy minimalnej szerokoœci...)
 * @param icoSize Szerokoœæ/Wysokoœæ ikonki (domyœlnie 32)
 */
void UIActionCfgAddInfoBox(unsigned int parent, const char * title, const char * info, unsigned int ico, int height = 0, int icoSize=32);

/** 
 * Dodaje standardowy zestaw akcji z boxem opisuj¹cym wtyczkê.
 *
 * @param parent Identyfikator akcji-rodzica
 * @param info Tekst (html) z informacj¹ o wtyczce
 * @param ico URL do ikonki
 * @param height Wysokoœæ tekstu. Najlepiej podaæ ujemn¹ liczbê wierszy przy minimalnej szerokoœci...
 * @param name Nazwa wtyczki do wyœwietlenia. Je¿eli pominiesz ten parametr, zarówno nazwa jak i wersja zostan¹ pobrane automatycznie.
 */
void UIActionCfgAddPluginInfoBox(unsigned int parent, const char * info, const char * ico = 0, int height = 0, const char * name = 0);

/** 
 * Dodaje standardowy zestaw akcji z boxem opisuj¹cym wtyczkê i przyciskiem z logiem i tipem z dodatkowymi informacjami.
 *
 * @param parent Identyfikator akcji-rodzica
 * @param info Tekst (html) z informacj¹ o funkcjonalnoœci
 * @param about_info Tekst (html) z dodatkowymi informacjami o wtyczce
 * @param ico URL do ikonki
 * @param height Wysokoœæ tekstu. Najlepiej podaæ ujemn¹ liczbê wierszy przy minimalnej szerokoœci...
 * @param name Nazwa wtyczki do wyœwietlenia. Je¿eli pominiesz ten parametr, zarówno nazwa jak i wersja zostan¹ pobrane automatycznie.
 * @param frame @a true jeœli ma rysowaæ ramkê wokó³
 */
void UIActionCfgAddPluginInfoBox2(unsigned int parent, const char * info, const char * about_info, const char * ico = 0, int height = 0, const char * name = 0, bool frame = true);

/** @} */  // imi_action

/** 
 * @defgroup icon_makra Funkcje do ikonek
 * @{
 */

int IconRegister(IML_enum target, int ID, const char * URL);
int IconRegister(IML_enum target, int ID, HINSTANCE inst, int icoID, int type = 1);
int IconRegister(IML_enum target, int ID, HANDLE image, int type = 1);
int IconRegisterList(IML_enum target, int count, int * IDList, HANDLE image, HANDLE mask = 0, int w = 0);

#ifdef _INC_COMMCTRL
  int IconRegisterList(IML_enum target, int count, int * IDList, HIMAGELIST ImageList);
#endif

/** @} */

bool GetExtParam(const char * ext, const char * name, char * valueBuff, size_t buffSize);
bool SetExtParam(const char * ext, const char * name, const char * value, char * extBuff, size_t buffSize);

#ifdef _STRING_
  std::string GetExtParam(const std::string ext, const std::string name);
  std::string SetExtParam(const std::string ext, const std::string name, const std::string value);

  /** 
   * Zwraca wartoœæ parametrów przekazywanych do kontrolek konfiguracji w sUIActionInfo::txt
   */
  std::string GetActParam(const std::string & txt, const std::string & param);
  /** 
   * Ustawia wartoœæ parametrów przekazywanych do kontrolek konfiguracji w sUIActionInfo::txt 
   */
  std::string SetActParam(const std::string & txt, const std::string & param, const std::string & value);

  bool ActParamExists(const std::string & txt, const std::string & param);
  bool ParamSpecialChar(unsigned char ch);

#endif

/** 
 * Ustawia status kontaktu. 
 */
int CntSetStatus(unsigned int cntID, unsigned int status, const char * info = 0);
/** 
 * Powinno byæ uruchomione zaraz przed zmian¹ statusu wtyczki. 
 */
int PlugStatusChange(unsigned int status, const char * info = 0);

/** 
 * Zapisuje wartoœæ tekstow¹ kontaktu w tablicy, lub oknie "Wiêcej" w zale¿noœci od @a toWindow.
 * Przydatne przy #IM_CNT_DOWNLOAD...
 *
 * @param toWindow (bool) czy ma zapisywaæ do okna
 * @param cntID ID kontaktu
 * @param colID ID kolumny
 * @param value Wartoœæ tekstowa
 */
void CntSetInfoValue(bool toWindow, int cntID, int colID, const char * value);
/** 
 * Pobiera wartoœæ tekstow¹ kontaktu w tablicy, lub oknie "Wiêcej" w zale¿noœci od @a fromWindow.
 * Przydatne przy #IM_CNT_UPLOAD...
 *
 * @param fromWindow (bool) czy ma pobieraæ z okna
 * @param cntID ID kontaktu
 * @param colID ID kolumny
 */
const char * CntGetInfoValue(bool fromWindow, int cntID, int colID);

/** 
 * Tworzy kolumnê w konfiguracji (@ref #IM_SETCOLS)
 */
int SetColumn(tTable table, int id, int type, int def, const char * name = 0);
/** 
 * Tworzy kolumnê w konfiguracji (@ref #IM_SETCOLS)
 */
inline int SetColumn(tTable table, int id, int type, const char * def , const char * name = 0) {
  return SetColumn(table, id, type, (int) def, name);
}

void testResult(const StringRef& title, int should, int got, bool swap = false);
void testResult(const StringRef& title, const StringRef& should, const StringRef& got, bool swap = false);

inline void testResult(int should, int got, bool swap = false) {
  testResult("", should, got, swap);
}
inline void testResult(const StringRef& should, const StringRef& got, bool swap = false) {
  testResult("", should, got, swap);
}


/** 
 * Zamienia cztery parametry wersji w liczbe typu long. 
 */
#define VERSION_TO_NUM(maj, min, rls, bld) ((((maj) & 0xF) << 28) | (((min) & 0xFF) << 20) | (((rls) & 0xFF) << 12) | ((bld) & 0xFFF))
#define VERSION_MAJ(ver) (((ver) >> 28) & 0xF)
#define VERSION_MIN(ver) (((ver) >> 20) & 0xFF)
#define VERSION_RLS(ver) (((ver) >> 12) & 0xFF)
#define VERSION_BLD(ver) ((ver) & 0xFFF)

#endif