#pragma once
#include"../../../features/overlay/ImGui/imgui.h"

int ScreenWidth = GetSystemMetrics(SM_CXSCREEN); int screenX = ScreenWidth / 2;
int ScreenHeight = GetSystemMetrics(SM_CYSCREEN); int screenY = ScreenHeight / 2;

std::string string_To_UTF8(const std::string& str)
{
	int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);

	wchar_t* pwBuf = new wchar_t[nwLen + 1];
	ZeroMemory(pwBuf, nwLen * 2 + 2);

	::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);

	int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

	char* pBuf = new char[nLen + 1];
	ZeroMemory(pBuf, nLen + 1);

	::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	std::string retStr(pBuf);

	delete[]pwBuf;
	delete[]pBuf;

	pwBuf = NULL;
	pBuf = NULL;

	return retStr;
}

typedef struct
{
	DWORD R;
	DWORD G;
	DWORD B;
	DWORD A;
}RGBA;

typedef struct CColor
{
    float r;
    float g;
    float b;
    float a;
};


class Color
{
public:
	RGBA red = { 255, 0, 0, 255 };
	RGBA white_ = { 255, 255, 255, 200 };
	RGBA gray_ = { 128, 128, 128, 200 };
	RGBA black = { 0, 0, 0, 255 };
	RGBA black_ = { 0, 0, 0, 100 };
	RGBA red_ = { 255, 0, 0, 200 };

	RGBA glassblack = { 0, 0, 0, 160 };
	RGBA GlassBlue = { 65, 105, 225, 80 };
	RGBA glassyellow = { 255, 255, 0, 160 };
	RGBA glass = { 200, 200, 200, 60 };


	RGBA Plum = { 221, 160, 221, 160 };

	RGBA FOV = { 54,54,54,255 };
	RGBA LineEsp = { 200,2,2,255 };
	RGBA BoxEsp = { 150,0,150,100 };
	RGBA SideBoxEsp = { 0, 0, 0, 255 };
	RGBA DistEsp = { 32,42,68,255 };
	RGBA NameEsp = { 32,42,68,255 };
	RGBA SkelitonEsp = { 255,255,255,255 };
};
Color allcol;

class Draw
{
public:
	__declspec() void DrawLine(const ImVec2& aPoint1, const ImVec2 aPoint2, ImU32 aColor, const float aLineWidth) 
	{
		auto vList = ImGui::GetBackgroundDrawList();
		vList->AddLine(aPoint1, aPoint2, aColor, aLineWidth);
	}
	
	__declspec() void DrawBox(float x, float y, float W, float H, const ImU32& Color, float thickness) 
	{
		auto vList = ImGui::GetBackgroundDrawList();
		
		float lineW = (W / 3);
		float lineH = (H / 3);

		auto col = ImGui::GetColorU32(Color);
		vList->AddLine(ImVec2(x, y - thickness / 2), ImVec2(x, y + lineH), col, thickness);
		vList->AddLine(ImVec2(x - thickness / 2, y), ImVec2(x + lineW, y), col, thickness);

		vList->AddLine(ImVec2(x + W - lineW, y), ImVec2(x + W + thickness / 2, y), col, thickness);//top right horizontal
		vList->AddLine(ImVec2(x + W, y - thickness / 2), ImVec2(x + W, y + lineH), col, thickness);

		vList->AddLine(ImVec2(x, y + H - lineH), ImVec2(x, y + H + (thickness / 2)), col, thickness);//bot left
		vList->AddLine(ImVec2(x - thickness / 2, y + H), ImVec2(x + lineW, y + H), col, thickness);

		vList->AddLine(ImVec2(x + W - lineW, y + H), ImVec2(x + W + thickness / 2, y + H), col, thickness);//bot right
		vList->AddLine(ImVec2(x + W, y + H - lineH), ImVec2(x + W, y + H + (thickness / 2)), col, thickness);
	}
	
	__declspec() void DrawCircle(float size, ImColor Color) 
	{
		auto vList = ImGui::GetBackgroundDrawList();
		vList->AddCircle(ImVec2(ScreenWidth / 2, ScreenHeight / 2), size, Color, 100, 1.f);
	}

	void DrawQuadFilled(ImVec2 p1, ImVec2 p2, ImVec2 p3, ImVec2 p4, ImColor color) {
		ImGui::GetForegroundDrawList()->AddQuadFilled(p1, p2, p3, p4, color);
	}

	void DrawHexagon(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, const ImVec2& p5, const ImVec2& p6, ImU32 col, float thickness)
	{
		ImGui::GetForegroundDrawList()->AddHexagon(p1, p2, p3, p4, p5, p6, col, thickness);
	}
	void DrawHexagonFilled(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, const ImVec2& p5, const ImVec2& p6, ImU32 col)
	{
		ImGui::GetForegroundDrawList()->AddHexagonFilled(p1, p2, p2, p4, p5, p6, col);
	}

	void DrawFilledRect(int x, int y, int w, int h, RGBA* color)
	{
		ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), 0, 0);
	}

    void DrawRect(int x, int y, int w, int h, RGBA* color, int thickness)
    {
        ImGui::GetOverlayDrawList()->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), 0, 0, thickness);
    }

	void DrawCornerBox(int x, int y, int w, int h, int borderPx, RGBA* color)
	{
		DrawFilledRect(x + borderPx, y, w / 3, borderPx, color); //top 
		DrawFilledRect(x + w - w / 3 + borderPx, y, w / 3, borderPx, color); //top 
		DrawFilledRect(x, y, borderPx, h / 3, color); //left 
		DrawFilledRect(x, y + h - h / 3 + borderPx * 2, borderPx, h / 3, color); //left 
		DrawFilledRect(x + borderPx, y + h + borderPx, w / 3, borderPx, color); //bottom 
		DrawFilledRect(x + w - w / 3 + borderPx, y + h + borderPx, w / 3, borderPx, color); //bottom 
		DrawFilledRect(x + w + borderPx, y, borderPx, h / 3, color);//right 
		DrawFilledRect(x + w + borderPx, y + h - h / 3 + borderPx * 2, borderPx, h / 3, color);//right 
	}

	void SeerHealth(float x, float y, int shield, int max_shield, int armorType, int health) {

        int bg_offset = 3;
        int bar_width = 83;
        // 4steps...2*3=6
        // 38*4=152 152+6 = 158
        // 5steps...2*4=8
        // 30*5=150 150+8 = 158
        float max_health = 100.0f;
        float shield_step = 25.0f;

        int shield_25 = 15;
        int steps = 5;
        //if (strncmp(gamemode, "arena", 5) == 0 || armorType == 4)
        //{ //not EVO shield (arena or gold armor)
        //    steps = 4;
        //    shield_25 = 38;
        //}

        ImVec2 bg1(x - bar_width / 2 - bg_offset, y);
        ImVec2 bg2(bg1.x - 10, bg1.y - 16);
        ImVec2 bg3(bg2.x + 5, bg2.y - 7);
        ImVec2 bg4(bg3.x + bar_width + bg_offset, bg3.y);
        ImVec2 bg5(bg4.x + 11, bg4.y + 18);
        ImVec2 bg6(x + bar_width / 2 + bg_offset, y);
        DrawHexagonFilled(bg1, bg2, bg3, bg4, bg5, bg6, ImColor(0, 0, 0, 120));


        ImVec2 h1(bg1.x + 3, bg1.y - 4);
        ImVec2 h2(h1.x - 5, h1.y - 8);
        ImVec2 h3(h2.x + (float)health / max_health * bar_width, h2.y);
        ImVec2 h4(h1.x + (float)health / max_health * bar_width, h1.y);
        ImVec2 h3m(h2.x + bar_width, h2.y);
        ImVec2 h4m(h1.x + bar_width, h1.y);
        DrawQuadFilled(h1, h2, h3m, h4m, ImColor(10, 10, 30, 60));
        DrawQuadFilled(h1, h2, h3, h4, ImColor(250, 250, 250, 255));


        ImColor shieldCracked(97, 97, 97);
        ImColor shieldCrackedDark(67, 67, 67);

        ImColor shieldCol;
        ImColor shieldColDark; //not used, but the real seer q has shadow inside
        if (armorType == 1)
        { //white
            shieldCol = ImColor(247, 247, 247);
            shieldColDark = ImColor(164, 164, 164);
        }
        else if (armorType == 2)
        { //blue
            shieldCol = ImColor(39, 178, 255);
            shieldColDark = ImColor(27, 120, 210);
        }
        else if (armorType == 3)
        { //purple
            shieldCol = ImColor(206, 59, 255);
            shieldColDark = ImColor(136, 36, 220);
        }
        else if (armorType == 4)
        { //gold
            shieldCol = ImColor(255, 255, 79);
            shieldColDark = ImColor(218, 175, 49);
        }
        else if (armorType == 5)
        { //red
            shieldCol = ImColor(219, 2, 2);
            shieldColDark = ImColor(219, 2, 2);
        }
        else
        {
            shieldCol = ImColor(247, 247, 247);
            shieldColDark = ImColor(164, 164, 164);
        }
        int shield_tmp = shield;
        int shield1 = 0;
        int shield2 = 0;
        int shield3 = 0;
        int shield4 = 0;
        int shield5 = 0;
        if (shield_tmp > 25)
        {
            shield1 = 25;
            shield_tmp -= 25;
            if (shield_tmp > 25)
            {
                shield2 = 25;
                shield_tmp -= 25;
                if (shield_tmp > 25)
                {
                    shield3 = 25;
                    shield_tmp -= 25;
                    if (shield_tmp > 25)
                    {
                        shield4 = 25;
                        shield_tmp -= 25;
                        shield5 = shield_tmp;
                    }
                    else
                    {
                        shield4 = shield_tmp;
                    }
                }
                else
                {
                    shield3 = shield_tmp;
                }
            }
            else
            {
                shield2 = shield_tmp;
            }
        }
        else
        {
            shield1 = shield_tmp;
        }
        ImVec2 s1(h2.x - 1, h2.y - 2);
        ImVec2 s2(s1.x - 3, s1.y - 5);
        ImVec2 s3(s2.x + shield1 / shield_step * shield_25, s2.y);
        ImVec2 s4(s1.x + shield1 / shield_step * shield_25, s1.y);
        ImVec2 s3m(s2.x + shield_25, s2.y);
        ImVec2 s4m(s1.x + shield_25, s1.y);

        ImVec2 ss1(s4m.x + 2, s1.y);
        ImVec2 ss2(s3m.x + 2, s2.y);
        ImVec2 ss3(ss2.x + shield2 / shield_step * shield_25, s2.y);
        ImVec2 ss4(ss1.x + shield2 / shield_step * shield_25, s1.y);
        ImVec2 ss3m(ss2.x + shield_25, s2.y);
        ImVec2 ss4m(ss1.x + shield_25, s1.y);

        ImVec2 sss1(ss4m.x + 2, s1.y);
        ImVec2 sss2(ss3m.x + 2, s2.y);
        ImVec2 sss3(sss2.x + shield3 / shield_step * shield_25, s2.y);
        ImVec2 sss4(sss1.x + shield3 / shield_step * shield_25, s1.y);
        ImVec2 sss3m(sss2.x + shield_25, s2.y);
        ImVec2 sss4m(sss1.x + shield_25, s1.y);

        ImVec2 ssss1(sss4m.x + 2, s1.y);
        ImVec2 ssss2(sss3m.x + 2, s2.y);
        ImVec2 ssss3(ssss2.x + shield4 / shield_step * shield_25, s2.y);
        ImVec2 ssss4(ssss1.x + shield4 / shield_step * shield_25, s1.y);
        ImVec2 ssss3m(ssss2.x + shield_25, s2.y);
        ImVec2 ssss4m(ssss1.x + shield_25, s1.y);

        ImVec2 sssss1(ssss4m.x + 2, s1.y);
        ImVec2 sssss2(ssss3m.x + 2, s2.y);
        ImVec2 sssss3(sssss2.x + shield5 / shield_step * shield_25, s2.y);
        ImVec2 sssss4(sssss1.x + shield5 / shield_step * shield_25, s1.y);
        ImVec2 sssss3m(sssss2.x + shield_25, s2.y);
        ImVec2 sssss4m(sssss1.x + shield_25, s1.y);
        if (max_shield == 50)
        {
            if (shield <= 25)
            {
                if (shield < 25)
                {
                    DrawQuadFilled(s1, s2, s3m, s4m, shieldCracked);
                    DrawQuadFilled(ss1, ss2, ss3m, ss4m, shieldCracked);
                }
                if (shield != 0)
                    DrawQuadFilled(s1, s2, s3, s4, shieldCol);

            }
            else if (shield <= 50)
            {
                DrawQuadFilled(s1, s2, s3, s4, shieldCol);
                if (shield != 50)
                {
                    DrawQuadFilled(ss1, ss2, ss3m, ss4m, shieldCracked);
                }
                if (shield != 0)
                    DrawQuadFilled(ss1, ss2, ss3, ss4, shieldCol);
            }
        }
        else if (max_shield == 75)
        {
            if (shield <= 25)
            {
                if (shield < 25)
                {
                    DrawQuadFilled(s1, s2, s3m, s4m, shieldCracked);
                    DrawQuadFilled(ss1, ss2, ss3m, ss4m, shieldCracked);
                    DrawQuadFilled(sss1, sss2, sss3m, sss4m, shieldCracked);
                }
                if (shield != 0)
                    DrawQuadFilled(s1, s2, s3, s4, shieldCol);

            }
            else if (shield <= 50)
            {
                DrawQuadFilled(s1, s2, s3, s4, shieldCol);
                if (shield < 50)
                {
                    DrawQuadFilled(ss1, ss2, ss3m, ss4m, shieldCracked);
                    DrawQuadFilled(sss1, sss2, sss3m, sss4m, shieldCracked);
                }
                if (shield != 0)
                    DrawQuadFilled(ss1, ss2, ss3, ss4, shieldCol);
            }
            else if (shield <= 75)
            {
                DrawQuadFilled(s1, s2, s3, s4, shieldCol);
                DrawQuadFilled(ss1, ss2, ss3, ss4, shieldCol);
                if (shield < 75)
                {
                    DrawQuadFilled(sss1, sss2, sss3m, sss4m, shieldCracked);
                }
                if (shield != 0)
                    DrawQuadFilled(sss1, sss2, sss3, sss4, shieldCol);
            }
        }
        else if (max_shield == 100)
        {
            if (shield <= 25)
            {
                if (shield < 25)
                {
                    DrawQuadFilled(s1, s2, s3m, s4m, shieldCracked);
                    DrawQuadFilled(ss1, ss2, ss3m, ss4m, shieldCracked);
                    DrawQuadFilled(sss1, sss2, sss3m, sss4m, shieldCracked);
                    DrawQuadFilled(ssss1, ssss2, ssss3m, ssss4m, shieldCracked);
                }
                if (shield != 0)
                    DrawQuadFilled(s1, s2, s3, s4, shieldCol);

            }
            else if (shield <= 50)
            {
                DrawQuadFilled(s1, s2, s3, s4, shieldCol);
                if (shield < 50)
                {
                    DrawQuadFilled(ss1, ss2, ss3m, ss4m, shieldCracked);
                    DrawQuadFilled(sss1, sss2, sss3m, sss4m, shieldCracked);
                    DrawQuadFilled(ssss1, ssss2, ssss3m, ssss4m, shieldCracked);
                }
                if (shield != 0)
                    DrawQuadFilled(ss1, ss2, ss3, ss4, shieldCol);
            }
            else if (shield <= 75)
            {
                DrawQuadFilled(s1, s2, s3, s4, shieldCol);
                DrawQuadFilled(ss1, ss2, ss3, ss4, shieldCol);
                if (shield < 75)
                {
                    DrawQuadFilled(sss1, sss2, sss3m, sss4m, shieldCracked);
                    DrawQuadFilled(ssss1, ssss2, ssss3m, ssss4m, shieldCracked);
                }
                if (shield != 0)
                    DrawQuadFilled(sss1, sss2, sss3, sss4, shieldCol);
            }
            else if (shield <= 100)
            {
                DrawQuadFilled(s1, s2, s3, s4, shieldCol);
                DrawQuadFilled(ss1, ss2, ss3, ss4, shieldCol);
                DrawQuadFilled(sss1, sss2, sss3, sss4, shieldCol);
                if (shield < 100)
                {
                    DrawQuadFilled(ssss1, ssss2, ssss3m, ssss4m, shieldCracked);
                }
                if (shield != 0)
                    DrawQuadFilled(ssss1, ssss2, ssss3, ssss4, shieldCol);
            }
        }
        else if (max_shield == 125)
        {
            if (shield <= 25)
            {
                if (shield < 25)
                {
                    DrawQuadFilled(s1, s2, s3m, s4m, shieldCracked);
                    DrawQuadFilled(ss1, ss2, ss3m, ss4m, shieldCracked);
                    DrawQuadFilled(sss1, sss2, sss3m, sss4m, shieldCracked);
                    DrawQuadFilled(ssss1, ssss2, ssss3m, ssss4m, shieldCracked);
                    DrawQuadFilled(sssss1, sssss2, sssss3m, sssss4m, shieldCracked);
                }
                if (shield != 0)
                    DrawQuadFilled(s1, s2, s3, s4, shieldCol);

            }
            else if (shield <= 50)
            {
                DrawQuadFilled(s1, s2, s3, s4, shieldCol);
                if (shield < 50)
                {
                    DrawQuadFilled(ss1, ss2, ss3m, ss4m, shieldCracked);
                    DrawQuadFilled(sss1, sss2, sss3m, sss4m, shieldCracked);
                    DrawQuadFilled(ssss1, ssss2, ssss3m, ssss4m, shieldCracked);
                    DrawQuadFilled(sssss1, sssss2, sssss3m, sssss4m, shieldCracked);
                }
                if (shield != 0)
                    DrawQuadFilled(ss1, ss2, ss3, ss4, shieldCol);
            }
            else if (shield <= 75)
            {
                DrawQuadFilled(s1, s2, s3, s4, shieldCol);
                DrawQuadFilled(ss1, ss2, ss3, ss4, shieldCol);
                if (shield < 75)
                {
                    DrawQuadFilled(sss1, sss2, sss3m, sss4m, shieldCracked);
                    DrawQuadFilled(ssss1, ssss2, ssss3m, ssss4m, shieldCracked);
                    DrawQuadFilled(sssss1, sssss2, sssss3m, sssss4m, shieldCracked);
                }
                if (shield != 0)
                    DrawQuadFilled(sss1, sss2, sss3, sss4, shieldCol);
            }
            else if (shield <= 100)
            {
                DrawQuadFilled(s1, s2, s3, s4, shieldCol);
                DrawQuadFilled(ss1, ss2, ss3, ss4, shieldCol);
                DrawQuadFilled(sss1, sss2, sss3, sss4, shieldCol);
                if (shield < 100)
                {
                    DrawQuadFilled(ssss1, ssss2, ssss3m, ssss4m, shieldCracked);
                    DrawQuadFilled(sssss1, sssss2, sssss3m, sssss4m, shieldCracked);
                }
                if (shield != 0)
                    DrawQuadFilled(ssss1, ssss2, ssss3, ssss4, shieldCol);
            }
            else if (shield <= 125)
            {
                DrawQuadFilled(s1, s2, s3, s4, shieldCol);
                DrawQuadFilled(ss1, ss2, ss3, ss4, shieldCol);
                DrawQuadFilled(sss1, sss2, sss3, sss4, shieldCol);
                DrawQuadFilled(ssss1, ssss2, ssss3, ssss4, shieldCol);
                if (shield < 125)
                {
                    DrawQuadFilled(sssss1, sssss2, sssss3m, sssss4m, shieldCracked);
                }
                if (shield != 0)
                    DrawQuadFilled(sssss1, sssss2, sssss3, sssss4, shieldCol);
            }
        }
	}

	auto health_bar(float x, float y, float w, float h, int phealth) -> VOID
	{
		auto vList = ImGui::GetOverlayDrawList();

		int healthValue = max(0, min(phealth, 100));

		int barColor = ImColor
		(min(510 * (100 - healthValue) / 100, 255), min(510 * healthValue / 100, 255), 25, 255);
		/*if (cfg.healthbaroutline)
		{
		}*/
		vList->AddRect(ImVec2(x - 1, y - 1), ImVec2(x + w + 1, y + h + 1), ImColor(0, 0, 0));
		vList->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + (((float)h / 100.0f) * (float)phealth)), barColor, 0.0f, 0);
	}

	auto shield_bar(float x, float y, float w, float h, int pshield) -> VOID
	{
		auto vList = ImGui::GetOverlayDrawList();
		int ShieldValue = max(0, min(pshield, 100));
		int barColor = ImColor(min(510 * (100 - ShieldValue) / 100, 255), min(510 & ShieldValue / 100, 255), 25, 255);
		vList->AddRect(ImVec2(x - 1, y - 1), ImVec2(x + w + 1, y + h + 1), ImColor(0, 0, 0));
		vList->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + (((float)h / 100.0f) * (float)pshield)), barColor, 0.0f, 0);
	}

	void draw_text(int x, int y, RGBA* color, const char* str, ...)
	{
		va_list(args);
		va_start(args, str);

		CHAR wbuffer[256] = { };
		vsprintf_s(wbuffer, str, args);

		va_end(args);

		ImFont a;
		std::string utf_8_1 = std::string(str);
		std::string utf_8_2 = string_To_UTF8(utf_8_1);
		ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), wbuffer);
	}

	float DrawOutlinedText( ImFont* pFont, const ImVec2& pos, float size, ImU32 color, bool center, const char* text, ... )
{
	va_list( args );
	va_start( args, text );

	CHAR wbuffer [ 256 ] = { };
	vsprintf_s( wbuffer, text, args );

	va_end( args );

	ImDrawList* window = ImGui::GetOverlayDrawList( );

	std::stringstream stream( text );
	std::string line;

	float y = 0.0f;
	int i = 0;

	while ( std::getline( stream, line ) )
	{
		ImVec2 textSize = pFont->CalcTextSizeA( size, FLT_MAX, 0.0f, wbuffer );

		if ( center )
		{
			window->AddText( pFont, size, ImVec2( ( pos.x - textSize.x / 2.0f ) + 1, ( pos.y + textSize.y * i ) + 1 ), ImGui::GetColorU32( ImVec4( 0, 0, 0, 255 ) ), wbuffer );
			window->AddText( pFont, size, ImVec2( ( pos.x - textSize.x / 2.0f ) - 1, ( pos.y + textSize.y * i ) - 1 ), ImGui::GetColorU32( ImVec4( 0, 0, 0, 255 ) ), wbuffer );
			window->AddText( pFont, size, ImVec2( ( pos.x - textSize.x / 2.0f ) + 1, ( pos.y + textSize.y * i ) - 1 ), ImGui::GetColorU32( ImVec4( 0, 0, 0, 255 ) ), wbuffer );
			window->AddText( pFont, size, ImVec2( ( pos.x - textSize.x / 2.0f ) - 1, ( pos.y + textSize.y * i ) + 1 ), ImGui::GetColorU32( ImVec4( 0, 0, 0, 255 ) ), wbuffer );

			window->AddText( pFont, size, ImVec2( pos.x - textSize.x / 2.0f, pos.y + textSize.y * i ), ImGui::GetColorU32( color ), wbuffer );
		}
		else
		{
			window->AddText( pFont, size, ImVec2( ( pos.x ) + 1, ( pos.y + textSize.y * i ) + 1 ), ImGui::GetColorU32( ImVec4( 0, 0, 0, 255 ) ), wbuffer );
			window->AddText( pFont, size, ImVec2( ( pos.x ) - 1, ( pos.y + textSize.y * i ) - 1 ), ImGui::GetColorU32( ImVec4( 0, 0, 0, 255 ) ), wbuffer );
			window->AddText( pFont, size, ImVec2( ( pos.x ) + 1, ( pos.y + textSize.y * i ) - 1 ), ImGui::GetColorU32( ImVec4( 0, 0, 0, 255 ) ), wbuffer );
			window->AddText( pFont, size, ImVec2( ( pos.x ) - 1, ( pos.y + textSize.y * i ) + 1 ), ImGui::GetColorU32( ImVec4( 0, 0, 0, 255 ) ), wbuffer );

			window->AddText( pFont, size, ImVec2( pos.x, pos.y + textSize.y * i ), ImGui::GetColorU32( color ), wbuffer );
		}

		y = pos.y + textSize.y * ( i + 1 );
		i++;
	}
	return y;
}

}; Draw* pDraw = new Draw();