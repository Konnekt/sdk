#pragma once

#include "plug.h"

namespace Konnekt { 
	/**
	*/
	namespace Unique {
		enum enDomainId {
			domainOther,
			domainDomain,
			domainRange,
			domainTable,
			domainIMessage,
			domainMessageType,
			domainAction,
			domainNet,
			domainIcon,
			domainNotFound = -1
		};
		enum enRangeId {
			rangeMain = 0,
			rangeStatic,
			rangeUnique,
			rangeUniqueLow,
			rangeDefault = -1,
			rangeNotFound = -1
		};

		typedef enDomainId tDomainId;
		typedef enRangeId tRangeId;
		typedef unsigned int tId;

		const tId idNotFound = -1;
		const tId commonUniqueStart = 0x00800000;

		class Range {
		public:
			/** Rodzaj zakresu		
			*/
			enum enType {
				typeBoth = 3,
				// Zakres tylko dla identyfikatorów statycznych
				typeStatic = 1,
				// Zakres tylko dla identyfikatorów unikalnych
				typeUnique = 2
			};

			/** Tworzy zakres identyfikatorów
		 *
		 * \param id Unikalny identyfikator zakresu
		 * \param priority Priorytet zakresu okreœlaj¹cy jego szczegó³owoœæ. Bardziej ogólne zakresy powinny mieæ ni¿szy priorytet. Zakres domyœlny powinien mieæ priorytet 0.
		 * \param type Rodzaj zakresu
		 * \param minimum Minimalny identyfikator
		 * \param maximum Maxymalny identyfikator
		 * \param uniqueStart Pierwszy identyfikator do automatycznego nadawania. -1 ustawia ten parametr na wartoœæ @a minimum.
		 * \return 
		 */
			Range(tRangeId rangeId, enType type, unsigned int priority,  unsigned int minimum = 1, unsigned int maximum = 0x7FFFFFFF, unsigned int uniqueStart=-1)
				:_rangeId(rangeId), _priority(priority), _type(type), _minimum(minimum), _maximum(maximum)
			{
				this->_nextUnique = (uniqueStart == -1)? minimum : uniqueStart;
			}
			Range(const Range & r) {
				*this = r;
			}
			virtual ~Range() {}
			virtual unsigned int getClassSize() const {return sizeof(*this);}
			tRangeId getRangeId() const {return _rangeId;}
			unsigned int getPriority() const {return _priority;}
			enType getType() const {return _type;}
			unsigned int getMinimum() const {return _minimum;}
			unsigned int getMaximum() const {return _maximum;}
			unsigned int getNextUnique() const {return _nextUnique;}

		protected:
			tRangeId _rangeId;
			unsigned int _priority;
			enType _type;
			unsigned int _minimum;
			unsigned int _maximum;
			unsigned int _nextUnique;
		};

		namespace IM {
			const unsigned int domainExists = 500;
			const unsigned int removeDomain = 501;
			const unsigned int addRange = 502;
			const unsigned int registerId = 503;
			const unsigned int registerName = 504;
			const unsigned int unregister = 505;
			struct _addRange: public sIMessage_base {
				_addRange(tDomainId domainId, const Range & range, bool setAsDefault = false)
					:sIMessage_base(IM::addRange, 0, 0), domainId(domainId), range(&range), setAsDefault(setAsDefault) 
				{
					this->s_size = sizeof(*this);
				}
				tDomainId domainId;
				const Range * range;
				bool setAsDefault;
			};
			struct _rangeIM: public sIMessage_base {
				_rangeIM(unsigned int IMid)
					:sIMessage_base(IMid, 0, 0)
					,domainId(domainNotFound), rangeId(rangeNotFound), identifier(idNotFound), name(0) {
					this->s_size = sizeof(*this);
				}
				tDomainId domainId;
				tRangeId rangeId;
				tId identifier;
				const char * name;
			};
		};


		bool domainExists(tDomainId domainId);
		bool removeDomain(tDomainId domainId);
		bool addRange(tDomainId domainId, const Range & range, bool setAsDefault = false);
		bool registerId(tDomainId domainId, tId id, const char * name);
		tId registerName(tDomainId domainId, const char * name, tRangeId rangeId = rangeDefault);
		bool unregister(tDomainId domainId, tId id);


	};
};