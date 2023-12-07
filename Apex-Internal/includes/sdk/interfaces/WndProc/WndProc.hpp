#pragma once
#include"../src/src.hpp"
extern "C" {namespace WndProc 
{
	LRESULT WINAPI Detour(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		SPOOF_FUNC
		if (pOverlay->render_overlay)
		{
			ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
			return TRUE;
		}
		return spoof_call::CallWndProc(pD3D11->oWndProc, hWnd, uMsg, wParam, lParam);
	}
}}