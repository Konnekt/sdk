#pragma once

#include "core_object.h"

namespace Konnekt {
	enum enPluginId {
		pluginNotFound = -1
	};
	typedef enPluginId tPluginId;

	/** Interfejs s�u��cy do operowania na wtyczkach
	
	Istniej� dwa rodzaje wtyczek:
	- Klasyczne - rejestrowane przez rdze� pliki .dll
	- Wirtualne - rejestrowane przez wtyczki w trakcie dzia�ania programu

	*/
	class iPlugin: public Stamina::iLockableObject {
	public:

		/** Rodzaje od��czania dla funkcji PlugOut() 
		Okre�laj� kiedy wtyczka ma zosta� od��czona.
		*/
		enum enPlugOutUnload{
			/** Wtyczka zostanie wypi�ta natychmiast.
			Rodzaj dost�pny tylko, gdy jeszcze nie wszystkie wtyczki zosta�y za�adowane po uruchomieniu (czyli przed komunikatem #IMI_ALLPLUGSINITIALIZED), lub gdy wtyczka obs�uguje mechanizm HotPlug co mo�na sprawdzi� funkcj� canHotPlug().
			*/
			poUnloadNow = 1, 
			/** Wtyczka nie zostanie za�adowana przy nast�pnym uruchomieniu */
			poUnloadOnNextStart = 2,
			/** Wtyczka zostanie wypi�ta natychmiast (o ile to mo�liwe), oraz nie b�dzie �adowana przy nast�pnych uruchomieniach. */
			poUnloadNowAndOnNextStart = 3,
		};


		virtual tPluginId __stdcall getPluginId()=0;

		/** Zwraca uchwyt do pliku .dll powi�zanego z t� wtyczk� */
		virtual HMODULE __stdcall getDllInstance()=0;

		/** Zwraca true je�eli jest to wtyczka dynamiczna
		@sa iPlugin*/
		virtual bool __stdcall isVirtual()=0;

		int net;
		int type;
		Stamina::Version version;
		string sig;
		string core_v;
		string ui_v;
		string name;
		string netname;
		string file;
		COLORREF debugColor;
		bool running;
		unsigned int ID;
		class cCtrl_ * Ctrl;
		int IMessage(unsigned int id , int p1=0 , int p2=0 , unsigned int sender=0);
		void madeError(const CStdString msg , unsigned int severity);
		const char * GetName();
		

		/** Czy wtyczka mo�e by� wypinana / wpinana podczas pracy */
		virtual bool __stdcall canHotPlug()=0;

		/** Przesy�a IMessage bezpo�rednio do wtyczki */
		virtual int __stdcall sendIMessage(sIMessage_base*im)=0;

		/** Wypina wtyczk�
		@param reason Przyczyna wypi�cia wtyczki
		@param quiet Czy wy�wietli� przyczyn� u�ytkownikowi?
		@param unload Typ wypi�cia - enPlugOutUnload
		@return Zwraca true je�eli operacja si� powiod�a... W przypadku poUnloadNowAndOnNextStart zwraca false, je�li wtyczka nie mog�a by� wypi�ta natychmiast, ale nie zostanie ona za�adowana przy nast�pnym uruchomieniu.
		@sa enPlugOutUnload, HotPlug
		*/
		virtual bool __stdcall plugOut(const StringRef& reason, bool quiet, enPlugOutUnload unload)=0;


		tPluginId getId() {
			return getPluginId();
		}
	private:
		virtual void __stdcall zz_ip1(){}
		virtual void __stdcall zz_ip2(){}
		virtual void __stdcall zz_ip3(){}
		virtual void __stdcall zz_ip4(){}
		virtual void __stdcall zz_ip5(){}
	};

	class oPlugin:public Stamina::StaticPtr<iPlugin> {
	public:
		oPlugin(tPluginId pluginId) {
			setById(pluginId);
		}
		oPlugin() {
		}
		void setById(tPluginId pluginId);
	};

};