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
  /**
   *
   */
  class iUID : public iSharedObject {
  public:
    inline bool operator == (const iUID& b) const {
      return this->equal(b);
    }
    inline bool operator != (const iUID& b) const {
      return !(*this == b);
    }

  public:
    virtual bool equal(const iUID& b) = 0;
    virtual String toString() = 0;
  };
  typedef SharedObject<iUID> oUID;

  /**
   *
   */
  class UID : public iUID {
  public:
    UID(const StringRef& uid): _uid(uid) { }

  public:
    inline bool equal(const iUID& b) {
      return _uid == b.toString();
    }
    inline String toString() {
      return _uid;
    }

  protected:
    String _uid;
  };
}

#endif // __UID_H__