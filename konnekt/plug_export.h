/**
 * @file
 * Nag³ówek eksportuj¹cy deklaracje funkcji wymagane przez rdzeñ do poprawnej komunikacji.
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
 * Funkcja wysy³a do rdzenia #IMessage #IMC_LOG (która nic nie robi, ale jej treœæ mo¿e zostaæ zalogowana
 * w trybie Debug).
 *
 * @brief Je¿eli program dzia³a w trybie Debug loguje treœæ wiadomoœci do pliku konnekt.log (i do okna).
 *
 * @param format Format dok³adnie taki sam jak przy funkcjach printf
 * @param ... Parametry potrzebne do utworzenia wiadomoœci
 * 
 * @attention W trybie @e Debug dostêpne jest okno debugowania (IMLOG) w którym pokazywana jest treœæ IMLOG!
 */
void IMLOG(const char *format, ...);

/** 
 * Wysy³a IMLOG z komunikatem ostatniego b³êdu systemu Windows (GetLastError())
 */
void IMERROR();


/** 
 * Wysy³a wiadomoœæ. Wywo³uje bezpoœrednio Controler::IMessage.
 *
 * @param id Identyfikator wiadomoœci
 * @param net Docelowa sieæ wtyczek
 * @param type Docelowy typ wtyczek
 * @param p1, p2 Parametry
 * @sa gr_im net_ imt_
*/
int IMessage(unsigned int id, tNet net = Net::none, enIMessageType type = imtAll, int p1 = 0, int p2 = 0);

/** 
 * Wysy³a wiadomoœæ. Wywo³uje bezpoœrednio Controler::IMessage.
 */
int IMessage(sIMessage_base * msg);


/** 
 * Wysy³a wiadomoœæ bezpoœrednio do rdzenia/ui (net = 0, type = 0).
 *
 * @param id Identyfikator wiadomoœci
 * @param p1, p2 Parametry
 * @sa im_
 */
int ICMessage(unsigned int id, int p1 = 0, int p2 = 0);

/** 
 * Wysy³a wiadomoœæ bezpoœrednio do wtyczki.
 *
 * @param id Identyfikator wiadomoœci
 * @param plug ID wtyczki
 * @param p1, p2 Parametry
 * @sa im_ imc_plug_
 */
int IMessageDirect(unsigned int id, tPluginId plug, int p1 = 0, int p2 = 0);

/** 
 * Wysy³a wiadomoœæ bezpoœrednio do wtyczki.
 *
 * @param plug ID wtyczki
 * @param msg WskaŸnik do struktury IMessage
 */
int IMessageDirect(tPluginId plug, sIMessage_base * msg);


void WMProcess(void);

/*
 * --- THREAD SAFE ---
 */

/**
 * @defgroup ThreadSafe Makra do prze³¹czania w¹tków.
 * @{
 */

/** 
 * Prze³¹czanie wiadomoœci do prawid³owych w¹tków.
 * Je¿eli wiadomoœæ zawiera kod, który @b MUSI byæ wykonany
 * w g³ównym w¹tku (np. tworzenie okien) mo¿na na pocz¹tku
 * kodu akcji wstawiæ #IMESSAGE_TS().
 * Sposób dzia³ania (w¹tek "prawid³owy" to w¹tek w którym powinna dzia³aæ wiadomoœæ) :
 *   - Makro sprawdza ID aktualnego w¹tku
 *     - Je¿eli jest równe ID @e prawid³owego w¹tku wykonuje dalej...
 *     - Je¿eli jest ró¿ne, kolejkuje procedurê APC w @e prawid³owym
 *       w¹tku i oczekuje na zwrócenie wartoœci.
 * 
 * Przyk³ad:
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
 *   // Je¿eli wiadomoœæ nie zwraca konkretnego wyniku
 *   // MUSI to zaznaczyæ!
 *   return 0;
 * }
 * @endcode
 * 
 * @attention U¿ycie makra jest dozwolone tylko je¿eli nie zosta³
 * jeszcze wykonany @b ¿aden fragment kodu nale¿¹cy do wiadomoœci.
 * (powinien byæ wstawiony @b od @b razu po @b case IM_...: .
 * @attention "Prze³¹czanie" odbywa siê poprzez procedury APC (patrz: MSDN)
 * Aby nie powiesiæ ca³ego programu wszystkie zdarzenia oczekuj¹ce
 * (Sleep, Wait itp.) musz¹ byæ wykonywane w trybie Alertable
 * (SleepEx, Wait...Ex itp.), tak ¿eby procedura APC mog³a byæ wykonana ...
 * @attention Je¿eli zdaje ci siê ¿e wieszasz kolejki APC g³ównego w¹tku
 * w³¹cz Test w oknie \@Dev...
 */
#define IMESSAGE_TS() \
  if (Ctrl->Is_TUS(0)) return Ctrl->RecallTS()
/**
 * To samo co #IMESSAGE_TS tyle, ¿e bez oczekiwania na wynik.
 * @warning Opcja potencjalnie niebezpieczna. Mo¿e byæ u¿ywana tylko przy prostych
 * wiadomoœciach, najlepiej nie przechowuj¹cych w swoich parametrach @b ¿adnych
 * wskaŸników (w momencie gdy wiadomoœæ zostanie przetworzona, wskaŸniki mog¹ ju¿
 * prowadziæ do zwolnionych obszarów pamiêci).
 */
#define IMESSAGE_TS_NOWAIT(ret) \
  if (Ctrl->Is_TUS(0)) { Ctrl->RecallTS(0,0); return ret; }

/** @} */

/**
 * @defgroup gr_cfg Korzystanie z tablic ustawieñ.
 * @{
 */
 
/**
 * Sprawdza czy @a ch nie jest == 0. Jeœli jest - zwraca pusty ci¹g znaków.
 *
 * @param ch (char *)
 */
const char * SAFECHAR(const char * ch);

/**
 * Zwraca wartoœæ tekstow¹ z tablicy kontaktów.
 * 
 * @param row (int) ID kontaktu
 * @param id  (int) ID kolumny
 * @param buff Bufor do którego ma zostaæ zapisana wartoœæ. 
 * @param size Rozmiar bufora.
 *
 * @return (const char *)
 * Je¿eli jako @a buff i @a size podamy 0, otrzymamy wskaŸnik do kopii wartoœci
 * przechowywanej w buforze tymczasowym (Controler::GetTempBuff). Je¿eli wczeœniej
 * zablokujemy tablicê, otrzymamy najprawdopodobniej wskaŸnik bezpoœredni.
 * Je¿eli @a buff bêdzie równy 0, a @a size -1, otrzymamy kopiê wartoœci
 * w œwie¿o zaalokowanej strukturze, któr¹ nale¿y zwolniæ przez Controler::free.
 *
 * @sa #GETCNTCA
 */
const char * GETCNTC(int row, int id, char * buff = 0, unsigned int size = 0);

/**
 * Zwraca wartoœæ tekstow¹ (w nowym buforze) z tablicy kontaktów.
 *
 * @param row (int) ID kontaktu
 * @param id  (int) ID kolumny
 *
 * @return (const char *)
 * @attention Zwrócony bufor trzeba zwolniæ przy pomocy Controler::free !
 */
#define GETCNTCA(row, id) GETCNTC(row, id, 0, -1)


/**
 * Zwraca wartoœæ liczbow¹ (4 bajty) z tablicy kontaktów.
 *
 * @param row (int) ID kontaktu
 * @param id  (int) ID kolumny
 *
 * @return (int)
 */
int GETCNTI(int row, int id);
__int64 GETCNTI64(int row, int id);


/**
 * Ustawia wartoœæ tekstow¹ w tablicy kontaktów.
 *
 * @param row (int) ID kontaktu
 * @param id  (int) ID kolumny
 * @param val (char*) wartoœæ do ustawienia
 */
bool SETCNTC(int row, int id, const char * val);

/**
 * Ustawia wartoœæ liczbow¹ (4 bajty) w tablicy kontaktów.
 *
 * @param row (int) ID kontaktu
 * @param id  (int) ID kolumny
 * @param val (int) wartoœæ do ustawienia
 * @param mask (int) maska ustawianych bitów
 */
bool SETCNTI(int row, int id, int val, int mask = -1);
bool SETCNTI64(int row, int id, __int64 val, __int64 mask = -1);

/**
 * Sprawdza czy @a row jest identyfikatorem, czy numerem wiersza.
 *
 * @param row (int) wartoœæ do sprawdzenia
 * @return (bool) true/false
 */
#define ISCNTID(row) (((row) != 0xFFFFFFFF) && ((row) & DT_ROWID_MASK))

/**
 * Zwraca identyfikator kontaktu.
 *
 * @param row (int) Numer wiersza z kontaktem w tablicy (ale mo¿e byæ te¿ identyfikator)
 * @return (int) identyfikator kontaktu.
 */
#define GETCNTID(row) (ISCNTID(row) ? row : Ctrl->DTgetID(DTCNT, (row)))

/**
 * Zwraca wiersz w tablicy z kontaktem.
 *
 * @param row (int) Identyfikator kontaktu (ale mo¿e byæ te¿ numer wiersza)
 * @return (int) Numer wiersza kontaktu.
 */
#define GETCNTPOS(row) (ISCNTID(row) ? Ctrl->DTgetPos(DTCNT, (row)) : row)

#ifndef _DTABLE_
  #define DT_ISROWID(row) (((row) != 0xFFFFFFFF) && ((row) & DT_ROWID_MASK))
  #define DT_MASKID(row) ((row) | DT_ROWID_MASK)
  #define DT_UNMASKID(row) (row & (~DT_ROWID_MASK)) // Zdejmuje maske z identyfikatora
#endif

/**
 * Zwraca wartoœæ liczbow¹ (4 bajty) z tablicy ustawieñ.
 *
 * @param id  (int) ID kolumny
 * @return (int)
 */
int GETINT(int id);

/**
 * Zwraca wartoœæ tekstow¹ z tablicy ustawieñ.
 *
 * @param id  (int) ID kolumny
 * @param buff Bufor do którego ma zostaæ zapisana wartoœæ. 
 * @param size Rozmiar bufora.
 *
 * @return (const char *)
 * Je¿eli jako @a buff i @a size podamy 0, otrzymamy wskaŸnik do kopii wartoœci
 * przechowywanej w buforze tymczasowym (Controler::GetTempBuff). Je¿eli wczeœniej
 * zablokujemy tablicê, otrzymamy najprawdopodobniej wskaŸnik bezpoœredni.
 * Je¿eli @a buff bêdzie równy 0, a @a size -1, otrzymamy kopiê wartoœci
 * w œwie¿o zaalokowanej strukturze, któr¹ nale¿y zwolniæ przez Controler::free.
 *
 * @sa #GETSTRA
 */
const char * GETSTR(int id, char * buff = 0, unsigned int size = 0);
#define GETSTRA(id) GETSTR(id, 0, -1)

/**
 * Ustawia wartoœæ liczbow¹ (4 bajty) w tablicy ustawieñ.
 *
 * @param id  (int) ID kolumny
 * @param val (int) wartoœæ
 * @param mask (int) maska ustawianych bitów
 */
bool SETINT(int id, int val, int mask = -1);

/**
 * Ustawia wartoœæ tekstow¹ (char*) w tablicy ustawieñ.
 *
 * @param id  (int) ID kolumny
 * @param val (char*) wartoœæ
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
 * Ta funkcja powinna byæ u¿yta w #IM_INIT.
 * Parametrami s¹ @a p1 i @a p2 przes³ane razem z #IM_INIT
 */
int Plug_Init(int p1, int p2);

/** 
 * Ta funkcja powinna byæ u¿yta w #IM_DEINIT.
 * Parametrami s¹ @a p1 i @a p2 przes³ane razem z #IM_DEINIT
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
