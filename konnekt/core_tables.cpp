#include <stdlib.h>
#include "konnekt/plug_export.h"
#include "konnekt/core_tables.h"
#include "konnekt/core_assert.h"

using namespace Konnekt;
using namespace Stamina;
using namespace Tables;

Tables::tTableId Tables::getTableId(const StringRef& tableName) {
	return (tTableId)Unique::getId(Unique::domainTable, tableName);
}


String Tables::iTable::getTableName() {
	TableLocker(this);
	return Unique::getName(Unique::domainTable, this->getTableId());
}


Tables::oTable Tables::registerTable(Controler * ctrl, Tables::tTableId tableId, const StringRef& name, enTableOptions tableOpts) {
	if (!ctrl) ctrl = Ctrl;
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



DT::oColumn Tables::iTable::setColumn(Tables::tColId id , Tables::tColType type, const StringRef& name) {
	return this->setColumn(Ctrl, id , type , name);
}

inline oColumn iTable::setColumn(Controler* plugin, const Stamina::StringRef& name, tColType type) {
	return this->setColumn(plugin, colByName, type, name);
}

inline oColumn iTable::setColumn(const Stamina::StringRef& name, tColType type) {
	return this->setColumn(Ctrl, name, type);
}



