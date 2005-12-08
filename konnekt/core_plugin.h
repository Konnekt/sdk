#pragma once

#include "core_object.h"
#include "core_net.h"
#include "core_imessage.h"

namespace Konnekt {
	enum tPluginId {
		pluginCore = 0x100, /// Sta�y identyfikator "wtyczki" rdzenia
		pluginUI = 0x101, /// Sta�y identyfikator wtyczki interfejsu
		pluginNotFound = -1,
	};

	enum enPluginPriority {
		priorityPriorityLowest = 0x10,  /// Koniec listy
        priorityPriorityLow = 0x40,  
        priorityPriorityStandard = 0x80, /// Zwyk�e wtyczki
        priorityPriorityHigh = 0xB0,  
        priorityHighest = 0xE0,  /// Pocz�tek listy
		priorityCore = 0xFF, /// Zarezerwowane dla Core i UI.
        priorityNone = 0x0  /// W efekcie to samo co plugStandard
	};

	const int pluginsMaxCount = 0xFF;
	const int pluginsDynamicIdStart = 0x1000;
	

	/** Interfejs s�u��cy do operowania na wtyczce
	
	Istniej� dwa rodzaje wtyczek:
	- Klasyczne - rejestrowane przez rdze� pliki .dll
	- Wirtualne - rejestrowane przez wtyczki w trakcie dzia�ania programu

	*/
	class iPlugin: public Stamina::iLockableObject {
	public:

		STAMINA_OBJECT_CLASS_VERSION(Konnekt::iPlugin, ::Stamina::iLockableObject, ::Stamina::Version(1, 0, 0, 0));


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


		/** Zwraca identyfikator wtyczki */
		virtual tPluginId __stdcall getPluginId()=0;

		/** Zwraca pozycj� wtyczki na li�cie */
		virtual int __stdcall getPluginIndex()=0;

		/** Zwraca uchwyt do pliku .dll powi�zanego z t� wtyczk� */
		virtual HMODULE __stdcall getDllInstance()=0;

		/** Zwraca �cie�k� pliku .dll */
		virtual const String& __stdcall getDllFile()=0;

		/** Zwraca true je�eli jest to wtyczka dynamiczna
		@sa iPlugin*/
		bool __stdcall isVirtual() {
			return this->getOwnerPlugin() != 0;
		}

		/** Zwraca wtyczk�, kt�ra zarejestrowa�a t� wtyczk�, lub 0 je�li jest to wtyczka klasyczna.  */
		virtual iPlugin* __stdcall getOwnerPlugin()=0;

		/** Zwraca sie� wtyczki */
		virtual tNet __stdcall getNet()=0;

		/** Zwraca typ wtyczki */
		virtual enIMessageType __stdcall getType()=0;

		/** Zwraca wersj� wtyczki
		Wersja pobierana jest z zasob�w pliku .dll (R�wnie� dla wtyczek wirtualnych!). Je�eli wersji tam nie ma, podawana jest wersja zwr�cona w IM_PLUG_VERSION z wtyczki "klasycznej"
		*/
		virtual Stamina::Version __stdcall getVersion()=0;

		/** Zwraca sygnatur� wtyczki (jej unikalny, niezmienny identyfikator) */
		virtual const String& __stdcall getSig()=0;

		/** Zwraca nazw� wtyczki czyteln� dla u�ytkownika */
		virtual const String& __stdcall getName()=0;

		/** Zwraca nazw� sieci, kt�r� obs�uguje wtyczki (o ile obs�uguje) */
		virtual const String& __stdcall getNetName()=0;

		/** Zwraca priorytet wtyczki */
		virtual enPlugPriority __stdcall getPriority()=0;


		/** Czy wtyczka mo�e by� wypinana / wpinana podczas pracy */
		virtual bool __stdcall canHotPlug()=0;

		virtual bool __stdcall canPlugOut()=0;

		virtual bool __stdcall isRunning()=0;

		/** Przesy�a IMessage bezpo�rednio do wtyczki */
		virtual int __stdcall sendIMessage(cCtrl* sender, sIMessage_base*im)=0;

		/** Wypina wtyczk�
		@param reason Przyczyna wypi�cia wtyczki
		@param quiet Czy wy�wietli� przyczyn� u�ytkownikowi?
		@param unload Typ wypi�cia - enPlugOutUnload
		@return Zwraca true je�eli operacja si� powiod�a... W przypadku poUnloadNowAndOnNextStart zwraca false, je�li wtyczka nie mog�a by� wypi�ta natychmiast, ale nie zostanie ona za�adowana przy nast�pnym uruchomieniu.
		@sa enPlugOutUnload, HotPlug
		*/
		virtual bool __stdcall plugOut(const cCtrl* sender, const StringRef& reason, bool quiet, enPlugOutUnload unload)=0;


		tPluginId getId() {
			return getPluginId();
		}
		

	private:
		virtual void __stdcall zz_ipl1(){}
		virtual void __stdcall zz_ipl2(){}
		virtual void __stdcall zz_ipl3(){}
		virtual void __stdcall zz_ipl4(){}
		virtual void __stdcall zz_ipl5(){}
		virtual void __stdcall zz_ipl6(){}
		virtual void __stdcall zz_ipl7(){}
		virtual void __stdcall zz_ipl8(){}
		virtual void __stdcall zz_ipl9(){}

	};

    /**  */
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