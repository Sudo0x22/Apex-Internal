#pragma once
#include "../../sdk/apex_src/engine/engine.hpp"
#include "../../sdk/apex_src/cbaseentity/cbaseentity.hpp"
class CAntiAim
{
private:
	Vector ViewAngles = {0,0,0};
	Vector HeadPos = {};
public:
	__inline void Initialize()
	{
		if (!anti_aim::enable_anti_aimbot)
			return;

		Entity* local_player = get_localEntity();
		if (local_player == NULL)	
			return;

		this->ViewAngles = local_player->view_angles();
		if (this->ViewAngles.x == 0 || this->ViewAngles.y == 0)
			return;

		this->HeadPos = local_player->bone_position(8);
		if (this->HeadPos.x == 0 || this->HeadPos.y == 0)
			return;

		auto CurrentAngle = this->ViewAngles;
		auto CurrentHeadPos = this->HeadPos;




	}
}; CAntiAim* pAntiAim = new CAntiAim();