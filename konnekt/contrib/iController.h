/**
  *  @file
  *  Base Controller class
  *
  *  Licensed under The GNU Lesser General Public License
  *  Redistributions of files must retain the above copyright notice.
  *
  *  @author        Sijawusz Pur Rahnama <sija@gibbon.pl>
  *  @license       http://creativecommons.org/licenses/LGPL/2.1/
  */

#pragma once

#ifndef __ICONTROLLER_H__
#define __ICONTROLLER_H__

// #include "Context.h"
#include "Singleton.h"
#include "Config.h"

#include "Events/IMEvent.h"
#include "Events/ActionEvent.h"

using namespace Stamina;
using namespace boost;

namespace Konnekt {
  class iController : public SharedObject<iSharedObject> {
  public:
    /**
     * Class version macro
     */
    STAMINA_OBJECT_CLASS_VERSION(iController, iSharedObject, Version(0,3,0,0));

  public:
    inline iController(): _ctrl(0) {
      _config.attachListeners(_imessage_dispatcher);

      // setting/unsetting Ctrl global pointer
      _imessage_dispatcher.connect(IM_PLUG_INIT, bind(&iController::_onPlugInit, this, _1));
      _imessage_dispatcher.connect(IM_PLUG_DEINIT, bind(&iController::_onPlugDeInit, this, _1));

      // actions subclassing
      _action_dispatcher.connect(IM_UI_PREPARE, bind(&ActionDispatcher::doSubclass, &_action_dispatcher, _1));
    }

  public:
    /**
     * Returns Controler tied to the plugin.
     */
    inline Controler* getCtrl() {
      return _ctrl;
    }

    /**
     * Returns Config class instance.
     */
    inline Config& getConfig() {
      return _config;
    }

    /**
     * Returns reference to IMessageDispatcher.
     */
    inline IMessageDispatcher& getIMessageDispatcher() {
      return _imessage_dispatcher;
    }

    /**
     * Returns reference to IMActionDispatcher.
     */
    inline ActionDispatcher& getActionDispatcher() {
      return _action_dispatcher;
    }

  public:
    /**
     * Dispatch incoming IMessage.
     */
    inline int dispatch(sIMessage_base* msgBase) {
      // dispatch IMessage
      oEvent ev = getIMessageDispatcher().dispatch(msgBase);

      // dispatch action
      if (ev->getID() == IM_UIACTION) {
        ev = getActionDispatcher().dispatch(msgBase);
      }
      return ev->getReturnValue();
    }

  public:
    inline void registerVirtualPlugin() {
      // Ctrl->IMessage(&sIMessage_plugVirtualAdd(this, &iController::dispatch));
    }

  protected:
    /**
     * Plugin initialization callback
     */
    inline void _onPlugInit(IMEvent& ev) {
      if (!Ctrl) {
        Plug_Init(ev.getP1(), ev.getP2());
      }
      _ctrl = (Controler*) ev.getP1();
      ev.setSuccess();
    }

    /**
     * Plugin deinitialization callback
     */
    inline void _onPlugDeInit(IMEvent& ev) {
      if (Ctrl == getCtrl()) {
        Plug_Deinit(ev.getP1(), ev.getP2());
      }
      _ctrl = 0;
      ev.setProcessed(true);
    }

  protected:
    Controler* _ctrl;
    IMessageDispatcher _imessage_dispatcher;
    ActionDispatcher _action_dispatcher;
    Config _config;
  };
}

#endif // __ICONTROLLER_H__