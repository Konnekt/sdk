#pragma once

/** @file Deklaracje do obs�ugi test�w
*/

#include <Stamina/String.h>
#include <Stamina/iArray.h>

#pragma pack(push, 1)

namespace Konnekt {
  namespace IM {
    /** 
     * Zapytanie o list� test�w (IM::GetTests).
     * Je�eli wtyczka posiada jakie� zestawy testowe - powinna je tutaj zwr�ci�.
     * @sa GetTests
     */
    const tIMid getTests = IM_BASE + 200;

    /** 
     * Uruchamia test. (IM::RunTests).
     */
    const tIMid runTests = IM_BASE + 201;

    /** 
     * Klasa u�ywana w GetTest
     * @sa GetTest getTest
     */
    class TestInfo {
    public:
      enum enFlags {
        flagNone = 0,
        flagSubOpen = 1, ///< Otwiera podgrup� test�w
        flagSubClose = 2, ///< Zamyka podgrup� test�w
        flagFailed = 4 ///< Oznacza test jako nieudany
      };

      TestInfo(const Stamina::StringRef& name, const Stamina::StringRef& command = "", enFlags flags = flagNone): name(name), command(command), flags(flags) { }
      TestInfo(enFlags flags): flags(flags) { }

      Stamina::String name;
      Stamina::String command;
      Stamina::String info;
      enFlags flags;

      const Stamina::String& getCommand() {
        if (this->command.empty()) {
          return this->name;
        } else {
          return this->command;
        }
      }

      void setFlag(enFlags flag, bool value) {
        if (value) {
          this->flags = (enFlags) (this->flags | flag);
        } else {
          this->flags = (enFlags) (this->flags & ~flag);
        }
      }

      bool getFlag(enFlags flag) {
        return (this->flags & flag) != 0;
      }

    private:
      void * reserved;
    };

    /** 
     * Struktura do przekazywania IM::getTests. 
     * Parametr @a tests trzeba wype�ni� informacjami o dost�pnych testach...
     * W tests domy�lnie jest ju� zainicjowana tablica...
     *
     * @code
     * case IM::getTests: {
     *   GetTests* gt = static_cast<GetTests*>(msgBase);
     *   gt->tests->append(TestInfo("Testy"));
     *   gt->tests->append(TestInfo(TestInfo::flagSubOpen));
     *   gt->tests->append(TestInfo("Test1", "test1"));
     *   gt->tests->append(TestInfo("Test2", "test2"));
     *   gt->tests->append(TestInfo(TestInfo::flagSubClose));
     *   return true;
     * }
     * @endcode
     */
    class GetTests: public sIMessage_base {
    public:
      Stamina::oArray<TestInfo> tests;

      GetTests(const Stamina::oArray<TestInfo>& array) {
        this->id = getTests;
        S_ASSERT(array.isValid());
        this->tests = array;
        this->s_size = sizeof(*this);
      }
    };

    class RunTests:public GetTests {
    public:
      RunTests(const Stamina::oArray<TestInfo>& array):GetTests(array) {
        this->id = runTests;
        S_ASSERT(array.isValid());
        this->tests = array;
        this->s_size = sizeof(*this);
      }
    };
  };
};

#pragma pack(pop)
