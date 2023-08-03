#include"../includes/includes.hpp"

class InitModules
{
public:
	NTSTATUS WINAPI GetGlobals(HMODULE hModule)
	{
		global::g_hInst = hModule;
		global::g_hGameImage = (DWORD64)m_pMemory->pNTModules->NtGetModuleHandleExW(NULL);
		global::g_dwModuleSize = m_pMemory->pNtImages->NtGetModuleSize((DWORD64)hModule);
		return TRUE;
	}

	NTSTATUS WINAPI CallThreads()
	{
		pThread->pNtCreateThread->NtCreateThreadEx((LPTHREAD_START_ROUTINE)present::hook_present, 0, 0);
		pThread->pNtCreateThread->NtCreateThreadEx((LPTHREAD_START_ROUTINE)FeaturesThread, 0, 0);
		return TRUE;
	}
}; InitModules pInitModules ;

__declspec() attach* attach::init_thread(HMODULE hModule, void* hBuffer)
{
	while(!m_pMemory->pNTModules->NtGetModuleHandleExW(__("EasyAntiCheat_launcher.exe")))
		spoof_call::SleepThread(420);

	pInitModules.GetGlobals(hModule);
	//pDumper.Initialize();
	pInitModules.CallThreads();

	return nullptr;
}

__declspec() attach* attach::attach_process(HMODULE hModule, DWORD hReasons, LPVOID hBuffer)
{
	if (hReasons != DLL_PROCESS_ATTACH) return nullptr;
	pAttach->init_thread(hModule, hBuffer);
}

BOOL __stdcall DllMain(HMODULE hModule, DWORD hReasons, LPVOID hBuffer)
{
	pAttach->attach_process(hModule, hReasons, hBuffer);
	return TRUE;
}

