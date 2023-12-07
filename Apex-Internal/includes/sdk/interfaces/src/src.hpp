#pragma once
#include"Client/client.hpp"

bool unload = false;
__declspec() NTSTATUS WINAPI FeaturesThread(LPVOID hBuffer)
{
	while (!unload)
	{
		UserCmd_t* pCmd = nullptr;
		CLocalEntity LocalEntity = CLocalEntity(offsets_modules::module_base,
			pInitOffsets.m_dwLocalEntity);

		static Vector3 ViewAngles = pCmd->m_vecViewAngles;
		static float forward_move = pCmd->m_flForwardmove;
		static float side_move = pCmd->m_flSidemove;

		Entity* local_entity = get_localEntity();

		if (LocalEntity.Entity || LocalEntity.IsAlive(pInitOffsets.m_iHealth))
		{
			pAimbot->Initialize(LocalEntity, pCmd);
			pVisuals->Initialize(LocalEntity);
			pAntiAim->Initialize();
			pMisc->Initialize(LocalEntity, pCmd);
		}
	}
	return STATUS_SUCCESS;
}
