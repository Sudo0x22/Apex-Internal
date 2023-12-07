#pragma once
#include"../ImGui/imgui.h"
#include"../ImGui/imgui_impl_dx11.h"
#include"../ImGui/imgui_impl_win32.h"
#include"../ImGui/imgui_internal.h"
#include"fonts/icons_data.hpp"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class Window
{
public:
	ImVec2 TitlePos = ImVec2(0.5, 0.5);
	ImVec2 WindowSize = ImVec2(795, 425);
public:
	float WindowRounding = 4.0f;
	float ChildRounding = 4.0f;
public:
	__forceinline void InitializeWindow()
	{
		SPOOF_FUNC;
		ImGuiStyle* pStyle = &ImGui::GetStyle();
		pStyle->WindowTitleAlign = this->TitlePos;
		pStyle->WindowRounding = this->WindowRounding;
	}
}; Window* pInitWindow = new Window();

ImU32 GetU32(int r, int b, int g, int a)
{
	SPOOF_FUNC;
	return ((a & 0xff) << 24) + ((g & 0xff) << 16) + ((b & 0xff) << 8)
		+ (r & 0xff);
}

ImVec4 Hex(int hexValue, float alpha)
{
	SPOOF_FUNC;
	float r = (hexValue >> 16) & 0xFF;
	float g = (hexValue >> 8) & 0xFF;
	float b = hexValue & 0xFF;

	return ImVec4(r / 255, g / 255, b / 255, alpha);
}

class WindowStyle
{
public:
	ImFont* TitleFont = nullptr;
	ImFont* SectionFont = nullptr;
	ImFont* VerdanaSmall = nullptr;
	ImFont* IconFont = nullptr;
	ImFont* gameFont = NULL;
public:
	ImColor WindowBackground = ImColor(0,0,0,250);
	
	ImColor ChildBackground = ImColor(0,0,0, 240);
	ImColor WindowTitleBar = ImColor(0,0,0,250);
	ImColor WindowSeparator = ImColor(68,0,255,255);
	
	ImColor WindowBorder = ImColor(68, 0, 255, 255);
	ImColor WindowButtonActive = ImColor(85, 0, 255, 255);
	ImColor WindowButtonHovered = ImColor(85, 0, 255, 255);

	ImColor WindowSlider = ImColor(68, 0, 255, 255);
	ImColor WindowSliderGrab = ImColor(68, 0, 255, 255);

	ImColor WindowFrameBackground = ImColor(28, 28, 28, 255);
	ImColor WindowFrameHover = ImColor(85, 0, 255, 255);
	ImColor WindowFrameActive = ImColor(85, 0, 255, 255);

	ImColor WindowFrameExtra = ImColor(85, 0, 255, 255);
public:
	__forceinline void InitializeStyle()
	{
		SPOOF_FUNC;
		ImGuiStyle& style = ImGui::GetStyle();
		ImGui::StyleColorsDark();

		style.WindowRounding = 4;
		style.ChildRounding = 4;
		style.FrameRounding = 3;
		style.PopupRounding = 3;
		style.GrabRounding = 3;
		style.TabRounding = 3;
		style.ScrollbarRounding = 3;
		style.ButtonTextAlign = { 0.5f, 0.5f };
		style.WindowTitleAlign = { 0.5f, 0.5f };
		style.FramePadding = { 6.0f, 6.0f };
		style.ItemSpacing = { 9.0f, 9.0f };
		style.WindowPadding = { 9.0f, 9.0f };
		style.ItemInnerSpacing = { 8.0f, 4.0f };
		style.WindowBorderSize = 1;
		style.FrameBorderSize = 1;
		style.ScrollbarSize = 12.f;
		style.GrabMinSize = 8.f;
		//style.WindowShadowSize = 0.f;

		//style.Colors[ImGuiCol_WindowShadow] = Hex(0xDB4141, 1.0f); // 0x5E61BA

		style.Colors[ImGuiCol_WindowBg] = Hex(0x111111, 1.0f);
		style.Colors[ImGuiCol_ChildBg] = Hex(0x151515, 1.0f);
		style.Colors[ImGuiCol_MenuBarBg] = Hex(0x191919, 1.0f);

		style.Colors[ImGuiCol_TitleBg] = Hex(0x111111, 1.0f);
		style.Colors[ImGuiCol_TitleBgActive] = Hex(0x111111, 1.0f);

		style.Colors[ImGuiCol_Border] = Hex(0x1F1F1F, 1.0f);
		style.Colors[ImGuiCol_Separator] = Hex(0x1F1F1F, 1.0f);

		style.Colors[ImGuiCol_SliderGrab] = Hex(0x5500ffd9, 1.0f);
		style.Colors[ImGuiCol_SliderGrabActive] = Hex(0x5500ffd9, 0.8f);

		style.Colors[ImGuiCol_CheckMark] = Hex(0xE8E8E8, 1.0f);
		style.Colors[ImGuiCol_Text] = Hex(0xE8E8E8, 1.0f);
		style.Colors[ImGuiCol_TextDisabled] = Hex(0x616161, 1.0f);

		style.Colors[ImGuiCol_Header] = Hex(0x212121, 1.0f);
		style.Colors[ImGuiCol_HeaderHovered] = Hex(0x444444, 1.0f);
		style.Colors[ImGuiCol_HeaderActive] = Hex(0x363636, 1.0f);

		style.Colors[ImGuiCol_FrameBg] = Hex(0x111111, 1.0f);
		style.Colors[ImGuiCol_FrameBgHovered] = Hex(0x111111, 0.9f);
		style.Colors[ImGuiCol_FrameBgActive] = Hex(0x111111, 0.8f);

		style.Colors[ImGuiCol_Button] = Hex(0x111111, 1.0f);
		style.Colors[ImGuiCol_ButtonHovered] = Hex(0x111111, 0.8f);
		style.Colors[ImGuiCol_ButtonActive] = Hex(0x111111, 0.6f);

		style.Colors[ImGuiCol_ScrollbarBg] = ImColor(0, 0, 0, 0);
		style.Colors[ImGuiCol_ScrollbarGrab] = ImColor(0, 0, 0, 0);
		style.Colors[ImGuiCol_ScrollbarGrabActive] = ImColor(0, 0, 0, 0);
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImColor(0, 0, 0, 0);
	}
	__declspec() void InitializeFonts()
	{
		SPOOF_FUNC;
		{
			const auto& io = ImGui::GetIO();
			auto fontConfig = ImFontConfig();
			fontConfig.OversampleH = 2;
			constexpr ImWchar fontRange[]{ 0x0020, 0x00FF,0x0400, 0x044F, 0 };
			this->VerdanaSmall = io.Fonts->AddFontFromFileTTF(skCrypt("C:\\Windows\\Fonts\\verdana.ttf").decrypt(), 12.0f, &fontConfig, fontRange);
			this->TitleFont = io.Fonts->AddFontFromFileTTF(skCrypt("C:\\Windows\\Fonts\\verdanab.ttf").decrypt(), 20.0f, &fontConfig, fontRange);

			constexpr ImWchar iconRange[]{ ICON_MIN_MD, ICON_MAX_MD, 0 };
			ImFontConfig iconConfig;
			iconConfig.MergeMode = true;
			iconConfig.PixelSnapH = true;
			IconFont = io.Fonts->AddFontFromMemoryCompressedTTF(MaterialFont_compressed_data, MaterialFont_compressed_size, 12.f, &iconConfig, iconRange);
			
			gameFont = ImGui::GetIO().Fonts->AddFontDefault();

			io.Fonts->Build();
		}
	}
}; WindowStyle* pInitStyle = new WindowStyle();