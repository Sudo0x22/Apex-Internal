#pragma once
#include<vector>
#include<string>
#include "../../sdk/apex_src/cbaseentity/cbaseentity.hpp"
#include "../../sdk/apex_src/vguisystem/vguisystem.hpp"

class CSyncUsers
{
private:
	std::string username = "";
	int username_length = 0;
	int total_users = 0;
public:
	CSyncUsers()
	{
		std::string users = username;
		int max_users = total_users;

		if (users == "")
			return;

		if (max_users == 0)
			return;



	}
public:
	void capture_users(std::vector<std::string> users, std::vector<int> total_users,
		int x, int y)
	{
		uint32_t array_size = users.size();
		int total_size = total_users.size();

		for (uint32_t players = 1; players < 64; players++)
		{
			Entity* entity = get_entiy(players);
			
			if (entity == NULL)
				continue;
			
			if (entity->name() == users[players].c_str())
				pDraw->draw_text(x, y, &allcol.GlassBlue, "[ Sync ]: %s", users[players].c_str());
		}
	}

	void initialize(int x, int y)
	{
		capture_users({ this->username }, { this->total_users }, x, y);
	}
}; CSyncUsers* pSyncUsers = new CSyncUsers();