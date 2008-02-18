#include <stdlib.h>

#include "core_tools.h"
#include "plug_export.h"

using namespace Konnekt;
using namespace Stamina;

namespace Konnekt {
  void setObsoleteString(const Stamina::StringRef& value, Stamina::String& modern, char*& obsolete, bool useModern) {
    if (useModern) {
      modern = value;
      obsolete = (char*) modern.a_str();
    } else {
      // alokuje miejsce
      obsolete = (char*) Ctrl->GetTempBuffer(value.getDataSize<char>() + 1);
      // kopiuje dane
      strcpy(obsolete, value.a_str());
    }
  }
}