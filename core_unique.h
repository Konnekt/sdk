#pragma once

#include "plug.h"
#include <Stamina\Unique.h>

namespace Konnekt { 
	/**
	*/
	namespace Unique {

		using namespace Stamina::Unique;

		namespace IMC {

			/** Zwraca wska�nik do g��wnego obiektu Unique. Je�eli wtyczka linkuje si� ze stamina.lib statycznie, powinna ustawi� Unique::setInstance na zwr�cony tutaj wska�nik. */
			const tIMCid getMainInstance = 500;

		};

	};
};