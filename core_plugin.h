#pragma once

#include "core_object.h"

namespace Konnekt {
	enum enPluginId {
		pluginNotFound = -1
	};
	typedef enPluginId tPluginId;

	class iPlugin {
	public:
		virtual tPluginId __stdcall getPluginId()=0;
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

	class Plugin:public KStaticObject<iPlugin> {
	public:
		Plugin(tPluginId pluginId) {
			setById(pluginId);
		}
		Plugin() {
		}
		void setById(tPluginId pluginId);
	};

};