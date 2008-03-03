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
    // mark as changed
    {
      Contact cnt(id);
      cnt.changed();
    }
    return id;
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
    return (bool) Ctrl->ICMessage(IMC_CNT_INGROUP, getID(), (int) name.a_str());
  }

  bool Contact::inActiveGroup() const {
    return (bool) Ctrl->ICMessage(IMC_CNT_INGROUP, getID());
  }

  bool Contact::remove(bool ask_user) {
    return (bool) Ctrl->ICMessage(IMC_CNT_REMOVE, getID(), ask_user);
  }

  bool Contact::isIgnored() const {
    return (bool) Ctrl->ICMessage(IMC_CNT_IGNORED, getNet(), (int) getUid().a_str());
  }

  bool Contact::exists() const {
    if (getID() == cntNotExist) {
      return false;
    }
    return (bool) Ctrl->ICMessage(IMC_CNT_IDEXISTS, getID());
  }

  void Contact::changed() {
    Ctrl->ICMessage(IMC_CNT_CHANGED, getID());
  }

  bool Contact::ignore() {
    return (bool) Ctrl->ICMessage(IMC_IGN_ADD, getNet(), (int) getUid().a_str());
  }

  void Contact::unignore() {
    Ctrl->ICMessage(IMC_IGN_DEL, getNet(), (int) getUid().a_str());
  }
};