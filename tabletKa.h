#pragma once

#ifndef SHARED_TABLETKA_H
#define SHARED_TABLETKA_H

namespace Tabs
{ 
	const int net = 306;
	namespace IM
	{
		const int GetTabWindow = IM_USER+1;		// Zwr�ci uchwyt okna tab�w (zbiorczego)
		const int GetCurrentCnt = IM_USER+2;	// Zwr�ci aktywny tab (cntId)
		const int GetCurrentWnd = IM_USER+3;	// Zwr�ci aktywny tab (hwnd okna)
		const int GetWindowState = IM_USER+4;	// U�ywa� poprzez Tabs::GetWindowstate(cnt)
	};
	inline int GetWindowState(int cnt) // Zwraca te same warto�ci co IMI_MSG_WINDOWSTATE
	{
		if(ICMessage(IMC_FINDPLUG, Tabs::net, IMT_ALL)) // Ten spos�b jest niezawodny
		{
			return IMessage(Tabs::IM::GetWindowState, Tabs::net,IMT_ALL, cnt, 0);
		}
		else
		{
			return IMessage(IMI_MSG_WINDOWSTATE, 0, IMT_ALL, cnt, 0);
		}
	}
};
#endif
