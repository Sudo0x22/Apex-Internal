#pragma once
#include"../Aimbot/Aimbot.hpp"
#include"../../sdk/utils/utils.hpp"

class VisualFeatures
{
public:
	NTSTATUS WINAPI ThirdPerson(CLocalEntity LocalEntity) 
	{ 
		static bool enabled = false;
		
		if (visuals::enable_thirdperson)
		{
			enabled = true;
			*(int*)(offsets_modules::module_base + offsets::thirdperson_override) = 1;
			*(int*)(LocalEntity.Entity + offsets::m_thirdPersonShoulderView) = 1;
		}
		else
		{
			if (enabled) 
			{
				enabled = false; 
				*(int*)(offsets_modules::module_base + offsets::thirdperson_override) = 0;
				*(int*)(LocalEntity.Entity + offsets::m_thirdPersonShoulderView) = 0;
			}
		}
		return STATUS_SUCCESS;
	}
	
	NTSTATUS WINAPI PlayerBox(CLocalEntity LocalEntity) 
	{ 
		CBaseEntity Entity = CBaseEntity();
		for (int i = 0; i < 200; i++)
		{
			DWORD64 BaseEntity = Entity.GetEntityIndex(offsets_modules::module_base,
				offsets::cl_entitylist, i, 32);
			if (!BaseEntity || BaseEntity == LocalEntity.Entity || !LocalEntity.Entity)
				continue;

		}
		return STATUS_SUCCESS; 
	}
	
	NTSTATUS WINAPI PlayerName(CLocalEntity LocalEntity) 
	{ 
		return STATUS_SUCCESS; 
	}
	
	NTSTATUS WINAPI PlayerOutline(CLocalEntity LocalEntity)
	{
		CBaseEntity Entity = CBaseEntity();
		for (int i = 0; i < 200; i++)
		{
			DWORD64 BaseEntity = *(DWORD64*)(offsets_modules::module_base +
				offsets::cl_entitylist + i * 32);
			
			if (!BaseEntity || BaseEntity == LocalEntity.Entity || !LocalEntity.Entity)
				continue;
			
			*(GlowMode*)(BaseEntity + offsets::glow_type) = Entity.GlowStyle;
			*(ColorRGB*)(BaseEntity + offsets::glow_color) = ColorRGB{ 155,155,155 };
			*(bool*)(BaseEntity + offsets::glow_enable) = true;
		}
		return STATUS_SUCCESS; 
	}
	
	NTSTATUS WINAPI ItemOutline(CLocalEntity LocalEntity)
	{
		if (!LocalEntity.Entity)
			return STATUS_ERROR;

		//*(DWORD64*)(BaseEntity + 0x2C0) = 0x51408A89;
		CBaseEntity Entity = CBaseEntity();
		for (int Index = 0; Index < 12000; Index++)
		{
			DWORD64 BaseEntity = *(DWORD64*)(offsets_modules::module_base +
				offsets::cl_entitylist + Index * 32);
			if (!BaseEntity || BaseEntity == LocalEntity.Entity)
				continue;
			
			DWORD64 EntityTeam = *(DWORD64*)(BaseEntity + Classes::CBaseEntity::m_iTeamNum);
			DWORD64 LocalTeam = *(DWORD64*)(LocalEntity.Entity + Classes::CBaseEntity::m_iTeamNum);

			if (EntityTeam == LocalTeam)
				continue;
			
			if (EntityTeam != LocalTeam)
				continue;
		
			*(GlowMode*)(BaseEntity + offsets::glow_type) = Entity.GlowStyle;
			*(ColorRGB*)(BaseEntity + offsets::glow_color) = ColorRGB(155, 155, 155);
			*(bool*)(BaseEntity + 0x2C0) = true;
		}
		return STATUS_SUCCESS;
	}

	NTSTATUS WINAPI WeaponChams(CLocalEntity LocalEntity)
	{
		if (!LocalEntity.Entity)
			return STATUS_ERROR;

		return STATUS_SUCCESS;
	}

}; VisualFeatures* pVisualFeatures = new VisualFeatures();

class Visuals {
public:
	NTSTATUS WINAPI RenderRadar()
	{
		if (pImGuiWindow->BeginWindow(skCrypt("Radar").decrypt(), 0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize))
		{
			ImGui::SetWindowSize(ImVec2(219, 213));

			ImVec2 siz = ImGui::GetWindowSize();
			ImVec2 pos = ImGui::GetWindowPos();

			ImDrawList* windowDrawList = ImGui::GetWindowDrawList();
			windowDrawList->AddLine(ImVec2(pos.x + (siz.x / 2), pos.y + 0), ImVec2(pos.x + (siz.x / 2), pos.y + siz.y), GetU32(255, 255, 255, 255), 1.5f);
			windowDrawList->AddLine(ImVec2(pos.x + 0, pos.y + (siz.y / 2)), ImVec2(pos.x + siz.x, pos.y + (siz.y / 2)), GetU32(255, 255, 255, 255), 1.5f);

			CLocalEntity LocalEnt = CLocalEntity(offsets_modules::module_base, offsets::local_player);
			CBaseEntity BaseEnt = CBaseEntity();

			if (!LocalEnt.Entity)
				return STATUS_ERROR;

			DWORD64 LocalTeam = *(DWORD64*)(LocalEnt.Entity + Classes::CBaseEntity::m_iTeamNum);
			CBaseEntity Entity = CBaseEntity();

			for (int i = 0; i < 100; i++)
			{
				DWORD64 BaseEntity = Entity.GetEntityIndex(offsets_modules::module_base, offsets::cl_entitylist, i, 32);
				if (!BaseEntity || Entity.Entity == LocalEnt.Entity)
					continue;

				DWORD64 EntityTeam = Entity.m_iTeamNum(Classes::CBaseEntity::m_iTeamNum);
				if (EntityTeam == LocalTeam)
					continue;

				windowDrawList->AddCircleFilled(ImVec2(pos.x + (siz.x / 2), pos.y + 0), 180, GetU32(155, 155, 155, 255), 0);
			}

			pImGuiWindow->EndWindow();
		}

		return STATUS_SUCCESS;
	}
	NTSTATUS WINAPI RenderFPSWindow()
	{
		pImGuiWindow->BeginWindow(skCrypt("FPS").decrypt(), 0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
		ImGui::SetWindowSize(ImVec2(108, 24));
		ImGui::Text(skCrypt("FPS: %f").decrypt(), ImGui::GetIO().Framerate);
		pImGuiWindow->EndWindow();
		return STATUS_SUCCESS;
	}
	NTSTATUS WINAPI InitVisuals(CLocalEntity LocalEntity)
	{
		if (!visuals::enable_visuals)
			return STATUS_ERROR;

		if (visuals::enable_box) { pVisualFeatures->PlayerBox(LocalEntity); }
		if (visuals::enable_thirdperson) { pVisualFeatures->ThirdPerson(LocalEntity); }
		
		if (visuals::enable_outline) { pVisualFeatures->PlayerOutline(LocalEntity); }
		
		if (visuals::item_esp) { pVisualFeatures->ItemOutline(LocalEntity); }
		if (visuals::weapon_chams) { pVisualFeatures->WeaponChams(LocalEntity); }
		
		return STATUS_SUCCESS;
	}

	NTSTATUS WINAPI ModifyFov()
	{
		auto fov_offset = pDumperPatterns->FindPattern("48 8D 05 ? ? ? ? 48 89 05 ? ? ? ? ");
		float result = *(float*)fov_offset;
		result = visuals::view_fov;
	}

public:	
	NTSTATUS WINAPI Initialize(CLocalEntity LocalEntity)
	{
		this->InitVisuals(LocalEntity);
		this->ModifyFov();
		return STATUS_SUCCESS;
	}
}; Visuals* pVisuals;