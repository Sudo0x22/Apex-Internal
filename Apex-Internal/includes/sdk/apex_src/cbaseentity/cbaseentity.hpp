#pragma once
#include"../../../modules/modules.hpp"
#include"../engine/engine.hpp"
#include"../cbasecombatweapons/cbasecombatweapon.hpp"
#include"../../../features/variables/variables.hpp"

enum HelmetTypes
{
	HELMSLOT_NONE = 0,
	HELMSLOT_GREY = 1,
	HELMSLOT_BLUE = 2,
	HELMSLOT_PURPLE = 3,
	HELMSLOT_GOLDEN = 4,
};
enum ArmorTypes
{
	ARMORSLOT_NONE = 0,
	ARMORSLOT_GREY = 1,
	ARMORSLOT_BLUE = 2,
	ARMORSLOT_PURPLE = 3,
	ARMORSLOT_GOLDEN = 4,
	ARMORSLOT_MYTHIC = 5
};

struct Bone {
	BYTE thing[0xCC];
	float x;
	BYTE thing2[0xC];
	float y;
	BYTE thing3[0xC];
	float z;
};

struct MyStr32
{
	char readstr[32];
};
struct MyStr64
{
	char readstr[32];
};

template<typename type>
type Read(uint64_t addr) {
	type Buffer{};
	return *(type*)(addr);
}

inline double GetCrossDist(double x1, double y1, double x2, double y2) {
	return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}

std::string ReadString64(uint64_t addr) {
	std::string result = Read<MyStr64>(addr).readstr;
	return result;
}

class CBaseEntity {
private:
	DWORD64 EntityList = NULL;
	DWORD64 BaseEntity = NULL;
	DWORD64 EntityHandle = NULL;

	int Index = 0;
	std::string ident = "";

	DWORD64 atIndex(int index)
	{
		this->Index = index;
		return *(DWORD64*)(this->EntityList + (index << 5));
	}

#define NUM_ENT_ENTRIES		(1 << 12)
#define ENT_ENTRY_MASK		(NUM_ENT_ENTRIES - 1)

public:
	DWORD64 Entity;
	LPCSTR IdentifierC = ident.c_str();
	//GlowMode GlowStyle = { 101, 101, 46, 90 };
	Vec3 pos{ 0,0,0 };
	std::string name;

	DWORD64 GetEntityIndex(DWORD64 ModuleBase, DWORD64 Offset, DWORD64 Index, INT HexCode)
	{
		this->Entity = *(DWORD64*)(ModuleBase + Offset + (Index * HexCode));
		return this->Entity;
	}
public:
	__declspec() bool IsNPC() {
		return (bool)(strcmp(this->IdentifierC, "npc_dummie"));
	}
	__declspec() bool isPlayer() {
		return (bool)(strcmp(this->IdentifierC, "player"));
	}
	__declspec() bool isDrone() {
		return !this->isPlayer() && !this->IsNPC() ? true : false;
	}
	__declspec() bool isAlive(DWORD64 offset) {
		return *(int*)(this->Entity + offset) != 0;
	}
public:
	inline std::string identifier() {
		return *(std::string*)(this->Entity + 0x589);
	}
public:
	__declspec() int m_iHealth(DWORD64 offset) {
		return *(int*)(this->Entity + offset);
	}
	__declspec() int m_iShieldHealth(DWORD64 offset) {
		return *(int*)(this->Entity + offset);
	}
	__declspec() DWORD64 m_iTeamNum(DWORD64 offset) {
		return *(DWORD64*)(this->Entity + offset);
	}
	__declspec() int m_iBleedoutState(DWORD64 offset) {
		return *(int*)(this->Entity + offset);
	}
public:
	__inline int m_iArmorType(DWORD64 offset) {
		return *(int*)(this->Entity + offset);
	}
	__inline int m_iHelmetType(DWORD64 offset) {
		return *(int*)(this->Entity + offset);
	}
public:
	__inline bool IsVisible(float current_time, DWORD64 offset) {
		float last_visible_time = *(float*)(Entity + offset);
		return last_visible_time > 0.0f && win_api::nt_abs(last_visible_time - current_time) < 0.1f;
	}
public:
	Vector3 Postition(DWORD64 offset) {
		return *(Vector3*)(this->Entity + offset);
	}
	Vector2 Postition2D(DWORD64 Offset) {
		return *(Vector2*)(this->Entity + Offset);
	}
	bool GetPosition(DWORD64 offset)
	{
		this->pos = *(Vec3*)(this->Entity + offset);
		return true;
	}
	Vector3 BonePostition(int boneIndex, DWORD64 offset, DWORD64 second_offset)
	{
		Bone bone = { };
		Vector3 vec_bone = Vector3();
		Vector3 pos = this->Postition(offset);
		
		ULONG64 bone_array = *(ULONG64*)(this->Entity + second_offset);
		ULONG64 bone_location = (boneIndex * 0x30);
		bone = *(Bone*)(bone_array + bone_location);
		
		vec_bone.x = bone.x + pos.x;
		vec_bone.y = bone.y + pos.y;
		vec_bone.z = bone.z + pos.z;
		
		return vec_bone;
	}
public:
	bool GetName(DWORD64 offset)
	{
		byte TempData[32]{};
		char* TempName = nullptr;
		DWORD64 NameAddr = *(DWORD64*)(this->Entity + offset);
		if (NameAddr == 0)
			return false;
		TempName = reinterpret_cast<char*>(TempData);
		this->name = TempName;
		return true;
	}
public:
};

class CLocalEntity {
public:
	DWORD64 Entity = 0;
	explicit CLocalEntity(DWORD64 dwbase, DWORD64 offset) {
		Entity = *(DWORD64*)(dwbase + offset);
	}
public:
	__declspec() Vector3 Position(DWORD64 offset) {
		return *(Vector3*)(this->Entity + offset);
	}
	__declspec() Vector3 GetViewAngles(DWORD64 offset) {
		return *(Vector3*)(this->Entity + offset);
	}
	__declspec() void SetViewAngles(DWORD64 offset, Vector3 Angles) {
		*(Vector3*)(Entity + offset) = Angles;
	}
	 Vector3 GetAimPunch(DWORD64 offset) {
		return *(Vector3*)(this->Entity + offset);
	}
	__declspec() Vector3 GetBreathAngles(DWORD64 offset) {
		return *(Vector3*)(this->Entity + offset);
	}
	__declspec() Vector3 GetRecoil(DWORD64 offset) {
		return *(Vector3*)(this->Entity + offset);
	}
	__declspec() Vector3 GetCamPostition(DWORD64 offset) {
		return *(Vector3*)(this->Entity + offset);
	}
	__declspec() Vector3 BonePosition(int boneIndex, DWORD64 view_offset, DWORD64 offset) {
		Bone bone = {};
		Vector3 vec_bone = Vector3();
		Vector3 pos = Position(view_offset);

		ULONG64 bone_array = *(ULONG64*)(this->Entity + offset);
		ULONG64 bone_location = (boneIndex * 0x30);

		bone = *(Bone*)(bone_array + bone_location);
		vec_bone.x = bone.x + pos.x;
		vec_bone.y = bone.y + pos.y;
		vec_bone.z = bone.z + pos.z;
		return vec_bone;
	}
public:
	__declspec() int m_iHealth(DWORD64 offset) {
		return *(int*)(this->Entity + offset);
	}
	__declspec() int m_shieldHealth(DWORD64 offset) {
		return *(int*)(this->Entity + offset);
	}
	__declspec() int m_iTeamNum(DWORD64 offset) {
		return *(int*)(this->Entity + offset);
	}
	__declspec() int m_armorType(DWORD64 offset) {
		if (!this->Entity) return -1;
		return *(int*)(this->Entity + offset);
	}
	_declspec() int m_helmetType(DWORD64 offset) {
		if (!this->Entity) return -1;
		return *(int*)(this->Entity + offset);
	}
	__declspec() bool IsAlive(DWORD64 offset) {
		return (bool)(this->Entity + offset) != 0;
	}
public:
	__declspec() unsigned long ModelNamePtr() {
		if (!this->Entity) return -1;
		return *(unsigned long long*)(this->Entity + 0x30);
	}
	__declspec() char ModelName() {
		char module_name;
		module_name = *(char*)(this->ModelNamePtr());
		return module_name;
	}
	__declspec() int m_nModelIndex(DWORD64 offset) {
		return *(int*)(this->Entity + offset);
	}
public:
	CBaseCombatWeapon ActiveWeapon(DWORD64 module_base, DWORD64 offset, DWORD64 pointer_offset)
	{
		DWORD64 pWeapon = *(DWORD64*)(this->Entity + offset);
		pWeapon &= 0xffff;
		DWORD64 pWeaponHandle = *(DWORD64*)(module_base + pointer_offset + (pWeapon << 5));
		return CBaseCombatWeapon(pWeaponHandle);
	}
};

Vector oldPunch;
Vector old_aimpunch;

class Entity
{
public:
	Vector bone_position(int index)
	{
		Vector position = *(Vector*)(this + pInitOffsets.m_vLocalOrigin);
		uintptr_t boneArray = *(uintptr_t*)(this + pInitOffsets.m_vBones);
		Vector bone = Vector();
		uint32_t boneloc = (index * 0x30);
		bone_t bo = { };
		bo = *(bone_t*)(boneArray + boneloc);
		bone.x = bo.x + position.x;
		bone.y = bo.y + position.y;
		bone.z = bo.z + position.z;
		return bone;
	}

	Vector base_position()
	{
		return *(Vector*)(this + pInitOffsets.m_vLocalOrigin);
	}

	Vector sway_angles()
	{
		return *(Vector*)(this + pInitOffsets.m_vBreathAngles);
	}

	QAngle Q_sway_angles()
	{
		return *(QAngle*)(this + pInitOffsets.m_vBreathAngles);
	}

	QAngle Q_view_angles()
	{
		return *(QAngle*)(this + pInitOffsets.m_vViewAngles);
	}

	Vector cam_pos()
	{
		return *(Vector*)(this + pInitOffsets.m_vCameraPos);
	}

	/*Vector getstudiohdr(int id)
	{
		uint64_t bones = *(uint64_t*)(global::g_hGameImage + this + OFFSET_BONES);
		if (!bones) return Vector();
		int Bone = BoneByHitBox(id, this);
		if (Bone == -1) return Vector();
		Matrix3x4 BoneMatrix = *(Matrix3x4*)(bones + (Bone * sizeof(Matrix3x4)));
		Vector BoneOff = { BoneMatrix._14, BoneMatrix._24, BoneMatrix._34 };
		Vector Pos = base_position() + BoneOff;
		return Pos;
	}*/

	std::string name()
	{
		//return *(char*)(engine::get_player_name(this));
		uintptr_t nameIndex = *(uintptr_t*)(this + 0x38);
		uintptr_t nameOffset = *(uintptr_t*)(global::g_hGameImage + pInitOffsets.m_iNameList + ((nameIndex - 1) << 4));
		std::string playerName = ReadString64(nameOffset);
		return playerName;
	}

	Vector view_angles()
	{
		return *(Vector*)(this + pInitOffsets.m_vViewAngles);
	}

	Vector aim_punch()
	{
		return *(Vector*)(this + pInitOffsets.m_vAimPunch);
	}

	void set_view_angles(Vector angles)
	{
		*(Vector*)(this + pInitOffsets.m_vViewAngles) = angles;
	}
	void Q_set_view_angles(QAngle angles)
	{
		*(QAngle*)(this + pInitOffsets.m_vViewAngles) = angles;
	}

	int health()
	{
		return *(int*)(this + pInitOffsets.m_iHealth);
	}

	int shield()
	{
		return *(int*)(this + pInitOffsets.m_iShield);
	}

	int armor_type()
	{
		return *(int*)(this + pInitOffsets.m_iArmorType);
	}

	inline float last_vis_time()
	{
		return *(float*)(this + pInitOffsets.m_iVisibleTime);
	}

	bool is_player()
	{
		return *(uint64_t*)(this + pInitOffsets.m_sName) == 125780153691248;
	}

	uint64_t get_wepon()
	{
		return *(uint64_t*)(this + pInitOffsets.m_wWeapon);
	}

	int ammo()
	{
		return *(int*)(this + pInitOffsets.m_wAmmo);
	}

	int down()
	{
		return *(int*)(this + pInitOffsets.m_iBleedOutState);
	}

	int max_shield()
	{
		return *(int*)(this + pInitOffsets.m_iMaxShield);
	}

	int team_num()
	{
		return *(int*)(this + pInitOffsets.m_iTeamNum);
	}

	bool isAlive()
	{
		return *(int*)(this + pInitOffsets.m_iLifeState) == 0;
	}

	bool isKnocked()
	{
		return *(int*)(this + pInitOffsets.m_iBleedOutState) > 0;
	}

	Vector getAbsVelocity()
	{
		return *(Vector*)(this + pInitOffsets.m_vAbsVelocity);
	}


	bool is_visible(int i) {
		const auto VisCheck = last_vis_time();

		const auto IsVis = VisCheck > oVisTime[i] || VisCheck < 0.f && oVisTime[i] > 0.f;

		oVisTime[i] = VisCheck;

		return IsVis;
	}

public:
	void start_glowing(int i)
	{
		//  109, 103, 100, 255 - solid
	//  0, 118, 100, 100 - out line
		glowMode glowStyle = { 101,101,46,90 }; //Default Glow is Outline

		float time = 5000.f;

		/*Vector glow_col = { 1.f,.5f,.5f };
		*(glowMode*)(this + GLOW_TYPE) = glowStyle;
		*(float*)(this + GLOW_DISTANCE) = visuals::max_esp_dist;
		*(float*)(this + GLOW_LIFE_TIME) = time;
		*(float*)(this + 0x1D0 + 0x30) = visuals::ouline_color_visible[0];
		*(float*)(this + 0x1D4 + 0x30) = visuals::ouline_color_visible[1];
		*(float*)(this + 0x1D8 + 0x30) = visuals::ouline_color_visible[2];
		time -= 1.f;
		*(int*)(this + GLOW_CONTEXT) = 1;
		*(int*)(this + GLOW_VISIBLE_TYPE) = 1;
		*(glowFade*)(this + GLOW_FADE) = { 872415232, 872415232, time, time, time, time };*/
	}
	void stop_glowing()
	{
		//*(int*)(this + OFFSET_GLOW_T1) = 0;
		//*(int*)(this + OFFSET_GLOW_T2) = 0;
		*(int*)(this + pInitOffsets.m_bGlowEnable) = 2;
		*(int*)(this + pInitOffsets.m_bGlowEnableThroughWalls) = 5;
		*(float*)(this + pInitOffsets.m_bGlowDistance) = 0;
	}

	void enable_glow(int i)
	{
		
		*(glowMode*)(this + pInitOffsets.m_bGlowType) = { 101,101,46,90 };
		*(int*)(this + pInitOffsets.m_bGlowEnable) = 1;
		*(int*)(this + pInitOffsets.m_bGlowEnableThroughWalls) = 2;
		*(float*)(this + pInitOffsets.m_bGlowDistance) = visuals::max_esp_dist;

		if (this->is_visible(i)) 
		{
			*(float*)(this + pInitOffsets.m_bGlowColorR) = visuals::ouline_color_visible[0] * 2.5f;
			*(float*)(this + pInitOffsets.m_bGlowColorG) = visuals::ouline_color_visible[1] * 2.5f;
			*(float*)(this + pInitOffsets.m_bGlowColorB) = visuals::ouline_color_visible[2] * 2.5f;

		} else
		{
			*(float*)(this + pInitOffsets.m_bGlowColorR) = visuals::ouline_color_nonvisible[0] * 2.5f;
			*(float*)(this + pInitOffsets.m_bGlowColorG) = visuals::ouline_color_nonvisible[1] * 2.5f;
			*(float*)(this + pInitOffsets.m_bGlowColorB) = visuals::ouline_color_nonvisible[2] * 2.5f;
		}
		
	}
};

Entity* get_entiy(uintptr_t idx) {
	return *(Entity**)(global::g_hGameImage + pInitOffsets.m_dwClientList + (idx << 5));
}

Entity* get_localEntity() {
	return *(Entity**)(global::g_hGameImage + pInitOffsets.m_dwLocalEntity);
}

int GetTeamId(uint64_t entity)
{
	return *(int*)(entity + pInitOffsets.m_iTeamNum);
}

void SetTeamId(uint64_t entity, int teamID)
{
	*(int*)(entity + pInitOffsets.m_iTeamNum) = teamID;
}

typedef char* (__fastcall* getplayername_fn)(Entity* ent);
getplayername_fn o_getplayername = 0;

typedef bool(__fastcall* islobby_fn)();
islobby_fn o_islobby = 0;

typedef bool(__fastcall* isprop_fn)(Entity* ent);
isprop_fn o_isprop = 0;

typedef bool(__fastcall* isweapon_fn)(Entity* ent);
isweapon_fn o_isweapon = 0;

namespace engine
{
	char* get_player_name(Entity* ent)
	{
		if (o_getplayername == 0)
			o_getplayername = (getplayername_fn)util::ida_signature(global::g_hGameImage, __("40 53 48 83 EC 20 48 8B D9 E8 ? ? ? ? 48 63 43 38"));

		return o_getplayername(ent);
	}

	bool is_lobby()
	{
		if (o_islobby == 0)
			o_islobby = (islobby_fn)util::ida_signature(global::g_hGameImage, __("48 83 EC 28 48 8B 0D ? ? ? ? 48 8D 15 ? ? ? ? 48 8B 01 48 3B C2 75 14 83 3D ? ? ? ? ?"));

		return o_islobby();
	}

	bool is_prop(Entity* ent)
	{
		if (o_isprop == 0)
			o_isprop = (isprop_fn)util::ida_signature(global::g_hGameImage, __("48 8B 01 FF A0 30 06 00 00"));

		return o_isprop(ent);
	}

	bool is_weapon(Entity* ent)
	{
		return false; // discontinued
	}
}

class WeaponXEntity
{
public:
	void update(Entity* LocalPlayer);
	float get_projectile_speed();
	float get_projectile_gravity();
	float get_zoom_fov();

private:
	float projectile_scale;
	float projectile_speed;
	float zoom_fov;
};

void WeaponXEntity::update(Entity* LocalPlayer)
{
	extern uint64_t g_Base;
	uint64_t entitylist = *(uint64_t*)(global::g_hGameImage + pInitOffsets.m_dwClientList);
	uint64_t wephandle = *(uint64_t*)(LocalPlayer + pInitOffsets.m_wWeapon);
	wephandle &= 0xffff;

	uint64_t wep_entity = 0;
	*(uint64_t*)(entitylist + (wephandle << 5), wep_entity);

	projectile_speed = (wep_entity + pInitOffsets.m_wBulletSpeed, projectile_speed);

	projectile_scale = (wep_entity + pInitOffsets.m_wBulletScale, projectile_scale);

	zoom_fov = (wep_entity + pInitOffsets.m_iZoomFov, zoom_fov);
}

float WeaponXEntity::get_projectile_speed()
{
	return projectile_speed;
}

float WeaponXEntity::get_projectile_gravity()
{
	return 750.0f * projectile_scale;
}

float WeaponXEntity::get_zoom_fov()
{
	return zoom_fov;
}

Vector prediction(Vector LPlayerpos, Vector Targetpos, Entity* from, Entity* target)
{
	WeaponXEntity curweap = WeaponXEntity();
	curweap.update(from);
	float BulletSpeed = curweap.get_projectile_speed();
	//printf("%f\n", BulletSpeed);
	float BulletGrav = curweap.get_projectile_gravity();
	//printf("%f\n", BulletGrav);
	float distance = LPlayerpos.DistTo(Targetpos);
	float time = distance / BulletSpeed;
	Vector BulletGravChange = { 0, BulletGrav * time, 0 };
	Vector TargetVel = target->getAbsVelocity();
	Vector MovementChange = TargetVel * time;
	Vector FinalPos = Targetpos + MovementChange + BulletGravChange;
	return FinalPos;
}

Vector ExtrapolatePos(const PredictCtx& Ctx, float Time)
{
	return Ctx.TargetPos + (Ctx.TargetVel * Time);
}

bool OptimalPitch(const PredictCtx& Ctx, const Vector2D& Dir2D, float* OutPitch)
{
	float Vel = Ctx.BulletSpeed, Grav = Ctx.BulletGravity, DirX = Dir2D.x, DirY = Dir2D.y;
	float Root = Vel * Vel * Vel * Vel - Grav * (Grav * DirX * DirX + 2.f * DirY * Vel * Vel);
	if (Root >= 0.f) { *OutPitch = atanf((Vel * Vel - sqrt(Root)) / (Grav * DirX)); return true; }
	return false;
}

bool SolveTrajectory(PredictCtx& Ctx, const Vector& ExtrPos, float* TravelTime)
{
	Vector Dir = ExtrPos - Ctx.StartPos;
	Vector2D Dir2D = { sqrtf(Dir.x * Dir.x + Dir.y * Dir.y), Dir.z };

	float CurPitch;
	if (!OptimalPitch(Ctx, Dir2D, &CurPitch))
	{
		return false;
	}

	*TravelTime = Dir2D.x / (cosf(CurPitch) * Ctx.BulletSpeed);
	Ctx.AimAngles.y = atan2f(Dir.y, Dir.x);
	Ctx.AimAngles.x = CurPitch;
	return true;
}

bool BulletPredict(PredictCtx& Ctx)
{
	float MAX_TIME = 1.f, TIME_STEP = (1.f / 256.f);
	for (float CurrentTime = 0.f; CurrentTime <= MAX_TIME; CurrentTime += TIME_STEP)
	{
		float TravelTime;
		Vector ExtrPos = ExtrapolatePos(Ctx, CurrentTime);
		if (!SolveTrajectory(Ctx, ExtrPos, &TravelTime))
		{
			return false;
		}

		if (TravelTime < CurrentTime)
		{
			Ctx.AimAngles = { -RAD2DEG(Ctx.AimAngles.x), RAD2DEG(Ctx.AimAngles.y) };
			return true;
		}
	}
	return false;
}

int BoneByHitBox(int HitBox, Entity* local_ent)
{
	//get model ptr
	uint64_t Model = *(uint64_t*)(local_ent + pInitOffsets.m_iStudioHDR);
	if (!Model) return -1;

	//get studio hdr
	uint64_t StudioHdr = *(uint64_t*)(Model + 0x8);
	if (!StudioHdr) return -1;

	//get hitbox array
	int HitBoxsArray = *(int*)(StudioHdr + 0xB4);
	uint64_t HitBoxsArray2 = HitBoxsArray + StudioHdr;
	if (!HitBoxsArray) return -1;

	//get bone index
	int Bone = *(int*)(HitBoxsArray2 + *(int*)(HitBoxsArray2 + 8) + (HitBox * 0x2C));

	return ((Bone < 0) || (Bone > 255)) ? -1 : Bone;
}

Vector HitBoxPos(int HitBox, Entity* local_ent, Vector EntityPosition)
{
	//get bones base data
	uint64_t Bones = *(uint64_t*)(local_ent + pInitOffsets.m_vBones);
	if (!Bones) return Vector();


	int Bone = BoneByHitBox(HitBox, local_ent);

	if (Bone == -1) return Vector();

	Matrix3x4 BoneMatrix = *(Matrix3x4*)(Bones + (Bone * sizeof(Matrix3x4)));
	Vector BoneOff = { BoneMatrix._14, BoneMatrix._24, BoneMatrix._34 };

	Vector Pos = EntityPosition + BoneOff;
	return Pos;
}

void PredictPos(Entity* target, Vector* bonePos, Entity* local)
{
	uint64_t WeaponHandle = *(uint64_t*)(local + pInitOffsets.m_wWeapon);
	WeaponHandle &= 0xffff;
	uint64_t activeWeap = *(uint64_t*)((global::g_hGameImage + pInitOffsets.m_dwClientList) + (WeaponHandle << 5));

	if (activeWeap != 0)
	{
		float bulletSpeed = *(float*)(activeWeap + pInitOffsets.m_wBulletSpeed);
		float bulletGravity = *(float*)(activeWeap + pInitOffsets.m_wBulletScale);

		if (bulletSpeed > 1.f)
		{
			Vector muzzle = local->cam_pos();
			float time = bonePos->DistTo(muzzle) / bulletSpeed;
			bonePos->z += (700.f * bulletGravity * 0.5f) * (time * time);
			Vector velDelta = (*(Vector*)(target + pInitOffsets.m_vLocalOrigin - 0xC) * time);
			bonePos->x += velDelta.x;
			bonePos->y += velDelta.y;
			bonePos->z += velDelta.z;
		}
	}
}

