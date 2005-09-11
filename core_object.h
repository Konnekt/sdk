#pragma once

#include "core_assert.h"

namespace Konnekt {

	class iObject {
	public:
		//virtual const char * 
		virtual ~iObject() {};
	private:
		virtual void __stdcall zz_io1(){}
		virtual void __stdcall zz_io2(){}
		virtual void __stdcall zz_io3(){}
		virtual void __stdcall zz_io4(){}
		virtual void __stdcall zz_io5(){}
		virtual void __stdcall zz_io6(){}
		virtual void __stdcall zz_io7(){}
		virtual void __stdcall zz_io8(){}
		virtual void __stdcall zz_io9(){}
		virtual void __stdcall zz_io10(){}
	};

	/* podstawowy interfejs obiektów "wspó³dzielonych" */
	class iLockableObj {
	public:
	    /** Blokuje dostêp do obiektu */
		virtual void __stdcall lock()=0;
		/** Odblokowuje dostêp do obiektu */
		virtual void __stdcall unlock()=0;

		virtual ~iLockableObj() {};
	private:
		virtual void __stdcall zz_ilo1(){}
		virtual void __stdcall zz_ilo2(){}
		virtual void __stdcall zz_ilo3(){}
		virtual void __stdcall zz_ilo4(){}
		virtual void __stdcall zz_ilo5(){}
	};

	class iSharedObj: public iLockableObj {
	public:
		virtual bool __stdcall hold() =0;
		virtual void __stdcall release() =0;
		/** Zwraca true je¿eli z obiektu mo¿na spokojnie korzystaæ.
		false oznacza np. ¿e obiekt jest w trakcie usuwania.
		*/
		virtual bool __stdcall isValid() =0;
		virtual bool __stdcall isDestroyed() =0;
		virtual unsigned int __stdcall getUseCount() =0;
		virtual ~iSharedObj() {};
	private:
		virtual void __stdcall zz_iso1(){}
		virtual void __stdcall zz_iso2(){}
		virtual void __stdcall zz_iso3(){}
		virtual void __stdcall zz_iso4(){}
		virtual void __stdcall zz_iso5(){}
	};


	template <class T> class KStaticObject {
	public:
		KStaticObject(T & obj) {
			this->set(obj);
		}
		KStaticObject(T * obj = 0) {
			this->set(obj);
		}
		KStaticObject(const KStaticObject & b) {
			this->set(*b);
		}
		KStaticObject & operator = (const KStaticObject & b) {
			this->set(*b);
			return *this;
		}
		void set(T * obj) {
			this->_obj = obj;
		}
		void set(T & obj) {
			set(&obj);
		}
		void set(const KStaticObject & obj) {
			this->set(obj.get());
		}
		T * get() const {
			return this->_obj;
		}
		T * operator -> () const {
			K_ASSERT(this->_obj != 0);
			return this->get();
		}
		T * operator * () const {
			return this->get();
		}
		operator bool () const {
			return this->_obj != 0;
		}
		bool operator == (const T * b) {
			return this->_obj == b;
		}
		bool operator == (const KStaticObject & b) {
			return this->_obj == b.get();
		}
	private:
		T * _obj;

		template <class T> friend class KObject;
	};
	template <class T> class KObject: public KStaticObject<T> {
	public:
		KObject(T * obj = 0):KStaticObject<T>() {
			this->set(obj);
		}
		KObject(T & obj):KStaticObject<T>() {
			this->set(obj);
		}
		KObject(const KObject & b):KStaticObject<T>() {
			this->set(*b);
		}
		KObject & operator = (const KObject & b) {
			this->set(*b);
			return *this;
		}
		~KObject() {
			this->set(0);
		}
		void set(T * obj) {
			if (this->_obj)
				this->_obj->release();
			KStaticObject<T>::set(obj);
			if (this->_obj) {
				K_ASSERT_LOGMSG(this->_obj->isValid(), "SharedObj not valid!");
				this->_obj->hold();
			}
		}
		void set(T & obj) {
			this->set(&obj);
		}
		void set(const KObject & obj) {
			this->set(obj.get());
		}
	private:
	};

	/* podstawowy interfejs obiektów "kontekstowych" */
	class iKObject: public KObject<iSharedObj> {
	public:
	};


};