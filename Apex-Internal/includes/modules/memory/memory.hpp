#pragma once
#include"../security/global.h"
#include "../spoofer/call_stack_spoofer.hpp"

#define MAXBUFFER 1024
#define STATUS_SUCCESS 1
#define STATUS_ERROR 0

typedef struct _SYSTEM_MEMORY
{
	DWORD64 dwEP;
	LPVOID dwParam;
	SIZE_T dwSize;
	SIZE_T* dwBytes;
	LPVOID dwBaseAddress;
	HANDLE dwProcess;
	LPVOID dwAddress;
	LPCVOID dwBufferAddress;
	DWORD dwProtect;
	PDWORD dwNewProtect;
	DWORD dwAllocType;
	BOOL dwWrite;
	BOOL dwRead;
	HINSTANCE dwModule;
	DWORD64 dwModuleSize;
	PBYTE dwModuleMemory;
} SYSTEM_MEMORY, * PSYSTEM_MEMORY;
typedef DWORD(*INIT_MEM)(LPVOID P);

inline HANDLE DriverHandle;
inline HWND hWindow = NULL;
inline DWORD ProcessId;

typedef struct _NULL_MEMORY {
	void* buffer_address;
	UINT_PTR address;
	ULONGLONG size;
	ULONG pid;
	BOOLEAN write;
	BOOLEAN read;
	BOOLEAN req_base;
	void* output;
	const char* module_name;
	ULONG64 base_address;
}NULL_MEMORY;

struct HandleDisposer {
	using pointer = HANDLE;
	void operator()(HANDLE handle) const {
		if (handle != NULL || handle != INVALID_HANDLE_VALUE) {
			CloseHandle(handle);
		}
	}
};

inline uintptr_t oBaseAddress = 0;
inline std::uint32_t oProcId = 0;
using unique_handle = std::unique_ptr<HANDLE, HandleDisposer>;

template<typename ... Arg>
inline uint64_t call_hook(const Arg ... Args) {
	void* hook_func = spoof_call_ex(jmpRdx, GetProcAddress, LoadLibraryA("win32u.dll"), "NtGdiDdDDINetDispGetNextChunkInfo");
	auto func_addr = static_cast<uint64_t(__stdcall*)(Arg...)>(hook_func);
	return func_addr(Args ...);
}

namespace driver {
	inline static ULONG64 GetModuleBaseAddress(std::uint32_t, const char* module_name) {
		NULL_MEMORY Inst = { 0 };
		Inst.pid = oProcId;
		Inst.req_base = TRUE;
		Inst.read = FALSE;
		Inst.write = FALSE;
		Inst.module_name = module_name;
		call_hook(&Inst);

		ULONG64 Base = 0;
		Base = Inst.base_address;
		return Base;
	}

	template<typename Type>
	inline Type DriverRead(unsigned long long int addr) {
		Type Response{};
		NULL_MEMORY Inst{};
		Inst.pid = oProcId;
		Inst.size = sizeof(Type);
		Inst.address = addr;
		Inst.read = TRUE;
		Inst.write = FALSE;
		Inst.req_base = FALSE;
		Inst.output = &Response;
		call_hook(&Inst);
		return Response;
	}

	template<typename Type>
	inline Type DriverReadMem(unsigned long long int addr, int length) {
		Type Response{};
		NULL_MEMORY Inst{};
		Inst.pid = oProcId;
		Inst.size = length;
		Inst.address = addr;
		Inst.read = TRUE;
		Inst.write = FALSE;
		Inst.output = &Response;
		call_hook(&Inst);
		return Response;
	}

	inline bool DriverWriteAll(unsigned long long int addr, UINT_PTR Value, SIZE_T WriteSize) {
		NULL_MEMORY Inst{};
		Inst.address = addr;
		Inst.pid = oProcId;
		Inst.write = TRUE;
		Inst.read = FALSE;
		Inst.req_base = FALSE;
		Inst.buffer_address = (void*)Value;
		Inst.size = WriteSize;
		call_hook(&Inst);
		return true;
	}

	template<typename Type>
	inline bool DriverWriteToReadOnlyMemory(UINT_PTR WriteAddress, const Type& Value) {
		return DriverWriteAll(WriteAddress, (UINT_PTR)&Value, sizeof(Type));
	}
}

extern "C" {namespace thread {
	NTSTATUS WINAPI InitThread(PSYSTEM_MEMORY pMemory) {
		SPOOF_FUNC;
		if (pMemory != NULL && pMemory->dwEP) {
			INIT_MEM CALL_MEM = (INIT_MEM)pMemory->dwEP;
			CALL_MEM(pMemory->dwParam);
		}
		return STATUS_SUCCESS;
	}
}}

