#pragma once

#include "core_unique.h"
#include "core_plugin.h"
#include "core_tables.h"

namespace Konnekt {
  /**
   * Klasa s�u��ca do komunikowania si� z "rdzeniem" systemu wtyczek.
   *
   * Adres tej struktury (zaalokowanej w rdzeniu) przekazywany jest
   * jako parametr w pierwszej wiadomosci do wtyczki - #IM_INIT ...<br>
   * Ka�da wtyczka posiada w�asn� kopi� Controler.
   *
   * @sa IMessageProc()
   */
  class Controler {
  public:
    virtual int __stdcall getLevel() = 0;     ///< Zwraca "poziom" dostepu do rdzenia. W 99% przypadk�w zwr�ci 1 ...
    virtual tPluginId __stdcall ID() = 0;     ///< Zwraca identyfikator wtyczki.
    virtual HINSTANCE __stdcall hInst() = 0;  ///< Zwraca uchwyt procesu (HINSTANCE).
    virtual HINSTANCE __stdcall hDll() = 0;   ///< Zwraca uchwyt biblioteki wtyczki.
  
    virtual enIMessageError __stdcall getError() = 0; ///< Zwraca kod ostatniego b��du.
    /**
     * Powinien byc ustawiony gdy wystapil blad przy ODBIORZE wiadomosci (np wiadomosc jest nieobslugiwana).
     * @sa IMessageProc() imerror_
     */
    virtual void __stdcall setError(enIMessageError err_code) = 0; ///< Ustawia kod b��du.
    /**
     * Zwraca 0 je�li program jest w trakcie zamykania.
     * �adne d�u�sze operacje nie powinny by� wykonywane. Cz�� IMessages
     * w innych modu�ach i tak nie zostanie wykonana...
     */
    virtual bool __stdcall isRunning() = 0;
    /**
     * Wysy�a wiadomo�� do wtyczek.
     * Aby przes�a� wiadomo�� do rdzenia lub ui jako \i net i \i type trzeba poda� 0
     *
     * @param msg Wiadomo�� do przes�ania
     * @sa im_ net_ imt_
     */
    virtual int __stdcall IMessage(sIMessage_base * msg) = 0;
    /**  
     * Wysy�a wiadomo�� bezpo�rednio do okre�lonej wtyczki.
     *
     * @param msg Wiadomo�� do przes�ania
     * @param plug ID wtyczki
     * @sa im_ imc_plug_
     */
    virtual int __stdcall IMessageDirect(tPluginId plug, sIMessage_base * msg) = 0;
    /** 
     * Zamienia (lub nie) identyfikator wiersza na jego numer.
     */
    virtual int __stdcall DTgetPos(tTable db, unsigned int row) = 0;
    /** 
     * Zamienia (lub nie) numer wiersza na jego identyfikator.
     */
    virtual int __stdcall DTgetID(tTable db, unsigned int row) = 0;
    virtual int __stdcall DTgetOld(tTable db, unsigned int row, unsigned int col) = 0;
    virtual int __stdcall DTsetOld(tTable db, unsigned int row, unsigned int col, int val, int mask = 0) = 0;
    /** 
     * Pobieta typ kolumny @a id.
     *
     * @param id Identyfikator kolumny
     *
     * @return typ kolumny
     * @sa @ref cfg dt_ct_
     */
    virtual int __stdcall DTgetType(tTable db, unsigned int id) = 0;
    /** 
     * Pobieta ilo�� wierszy w tablicy.
     *
     * @param db Identyfikator tablicy
     * @sa @ref cfg dt_ct_
     */
    virtual int __stdcall DTgetCount(tTable db) = 0;
    /** 
     * Pobieta identyfikator kolumny o podanej nazwie.
     *
     * @param db Identyfikator tablicy
     * @param name nazwa kolumny
     * @sa @ref cfg dt_ct_
     */
    virtual int __stdcall DTgetNameID(tTable db, const char * name) = 0;
  
    virtual unsigned int __stdcall Is_TUS(unsigned int thID) = 0; ///< Zwraca \a thID je�li aktualny w�tek jest r�ny od \a thID. Lub 0 gdy s� r�wne. Jako \a thID mo�na poda� 0 - zostanie zamienione na g��wny w�tek aplikacji.
    virtual int __stdcall RecallTS(HANDLE th = 0, bool wait = 1) = 0;
    virtual int __stdcall RecallIMTS(HANDLE th, bool wait, sIMessage_base * msg, tPluginId plugID) = 0;
  
    /**
     * Opr�nienie kolejki wiadomo�ci windowsowych.
     * Powinno by� wykonywane TYLKO w g��wnym w�tku, w d�ugich
     * blokuj�cych p�tlach (aby od�wie�y� wygl�d okien)
     */
    virtual void __stdcall WMProcess() = 0;
    /**
     * Zwraca wska�nik do bufora tymczasowego o rozmiarze @a size.
     * Bufor alokowany jest w kontek�cie wtyczki i w�tku.
     *
     * @attention Nie mo�na zwalnia� tej pami�ci!
     */
    virtual void * __stdcall GetTempBuffer(unsigned int size) = 0;
  
    /** 
     * Pobiera wartosc wiersza z tablicy danych z konwersj� typ�w.
     * Konwersja odbywa si� gdy Tables::Value::type jest r�ny od DT_CT_UNKNOWN.
     * W przeciwnym wypadku jako typ przyjmowany jest typ kolumny.
     * 
     * @param db Identyfikator tabeli
     * @param row Identyfikator/numer wiersza
     * @param col Identyfikator kolumny
     * @param value Struktura z warto�ci�
     * 
     * @return warto�� (lub adres do warto�ci je�li typ != DT_CT_INT)
     * @attention W #DTMSG mo�na zapisywa� tylko w okre�lonych okoliczno�ciach!
     */
    virtual bool __stdcall DTget(tTable db, unsigned int row, unsigned int col, Stamina::DT::OldValue * value) = 0;
    /** 
     * Ustawia wartosc wiersza z tablicy danych z konwersj� typ�w.
     * Konwersja odbywa si� gdy Tables::Value::type jest r�ny od DT_CT_UNKNOWN.
     * W przeciwnym wypadku jako typ przyjmowany jest typ kolumny.
     *
     * @param db Identyfikator tabeli
     * @param row Identyfikator/numer wiersza
     * @param col Identyfikator kolumny
     * @param value Struktura do kt�rej zostanie zapisana warto��.
     * @attention Do odczytu danych z #DTMSG przygotowane s� inne funkcje!
     */
    virtual bool __stdcall DTset(tTable db, unsigned int row, unsigned int col, Stamina::DT::OldValue * value) = 0;
    /** 
     * Blokuje dost�p do wiersza w tablicy dla innych w�tk�w. Zaraz po
     * wykorzystaniu zabezpieczonych danych trzeba wywo�a� Controler::DTunlock z tymi
     * samymi parametrami!
     *
     * @param db Identyfikator tabeli
     * @param row Identyfikator/numer wiersza, lub -1 je�li chcemy zablokowa� CA�� tablic�
     * @param reserved Zarezerwowane na p�niej, musi by� r�wne 0.
     * 
     * @return Ilo�� wcze�niej za�o�onych blokad.
     */
    virtual unsigned short __stdcall DTlock(tTable db, unsigned int row, int reserved = 0) = 0;
    /** 
     * Odblokowuje dost�p do wiersza w tablicy dla innych w�tk�w,
     * zastrze�ony wcze�niej przy u�yciu cCtrk::DTlock.
     * 
     * @param db Identyfikator tabeli
     * @param row Identyfikator/numer wiersza, lub -1 je�li chcemy zablokowa� CA�� tablic�
     * @param reserved Zarezerwowane na p�niej, musi by� r�wne 0.
     * 
     * @return Ilo�� pozosta�ych blokad.
     * @attention Po wykonaniu tej funkcji, wszystkie zwr�cone wska�niki
     * bezpo�rednie mog� by� ju� nieaktualne!
     */
    virtual unsigned short __stdcall DTunlock(tTable db, unsigned int row, int reserved = 0) = 0;
    /** 
     * Wszystkie bufory wrzucane do API, �eby mog�by by� zwolnione
     * w innym module musz� by� zaalokowane poni�sz� funkcj�. 
     */
    virtual void * __stdcall malloc(size_t size) = 0; 
    /** 
     * Wszystkie bufory tekstowe wrzucane do API, �eby mog�by by� zwolnione
     * w innym module musz� by� zaalokowane poni�sz� funkcj�. 
     */
    virtual char * __stdcall strdup(const char * str) = 0;
    /** 
     * Wszystkie bufory zaalokowane przez Controler::malloc i Controler::strdup
     * powinny by� zwolnione t� funkcj�. 
     */
    virtual void __stdcall free(void * buff) = 0;
  
    /** 
     * U�ywanie zwyk�ego Sleep w g��wnym w�tku najpr�dzej doprowadzi
     * K do stanu chwilowej nieu�ywalno�ci, bardzo mo�liwe r�wnie�,
     * �e nast�pi zupe�ny DeadLock.
     * Zamiast tego mo�na u�ywa� tej funkcji, kt�ra po prostu zamiast Sleep
     * wywo�uje MsgWaitForMultipleObjectsEx. Nie jest wi�c gwarantowane, 
     * �e podany czas w og�le minie. Trzeba pami�ta� te�, �e nie jest gwarantowane,
     * �e aktualny w�tek nie wykona gdzie� po drodze innego kodu w wyniku
     * wywo�ania f-cji APC, timer'a czy windowsowej wiadomo�ci...
     * Podczas zamykania (w IM_END) nie powinny by� wywo�ywane procedury APC ani
     * prze��czanie w�tk�w...
     * Generalnie, je�eli musisz czeka� na co� w g��wnym w�tku, u�ywaj
     * MsgWaitForMultipleObjectsEx w po��czeniu z Ctrl->WMProcess, kt�re
     * przegl�da kolejk� oczekuj�cych wiadomo�ci w aktualnym w�tku.
     */
    virtual int __stdcall Sleep(unsigned int time) = 0;
  
    typedef unsigned int ( __stdcall * fBeginThread)( void * );
  
    /**
     * BeginThread dzia�a identycznie jak _beginthreadex z wyj�tkiem
     * tego, �e w trybie debug potrafi wychwytywa� b��dy w w�tku
     * i je raportowa�... U�ywanie wysoko zalecane!
     *
     * @warn Funkcja zwraca uchwyt w�tku! Nale�y go zamkn�� przy pomocy CloseHandle()!!!
     */
    virtual HANDLE __stdcall BeginThreadOld(void *security,
      unsigned stack_size,
      fBeginThread start_address,
      void *arglist = 0,
      unsigned initflag = 0,
      unsigned *thrdaddr = 0
      ) = 0;
    /** 
     * Tworzy w�tek i czeka a� si� sko�czy.
     * Parametry te same co w Controler::BeginThread()
     */
    int BeginThreadAndWait(const char * name, void *security, unsigned stack_size, fBeginThread start_address, void *arglist = 0, unsigned initflag = 0, unsigned *thrdaddr = 0);
  
    /** Pobiera poziom debugowania dla wtyczki */
    virtual unsigned int __stdcall DebugLevel(enDebugLevel level = DBG_ALL) = 0;
  
    /** 
     * Podaje, czy Konnekt jest zamykany w trybie natychmiastowym (np. podczas zamykania systemu).
     * Wtyczki nie powinny w tym czasie wykonywa� d�ugich operacji, prze��cza� w�tk�w (#IMESSAGE_TS),
     * ani przetwarza� procedur APC (flaga Alertable w funkcjach oczekuj�cych WinApi).
     */
    virtual bool __stdcall QuickShutdown() = 0;
  
    /** 
     * Ustawia poziom debugowania wtyczki.
     */
    virtual unsigned int __stdcall SetDebugLevel(enDebugLevel levelMask, enDebugLevel level = DBG_ALL) = 0;
  
    /** 
     * Pobiera nazwe kolumny o podanym identyfikatorze.
     *
     * @param db Identyfikator tablicy
     * @param col Identyfikator kolumny
     * @sa @ref cfg dt_ct_
     */
    virtual const char * __stdcall DTgetName(tTable db, unsigned int col) = 0;

    virtual Unique::tId __stdcall getId(Unique::tDomainId domainId, const char * name) = 0;
    virtual const char * __stdcall getName(Unique::tDomainId domainId, Unique::tId id) = 0;
    Unique::tDomainId getDomainId(const char * name) {return (Unique::tDomainId) this->getId(Unique::domainDomain, name);}
    Unique::tRangeId getRangeId(const char * name) {return (Unique::tRangeId) this->getId(Unique::domainRange, name);}
    virtual bool __stdcall idInRange(Unique::tDomainId domainId, Unique::tRangeId rangeId, Unique::tId id) = 0;
    virtual Unique::tRangeId __stdcall idInRange(Unique::tDomainId domainId, Unique::tId id, Unique::iRange::enType check = Unique::iRange::typeBoth) = 0;

    virtual Tables::oTable __stdcall getTable(Tables::tTableId tableId) = 0;

    /** 
     * Zwraca obiekt wtyczki.
     *
     * @param pluginId Identyfikator, indeks, lub pluginNotFound je�eli chcemy uzyska� obiekt przypisany do Controler.
     */
    virtual Konnekt::oPlugin __stdcall getPlugin(Konnekt::tPluginId pluginId = pluginNotFound) = 0;

    virtual HANDLE __stdcall BeginThread(const char* name, void *security,
      unsigned stack_size,
      fBeginThread start_address,
      void *arglist = 0,
      unsigned initflag = 0,
      unsigned *thrdaddr = 0
      ) = 0;

    /** 
     * Nadaje nazw� wykonywanemu w�tkowi, inicjalizuje bufory tymczasowe i dodaje do listy kontrolowanych w�tk�w (kt�re zostan� np. zatrzymane w chwili wyst�pienia b��du krytycznego).
     *
     * @warning Musi by� wywo�ane Z poziomu w�tku!
     * @notice Funkcja ta wywo�ywana jest automatycznie zaraz po utworzeniu w�tku.
     */
    virtual void __stdcall onThreadStart(const char* name = 0) = 0;
    /** 
     * Zwalnia bufory tymczasowe i usuwa z listy kontrolowanych w�tk�w.
     *
     * @warning Musi by� wywo�ane Z poziomu w�tku!
     * @notice Funkcja ta wywo�ywana jest automatycznie zaraz przed zako�czeniem w�tku.
     */
    virtual void __stdcall onThreadEnd() = 0;

    virtual unsigned int __stdcall getPluginsCount() = 0;

    /** 
     * Zwraca obiekt loguj�cy przypisany do wtyczki (Stamina::Logger)
     */
    virtual class Stamina::Logger* __stdcall getLogger() = 0;

    /** 
     * Loguje tre�� 
     *
     * @param level Rodzaj logowanego komunikatu
     * @param module Dowolna tre�� okre�laj�ca logiczny modu� wtyczki, lub NULL. Nie trzeba podawa� nazwy wtyczki.
     * @param where Dowolna tre�� okre�laj�ca miejsce zdarzenia, lub NULL
     * @param msg Tre�� do zapisania
     * 
     * Parametry module i where s�u�� tylko i wy��cznie czytelno�ci log�w. Najlepiej okre�la� logowane tre�ci w jednolity spos�b. Np. informacj� o obs�u�eniu komunikatu IM_CONNECT mo�na zapisa� jako:
     * @code
     * Ctrl->log(logFunc, "IMessage", "Connect", "Connected");
     * @endcode
     * 
     * Istnieje osobna f-cja do tworzenia tre�ci fomatowanych Ctrl::log().
     * Bardziej zaawansowane mo�liwo�ci daje obiekt typu Stamina::Logger, kt�ry mo�na otrzyma� z f-cji Ctrl::getLogger(). 
     */
    virtual void __stdcall logMsg(enDebugLevel level, const char* module, const char* where, const char* msg) = 0;

    // --------------

    // funkcje lokalne, dla ulatwienia
    int DTgetInt(tTable db, unsigned int row, unsigned int col);
    bool DTsetInt(tTable db, unsigned int row, unsigned int col, int value, int mask = -1);
    char * DTgetStr(tTable db, unsigned int row, unsigned int col, char * buff = 0, unsigned int size = 0);
    bool DTsetStr(tTable db, unsigned int row, unsigned int col, const char * value);
    __int64 DTgetInt64(tTable db, unsigned int row, unsigned int col);
    bool DTsetInt64(tTable db, unsigned int row, unsigned int col, __int64 value, __int64 mask = -1);

    int DTgetInt(tTable db, unsigned int row, const char * name);
    bool DTsetInt(tTable db, unsigned int row, const char * name, int value, int mask = -1);
    char * DTgetStr(tTable db, unsigned int row, const char * name, char * buff = 0, unsigned int size = 0);
    bool DTsetStr(tTable db, unsigned int row, const char * name, const char * value);
    __int64 DTgetInt64(tTable db, unsigned int row, const char * name);
    bool DTsetInt64(tTable db, unsigned int row, const char * name, __int64 value, __int64 mask = -1);


    /** 
     * Zapisuje sfromatowan� informacj� do pliku konnekt.log (i ew. wy�wietla j� w oknie @Dev)
     */
    void IMLOG(const char *format, ...);
    /** 
     * Loguje, je�eli wtyczka ma w��czone logowanie na danym "poziomie" 
     */
    void IMDEBUG(enDebugLevel level, const char *format, ...);

    void log(enDebugLevel level, const char* module, const char* where, const char *format, ...);
    void logV(enDebugLevel level, const char* module, const char* where, const char *format, va_list p);

    // ----
    int IMessage(unsigned int  id, tNet net = Net::none, enIMessageType type = imtAll, int p1 = 0, int p2 = 0);
    int ICMessage(unsigned int  id, int p1 = 0, int p2 = 0);
    int IMessageDirect(unsigned int  id, tPluginId plug, int p1 = 0, int p2 = 0);

    int UIActionInsert(int _parent, int _id, int _pos, int _status = 0, const char * _txt = 0, int _p1 = 0, short _w = 0, short _h = 0, int _p2 = 0, int _param = 0);

    int SetColumn(tTable table, int id, int type, int def, const char * name);
    inline int SetColumn(tTable table, int id, int type, const char * def , const char * name = 0) {
      return this->SetColumn(table, id, type, (int) def, name);
    }

    inline operator oPlugin () {
      return this->getPlugin();
    }
  };

  typedef Controler cCtrl;
};