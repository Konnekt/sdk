#include <Stamina/Stamina.h>

#include <stdlib.h>

#include "plug_export.h"
#include "core_tables.h"
#include "core_account.h"

namespace Konnekt {
  Account Account::create(tNet net, const StringRef& display) {
    tCntId id = (tCntId) Ctrl->ICMessage(IM::imcAccountAdd, net, (int) display.a_str());

    if (id == -1) {
      throw ExceptionString("Account name is using or net is empty");
    }
    return id;
  }

  Account Account::find(tNet net, const StringRef& uid) {
    tAccountId id = (tCntId) Ctrl->ICMessage(IM::imcFindAccount, net, (int) uid.a_str());

    if (id == accountNotExist) {
      throw ExceptionString("Account does not exist");
    }
    return id;
  }
  Account Account::find(const StringRef& display) {
    tAccountId id = (tCntId) Ctrl->ICMessage(IM::imcFindAccount, -1, (int) display.a_str());

    if (id == accountNotExist) {
      throw ExceptionString("Account does not exist");
    }
    return id;
  }

  bool Account::exists(tNet net, const StringRef& uid) {
    return Ctrl->ICMessage(IM::imcFindAccount, net, (int) uid.a_str()) != accountNotExist;
  }

  bool Account::exists(const StringRef& display) {
    return Ctrl->ICMessage(IM::imcFindAccount -1, (int) display.a_str()) != accountNotExist;
  }

  bool Account::remove() {
    return (bool) Ctrl->ICMessage(IM::imcAccountRemove, getID());
  }

  bool Account::exists() const {
    if (getID() == accountNotExist) {
      return false;
    }
    return (bool) Ctrl->ICMessage(IM::imcAccountIdExist, getID());
  }

  void Account::changed() {
    Ctrl->ICMessage(IM::imcAccountChanged, getID());
  }
};