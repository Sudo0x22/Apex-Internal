#pragma once
#include"../../sdk/utils/dumper/dumper.h"
#define STATUS_SUCCESS 1
#define STATUS_ERROR 0

typedef const char* (__fastcall* print_to_screen)(char* format, ...);
print_to_screen o_print_to_screen;

class CMisc
{
private:
	NTSTATUS WINAPI UnlockAll() 
	{ 
		static bool enabled = false;
		if (misc::unlock_all) {
			*(long*)(global::g_hGameImage + 0x0221f440 + 0x6c) = 1;
			enabled = true;
		}
		else
		{
			if (enabled)
			{
				*(long*)(global::g_hGameImage + 0x0221f440 + 0x6c) = 0;
				enabled = false;
			}
		}

		return STATUS_SUCCESS;
	}
	NTSTATUS WINAPI FreeCam(CLocalEntity LocalEntity, UserCmd_t* pCmd)
	{
		static bool enabled = false;
		if (misc::free_cam)
		{
			*(int*)(LocalEntity.Entity + pInitOffsets.m_bSaverMode) = 7;
			enabled = true;
		}
		else
		{
			if (enabled)
			{
				*(int*)(LocalEntity.Entity + pInitOffsets.m_bSaverMode) = 0;
				enabled = true;
			}
		}
		return STATUS_SUCCESS;
	}
	NTSTATUS WINAPI TapStrafe(CLocalEntity LocalEntity, UserCmd_t* pCmd)
	{
		if (spoof_call::GetKey(VK_SPACE)) { mouse_event(MOUSEEVENTF_MIDDLEUP, 0, 0, 0, 0); }
		return STATUS_SUCCESS;
	}


	NTSTATUS WINAPI NoSpread(CLocalEntity LocalEntity)
	{
		uintptr_t pWeapon = *(uintptr_t*)(LocalEntity.Entity + 0x1954);
		pWeapon &= 0xffff;
		uintptr_t weapon_handle = *(uintptr_t*)(global::g_hGameImage + pInitOffsets.m_dwClientList + (pWeapon << 5));
		*(float*)(weapon_handle + pInitOffsets.m_wBulletScale) = 0;
		return TRUE;
	}
	NTSTATUS WINAPI SpeedHack()
	{
		if (pKeyInput->GetKeyState(VK_LSHIFT)) {
			*(float*)(global::g_hGameImage + pInitOffsets.m_iTimeScale + 0x68) = 5.f;
		}
		else {
			*(float*)(global::g_hGameImage + pInitOffsets.m_iTimeScale + 0x68) = 1;
		}
		return TRUE;
	}

	NTSTATUS WINAPI AutoGrapple()
	{
		Entity* local_entity = get_localEntity();

		if (local_entity == NULL) return FALSE;
		if (local_entity->isKnocked()) return FALSE;
		if (local_entity->health() == 0) return FALSE;

		unsigned long millseconds = 1000;

		int GrappleAttach = *(int*)(local_entity + pInitOffsets.m_bGrapple + pInitOffsets.m_bGrappleAttached);
		if (GrappleAttach == 1)
		{
			*(int*)(global::g_hGameImage + pInitOffsets.m_bInJump + 0x8) = 5;
			SpoofReturn(Sleep, millseconds);
			*(int*)(global::g_hGameImage + pInitOffsets.m_bInJump + 0x8) = 4;
		}
	}

	/*NTSTATUS WINAPI ChargeRifle(CLocalEntity LocalEntity)
	{
		bool attack = *(bool*)(global::g_hGameImage + offsets::offset_attack);

		uint64_t entitylist = global::g_hGameImage + offsets::cl_entitylist;
		uint64_t weapon_handle = *(uint64_t*)(LocalEntity.Entity + OFFSET_CURRENT_WEAPON);
		weapon_handle &= 0xffff;
		uint64_t weapon_entity = *(uint64_t*)(entitylist + (weapon_handle << 5));
		int weapon_index = *(int*)(weapon_entity + 0x1804);
		if (attack && weapon_index == 103)
			*(float*)(global::g_hGameImage + offsets::time_scale + 0x68) = 0.00000001;
		else
			*(float*)(global::g_hGameImage + offsets::time_scale + 0x68) = 1;
		return TRUE;
	}*/
	/*NTSTATUS WINAPI AutoSuperGlide(CLocalEntity LocalEntity) {
		static float startJumpTime = 0;
		static bool startSig = false;

		float WorldTime = *(float*)(LocalEntity.Entity + GameOffsets::timeBase);
		float m_traversalStartTime = *(float*)(LocalEntity.Entity + GameOffsets::m_traversalStartTime);
		float m_traversalProgress = *(float*)(LocalEntity.Entity + GameOffsets::m_traversalProgress);
		auto HangOnWall = -(m_traversalStartTime - WorldTime);

		if (m_traversalProgress > 0.87f && !startSig && HangOnWall > 0.05f && HangOnWall < 1.5f) {
			startJumpTime = WorldTime;
			startSig = true;
		}

		if (!HangOnWall)
			return FALSE;

		if (startSig) {
			*(int*)(global::g_hGameImage + GameOffsets::in_jump + 0x8) = 7;
			if ((WorldTime - startJumpTime) > 0.007) {
				*(int*)(global::g_hGameImage + GameOffsets::in_duck + 0x8) = 6;
			}
		}

		if ((WorldTime - startJumpTime) > 1.5f && startSig) {
			*(int*)(global::g_hGameImage + GameOffsets::in_jump + 0x8) = 4;
			*(int*)(global::g_hGameImage + GameOffsets::in_duck + 0x8) = 4;
			startSig = false;
		}

		return TRUE;
	}*/

	NTSTATUS WINAPI SpamChatBox()
	{
		Entity* local_entity = get_localEntity();
		if (local_entity == NULL)
			return FALSE;

		const float curTime = *(float*)(global::g_hGameImage + pInitOffsets.m_iTimeBase);
		static float NextSend = 0.0f;

		if (curTime > NextSend)
		{
			if (misc::chat_spam == true)
			{
				std::string spamMsg = SPAM_SYNC[Utils::RandIntSimple(0, ARRAYSIZE(SPAM_SYNC) - 1)];
				Utils::ReplaceSpecials(spamMsg);
				spamMsg.insert(0, "say ");
			}
		}

		return TRUE;
	}
public:
	NTSTATUS WINAPI Initialize(CLocalEntity LocalEntity, UserCmd_t* pCmd)
	{
		this->UnlockAll();
		this->FreeCam(LocalEntity, pCmd);
		if (misc::tap_strafe) { this->TapStrafe(LocalEntity, pCmd); }
		//if (misc::no_spread) { this->NoSpread(LocalEntity); }
		//this->FakeDuck(LocalEntity);
		if (misc::speed_hack) { this->SpeedHack(); }
		//if (misc::charge_rifle_exploit) { this->ChargeRifle(LocalEntity); }
		//if (misc::auto_super_glide) { this->AutoSuperGlide(LocalEntity); }
		if (misc::auto_grapple) { this->AutoGrapple(); }
		return STATUS_SUCCESS;
	}
}; CMisc* pMisc = new CMisc();