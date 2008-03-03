/**
 * @file
 * Nag��wek eksportuj�cy deklaracje funkcji wymagane przez rdze� do poprawnej komunikacji.
 * Od razu importuje plug_shared.h.
 * Dodatkowo kilka funkcji / makr dla Waszej wygody :)
 */

#ifndef PLUGEXPORTH
#define PLUGEXPORTH

#include <Stamina/VersionControl.h>
#include "plug.h"

/**
 * Wskaznik do struktury #Controler.
 */
extern Controler * Ctrl;

#pragma pack(push, 1)


/**
 * Funkcje eksportowane
 */
#ifndef KONNEKT_SDK_NOEXPORT
  /**
   * Deklaracja jedynej eksportowanej z wtyczki funkcji.
   */
  extern "C"
     __declspec(dllexport) int __stdcall IMessageProc(sIMessage_base * msgBase);

  extern "C"
    __declspec(dllexport) void __stdcall KonnektApiVersions(fApiVersionCompare cmp);

#endif


/*
 * Wszystkie nastepne funkcje sa funkcjami TYLKO pomocniczymi ... Mozna je usunac, ale
 * najwygodniej jest z nich po prostu korzystac :)
 */

/**
 * Funkcja wysy�a do rdzenia #IMessage #IMC_LOG (kt�ra nic nie robi, ale jej tre�� mo�e zosta� zalogowana
 * w trybie Debug).
 *
 * @brief Je�eli program dzia�a w trybie Debug loguje tre�� wiadomo�ci do pliku konnekt.log (i do okna).
 *
 * @param format Format dok�adnie taki sam jak przy funkcjach printf
 * @param ... Parametry potrzebne do utworzenia wiadomo�ci
 * 
 * @attention W trybie @e Debug dost�pne jest okno debugowania (IMLOG) w kt�rym pokazywana jest tre�� IMLOG!
 */
void IMLOG(const char *format, ...);

/** 
 * Wysy�a IMLOG z komunikatem ostatniego b��du systemu Windows (GetLastError())
 */
void IMERROR();


/** 
 * Wysy�a wiadomo��. Wywo�uje bezpo�rednio Controler::IMessage.
 *
 * @param id Identyfikator wiadomo�ci
 * @param net Docelowa sie� wtyczek
 * @param type Docelowy typ wtyczek
 * @param p1, p2 Parametry
 * @sa gr_im net_ imt_
*/
int IMessage(unsigned int id, tNet net = Net::none, enIMessageType type = imtAll, int p1 = 0, int p2 = 0);

/** 
 * Wysy�a wiadomo��. Wywo�uje bezpo�rednio Controler::IMessage.
 */
int IMessage(sIMessage_base * msg);


/** 
 * Wysy�a wiadomo�� bezpo�rednio do rdzenia/ui (net = 0, type = 0).
 *
 * @param id Identyfikator wiadomo�ci
 * @param p1, p2 Parametry
 * @sa im_
 */
int ICMessage(unsigned int id, int p1 = 0, int p2 = 0);

/** 
 * Wysy�a wiadomo�� bezpo�rednio do wtyczki.
 *
 * @param id Identyfikator wiadomo�ci
 * @param plug ID wtyczki
 * @param p1, p2 Parametry
 * @sa im_ imc_plug_
 */
int IMessageDirect(unsigned int id, tPluginId plug, int p1 = 0, int p2 = 0);

/** 
 * Wysy�a wiadomo�� bezpo�rednio do wtyczki.
 *
 * @param plug ID wtyczki
 * @param msg Wska�nik do struktury IMessage
 */
int IMessageDirect(tPluginId plug, sIMessage_base * msg);


void WMProcess(void);

/*
 * --- THREAD SAFE ---
 */

/**
 * @defgroup ThreadSafe Makra do prze��czania w�tk�w.
 * @{
 */

/** 
 * Prze��czanie wiadomo�ci do prawid�owych w�tk�w.
 * Je�eli wiadomo�� zawiera kod, kt�ry @b MUSI by� wykonany
 * w g��wnym w�tku (np. tworzenie okien) mo�na na pocz�tku
 * kodu akcji wstawi� #IMESSAGE_TS().
 * Spos�b dzia�ania (w�tek "prawid�owy" to w�tek w kt�rym powinna dzia�a� wiadomo��) :
 *   - Makro sprawdza ID aktualnego w�tku
 *     - Je�eli jest r�wne ID @e prawid�owego w�tku wykonuje dalej...
 *     - Je�eli jest r�ne, kolejkuje procedur� APC w @e prawid�owym
 *       w�tku i oczekuje na zwr�cenie warto�ci.
 * 
 * Przyk�ad:
 * @code
 * int __stdcall IMessageProc(sIMessage_base * msg) {
 *   switch (msg->id) {
 *     case IM_NIEZABEZPIECZANA:
 *       return 1;
 *     case IM_ZABEZPIECZANA:
 *       IMESSAGE_TS();
 *       // Potencjalnie niebezpieczne operacje...
 *       return 1;
 *   }
 *   if (Ctrl) Ctrl->setError(IMERROR_NORESULT);
 *   // Je�eli wiadomo�� nie zwraca konkretnego wyniku
 *   // MUSI to zaznaczy�!
 *   return 0;
 * }
 * @endcode
 * 
 * @attention U�ycie makra jest dozwolone tylko je�eli nie zosta�
 * jeszcze wykonany @b �aden fragment kodu nale��cy do wiadomo�ci.
 * (powinien by� wstawiony @b od @b razu po @b case IM_...: .
 * @attention "Prze��czanie" odbywa si� poprzez procedury APC (patrz: MSDN)
 * Aby nie powiesi� ca�ego programu wszystkie zdarzenia oczekuj�ce
 * (Sleep, Wait itp.) musz� by� wykonywane w trybie Alertable
 * (SleepEx, Wait...Ex itp.), tak �eby procedura APC mog�a by� wykonana ...
 * @attention Je�eli zdaje ci si� �e wieszasz kolejki APC g��wnego w�tku
 * w��cz Test w oknie \@Dev...
 */
#define IMESSAGE_TS() \
  if (Ctrl->Is_TUS(0)) return Ctrl->RecallTS()
/**
 * To samo co #IMESSAGE_TS tyle, �e bez oczekiwania na wynik.
 * @warning Opcja potencjalnie niebezpieczna. Mo�e by� u�ywana tylko przy prostych
 * wiadomo�ciach, najlepiej nie przechowuj�cych w swoich parametrach @b �adnych
 * wska�nik�w (w momencie gdy wiadomo�� zostanie przetworzona, wska�niki mog� ju�
 * prowadzi� do zwolnionych obszar�w pami�ci).
 */
#define IMESSAGE_TS_NOWAIT(ret) \
  if (Ctrl->Is_TUS(0)) { Ctrl->RecallTS(0,0); return ret; }

/** @} */

/**
 * @defgroup gr_cfg Korzystanie z tablic ustawie�.
 * @{
 */
 
/**
 * Sprawdza czy @a ch nie jest == 0. Je�li jest - zwraca pusty ci�g znak�w.
 *
 * @param ch (char *)
 */
const char * SAFECHAR(const char * ch);

/**
 * Zwraca warto�� tekstow� z tablicy kontakt�w.
 * 
 * @param row (int) ID kontaktu
 * @param id  (int) ID kolumny
 * @param buff Bufor do kt�rego ma zosta� zapisana warto��. 
 * @param size Rozmiar bufora.
 *
 * @return (const char *)
 * Je�eli jako @a buff i @a size podamy 0, otrzymamy wska�nik do kopii warto�ci
 * przechowywanej w buforze tymczasowym (Controler::GetTempBuff). Je�eli wcze�niej
 * zablokujemy tablic�, otrzymamy najprawdopodobniej wska�nik bezpo�redni.
 * Je�eli @a buff b�dzie r�wny 0, a @a size -1, otrzymamy kopi� warto�ci
 * w �wie�o zaalokowanej strukturze, kt�r� nale�y zwolni� przez Controler::free.
 *
 * @sa #GETCNTCA
 */
const char * GETCNTC(int row, int id, char * buff = 0, unsigned int size = 0);

/**
 * Zwraca warto�� tekstow� (w nowym buforze) z tablicy kontakt�w.
 *
 * @param row (int) ID kontaktu
 * @param id  (int) ID kolumny
 *
 * @return (const char *)
 * @attention Zwr�cony bufor trzeba zwolni� przy pomocy Controler::free !
 */
#define GETCNTCA(row, id) GETCNTC(row, id, 0, -1)


/**
 * Zwraca warto�� liczbow� (4 bajty) z tablicy kontakt�w.
 *
 * @param row (int) ID kontaktu
 * @param id  (int) ID kolumny
 *
 * @return (int)
 */
int GETCNTI(int row, int id);
__int64 GETCNTI64(int row, int id);


/**
 * Ustawia warto�� tekstow� w tablicy kontakt�w.
 *
 * @param row (int) ID kontaktu
 * @param id  (int) ID kolumny
 * @param val (char*) warto�� do ustawienia
 */
bool SETCNTC(int row, int id, const char * val);

/**
 * Ustawia warto�� liczbow� (4 bajty) w tablicy kontakt�w.
 *
 * @param row (int) ID kontaktu
 * @param id  (int) ID kolumny
 * @param val (int) warto�� do ustawienia
 * @param mask (int) maska ustawianych bit�w
 */
bool SETCNTI(int row, int id, int val, int mask = -1);
bool SETCNTI64(int row, int id, __int64 val, __int64 mask = -1);

/**
 * Sprawdza czy @a row jest identyfikatorem, czy numerem wiersza.
 *
 * @param row (int) warto�� do sprawdzenia
 * @return (bool) true/false
 */
#define ISCNTID(row) (((row) != 0xFFFFFFFF) && ((row) & DT_ROWID_MASK))

/**
 * Zwraca identyfikator kontaktu.
 *
 * @param row (int) Numer wiersza z kontaktem w tablicy (ale mo�e by� te� identyfikator)
 * @return (int) identyfikator kontaktu.
 */
#define GETCNTID(row) (ISCNTID(row) ? row : Ctrl->DTgetID(DTCNT, (row)))

/**
 * Zwraca wiersz w tablicy z kontaktem.
 *
 * @param row (int) Identyfikator kontaktu (ale mo�e by� te� numer wiersza)
 * @return (int) Numer wiersza kontaktu.
 */
#define GETCNTPOS(row) (ISCNTID(row) ? Ctrl->DTgetPos(DTCNT, (row)) : row)

#ifndef _DTABLE_
  #define DT_ISROWID(row) (((row) != 0xFFFFFFFF) && ((row) & DT_ROWID_MASK))
  #define DT_MASKID(row) ((row) | DT_ROWID_MASK)
  #define DT_UNMASKID(row) (row & (~DT_ROWID_MASK)) // Zdejmuje maske z identyfikatora
#endif

/**
 * Zwraca warto�� liczbow� (4 bajty) z tablicy ustawie�.
 *
 * @param id  (int) ID kolumny
 * @return (int)
 */
int GETINT(int id);

/**
 * Zwraca warto�� tekstow� z tablicy ustawie�.
 *
 * @param id  (int) ID kolumny
 * @param buff Bufor do kt�rego ma zosta� zapisana warto��. 
 * @param size Rozmiar bufora.
 *
 * @return (const char *)
 * Je�eli jako @a buff i @a size podamy 0, otrzymamy wska�nik do kopii warto�ci
 * przechowywanej w buforze tymczasowym (Controler::GetTempBuff). Je�eli wcze�niej
 * zablokujemy tablic�, otrzymamy najprawdopodobniej wska�nik bezpo�redni.
 * Je�eli @a buff b�dzie r�wny 0, a @a size -1, otrzymamy kopi� warto�ci
 * w �wie�o zaalokowanej strukturze, kt�r� nale�y zwolni� przez Controler::free.
 *
 * @sa #GETSTRA
 */
const char * GETSTR(int id, char * buff = 0, unsigned int size = 0);
#define GETSTRA(id) GETSTR(id, 0, -1)

/**
 * Ustawia warto�� liczbow� (4 bajty) w tablicy ustawie�.
 *
 * @param id  (int) ID kolumny
 * @param val (int) warto��
 * @param mask (int) maska ustawianych bit�w
 */
bool SETINT(int id, int val, int mask = -1);

/**
 * Ustawia warto�� tekstow� (char*) w tablicy ustawie�.
 *
 * @param id  (int) ID kolumny
 * @param val (char*) warto��
 */
bool SETSTR(int id, const char * val);

#ifdef _STRING_
  #define GETCNTS(row, id) (string(GETCNTC(row, id)))
  #define GETSTRING(id) (string(GETSTR(id)))
#endif

/** @} */

/*
 * --------------------------------------------------------------------
 */
 
/** 
 * Ta funkcja powinna by� u�yta w #IM_INIT.
 * Parametrami s� @a p1 i @a p2 przes�ane razem z #IM_INIT
 */
int Plug_Init(int p1, int p2);

/** 
 * Ta funkcja powinna by� u�yta w #IM_DEINIT.
 * Parametrami s� @a p1 i @a p2 przes�ane razem z #IM_DEINIT
 */
void Plug_Deinit(int p1, int p2);

/*
 * --------------------------------------------------------------------
 */
 
#ifdef __BORLANDC__
  #define VSNPRINTF vsnprintf
#else
  #define VSNPRINTF _vsnprintf
#endif

#ifdef IMLOG_AUTOALLOC
  char * __vsaprintf(const char *format, va_list ap);
#endif

/** 
 * @sa Controler::IMLOG()
 */
void IMLOG(const char *format, ...);

/** 
 * @sa Controler::IMDEBUG()
 */
void IMDEBUG(enDebugLevel level, const char *format, ...);

#ifdef _WINDOWS_
  void IMERROR();
#endif


#pragma pack(pop)

#endif
