#pragma once
#include"../WndProc/WndProc.hpp"

extern "C" {namespace Cursor
{
	BOOL WINAPI cursor_hk(bool open) 
	{
		if (pOverlay->render_overlay)
			return FALSE;
		return pD3D11->oCursor(open);
	}

	BOOL WINAPI show_cursor(int x, int y) 
	{
		return SpoofReturn(__safecall(SetCursorPos).get(), x, y); 
	}

	NTSTATUS WINAPI init_hook(LPVOID pFunction, LPVOID pDetour, LPVOID* pOriginal)
	{
		if (NTMakeHook::NTCreateHook(pFunction, pDetour, pOriginal) != MH_OK)
			return FALSE;
		if (NTMakeHook::NTEnableHook(pFunction) != MH_OK)
			return FALSE;
		return TRUE;
	}

	NTSTATUS WINAPI remove_hook(LPVOID pFunc)
	{
		NTMakeHook::NTDisableHook(pFunc);
		NTMakeHook::NTRemoveHook(pFunc);
		return TRUE;
	}
}}