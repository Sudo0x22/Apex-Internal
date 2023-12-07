#pragma once
#include"../Triggerbot/triggerbot.h"
#include"../../sdk/utils/utils.hpp"
#include"../users/users.hpp"

#define OutlineContext 0x100
#define OutlineServerActiveState 0x100

struct HighlightFunctionBits
{
	uint8_t functionBits[4];
};

struct HighlightParameter
{
	float parameter[3];
};

class SpectatorList
{
	struct Spectator_t
	{
		std::wstring name;
		std::wstring mode;
		bool IsFriend;
		int team;
		int index;
	};

	std::vector<Spectator_t> Spectators;
	int SpecListW = 300, SpecListTitleBar = 12;
public:
	int SpecListX = 30, SpecListY = 100;
	bool GetSpectators()
	{

	}
	bool Draw()
	{
		if (pImGuiWindow->BeginWindow(__("Spec List"), nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse))
		{
			ImGui::SetWindowSize(ImVec2(250, 250));

			auto size = ImGui::GetWindowSize();
			auto pos = ImGui::GetWindowPos();

			Entity* local_entity = get_localEntity();
			if (local_entity == NULL) return false;

			for (int index = 1; index < 64; index++)
			{
				Entity* entity = get_entiy(index);

				if (entity == NULL) continue;
				if (entity->isAlive() != 0) continue;
				if (entity->isKnocked() == true) continue;

				pDraw->draw_text(size.x, size.y, &allcol.white_, entity->name().c_str());
			}

			pImGuiWindow->EndWindow();
		}
	}
}; SpectatorList* pSpectatorList = new SpectatorList();

class VisualFeatures
{
public:
	NTSTATUS WINAPI ThirdPerson(CLocalEntity LocalEntity) 
	{ 
		static bool enabled = false;
		
		if (visuals::enable_thirdperson)
		{
			//*(int*)(global::g_hGameImage + 0x01daff70 + 0x6c) = 1;
			*(int*)(global::g_hGameImage + pInitOffsets.m_bThirdPerson) = 1;
			//*(int*)(LocalEntity.Entity + OFFSET_THIRDPERSON_SV) = 1;
			enabled = true;
		}
		else
		{
			if (enabled)
			{
				*(int*)(global::g_hGameImage + pInitOffsets.m_bThirdPerson) = -1;
				//*(int*)(LocalEntity.Entity + OFFSET_THIRDPERSON_SV) = -1;
			}
		}
		return STATUS_SUCCESS;
	}
	
	NTSTATUS WINAPI PlayerName(CLocalEntity LocalEntity) 
	{ 
		return STATUS_SUCCESS; 
	}
	
	NTSTATUS WINAPI ToggleOutline(Entity* entity, INT contextId, uint8_t settingIndex, HighlightFunctionBits setting, HighlightParameter color)
	{
		if (!visuals::enable_outline)
			setting = { 0,0,64,64 };

		*(int*)(entity + 0x270) = 1;

		*(int*)(entity + pInitOffsets.m_bGlowEnableThroughWalls) = 2;
		*(int*)(entity + pInitOffsets.m_bGlowEnable) = contextId;
		*(uint8_t*)(entity + contextId + pInitOffsets.m_bGlowActive) = settingIndex;
		uint64_t HighlightSettings = *(uint64_t*)(global::g_hGameImage + pInitOffsets.m_vecPunchWeapon_Angle);

		*(HighlightFunctionBits*)(HighlightSettings + 40 * uint64_t(settingIndex) + 4) = setting;
		*(HighlightParameter*)(HighlightSettings + 40 * uint64_t(settingIndex) + 8) = color;

		return TRUE;
	}
	
	NTSTATUS WINAPI ItemOutline(CLocalEntity LocalEntity)
	{
		if (!LocalEntity.Entity)
			return STATUS_ERROR;

		for (int i = 0; i < 12000; i++)
		{
			Entity* entity = get_entiy(i);
			if (entity == NULL)
				continue;

			*(uint32_t*)(entity + pInitOffsets.m_bGlowEnableThroughWalls) = 2;
			uint32_t contextId = *(uint32_t*)(entity + OutlineContext);
			uint8_t outlineState = *(uint8_t*)(entity + contextId + OutlineServerActiveState);
			uint64_t outineSettings = *(uint64_t*)(global::g_hGameImage + pInitOffsets.m_vecPunchWeapon_Angle);
			HighlightFunctionBits setting{ 127,138,64,64 };
			*(HighlightFunctionBits*)(outineSettings + 40 * outlineState + 4) = setting;
		}


		return STATUS_SUCCESS;
	}

	NTSTATUS WINAPI WeaponChams(CLocalEntity LocalEntity)
	{
		
		return STATUS_SUCCESS;
	}

	NTSTATUS WINAPI SkinChanger(CLocalEntity LocalEntity, bool isPlayer, int index)
	{
		if (!LocalEntity.Entity)
			return FALSE;

		uint64_t WeaponHandle = *(uint64_t*)(LocalEntity.Entity + pInitOffsets.m_wWeapon);
		WeaponHandle &= 0xffff;
		uint64_t WeaponEntity = *(uint64_t*)(global::g_hGameImage + pInitOffsets.m_dwClientList + (WeaponHandle << 5));

		float curTime = *(float*)(LocalEntity.Entity + pInitOffsets.m_iTimeBase);
		float endTime = curTime + 0.5;
		std::map<int, std::vector<int>> weaponSkinMap;

		weaponSkinMap[103] = { 11,9 };   //R99  
		weaponSkinMap[0] = { 7 };     //R301   
		weaponSkinMap[79] = { 9 };    //转换者  
		weaponSkinMap[89] = { 16 };   //赫姆洛克  
		weaponSkinMap[87] = { 17 };    //平行  
		weaponSkinMap[110] = { 11 };      //3030  
		weaponSkinMap[111] = { 10,11 };   //car   
		weaponSkinMap[20] = { 10 };       //暴走   
		weaponSkinMap[89] = { 12 }; //哈沃克
		weaponSkinMap[83] = { 10 };     //专注  
		weaponSkinMap[109] = { 13 };     //电冲  
		weaponSkinMap[112] = { 8 };     //复仇女神  

		weaponSkinMap[86] = { 11 };     //ev8  
		weaponSkinMap[102] = { 15 };     //heping  
		weaponSkinMap[94] = { 11 };     //aoquan  

		if (isPlayer == false)
		{
			int WeaponIndex = *(int*)(WeaponEntity + pInitOffsets.m_wWeaponName);
			if (weaponSkinMap.count(WeaponIndex) == 0)
				return FALSE;
			index = weaponSkinMap[WeaponIndex][0];
		}
		while (curTime < endTime)
		{
			if (isPlayer == true)
				*(int*)(LocalEntity.Entity + pInitOffsets.m_wSkin) = index;
			else
				*(int*)(WeaponEntity + pInitOffsets.m_wSkin) = index;
			curTime = *(float*)(LocalEntity.Entity + pInitOffsets.m_iTimeBase);
		}
		return TRUE;
	}

}; VisualFeatures* pVisualFeatures = new VisualFeatures();

class Visuals {
public:

	NTSTATUS WINAPI RenderRadar(CLocalEntity LocalEntity)
	{
	

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

		pVisualFeatures->ThirdPerson(LocalEntity);
		
		if (visuals::item_esp) { pVisualFeatures->ItemOutline(LocalEntity); }
		
		if (visuals::render_radar_option) { this->RenderRadar(LocalEntity); }

		int WeaponSkinIndex = 1;
		int playerSkinIndex = 1;

		if (visuals::init_skin_changer) 
		{
			WeaponSkinIndex = max(0, WeaponSkinIndex - 1);
			playerSkinIndex = max(0, playerSkinIndex - 1);

			pVisualFeatures->SkinChanger(LocalEntity, false, WeaponSkinIndex); 
			pVisualFeatures->SkinChanger(LocalEntity, true, playerSkinIndex);
		}
		
		return STATUS_SUCCESS;
	}

	void WINAPI MainFuncs()
	{
		Entity* local_entity = get_localEntity();
		if (!local_entity) return;

		for (int i = 0; i < 64; i++)
		{
			Entity* entity = get_entiy(i);
			if (!entity) continue;
			if (entity == local_entity) continue;
			
			//if (entity->team_num() != 97) continue;
			if (entity->team_num() == local_entity->team_num()) continue;
			
			if (entity->health() == 0) continue;
			if (entity->isKnocked()) continue;

			{
				Vector localOrigen = local_entity->base_position();
				int shild = entity->shield();
				int health = entity->health();
				int totallENThealth = health + shild;
				int totalEntityShield = entity->max_shield();

				Vector entityHead = entity->bone_position(8);
				Vector entityOrigen = entity->base_position();

				Vector2D S_localOrigen;

				Vector2D S_entityHead;
				Vector2D S_entityOrigen;

				world_to_screen(localOrigen, S_localOrigen);
				world_to_screen(entityHead, S_entityHead);			
				world_to_screen(entityOrigen, S_entityOrigen);

				if (S_localOrigen.x == 0 || S_localOrigen.y == 0) continue;
				if (S_entityHead.x == 0 || S_entityHead.y == 0) continue;
				if (S_entityOrigen.x == 0 || S_entityOrigen.y == 0) continue;

				float hight = S_entityHead.DistTo(S_entityOrigen);
				float width = hight / 2.f;
				int distance = ToMeters(localOrigen.DistTo(entityOrigen));

				if (distance >= visuals::max_esp_dist) continue;

				//bool is_visiable = entity->is_visible(5);
				float newEntVisTime = *(float*)(entity + pInitOffsets.m_iVisibleTime);
				bool isVisable = newEntVisTime > -1 || (newEntVisTime != -1 && newEntVisTime > 0.f);

				Vector2D topLeft = Vector2D(S_entityHead.x - width / 2, S_entityHead.y - hight);
				Vector2D bottomRight = Vector2D(S_entityHead.x + width / 2, S_entityHead.y);
				float boxMiddle = S_entityOrigen.x - (width / 2.0f);

				if (visuals::enable_users == true)
				{
					pSyncUsers->initialize(S_entityHead.x - 15, S_entityHead.y - 15);
				}

				if (visuals::enable_outline == true)
				{
					pVisualFeatures->ToggleOutline(entity, 5, 80, { 0,125,64,64 }, { 0,255,255 });
					/*else {
						pVisualFeatures->ToggleOutline(entity, 6, 81, HighlightFunctionBits{ 101,125,64,64 }, { 60,0,0 });
					}*/
				}

				if (visuals::enable_box == true)
				{
					if (visuals::stand_box == true) {
						pDraw->DrawRect(S_entityHead.x - (width / 2), S_entityHead.y, width, hight, &allcol.NameEsp, 3);
					}
					if (visuals::corner_box == true) {
						pDraw->DrawCornerBox(S_entityHead.x - (width / 2), S_entityHead.y, width, hight, 3, &allcol.NameEsp);
					}
				}

				if (visuals::seers_info == true)
				{
					if (visuals::health_bar == true) {
						pDraw->health_bar((S_entityHead.x - (width / 2)) - 3, S_entityHead.y, 2, hight, health);
						pDraw->shield_bar((S_entityHead.x - (width / 2)) - 6, S_entityHead.y, 2, hight, entity->max_shield());
					}

					if (visuals::seers_health == true) {
						pDraw->SeerHealth(S_entityHead.x, S_entityHead.y - 15, shild, entity->max_shield(), entity->armor_type(), health);
					}
				}

				if (visuals::name_esp == true) {
					pDraw->draw_text(S_entityHead.x - 10, S_entityHead.y - 15, &allcol.white_, entity->name().c_str());
				}

				if (visuals::render_warning_sign == true) {
					if (!isVisable)
						continue;
					pDraw->DrawOutlinedText(pInitStyle->gameFont, ImVec2(1920 / 2, 15), 50.0f, ImColor(255, 0, 0), true, __("WARNING!"));
				}

				if (visuals::dist_to == true) {
					char dist[64];
					sprintf_s(dist, "%.fm", distance);
					ImVec2 TextSize = ImGui::CalcTextSize(dist);
					ImGui::GetOverlayDrawList()->AddText(ImVec2(S_entityHead.x - TextSize.x / 2, S_entityHead.y - TextSize.y / 2), ImGui::GetColorU32({ 255,255,255,255 }), dist);
				}
			}
		}
	}

	NTSTATUS WINAPI ModifyFov(CLocalEntity LocalEntity)
	{
		Entity* local_entity = get_localEntity();
		
		if (local_entity == NULL) return FALSE;
		if (local_entity->health() == 0) return FALSE;



		return TRUE;
	}

public:	
	NTSTATUS WINAPI Initialize(CLocalEntity LocalEntity)
	{
		this->InitVisuals(LocalEntity);
		//this->ModifyFov(LocalEntity);
		
		return STATUS_SUCCESS;
	}
}; Visuals* pVisuals;