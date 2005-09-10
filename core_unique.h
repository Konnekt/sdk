#pragma once

#include "plug.h"
#include <Stamina\Unique.h>

namespace Konnekt { 
	/**
	*/
	namespace Unique {

		using namespace Stamina::Unique;

		namespace IMC {

			/** Zwraca wskaŸnik do g³ównego obiektu Unique. Je¿eli wtyczka linkuje siê ze stamina.lib statycznie, powinna ustawiæ Unique::setInstance na zwrócony tutaj wskaŸnik. */
			const tIMCid getMainInstance = 500;

		};

	};
};