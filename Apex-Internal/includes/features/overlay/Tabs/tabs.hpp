#pragma once
#include"../Extra/extra.hpp"
#include"../../visuals/visuals.hpp"

class Frames
{
public:
	__declspec() void main_aimbot_frame(const char* id, const ImVec2& size = ImVec2(0, 0), bool border = false)
	{
		pImGuiFeatures->PushStyleColor(ImGuiCol_Border, ImColor(53, 53, 53, 255).Value);
		pImGuiChildWindow->BeginChildFrame(id, size, border);
		
		ImGui::SetCursorPosX(115);
		ImGui::Text(skCrypt("Aimbot Settings").decrypt());
		pImGuiFeatures->Separator();

		pImGuiFeatures->Spacing1();
		// aim options
		pImGuiFeatures->CheckBox(skCrypt("Enable Aimbot").decrypt(), &aimbot::enable_aimbot);
		pImGuiFeatures->Spacing1();
		
		pImGuiFeatures->CheckBox(skCrypt("Draw Fov").decrypt(), &aimbot::draw_aim_fov);
		pImGuiFeatures->Spacing1();

		pImGuiFeatures->CheckBox(skCrypt("Smooth Aim").decrypt(), &aimbot::smooth_aim);
		pImGuiFeatures->Spacing1();

		pImGuiFeatures->CheckBox(skCrypt("Slient Aim").decrypt(), &aimbot::slient_aim);
		pImGuiFeatures->Spacing1();

		pImGuiFeatures->CheckBox(skCrypt("Enable NPCS").decrypt(), &aimbot::npcs);
		pImGuiFeatures->Spacing1();

		pImGuiFeatures->CheckBox(skCrypt("No Recoil").decrypt(), &aimbot::no_recoil);
		pImGuiFeatures->Spacing1();

		pImGuiChildWindow->EndChildFrame();
		pImGuiFeatures->PopStyleColor(1);
	}
	__declspec() void second_aimbot_frame(const char* id, const ImVec2& size = ImVec2(0, 0), bool border = false)
	{
		pImGuiFeatures->PushStyleColor(ImGuiCol_Border, ImColor(53, 53, 53, 255).Value);
		pImGuiChildWindow->BeginChildFrame(id, size, border);

		ImGui::SetCursorPosX(105);
		ImGui::Text(skCrypt("Aimbot Misc Settings").decrypt());
		pImGuiFeatures->Separator();

		pImGuiFeatures->Spacing1();

		ImGui::SliderFloat(skCrypt("Aim Fov").decrypt(), &aimbot::aim_fov, 1, 360, skCrypt("%.0f").decrypt());
		pImGuiFeatures->Spacing1();

		ImGui::SliderFloat(skCrypt("Smooth Value").decrypt(), &aimbot::smooth_value, 1, 10, skCrypt("%.0f").decrypt());
		pImGuiFeatures->Spacing1();

		ImGui::SliderFloat(skCrypt("Recoil Amount").decrypt(), &aimbot::recoil_amount, 1, 100, skCrypt("%.0f").decrypt());
		pImGuiFeatures->Spacing1();

		ImGui::SliderFloat(skCrypt("Aim Distance").decrypt(), &aimbot::aim_dist, 10, 1000, skCrypt("%.0f").decrypt());
		pImGuiFeatures->Spacing1();

		pImGuiFeatures->ComboBox(skCrypt("Player Hitboxes").decrypt(), &aimbot::hitboxes::player_hitbox_items, aimbot::hitboxes::player_hitbox_chars, IM_ARRAYSIZE(aimbot::hitboxes::player_hitbox_chars));
		pImGuiFeatures->Spacing1();

		pImGuiFeatures->ComboBox(skCrypt("NPC Hitboxes").decrypt(), &aimbot::hitboxes::npcs_hitbox_items, aimbot::hitboxes::npcs_hitbox_chars, IM_ARRAYSIZE(aimbot::hitboxes::npcs_hitbox_chars));
		pImGuiFeatures->Spacing1();

		pImGuiFeatures->ComboBox(skCrypt("Aim Type").decrypt(), &aimbot::aim_type::aim_items, aimbot::aim_type::aim_chars, IM_ARRAYSIZE(aimbot::aim_type::aim_chars));

		switch (aimbot::hitboxes::player_hitbox_items)
		{
		case 0:
			aimbot::hitbox_set::head_enabled = true;
			break;
		case 1:
			aimbot::hitbox_set::head_enabled = false;
			aimbot::hitbox_set::neck_enabled = true;
			break;
		case 2:
			aimbot::hitbox_set::head_enabled = false;
			aimbot::hitbox_set::neck_enabled = false;
			aimbot::hitbox_set::body_enabled = true;
			break;
		case 3:
			aimbot::hitbox_set::head_enabled = false;
			aimbot::hitbox_set::neck_enabled = false;
			aimbot::hitbox_set::body_enabled = false;
			aimbot::hitbox_set::legs_enabled = true;
			break;
		case 4:
			aimbot::hitbox_set::head_enabled = false;
			aimbot::hitbox_set::neck_enabled = false;
			aimbot::hitbox_set::body_enabled = false;
			aimbot::hitbox_set::legs_enabled = false;
			aimbot::hitbox_set::feet_enabled = true;
		}

		switch (aimbot::aim_type::aim_items)
		{
		case 0:
			aimbot::fov_closest = true;
			break;
		case 1:
			aimbot::fov_closest = false;
			aimbot::fov_aim = true;
			break;
		case 2:
			aimbot::fov_aim = false;
			aimbot::fov_closest = false;
			aimbot::cursor = true;
			break;
		}

		pImGuiChildWindow->EndChildFrame();
		pImGuiFeatures->PopStyleColor(1);
	}
public:
	/*__declspec() void main_trigger_frame(const char* id, const ImVec2& size = ImVec2(0, 0), bool border = false)
	{
		pImGuiFeatures->PushStyleColor(ImGuiCol_Border, ImColor(53, 53, 53, 255).Value);
		pImGuiChildWindow->BeginChildFrame(id, size, border);

		ImGui::SetCursorPosX(115);
		ImGui::Text(skCrypt("Triggerbot Settings").decrypt());
		pImGuiFeatures->Separator();

		pImGuiFeatures->CheckBox(__("Enable Triggerbot"), &triggerbot::enable_trigger_bot);
		pImGuiFeatures->Separator();

		ImGui::SliderInt(__("Trigger Fov"), &triggerbot::trigger_fov, 0, 180, "%i");

		pImGuiChildWindow->EndChildFrame();
		pImGuiFeatures->PopStyleColor(1);
	}
	__declspec() void second_trigger_frame(const char* id, const ImVec2& size = ImVec2(0, 0), bool border = false)
	{
		pImGuiFeatures->PushStyleColor(ImGuiCol_Border, ImColor(53, 53, 53, 255).Value);
		pImGuiChildWindow->BeginChildFrame(id, size, border);

		ImGui::SetCursorPosX(105);
		ImGui::Text(skCrypt("Triggerbot Misc Settings").decrypt());
		pImGuiFeatures->Separator();

		pImGuiChildWindow->EndChildFrame();
		pImGuiFeatures->PopStyleColor(1);
	}*/
public:
	__declspec() void main_visuals_frame(const char* id, const ImVec2& size = ImVec2(0, 0), bool border = false)
	{
		pImGuiFeatures->PushStyleColor(ImGuiCol_Border, ImColor(53, 53, 53, 255).Value);
		pImGuiChildWindow->BeginChildFrame(id, size, border);

		ImGui::SetCursorPosX(115);
		ImGui::Text(skCrypt("Visual Settings").decrypt());
		pImGuiFeatures->Separator();
		pImGuiFeatures->Spacing1();

		pImGuiFeatures->CheckBox("Enable Visuals", &visuals::enable_visuals);
		pImGuiFeatures->Spacing1();

		pImGuiFeatures->CheckBox(skCrypt("Enable Radar").decrypt(), &visuals::render_radar_option);
		pImGuiFeatures->Spacing1();

		pImGuiFeatures->CheckBox(skCrypt("Enable Outline").decrypt(), &visuals::enable_outline);
		pImGuiFeatures->Spacing1();

		pImGuiFeatures->CheckBox(skCrypt("Enable Box Esp").decrypt(), &visuals::enable_box);
		pImGuiFeatures->Spacing1();

		pImGuiFeatures->CheckBox(skCrypt("Enable Health Info").decrypt(), &visuals::seers_info);
		pImGuiFeatures->Spacing1();

		pImGuiFeatures->CheckBox(skCrypt("Enable Name Esp").decrypt(), &visuals::name_esp);
		pImGuiFeatures->Spacing1();

		pImGuiFeatures->CheckBox(skCrypt("Enable Dist To Esp").decrypt(), &visuals::dist_to);
		pImGuiFeatures->Spacing1();

		pImGuiChildWindow->EndChildFrame();
		pImGuiFeatures->PopStyleColor(1);
	}
	__declspec() void second_visuals_frame(const char* id, const ImVec2& size = ImVec2(0, 0), bool border = false)
	{
		pImGuiFeatures->PushStyleColor(ImGuiCol_Border, ImColor(53, 53, 53, 255).Value);
		pImGuiChildWindow->BeginChildFrame(id, size, border);

		ImGui::SetCursorPosX(105);
		ImGui::Text(skCrypt("Visual Misc Settings").decrypt());
		pImGuiFeatures->Separator();

		pImGuiFeatures->CheckBox(skCrypt("Skin Changer").decrypt(), &visuals::init_skin_changer);
		pImGuiFeatures->Spacing1();

		/*pImGuiFeatures->CheckBox(skCrypt("Spec Counter").decrypt(), &visuals::enable_spec_list);
		pImGuiFeatures->Spacing1();*/

		pImGuiFeatures->CheckBox(skCrypt("Enable ThirdPerson").decrypt(), &visuals::enable_thirdperson);
		pImGuiFeatures->Spacing1();

		pImGuiFeatures->CheckBox(skCrypt("Warning Sign").decrypt(), &visuals::render_warning_sign);
		pImGuiFeatures->Spacing1();

		pImGuiFeatures->CheckBox(skCrypt("Item Outline").decrypt(), &visuals::item_esp);
		pImGuiFeatures->Spacing1();

		ImGui::SliderFloat(skCrypt("Max Esp Dist").decrypt(), &visuals::max_esp_dist, 1, 500, skCrypt("%.0f").decrypt());
		pImGuiFeatures->Spacing1();

		pImGuiFeatures->ComboBox(skCrypt("Box Type").decrypt(), &visuals::box_items, visuals::box_chars, IM_ARRAYSIZE(visuals::box_chars));
		pImGuiFeatures->Spacing1();

		pImGuiFeatures->ComboBox(skCrypt("Health Type").decrypt(), &visuals::health_items, visuals::health_chars, IM_ARRAYSIZE(visuals::health_chars));
		pImGuiFeatures->Spacing1();

		switch (visuals::box_items)
		{
		case 0:
			visuals::stand_box = true;
			visuals::corner_box = false;
			//visuals::multid_box = false;
			break;
		case 1:
			visuals::stand_box = false;
			//visuals::multid_box = false;
			visuals::corner_box = true;
			break;
		}

		switch (visuals::health_items)
		{
		case 0:
			visuals::health_bar = true;
			visuals::seers_health = false;
			break;
		case 1:
			visuals::health_bar = false;
			visuals::seers_health = true;
		}

		/*ImGui::ColorEdit3(skCrypt("Box Color").decrypt(), visuals::box_color, 0);
		pImGuiFeatures->Spacing1();*/

		pImGuiChildWindow->EndChildFrame();
		pImGuiFeatures->PopStyleColor(1);
	}
public:
	__declspec() void main_misc_frame(const char* id, const ImVec2& size = ImVec2(0, 0), bool border = false)
	{
		pImGuiFeatures->PushStyleColor(ImGuiCol_Border, ImColor(53, 53, 53, 255).Value);
		pImGuiChildWindow->BeginChildFrame(id, size, border);

		ImGui::SetCursorPosX(125);
		ImGui::Text(skCrypt("Misc Settings").decrypt());
		pImGuiFeatures->Separator();

		pImGuiFeatures->CheckBox(__("Unlock All"), &misc::unlock_all);
		pImGuiFeatures->Spacing1();

	/*	pImGuiFeatures->CheckBox(__("Auto Tap Strafe"), &misc::tap_strafe);
		pImGuiFeatures->Spacing1();*/

		pImGuiFeatures->CheckBox(__("Free cam"), &misc::free_cam);
		pImGuiFeatures->Spacing1();

		/*pImGuiFeatures->CheckBox(__("No Spread"), &misc::no_spread);
		pImGuiFeatures->Spacing1();*/

		/*pImGuiFeatures->CheckBox(__("Fake Duck"), &misc::fake_duck);
		pImGuiFeatures->Spacing1();*/

		pImGuiChildWindow->EndChildFrame();
		pImGuiFeatures->PopStyleColor(1);
	}
	__declspec() void second_misc_frame(const char* id, const ImVec2& size = ImVec2(0, 0), bool border = false)
	{
		pImGuiFeatures->PushStyleColor(ImGuiCol_Border, ImColor(53, 53, 53, 255).Value);
		pImGuiChildWindow->BeginChildFrame(id, size, border);

		ImGui::SetCursorPosX(115);
		ImGui::Text(skCrypt("Misc Extra Settings").decrypt());
		pImGuiFeatures->Separator();

		pImGuiFeatures->CheckBox(__("Speed Hack"), &misc::speed_hack);
		pImGuiFeatures->Spacing1();

		/*pImGuiFeatures->CheckBox(__("Charge Rifle"), &misc::charge_rifle_exploit);
		pImGuiFeatures->Spacing1();*/

		/*pImGuiFeatures->CheckBox(__("Auto Glide"), &misc::auto_super_glide);
		pImGuiFeatures->Spacing1();*/

		pImGuiFeatures->CheckBox(__("Auto Grapple"), &misc::auto_grapple);
		pImGuiFeatures->Spacing1();

		pImGuiFeatures->CheckBox(__("Fps Window"), &misc::render_frame_window);
		pImGuiFeatures->Spacing1();


		pImGuiChildWindow->EndChildFrame();
		pImGuiFeatures->PopStyleColor(1);
	}
}; Frames* pFrames;

class tabs
{
public:
	__declspec() void aimbot_tab() 
	{
		pImGuiFeatures->PushFont(pInitStyle->VerdanaSmall);
		pFrames->main_aimbot_frame(skCrypt("##Aimbot").decrypt(), ImVec2(318, 409), true);
		ImGui::SameLine();
		ImGui::SetCursorPosX(462);
		pFrames->second_aimbot_frame(skCrypt("##AimbotMisc").decrypt(), ImVec2(318, 409), true);
		pImGuiFeatures->PopFont();
	}
	/*__declspec() void triggerbot_tab() 
	{
		pImGuiFeatures->PushFont(pInitStyle->VerdanaSmall);
		pFrames->main_trigger_frame(skCrypt("##Trigger").decrypt(), ImVec2(318, 409), true);
		ImGui::SameLine();
		ImGui::SetCursorPosX(462);
		pFrames->second_trigger_frame(skCrypt("##TriggerMisc").decrypt(), ImVec2(318, 409), true);
		pImGuiFeatures->PopFont();
	}*/
public:
	__declspec() void visuals_tab() 
	{
		pImGuiFeatures->PushFont(pInitStyle->VerdanaSmall);
		pFrames->main_visuals_frame(skCrypt("##Visuals").decrypt(), ImVec2(318, 409), true);
		ImGui::SameLine();
		ImGui::SetCursorPosX(462);
		pFrames->second_visuals_frame(skCrypt("##VisualsMisc").decrypt(), ImVec2(318, 409), true);
		pImGuiFeatures->PopFont();
	}
	__declspec() void misc_tab() 
	{
		pImGuiFeatures->PushFont(pInitStyle->VerdanaSmall);
		pFrames->main_misc_frame(skCrypt("##Misc").decrypt(), ImVec2(318, 409), true);
		ImGui::SameLine();
		ImGui::SetCursorPosX(462);
		pFrames->second_misc_frame(skCrypt("##MiscMisc").decrypt(), ImVec2(318, 409), true);
		pImGuiFeatures->PopFont();
	}
}; tabs* pTabs = new tabs();
