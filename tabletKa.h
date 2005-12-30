#pragma once

#ifndef SHARED_TABLETKA_H
#define SHARED_TABLETKA_H

namespace Tabs
{ 
	const int net = 306;
	namespace IM
	{
		const int GetTabWindow = IM_USER+1;		// Zwróci uchwyt okna tabów (zbiorczego)
		const int GetCurrentCnt = IM_USER+2;	// Zwróci aktywny tab (cntId)
		const int GetCurrentWnd = IM_USER+3;	// Zwróci aktywny tab (hwnd okna)
		const int GetWindowState = IM_USER+4;	// U¿ywaæ poprzez Tabs::GetWindowstate(cnt)
	};
	inline int GetWindowState(int cnt) // Zwraca te same wartoœci co IMI_MSG_WINDOWSTATE
	{
		if(ICMessage(IMC_FINDPLUG, Tabs::net, IMT_ALL)) // Ten sposób jest niezawodny
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
