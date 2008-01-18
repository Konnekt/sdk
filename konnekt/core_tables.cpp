#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT 0x0500

#include <Stamina/Stamina.h>

#include <stdlib.h>
#include "plug_export.h"
#include "core_tables.h"
#include "core_assert.h"

using namespace Konnekt;
using namespace Stamina;
using namespace Tables;

Tables::tTableId Tables::getTableId(const StringRef& tableName) {
  return (tTableId) Unique::getId(Unique::domainTable, tableName);
}

String Tables::iTable::getTableName() {
  TableLocker(this);
  return Unique::getName(Unique::domainTable, this->getTableId());
}

Tables::oTable Tables::registerTable(Controler * ctrl, Tables::tTableId tableId, const StringRef& name, enTableOptions tableOpts) {
  if (!ctrl) ctrl = Ctrl;
  S_ASSERT(ctrl != 0);

  if (tableId == Tables::tableNotFound && name.empty() == false) {
    tableId = (tTableId) Unique::registerName(Unique::domainTable, name);
  } else if (name.empty() == false) {
    Unique::registerId(Unique::domainTable, tableId, name);
  }

  IM::RegisterTable rt(tableId, tableOpts);
  int registerTableSuccess = ctrl->IMessage(&rt);
  K_ASSERT(registerTableSuccess);

  return rt.table;
}

void Tables::oTable::setById(Tables::tTableId tableId) {
  this->set(Ctrl->getTable(tableId));
}

DT::oColumn Tables::iTable::setColumn(Tables::tColId id, Tables::tColType type, const StringRef& name) {
  return this->setColumn(Ctrl, id, type, name);
}

oColumn iTable::setColumn(Controler* plugin, const Stamina::StringRef& name, tColType type) {
  return this->setColumn(plugin, colByName, type, name);
}

oColumn iTable::setColumn(const Stamina::StringRef& name, tColType type) {
  return this->setColumn(Ctrl, name, type);
}
