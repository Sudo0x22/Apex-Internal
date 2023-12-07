#include"../includes/includes.hpp"

class InitModules
{
public:
	NTSTATUS WINAPI GetGlobals(HMODULE hModule)
	{
		SPOOF_FUNC;
		global::g_hInst = hModule;
		global::g_hGameImage = (DWORD64)m_pMemory->pNTModules->NtGetModuleHandleExW(NULL);
		global::g_dwModuleSize = m_pMemory->pNtImages->NtGetModuleSize((DWORD64)hModule);
		return TRUE;
	}

	NTSTATUS WINAPI CallThreads()
	{
		SPOOF_FUNC;
		const auto present_thread = pThread->pNtCreateThread->NtCreateThreadEx((LPTHREAD_START_ROUTINE)present::hook_present, 0, 0);
		const auto features_thread = pThread->pNtCreateThread->NtCreateThreadEx((LPTHREAD_START_ROUTINE)FeaturesThread, 0, 0);

		if (present_thread && features_thread) {
			pThread->pNtCreateThread->NtCloseHandle((HANDLE)present_thread);
			pThread->pNtCreateThread->NtCloseHandle((HANDLE)features_thread);
		}

		return TRUE;
	}

}; InitModules pInitModules ;

__declspec() attach* attach::init_thread(HMODULE hModule, void* hBuffer)
{
	SPOOF_FUNC;
	while(!m_pMemory->pNTModules->NtGetModuleHandleExW(__("r5apex.exe")))
		spoof_call::SleepThread(420);

	pInitModules.GetGlobals(hModule);
	
	InitInterfaces::Initialize();	
	pInitOffsets.Initialize();
	EasyAntiCheat::Initialize();
	
	pInitModules.CallThreads();

	return nullptr;
}

BOOL __stdcall DllMain(HMODULE hModule, DWORD hReasons, LPVOID hBuffer)
{
	SPOOF_FUNC;
	if (hReasons != DLL_PROCESS_ATTACH) return FALSE;

	pAttach->init_thread(hModule, hBuffer);

	return TRUE;
}

