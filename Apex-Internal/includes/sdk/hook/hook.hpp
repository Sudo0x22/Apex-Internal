#include"../../features/overlay/overlay.hpp"
#include"minhook/include/MinHook.h"
#include<cassert>

extern "C" {namespace NTMakeHook
{
	MH_STATUS WINAPI NTCreateHook(LPVOID pFunction, LPVOID pDetour, LPVOID* pOriginal) {
		SPOOF_FUNC;
		return SpoofReturn(MH_CreateHook, pFunction, pDetour, pOriginal);
	}
	MH_STATUS WINAPI NTEnableHook(LPVOID pFunction) {
		SPOOF_FUNC;
		return SpoofReturn(MH_EnableHook, pFunction);
	}
	MH_STATUS WINAPI NTDisableHook(LPVOID pFunction) {
		SPOOF_FUNC;
		return SpoofReturn(MH_DisableHook, pFunction);
	}
	MH_STATUS WINAPI NTRemoveHook(LPVOID pFunction) {
		SPOOF_FUNC;
		return SpoofReturn(MH_RemoveHook, pFunction);
	}
	MH_STATUS WINAPI NTInitializeHook() {
		SPOOF_FUNC;
		return SpoofReturn(MH_Initialize);
	}
}}

class hook
{
public:
	class function
	{
	private:
		LPVOID m_pOriginals = nullptr;
	public:
		__forceinline bool make_hook(LPVOID pTarget, LPVOID pDetour)
		{
			return (NTMakeHook::NTCreateHook(pTarget, pDetour, &this->m_pOriginals) == MH_STATUS::MH_OK);
		}
	public:
		template<typename original>
		__inline original Orignal() const {
			return reinterpret_cast<original>(this->m_pOriginals);
		}
	public:
		__forceinline bool func_hook(LPVOID pFunction, LPVOID pDetour, LPVOID pOriginal)
		{
			return (NTMakeHook::NTCreateHook(pFunction, pDetour, &pOriginal) && NTMakeHook::NTEnableHook(pFunction));
		}
	public:
		__forceinline bool disable_hook(LPVOID pFunction)
		{
			NTMakeHook::NTDisableHook(pFunction);
			NTMakeHook::NTRemoveHook(pFunction);
			return true;
		}
	}; function* pFunction = new function();

	class table
	{
	private:
		DWORD** m_pBase = 0u;
		DWORD m_pSize = 0u;
		std::unique_ptr<LPVOID[]> m_pOriginals = {};
	public:
		__forceinline bool make_hook(const LPVOID pTable)
		{
			this->m_pBase = (DWORD**)(pTable);
			while (reinterpret_cast<DWORD*>(*this->m_pBase)[this->m_pSize])
				this->m_pSize += 1u;
			this->m_pOriginals = std::make_unique<LPVOID[]>(this->m_pSize);
			return (this->m_pBase && this->m_pSize);
		}
	public:
		__forceinline bool hook(LPVOID pDetour, const DWORD nIndex)
		{
			if (this->m_pBase && this->m_pSize)
				return (NTMakeHook::NTCreateHook((*reinterpret_cast<LPVOID**>(this->m_pBase))[nIndex], pDetour, &this->m_pOriginals[nIndex]) == MH_STATUS::MH_OK);
			return false;
		}
	public:
		template<typename original>
		__forceinline original Original(const DWORD nIndex) const 
		{
			return reinterpret_cast<original>(this->m_pOriginals[nIndex]);
		}
	};

	class create_hook
	{
	public:
		__forceinline bool make_hook(uint16_t nIndex, LPVOID* pOriginal, LPVOID pDetour)
		{
			SPOOF_FUNC;
			assert(_index >= 0 && _original != NULL && _detour != NULL);
			LPVOID pTarget = (LPVOID)MethodsTable[nIndex] ;
			if (NTMakeHook::NTCreateHook(pTarget, pDetour, pOriginal) != MH_OK || NTMakeHook::NTEnableHook(pTarget) != MH_OK) { return false; }
			return true;
		}
	public:
		__forceinline void remove_hook(uint16_t nIndex)
		{
			SPOOF_FUNC;
			assert(nIndex >= 0);
			NTMakeHook::NTDisableHook((LPVOID)MethodsTable[nIndex]);
			NTMakeHook::NTRemoveHook((LPVOID)MethodsTable[nIndex]);
		}
	}; create_hook* pCreateHook = new create_hook();

}; hook* pInitHook = new hook();