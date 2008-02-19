#pragma once

#include "core_unique.h"
#include "core_plugin.h"
#include "core_tables.h"

namespace Konnekt {
  /**
   * Klasa s³u¿¹ca do komunikowania siê z "rdzeniem" systemu wtyczek.
   *
   * Adres tej struktury (zaalokowanej w rdzeniu) przekazywany jest
   * jako parametr w pierwszej wiadomosci do wtyczki - #IM_INIT ...<br>
   * Ka¿da wtyczka posiada w³asn¹ kopiê Controler.
   *
   * @sa IMessageProc()
   */
  class Controler {
  public:
    virtual int __stdcall getLevel() = 0;     ///< Zwraca "poziom" dostepu do rdzenia. W 99% przypadków zwróci 1 ...
    virtual tPluginId __stdcall ID() = 0;     ///< Zwraca identyfikator wtyczki.
    virtual HINSTANCE __stdcall hInst() = 0;  ///< Zwraca uchwyt procesu (HINSTANCE).
    virtual HINSTANCE __stdcall hDll() = 0;   ///< Zwraca uchwyt biblioteki wtyczki.
  
    virtual enIMessageError __stdcall getError() = 0; ///< Zwraca kod ostatniego b³êdu.
    /**
     * Powinien byc ustawiony gdy wystapil blad przy ODBIORZE wiadomosci (np wiadomosc jest nieobslugiwana).
     * @sa IMessageProc() imerror_
     */
    virtual void __stdcall setError(enIMessageError err_code) = 0; ///< Ustawia kod b³êdu.
    /**
     * Zwraca 0 jeœli program jest w trakcie zamykania.
     * ¯adne d³u¿sze operacje nie powinny byæ wykonywane. Czêœæ IMessages
     * w innych modu³ach i tak nie zostanie wykonana...
     */
    virtual bool __stdcall isRunning() = 0;
    /**
     * Wysy³a wiadomoœæ do wtyczek.
     * Aby przes³aæ wiadomoœæ do rdzenia lub ui jako \i net i \i type trzeba podaæ 0
     *
     * @param msg Wiadomoœæ do przes³ania
     * @sa im_ net_ imt_
     */
    virtual int __stdcall IMessage(sIMessage_base * msg) = 0;
    /**  
     * Wysy³a wiadomoœæ bezpoœrednio do okreœlonej wtyczki.
     *
     * @param msg Wiadomoœæ do przes³ania
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
     * Pobieta iloœæ wierszy w tablicy.
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
  
    virtual unsigned int __stdcall Is_TUS(unsigned int thID) = 0; ///< Zwraca \a thID jeœli aktualny w¹tek jest ró¿ny od \a thID. Lub 0 gdy s¹ równe. Jako \a thID mo¿na podaæ 0 - zostanie zamienione na g³ówny w¹tek aplikacji.
    virtual int __stdcall RecallTS(HANDLE th = 0, bool wait = 1) = 0;
    virtual int __stdcall RecallIMTS(HANDLE th, bool wait, sIMessage_base * msg, tPluginId plugID) = 0;
  
    /**
     * Opró¿nienie kolejki wiadomoœci windowsowych.
     * Powinno byæ wykonywane TYLKO w g³ównym w¹tku, w d³ugich
     * blokuj¹cych pêtlach (aby odœwie¿yæ wygl¹d okien)
     */
    virtual void __stdcall WMProcess() = 0;
    /**
     * Zwraca wskaŸnik do bufora tymczasowego o rozmiarze @a size.
     * Bufor alokowany jest w kontekœcie wtyczki i w¹tku.
     *
     * @attention Nie mo¿na zwalniaæ tej pamiêci!
     */
    virtual void * __stdcall GetTempBuffer(unsigned int size) = 0;
  
    /** 
     * Pobiera wartosc wiersza z tablicy danych z konwersj¹ typów.
     * Konwersja odbywa siê gdy Tables::Value::type jest ró¿ny od DT_CT_UNKNOWN.
     * W przeciwnym wypadku jako typ przyjmowany jest typ kolumny.
     * 
     * @param db Identyfikator tabeli
     * @param row Identyfikator/numer wiersza
     * @param col Identyfikator kolumny
     * @param value Struktura z wartoœci¹
     * 
     * @return wartoœæ (lub adres do wartoœci jeœli typ != DT_CT_INT)
     * @attention W #DTMSG mo¿na zapisywaæ tylko w okreœlonych okolicznoœciach!
     */
    virtual bool __stdcall DTget(tTable db, unsigned int row, unsigned int col, Stamina::DT::OldValue * value) = 0;
    /** 
     * Ustawia wartosc wiersza z tablicy danych z konwersj¹ typów.
     * Konwersja odbywa siê gdy Tables::Value::type jest ró¿ny od DT_CT_UNKNOWN.
     * W przeciwnym wypadku jako typ przyjmowany jest typ kolumny.
     *
     * @param db Identyfikator tabeli
     * @param row Identyfikator/numer wiersza
     * @param col Identyfikator kolumny
     * @param value Struktura do której zostanie zapisana wartoœæ.
     * @attention Do odczytu danych z #DTMSG przygotowane s¹ inne funkcje!
     */
    virtual bool __stdcall DTset(tTable db, unsigned int row, unsigned int col, Stamina::DT::OldValue * value) = 0;
    /** 
     * Blokuje dostêp do wiersza w tablicy dla innych w¹tków. Zaraz po
     * wykorzystaniu zabezpieczonych danych trzeba wywo³aæ Controler::DTunlock z tymi
     * samymi parametrami!
     *
     * @param db Identyfikator tabeli
     * @param row Identyfikator/numer wiersza, lub -1 jeœli chcemy zablokowaæ CA£¥ tablicê
     * @param reserved Zarezerwowane na póŸniej, musi byæ równe 0.
     * 
     * @return Iloœæ wczeœniej za³o¿onych blokad.
     */
    virtual unsigned short __stdcall DTlock(tTable db, unsigned int row, int reserved = 0) = 0;
    /** 
     * Odblokowuje dostêp do wiersza w tablicy dla innych w¹tków,
     * zastrze¿ony wczeœniej przy u¿yciu cCtrk::DTlock.
     * 
     * @param db Identyfikator tabeli
     * @param row Identyfikator/numer wiersza, lub -1 jeœli chcemy zablokowaæ CA£¥ tablicê
     * @param reserved Zarezerwowane na póŸniej, musi byæ równe 0.
     * 
     * @return Iloœæ pozosta³ych blokad.
     * @attention Po wykonaniu tej funkcji, wszystkie zwrócone wskaŸniki
     * bezpoœrednie mog¹ byæ ju¿ nieaktualne!
     */
    virtual unsigned short __stdcall DTunlock(tTable db, unsigned int row, int reserved = 0) = 0;
    /** 
     * Wszystkie bufory wrzucane do API, ¿eby mog³by byæ zwolnione
     * w innym module musz¹ byæ zaalokowane poni¿sz¹ funkcj¹. 
     */
    virtual void * __stdcall malloc(size_t size) = 0; 
    /** 
     * Wszystkie bufory tekstowe wrzucane do API, ¿eby mog³by byæ zwolnione
     * w innym module musz¹ byæ zaalokowane poni¿sz¹ funkcj¹. 
     */
    virtual char * __stdcall strdup(const char * str) = 0;
    /** 
     * Wszystkie bufory zaalokowane przez Controler::malloc i Controler::strdup
     * powinny byæ zwolnione t¹ funkcj¹. 
     */
    virtual void __stdcall free(void * buff) = 0;
  
    /** 
     * U¿ywanie zwyk³ego Sleep w g³ównym w¹tku najprêdzej doprowadzi
     * K do stanu chwilowej nieu¿ywalnoœci, bardzo mo¿liwe równie¿,
     * ¿e nast¹pi zupe³ny DeadLock.
     * Zamiast tego mo¿na u¿ywaæ tej funkcji, która po prostu zamiast Sleep
     * wywo³uje MsgWaitForMultipleObjectsEx. Nie jest wiêc gwarantowane, 
     * ¿e podany czas w ogóle minie. Trzeba pamiêtaæ te¿, ¿e nie jest gwarantowane,
     * ¿e aktualny w¹tek nie wykona gdzieœ po drodze innego kodu w wyniku
     * wywo³ania f-cji APC, timer'a czy windowsowej wiadomoœci...
     * Podczas zamykania (w IM_END) nie powinny byæ wywo³ywane procedury APC ani
     * prze³¹czanie w¹tków...
     * Generalnie, je¿eli musisz czekaæ na coœ w g³ównym w¹tku, u¿ywaj
     * MsgWaitForMultipleObjectsEx w po³¹czeniu z Ctrl->WMProcess, które
     * przegl¹da kolejkê oczekuj¹cych wiadomoœci w aktualnym w¹tku.
     */
    virtual int __stdcall Sleep(unsigned int time) = 0;
  
    typedef unsigned int ( __stdcall * fBeginThread)( void * );
  
    /**
     * BeginThread dzia³a identycznie jak _beginthreadex z wyj¹tkiem
     * tego, ¿e w trybie debug potrafi wychwytywaæ b³êdy w w¹tku
     * i je raportowaæ... U¿ywanie wysoko zalecane!
     *
     * @warn Funkcja zwraca uchwyt w¹tku! Nale¿y go zamkn¹æ przy pomocy CloseHandle()!!!
     */
    virtual HANDLE __stdcall BeginThreadOld(void *security,
      unsigned stack_size,
      fBeginThread start_address,
      void *arglist = 0,
      unsigned initflag = 0,
      unsigned *thrdaddr = 0
      ) = 0;
    /** 
     * Tworzy w¹tek i czeka a¿ siê skoñczy.
     * Parametry te same co w Controler::BeginThread()
     */
    int BeginThreadAndWait(const char * name, void *security, unsigned stack_size, fBeginThread start_address, void *arglist = 0, unsigned initflag = 0, unsigned *thrdaddr = 0);
  
    /** Pobiera poziom debugowania dla wtyczki */
    virtual unsigned int __stdcall DebugLevel(enDebugLevel level = DBG_ALL) = 0;
  
    /** 
     * Podaje, czy Konnekt jest zamykany w trybie natychmiastowym (np. podczas zamykania systemu).
     * Wtyczki nie powinny w tym czasie wykonywaæ d³ugich operacji, prze³¹czaæ w¹tków (#IMESSAGE_TS),
     * ani przetwarzaæ procedur APC (flaga Alertable w funkcjach oczekuj¹cych WinApi).
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
     * @param pluginId Identyfikator, indeks, lub pluginNotFound je¿eli chcemy uzyskaæ obiekt przypisany do Controler.
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
     * Nadaje nazwê wykonywanemu w¹tkowi, inicjalizuje bufory tymczasowe i dodaje do listy kontrolowanych w¹tków (które zostan¹ np. zatrzymane w chwili wyst¹pienia b³êdu krytycznego).
     *
     * @warning Musi byæ wywo³ane Z poziomu w¹tku!
     * @notice Funkcja ta wywo³ywana jest automatycznie zaraz po utworzeniu w¹tku.
     */
    virtual void __stdcall onThreadStart(const char* name = 0) = 0;
    /** 
     * Zwalnia bufory tymczasowe i usuwa z listy kontrolowanych w¹tków.
     *
     * @warning Musi byæ wywo³ane Z poziomu w¹tku!
     * @notice Funkcja ta wywo³ywana jest automatycznie zaraz przed zakoñczeniem w¹tku.
     */
    virtual void __stdcall onThreadEnd() = 0;

    virtual unsigned int __stdcall getPluginsCount() = 0;

    /** 
     * Zwraca obiekt loguj¹cy przypisany do wtyczki (Stamina::Logger)
     */
    virtual class Stamina::Logger* __stdcall getLogger() = 0;

    /** 
     * Loguje treœæ 
     *
     * @param level Rodzaj logowanego komunikatu
     * @param module Dowolna treœæ okreœlaj¹ca logiczny modu³ wtyczki, lub NULL. Nie trzeba podawaæ nazwy wtyczki.
     * @param where Dowolna treœæ okreœlaj¹ca miejsce zdarzenia, lub NULL
     * @param msg Treœæ do zapisania
     * 
     * Parametry module i where s³u¿¹ tylko i wy³¹cznie czytelnoœci logów. Najlepiej okreœlaæ logowane treœci w jednolity sposób. Np. informacjê o obs³u¿eniu komunikatu IM_CONNECT mo¿na zapisaæ jako:
     * @code
     * Ctrl->log(logFunc, "IMessage", "Connect", "Connected");
     * @endcode
     * 
     * Istnieje osobna f-cja do tworzenia treœci fomatowanych Ctrl::log().
     * Bardziej zaawansowane mo¿liwoœci daje obiekt typu Stamina::Logger, który mo¿na otrzymaæ z f-cji Ctrl::getLogger(). 
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
     * Zapisuje sfromatowan¹ informacjê do pliku konnekt.log (i ew. wyœwietla j¹ w oknie @Dev)
     */
    void IMLOG(const char *format, ...);
    /** 
     * Loguje, je¿eli wtyczka ma w³¹czone logowanie na danym "poziomie" 
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