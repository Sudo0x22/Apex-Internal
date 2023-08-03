#pragma once
#include"Prediection/Prediction.hpp"
#include"../../sdk/apex_src/apex_src.hpp"
#include"../../sdk/utils/memory/memory.h"
#include"../Misc/Misc.h"

class Hitbox
{
public:
	int TargetHitbox()
	{
		switch (aimbot::hitboxes::player_hitbox_items)
		{
		case 0:
			return 10;
			break;
		case 1:
			return 9;
			break;
		case 2:
			return 8;
			break;
		case 3:
			return 7;
			break;
		case 4:
			return 6;
			break;
		default:
			return 8;
		}
	}
}; Hitbox* pHitbox = new Hitbox();

class CAimbot
{
private:
	NTSTATUS WINAPI SlientAim(CLocalEntity LocalEntity, UserCmd_t* pCmd) 
	{ 
		if (!LocalEntity.Entity)
			return STATUS_ERROR;

		return STATUS_SUCCESS;
	}
	NTSTATUS WINAPI SmoothAim(CLocalEntity LocalEntity, UserCmd_t* pCmd) 
	{
		if (!LocalEntity.Entity)
			return STATUS_ERROR;

		CBaseEntity BaseEntity = CBaseEntity();
		for (int index = 0; index < 100; index++)
		{
			DWORD64 Entity = BaseEntity.GetEntityIndex(global::g_hGameImage, offsets::cl_entitylist, index, 32);
			
			if (!Entity || Entity == LocalEntity.Entity)
				continue;

			DWORD64 EntityTeam = *(DWORD64*)(Entity + Classes::CBaseEntity::m_iTeamNum);
			DWORD64 LocalTeam = *(DWORD64*)(LocalEntity.Entity + Classes::CBaseEntity::m_iTeamNum);

			if (EntityTeam == LocalTeam)
				continue;

			CGlobalVars GlobalVars = *(CGlobalVars*)(offsets_modules::module_base + offsets::global_vars);

			if (!BaseEntity.IsVisible(GlobalVars.curtime, 0x00))
				continue;
			
			if (!aimbot::draw_aim_fov)
				continue;
			
			if (!abs(aimbot::aim_fov))
				continue;
			
			if (!pKeyInput->GetKeyState(VK_RBUTTON))
				continue;

			Vector3 EntityPos = BaseEntity.Postition(Classes::CPlayer::m_vecAbsOrigin);
			Vector3 target_bone = BaseEntity.BonePostition(pHitbox->TargetHitbox(),
				Classes::CPlayer::m_vecAbsOrigin, Classes::CRopeKeyframe::m_bConstrainBetweenEndpoints);
			
			LocalEntity.SetViewAngles(Classes::CPlayer::m_view_angles, EntityPos);
			LocalEntity.SetViewAngles(Classes::CPlayer::m_view_angles, target_bone);
		}

		return STATUS_SUCCESS;
	}
private:
	NTSTATUS WINAPI InitAimbot(CLocalEntity LocalEntity, UserCmd_t* pCmd)
	{
		if (!aimbot::enable_aimbot)
			return STATUS_ERROR;

		if (aimbot::smooth_aim) { this->SmoothAim(LocalEntity, pCmd); }
		if (aimbot::slient_aim) { this->SlientAim(LocalEntity, pCmd); }
		
		return STATUS_SUCCESS;
	}
	NTSTATUS WINAPI NoRecoil(CLocalEntity LocalEnity, UserCmd_t* pCmd)
	{
		if (!aimbot::no_recoil)
			return STATUS_ERROR;
		
		Vector3 oPunch{ 0,0,0 };
		Vector3 AimPunch = LocalEnity.GetAimPunch(Classes::CPlayer::m_vecPunchWeapon_Angle) * (0.500f * 2);

		if (spoof_call::GetKey(VK_LBUTTON)) 
		{
			Vector3 ViewAngles = LocalEnity.GetViewAngles(Classes::CPlayer::m_view_angles);
			Vector3 NewAngle = ViewAngles + oPunch - AimPunch;
			LocalEnity.SetViewAngles(Classes::CPlayer::m_view_angles, NewAngle);
		}

		oPunch = AimPunch;
		
		return STATUS_SUCCESS;
	}
public:
	NTSTATUS WINAPI Initialize(CLocalEntity LocalEntity, UserCmd_t* pCmd)
	{
		this->InitAimbot(LocalEntity, pCmd);
		this->NoRecoil(LocalEntity, pCmd);
		return STATUS_SUCCESS;
	}
}; CAimbot* pAimbot = new CAimbot();