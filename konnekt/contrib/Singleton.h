/**
  *  @file
  *  Singleton class
  *
  *  Licensed under The GNU Lesser General Public License
  *  Redistributions of files must retain the above copyright notice.
  *
  *  @author        Sijawusz Pur Rahnama <sija@gibbon.pl>
  *  @license       http://creativecommons.org/licenses/LGPL/2.1/
  */

#pragma once

#ifndef __SINGLETON_H__
#define __SINGLETON_H__

namespace Konnekt {
  /**
   *
   */
  template <class T>
  class Singleton : public T {
  public:
    STAMINA_OBJECT_CLASS_VERSION(Singleton<T>, T, Version(0,1,0,0));

  public:
    typedef SharedPtr<T> oInstance;

  public:
    inline static T* getInstance() {
      if (!_instance.isValid()) {
        _instance = new Singleton<T>;
      }
      return _instance;
    }

  private:
    Singleton(): T() { }
    ~Singleton() { }

  protected:
    static oInstance _instance;
  };

  template <class T>
  SharedPtr<T> Singleton<T>::_instance = 0;
};

#endif // __SINGLETON_H__