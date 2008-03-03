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
      // pobiera rozmiar
      int size = value.getDataSize<char>();
      // alokuje miejsce
      obsolete = (char*) Ctrl->GetTempBuffer(size + 1);
      // kopiuje dane
      strcpy_s(obsolete, size + 1, value.a_str());
    }
  }
}