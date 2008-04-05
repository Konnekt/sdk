#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT 0x0500

#include <Stamina/Stamina.h>
#include <stdio.h>
#include <stdarg.h>
#include <windows.h>
#include <commctrl.h>
#include <string>

#include <Stamina/Lib.h>
#include <Stamina/DataTable/DTDeprecated.h>

#include "plug.h"
#include "core_assert.h"

#include "ui.h"
#include "plug_func.h"

Controler * Ctrl = 0;

using namespace Konnekt;
using Stamina::DT::OldValue;

int Controler::IMessage(tIMid id, tNet net, enIMessageType type, int p1, int p2) {
  return (this->IMessage)(&sIMessage (id, net, type, p1, p2));
}
int Controler::IMessage(sIMessage_base * msg) {
  return this->IMessage(msg);
}
int Controler::ICMessage(tIMCid id, int p1, int p2) {
  return (this->IMessage)(&sIMessage (id, Net::none, imtNone, p1, p2));
}
int Controler::IMessageDirect(tIMid id, tPluginId plug, int p1, int p2) {
  if (!plug) {
    plug = this->ID();
  }
  return (this->IMessageDirect)(plug, &sIMessage (id, Net::none, imtNone, p1, p2));
}


int Controler::DTgetInt(tTable db, unsigned int row, const char * name) {
  return this->DTgetInt(db, row, this->DTgetNameID(db, name));
}
bool Controler::DTsetInt(tTable db, unsigned int row, const char * name, int value, int mask) {
  return this->DTsetInt(db, row, this->DTgetNameID(db, name), value, mask);
}
char * Controler::DTgetStr(tTable db, unsigned int row, const char * name, char * buff, unsigned int size) {
  return this->DTgetStr(db, row, this->DTgetNameID(db, name), buff, size);
}
bool Controler::DTsetStr(tTable db, unsigned int row, const char * name, const char * value) {
  return this->DTsetStr(db, row, this->DTgetNameID(db, name), value);
}
__int64 Controler::DTgetInt64(tTable db, unsigned int row, const char * name) {
  return this->DTgetInt64(db, row, this->DTgetNameID(db, name));
}
bool Controler::DTsetInt64(tTable db, unsigned int row, const char * name, __int64 value, __int64 mask) {
  return this->DTsetInt64(db, row, this->DTgetNameID(db, name), value, mask);
}


int Controler::DTgetInt(tTable db, unsigned int row, unsigned int col) {
  OldValue v(Tables::ctypeInt);
  DTget(db, row, col, &v); 
  return v.vInt;
}
bool Controler::DTsetInt(tTable db, unsigned int row, unsigned int col, int val, int mask) {
  OldValue v(Tables::ctypeInt);
  if (mask != -1) { // maskowanie
    DTget(db, row, col, &v);
    v.vInt = (v.vInt & ~mask) | val;
    return DTset(db, row, col, &v);
  } else {
    v.vInt = val;
    return DTset(db, row, col, &v); 
  }
}
char * Controler::DTgetStr(tTable db, unsigned int row, unsigned int col, char * buff, unsigned int size) {
  OldValue v(Tables::ctypeString);
  v.vChar = buff;
  v.buffSize = size;
  DTget(db, row, col, &v); 
  return v.vChar;
}
bool Controler::DTsetStr(tTable db, unsigned int row, unsigned int col, const char * val) {
  OldValue v(Tables::ctypeString); 
  v.vCChar = val;
  return DTset(db, row, col, &v); 
}
__int64 Controler::DTgetInt64(tTable db, unsigned int row, unsigned int col) {
  OldValue v(Tables::ctypeInt64); 
  DTget(db, row, col, &v); 
  return v.vInt64;
}
bool Controler::DTsetInt64(tTable db, unsigned int row, unsigned int col, __int64 val, __int64 mask) {
  OldValue v(Tables::ctypeInt64); 
  if (mask != -1) { // maskowanie
    DTget(db, row, col, &v);
    v.vInt64 = (v.vInt64 & ~mask) | val;
    return DTset(db, row, col, &v);
  } else {
    v.vInt64 = val;
    return DTset(db, row, col, &v); 
  }
}


void Controler::IMLOG(const char *format, ...) {
  if (!this) return;

  va_list ap;
  va_start(ap, format);
  this->logV(DBG_LOG, 0, 0, format, ap);
  va_end(ap);
}
void Controler::IMDEBUG(enDebugLevel level, const char *format, ...) {
  if (!this || !this->DebugLevel(level)) {
    return;
  }
  va_list ap;
  va_start(ap, format);
  this->logV(level, 0, 0, format, ap);
  va_end(ap);
}


void Controler::log(enDebugLevel level, const char* module, const char* where, const char *format, ...) {
  if (!this || !this->DebugLevel(level)) {
    return;
  }
  va_list ap;
  va_start(ap, format);
  this->logV(level, module, where, format, ap);
  va_end(ap);
}
void Controler::logV(enDebugLevel level, const char* module, const char* where, const char *format, va_list p) {
  if (!this || !this->DebugLevel(level)) {
    return;
  }
  int size = _vscprintf(format, p);
  char * buff = new char [size + 2];
  buff[size + 1] = 0;
  /// @todo 'size + 2' argument here is ok ?
  size = _vsnprintf_s(buff, size + 2, size + 1, format, p);
  buff[size] = 0;
  this->logMsg(level, module, where, buff);
  delete [] buff;
}


int Controler::BeginThreadAndWait(const char * name, void *security, unsigned stack_size, Controler::fBeginThread start_address,  void *arglist, unsigned initflag, unsigned *thrdaddr) {
  HANDLE th = (HANDLE) this->BeginThread(name, security, stack_size, start_address, arglist, CREATE_SUSPENDED | initflag, thrdaddr);
  if (!th) return 0;

  ResumeThread(th);
  /* 
  while (MsgWaitForMultipleObjectsEx(1, &th, 250, QS_ALLINPUT | QS_ALLPOSTMESSAGE, MWMO_ALERTABLE | MWMO_INPUTAVAILABLE) - WAIT_OBJECT_0 != 0) {
    this->WMProcess();
    // SleepEx(0, true); // metoda, która mo¿e pomo¿e przy problemach z W98. Pomog³a ju¿ kiedyœ...
  }
  */
  while (WaitForSingleObjectEx(th, 10, TRUE) != WAIT_OBJECT_0) {
    this->WMProcess();
  }
  DWORD ret = 0;
  GetExitCodeThread(th, &ret);
  CloseHandle(th);  
  return ret;
}

// -- plug_func.h

int Controler::SetColumn(tTable table, int id, int type, int def, const char * name) {
  return this->IMessage(&sIMessage_setColumn(table, id, type, def, name));
}
int SetColumn(tTable table, int id, int type, int def, const char * name) {
  return Ctrl->SetColumn(table, id, type, def, name);
}
