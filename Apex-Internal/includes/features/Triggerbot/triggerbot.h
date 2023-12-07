#pragma once
#include"../Aimbot/Aimbot.hpp"

class CTriggerbot
{
private:
	NTSTATUS WINAPI ToggleTriggerbot(CLocalEntity LocalEntity)
	{
		return STATUS_SUCCESS;
	}
public:
	NTSTATUS WINAPI Initialize(CLocalEntity LocalEntity)
	{
		if (triggerbot::enable_trigger_bot) { this->ToggleTriggerbot(LocalEntity); }
		return TRUE;
	}
}; CTriggerbot* pTriggerbot = new CTriggerbot();