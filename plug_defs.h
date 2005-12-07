#pragma once

#include <Stamina/VersionControl.h>

namespace Konnekt {


	typedef void (__stdcall *fApiVersionCompare)(const Stamina::ModuleVersion& v);

	const Stamina::ModuleVersion apiVersion = Stamina::ModuleVersion(Stamina::versionAPI, "Konnekt", Stamina::Version(3,0,0,0));
	STAMINA_REGISTER_VERSION(Konnekt, apiVersion);




	typedef unsigned int tIMid;
	typedef unsigned int tIMCid;
	typedef unsigned int tIMIid;
	typedef unsigned int tCntId;

	typedef char tTable;


	 /** Rodzaj zapisywanej informacji dla cCtrl::IMDEBUG() */
	 enum enDebugLevel {
		DBG_NONE = 0,
		DBG_NET = 1,
		DBG_TRAFFIC = 2 , 
		DBG_DUMP = 4 , 
		DBG_FUNC = 8 , 
		DBG_MISC = 0x10 ,
		DBG_ERROR = 0x20 , 
		DBG_WARN = 0x40 ,
		DBG_ASSERT = 0x80 ,
		DBG_LOG = 0x100 ,
		DBG_DEBUG = 0x1000 ,
		DBG_TEST = 0x10000 ,
		DBG_TEST_FAILED = 0x30000 , 
		DBG_TEST_PASSED = 0x50000 , 
		DBG_TEST_TITLE = 0x70000 , 
		DBG_COMMAND = 0x100000 , 
		DBG_ALL = 0xFF0FFF

	 };


}

using namespace Konnekt;