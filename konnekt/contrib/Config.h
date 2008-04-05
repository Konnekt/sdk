/**
  *  @file
  *  Configuration class
  *
  *  Licensed under The GNU Lesser General Public License
  *  Redistributions of files must retain the above copyright notice.
  *
  *  @author        Sijawusz Pur Rahnama <sija@gibbon.pl>
  *  @license       http://creativecommons.org/licenses/LGPL/2.1/
  */

#pragma once

#ifndef __KONNEKT_CONFIG_H__
#define __KONNEKT_CONFIG_H__

#include "Events/IMessageDispatcher.h"
#include "Events/IMEvent.h"

using namespace Konnekt::Tables;
using namespace Stamina;
using namespace boost;

namespace Konnekt {
  class Config : public SharedObject<iSharedObject>, public signals::trackable {
  public:
    /**
     * Class version macro
     */
    STAMINA_OBJECT_CLASS_VERSION(Config, iSharedObject, Version(0,3,0,0));

  public:
    class Item {
    public:
      Item(tTable table, tColId col, tRowId row = 0): _table(table), _col(col), _row(row) { }

    public:
      inline operator String () const {
        return to_s();
      }

    public:
      inline Item& operator << (const Item& value) {
        set(value);
        return *this;
      }

      inline Item& operator << (const StringRef& value) {
        set(value);
        return *this;
      }

      template <typename T>
      inline Item& operator << (T value) {
        set(value);
        return *this;
      }

    public:
      inline tColId getID() const {
        return _col;
      }

      inline int getTable() const {
        return _table;
      }

      inline tRowId getRow() const {
        return _row;
      }

    public:
      inline tColType getType() const {
        return (tColType) Ctrl->DTgetType(_table, _col);
      }

      inline string getName() const {
        return Ctrl->DTgetName(_table, _col);
      }

    public:
      inline int to_i(tRowId row) const {
        return Ctrl->DTgetInt(_table, row, _col);
      }
      inline int to_i() const {
        return to_i(getRow());
      }

      inline __int64 to_i64(tRowId row) const {
        return Ctrl->DTgetInt64(_table, row, _col);
      }
      inline __int64 to_i64() const {
        return to_i64(getRow());
      }

      inline String to_s(tRowId row) const {
        return Ctrl->DTgetStr(_table, row, _col);
      }
      inline String to_s() const {
        return to_s(getRow());
      }

    public:
      inline bool set(const Item& value, tRowId row) {
        switch (value.getType()) {
          case ctypeInt:
            return set(value.to_i(), row);
          case ctypeInt64:
            return set(value.to_i64(), row);
          case ctypeString:
            return set(value.to_s(), row);
          default:
            return false;
        }
        return true;
      }

      inline bool set(int value, tRowId row) {
        return Ctrl->DTsetInt(_table, row, _col, value);
      }
      inline bool set(__int64 value, tRowId row) {
        return Ctrl->DTsetInt64(_table, row, _col, value);
      }
      inline bool set(const StringRef& value, tRowId row) {
        return Ctrl->DTsetStr(_table, row, _col, value.a_str());
      }

      inline bool set(const Item& value) {
        return set(value, getRow());
      }
      inline bool set(const StringRef& value) {
        return set(value, getRow());
      }

      template <typename T>
      inline bool set(T value) {
        return set(value, getRow());
      }

    protected:
      tTable _table;
      tColId _col;
      tRowId _row;
    };

  public:
    /**
     * Gets configuration item.
     *
     * @param table table id
     * @param col   column id
     * @param row   row id
     */
    static Item get(tTable table, tColId col, tRowId row) {
      return Item(table, col, row);
    }
    /**
     * Gets configuration item from global configuration table.
     *
     * @param col column id
     */
    static Item get(tColId col) {
      return get(tableConfig, col, 0);
    }
    /**
     * Gets configuration item from contact table.
     *
     * @param col column id
     * @param cnt contact id
     */
    static Item get(tColId col, tCntId cnt) {
      return get(tableContacts, col, cnt);
    }

  public:
    typedef std::deque<sIMessage_setColumn*> tColumns;

  public:
    /**
     * Creates new instance of Config class with column registration listeners attached.
     */
    inline Config(IMessageDispatcher& dispatcher) {
      attachListeners(dispatcher);
    }
    inline Config() { }

    inline ~Config() { 
      for (tColumns::iterator it = _cols.begin(); it != _cols.end(); ++it) {
        delete *it;
      }
    }

  public:
    /**
     * Connects listeners to the #IM_SETCOLS IMessage id.
     *
     * @see setColumn
     */
    inline void attachListeners(IMessageDispatcher& dispatcher) {
      dispatcher.connect(IM_SETCOLS, bind(&Config::_registerColumns, this, _1));
    }

    /**
     * Registers column in the given table.
     *
     * @param table   Table id
     * @param id      Column id
     * @param type    Column type
     * @param def     Column default value
     * @param name    Column name
     */
    inline void setColumn(tTable table, tColId id, int type, const char* def, const char* name) {
      _cols.push_back(new sIMessage_setColumn(table, id, type, def, name));
    }
    /**
     * @sa setColumn
     */
    inline void setColumn(tTable table, tColId id, int type, int def, const char* name) {
      _cols.push_back(new sIMessage_setColumn(table, id, type, def, name));
    }

    /**
     * Sets all registered columns to their's default values.
     *
     * @param table Table id to reset
     */
    inline void resetColumns(tTable table) {
      int count = 0;
      if (_cols.empty() || !(count = Ctrl->DTgetCount(table))) {
        return;
      }
      for (tColumns::iterator it = _cols.begin(); it != _cols.end(); ++it) {
        if ((*it)->_table == table) {
          for (int i = 0; i < count; i++) {
            _resetColumn(*it, i);
          }
        }
      }
    }

    /**
     * Sets the given column to it's default value.
     *
     * @param table   Table id
     * @param id      Column id
     * @param row     Row id
     * @param an      sUIAction if applicable
     */
    inline void resetColumn(tTable table, tColId id, tRowId row = 0, sUIAction* an = 0) {
      for (tColumns::iterator it = _cols.begin(); it != _cols.end(); ++it) {
        if ((*it)->_table == table && (*it)->_id == id) {
          _resetColumn(*it, row, an); break;
        }
      }
    }

  protected:
    inline void _resetColumn(sIMessage_setColumn* it, tRowId row = 0, sUIAction* an = 0) {
      Item item = get(it->_table, it->_id, row);

      String val;
      bool convert = true;

      switch (it->_type) {
        case ctypeInt: {
          item.set(it->_def);
          val = inttostr(it->_def);
          break;
        }
        case ctypeInt64: {
          item.set(*it->_def_p64);
          // val = i64tostr(*it->_def_p64);
          break;
        }
        case ctypeString: {
          item.set(it->_def_ch);
          val = it->_def_ch;
          convert = false;
          break;
        }
      }
      if (an) {
        UIActionCfgSetValue(*an, val.c_str(), convert);
      }
    }

    /**
     * Bulk columns registration
     */
    inline void _registerColumns(IMEvent& ev) {
      for (tColumns::iterator it = _cols.begin(); it != _cols.end(); ++it) {
        Ctrl->IMessage(*it);
      }
      ev.setSuccess();
    }

  protected:
    tColumns _cols;
  };

  /// smart pointer
  typedef SharedPtr<Config> oConfig;
}

#endif // __KONNEKT_CONFIG_H__
