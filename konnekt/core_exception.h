#pragma once

#include <Stamina/Exception.h>
#include "core_imessage.h"

class KException : public Stamina::ExceptionString {
public:
  KException(const Stamina::StringRef& reason = ""): ExceptionString(reason) { }
};

class KException_IM: public KException {
public:
  KException_IM(const Stamina::StringRef& reason, const sIMessage_base * im): KException(reason), _im(im) { }
  KException_IM(const sIMessage_base * im): _im(im) { }

public:
  const sIMessage_base * getIM() const {
    return _im;
  }

private:
  const sIMessage_base * _im;
};
