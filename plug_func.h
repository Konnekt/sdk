/*
  nazwa="plug Functions"
  data="2002-11-01"
  ver="0.6.16.x"
  info="Zestaw makr i funkcji pomocniczych."
*/
#ifndef PLUGFUNCH
#define PLUGFUNCH

/**\file
  Zestaw makr i funkcji pomocniczych . <br><br>
  Musi by� include'owany po plug_export.h.  
*/

using ::Stamina::StringRef;
using ::Stamina::String;

/**
\addtogroup imi_action_
\{
*/

    /**\defgroup action_makra Funkcje pomocnicze.
     \{
    */

    /** Do wstawienia w switch'u akcji. Je�li akcja nie zosta�a wywo�ana z kodem ACTN_ACTION - wychodzi. */
    #define ACTIONONLY(notify) if (notify->code != ACTN_ACTION) return 0
    /** Pusta akcja. */
    #define NOACTION sUIAction(0,0)
    /** Sprawdza czy cCtrl::isRunning() zwraca true, je�li nie, wychodzi. */
    #define ISRUNNING() if (!Ctrl->isRunning()) {Ctrl->setError(IMERROR_SHUTDOWN); return 0;}

    /// Dodaje akcj�.
    /// \blank
    int UIActionAdd(int _parent , int _id , int _status=0 , const char * _txt = 0 , int _p1=0 , short _w=0 , short _h=0 , int _p2=0 , int _param=0);
    /// Wstawia akcj�.
    /// \blank
	inline int UIActionInsert(int _parent , int _id , int _pos , int _status=0 , const char * _txt = 0 , int _p1=0 , short _w=0 , short _h=0 , int _p2=0 , int _param=0);
    /// Dodaje akcj� do konfiguracji.
    /// \blank
    int UIActionCfgAdd(int _parent , int _id , int _status=0 , const char * _txt = 0 , int _p1=0 , short _x=0 , short _y=0 , short _w=0 , short _h=0 , int _p2=0 , int _param=0);
    /// Wstawia akcj� do konfiguracji.
    /// \blank
    int UIActionCfgInsert(int _parent , int _id , int _pos , int _status=0 , const char * _txt = 0 , int _p1=0 , short _x=0 , short _y=0 , short _w=0 , short _h=0 , int _p2=0 , int _param=0);


    /// Dodaje grup�.
    /// \blank
    int UIGroupAdd(int _parent , int _id , int _status=0 , const char * _txt = 0 , int _p1=0 , short _w=0 , short _h=0 , int _p2=0 , int _param=0);
    /// Wstawia grup�.
    /// \blank
    int UIGroupInsert(int _parent , int _id , int _pos , int _status=0 , const char * _txt = 0 , int _p1=0 , short _w=0 , short _h=0 , int _p2=0 , int _param=0);
    /// Zwraca pozycj� w grupie.
    /// \blank
    int UIActionGetPos(int _parent , int _id);

    /// Pobiera akcje.
    /// \blank
    int UIActionSet(sUIActionInfo & nfo);
    /// Ustawia akcje.
    /// \blank
    int UIActionGet(sUIActionInfo & nfo);


    /// Ustawia status.
    /// \blank
    int UIActionSetStatus(sUIAction act , int status , int mask = -1);
    /// \blank
    int UIActionGetStatus(sUIAction act);

	/// Zwraca uchwyt grupy
	void * UIGroupHandle(sUIAction act);
	/// Zwraca uchwyt akcji
	void * UIActionHandle(sUIAction act);
	/** Zwraca uchwyt akcji dla kontrolek z ACTR_SETCNT
	    W niekt�rych przypadkach pozwala na pobranie uchwytu
		bez zmieniania kontaktu przypisanego do akcji...
	*/
	void * UIActionHandleDirect(sUIAction act);
	int UIActionCall(sUIActionNotify_base * an);

    int UIActionSetStatus(int parent , int id , int status , int mask = -1);
    /// Ustawia text.
    /// \blank
    int UIActionSetText(sUIAction act , const char * txt);
    int UIActionSetText(int parent , int id , const char * txt);
    /// Ustawia wartosc kontrolki w konfiguracji.
    /// \blank
    int UIActionCfgSetValue(sUIAction act , const char * val , bool convert = true);
    /// Pobiera wartosc kontrolki z konfiguracji.
    /// \blank
    const char * UIActionCfgGetValue(sUIAction act , char * val , int size , bool convert = true);
    ///\}

	/** Dodaje standardowy zestaw akcji z boxem informacyjnym.
	 *
	 * \param parent Identyfikator akcji-rodzica
	 * \param title Tytu� boxa
	 * \param info Tre�� informacji (html)
	 * \param ico URL ikonki/obrazka
	 * \param height Wysoko�� tre�ci (Najlepiej poda� ujemn� liczb� wierszy przy minimalnej szeroko�ci...)
	 * \param icoWidth Szeroko�� ikonki (domy�lnie 32)
	 * \param icoHeight Wysoko�� ikonki (domy�lnie taka sama jak szeroko��)
	 */
	void UIActionCfgAddInfoBox(unsigned int parent, const char * title, const char * info, const char * ico, int height = 0, int icoWidth=0, int icoHeight=0);
	/** Dodaje standardowy zestaw akcji z boxem informacyjnym.
	 *
	 * \param parent Identyfikator akcji-rodzica
	 * \param title Tytu� boxa
	 * \param info Tre�� informacji (html)
	 * \param ico identyfikator ikonki na li�cie IML_16, lub IML_32
	 * \param height Wysoko�� tre�ci (Najlepiej poda� ujemn� liczb� wierszy przy minimalnej szeroko�ci...)
	 * \param icoSize Szeroko��/Wysoko�� ikonki (domy�lnie 32)
	 */
	void UIActionCfgAddInfoBox(unsigned int parent, const char * title, const char * info, unsigned int ico, int height = 0, int icoSize=32);

	/** Dodaje standardowy zestaw akcji z boxem opisuj�cym wtyczk�.
	 * \param parent Identyfikator akcji-rodzica
	 * \param info Tekst (html) z informacj� o wtyczce
	 * \param ico URL do ikonki
	 * \param height Wysoko�� tekstu. Najlepiej poda� ujemn� liczb� wierszy przy minimalnej szeroko�ci...
	 * \param name Nazwa wtyczki do wy�wietlenia. Je�eli pominiesz ten parametr, zar�wno nazwa jak i wersja zostan� pobrane automatycznie.
	 */
	void UIActionCfgAddPluginInfoBox(unsigned int parent, const char * info, const char * ico = 0, int height = 0, const char * name=0);

	/** Dodaje standardowy zestaw akcji z boxem opisuj�cym wtyczk� i przyciskiem z logiem i tipem z dodatkowymi informacjami.
	 * \param parent Identyfikator akcji-rodzica
	 * \param info Tekst (html) z informacj� o funkcjonalno�ci
	 * \param about_info Tekst (html) z dodatkowymi informacjami o wtyczce
	 * \param ico URL do ikonki
	 * \param height Wysoko�� tekstu. Najlepiej poda� ujemn� liczb� wierszy przy minimalnej szeroko�ci...
	 * \param name Nazwa wtyczki do wy�wietlenia. Je�eli pominiesz ten parametr, zar�wno nazwa jak i wersja zostan� pobrane automatycznie.
	 */
	void UIActionCfgAddPluginInfoBox2(unsigned int parent, const char * info, const char * about_info, const char * ico = 0, int height = 0, const char * name=0, bool frame = true);

/// \}   // imi_action

 /** @defgroup icon_makra Funkcje do ikonek
     @{
    */

    /** \brief \no */
    int IconRegister(IML_enum target , int ID , const char * URL);
    /** \brief \no */
    int IconRegister(IML_enum target , int ID , HINSTANCE inst , int icoID , int type = 1);
    /** \brief \no */
    int IconRegister(IML_enum target , int ID , HANDLE image, int type = 1);
    /** \brief \no */
    int IconRegisterList(IML_enum target , int count , int * IDList , HANDLE image , HANDLE mask=0 , int w = 0);
#ifdef _INC_COMMCTRL
    /** \brief \no */
    int IconRegisterList(IML_enum target , int count , int * IDList , HIMAGELIST ImageList);
#endif

 /** @} */

    /** \blank \no */
    bool GetExtParam(const char * ext , const char * name , char * valueBuff , size_t buffSize);
    /** \blank \no */
    bool SetExtParam(const char * ext , const char * name , const char * value , char * extBuff , size_t buffSize);
#ifdef _STRING_
    /** \blank \no */
    std::string GetExtParam(const std::string ext , const std::string name);
    /** \blank \no */
    std::string SetExtParam(const std::string ext , const std::string name , const std::string value);

    /** Zwraca warto�� parametr�w przekazywanych do kontrolek konfiguracji w sUIActionInfo::txt
	*/
    std::string GetActParam(const std::string & txt , const std::string & param);
    /** Ustawia warto�� parametr�w przekazywanych do kontrolek konfiguracji w sUIActionInfo::txt */
    std::string SetActParam(const std::string & txt , const std::string & param , const std::string & value);
    bool ActParamExists(const std::string & txt , const std::string & param);
	bool ParamSpecialChar(unsigned char ch);

#endif


    /** Ustawia status kontaktu. */
    int CntSetStatus(unsigned int cntID , unsigned int status , const char * info = 0);
    /** Powinno by� uruchomione zaraz przed zmian� statusu wtyczki. */
    int PlugStatusChange(unsigned int status , const char * info = 0);

	/** Zapisuje warto�� tekstow� kontaktu w tablicy, lub oknie "Wi�cej" w zale�no�ci od @a toWindow.
		Przydatne przy #IM_CNT_DOWNLOAD...
		@param toWindow (bool) czy ma zapisywa� do okna
	*/
	void CntSetInfoValue(bool toWindow , int cntID , int colID , const char * value);
	/** Pobiera warto�� tekstow� kontaktu w tablicy, lub oknie "Wi�cej" w zale�no�ci od @a fromWindow.
		Przydatne przy #IM_CNT_UPLOAD...
		@param fromWindow (bool) czy ma pobiera� z okna
	*/
	const char * CntGetInfoValue(bool fromWindow , int cntID , int colID);



/** Tworzy kolumn� w konfiguracji (@ref #IMC_SETCOL) */
int SetColumn(tTable table , int id , int type , int def , const char * name=0);
/** Tworzy kolumn� w konfiguracji (@ref #IMC_SETCOL) */
inline int SetColumn(tTable table , int id , int type , const char * def  , const char * name=0) {
	return SetColumn(table , id , type , (int)def , name);
}

/** Tworzy kopie cMessage. 
    Wykorzystywane, gdy po odebraniu np. #IM_MSG_SEND wysy�amy wiadomo��
    w osobnym w�tku. Tworzymy kopi� w IMessageProcess, a zwalniamy
    na ko�cu w�tku. F-cja alokuje ca�� struktur�!
*/
cMessage * messageDuplicate(cMessage * m);
/** Zwalnia cMessage (to co zaalokowa� messageDuplicate. */
void messageFree(cMessage * m, bool deleteObject = true);

void testResult(const StringRef& title, int should, int got, bool swap = false);
void testResult(const StringRef& title, const StringRef& should, const StringRef& got, bool swap = false);
inline void testResult(int should, int got, bool swap = false) {
	testResult("", should, got, swap);
}
inline void testResult(const StringRef& should, const StringRef& got, bool swap = false) {
	testResult("", should, got, swap);
}


/** Zamienia cztery parametry wersji w liczbe typu long. */
#define VERSION_TO_NUM(maj,min,rls,bld) ((((maj)&0xF)<<28) | (((min)&0xFF)<<20) | (((rls)&0xFF)<<12) | ((bld)&0xFFF))
#define VERSION_MAJ(ver) (((ver)>>28)&0xF)
#define VERSION_MIN(ver) (((ver)>>20)&0xFF)
#define VERSION_RLS(ver) (((ver)>>12)&0xFF)
#define VERSION_BLD(ver) ((ver)&0xFFF)

#endif