#pragma once
#include"../../../modules/modules.hpp"
#include"../engine/engine.hpp"
#include"../cbasecombatweapons/cbasecombatweapon.hpp"

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


inline double GetCrossDist(double x1, double y1, double x2, double y2) {
	return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
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
	GlowMode GlowStyle = { 101, 101, 46, 90 };
	Vec3 pos{ 0,0,0 };
	std::string name;

	DWORD64 GetEntityIndex(DWORD64 ModuleBase, DWORD64 Offset, DWORD64 Index, INT HexCode)
	{
		this->Entity = *(DWORD64*)(ModuleBase + Offset + Index * HexCode);
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
	__declspec() void EnableGlow(DWORD64 offset, DWORD64 offset_two, DWORD64 offset_three,
		float r, float g, float b, float a)
	{
		ColorRGB Clr = { r * a / 255, g * a / 255, b * a / 255 };
		*(GlowMode*)(this->Entity + offset) = this->GlowStyle;
		*(ColorRGB*)(this->Entity + offset_two) = Clr;
		*(DWORD64*)(this->Entity + offset_three) = 1;
	}
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
	__declspec() DWORD64 m_iTeamNum(DWORD64 offset) {
		return *(DWORD64*)(this->Entity + offset);
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
