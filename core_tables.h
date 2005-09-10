#pragma once

#include <Stamina/Object.h>
#include <Stamina/DataTable.h>
#include <Stamina/DataTable/DTDeprecated.h>
#include <Stamina/DataTable/Find.h>
#include <Stamina/DataTable/iColumn.h>
#include <Stamina/DataTable/iRow.h>

#include "core_object.h"
#include "core_unique.h"
#include "core_plugin.h"

#define DTCFG Konnekt::Tables::tableConfig
#define DTCNT Konnekt::Tables::tableContacts
#define DTMSG Konnekt::Tables::tableMessages
#define DTNONE Konnekt::Tables::tableNotFound


namespace Konnekt { 

/** Przestrze� obs�ugi tablic z danymi.

@warning Obs�uga tablic opiera si� na bibliotece Stamina::DT (DataTable). Dlatego wiele klas, enumeracji etc. korzysta z tej przestrzeni nazw.
*/
namespace Tables {
	using namespace ::Stamina::DT;
	using ::Stamina::String;
	using ::Stamina::StringRef;
	using ::Stamina::ByteBuffer;

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

	typedef enTableId tTableId;



	enum enTableOptions {
		/** Przy zamykaniu, zapisywaniu profilu, lub unloadData() dane zostan� automatycznie zapisane */
        optAutoSave = 1,
		/** Tablica nie b�dzie dost�pna przez Ctrl::getTable */
		optPrivate = 2,
		/** Tablica nie b�dzie rozsy�a�a komunikat�w */
		optBroadcastEvents = 4, 
		optUsePassword = 8,
		/** Dane dotycz� wszystkich profili konnekta i b�d� przechowywane w katalogu %KonnektData% */
		optGlobalData = 0x10,          
		/** Nie wczytuje nie zarejestrowanych kolumn.
		Standardowo �adowane s� wszystkie kolumny, co umo�liwia przechowywanie danych
		zapisanych przez wtyczki, kt�re p�niej zosta�y wy��czone i nie mog�y zarejestrowa� swoich kolumn.
		*/
		optDiscardLoadedColumns = 0x20,
		/** Po zmianie g��wnego has�a profilu ta tablica zostanie r�wnie� zaktualizowana  */
		optUseCurrentPassword = 0x48,
		/** Automatycznie �aduje dane przy pierwszym u�yciu. Zabezpiecza r�wnie� przed zapisaniem danych bez uprzedniego za�adowania. */
		optAutoLoad = 0x80,
		/** Automatycznie roz�adowuje dane gdy zostanie zamkni�ta ostatnia referencja do oibiektu bazy.
		�aby dzia�a�o to prawid�owo:
		- nie mo�na przechowywa� globalnego obiektu do tablicy
		- deklarowa� obiekt bazy danych tylko na czas jej u�ywania:
		@code
		void mojaFunkcja() {
			oTable dt("MojaTablica");
			dt->setInt(...);
			...
		} // "MojaTablica" zostanie zwolniona na ko�cu tej funkcji. Je�eli nic wi�cej nie korzysta ju� z tej tablicy dane zostan� zapisane do pliku i zwolnione z pami�ci!
		@endcode
		*/
		optAutoUnload = 0x100,
		/** Pliki zapisywane s� w starym formacie zabezpiecze� */
		optUseOldCryptVersion = 0x200,
		/** Automatycznie tworzy i przywraca backupy */
		optMakeBackups = 0x400,
		/** U�ywa plik�w tymczasowych do zapisywania danych */
		optUseTemporary = 0x800,
		/** Nie wy�wietla �adnych komunikat�w o b��dach */
		optSilent = 0x1000,


		optDefaultSet = /*optBroadcastEvents | */optUseCurrentPassword | optUseTemporary,
	};

	inline enTableOptions operator | (enTableOptions a, enTableOptions b) {
		return (enTableOptions)((int)a | (int)b);
	}

	class iTable: public ::Stamina::iSharedObject {
	public:

		STAMINA_OBJECT_CLASS_VERSION(Konnekt::Tables::iTable, ::Stamina::iSharedObject, ::Stamina::Version(1, 1, 0, 0));


        /** Zamienia (lub nie) identyfikator na numer wiersza.*/
        virtual int __stdcall getRowPos(tRowId rowId)=0;
        /** Zamienia (lub nie) numer wiersza na jego identyfikator.*/
        virtual int __stdcall getRowId(unsigned int rowPos)=0;

		/** Zwraca obiekt kolumny o podanym identyfikatorze, o ile istnieje */
		virtual oRow __stdcall getRow(tRowId rowId)=0;

		 /** Znajduje wiersz spe�niaj�cy podane kryteria.
		 @param startPos - numer wiersza od kt�rego zaczynamy szukanie
		 @param argCount - liczba przekazywanych struktur Find*, lub -1 je�eli ostatnie kryterium jest r�wne 0
		 @param ... - kolejne kryteria jako struktury Find*, najbezpieczniej doda� na ko�cu kryterium 0

		 np. Znajduje pierwszy kontakt sieci NET_GG aktywny w ci�gu ostatniej minuty.
		 dt->findRow(0, -1, &Find::EqInt(CNT_NET, NET_GG), &Find(Find::gt, CNT_ACTIVITY, ValueInt64(_time64(0) - 60000)), 0);
		 */
         virtual oRow __cdecl _findRow(unsigned int startPos, int argCount, ...)=0;

		 inline oRow findRow(unsigned int startPos, Find& f1) {
			 return this->_findRow(startPos, 1, &f1);
		 }
		 inline oRow findRow(unsigned int startPos, Find& f1, Find& f2) {
			 return this->_findRow(startPos, 2, &f1, &f2);
		 }
		 inline oRow findRow(unsigned int startPos, Find& f1, Find& f2, Find& f3) {
			 return this->_findRow(startPos, 3, &f1, &f2, &f3);
		 }

		 /** Zwraca ilo�� wierszy w tablicy.*/
         virtual unsigned int __stdcall getRowCount()=0;

		 int getCount() {
			 return this->getRowCount();
		 }

		 /** Zwraca obiekt kolumny o podanym identyfikatorze.
		 @warning Zawsze zwraca jaki� obiekt! Istnienie kolumny nale�y sprawdzi� funkcj� iColumn::isUndefined()
		 */
		 virtual oColumn __stdcall getColumn(tColId colId)=0;

		 virtual oColumn __stdcall getColumn(const Stamina::StringRef& colName)=0;

		 inline tColId getColumnId(const StringRef& colName) {
			 return this->getColumn(colName)->getId();
		 }

		 /** Zwraca liczb� kolumn */
		 virtual unsigned int __stdcall getColCount()=0;

		 /** Zwraca identyfikator kolumny na wskazanej pozycji lub colNotFound */
		 virtual oColumn __stdcall getColumnByPos(unsigned int colPos)=0;

		 bool columnExists(tColId colId) {
			 return this->getColumn(colId)->isUndefined() == false;
		 }

         /** Blokuje dost�p do wiersza dla innych w�tk�w. 
		 Zaraz po wykorzystaniu zabezpieczonych danych trzeba wywo�a� unlockData() z tymi samymi parametrami!
         @param rowId Identyfikator/numer wiersza, lub allRows je�li chcemy zablokowa� WSZYSTKIE dane
         @param reserved Zarezerwowane na p�niej, musi by� r�wne 0.
         @return Ilo�� wcze�niej za�o�onych blokad.
         */
         virtual void __stdcall lockData(tRowId rowId , int reserved=0)=0;
         /** Odblokowuje dost�p do wiersza dla innych w�tk�w, zastrze�ony wcze�niej przy u�yciu lockData().
         @param rowId Identyfikator/numer wiersza, lub allRows je�li chcemy dblokowa� WSZYSTKIE dane
         @param reserved Zarezerwowane na p�niej, musi by� r�wne 0.
         @return Ilo�� pozosta�ych blokad.
         @attention Po wykonaniu tej funkcji, wszystkie zwr�cone wska�niki bezpo�rednie mog� by� ju� nieaktualne!
         */
         virtual void __stdcall unlockData(tRowId rowId , int reserved=0)=0;



		 /** Rejestruje kolumn� w tablicy.
		 Kolumny mo�na dodawa� dop�ki tablica jest pusta, lub nie zosta�a za�adowana z pliku.	
		 @param obiekt wtyczki rejestruj�cej - cCtrl::getPlugin()
		 @param colId Identyfikator rejestrowanej kolumny, lub colByName je�eli chcemy odnosi� si� do niej tylko po nazwie
		 @param type Typ warto�ci kolumny z flagami (enColumnType | enColumnFlag)
		 @param name Nazwa kolumny. Idnetyfikator kolumny zarejestrowanej tylko po nazwie mo�na zdoby� przy pomocy getColId().
		 @return Obiekt zarejestrowanej kolumny

		 @code
		 // zwykla rejestracja
		 dt->setColumn(identyfikator_kolumny, ctypeInt);
		 // rejestracja po nazwie
		 dt->setColumn(DT::colByName, ctypeInt, "NazwaKolumny");
		 // ustawianie wartosci domyslnej
		 dt->setColumn(idKolumny, ctypeString)->setString(rowDefault, "Warto�� domy�lna");
		 @endcode

		 */
		 virtual oColumn __stdcall setColumn(const oPlugin& plugin, tColId colId , tColType type , const Stamina::StringRef& name = StringRef())=0;

 		 oColumn setColumn(tColId id, tColType type, const Stamina::StringRef& name = StringRef());


		 /** Dodaje wiersz do tablicy.
		 @warning W wi�kszo�ci przypadk�w to w�a�ciciel tablicy dodaje do niej wiersze!
		 */
		 virtual oRow __stdcall addRow(tRowId rowId = rowNotFound)=0;
		 /** Usuwa wiersz z tablicy.
		 @warning W wi�kszo�ci przypadk�w to w�a�ciciel tablicy usuwa z niej wiersze!
		 */
		 virtual bool __stdcall removeRow(tRowId rowId)=0;
         /** Kasuje kolumny i dane */
		 virtual void __stdcall reset()=0;
         /** Kasuje dane */
		 virtual void __stdcall resetData()=0;
         /** Zwalnia dane z pami�ci */
		 virtual void __stdcall unloadData()=0;
		 /** Rozsy�a komunikat IM::setColumns dla tablicy */
		 virtual void __stdcall requestColumns(cCtrl * ctrl, unsigned int net = -1, unsigned int plugType = -1)=0;
		 /** Rozsy�a komunikat IM::dataChanged dla tablicy, lub wiersza. 
		 @param ctrl - cCtrl wtyczki
		 @param rowId - identyfikator zmienionego wiersza, lub allRows
		 */
		 virtual void __stdcall dataChanged(cCtrl * ctrl, tRowId rowId,unsigned int net = -1, unsigned int plugType = -1)=0;

		 void dataChanged(cCtrl * ctrl, unsigned int net = -1, unsigned int plugType = -1) {
			 dataChanged(ctrl, allRows, net, plugType);
		 }
		 
		 /** Zwraca true je�eli dane zosta�y za�adowane */
		 virtual bool __stdcall isLoaded()=0;

		 /** Wczytuje dane z pliku, o ile wcze�niej nie by�y ju� za�adowane.
		  Je�eli z tablic� nie jest skojarzony �aden plik wywo�anie load() blokuje mo�liwo�� dodawania kolumn.
		  \param force Wymusza prze�adowanie danych na nowo. Wszystkie zmiany zostan� utracone.
		  \param filePath �aduje dane z innego pliku ni� domy�lny.
		  \return true je�eli dane zosta�y za�adowane 
		  */
		 virtual enResult __stdcall load(bool force = false, const StringRef& filePath = StringRef())=0;
		 /** Zapisuje dane do pliku, je�eli dane uleg�y zmianie.
		  Je�eli z tablic� nie jest skojarzony �aden plik wywo�anie save() nie ma �adnego skutku.
		  \param force Wymusza zapisanie danych.
		  \param filePath Zapisuje dane do innego pliku ni� domy�lny.
		  \return true je�eli dane zosta�y zapisane 
		  */
		 virtual enResult __stdcall save(bool force = false, const StringRef& filePath = StringRef())=0;
		 /** Zapis z op�nieniem. 
		 Dane zostan� zapisane do domy�lnego pliku, je�eli przez kilka sekund nie b�dzie wywo�ywana f-cja lateSave.
		 Dane zapisywane s� jednorazowo.
		 @warning Je�eli po kilku sekundach od wywo�ania lateSave() zaczniemy zapisywa� do tablicy dane bez wcze�niejszego wywo�ania lateSave(false) tablica mo�e zosta� zapisana ze zmianami wprowadzonymi do po�owy...
		 @param enabled W��cza/wy��cza opcj� op�nionego zapisu.
		 */
		 virtual void __stdcall lateSave(bool enabled=true)=0;

		 virtual bool __stdcall setOpt(enTableOptions option , bool enabled)=0;
		 virtual bool __stdcall getOpt(enTableOptions option)=0;

		 /** Ustawia nazw� pliku */
		 virtual void __stdcall setFilename(const StringRef& filename)=0;
		 /** Zwraca nazw� pliku (bez �cie�ki) */
		 virtual String __stdcall getFilename()=0;
		 /** Ustawia �cie�k� katalogu z plikiem.
		 @param path Nowa �cie�ka, lub 0 je�eli chcemy ustawi� �cie�k� standardow�
		 */
		 virtual void __stdcall setDirectory(const StringRef& path = StringRef())=0;
		 /** Zwraca �cie�k� do pliku */
		 virtual String __stdcall getDirectory()=0;
		 /** Zwraca nazw� tablicy.
		 Nazwa pobierana jest z Unique::domainTables i tam powinna by� rejestrowana
		 */
		 String getTableName();
		 virtual tTableId __stdcall getTableId()=0;
		 virtual oPlugin __stdcall getTableOwner()=0;

		 virtual bool __stdcall unregisterTable()=0;

#ifdef __DATATABLE__
		 virtual DataTable& __stdcall getDT()=0;
#else
		 virtual void* __stdcall getDT()=0;
#endif

 		 virtual void setTablePassword(const StringRef& password)=0;


		 // wczytywanie danych

		inline int getInt(tRowId row , tColId id, GetSet flags = gsNone)  {
			return this->getColumn(id)->getInt( this->getRow(row), flags);
		}
		inline bool setInt(tRowId rowId , tColId id , int val, GetSet flags = gsNone) {
			oRow row = this->getRow(rowId);
			if (row) {
				return this->getColumn(id)->setInt(row , val, flags);
			}
			return row;
		}
		inline String getString(tRowId row , tColId id, GetSet flags = getCopy) {
			return ::Stamina::PassStringRef( this->getColumn(id)->getString( this->getRow(row), flags ) );
		}
		inline bool setString(tRowId rowId , tColId id , const StringRef& val, GetSet flags = gsNone) {
			oRow row = this->getRow(rowId);
			if (row) {
				return this->getColumn(id)->setString(row, val, flags);
			}
			return row;
		}

		inline ByteBuffer getBin(tRowId row , tColId id, GetSet flags = getCopy) {
			ByteBuffer b;
			b.swap( this->getColumn(id)->getBin( this->getRow(row), flags ) );
			return b;
		}
		inline bool setBin(tRowId rowId , tColId id , const ByteBuffer& val, GetSet flags = gsNone) {
			oRow row = this->getRow(rowId);
			if (row) {
				return this->getColumn(id)->setBin(row, val, flags);
			}
			return row;
		}

		inline __int64 getInt64(tRowId row , tColId id, GetSet flags = gsNone) {
			return this->getColumn(id)->getInt64( this->getRow(row), flags );
		}
		inline bool setInt64(tRowId rowId , tColId id , __int64 val, GetSet flags = gsNone) {
			oRow row = this->getRow(rowId);
			if (row) {
				return this->getColumn(id)->setInt64(row , val, flags );
			}
			return row;
		}

		inline double getDouble(tRowId row , tColId id, GetSet flags = gsNone) {
			return this->getColumn(id)->getDouble( this->getRow(row), flags );
		}
		inline bool setDouble(tRowId rowId , tColId id , double val, GetSet flags = gsNone) {
			oRow row = this->getRow(rowId);
			if (row) {
				return this->getColumn(id)->setDouble(row , val, flags );
			}
			return row;
		}

// byName

		inline int getInt(tRowId row , const StringRef& colName, GetSet flags = gsNone)  {
			return this->getInt(row, this->getColumnId(colName), flags);
		}
		inline bool setInt(tRowId rowId , const StringRef& colName , int val, GetSet flags = gsNone) {
			return this->setInt(rowId, this->getColumnId(colName), val, flags);
		}
		inline String getString(tRowId row , const StringRef& colName, GetSet flags = getCopy) {
			return ::Stamina::PassStringRef( this->getString(row, this->getColumnId(colName), flags) );
		}
		inline bool setString(tRowId rowId , const StringRef& colName , const StringRef& val, GetSet flags = gsNone) {
			return this->setString(rowId, this->getColumnId(colName), val, flags);
		}

		inline ByteBuffer getBin(tRowId row , const StringRef& colName, GetSet flags = getCopy) {
			return this->getBin(row, this->getColumnId(colName), flags);
		}
		inline bool setBin(tRowId rowId , const StringRef& colName , const ByteBuffer& val, GetSet flags = gsNone) {
			return this->setBin(rowId, this->getColumnId(colName), val, flags);
		}

		inline __int64 getInt64(tRowId row , const StringRef& colName, GetSet flags = gsNone) {
			return this->getInt64(row, this->getColumnId(colName), flags);
		}
		inline bool setInt64(tRowId rowId , const StringRef& colName , __int64 val, GetSet flags = gsNone) {
			return this->setInt64(rowId, this->getColumnId(colName), val, flags);
		}

		inline double getDouble(tRowId row , const StringRef& colName, GetSet flags = gsNone) {
			return this->getDouble(row, this->getColumnId(colName), flags);
		}
		inline bool setDouble(tRowId rowId , const StringRef& colName , double val, GetSet flags = gsNone) {
			return this->setDouble(rowId, this->getColumnId(colName), val, flags);
		}


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
		//virtual void __stdcall zz_it10(){}

	};

	inline tTableId getTableId(const StringRef& tableName);


	/** Obiekt tablicy. */
	class oTable:public ::Stamina::SharedPtr<iTable> {
	public:
		oTable(tTableId tableId) {
			this->setById(tableId);
		}
		oTable(const StringRef& tableName) {
			this->setById(getTableId(tableName));
		}
		oTable(iTable * obj = 0) {
			this->set(obj);
		}
		void setById(tTableId tableId);
/*
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
		 */

	};

	oTable registerTable(cCtrl * ctrl, tTableId tableId, const StringRef& name, enTableOptions tableOpts = optDefaultSet);
	inline oTable registerTable(cCtrl * ctrl, tTableId tableId, enTableOptions tableOpts = optDefaultSet) {
		return registerTable(ctrl, tableId, tableOpts);
	}
	inline oTable registerTable(cCtrl * ctrl, const StringRef& name, enTableOptions tableOpts = optDefaultSet) {
		return registerTable(ctrl, tableByName, name, tableOpts);
	}


	class TableLocker { 
	public:
		inline TableLocker(const oTable& table, tRowId row = allRows):_table(table), _row(row) {
			_table->lockData(_row);
		}
		inline ~TableLocker() {
			_table->unlockData(_row);
		}
	private:
		oTable _table;
		tRowId _row;
	};



	namespace IM {
		const tIMCid registerTable = 600;
		//const tIMid unregisterTable = 601;

		/** Tablica oczekuje rejestracji kolumn.
		Po otrzymaniu tego komunikatu, mo�emy zarejestrowa�, w tablicy kt�rej komunikat dotyczy, w�asne kolumny.
		Komunikat wysy�any jest w formie Tables::_tableIM, dotyczy tylko @b jednej tablicy i @b tylko w niej powinni�my dodawa� kolumny.
		@attention Na tablicy mo�na wykonywa� @b tylko operacje zwi�zane z dodawaniem kolumn!

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

		/** Dane w tablicy uleg�y zmianie
		Komunikat przesy�any w postaci TableIM */
		const tIMid dataChanged = IM_BASE + 1100;
		/** Tablica zostanie za chwil� zapisana
		Komunikat przesy�any w postaci TableIM */
		const tIMid beforeSave  = IM_BASE + 1101;
		/** Tablica zosta�a prze�adowana z pliku
		Komunikat przesy�any w postaci TableIM */
		const tIMid afterLoad	= IM_BASE + 1102;
		/** Nowy wiersz _tableRowIM::rowId w tablicy...
		Komunikat przesy�any w postaci TableRow */
		const tIMid rowAdded	= IM_BASE + 1103;
		/** Wiersz _tableRowIM::rowId zosta� usuni�ty
		Komunikat przesy�any w postaci TableRow */
		const tIMid rowRemoved	= IM_BASE + 1104;
		/** Komunikat przesy�any w postaci TableIM */
		const tIMid resetting	= IM_BASE + 1105;
		/** Wiersz _tableRowIM::rowId za chwil� zostanie usuni�ty
		Komunikat przesy�any w postaci TableRow */
		const tIMid rowRemoving	= IM_BASE + 1106;

		const tIMid tableRegistered = IM_BASE + 1107;
		const tIMid tableUnregistering = IM_BASE + 1108;

		class TableIM: public sIMessage_base {
		public:
			/** Obiekt tablicy. */
			oTable table;

			TableIM(tIMid IMid, oTable & table):sIMessage_base(IMid, 0, 0), table(table) {
				this->s_size = sizeof(*this);
			}
		};
		class RegisterTable: public TableIM {
		public:
			tTableId tableId;
			enTableOptions tableOpts;
			RegisterTable(tTableId tableId, enTableOptions tableOpts = optDefaultSet):TableIM(registerTable, oTable()),tableId(tableId),tableOpts(tableOpts) {
				this->s_size = sizeof(*this);
			}
		};
		class TableRow: public TableIM {
		public:
			tRowId rowId;
			TableRow(tIMid imId, oTable & table, tRowId rowId):TableIM(imId, table), rowId(rowId) {
				this->s_size = sizeof(*this);
			}
		};
	};

};};

#ifndef _DTABLE_
//typedef Konnekt::Tables::Value sDTValue;
#endif

using Tables::tTableId;
