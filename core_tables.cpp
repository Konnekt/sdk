#include <stdlib.h>
#include "konnekt/core_tables.h"

using namespace Konnekt;

Tables::tTableId Tables::getTableId(const StringRef& tableName) {
	return (tTableId)Unique::getId(Unique::domainTable, tableName);
}


String Tables::iTable::getTableName() {
	TableLocker(this);
	return Unique::getName(Unique::domainTable, this->getTableId());
}


Tables::oTable Tables::registerTable(cCtrl * ctrl, Tables::tTableId tableId, const StringRef& name, enTableOptions tableOpts) {
	if (!ctrl) ctrl = Ctrl;
	if (tableId == Tables::tableNotFound && name && *name) {
		tableId = (tTableId) Unique::registerName(Unique::domainTable, name);
	} else if (name && *name) {
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


DT::oColumn Tables::iTable::setColumn(Tables::tColId id , Tables::tColType type, const char * name) {
	return this->setColumn(Ctrl->getPlugin(), id , type , name);
}



