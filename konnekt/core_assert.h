#pragma once

#include <crtdbg.h>

#define K_ASSERT(a) _ASSERTE(a);
#define K_ASSERT_MSG(a, msg) _ASSERTE(a);

#ifdef _DEBUG
  #define K_ASSERT_LOGMSG(a, log) if (!(a)) { IMDEBUG(DBG_ASSERT, log #a " (" __FUNCTION__ " : " __FILE__ ":%d)", __LINE__ ); }
  #define K_ASSERT_LOG(a) K_ASSERT_LOGMSG(a, "Assert failed: ")
#else
  #define K_ASSERT_LOGMSG(a, log) 
  #define K_ASSERT_LOG(a) 
#endif

#define K_CHECK_PTR(ptr) ((int) ptr & 0xFFFF0000)

/*
#ifdef _DEBUG
  #define K_ASSERT_PTR(ptr) K_ASSERT(K_CHECK_PTR(ptr))
#else
  #define K_ASSERT_PTR(ptr) { if (!K_CHECK_PTR(ptr)) { IMDEBUG(DBG_ERROR, "Bad pointer: " #ptr " = %x in " __FUNCTION__, ptr); } }
#endif
*/
