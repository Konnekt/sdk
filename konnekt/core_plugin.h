#pragma once

#include <Stamina/String.h>

namespace Konnekt {
  /** 
   * Identyfikator wtyczki.
   * W komunikacji z API mo�na zamiennie u�ywa� identyfikatora i pozycji
   * wtyczki na li�cie. Poni�szy kod jest prawid�owy i dotyczy tej samej wtyczki:
   *
   * @code
   * Ctrl->getPlugin(pluginUI) == Ctrl->getPlugin((tPluginId) 1);
   * @endcode
   */
  enum tPluginId {
    pluginCore = 0x100, /// Sta�y identyfikator "wtyczki" rdzenia
    pluginUI = 0x101, /// Sta�y identyfikator wtyczki interfejsu
    pluginFirstDynamic = 0x1000, /// Pierwszy plugin spoza rdzenia
    pluginNotFound = -1
  };

  enum enPluginPriority {
    priorityLowest = 0x10,  /// Koniec listy
    priorityLow = 0x40,  
    priorityStandard = 0x80, /// Zwyk�e wtyczki
    priorityHigh = 0xB0,  
    priorityHighest = 0xE0,  /// Pocz�tek listy
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
  /** 
   * Interfejs s�u��cy do operowania na wtyczce
   *
   * Istniej� dwa rodzaje wtyczek:
   * - Klasyczne - rejestrowane przez rdze� pliki .dll
   * - Wirtualne - rejestrowane przez wtyczki w trakcie dzia�ania programu
   */
  class iPlugin: public Stamina::iLockableObject {
  public:
    STAMINA_OBJECT_CLASS_VERSION(Konnekt::iPlugin, ::Stamina::iLockableObject, ::Stamina::Version(1,0,0,0));

    /** 
     * Rodzaje od��czania dla funkcji PlugOut() 
     * Okre�laj� kiedy wtyczka ma zosta� od��czona.
     */
    enum enPlugOutUnload {
      /** 
       * Wtyczka zostanie wypi�ta natychmiast.
       * Rodzaj dost�pny tylko, gdy jeszcze nie wszystkie wtyczki zosta�y za�adowane po uruchomieniu (czyli przed komunikatem #IMI_ALLPLUGSINITIALIZED), 
       * lub gdy wtyczka obs�uguje mechanizm HotPlug co mo�na sprawdzi� funkcj� canHotPlug().
       */
      poUnloadNow = 1, 
      /** 
       * Wtyczka nie zostanie za�adowana przy nast�pnym uruchomieniu
       */
      poUnloadOnNextStart = 2,
      /** 
       * Wtyczka zostanie wypi�ta natychmiast (o ile to mo�liwe), oraz nie b�dzie �adowana przy nast�pnych uruchomieniach.
       */
      poUnloadNowAndOnNextStart = 3
    };

    /** 
     * Zwraca identyfikator wtyczki
     */
    virtual tPluginId getPluginId() = 0;

    /** 
     * Zwraca pozycj� wtyczki na li�cie 
     */
    virtual int getPluginIndex() = 0;

    /** 
     * Zwraca uchwyt do pliku .dll powi�zanego z t� wtyczk� 
     */
    virtual HMODULE getDllModule() = 0;

    /** 
     * Zwraca �cie�k� pliku .dll 
     */
    virtual const Stamina::String& getDllFile() = 0;

    /** 
     * Zwraca true je�eli jest to wtyczka dynamiczna
     * @sa iPlugin
     */
    bool isVirtual() {
      return this->getOwnerPlugin() != 0;
    }

    /** 
     * Zwraca wtyczk�, kt�ra zarejestrowa�a t� wtyczk�, lub 0 je�li jest to wtyczka klasyczna.
     */
    virtual iPlugin* getOwnerPlugin() = 0;

    /** 
     * Zwraca sie� wtyczki 
     */
    virtual tNet getNet() = 0;

    /** 
     * Zwraca typ wtyczki 
     */
    virtual enIMessageType getType() = 0;

    /** 
     * Zwraca wersj� wtyczki
     * Wersja pobierana jest z zasob�w pliku .dll (R�wnie� dla wtyczek wirtualnych!). 
     * Je�eli wersji tam nie ma, podawana jest wersja zwr�cona w IM_PLUG_VERSION z wtyczki "klasycznej"
     */
    virtual Stamina::Version getVersion() = 0;

    /** 
     * Zwraca sygnatur� wtyczki (jej unikalny, niezmienny identyfikator)
     */
    virtual const Stamina::String& getSig() = 0;

    /** 
     * Zwraca nazw� wtyczki czyteln� dla u�ytkownika
     */
    virtual const Stamina::String& getName() = 0;

    /** 
     * Zwraca nazw� sieci, kt�r� obs�uguje wtyczki (o ile obs�uguje) 
     */
    virtual const Stamina::String& getNetName() = 0;

    /** 
     * Zwraca priorytet wtyczki 
     */
    virtual enPluginPriority getPriority() = 0;

    /** 
     * Czy wtyczka mo�e by� wypinana / wpinana podczas pracy 
     */
    virtual bool canHotPlug() = 0;
    virtual bool canPlugOut() = 0;

    virtual bool isRunning() = 0;

    /** 
     * Przesy�a IMessage bezpo�rednio do wtyczki
     */
    virtual int IMessageDirect(Controler* sender, sIMessage_base* im) = 0;

    int IMessageDirect(tIMid id, int p1 = 0, int p2 = 0);

    /** 
     * Wypina wtyczk�
     *
     * @param reason Przyczyna wypi�cia wtyczki
     * @param quiet Czy wy�wietli� przyczyn� u�ytkownikowi?
     * @param unload Typ wypi�cia - enPlugOutUnload
     *
     * @return Zwraca true je�eli operacja si� powiod�a... W przypadku poUnloadNowAndOnNextStart zwraca false, 
     * je�eli wtyczka nie mog�a by� wypi�ta natychmiast, ale nie zostanie ona za�adowana przy nast�pnym uruchomieniu.
     * @sa enPlugOutUnload, HotPlug
     */
    virtual bool plugOut(Controler* sender, const Stamina::StringRef& reason, bool quiet, enPlugOutUnload unload) = 0;

    /** 
     * Subclassuje f-cj� obs�uguj�c� komunikaty wtyczki.
     * Subclassowanie pozwala na przechwytywanie komunikat�w zanim dotr� do docelowej wtyczki. 
     * Technika mo�e by� przydatna przy obchodzeniu pewnych ogranicze� w API, ale @b nie powinna by� nadu�ywana!
     * 
     * @param proc   Wska�nik do nowej f-cji obs�uguj�cej. Przekazanie 0 spowoduje tylko zwr�cenie aktualnych wska�nik�w
     * @param object Wska�nik do obiektu dla kt�rego ta f-cja ma by� wywo�ywana, lub 0
     * 
     * @return Zwraca true je�eli operacja si� powiod�a. W zmiennych proc i object znajduj� si� poprzednio ustawione dla wtyczki warto�ci.
     * 
     * @warning Wtyczka subclassuj�ca jest odpowiedzialna za przechowanie poprzednio ustawionych warto�ci @a proc i @a object, 
     * oraz wywo�ywanie oryginalnej funkcji przy ich pomocy (najlepiej przy u�yciu f-cji iPlugin::callIMessageProc() ).
     * @warning Jest to zaawansowana funkcja API! U�ywaj jej tylko je�eli jeste� �wiadomy tego co robisz! Mo�na w ten spos�b wi�cej popsu� ni� naprawi�!
     * @warning F-cja nie jest w �aden spos�b zabezpieczona przed wielow�tkowo�ci�! Subclassowa� nale�y jak najszybciej jest to mo�liwe, 
     * dop�ki wtyczki nie uruchomi� swoich w�tk�w...
     * 
     * Przyk�ad 1 (wersja bez obiektu)
     * @code
     *   void* subclassUI_proc;
     *   void* subclassUI_object;
     * 
     *   int __stdcall newUIProc(sIMessage_base* msg) {
     *     switch (msg->id) {
     *       ....
     *     }
     *     return iPlugin::callIMessageProc(msg, subclassUI_proc, subclassUI_object);
     *   }
     * 
     *   void subclassUI() {
     *     oPlugin ui = Ctrl->getPlugin(pluginUI);
     *     subclassUI_proc = newUIProc;
     *     subclassUI_object = 0;
     *     bool ret = ui->subclassIMessageProc(Ctrl, subclassUI_proc, subclassUI_object);
     *     S_ASSERT(ret);
     *   }
     * @endcode
     * 
     * Przyk�ad 2 (wersja z obiektem)
     * @code
     *   class Subclass {
     *   public:
     *     Subclass(const oPlugin& plugin) {
     *       _proc = newProc;
     *       _object = this;
     *       bool ret = plugin->subclassIMessageProc(Ctrl, _proc, _object);
     *       S_ASSERT(ret);
     *     }
     * 
     *   private:
     *     void* _proc;
     *     void* _object;
     * 
     *     // newProc b�dzie wywo�ywany w kontek�cie tego obiektu
     *     int __stdcall newProc(sIMessage_base* msg) {
     *       switch (msg->id) {
     *         ....
     *       }
     *       return iPlugin::callIMessageProc(msg, _proc, _object);
     *     }
     *   };
     * 
     *   void subclassUI() {
     *     new Subclass(Ctrl->getPlugin(pluginUI));
     *   }
     * @endcode
     */
    virtual bool subclassIMessageProc(Controler* sender, void*& proc, void*& object) = 0;

    /** 
     * Zwraca wtyczk�, kt�ra jako ostatnia u�ywa�a subclassIMessageProc()
     */
    virtual class oPlugin getLastSubclasser() = 0;

    /** 
     * Resetuje wszystkie zmiany spowodowane przez subclassIMessageProc()
     */
    virtual void resetSubclassing() = 0;

    /** 
     * Zwraca skr�con� nazw� sieci, kt�r� obs�uguje wtyczka (o ile obs�uguje)
     */
    virtual const Stamina::String& getNetShortName() = 0;

    /** 
     * Zwraca nazw� identyfikatora sieci, kt�r� obs�uguje wtyczka (o ile obs�uguje)
     */
    virtual const Stamina::String& getUIDName() = 0;

    tPluginId getId() {
      return getPluginId();
    }
    
    /** 
     * F-cja pomocnicza przy subclassowaniu kolejki
     */
    static inline int callIMessageProc(sIMessage_base* im, void* imessageProc, void* object) {
      if (object == 0) {
        return ((fIMessageProc) imessageProc)(im);
      } else {
        typedef int (__stdcall *fIMessageProcObject)(void*, sIMessage_base * msg);
        return ((fIMessageProcObject) imessageProc)(object, im);
      }
    }

  private:
    virtual void zz_ipl1() { }
    virtual void zz_ipl2() { }
    virtual void zz_ipl3() { }
    virtual void zz_ipl4() { }
    virtual void zz_ipl5() { }
    virtual void zz_ipl6() { }
    virtual void zz_ipl7() { }
    virtual void zz_ipl8() { }
    virtual void zz_ipl9() { }
  };

  class oPlugin: public Stamina::StaticPtr<iPlugin> {
  public:
    oPlugin(tPluginId pluginId) {
      setById(pluginId);
    }

    oPlugin(iPlugin & obj) {
      this->set(obj);
    }
    oPlugin(iPlugin * obj = 0) {
      this->set(obj);
    }
    oPlugin(const oPlugin & b) {
      this->set(*b);
    }
    oPlugin & operator = (const oPlugin & b) {
      this->set(*b);
      return *this;
    }

    void setById(tPluginId pluginId);
  };

  STAMINA_REGISTER_CLASS_VERSION(iPlugin);
};