#include"../ImGui/imgui.h"
#include<Windows.h>

class ImGuiExtra
{
public:
	__forceinline void CheckBox(LPCSTR szFeature, bool* toggle) { SPOOF_FUNC;  ImGui::Checkbox(szFeature, toggle); }
	__forceinline void Slider(LPCSTR szName, INT* toggle, INT min, INT max, LPCSTR format = "%d") { SPOOF_FUNC; ImGui::SliderInt(szName, toggle, min, max, format); }
	__forceinline bool FloatSlider(LPCSTR szName, FLOAT* toggle, FLOAT min, FLOAT max, LPCSTR format = "%i", FLOAT power = (1.0f)) {
		SPOOF_FUNC;
		return ImGui::SliderFloat(szName, toggle, min, max, format, power);
	}
	__forceinline void WindowSize(ImVec2 Size) { SPOOF_FUNC;  ImGui::SetWindowSize(Size, ImGuiCond_Once); }
public:
	bool ComboBox(LPCSTR label, INT* current_item, LPCSTR const items[], INT items_count) { 
		SPOOF_FUNC;
		return ImGui::Combo(label, current_item, items, items_count, 0);
	}
	__declspec() void Columns(int id) { SPOOF_FUNC; ImGui::Columns(id); }
	__declspec() void SetColumns(int index, float offset) { SPOOF_FUNC; ImGui::SetColumnOffset(index, offset); }
	__declspec() void NextColumns() { SPOOF_FUNC; ImGui::NextColumn(); }
public:
	__declspec() void Spacing1() { SPOOF_FUNC;  ImGui::Spacing(); }
	__declspec() void Spacing3() { SPOOF_FUNC;  ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing(); }
public:
	__declspec() void PushStyleColor(ImGuiCol idx, const ImVec4& clr) { SPOOF_FUNC; ImGui::PushStyleColor(idx, clr); }
	__declspec() bool Button(LPCSTR name, ImVec2 size) { SPOOF_FUNC;  return ImGui::Button(name, size); }
	__declspec() void PopStyleColor(INT index) { SPOOF_FUNC;  ImGui::PopStyleColor(index); }
public:
	__declspec() void Separator() { ImGui::Separator(); }
public:
	__declspec() void PushStyleVar(ImGuiStyleVar idx, const ImVec2& size) { SPOOF_FUNC;  ImGui::PushStyleVar(idx, size); }
	__declspec() void PopStyleVar(INT index) { SPOOF_FUNC; ImGui::PopStyleVar(index); }
public:
	__declspec() void IconButton(LPCSTR icon, ImVec2 size);
	__declspec() void PushFont(ImFont* font) { SPOOF_FUNC;  ImGui::PushFont(font); }
	__declspec() void PopFont() { SPOOF_FUNC; ImGui::PopFont(); }
}; ImGuiExtra* pImGuiFeatures = new ImGuiExtra();

class ImGuiWindowEx
{
public:
	__forceinline void ProcessBackground() {
		SPOOF_FUNC;
		auto background = ImGui::GetBackgroundDrawList();
		background->AddRectFilled(ImVec2{ 0,0 }, ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y), ImColor(15, 15, 15, 200));
	}
	__forceinline void SetSize(ImVec2 Size) {
		SPOOF_FUNC;
		pImGuiFeatures->WindowSize(Size);
	}
	__forceinline bool BeginWindow(LPCSTR name, bool* open = (bool*)0, ImGuiWindowFlags flags = 0) { SPOOF_FUNC; return ImGui::Begin(name, open, flags); }
	__forceinline void EndWindow() { SPOOF_FUNC; ImGui::End(); }
}; ImGuiWindowEx* pImGuiWindow = new ImGuiWindowEx();

class ImGuiChildWindow
{
public:
	bool BeginChildFrame(const char* id, const ImVec2& size = ImVec2(0, 0), bool border = false, ImGuiWindowFlags flags = 0) { SPOOF_FUNC; return ImGui::BeginChild(id, size, border, flags); }
	__declspec() void EndChildFrame() { SPOOF_FUNC; ImGui::EndChild(); }
}; ImGuiChildWindow* pImGuiChildWindow = new ImGuiChildWindow();

class ImGuiTabs
{
public:
	bool BeginTabBar(LPCSTR str_id, ImGuiTabBarFlags flags = 0) { SPOOF_FUNC;  return ImGui::BeginTabBar(str_id, flags); }
	__declspec() void EndTabBar() { SPOOF_FUNC;  ImGui::EndTabBar(); }
public:
	bool BeginTabItem(LPCSTR name, bool* open = (bool*)0, ImGuiTabItemFlags flags = 0) { SPOOF_FUNC;  return ImGui::BeginTabItem(name, open, flags); }
	__declspec() void EndTabItem() { SPOOF_FUNC;  ImGui::EndTabItem(); }
}; ImGuiTabs* pImGuiTabs = new ImGuiTabs();

#include<time.h>
class ImGuiTime
{
public:
	LPCSTR GetTime(LPCSTR szFormat) {
		SPOOF_FUNC;
		time_t now = time(0);
		struct tm tstruct;
		char buf[50];
		tstruct = *localtime(&now);
		__safecall(strftime)(buf, sizeof(buf), szFormat, &tstruct);
		return buf;
	}
}; ImGuiTime* pImGuiTime = new ImGuiTime();

class ImGuiImage
{
public:
	__declspec() void RenderImage(LPCSTR str_id, size_t size, bool* show = (bool*)0) {
		// TODO: Later
	}
};