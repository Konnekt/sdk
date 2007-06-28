#pragma once

#include <Stamina/String.h>


namespace Konnekt {


	inline Stamina::String getObsoleteString(const Stamina::String& modern, const char* obsolete, bool useModern) {
		if (useModern) {
			return modern;
		} else {
			return obsolete;
		}
	}

	inline void setObsoleteString(const Stamina::StringRef& value, Stamina::String& modern, char*& obsolete, bool useModern);


}