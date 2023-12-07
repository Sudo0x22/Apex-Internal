#pragma once
#include"IBaseClient/IBaseClient.h"
#include"IClientEntityList/IClientEntityList.hpp"
#include"IEngineClient/IEngineClient.hpp"
#include"ICvar/ICvar.hpp"

#include "../../../apex_src/steam/isteamclient.h"
#include "../../../apex_src/steam/isteamfriends.h"
#include "../../../apex_src/steam/isteamutils.h"
#include "../../../apex_src/steam/isteamapps.h"
#include "../../../apex_src/steam/isteamuserstats.h"
#include "../../../apex_src/steam/isteamuser.h"
#include "../../../apex_src/steam/isteamnetworkingutils.h"

namespace I
{
	IBaseClientDLL* Client = nullptr;
	IEngineClient* Engine = nullptr;
	IClientEntityList* EntityList = nullptr;
	ICvar* CVar = nullptr;
	ISteamClient* SteamClient = nullptr;
	ISteamFriends* SteamFriends = nullptr;
	ISteamUtils* SteamUtils = nullptr;
	ISteamApps* SteamApps = nullptr;
	ISteamUserStats* SteamUserStats = nullptr;
	ISteamUser* SteamUser = nullptr;
	ISteamNetworkingUtils* SteamNetworkUtils = nullptr;
}

namespace Capture
{
	template<typename type>
	inline type* CaptureInterfaces(const char* module_name, const char* library_name)
	{
		auto h_module = SpoofReturn(GetModuleHandleA, library_name);
		if (!h_module)
			return nullptr;
		auto h_function = SpoofReturn(GetProcAddress, h_module, "CreateInterface");
		if (!h_function)
			return nullptr;

		using Fn = type * (*)(const char*, int*);
		const auto CreateInterfaceEx = reinterpret_cast<Fn>(h_function);

		return CreateInterfaceEx(module_name, nullptr);
	}
}

namespace InitInterfaces
{
	__inline void InitSteam() 
	{
		I::SteamClient = Capture::CaptureInterfaces<ISteamClient>(STEAMCLIENT_INTERFACE_VERSION, "steamclient.dll");

		const HSteamPipe hsNewPipe = I::SteamClient->CreateSteamPipe();
		const HSteamPipe hsNewUser = I::SteamClient->ConnectToGlobalUser(hsNewPipe);

		I::SteamFriends = I::SteamClient->GetISteamFriends(hsNewUser, hsNewPipe, STEAMFRIENDS_INTERFACE_VERSION);
		I::SteamUtils = I::SteamClient->GetISteamUtils(hsNewUser, STEAMUTILS_INTERFACE_VERSION);
		I::SteamApps = I::SteamClient->GetISteamApps(hsNewUser, hsNewPipe, STEAMAPPS_INTERFACE_VERSION);
		I::SteamUserStats = I::SteamClient->GetISteamUserStats(hsNewUser, hsNewPipe, STEAMUSERSTATS_INTERFACE_VERSION);
		I::SteamUser = I::SteamClient->GetISteamUser(hsNewUser, hsNewPipe, STEAMUSER_INTERFACE_VERSION);

		const auto hModule = SpoofReturn(GetModuleHandleA, "steamnetworkingsockets.dll");
		static auto Fn = reinterpret_cast<ISteamNetworkingUtils * (__cdecl*)()>(SpoofReturn(GetProcAddress, hModule, "SteamNetworkingUtils_LibV4"));
		I::SteamNetworkUtils = Fn();

	}

	__inline void InitGame()
	{
		I::Client = Capture::CaptureInterfaces<IBaseClientDLL>("", "r5apex.exe");
		I::Engine = Capture::CaptureInterfaces<IEngineClient>("", "r5apex.exe");
		I::EntityList = Capture::CaptureInterfaces<IClientEntityList>("", "r5apex.exe");
	}

	inline void Initialize()
	{
		//InitSteam();
		//InitGame();
	}
}