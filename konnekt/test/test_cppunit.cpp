// TestSuite.cpp : Defines the entry point for the console application.
//

#include <map>

#include "..\plug.h"
#include "..\plugin_test.h"
#include "..\plug_export.h"

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h> 
#include <cppunit/TestFailure.h> 
#include <cppunit/SourceLine.h> 
#include <cppunit/Exception.h> 

#include <Stamina/Helpers.h>

using namespace CPPUNIT_NS;

namespace Konnekt {

	using namespace IM;

	void cppunit_getTests_recurse(IM::GetTests* dt, Test* test) {
		dt->tests->append(IM::TestInfo(test->getName(), test->getName(), (test->getChildTestCount() > 0 ? TestInfo::flagSubOpen : TestInfo::flagNone)));
		if (test->getChildTestCount() > 0) {
	
			for (int i = 0; i < test->getChildTestCount(); ++i) {
				cppunit_getTests_recurse(dt, test->getChildTestAt(i));
			}

			dt->tests->append(IM::TestInfo(TestInfo::flagSubClose));

		}
	}

	void cppunit_getTests(IM::GetTests* dt) {
		Test* suite = CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest();

		cppunit_getTests_recurse(dt, suite);
	}

	class CppunitTestLogPrinter: public TestListener {
	public:
		std::map<std::string, TestInfo*> tests;

		void  startTest (Test *test) {
			Ctrl->logMsg(DBG_TEST_TITLE, "Test", test->getName().c_str(), "Start");
		}
 
		void  addFailure (const TestFailure &failure) {
			Exception* ex = failure.thrownException();
			SourceLine sl = failure.sourceLine();

			TestInfo* ti = tests[ failure.failedTestName() ];
			std::string info = Stamina::stringf("%s (%d) : %s\r\n%s"
					, sl.fileName().c_str()
					, sl.lineNumber()
					, ex->what()
					, ex->message().details().c_str()
					);
			if (ti) {
				ti->setFlag(TestInfo::flagFailed, true);
				CPPUNIT_NS::Exception* ex = failure.thrownException();
				SourceLine sl = failure.sourceLine();
				ti->info = info;
			}
			Ctrl->logMsg(DBG_TEST_FAILED, "Test", failure.failedTestName().c_str(), info.c_str());


		}
 
		void  endTest (Test *test) {
			Ctrl->logMsg(DBG_TEST, "Test", test->getName().c_str(), "End");
		}

	};

	void cppunit_runTests(IM::RunTests* rt) {
		Test* suite = CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest();

		// Create the event manager and test controller
		CPPUNIT_NS::TestResult controller;

		// Add a listener that colllects test result
		CPPUNIT_NS::TestResultCollector result;
		controller.addListener( &result );        

		CppunitTestLogPrinter testLog;
		controller.addListener( &testLog );


		CPPUNIT_NS::TestRunner runner;
		for (int i = 0; i < rt->tests->size(); ++i) {
			IM::TestInfo & ti = rt->tests->at(i);
			if (ti.getCommand().empty()) continue;
			ti.setFlag(TestInfo::flagFailed, false);
			ti.info = "";

			Test * test;

			try {
				test = suite->findTest(ti.getCommand());
			} catch (...) {
				Ctrl->logMsg(DBG_ERROR, "Test", ti.getCommand().a_str(), "Test doesn't exist!");
				test = 0;
			}

			if (test) {
				testLog.tests[ test->getName() ] = &ti;
				runner.addTest( test );
			}
		}
		
		runner.run( controller );


	}


};

