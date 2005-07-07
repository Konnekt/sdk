#pragma once

#include "core_object.h"
#include "core_unique.h"
#include "core_plugin.h"

#include <Stamina/DataTable.h>

#define DTCFG Konnekt::Tables::tableConfig
#define DTCNT Konnekt::Tables::tableContacts
#define DTMSG Konnekt::Tables::tableMessages
#define DTNONE Konnekt::Tables::tableNotFound


namespace Konnekt { namespace Tables {

	enum enTableId {
		tableConfig = 0,
		tableContacts = 1,
		tableMessages = 2,
		tableByName = -1,

		dtCfg = 0,
		dtCnt = 1,
		dtMsg = 2,

		tableNotFound = -1
	};
	enum enColumnType {
		ctypeInt = DT_CT_INT,
		ctypeString = DT_CT_PCHAR,
		ctypeInt64 = DT_CT_64,
		ctype64 = DT_CT_64,
		ctypeUnknown = DT_CT_UNKNOWN,
	};
	enum enColumnFlag {
		ctypeMask = 0xFF,
		cflagDontSave = DT_CF_NOSAVE,
		cflagNoSave = DT_CF_NOSAVE,
		cflagSecret = DT_CF_SECRET,
		cflagXor = DT_CF_CXOR,
	};
	inline enColumnType operator | (const enColumnType & a, const enColumnFlag & b) {
		return (enColumnType) ((int)a | (int)b); 
	}

	typedef enTableId tTableId;
	typedef unsigned int tColId;
	typedef enColumnType tColType;
	typedef unsigned int tRowId;

//#ifndef _DTABLE_
    #pragma pack(push, 1)

    struct Value {
		short type; ///< Typ przekazywanej wartoœci
        union {
            struct {
                union {
                    char * vChar;
                    const char * vCChar;
                };
                unsigned int buffSize;
            };
            int vInt;
            __int64 vInt64;
        };
		Value(tColType type=ctypeUnknown):type(type) {vInt64 = 0;buffSize=0;}
		Value(char type):type((tColType)type) {vInt64 = 0;buffSize=0;}

		struct sDTValue* dtRef() {
			return (sDTValue*)this;
		}

    };

    #pragma pack(pop)

//#else
//	typedef sDTValue Value;
//#endif  // _DTABLE_

	inline Value ValueStr(const char* value, int buffSize=0) {
		Value v(ctypeString);
		v.vCChar = value;
		v.buffSize = buffSize;
		return v;
	}
	inline Value ValueInt(int value) {
		Value v(ctypeInt);
		v.vInt = value;
		return v;
	}
	inline Value ValueInt64(__int64 value) {
		Value v(ctypeInt64);
		v.vInt64 = value;
		return v;
	}


	const tRowId rowNotFound = -1;
	const tRowId allRows = -1;
	const tColId colNotFound = -1;
	const tColId colByName = -1;
	//const tRowId rowIdMask = DT_ROWID_MASK;


	enum enTableOptions {
        optAutoSave = 1,
		optPrivate = 2,
		optBroadcastEvents = 4, 
		optUsePassword = 8,
		/** Dane dotycz¹ wszystkich profili konnekta i bêd¹ przechowywane w katalogu %KonnektData% */
		optGlobalData = 0x10,          
		/** Nie wczytuje nie zarejestrowanych kolumn.
		Standardowo ³adowane s¹ wszystkie kolumny, co umo¿liwia przechowywanie danych
		zapisanych przez wtyczki, które póŸniej zosta³y wy³¹czone i nie mog³y zarejestrowaæ swoich kolumn.
		*/
		optDiscardLoadedColumns = 0x20,
		/** Po zmianie g³ównego has³a profilu ta tablica zostanie równie¿ zaktualizowana  */
		optUseCurrentPassword = 0x48,
		optAutoLoad = 0x80,

		optDefaultSet = optBroadcastEvents | optUseCurrentPassword,
	};


	class iTable: public Stamina::iSharedObject {
	public:

		STAMINA_OBJECT_CLASS(Konnekt::Tables::iTable, Stamina::iSharedObject);

		 virtual ~iTable() {};

         /** Zamienia (lub nie) identyfikator na numer wiersza.*/
         virtual int __stdcall getRowPos(tRowId rowId)=0;
         /** Zamienia (lub nie) numer wiersza na jego identyfikator.*/
         virtual int __stdcall getRowId(unsigned int rowPos)=0;

		 /** Znajduje wiersz spe³niaj¹cy podane kryteria.
		 @param startPos - numer wiersza od którego zaczynamy szukanie
		 @param argCount - liczba przekazywanych struktur Find*, lub -1 je¿eli ostatnie kryterium jest równe 0
		 @param ... - kolejne kryteria jako struktury Find*, najbezpieczniej dodaæ na koñcu kryterium 0

		 np. Znajduje pierwszy kontakt sieci NET_GG aktywny w ci¹gu ostatniej minuty.
		 dt->findRow(0, -1, &Find::EqInt(CNT_NET, NET_GG), &Find(Find::gt, CNT_ACTIVITY, ValueInt64(_time64(0) - 60000)), 0);
		 */
         virtual tRowId __cdecl findRow(unsigned int startPos, int argCount, ...)=0;

		 inline tRowId findRow(unsigned int startPos, Stamina::DT::Find& f1) {
			 return this->findRow(startPos, 1, &f1);
		 }
		 inline tRowId findRow(unsigned int startPos, Stamina::DT::Find& f1, Stamina::DT::Find& f2) {
			 return this->findRow(startPos, 2, &f1, &f2);
		 }
		 inline tRowId findRow(unsigned int startPos, Stamina::DT::Find& f1, Stamina::DT::Find& f2, Stamina::DT::Find& f3) {
			 return this->findRow(startPos, 3, &f1, &f2, &f3);
		 }

		 /** Zwraca typ i flagi kolumny.
		 ¯eby uzyskaæ sam typ kolumny trzeba pozbyæ siê flag:
		 @code
		 tColType type = table->getColType(CNT_UID) | ctypeMask;
		 @endcode
		 */
		 virtual tColType __stdcall getColType(tColId colId)=0;
         /** Zwraca iloœæ wierszy w tablicy.*/
         virtual unsigned int __stdcall getRowCount()=0;
		 int getCount() {
			 return this->getRowCount();
		 }
         /** Zwraca identyfikator kolumny o podanej nazwie.
         @param name nazwa kolumny
		 @return Identyfikator lub colNotFound.
         */
         virtual tColId __stdcall getColId(const char * colName)=0;
         /** Pobiera nazwê kolumny o podanym identyfikatorze.
         @param colId Identyfikator kolumny
		 @return Zarejestrowana nazwa kolumny, lub ""
         */
         virtual const char * __stdcall getColName(tColId colId)=0;

		 /** Zwraca liczbê kolumn */
		 virtual unsigned int __stdcall getColCount()=0;
		 /** Zwraca identyfikator kolumny na wskazanej pozycji lub colNotFound */
		 virtual tColId __stdcall getColIdByPos(unsigned int colPos)=0;

         /** Pobiera wartoœæ wiersza z konwersj¹ typów.
         Konwersja odbywa siê gdy Value::type jest ró¿ny od ctypeUnknown. 
		 W przeciwnym wypadku jako typ przyjmowany jest typ kolumny.
         @param rowId Identyfikator/numer wiersza
         @param colId Identyfikator kolumny
         @param value Struktura do której zostanie wpisana wartoœæ
         @return true je¿eli siê powiod³o

		 Zobacz gotowe funkcje dla poszczególnych typów jak Table::getInt().
		 */
         virtual bool __stdcall get(tRowId rowId , tColId colId , Value & value)=0;
         /** Ustawia wartoœæ wiersza z konwersj¹ typów.
         Konwersja odbywa siê gdy Value::type jest ró¿ny od ctypeUnknown. 
		 W przeciwnym wypadku przyjmowany jest typ kolumny.
         @param rowId Identyfikator/numer wiersza
         @param colId Identyfikator kolumny
         @param value Struktura do której zostanie zapisana wartoœæ.
         @return true je¿eli siê powiod³o
		 
		 Zobacz gotowe funkcje dla poszczególnych typów jak Table::setInt().
         */
         virtual bool __stdcall set(tRowId rowId , tColId colId , Value & value)=0;
         /** Blokuje dostêp do wiersza dla innych w¹tków. 
		 Zaraz po wykorzystaniu zabezpieczonych danych trzeba wywo³aæ unlockData() z tymi samymi parametrami!
         @param rowId Identyfikator/numer wiersza, lub allRows jeœli chcemy zablokowaæ WSZYSTKIE dane
         @param reserved Zarezerwowane na póŸniej, musi byæ równe 0.
         @return Iloœæ wczeœniej za³o¿onych blokad.
         */
         virtual unsigned short __stdcall lockData(tRowId rowId , int reserved=0)=0;
         /** Odblokowuje dostêp do wiersza dla innych w¹tków, zastrze¿ony wczeœniej przy u¿yciu lockData().
         @param rowId Identyfikator/numer wiersza, lub allRows jeœli chcemy dblokowaæ WSZYSTKIE dane
         @param reserved Zarezerwowane na póŸniej, musi byæ równe 0.
         @return Iloœæ pozosta³ych blokad.
         @attention Po wykonaniu tej funkcji, wszystkie zwrócone wskaŸniki bezpoœrednie mog¹ byæ ju¿ nieaktualne!
         */
         virtual unsigned short __stdcall unlockData(tRowId rowId , int reserved=0)=0;



		 /** Rejestruje kolumnê w tablicy.
		 Kolumny mo¿na dodawaæ dopóki tablica jest pusta, lub nie zosta³a za³adowana z pliku.	
		 @param obiekt wtyczki rejestruj¹cej - cCtrl::getPlugin()
		 @param colId Identyfikator rejestrowanej kolumny, lub colByName je¿eli chcemy odnosiæ siê do niej tylko po nazwie
		 @param type Typ wartoœci kolumny z flagami (enColumnType | enColumnFlag)
		 @param def Wartoœæ domyœlna
		 @param name Nazwa kolumny. Idnetyfikator kolumny zarejestrowanej tylko po nazwie mo¿na zdobyæ przy pomocy getColId().
		 @return Identyfikator zarejestrowanej kolumny
		 */
		 virtual tColId __stdcall setColumn(oPlugin plugin, tColId colId , tColType type , int def , const char * name=0)=0;
		 /**
		 @attention Tekstowa wartoœæ domyœlna musi "istnieæ" przez ca³y okres istnienia tablicy danych!
		 */
 		 tColId setColumn(oPlugin plugin, tColId id , tColType type , const char * def  , const char * name=0) {
			return this->setColumn(plugin, id , type , (int)def , name);
		 }

 		 tColId setColumn(tColId id , tColType type  , int def  , const char * name=0);
 		 tColId setColumn(tColId id , tColType type , const char * def  , const char * name=0);

         // funkcje lokalne, dla ulatwienia
         int getInt(tRowId row , tColId col);
         bool setInt(tRowId row , tColId col , int value , int mask = -1);
         char * getStr(tRowId row , tColId col , char * buff = 0 , unsigned int size = 0);
         bool setStr(tRowId row , tColId col , const char * value);
         __int64 getInt64(tRowId row , tColId col);
         bool setInt64(tRowId row , tColId col , __int64 value , __int64 mask = -1);

         int getInt(tRowId row , const char * colName);
         bool setInt(tRowId row , const char * colName , int value , int mask = -1);
         char * getStr(tRowId row , const char * colName , char * buff = 0 , unsigned int size = 0);
         bool setStr(tRowId row , const char * colName , const char * value);
         __int64 getInt64(tRowId row , const char * colName);
         bool setInt64(tRowId row , const char * colName , __int64 value , __int64 mask = -1);

		 /** Dodaje wiersz do tablicy.
		 @warning W wiêkszoœci przypadków to w³aœciciel tablicy dodaje do niej wiersze!
		 */
		 virtual tRowId __stdcall addRow(tRowId rowId = rowNotFound)=0;
		 /** Usuwa wiersz z tablicy.
		 @warning W wiêkszoœci przypadków to w³aœciciel tablicy usuwa z niej wiersze!
		 */
		 virtual bool __stdcall removeRow(tRowId rowId)=0;
         /** Kasuje kolumny i dane */
		 virtual void __stdcall reset()=0;
         /** Kasuje dane */
		 virtual void __stdcall resetData()=0;
         /** Zwalnia dane z pamiêci */
		 virtual void __stdcall unloadData()=0;
		 /** Rozsy³a komunikat IM::setColumns dla tablicy */
		 virtual void __stdcall requestColumns(cCtrl * ctrl, unsigned int net = -1, unsigned int plugType = -1)=0;
		 /** Rozsy³a komunikat IM::dataChanged dla tablicy, lub wiersza. 
		 @param ctrl - cCtrl wtyczki
		 @param rowId - identyfikator zmienionego wiersza, lub allRows
		 */
		 virtual void __stdcall dataChanged(cCtrl * ctrl, tRowId rowId,unsigned int net = -1, unsigned int plugType = -1)=0;

		 void dataChanged(cCtrl * ctrl, unsigned int net = -1, unsigned int plugType = -1) {
			 dataChanged(ctrl, allRows, net, plugType);
		 }
		 
		 /** Zwraca true je¿eli dane zosta³y za³adowane */
		 virtual bool __stdcall isLoaded()=0;

		 /** Wczytuje dane z pliku, o ile wczeœniej nie by³y ju¿ za³adowane.
		  Je¿eli z tablic¹ nie jest skojarzony ¿aden plik wywo³anie load() blokuje mo¿liwoœæ dodawania kolumn.
		  \param force Wymusza prze³adowanie danych na nowo. Wszystkie zmiany zostan¹ utracone.
		  \param filePath £aduje dane z innego pliku ni¿ domyœlny.
		  \return true je¿eli dane zosta³y za³adowane 
		  */
		 virtual bool __stdcall load(bool force = false, const char * filePath = 0)=0;
		 /** Zapisuje dane do pliku, je¿eli dane uleg³y zmianie.
		  Je¿eli z tablic¹ nie jest skojarzony ¿aden plik wywo³anie save() nie ma ¿adnego skutku.
		  \param force Wymusza zapisanie danych.
		  \param filePath Zapisuje dane do innego pliku ni¿ domyœlny.
		  \return true je¿eli dane zosta³y zapisane 
		  */
		 virtual bool __stdcall save(bool force = false, const char * filePath = 0)=0;
		 /** Zapis z opóŸnieniem. 
		 Dane zostan¹ zapisane do domyœlnego pliku, je¿eli przez kilka sekund nie bêdzie wywo³ywana f-cja lateSave.
		 Dane zapisywane s¹ jednorazowo.
		 @warning Je¿eli po kilku sekundach od wywo³ania lateSave() zaczniemy zapisywaæ do tablicy dane bez wczeœniejszego wywo³ania lateSave(false) tablica mo¿e zostaæ zapisana ze zmianami wprowadzonymi do po³owy...
		 @param enabled W³¹cza/wy³¹cza opcjê opóŸnionego zapisu.
		 */
		 virtual void __stdcall lateSave(bool enabled=true)=0;

		 virtual bool __stdcall setOpt(enTableOptions option , bool enabled)=0;
		 virtual bool __stdcall getOpt(enTableOptions option)=0;

		 /** Ustawia nazwê pliku */
		 virtual void __stdcall setFilename(const char * filename)=0;
		 virtual const char * __stdcall _getFilename()=0;
		 /** Ustawia œcie¿kê katalogu z plikiem.
		 @param path Nowa œcie¿ka, lub 0 je¿eli chcemy ustawiæ œcie¿kê standardow¹
		 */
		 virtual void __stdcall setDirectory(const char * path)=0;
		 virtual const char * __stdcall _getDirectory()=0;
		 virtual const char * __stdcall _getTableName()=0;
		 virtual tTableId __stdcall getTableId()=0;
		 virtual oPlugin __stdcall getTableOwner()=0;

		 virtual bool __stdcall unregisterTable()=0;

#ifdef _STRING_
		 /** Zwraca nazwê pliku (bez œcie¿ki) */
		 std::string getFilename() {
			 this->lock();
			 std::string str = this->_getFilename();
			 this->unlock();
			 return str;
		 }
		 /** Zwraca œcie¿kê do pliku */
		 std::string getDirectory() {
			 this->lock();
			 std::string str = this->_getDirectory();
			 this->unlock();
			 return str;
		 }
		 /** Zwraca nazwê tablicy.
		 Nazwa pobierana jest z Unique::domainTables i tam powinna byæ rejestrowana
		 */
		 std::string getTableName() {
			 this->lock();
			 std::string str = this->_getTableName();
			 this->unlock();
			 return str;
		 }
#endif

	  private:
		virtual void __stdcall zz_it1(){}
		virtual void __stdcall zz_it2(){}
		virtual void __stdcall zz_it3(){}
		virtual void __stdcall zz_it4(){}
		virtual void __stdcall zz_it5(){}
		virtual void __stdcall zz_it6(){}
		virtual void __stdcall zz_it7(){}
		virtual void __stdcall zz_it8(){}
		virtual void __stdcall zz_it9(){}
		virtual void __stdcall zz_it10(){}

	};

	inline tTableId getTableId(const char * tableName);


	/** Obiekt tablicy. */
	class oTable:public Stamina::SharedPtr<iTable> {
	public:
		oTable(tTableId tableId) {
			this->setById(tableId);
		}
		oTable(const char * tableName) {
			this->setById(getTableId(tableName));
		}
		oTable(iTable * obj = 0) {
			this->set(obj);
		}
		void setById(tTableId tableId);

		 oTable & operator |= (enTableOptions option) {
			 this->get()->setOpt(option, true);
			 return *this;
		 }
		 oTable & operator ^= (enTableOptions option) {
			 this->get()->setOpt(option, false);
			 return *this;
		 }
		 bool operator & (enTableOptions option) {
			 return this->get()->getOpt(option);
		 }

	};

	oTable registerTable(cCtrl * ctrl, tTableId tableId, const char * name, enTableOptions tableOpts = optDefaultSet);
	inline oTable registerTable(cCtrl * ctrl, tTableId tableId, enTableOptions tableOpts = optDefaultSet) {
		return registerTable(ctrl, tableId, 0, tableOpts);
	}
	inline oTable registerTable(cCtrl * ctrl, const char * name, enTableOptions tableOpts = optDefaultSet) {
		return registerTable(ctrl, tableByName, name, tableOpts);
	}

	namespace IM {
		const tIMid registerTable = 600;
		//const tIMid unregisterTable = 601;

		/** Tablica oczekuje rejestracji kolumn.
		Po otrzymaniu tego komunikatu, mo¿emy zarejestrowaæ, w tablicy której komunikat dotyczy, w³asne kolumny.
		Komunikat wysy³any jest w formie Tables::_tableIM, dotyczy tylko @b jednej tablicy i @b tylko w niej powinniœmy dodawaæ kolumny.
		@attention Na tablicy mo¿na wykonywaæ @b tylko operacje zwi¹zane z dodawaniem kolumn!

		@return zawsze 0

		@code
		case Tables::setColumns: {
			Tables::_tableIM * sc = static_cast<Tables::_tableIM *> msgBase;
			if (sc->table->getId() == Tables::tableConfig) {
				sc->table->setColumn(...);
			}
			return 0;
		}
		@endcode
		*/
		const tIMid setColumns	= IM_BASE + 1100;

		/** Dane w tablicy uleg³y zmianie
		Komunikat przesy³any w postaci _tableIM */
		const tIMid dataChanged = IM_BASE + 1100;
		/** Tablica zostanie za chwilê zapisana
		Komunikat przesy³any w postaci _tableIM */
		const tIMid beforeSave  = IM_BASE + 1101;
		/** Tablica zosta³a prze³adowana z pliku
		Komunikat przesy³any w postaci _tableIM */
		const tIMid afterLoad	= IM_BASE + 1102;
		/** Nowy wiersz _tableRowIM::rowId w tablicy...
		Komunikat przesy³any w postaci _tableRowIM */
		const tIMid rowAdded	= IM_BASE + 1103;
		/** Wiersz _tableRowIM::rowId zosta³ usuniêty
		Komunikat przesy³any w postaci _tableRowIM */
		const tIMid rowRemoved	= IM_BASE + 1104;
		/** Komunikat przesy³any w postaci _tableIM */
		const tIMid resetting	= IM_BASE + 1105;
		/** Wiersz _tableRowIM::rowId za chwilê zostanie usuniêty
		Komunikat przesy³any w postaci _tableRowIM */
		const tIMid rowRemoving	= IM_BASE + 1106;

		class _tableIM: public sIMessage_base {
		public:
			/** Obiekt tablicy. */
			oTable table;

			_tableIM(tIMid IMid, oTable & table):sIMessage_base(IMid, 0, 0), table(table) {
				this->s_size = sizeof(*this);
			}
		};
		class _registerTable: public _tableIM {
		public:
			tTableId tableId;
			enTableOptions tableOpts;
			_registerTable(tTableId tableId, enTableOptions tableOpts = optDefaultSet):_tableIM(registerTable, oTable()),tableId(tableId),tableOpts(tableOpts) {
				this->s_size = sizeof(*this);
			}
		};
		class _tableRowIM: public _tableIM {
		public:
			tRowId rowId;
			_tableRowIM(tIMid imId, oTable & table, tRowId rowId):_tableIM(imId, table), rowId(rowId) {
				this->s_size = sizeof(*this);
			}
		};
	};

};};

#ifndef _DTABLE_
//typedef Konnekt::Tables::Value sDTValue;
#endif

