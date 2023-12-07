#pragma once
#include"../../../modules/modules.hpp"

class KeyInput
{
public:
	BOOL WINAPI GetKeyState(INT KEY_CODE) {
		SPOOF_FUNC;
		return spoof_call_ex(jmp_rbx_0, __safecall(GetAsyncKeyState).get(), KEY_CODE);
	}
	BOOL WINAPI ExitThreadKey(INT KEY_CODE) {
		return FALSE;
	}
}; KeyInput* pKeyInput;