#pragma once
#include"../scanner/scanner.hpp"

namespace offsets_modules 
{
	inline DWORD64 module_base = (DWORD64)m_pMemory->pNTModules->NtGetModuleHandleExW(__("r5apex.exe"));
}

class Offsets
{
public:
	uintptr_t m_dwClientList = 0x00;
	uintptr_t m_dwLocalEntity = 0x00;
	
	uintptr_t m_vLocalOrigin = 0x00;
	uintptr_t m_sLevel = 0x00;
	uintptr_t m_sName = 0x00;
	
	uintptr_t m_vViewMatrix = 0x00;
	uintptr_t m_vViewRender = 0x00;
	uintptr_t m_iTeamNum = 0x00;
	
	uintptr_t m_iHealth = 0x00;
	uintptr_t m_iMaxShield = 0x00;
	uintptr_t m_iShield = 0x00;
	uintptr_t m_iArmorType = 0x00;
	
	uintptr_t m_iBleedOutState = 0x00;
	uintptr_t m_iVisibleTime = 0x00;
	uintptr_t m_vAbsVelocity = 0x00;
	
	uintptr_t m_vCameraPos = 0x00;
	uintptr_t m_vViewAngles = 0x00;
	uintptr_t m_vBreathAngles = 0x00;
	
	uintptr_t m_vAimPunch = 0x00;
	uintptr_t m_vBones = 0x00;
	uintptr_t m_bThirdPerson = 0x00;

	uintptr_t m_iNameList = 0x00;
	uintptr_t m_bGrapple = 0x00;
	uintptr_t m_bGrappleActive = 0x00;
	uintptr_t m_bGrappleAttached = 0x00;

	uintptr_t m_bInJump = 0x00;
	uintptr_t m_bInAttack = 0x00;
	uintptr_t m_bInForward = 0x00;
	uintptr_t m_bInDuck = 0x00;

	uintptr_t m_bInReload = 0x00;
	uintptr_t m_bInUse = 0x00;

	uintptr_t m_iTraversalStartTime = 0x00;
	uintptr_t m_iTraversalProgress = 0x00;
	uintptr_t m_iTimeScale = 0x00;

	uintptr_t m_iTimeBase = 0x00;
	uintptr_t m_iStudioHDR = 0x00;

	uintptr_t m_iLifeState = 0x00;
	uintptr_t m_vYaw = 0x00;
	uintptr_t m_vCrosshairLast = 0x00;

	uintptr_t m_wWeapon = 0x00;
	uintptr_t m_wOffWeapon = 0x00;
	uintptr_t m_wWeaponName = 0x00;
	uintptr_t m_iIteamId = 0x00;

	uintptr_t m_wSkin = 0x00;
	uintptr_t m_wBulletSpeed = 0x00;
	uintptr_t m_wBulletScale = 0x00;

	uintptr_t m_wAmmo = 0x00;
	uintptr_t m_iZoomFov = 0x00;

	uintptr_t m_bGlowEnable = 0x00;
	uintptr_t m_bGlowEnableThroughWalls = 0x00;
	
	uintptr_t m_bGlowColorR = 0x00;
	uintptr_t m_bGlowColorG = 0x00;
	uintptr_t m_bGlowColorB = 0x00;

	uintptr_t m_bGlowType = 0x00;
	uintptr_t m_bGlowVisibleType = 0x00;
	uintptr_t m_bGlowLifeTime = 0x00;

	uintptr_t m_bGlowDistance = 0x00;
	uintptr_t m_bGlowActive = 0x00;

	uintptr_t m_vecPunchWeapon_Angle = 0x00;
	uintptr_t m_bSaverMode = 0x00;

};

class InitOffsets : public Offsets
{
public:
	__declspec(dllexport) bool Initialize()
	{
		this->m_dwClientList = 0x1d71858;
		this->m_dwLocalEntity = 0x211fac8;
		this->m_vLocalOrigin = 0x017c;
		this->m_sLevel = 0x16966f0;

		this->m_sName = 0x04b9;
		this->m_vViewMatrix = 0x11a350;
		this->m_vViewRender = 0x7389d40;

		this->m_iTeamNum = 0x037c;
		this->m_iHealth = 0x036c;
		this->m_iMaxShield = 0x01a4;
		this->m_iArmorType = 0x4634;

		this->m_iShield = 0x01a0;
		this->m_iBleedOutState = 0x2710;
		this->m_iVisibleTime = 0x19b8 + 0x8;

		this->m_vAbsVelocity = 0x0170;
		this->m_vCameraPos = 0x1f00;
		this->m_vViewAngles = 0x2564 - 0x14;

		this->m_vBreathAngles = 0x2564 - 0x14 - 0x10;
		this->m_vAimPunch = 0x2468;

		this->m_vBones = 0x0dd0 + 0x48;
		this->m_bThirdPerson = 0x01cfa4d0 + 0x6c;

		this->m_iNameList = 0xc26e750;
		this->m_bSaverMode = 0x34c4;

		this->m_bGrapple = 0x2c78;
		this->m_bGrappleActive = 0x2d08;
		this->m_bGrappleAttached = 0x0048;

		this->m_bInJump = 0x0738b0a0;
		this->m_bInAttack = 0x0738af90;
		this->m_bInForward = 0x0738b1d0;
		this->m_bInDuck = 0x0738b190;

		this->m_bInReload = 0x0738b000;
		this->m_bInUse = 0x0738b110;

		this->m_iTraversalStartTime = 0x2b30;
		this->m_iTraversalProgress = 0x2b2c;

		this->m_iTimeBase = 0x20b8;
		this->m_iStudioHDR = 0x1020;

		this->m_iLifeState = 0x06c8;
		this->m_vYaw = 0x226c - 0x8;
		this->m_vCrosshairLast = 0x00;

		this->m_wWeapon = 0x1964;
		this->m_wOffWeapon = 0x1974;
		this->m_wWeaponName = 0x17a8;
		this->m_iIteamId = 0x1588;

		this->m_wSkin = 0x0d88;
		this->m_wBulletSpeed = (0x19e0 + 0x04dc);
		this->m_wBulletScale = (0x19e0 + 0x04e4);

		this->m_wAmmo = 0x15b0;
		this->m_iZoomFov = 0x1600 + 0xb8;

		this->m_bGlowEnable = 0x294;
		this->m_bGlowEnableThroughWalls = 0x278;

		this->m_bGlowColorR = 0x1D0 + 0x30;
		this->m_bGlowColorG = 0x1D4 + 0x30;
		this->m_bGlowColorB = 0x1D8 + 0x30;

		this->m_bGlowType = 0x29c;
		this->m_bGlowVisibleType = 0x278;
		this->m_bGlowLifeTime = 0x3A4;

		this->m_bGlowDistance = 0x26c;
		this->m_bGlowActive = 0x298;

		this->m_vecPunchWeapon_Angle = 0xB5CC530;
		this->m_iTimeScale = 0x01702ff0;

		return true;
	}
}; InitOffsets pInitOffsets;