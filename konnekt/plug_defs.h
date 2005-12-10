#pragma once

#include <Stamina/VersionControl.h>

namespace Konnekt {


	typedef void (__stdcall *fApiVersionCompare)(const Stamina::ModuleVersion& v);

	const Stamina::ModuleVersion apiVersion = Stamina::ModuleVersion(Stamina::versionAPI, "Konnekt", Stamina::Version(3,0,0,0));
	STAMINA_REGISTER_VERSION(Konnekt, apiVersion);


	class Controler;

	typedef unsigned int tIMid;
	typedef unsigned int tIMCid;
	typedef unsigned int tIMIid;
	typedef unsigned int tCntId;

	typedef char tTable;

	typedef Stamina::LogLevel enDebugLevel;

	 /** Rodzaj zapisywanej informacji dla Controler::IMDEBUG() */
	const enDebugLevel DBG_NONE = 0;
	const enDebugLevel DBG_NET = 1;
	const enDebugLevel DBG_TRAFFIC = 2;
	const enDebugLevel DBG_DUMP = 4;
	const enDebugLevel DBG_FUNC = 8;
	const enDebugLevel DBG_MISC = 0x10;
	const enDebugLevel DBG_ERROR = 0x20;
	const enDebugLevel DBG_WARN = 0x40;
	const enDebugLevel DBG_ASSERT = 0x80;
	const enDebugLevel DBG_LOG = 0x100;
	const enDebugLevel DBG_DEBUG = 0x1000;
	const enDebugLevel DBG_TEST = 0x10000;
	const enDebugLevel DBG_TEST_FAILED = 0x30000;
	const enDebugLevel DBG_TEST_PASSED = 0x50000;
	const enDebugLevel DBG_TEST_TITLE = 0x70000;
	const enDebugLevel DBG_COMMAND = 0x100000;
	const enDebugLevel DBG_ALL = 0xFF0FFF;


}

using namespace Konnekt;