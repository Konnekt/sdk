#pragma once

/** @file Deklaracje do obs³ugi testów

*/

#include <Stamina/iArray.h>

namespace Konnekt {


	namespace IM {

		/** Zapytanie o listê testów ( IM::GetTests ).
		Je¿eli wtyczka posiada jakieœ zestawy testowe - powinna je tutaj zwróciæ.
		@sa GetTests
		*/
		const tIMid getTests = IM_BASE + 200;

		/** Uruchamia test. (sIMessage_plugArgs).
		Przekazane w sIMessage_plugArgs argumenty to:
		test SIG KOMENDA PARAMETRY
		SIG - wpisana sygnatura wtyczki. Mo¿e byæ sygnatur¹ wtyczki, która otrzyma³a komunikat, lub * oznaczaj¹ca wszystkie wtyczki
		KOMENDA - Komenda testu (zadeklarowana wczeœniej w getTests w TestInfo::command) 
		PARAMETRY - wszystkie dodatkowo wpisane parametry...

		@return Nale¿y zwróciæ liczbê @b b³êdów w testach!
		*/
		const tIMid runTests = IM_BASE + 201;

		/** Klasa u¿ywana w GetTest
		@sa GetTest getTest
		*/
		class TestInfo {
		public:

			enum enFlags {
				flagNone = 0,
				flagSubOpen = 1, ///< Otwiera podgrupê testów
				flagSubClose = 2, ///< Zamyka podgrupê testów
			};

			TestInfo(const StringRef& name, const StringRef& command = "", enFlags flags = flagNone):name(name), command(command), flags(flags) {}

			TestInfo(enFlags flags):flags(flags) {}

			Stamina::String name;
			Stamina::String command;
			enFlags flags;

		private:
			void* reserved;

		};

		/** Struktura do przekazywania IM::getTests. 
		Parametr @a tests trzeba wype³niæ informacjami o dostêpnych testach...
		W tests domyœlnie jest ju¿ zainicjowana tablica...

		@code
		case IM::getTests: {
			GetTests* gt = static_cast<GetTests*>(msgBase);
			gt->tests->append(TestInfo("Testy"));
			gt->tests->append(TestInfo(TestInfo::flagSubOpen));
			gt->tests->append(TestInfo("Test1", "test1"));
			gt->tests->append(TestInfo("Test2", "test2"));
			gt->tests->append(TestInfo(TestInfo::flagSubClose));
			return true;
		}
		@endcode
		*/
		class GetTests:public sIMessage_base {
		public:

			Stamina::oArray<TestInfo> tests;

			GetTests(const Stamina::oArray<TestInfo>& array) {
				this->id = getTests;
				S_ASSERT(array.isValid());
				this->tests = array;
				this->s_size=sizeof(*this);
			}
		};



	};



};