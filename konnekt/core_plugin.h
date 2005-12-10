#pragma once

#include <Stamina/String.h>

namespace Konnekt {

	/** Identyfikator wtyczki.
	W komunikacji z API mo¿na zamiennie u¿ywaæ identyfikatora i pozycji
	wtyczki na liœcie. Poni¿szy kod jest prawid³owy i dotyczy tej samej wtyczki:

	@code
	Ctrl->getPlugin(pluginUI) == Ctrl->getPlugin((tPluginId)1);
	@endcode

	*/
	enum tPluginId {
		pluginCore = 0x100, /// Sta³y identyfikator "wtyczki" rdzenia
		pluginUI = 0x101, /// Sta³y identyfikator wtyczki interfejsu
		pluginFirstDynamic = 0x1000, /// Pierwszy plugin spoza rdzenia
		pluginNotFound = -1,
	};

	enum enPluginPriority {
		priorityLowest = 0x10,  /// Koniec listy
        priorityLow = 0x40,  
        priorityStandard = 0x80, /// Zwyk³e wtyczki
        priorityHigh = 0xB0,  
        priorityHighest = 0xE0,  /// Pocz¹tek listy
		priorityCore = 0xFF, /// Zarezerwowane dla Core i UI.
        priorityNone = 0x0  /// W efekcie to samo co plugStandard
	};

	const int pluginsMaxCount = 0xFF;
	const int pluginsDynamicIdStart = pluginFirstDynamic;
};

#include "core_object.h"
#include "core_net.h"
#include "core_imessage.h"

namespace Konnekt {

	/** Interfejs s³u¿¹cy do operowania na wtyczce
	
	Istniej¹ dwa rodzaje wtyczek:
	- Klasyczne - rejestrowane przez rdzeñ pliki .dll
	- Wirtualne - rejestrowane przez wtyczki w trakcie dzia³ania programu

	*/
	class iPlugin: public Stamina::iLockableObject {
	public:

		STAMINA_OBJECT_CLASS_VERSION(Konnekt::iPlugin, ::Stamina::iLockableObject, ::Stamina::Version(1, 0, 0, 0));


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


		/** Zwraca identyfikator wtyczki */
		virtual tPluginId getPluginId()=0;

		/** Zwraca pozycjê wtyczki na liœcie */
		virtual int getPluginIndex()=0;

		/** Zwraca uchwyt do pliku .dll powi¹zanego z t¹ wtyczk¹ */
		virtual HMODULE getDllModule()=0;

		/** Zwraca œcie¿kê pliku .dll */
		virtual const Stamina::String& getDllFile()=0;

		/** Zwraca true je¿eli jest to wtyczka dynamiczna
		@sa iPlugin*/
		bool isVirtual() {
			return this->getOwnerPlugin() != 0;
		}

		/** Zwraca wtyczkê, która zarejestrowa³a t¹ wtyczkê, lub 0 jeœli jest to wtyczka klasyczna.  */
		virtual iPlugin* getOwnerPlugin()=0;

		/** Zwraca sieæ wtyczki */
		virtual tNet getNet()=0;

		/** Zwraca typ wtyczki */
		virtual enIMessageType getType()=0;

		/** Zwraca wersjê wtyczki
		Wersja pobierana jest z zasobów pliku .dll (Równie¿ dla wtyczek wirtualnych!). Je¿eli wersji tam nie ma, podawana jest wersja zwrócona w IM_PLUG_VERSION z wtyczki "klasycznej"
		*/
		virtual Stamina::Version getVersion()=0;

		/** Zwraca sygnaturê wtyczki (jej unikalny, niezmienny identyfikator) */
		virtual const Stamina::String& getSig()=0;

		/** Zwraca nazwê wtyczki czyteln¹ dla u¿ytkownika */
		virtual const Stamina::String& getName()=0;

		/** Zwraca nazwê sieci, któr¹ obs³uguje wtyczki (o ile obs³uguje) */
		virtual const Stamina::String& getNetName()=0;

		/** Zwraca priorytet wtyczki */
		virtual enPluginPriority getPriority()=0;


		/** Czy wtyczka mo¿e byæ wypinana / wpinana podczas pracy */
		virtual bool canHotPlug()=0;

		virtual bool canPlugOut()=0;

		virtual bool isRunning()=0;

		/** Przesy³a IMessage bezpoœrednio do wtyczki */
		virtual int IMessageDirect(Controler* sender, sIMessage_base* im)=0;

		int IMessageDirect(tIMid id, int p1 = 0, int p2 = 0);

		/** Wypina wtyczkê
		@param reason Przyczyna wypiêcia wtyczki
		@param quiet Czy wyœwietliæ przyczynê u¿ytkownikowi?
		@param unload Typ wypiêcia - enPlugOutUnload
		@return Zwraca true je¿eli operacja siê powiod³a... W przypadku poUnloadNowAndOnNextStart zwraca false, je¿li wtyczka nie mog³a byæ wypiêta natychmiast, ale nie zostanie ona za³adowana przy nastêpnym uruchomieniu.
		@sa enPlugOutUnload, HotPlug
		*/
		virtual bool plugOut(Controler* sender, const Stamina::StringRef& reason, bool quiet, enPlugOutUnload unload)=0;


		tPluginId getId() {
			return getPluginId();
		}
		

	private:
		virtual void zz_ipl1(){}
		virtual void zz_ipl2(){}
		virtual void zz_ipl3(){}
		virtual void zz_ipl4(){}
		virtual void zz_ipl5(){}
		virtual void zz_ipl6(){}
		virtual void zz_ipl7(){}
		virtual void zz_ipl8(){}
		virtual void zz_ipl9(){}

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