#pragma once
#include"windows/windows_api.h"


extern "C" {namespace spoof_call 
{
	HINSTANCE WINAPI GetModuleBase(_In_ LPCSTR szModuleName) { 
		return spoof_call_ex(jmp_rbx_0, __safecall(GetModuleHandleA).get(), szModuleName); }
	FARPROC WINAPI GetModuleProcAddr(_In_ HMODULE hModule, _In_ LPCSTR szModuleProc) { 
		return spoof_call_ex(jmp_rbx_0, __safecall(GetProcAddress).get(), hModule, szModuleProc); }
	LPVOID WINAPI SafeCopy(_In_ void* Source, _In_ const void* Detour, _In_ size_t Size) { 
		return spoof_call_ex(jmp_rbx_0, __safecall(memcpy).get(), Source, Detour, Size); }
	BOOL WINAPI GetKey(int Key) { 
		return spoof_call_ex(jmp_rbx_0, __safecall(GetAsyncKeyState).get(), Key); }
	BOOL WINAPI VirtualProcMem(_In_ LPVOID BaseAddr, _In_ SIZE_T BaseSize, _In_ DWORD OldProtect, _In_ PDWORD NewProtect) {
		return spoof_call_ex(jmp_rbx_0, __safecall(VirtualProtect).get(), BaseAddr, BaseSize, OldProtect, NewProtect); }
	LPVOID WINAPI VirtualAllocMem(_In_ LPVOID BaseAddr, _In_ SIZE_T BaseSize, _In_ DWORD AllocType, _In_ DWORD NewProtect) {
		return spoof_call_ex(jmp_rbx_0, __safecall(VirtualAlloc).get(), BaseAddr, BaseSize, AllocType, NewProtect); }
	
	
	HANDLE NTCreateRemoteThread(_In_ HANDLE hProcess, _In_ LPSECURITY_ATTRIBUTES Thread, _In_ SIZE_T Size, _In_ LPTHREAD_START_ROUTINE Entry, _In_ LPVOID Param, _In_ DWORD Flags, _In_ LPDWORD ThreadId) {
		return spoof_call_ex(jmp_rbx_0, __safecall(CreateRemoteThread).get(), hProcess, Thread, Size, Entry, Param, Flags, ThreadId); }
	
	
	HANDLE NTGetCurrentProcess() { 
		return spoof_call_ex(jmp_rbx_0, __safecall(GetCurrentProcess).get()); }
	
	
	BOOL _DeleteWindow(_In_ HWND hWindow) {
		return spoof_call_ex(jmp_rbx_0, __safecall(DestroyWindow).get(), hWindow); }
	
	
	ATOM WINAPI RegisterWndClas(_In_ const WNDCLASSEX* WndClass) {
		return spoof_call_ex(jmp_rbx_0, RegisterClassEx, WndClass); }
	
	
	ATOM WINAPI UnregisterWndClass(_In_ LPCWSTR Class, _In_ HINSTANCE hInst) {
		return spoof_call_ex(jmp_rbx_0, UnregisterClass, Class, hInst); }
	
	
	VOID WINAPI SleepThread(_In_ DWORD Time) {
		SPOOF_FUNC;
		return spoof_call_ex(jmp_rbx_0, __safecall(Sleep).get(), Time); }
	
	
	LPVOID WINAPI SafeMemSet(_In_ void* ptr, _In_ int Value, _In_ size_t size) {
		//return SpoofReturn(__safecall(memset).get(), ptr, Value, size); }}
		SPOOF_FUNC;
		return spoof_call_ex(jmp_rbx_0, __safecall(memset).get(), ptr, Value, size);
	}
	LRESULT WINAPI CallWndProc(_In_ WNDPROC WndProc, _In_ HWND hWnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam) {
		//return SpoofReturn(CallWindowProcW, WndProc, hWnd, uMsg, wParam, lParam); }
		SPOOF_FUNC;
		return spoof_call_ex(jmp_rbx_0, CallWindowProcW, WndProc, hWnd, uMsg, wParam, lParam);
	}
		
	LRESULT WINAPI DefWndProc(_In_ HWND hWnd, _In_ UINT uMsg, _In_  WPARAM wParam, _In_ LPARAM lParam) {
		return SpoofReturn(DefWindowProc, hWnd, uMsg, wParam, lParam); }
	
	
	HWND WINAPI NtCreateWindow(_In_ DWORD Exit, _In_ LPCWSTR Class, _In_ LPCWSTR Name, _In_ DWORD Style, _In_ int x, _In_ int y, _In_ int w, _In_ int h,
		_In_ HWND hWindow, _In_ HMENU hMenu, _In_ HINSTANCE hInst, _In_ LPVOID Param) {
		return spoof_call_ex(jmp_rbx_0, CreateWindowExW, Exit, Class, Name, Style, x, y, w, h, hWindow, hMenu, hInst, Param); }
	
	
	int __cdecl NtStrCmp(_In_ const char* offset, _In_ const char* pointer) {
		return SpoofReturn(__safecall(strcmp).get(), offset, pointer); }
	
	
	size_t __cdecl StrLen(_In_ const char* offset) {
		return SpoofReturn(__safecall(strlen).get(), offset); }
	
	
	BOOL WINAPI NtGetModuleInformation(_In_ HANDLE hProcess, _In_ HMODULE hModule, _In_ LPMODULEINFO Info, _In_ DWORD cb) {
		return spoof_call_ex(jmp_rbx_0, __safecall(K32GetModuleInformation).get(), hProcess, hModule, Info, cb); }
	
	
	LONG_PTR WINAPI NtSetWindowLongPtr(_In_ HWND hWindow, _In_ INT hIndex, _In_ LONG_PTR dwLong) {
		SPOOF_FUNC
			//return SpoofReturn(__safecall(SetWindowLongPtrW,).get(), hWindow, hIndex, dwLong); }
			return spoof_call_ex(jmp_rbx_0, __safecall(SetWindowLongPtrW).get(), hWindow, hIndex, dwLong);
	}
		
	LRESULT WINAPI NtDefWndProc(_In_ HWND hWindow, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam) {
		return SpoofReturn(DefWindowProc, hWindow, uMsg, wParam, lParam);  }
	
	
	LPVOID WINAPI NtCalloc(_In_ size_t base, _In_ size_t address) {
		SPOOF_FUNC;
		//return SpoofReturn(__safecall(calloc).get(), base, address); 
		return spoof_call_ex(jmp_rbx_0, __safecall(calloc).get(), base, address);
	}
}}
