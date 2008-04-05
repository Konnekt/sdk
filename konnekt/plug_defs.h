#pragma once

#include <Stamina/VersionControl.h>
#include <Stamina/Logger.h>

namespace Konnekt {
  typedef void (__stdcall *fApiVersionCompare)(const Stamina::ModuleVersion& v);
  typedef int (__stdcall *fIMessageProc)(struct sIMessage_base * msg);

  const Stamina::ModuleVersion apiVersion = Stamina::ModuleVersion(Stamina::versionAPI, "KonnektAPI", Stamina::Version(3,0,0,0));
  STAMINA_REGISTER_VERSION(Konnekt, apiVersion);

  const unsigned int sdkVersion = 3;
  const unsigned int coreVersion = 0;
  const unsigned int uiVersion = (int) "W98";

  class Controler;

  typedef unsigned int tIMid;
  typedef unsigned int tIMCid;
  typedef unsigned int tIMIid;
  typedef unsigned int tCntId;
  typedef unsigned int tAccountId;

  typedef char tTable;

  typedef Stamina::LogLevel enDebugLevel;

  /** 
   * Rodzaj zapisywanej informacji dla Controler::IMDEBUG() 
   */
  const enDebugLevel DBG_NONE = Stamina::logNone;
  const enDebugLevel DBG_NET = Stamina::logNet;
  const enDebugLevel DBG_TRAFFIC = Stamina::logTraffic;
  const enDebugLevel DBG_DUMP = Stamina::logDump;
  const enDebugLevel DBG_FUNC = Stamina::logFunc;
  const enDebugLevel DBG_MISC = Stamina::logMisc;
  const enDebugLevel DBG_ERROR = Stamina::logError;
  const enDebugLevel DBG_WARN = Stamina::logWarn;
  const enDebugLevel DBG_ASSERT = Stamina::logAssert;
  const enDebugLevel DBG_LOG = Stamina::logLog;
  const enDebugLevel DBG_DEBUG = Stamina::logDebug;
  const enDebugLevel DBG_TEST = (enDebugLevel) 0x1000000;
  const enDebugLevel DBG_TEST_FAILED = (enDebugLevel) 0x2000000;
  const enDebugLevel DBG_TEST_PASSED = (enDebugLevel) 0x3000000;
  const enDebugLevel DBG_TEST_TITLE = (enDebugLevel) 0x4000000;
  const enDebugLevel DBG_COMMAND = (enDebugLevel) 0x5000000;
  const enDebugLevel DBG_SPECIAL = (enDebugLevel) 0xF000000;
  const enDebugLevel DBG_ALL = (enDebugLevel) 0xFF0FFF;
}

using namespace Konnekt;