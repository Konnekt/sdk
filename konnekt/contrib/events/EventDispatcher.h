/**
  *  @file
  *  Generic Event Dispatcher class
  *
  *  Licensed under The GNU Lesser General Public License
  *  Redistributions of files must retain the above copyright notice.
  *
  *  @author        Sijawusz Pur Rahnama <sija@gibbon.pl>
  *  @license       http://creativecommons.org/licenses/LGPL/2.1/
  */

#pragma once

#ifndef __EVENTDISPATCHER_H__
#define __EVENTDISPATCHER_H__

#include <hash_map>
#include <deque>

#include <boost/signal.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>

#include <Stamina/Exception.h>

using namespace Stamina;
using namespace boost;

using namespace std;
using stdext::hash_map;

namespace Konnekt {
  /**
   * Exception which stops chain execution
   */
  class StopEventNotifyException : public ExceptionString {
  public:
    StopEventNotifyException() : ExceptionString("Event notification was interrupted") { }
  };

  template <class E>
  class EventDispatcher : public iObject {
  public:
    /**
     * Class version macro
     */
    STAMINA_OBJECT_CLASS_VERSION(EventDispatcher<E>, iObject, Version(0,1,0,0));

  public:
    typedef function<void(E&)> fListener;
    typedef signal<void(E&)> sigListener;

  public:
    typedef hash_map<int, sigListener*> tListeners;

  public:
    inline ~EventDispatcher() {
      for (tListeners::iterator it = _listeners.begin(); it != _listeners.end(); ++it) {
        delete it->second;
      }
    }

  public:
    /**
     * Connects a listener to a given event id.
     *
     * @param id        An event id
     * @param f         Listener callback
     * @param priority  Listener priority
     * @param pos       Position in list
     *
     * @return connection object
     */
    inline signals::connection connect(int id, const fListener& f, int priority = 0, signals::connect_position pos = signals::at_back) {
      if (f.empty()) {
        throw ExceptionString("Empty functor was given.");
      }
      if (_listeners.find(id) == _listeners.end()) {
        _listeners[id] = new sigListener;
      }
      signals::connection c = _listeners[id]->connect(priority, f, pos);
      if (!c.connected()) {
        throw ExceptionString("Listener was not connected.");
      }
      return c;
    }

    /**
     * Notifies all listeners of a given event.
     *
     * @param ev  An Event object
     * @return    Modified @a ev object
     */
    inline E& notify(E& ev) {
      int id = ev.getID();

      if (hasListeners(id)) {
        try {
          (*_listeners[id])(ev);
        } catch (StopEventNotifyException&) { }
      }
      return ev;
    }

    /**
     * Returns true if the given event id has some listeners.
     * @param  id  The event id
     */
    inline bool hasListeners(int id) {
      if (_listeners.find(id) == _listeners.end()) {
        return false;
      }
      return !_listeners[id]->empty();
    }

  protected:
    tListeners _listeners;
  };
}

#endif // __EVENTDISPATCHER_H__
