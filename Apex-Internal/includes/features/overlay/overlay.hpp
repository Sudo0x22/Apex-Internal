#pragma once
#include"DX11/DX11.hpp"
#include"window/window.hpp"
#include"key_helper/key_helper.hpp"
#include"Tabs/tabs.hpp"
#include"Image/Image.h"
#include <D3DX11tex.h>
#pragma comment(lib, "D3DX11.lib")

static int items = 0;

class OverlaySnowEffect
{
public:
	__inline void DrawRainEffect() {
		SPOOF_FUNC;
		struct RainFlakeT {
			int X;
			int Y;
		};

		static std::vector<RainFlakeT> vRainFlakes;
		const int RainCount = 1000;
		
		static bool bInit = false;
		while (!bInit) {
			for (int i = 0; i < RainCount; i++) {
				vRainFlakes.emplace_back(Utils::RandIntSimple(0, ImGui::GetIO().DisplaySize.x), Utils::RandIntSimple(0, ImGui::GetIO().DisplaySize.y / 2.f));
			}
			bInit = true;
		}

		const auto& MenuFont = pInitStyle->gameFont;
		for (auto& flake : vRainFlakes) {
			constexpr int drift = 1;
			flake.X += Utils::RandIntSimple(-drift, drift);
			flake.Y += drift;

			const float alpha = Math::MapFloat(flake.Y, 0.0f, ImGui::GetIO().DisplaySize.y / 2.f, 1.0f, 0.0f);
			if (alpha <= 0.f || flake.X >= ImGui::GetIO().DisplaySize.x || flake.X <= 0) {
				flake.X = Utils::RandIntSimple(0, ImGui::GetIO().DisplaySize.x);
				flake.Y = Utils::RandIntSimple(0, 150);
			}

			pDraw->draw_text(flake.X, flake.Y, &allcol.white_, __("|"));
		}
	}
	void DrawMenuSnow() {
		SPOOF_FUNC;
		struct SnowFlakeT {
			int X;
			int Y;
		};

		static std::vector<SnowFlakeT> vSnowFlakes;
		constexpr int snowCount = 150;

		static bool bInit = false;
		while (!bInit) {
			for (int i = 0; i < snowCount; i++) {
				vSnowFlakes.emplace_back(Utils::RandIntSimple(0, ImGui::GetIO().DisplaySize.x), Utils::RandIntSimple(0, ImGui::GetIO().DisplaySize.y / 2.f));
			}
			bInit = true;
		}

		const auto& menuFont = pInitStyle->gameFont;
		for (auto& flake : vSnowFlakes) {
			constexpr int drift = 1;
			flake.X += Utils::RandIntSimple(-drift, drift);
			flake.Y += drift;

			const float alpha = Math::MapFloat(flake.Y, 0.0f, ImGui::GetIO().DisplaySize.y / 2.f, 1.0f, 0.0f);
			if (alpha <= 0.f || flake.X >= ImGui::GetIO().DisplaySize.x || flake.X <= 0)
			{
				flake.X = Utils::RandIntSimple(0, ImGui::GetIO().DisplaySize.x);
				flake.Y = Utils::RandIntSimple(0, 150);
			}

			pDraw->draw_text(flake.X, flake.Y, &allcol.white_, __("*"));
		}
	}
}; OverlaySnowEffect* pOverlaySnowEffect = new OverlaySnowEffect();

#include <Lmcons.h>

class OverlayWatermark
{
public:
	__inline void Draw()
	{
		SPOOF_FUNC;
		char* user = getenv(__("username"));
		std::string username_pointer = std::string(user);

		pDraw->draw_text(0, 0, &allcol.white_, __("Developer Build Registered To: %s"), username_pointer);
		pDraw->draw_text(0, 10, &allcol.white_, __("Build Version: %hs"), __DATE__ "" __TIME__);
		pDraw->draw_text(0, 20, &allcol.white_, __("https://sync.solutions"));

	}
}; OverlayWatermark* pOverlayWatermark = new OverlayWatermark();

class Overlay
{
public:
	bool init_imgui = false;
	bool render_overlay = false;
	bool capture_cursor = false;
	bool render_cursor = false;
public:
	DWORD window_flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar;
	bool close_button = true;
public:

	enum class MenuTabs
	{
		Aimbot,
		Triggerbot,
		Visuals,
		Binds,
		Misc,
		Configs
	};

	MenuTabs CurrentTab = MenuTabs::Visuals;

public:
	__forceinline void InitImGui() 
	{
		SPOOF_FUNC;
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		/*D3DX11_IMAGE_LOAD_INFO info;
		ID3DX11ThreadPump* pump{ nullptr };
		D3DX11CreateShaderResourceViewFromMemory(pD3D11->pDevice, rawData, sizeof(rawData), &info,
			pump, &Image, 0);*/

		ImGui_ImplWin32_Init(pD3D11->hWindow);
		ImGui_ImplDX11_Init(pD3D11->pDevice, pD3D11->pContext);
	}

	__forceinline void InitStyle() 
	{
		SPOOF_FUNC;
		pInitWindow->InitializeWindow();
		pInitStyle->InitializeStyle();
		pInitStyle->InitializeFonts();
	}

	__declspec() void Tabs(MenuTabs Tab)
	{
		SPOOF_FUNC;
		switch (Tab)
		{
		case MenuTabs::Aimbot:
			pTabs->aimbot_tab();
			break;
		/*case MenuTabs::Triggerbot:
			pTabs->triggerbot_tab();
			break;*/
		case MenuTabs::Visuals:
			pTabs->visuals_tab();
			break;
		case MenuTabs::Misc:
			pTabs->misc_tab();
			break;
/*		case MenuTabs::Configs:
			pTabs->configs_tab();
			break;*/
		}
	}

	std::string icon_text(std::string icon, std::string text)
	{
		SPOOF_FUNC;
		auto add_strings = icon + text;
		return add_strings;
	}

	__forceinline void MenuTab()
	{
		SPOOF_FUNC;
		// skCrypt(%d-%m-%Y | %X).decrypt();
		int height = 40;
		int width = 100;

		pImGuiFeatures->Columns(2);
		pImGuiFeatures->SetColumns(1, width + 30);

		static MenuTabs Tab = MenuTabs::Visuals;
		{
			static ImVec4 InActive = ImVec4(0.09f, 0.09, 0.09f, 0.88f);
			static ImVec4 Active = ImVec4(0.0f, 0.5f, 0.5f, 0.9f);

		/*	ImGui::SetCursorPosX(5);
			ImGui::Image((LPVOID)Image, ImVec2(125, 140));*/
			
			pImGuiFeatures->Spacing1();
			ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 4.f);
			pImGuiFeatures->PushFont(pInitStyle->IconFont);
		
			/*pImGuiFeatures->PushStyleColor(ImGuiCol_Button, Tab == MenuTabs::Aimbot ? Active : InActive);
			if (pImGuiFeatures->Button(this->icon_text(ICON_MD_SETTINGS, skCrypt(" Aimbot").decrypt()).c_str(), ImVec2(width, height)))
				Tab = MenuTabs::Aimbot;
			*/

			/*pImGuiFeatures->Spacing1();
			pImGuiFeatures->PushStyleColor(ImGuiCol_Button, Tab == MenuTabs::Triggerbot ? Active : InActive);
			if (pImGuiFeatures->Button(this->icon_text(ICON_MD_ZOOM_IN, skCrypt(" Trigger").decrypt()).c_str(), ImVec2(width, height)))
				Tab = MenuTabs::Triggerbot;*/

			pImGuiFeatures->Spacing1();
			pImGuiFeatures->PushStyleColor(ImGuiCol_Button, Tab == MenuTabs::Visuals ? Active : InActive);
			if (pImGuiFeatures->Button(this->icon_text(ICON_MD_BRUSH, skCrypt(" Visuals").decrypt()).c_str(), ImVec2(width, height)))
				Tab = MenuTabs::Visuals;

			pImGuiFeatures->Spacing1();
			pImGuiFeatures->PushStyleColor(ImGuiCol_Button, Tab == MenuTabs::Misc ? Active : InActive);
			if (pImGuiFeatures->Button(this->icon_text(ICON_MD_KEYBOARD, skCrypt(" Misc  ").decrypt()).c_str(), ImVec2(width, height)))
				Tab = MenuTabs::Misc;

			/*pImGuiFeatures->Spacing1();
			pImGuiFeatures->PushStyleColor(ImGuiCol_Button, Tab == MenuTabs::Misc ? Active : InActive);
			if (pImGuiFeatures->Button(this->icon_text(ICON_MD_KEYBOARD, skCrypt(" Configs  ").decrypt()).c_str(), ImVec2(width, height)))
				Tab = MenuTabs::Configs;*/

			pImGuiFeatures->PopFont();
			pImGuiFeatures->PopStyleColor(2);
			pImGuiFeatures->PopStyleVar(1);
		}

		pImGuiFeatures->NextColumns();
		{
			this->Tabs(Tab);
		}
	}

	__forceinline void RenderOverlay()
	{
		SPOOF_FUNC;
		pImGuiWindow->ProcessBackground();
		
		if (pImGuiWindow->BeginWindow(skCrypt("Synchronize | Solutions").decrypt(), &this->close_button, this->window_flags)) 
		{
			pImGuiWindow->SetSize(pInitWindow->WindowSize);
			this->MenuTab();
			pImGuiWindow->EndWindow();
		}
	}
}; Overlay* pOverlay = new Overlay();