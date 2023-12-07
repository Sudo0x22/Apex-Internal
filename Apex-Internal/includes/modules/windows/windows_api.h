#pragma once
#include"../spoofer/spoofer.hpp"
#include"../memory/memory.hpp"
#include"../security/global.h"
#include"../spoofer/call_stack_spoofer.hpp"

#pragma section(".text")
__declspec(allocate(".text")) const unsigned char jmp_rbx_0[] = { 0xff, 0x23 };//jmp qword ptr[rbx]

class Memory
{
public:
	class NTVirtualAllocEx
	{
	public:
		LPVOID WINAPI NtVirtualAllocExW(LPVOID BaseAddr, SIZE_T Size, DWORD AllocType, DWORD Protect) {
			SPOOF_FUNC;
			//return SpoofReturn(__safecall(VirtualAlloc).get(), BaseAddr, Size, AllocType, Protect);
			return spoof_call_ex(jmp_rbx_0, __safecall(VirtualAlloc).get(), BaseAddr, Size, AllocType, Protect);
		}
	}; NTVirtualAllocEx* pNTVirtualAllocEx = new NTVirtualAllocEx();
	class NTVirtualProtect
	{
	public:
		BOOL WINAPI NtVirtualProtectExW(LPVOID BaseAddr, SIZE_T Size, DWORD OldProtect, PDWORD NewProtect) {
			SPOOF_FUNC;
			//return SpoofReturn(__safecall(VirtualProtect).get(), BaseAddr, Size, OldProtect, NewProtect);
			return spoof_call_ex(jmp_rbx_0, __safecall(VirtualProtect).get(), BaseAddr, Size, OldProtect, NewProtect);
		}
	}; NTVirtualProtect* pNTVirtualProtect = new NTVirtualProtect();
public:
	class NTModules
	{
	public:
		HMODULE WINAPI NtGetModuleHandleExW(LPCSTR ModuleName) {
			SPOOF_FUNC;
			//return SpoofReturn(__safecall(GetModuleHandleA).get(), ModuleName);
			return spoof_call_ex(jmp_rbx_0, __safecall(GetModuleHandleA).get(), ModuleName);
		}
		FARPROC WINAPI NtGetProcAddress(HMODULE hModule, LPCSTR ProcAddr) {
			SPOOF_FUNC;
			//return SpoofReturn(__safecall(GetProcAddress).get(), hModule, ProcAddr);
			return spoof_call_ex(jmp_rbx_0, __safecall(GetProcAddress).get(), hModule, ProcAddr);
		}
		HANDLE NTGetCurrentProcess() {
			SPOOF_FUNC;
			//return SpoofReturn(__safecall(GetCurrentProcess).get());
			return spoof_call_ex(jmp_rbx_0, __safecall(GetCurrentProcess).get());
		}
	}; NTModules* pNTModules = new NTModules();
public:
	class NtImages
	{
	public:
		DWORD64 WINAPI NtGetModuleSize(DWORD64 ModuleImage)
		{
			SPOOF_FUNC;
			IMAGE_DOS_HEADER dos_header = *(IMAGE_DOS_HEADER*)ModuleImage;
			IMAGE_NT_HEADERS nt_headers = *(IMAGE_NT_HEADERS*)(ModuleImage + dos_header.e_lfanew);
			return (DWORD64)nt_headers.OptionalHeader.SizeOfImage;
		}
		PBYTE WINAPI NtGetModuleBytes(HMODULE hModule, DWORD64 hSize, DWORD64 HexCode) {
			SPOOF_FUNC;
			return (PBYTE)hModule + hSize - HexCode;
		}
	}; NtImages* pNtImages = new NtImages();
public:
	class NtMemCopy
	{
	public:
		LPVOID WINAPI NtMemCopyEx(void* src, const void* det, size_t size) {
			SPOOF_FUNC;
			//return SpoofReturn(__safecall(memcpy).get(), src, det, size);
			return spoof_call_ex(jmp_rbx_0, __safecall(memcpy).get(), src, det, size);
		}
	}; NtMemCopy* pNtMemCopy = new NtMemCopy();
}; Memory* m_pMemory = new Memory();

class Thread
{
public:
	class NtCreateThread
	{
	public:
		BOOL WINAPI NtCloseHandle(HANDLE hModule)
		{
			SPOOF_FUNC;
			//return SpoofReturn(__safecall(CloseHandle).get(), hModule);
			return spoof_call_ex(jmp_rbx_0, __safecall(CloseHandle).get(), hModule);
		}
	public:
		HANDLE WINAPI NtRemoteThread(_In_ HANDLE hProcess, _In_ LPSECURITY_ATTRIBUTES Thread, 
			_In_ SIZE_T Size, _In_ LPTHREAD_START_ROUTINE Entry, _In_ LPVOID Param, _In_ DWORD Flags, _In_ LPDWORD ThreadId) {
			SPOOF_FUNC;
			//return SpoofReturn(__safecall(CreateRemoteThread).get(), hProcess, Thread, Size, Entry, Param, Flags, ThreadId);
			return spoof_call_ex(jmp_rbx_0, __safecall(CreateRemoteThread).get(), hProcess, Thread, Size, Entry, Param, Flags, ThreadId);
		}
	public:
		NTSTATUS WINAPI NtCreateThreadEx(LPTHREAD_START_ROUTINE EntryPoint, LPVOID Buffer, LPDWORD ThreadId)
		{
			SPOOF_FUNC;
			LPVOID Address = m_pMemory->pNTVirtualAllocEx->NtVirtualAllocExW(NULL, 0x100, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
			PSYSTEM_MEMORY pMemory = (PSYSTEM_MEMORY)Address;

			pMemory->dwModule = m_pMemory->pNTModules->NtGetModuleHandleExW(skCrypt("ntdll.dll").decrypt());
			pMemory->dwModuleSize = m_pMemory->pNtImages->NtGetModuleSize((DWORD64)pMemory->dwModule);
			pMemory->dwModuleMemory = m_pMemory->pNtImages->NtGetModuleBytes(pMemory->dwModule, pMemory->dwModuleSize, 0x400);

			m_pMemory->pNTVirtualProtect->NtVirtualProtectExW(pMemory->dwModuleMemory, 0x100, PAGE_EXECUTE_READWRITE, &pMemory->dwProtect);
			pMemory->dwEP = (DWORD64)(EntryPoint);
			pMemory->dwParam = Buffer;

			m_pMemory->pNtMemCopy->NtMemCopyEx((LPVOID)pMemory->dwModuleMemory, (LPVOID)thread::InitThread, 0x100);
			HANDLE hRemoteThread = this->NtRemoteThread(m_pMemory->pNTModules->NTGetCurrentProcess(), 0, 0x100, (LPTHREAD_START_ROUTINE)pMemory->dwModuleMemory, pMemory, 0, ThreadId);
			this->NtCloseHandle(hRemoteThread);
			return STATUS_SUCCESS;
		}
	}; NtCreateThread* pNtCreateThread = new NtCreateThread();
}; Thread* pThread = new Thread();