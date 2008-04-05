/**
  *  @file
  *  UID class
  *
  *  Licensed under The GNU Lesser General Public License
  *  Redistributions of files must retain the above copyright notice.
  *
  *  @author        Sijawusz Pur Rahnama <sija@gibbon.pl>
  *  @license       http://creativecommons.org/licenses/LGPL/2.1/
  */

#pragma once

#ifndef __UID_H__
#define __UID_H__

namespace Konnekt {
  using namespace Stamina;

  /**
   *
   */
  class iUID : public SharedObject<iSharedObject> {
  public:
    virtual bool equal(const class oUID& b) const = 0;
    virtual String toString() const = 0;
  };

  /**
   *
   */
  class oUID : public SharedPtr<iUID> {
  public:
    oUID(iUID* obj = 0) : SharedPtr<iUID>(obj) { }
    oUID(iUID& obj) : SharedPtr<iUID>(obj) { }
    oUID(const SharedPtr& b) : SharedPtr<iUID>(b) { }

  public:
    inline bool operator == (const oUID& b) const {
      return (this->empty() || b.empty()) 
        ? false
        : get()->equal(b);
    }
    inline bool operator != (const oUID& b) const {
      return !(*this == b);
    }

    inline operator String () const {
      return this->empty() ? String() : get()->toString();
    }
  };

  /**
   *
   */
  class UID : public iUID {
  public:
    UID(const StringRef& uid): _uid(uid) { }

  public:
    inline bool equal(const oUID& b) const {
      return _uid == b->toString();
    }
    inline String toString() const {
      return _uid;
    }

  protected:
    String _uid;
  };
}

#endif // __UID_H__