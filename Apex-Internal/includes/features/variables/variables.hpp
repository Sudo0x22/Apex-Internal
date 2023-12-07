#include<Windows.h>
#include"json.hpp"

const std::string SPAM_SYNC[] = {
	"Sync Solutions Owning Since 2K17",
	"Killing Meth Heads Since 90s",
	"www.syncsolutions.build"
};

namespace anti_aim
{
	bool enable_anti_aimbot = false;
}

namespace aimbot
{
	bool enable_aimbot = false;
	bool draw_aim_fov = false;
	
	static float aim_fov = 1.f;
	bool smooth_aim = false;
	static float smooth_value = 1.f;

	bool slient_aim = false;
	bool npcs = false;
	bool no_recoil = false;
	float recoil_amount = 50.f;

	float aim_dist = 1000;

	namespace hitboxes
	{
		static int player_hitbox_items = 0;
		const char* player_hitbox_chars[5] = { "Head", "Neck", "Body", "Legs", "Feet" };

		static int npcs_hitbox_items = 0;
		const char* npcs_hitbox_chars[5] = { "Head", "Neck", "Body", "Legs", "Feet" };
	}

	namespace hitbox_set
	{
		static bool head_enabled = false;
		static bool neck_enabled = false;
		static bool body_enabled = false;
		static bool legs_enabled = false;
		static bool feet_enabled = false;
	}

	namespace aim_type
	{
		static int aim_items = 0;
		const char* aim_chars[3] = { "Closest", "Fov", "Cursor" };
	}

	static bool fov_closest = false;
	static bool fov_aim = false;
	static bool cursor = false;
}

namespace triggerbot
{
	static bool enable_trigger_bot = false;
	static int trigger_fov = 0;
}

namespace visuals
{
	bool enable_visuals = false;
	bool enable_outline = false;
	bool enable_chams = false;

	bool enable_users = false;

	bool item_esp = false;
	
	bool enable_box = false;
	bool name_esp = false;
	bool health_esp = false;

	bool weapon_chams = false;

	bool enable_thirdperson = false;
	bool line_esp = false;
	bool seers_info = false;

	static float view_fov = 90.f;

	namespace colors {
		float glow_color[3];
		float chams_color[3];
	}

	bool init_skin_changer = false;
	bool skin_roller = false;
	int weapon_skin_id = 0;
	
	bool render_radar_option = false;
	bool render_frame_window = false;
	bool render_warning_sign = false;

	bool dist_to = false;

	float ouline_color_visible[3] = { 150.0f,150.0f,150.0f };
	float ouline_color_nonvisible[3] = { 150.0f,150.0f,150.0f };
	float box_color[3] = { 150.0f,150.0f,150.0f };

	float max_esp_dist = 100.0f;

	static bool corner_box = false;
	static bool stand_box = false;
	static bool multid_box = false;

	static int box_items = 0;
	const char* box_chars[2] = { "Normal", "Cornerd" };

	static int glow_items = 0;
	const char* glow_chars[3] = { "Team Glow", "Stenical", "Health" };

	static int health_items = 0;
	const char* health_chars[2] = { "Normal", "Seers" };

	static bool enable_spec_list = false;
	std::string spec_list = "";

	static bool seers_health = false;
	static bool health_bar = false;
}

namespace misc
{
	bool unlock_all = false;
	bool render_frame_window = false;
	bool tap_strafe = false;
	bool free_cam = false;
	bool no_spread = false;
	bool fake_duck = false;
	bool speed_hack = false;
	bool charge_rifle_exploit = false;
	bool auto_super_glide = false;
	bool auto_grapple = false;
	bool discord_rpc = false;
	bool chat_spam = false;
}

namespace configs
{
	//std::string config_path = "C:\\Windows\\System32\\configs";
	std::vector<std::string> left;

	int selected_config = 0;

	template<typename Type>
	void try_val();
}