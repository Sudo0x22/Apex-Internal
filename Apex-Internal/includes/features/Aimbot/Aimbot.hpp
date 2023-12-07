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
			return 7;
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
}; Hitbox* TargetHitbox = new Hitbox();

QAngle CalculateBestBoneAim(Entity* from, uintptr_t t, float max_fov)
{
	Entity* target = get_entiy(t);


	if (!target->isAlive() || target->isKnocked())
	{
		return QAngle(0, 0, 0);
	}

	Vector LocalCamera = from->cam_pos();
	//Vector TargetBonePosition = target.getBonePosition(bone);
	//get TartgetBonePosition by using hitboxpos
	Vector TargetBonePosition = target->bone_position(TargetHitbox->TargetHitbox());
	QAngle CalculatedAngles = QAngle(0, 0, 0);

	WeaponXEntity curweap = WeaponXEntity();
	curweap.update(from);
	float BulletSpeed = curweap.get_projectile_speed();
	float BulletGrav = curweap.get_projectile_gravity();
	float zoom_fov = curweap.get_zoom_fov();

	if (zoom_fov != 0.0f && zoom_fov != 1.0f)
	{
		max_fov *= zoom_fov / 90.0f;
	}

	// more accurate prediction
	if (BulletSpeed > 1.f)
	{
		PredictCtx Ctx;
		Ctx.StartPos = LocalCamera;
		Ctx.TargetPos = TargetBonePosition;
		Ctx.BulletSpeed = BulletSpeed - (BulletSpeed * 0.08);
		Ctx.BulletGravity = BulletGrav + (BulletGrav * 0.05);
		Ctx.TargetVel = target->getAbsVelocity();

		if (BulletPredict(Ctx))
			CalculatedAngles = QAngle{ Ctx.AimAngles.x, Ctx.AimAngles.y, 0.f };
	}

	if (CalculatedAngles == QAngle(0, 0, 0))
		CalculatedAngles = CalcAngle(LocalCamera, TargetBonePosition);

	QAngle ViewAngles = from->Q_view_angles();
	QAngle SwayAngles = from->Q_sway_angles();


	// remove sway and recoil
	//if (aim_no_recoil)
	CalculatedAngles -= SwayAngles - ViewAngles;
	monkey(CalculatedAngles);
	QAngle Delta = CalculatedAngles - ViewAngles;
	double fov = GetFov(SwayAngles, CalculatedAngles);
	if (fov > max_fov)
	{
		return QAngle(0, 0, 0);
	}

	monkey(Delta);

	QAngle SmoothedAngles = ViewAngles + Delta / aimbot::smooth_value;

	return SmoothedAngles;
}

Vector calculate_best_bone(Entity* from, Entity* to)
{
	auto calculated_angles = calc_angle(from->cam_pos(), to->bone_position(TargetHitbox->TargetHitbox()));

	Vector view_angles = from->view_angles();
	Vector punchAngle = from->aim_punch();
	Vector sway_angles = from->sway_angles();

	calculated_angles.Normalize();

	calculated_angles -= sway_angles * (100 / 100.f);
	calculated_angles -= (punchAngle * 0.05f) * (100 / 100.f);
	calculated_angles += view_angles * (100 / 100.f);
	oldPunch = punchAngle; // do this so the rcs doesnt

	Vector delta = calculated_angles - view_angles;

	delta.Normalize();

	Vector smoothed_angles = view_angles + delta / aimbot::smooth_value;

	return smoothed_angles;
}

Vector calculate_best_bone_legit(Entity* from, Entity* to)
{
	auto calculated_angles = calc_angle(from->cam_pos(), to->bone_position(5));

	Vector view_angles = from->view_angles();
	Vector sway_angles = from->sway_angles();

	calculated_angles.Normalize();

	Vector delta = calculated_angles - view_angles;

	delta.Normalize();

	Vector smoothed_angles = view_angles + delta / 10;

	return smoothed_angles;
}

bool check_in_fov(Vector2D screen_body, float FOVmax)
{
	float Dist = Utils::GetCrossDistance(screen_body.x, screen_body.y, (SCREEN_W / 2), (SCREEN_H / 2));

	if (Dist < FOVmax)
	{
		float Radius = aimbot::aim_fov;

		if (screen_body.x <= ((SCREEN_W / 2) + Radius) &&
			screen_body.x >= ((SCREEN_W / 2) - Radius) &&
			screen_body.y <= ((SCREEN_H / 2) + Radius) &&
			screen_body.y >= ((SCREEN_H / 2) - Radius))
		{
			FOVmax = Dist;
			return true;
		}
		return false;
	}
}

class CAimbot
{
private:
	QAngle WINAPI SlientAim(CLocalEntity LocalEntity, UserCmd_t* pCmd) 
	{ 
		return QAngle(0, 0, 0);
	}
	NTSTATUS WINAPI SmoothAim(CLocalEntity LocalEntity, UserCmd_t* pCmd) 
	{
		Entity* local_entity = get_localEntity();
		for (int index = 0; index < 17000; index++) {
			uint64_t worldEnt = *(uint64_t*)(global::g_hGameImage + pInitOffsets.m_dwClientList);
			if (worldEnt == NULL) continue;

			Entity* entity = get_entiy(index);
			
			if (!entity) continue;
			if (entity == local_entity) continue;
			
			if (entity->team_num() == local_entity->team_num()) continue;
			if (entity->health() == 0) continue;

			Vector Pos = entity->bone_position(10);
			Vector2D PosScreen;

			if (!world_to_screen(Pos, PosScreen))
				return FALSE;
			
			if (check_in_fov(PosScreen, aimbot::aim_fov) == true) 
			{
				if (entity->isKnocked()) continue;
				
				if (entity->is_visible(1000)) 
				{
					if (pKeyInput->GetKeyState(VK_RBUTTON))
						local_entity->Q_set_view_angles(CalculateBestBoneAim(entity,index,aimbot::aim_fov));
				}
			}
			else continue;
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
	NTSTATUS WINAPI NoRecoil(CLocalEntity LocalEntity, UserCmd_t* pCmd)
	{
		if (!aimbot::no_recoil)
			return STATUS_ERROR;

		Entity* local_entity = get_localEntity();
		if (local_entity == NULL) return STATUS_ERROR;

		if (local_entity->health() != 0)
		{
			Vector view_angles = local_entity->view_angles();
			Vector punch_angle = local_entity->aim_punch();

			Vector new_angle = view_angles + (old_aimpunch - punch_angle) * (aimbot::recoil_amount / 100.f);
			//new_angle.Normalize();

			local_entity->set_view_angles(new_angle);
			old_aimpunch = punch_angle;
		}

		return STATUS_SUCCESS;
	}
public:
	NTSTATUS WINAPI Initialize(CLocalEntity LocalEntity, UserCmd_t* pCmd)
	{
		this->InitAimbot(LocalEntity, pCmd);
		//this->NoRecoil(LocalEntity, pCmd);
		return STATUS_SUCCESS;
	}
}; CAimbot* pAimbot = new CAimbot();