#pragma once

#include "core_object.h"

namespace Konnekt {
	enum enPluginId {
		pluginNotFound = -1
	};
	typedef enPluginId tPluginId;

	/** Interfejs s³u¿¹cy do operowania na wtyczkach
	
	Istniej¹ dwa rodzaje wtyczek:
	- Klasyczne - rejestrowane przez rdzeñ pliki .dll
	- Wirtualne - rejestrowane przez wtyczki w trakcie dzia³ania programu

	*/
	class iPlugin: public Stamina::iLockableObject {
	public:

		/** Rodzaje od³¹czania dla funkcji PlugOut() 
		Okreœlaj¹ kiedy wtyczka ma zostaæ od³¹czona.
		*/
		enum enPlugOutUnload{
			/** Wtyczka zostanie wypiêta natychmiast.
			Rodzaj dostêpny tylko, gdy jeszcze nie wszystkie wtyczki zosta³y za³adowane po uruchomieniu (czyli przed komunikatem #IMI_ALLPLUGSINITIALIZED), lub gdy wtyczka obs³uguje mechanizm HotPlug co mo¿na sprawdziæ funkcj¹ canHotPlug().
			*/
			poUnloadNow = 1, 
			/** Wtyczka nie zostanie za³adowana przy nastêpnym uruchomieniu */
			poUnloadOnNextStart = 2,
			/** Wtyczka zostanie wypiêta natychmiast (o ile to mo¿liwe), oraz nie bêdzie ³adowana przy nastêpnych uruchomieniach. */
			poUnloadNowAndOnNextStart = 3,
		};


		virtual tPluginId __stdcall getPluginId()=0;

		/** Zwraca uchwyt do pliku .dll powi¹zanego z t¹ wtyczk¹ */
		virtual HMODULE __stdcall getDllInstance()=0;

		/** Zwraca true je¿eli jest to wtyczka dynamiczna
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
		

		/** Czy wtyczka mo¿e byæ wypinana / wpinana podczas pracy */
		virtual bool __stdcall canHotPlug()=0;

		/** Przesy³a IMessage bezpoœrednio do wtyczki */
		virtual int __stdcall sendIMessage(sIMessage_base*im)=0;

		/** Wypina wtyczkê
		@param reason Przyczyna wypiêcia wtyczki
		@param quiet Czy wyœwietliæ przyczynê u¿ytkownikowi?
		@param unload Typ wypiêcia - enPlugOutUnload
		@return Zwraca true je¿eli operacja siê powiod³a... W przypadku poUnloadNowAndOnNextStart zwraca false, je¿li wtyczka nie mog³a byæ wypiêta natychmiast, ale nie zostanie ona za³adowana przy nastêpnym uruchomieniu.
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