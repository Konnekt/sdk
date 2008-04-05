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

using Stamina::DT::OldValue;
#define KONNEKT_SDK_NOEXPORT

#include "plug_export.h"
#include "plug.h"
#include "core_assert.h"
#include "ui.h"
#include "plug_func.h"

using namespace Konnekt;


extern "C" __declspec(dllexport) void __stdcall KonnektApiVersions(fApiVersionCompare cmp) {
  using namespace Stamina;

  cmp(iObject::staticClassInfo().getModuleVersion());
  cmp(iSharedObject::staticClassInfo().getModuleVersion());
  cmp(iLockableObject::staticClassInfo().getModuleVersion());
  cmp(Stamina::Lib::version);
  cmp(Konnekt::apiVersion);

  VersionControl * vc = VersionControl::instance();
  for (VersionControl::tModuleList::const_iterator it = vc->begin(); it != vc->end(); ++it) {
    cmp(*it);
  }
}


extern inline int IMessage(tIMid id, tNet net, enIMessageType type, int p1, int p2) {
  return Ctrl->IMessage(id, net, type, p1, p2);
}
extern inline int IMessage(sIMessage_base * msg) {
  return Ctrl->IMessage(msg);
}
extern inline int ICMessage(tIMCid id, int p1, int p2) {
  return Ctrl->ICMessage(id, p1, p2);
}
extern inline int IMessageDirect(tIMid id, tPluginId plug, int p1, int p2) {
  return Ctrl->IMessageDirect(id, plug, p1, p2);
}
extern inline int IMessageDirect(tPluginId plug, sIMessage_base * msg) {
  return Ctrl->IMessageDirect(plug, msg);
}

int iPlugin::IMessageDirect(tIMid id, int p1, int p2) {
  return this->IMessageDirect(Ctrl, &sIMessage_2params(id, p1, p2));
}

int Plug_Init(int p1, int p2) {
  Ctrl = (Controler*) p1;
  return 1;
}

void Plug_Deinit(int p1, int p2) {
  Ctrl = 0;
}

void WMProcess(void) {
  Ctrl->WMProcess();
}


const char * SAFECHAR(const char * ch) {
  return ch ? ch : "";
}


#ifdef __BORLANDC__
  #define VSNPRINTF vsnprintf
#else
  #define VSNPRINTF _vsnprintf
#endif

#ifdef IMLOG_AUTOALLOC
  char * __vsaprintf(const char *format, va_list ap) {
    va_list temp_ap = ap;
    char *buf = NULL, *tmp;
    int size = 0, res;

    if ((size = VSNPRINTF(buf, 0, format, ap)) < 1) {
      size = 128;
      do {
        size *= 2;
        if ((tmp = (char*) realloc(buf, size + 1)) == 0) {
          free(buf);
          return NULL;
        }
        buf = tmp;
        res = VSNPRINTF(buf, size, format, ap);
      } while (res == size - 1 || res= = -1);
    } else {
      if ((buf = (char*) malloc(size + 1))= = 0) {
        return NULL;
      }
    }
    ap = temp_ap;
    VSNPRINTF(buf, size + 1, format, ap);

    return buf;
  }
#endif

#ifndef NO_PLUG_EXPORT
  bool SETSTR(int id, const char * val) {
    OldValue v(Tables::ctypeString); 
    v.vCChar = val;
    return Ctrl->DTset(DTCFG, 0, id, &v);
  }    
  bool SETINT(int id, int val, int mask) {
    OldValue v(Tables::ctypeInt); 
    if (mask != -1) { // maskowanie
      Ctrl->DTget(DTCFG, 0, id, &v);
      v.vInt = (v.vInt & ~mask) | val;
      return Ctrl->DTset(DTCFG, 0, id, &v);
    } else {
      v.vInt = val;
      return Ctrl->DTset(DTCFG, 0, id, &v);
    }
  }  
  
  const char * GETSTR(int id, char * buff, unsigned int size) {
    OldValue v(Tables::ctypeString); 
    v.vChar = buff;
    v.buffSize = size;
    Ctrl->DTget(DTCFG, 0, id, &v);
    return v.vCChar;
  }    
  int GETINT(int id) {
    OldValue v(Tables::ctypeInt); 
    Ctrl->DTget(DTCFG, 0, id, &v); 
    return v.vInt;
  }    
  
  bool SETCNTI(int row, int id, int val, int mask) {
    OldValue v(Tables::ctypeInt); 
    if (mask != -1) { // maskowanie
      Ctrl->DTget(DTCNT, row, id, &v);
      v.vInt = (v.vInt & ~mask) | val;
      return Ctrl->DTset(DTCNT, row, id, &v);
    } else {
      v.vInt = val;
      return Ctrl->DTset(DTCNT, row, id, &v); 
    }
  }
  bool SETCNTI64(int row, int id, __int64 val, __int64 mask) {
    OldValue v(Tables::ctypeInt64); 
    if (mask != -1) { // maskowanie
      Ctrl->DTget(DTCNT, row, id, &v);
      v.vInt64 = (v.vInt64 & ~mask) | val;
      return Ctrl->DTset(DTCNT, row, id, &v);
    } else {
      v.vInt64 = val;
      return Ctrl->DTset(DTCNT, row, id, &v); 
    }
  }
  
  bool SETCNTC(int row, int id, const char * val) {
    OldValue v(Tables::ctypeString); 
    v.vCChar = val;
    return Ctrl->DTset(DTCNT, row, id, &v); 
  }
  int GETCNTI(int row, int id) {
    OldValue v(Tables::ctypeInt); 
    Ctrl->DTget(DTCNT, row, id, &v); 
    return v.vInt;}
  
  __int64 GETCNTI64(int row, int id) {
    OldValue v(Tables::ctypeInt64); 
    Ctrl->DTget(DTCNT, row, id, &v); 
    return v.vInt64;
  }
  
  const char * GETCNTC(int row, int id, char * buff, unsigned int size) {
    OldValue v(Tables::ctypeString); 
    v.vChar = buff;
    v.buffSize = size;
    Ctrl->DTget(DTCNT, row, id, &v); 
    return v.vCChar;
  }


  void IMLOG(const char *format, ...) {
    if (!Ctrl) return;

    va_list ap;
    va_start(ap, format);
    Ctrl->logV(DBG_LOG, 0, 0, format, ap);
    va_end(ap);
  }
  void IMDEBUG(enDebugLevel level, const char *format, ...) {
    if (!Ctrl || !Ctrl->DebugLevel(level)) {
      return;
    }
    va_list ap;
    va_start(ap, format);
    Ctrl->logV(level, 0, 0, format, ap);
    va_end(ap);
  }


  #ifdef _WINDOWS_
    void IMERROR() {  // Windows errors
      if (GetLastError()) {
        #ifdef WINFUNCH
          IMLOG("E[%d] %s", GetLastError(), GetLastErrorMsg());
        #else
          IMLOG("E[%d] ...", GetLastError());
        #endif
      }
    }
  #endif
#endif // NO_PLUG_EXPORT

/*
 * ___________________________________________________
 * konnekt/plug.h
 * ---------------------------------------------------
 */

int UIActionAdd(int _parent, int _id, int _status, const char * _txt, int _p1, short _w, short _h, int _p2, int _param) {
  sUIActionInfo ai = sUIActionInfo(_parent, _id, -1, _status, (char*) _txt, _p1, _w, _h, _p2, _param);
  return ICMessage(IMI_ACTION, (IMPARAM) &ai, 0);
}

extern inline int UIActionInsert(int _parent, int _id, int _pos, int _status, const char * _txt, int _p1, short _w, short _h, int _p2, int _param) {
  return Ctrl->UIActionInsert(_parent, _id, _pos, _status, _txt, _p1, _w, _h, _p2, _param);
}

int Controler::UIActionInsert(int _parent, int _id, int _pos, int _status, const char * _txt , int _p1, short _w, short _h, int _p2, int _param) {
  sUIActionInfo ai = sUIActionInfo(_parent, _id, _pos, _status, (char*) _txt, _p1, _w, _h, _p2, _param);
  return this->ICMessage(IMI_ACTION, (IMPARAM) &ai, 0);
}

int UIActionCfgAdd(int _parent, int _id, int _status, const char * _txt, int _p1, short _x, short _y, short _w, short _h, int _p2, int _param) {
  sUIActionInfo_cfg ai = sUIActionInfo_cfg(_parent, _id, -1, _status, (char*) _txt, _p1, _x, _y, _w, _h, _p2, _param);
  return ICMessage(IMI_ACTION, (IMPARAM) &ai, 0);
}

int UIActionCfgInsert(int _parent, int _id, int _pos, int _status, const char * _txt, int _p1, short _x, short _y, short _w, short _h, int _p2, int _param) {
  sUIActionInfo_cfg ai = sUIActionInfo_cfg(_parent, _id, _pos, _status, (char*) _txt, _p1, _x, _y, _w, _h, _p2, _param);
  return ICMessage(IMI_ACTION, (IMPARAM) &ai, 0);
}

int UIGroupAdd(int _parent, int _id, int _status, const char * _txt, int _p1, short _w, short _h, int _p2, int _param) {
  return UIActionAdd(_parent, _id, _status | ACTS_GROUP, (char*) _txt, _p1, _w, _h, _p2, _param);
}

int UIGroupInsert(int _parent, int _id, int _pos, int _status, const char * _txt , int _p1, short _w, short _h, int _p2, int _param) {
  return UIActionInsert(_parent, _id, _pos, _status | ACTS_GROUP, (char*) _txt, _p1, _w, _h, _p2, _param);
}

int UIActionGetPos(int _parent, int _id) {
  sUIActionInfo ai;
  ai.act = sUIAction(_parent, _id);
  ai.mask = UIAIM_POS;

  ICMessage(IMI_ACTION_GET, (int) &ai, 0);
  return ai.pos;
}

int UIActionSetStatus(sUIAction act, int status, int mask) {
  sUIActionInfo ai;
  ai.act = act;
  ai.mask = UIAIM_STATUS;
  ai.status = status;
  ai.statusMask = mask;

  return ICMessage(IMI_ACTION_SET, (int) &ai, 0);
}
int UIActionGetStatus(sUIAction act) {
  sUIActionInfo ai;
  ai.act = act;
  ai.mask = UIAIM_STATUS;
  ai.statusMask = -1;

  ICMessage(IMI_ACTION_GET, (int) &ai, 0);
  return ai.status;
}

void * UIActionHandle(sUIAction act) {
  sUIActionInfo ai;
  ai.act = act;
  ai.mask = UIAIM_HANDLE;

  ICMessage(IMI_ACTION_GET, (int) &ai, 0);
  return ai.handle;
}

int UIActionCall(sUIActionNotify_base * an) {
  return ICMessage(IMI_ACTION_CALL, (int) an, 0);
}
void * UIActionHandleDirect(sUIAction act) {
  sUIActionNotify_2params an(act, ACTN_SETCNT, AC_CURRENT, 0);
  UIActionCall(&an);
  return (void*) an.notify2;
}

int UIActionSetStatus(int parent, int id, int status, int mask) {
  return UIActionSetStatus(sUIAction(parent, id), status, mask);
}

int UIActionSetText(sUIAction act, const char * txt) {
  sUIActionInfo ai;
  ai.act = act;
  ai.mask = UIAIM_TXT;
  ai.txt = (char *) txt;
  return ICMessage(IMI_ACTION_SET, (int) &ai, 0);
}
int UIActionSetText(int parent, int id, const char * txt) {
  return UIActionSetText(sUIAction(parent, id), txt);
}

int UIActionCfgSetValue(sUIAction act, const char * val, bool convert) {
  sUIActionInfo ai;
  ai.act = act;
  ai.mask = UIAIM_TXT;
  if (convert) {
    ai.mask |= UIAIM_VALUE_CONVERT;
  }
  ai.txt = (char *) val;

  return ICMessage(IMI_ACTION_SETVALUE, (int) &ai, 0);
}
const char * UIActionCfgGetValue(sUIAction act, char * val, int size, bool convert) {
  sUIActionInfo ai;
  ai.act = act;
  ai.mask = UIAIM_TXT;
  if (convert) {
    ai.mask |= UIAIM_VALUE_CONVERT;
  }
  ai.txt = (char *) val;
  ai.txtSize = size;
  ai.txt = (char*) ICMessage(IMI_ACTION_GETVALUE, (int) &ai, 0);

  return ai.txt;
}

int UIActionSet(sUIActionInfo & nfo) {
  return ICMessage(IMI_ACTION_SET, (int) &nfo, 0);
}
int UIActionGet(sUIActionInfo & nfo) {
  return ICMessage(IMI_ACTION_GET, (int) &nfo, 0);
}
void * UIGroupHandle(sUIAction act) {
  return (HANDLE) ICMessage(IMI_GROUP_GETHANDLE, (int) &act, 0);
}

void UIActionCfgAddInfoBox(unsigned int parent, const char * title, const char * info, const char * ico, int height, int icoWidth, int icoHeight) {
  UIActionAdd(parent, 0, ACTT_GROUP,  title);
  {
    UIActionAdd(parent, 0, ACTT_IMAGE | ACTSC_INLINE, ico, 0, icoWidth, icoHeight ? icoHeight : icoWidth);
    UIActionCfgAdd(parent, 0, ACTT_HTMLINFO | ACTSC_FULLWIDTH, info, 0, 4, 0, 300, height);
  }
  UIActionAdd(parent, 0, ACTT_GROUPEND);
}

void UIActionCfgAddInfoBox(unsigned int parent, const char * title, const char * info, unsigned int ico, int height, int icoSize) {
  char buff[32] = {0};
  sprintf_s<32>(buff, "reg://IML%i/%i.ico", icoSize, ico);

  UIActionCfgAddInfoBox(parent, title, info, buff, height, icoSize, icoSize);
}

void UIActionCfgAddPluginInfoBox(unsigned int parent, const char * info, const char * ico, int height, const char * name) {
  UIActionAdd(parent, 0, ACTT_GROUP,  "Informacje o wtyczce");
  {
    if (!name || *name) {
      std::string plugName;
      if (name) {
        plugName = name;
      } else {
        plugName = Ctrl->getPlugin()->getName();
        char ver [50];
        ver[0] = 0;

        ICMessage(IMC_PLUG_VERSION, ICMessage(IMC_PLUGID_POS, Ctrl->ID(), 0), (int) ver);
        if (Ctrl->getError() != errorNoResult) {
          plugName += " ";  
          plugName += ver;
        }
      }
      UIActionAdd(parent, 0, ACTT_COMMENT | ACTSC_BOLD, plugName.c_str());
    }
    if (ico) {
      UIActionAdd(parent, 0, ACTT_IMAGE | ACTSC_INLINE, ico, 0, 16, 16);
    }
    UIActionCfgAdd(parent, 0, ACTT_HTMLINFO | ACTSC_FULLWIDTH, info, 0, 0, 0, 300, height);
  } 
  UIActionAdd(parent, 0, ACTT_GROUPEND);
}

void UIActionCfgAddPluginInfoBox2(unsigned int parent, const char * info, const char * about_info, const char * ico, int height, const char * name, bool frame) {
  if (frame) {
    UIActionAdd(parent, 0, ACTT_GROUP,  "");
  }
  {
    std::string tip;
    if (!name || *name) {
      if (name) {
        tip = name;
      } else {
        tip = Ctrl->getPlugin()->getName();
        char ver [50];
        ver[0] = 0;

        ICMessage(IMC_PLUG_VERSION, ICMessage(IMC_PLUGID_POS, Ctrl->ID(), 0), (int) ver);
        if (Ctrl->getError() != errorNoResult) {
          tip += " ";  
          tip += ver;
        }
      }
    }
    if (!tip.empty()) {
      tip = "<b>" + tip + "</b><br/>";
    }
    if (about_info) {
      tip += about_info;
    }
    std::string txt;
    if (ico) {
      txt = SetActParam(txt, AP_IMGURL, ico);
      if (!ActParamExists(txt, AP_ICONSIZE)) {
        txt = SetActParam(txt, AP_ICONSIZE, "32");
      }
    }
    txt = SetActParam(txt, AP_TIPRICH, tip);
    txt = SetActParam(txt, AP_TIPRICH_WIDTH, "300");

    UIActionAdd(parent, 0, ACTT_TIPBUTTON | ACTSC_INLINE, txt.c_str(), 0, 40, 40);
    UIActionCfgAdd(parent, 0, ACTT_HTMLINFO | ACTSC_FULLWIDTH, info, 0, 0, 0, 300, height);
  }
  if (frame) {
    UIActionAdd(parent, 0, ACTT_GROUPEND);
  }
}


int IconRegister(IML_enum target, int ID, const char * URL) {
  sUIIconRegister ir;
  ir.URL = URL;
  ir.ID = ID;
  ir.target = target;
  ICMessage(IMI_ICONREGISTER, (int) &ir, 0);
  return ID;
}
int IconRegister(IML_enum target, int ID, HINSTANCE inst, int icoID, int type) {
  sUIIconRegister ir;
  ir.ID = ID;
  ir.target = target;
  ir.imgInst = inst;
  ir.imgId = icoID;
  ir.imgType = type;
  ICMessage(IMI_ICONREGISTER, (int) &ir, 0);
  return ID;
}
int IconRegister(IML_enum target, int ID, HANDLE image, int type) {
  sUIIconRegister ir;
  ir.ID = ID;
  ir.target = target;
  ir.imgHandle = image;
  ir.imgType = type;
  ICMessage(IMI_ICONREGISTER, (int) &ir, 0);
  return ID;
}
int IconRegisterList(IML_enum target, int count, int * IDList, HANDLE image, HANDLE mask, int w ) {
  sUIIconRegisterList irl;
  irl.target = target;
  irl.count = count;
  irl.idList = IDList;
  irl.imgBmp = image;
  irl.maskBmp = mask;
  irl.w = w;
  return ICMessage(IMI_ICONREGISTERLIST, (int) &irl, 0);
}

#ifdef _INC_COMMCTRL
  int IconRegisterList(IML_enum target, int count, int * IDList, HIMAGELIST ImageList) {
    sUIIconRegisterList irl;
    irl.target = target;
    irl.count = count;
    irl.idList = IDList;
    irl.ImageList = ImageList;
    return ICMessage(IMI_ICONREGISTERLIST, (int) &irl, 0);
  }
#endif

bool GetExtParam(const char * ext, const char * name, char * valueBuff, size_t buffSize) {
  *valueBuff = 0;
  if (!*name) {
    return false;
  }

  // To, czego chcemy szukaæ
  size_t nameLen = strlen(name);
  char * find = new char[nameLen + 3];
  strcpy(find + 1, name);
  find[0] = EXT_PARAM_CHAR;
  strcpy(find + nameLen + 1, "=\0");

  // Znajdujemy parametr
  const char * start = strstr(ext, find);
  size_t size = 0;
  delete [] find;
  if (!start) {
    return false;
  }
  start += nameLen + 2;

  // Kopiujemy wartoœæ
  while (*start && *start != EXT_PARAM_CHAR && size < buffSize - 1) {
    *valueBuff = *start;
    valueBuff++;
    start++;
    size++;
  }

  *valueBuff = 0;
  return true;
}

bool SetExtParam(const char * ext, const char * name, const char * value, char * extBuff, size_t buffSize) {
  if (!*name) {
    return false;
  }
  size_t nameLen = strlen(name);
  size_t extLen = strlen(ext);
  size_t valueLen = strlen(value);

  // To, czego chcemy szukac
  char * find = new char[nameLen + 3];
  strcpy(find + 1, name);
  find[0] = EXT_PARAM_CHAR;
  strcpy(find + nameLen + 1, "=\0");

  // Znajdujemy parametr
  const char * start = strstr(ext, find);
  // Sprawdzamy, czy to co nam powstanie, w ogole zmiesci sie w pamieci.
  if (!start && buffSize < extLen + nameLen + valueLen + 3) {
    return false;
  }
  // Kopiujemy to, co i tak nie zostanie zmienione. Jezeli ext i extBuff to to samo - nie ma sensu kopiowac.
  // Nie kopiujemy calej czesci ze zmieniana wartoscia - ona powedruje na koniec...
  if (ext != extBuff) {
    strncpy(extBuff, ext, min(start ? (start - ext) : extLen, buffSize));
  }
  const char * end = start ? strchr(start + 1, EXT_PARAM_CHAR) : 0;
  // Kopiujemy reszte parametrow
  if (end) {
    strncpy(extBuff + (start - ext), end, buffSize - (start - ext));
  }
  // Teraz mozemy dopiero zapisac nasz nowy parametr
  extLen = strlen(extBuff);
  if (buffSize < extLen + nameLen + valueLen + 3) {
    return false;
  }
  strcpy(extBuff + extLen, find); // Zapisujemy nazwe
  strcpy(extBuff + extLen + nameLen + 2, value);

  delete [] find;
  return true;
}

#ifdef _STRING_
  std::string GetExtParam(const std::string ext, const std::string name) {
    if (name.empty()) {
      return "";
    }
    size_t start = ext.find(EXT_PARAM_CHAR + name + "="); // Znajdujemy parametr
    if (start == ext.npos) {
      return "";
    }
    start += name.length() + 2;
    size_t end = ext.find(EXT_PARAM_CHAR, start); // Znajdujemy koniec wartosci

    return ext.substr(start, (end == ext.npos) ? end : end - start); // Zwracamy kopie
  }

  std::string SetExtParam(const std::string ext, const std::string name, const std::string value) {
    if (name.empty()) {
      return ext;
    }
    size_t start = ext.find(EXT_PARAM_CHAR + name + "="); // Znajdujemy parametr
    size_t end = (start == ext.npos) ? ext.npos : ext.find(EXT_PARAM_CHAR, start + 1); // Znajdujemy koniec wartosci

    return ext.substr(0, start) + EXT_PARAM_CHAR + name + "=" + value + ((end != ext.npos) ? ext.substr(end) : "");
  }

  bool ParamSpecialChar(unsigned char ch) {
    return ch < 8 || ch == EXT_PARAM_CHAR;
  }

  std::string GetActParam(const std::string & txt, const std::string & param) {
    size_t start = txt.find(AP_PARAMS);
    if (start == txt.npos) {
      start = 0;
    }
    if (!param.empty()) {
      start = txt.find(param, start); // Znajdujemy parametr
      if (start == txt.npos) {
        return "";
      }
      start = start + param.size();
    } 
    size_t end = start;
    if (param.empty()) {
      start = 0;
    }
    while (end < txt.length() && !ParamSpecialChar(txt[end])) {
      end++;
    }
    // Znajdujemy koniec wartosci (znka < 32)
    return txt.substr(start, (end >= txt.length()) ? txt.npos : end - start); // Zwracamy kopie
  }

  bool ActParamExists(const std::string & txt, const std::string & param) {
    if (param.empty()) {
      if (txt.length() > 0) {
        return !ParamSpecialChar(txt[0]);
      }
      return true;
    }
    return txt.find(param) != txt.npos;
  }

  std::string SetActParam(const std::string & txt, const std::string & param, const std::string & value) {
    size_t start = txt.find(AP_PARAMS);
    if (start == txt.npos) {
      start = 0;
    }
    if (!param.empty()) {
      start = txt.find(param, start); // Znajdujemy parametr
    }
    size_t end = start;
    if (param.empty()) {
      start = 0;
    }
    while (end != txt.npos && end < txt.length() && !ParamSpecialChar(txt[end])) {
      end++;
    }
    return txt.substr(0, start) + param + value + ((end != txt.npos) ? txt.substr(end) : "");
  }

#endif


int CntSetStatus(unsigned int cntID, unsigned int status, const char * info) {
  return Ctrl->IMessage(&sIMessage_StatusChange(IMC_CNT_SETSTATUS, cntID, status, info));
}
int PlugStatusChange(unsigned int status, const char * info) {
  return Ctrl->IMessage(&sIMessage_StatusChange(IMC_STATUSCHANGE, 0, status, info));
}

void CntSetInfoValue(bool toWindow, int cntID, int colID, const char * value) {
  if (!toWindow) {
    Ctrl->DTsetStr(DTCNT, cntID, colID, value);
    return;
  }
  UIActionCfgSetValue(sUIAction(
    ICMessage(IMI_ACTION_FINDPARENT, (int) &sUIAction(IMIG_NFO, colID | IMIB_CNT), 0),
    colID | IMIB_CNT, cntID), value, true
  );
}
const char * CntGetInfoValue(bool fromWindow, int cntID, int colID) {
  if (!fromWindow) {
    return Ctrl->DTgetStr(DTCNT, cntID, colID, 0, 0);
  }
  return UIActionCfgGetValue(sUIAction(
    ICMessage(IMI_ACTION_FINDPARENT, (int) &sUIAction(IMIG_NFO, colID | IMIB_CNT), 0),
    colID | IMIB_CNT, cntID), 0, 0, true
  );
}


bool ShowBits::checkBits(ShowBits::enShowBits show) {
  return (getAllBits() & (int) show) == show;
}
ShowBits::enShowBits ShowBits::getBits(int bits) {
  return (ShowBits::enShowBits) ((getAllBits() & bits) & ~ShowBits::levelFull);
}

bool ShowBits::checkLevel(ShowBits::enLevel level) {
  return (getAllBits() & (int) level) == level;
}
ShowBits::enLevel ShowBits::getLevel() {
  return (ShowBits::enLevel) (getAllBits() & ShowBits::levelFull);
}

unsigned int ShowBits::getAllBits() {
  OldValue v(Tables::ctypeInt); 
  if (Ctrl->DTget(DTCFG, 0, CFG_SHOWBITS, &v)) {
    return v.vInt;
  }
  return 0xFFFFFFFF;
}


/*
 * ---------------------------------------------------------
 */

void testResult(const StringRef& title, int should, int got, bool swap) {
  bool failed = (should != got);
  if (swap) {
    failed = !failed;
  }
  if (failed) {
    IMDEBUG(DBG_TEST_FAILED, "%s Failed - %x != %x", title.a_str(), got, should);
  } else {
    IMDEBUG(DBG_TEST_PASSED, "%s Passed - %x", title.a_str(), got);
  }
}
void testResult(const StringRef& title, const StringRef& should, const StringRef& got, bool swap) {
  bool failed = (should != got);
  if (swap) {
    failed = !failed;
  }
  if (failed) {
    IMDEBUG(DBG_TEST_FAILED, "%s Failed - \"%s\" != \"%s\"", title.a_str(), got.a_str(), should.a_str());
  } else {
    IMDEBUG(DBG_TEST_PASSED, "%s Passed - \"%s\"", title.a_str(), got.a_str());
  }
}

bool sIMessage_plugArgs::argEq(unsigned int i, const char * cmp) {
  if (this->argc <= i) {
    return -2;
  }
  return _stricmp(this->argv[i], cmp) == 0;
}
