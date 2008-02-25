#include <Stamina/Stamina.h>

#include <stdlib.h>

#include "plug_export.h"
#include "core_tables.h"
#include "core_contact.h"

namespace Konnekt {
  Contact Contact::create(tNet net, const StringRef& uid) {
    tCntId id = (tCntId) Ctrl->ICMessage(IMC_CNT_ADD, net, (int) uid.a_str());

    if (id == -1) {
      throw ExceptionString("Contact already exists");
    }

    Contact cnt(id);
    cnt.changed();

    return cnt;
  }

  Contact Contact::find(tNet net, const StringRef& uid) {
    tCntId id = (tCntId) Ctrl->ICMessage(IMC_FINDCONTACT, net, (int) uid.a_str());

    if (id == cntNotExist) {
      throw ExceptionString("Contact does not exist");
    }
    return id;
  }

  bool Contact::exists(tNet net, const StringRef& uid) {
    return Ctrl->ICMessage(IMC_FINDCONTACT, net, (int) uid.a_str()) != cntNotExist;
  }

  bool Contact::inGroup(const StringRef& name) const {
    return Ctrl->ICMessage(IMC_CNT_INGROUP, getID(), (int) name.a_str()) == 1;
  }

  bool Contact::inActiveGroup() const {
    return Ctrl->ICMessage(IMC_CNT_INGROUP, getID()) == 1;
  }

  bool Contact::remove(bool ask_user) {
    return Ctrl->ICMessage(IMC_CNT_REMOVE, getID(), ask_user) == 1;
  }

  bool Contact::isIgnored() const {
    return Ctrl->ICMessage(IMC_CNT_IGNORED, getNet(), (int) getUid().a_str()) == 1;
  }

  bool Contact::exists() const {
    if (getID() == cntNotExist) {
      return false;
    }
    return Ctrl->ICMessage(IMC_CNT_IDEXISTS, getID()) == 1;
  }

  void Contact::changed() {
    Ctrl->ICMessage(IMC_CNT_CHANGED, getID());
  }

  void Contact::ignore() {
    Ctrl->ICMessage(IMC_IGN_ADD, getNet(), (int) getUid().a_str());
  }

  void Contact::unignore() {
    Ctrl->ICMessage(IMC_IGN_DEL, getNet(), (int) getUid().a_str());
  }
};