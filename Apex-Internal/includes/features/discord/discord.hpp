#pragma once
#include"discord_rpc.hpp"
#include "../../modules/spoofer/spoofer.hpp"
#include "../../modules/windows/windows_api.h"
#include "../variables/variables.hpp"

const char* APPLICATION_ID = "";
HMODULE DiscordLib = nullptr;

using InitializeFn = decltype(Discord_Initialize);
using ClearPresenceFn = decltype(Discord_ClearPresence);
using UpdatePresenceFn = decltype(Discord_UpdatePresence);
using ShutdownFn = decltype(Discord_Shutdown);

namespace Discord
{
	InitializeFn* Initialize = nullptr;
	ClearPresenceFn* ClearPresence = nullptr;
	UpdatePresenceFn* UpdatePresence = nullptr;
	ShutdownFn* Shutdown = nullptr;
}

namespace discord
{
	class CDiscordRPC
	{
	private:
		bool m_IsActive = false;
		bool m_Loaded = false;
	public:
		CDiscordRPC();

		void Init();
		void Shutdown();
		void Update();

		bool isLoaded() { return this->m_Loaded; }
	}; CDiscordRPC DiscordRPC;


	CDiscordRPC::CDiscordRPC()
	{
		DiscordLib = spoof_call_ex(jmp_rbx_0, LoadLibraryA, "discord-rpc.dll");
		if (!DiscordLib) { return; }

		Discord::Initialize = reinterpret_cast<InitializeFn*>(spoof_call_ex(jmp_rbx_0, GetProcAddress, DiscordLib, "Discord_Initialize"));
		Discord::ClearPresence = reinterpret_cast<ClearPresenceFn*>(spoof_call_ex(jmp_rbx_0, GetProcAddress, DiscordLib, ""));
		Discord::UpdatePresence = reinterpret_cast<UpdatePresenceFn*>(spoof_call_ex(jmp_rbx_0, GetProcAddress, DiscordLib, ""));
		Discord::Shutdown = reinterpret_cast<ShutdownFn*>(spoof_call_ex(jmp_rbx_0, GetProcAddress, DiscordLib, ""));

		m_Loaded = true;
	}

	void CDiscordRPC::Init()
	{
		if (!m_Loaded) { return; }
		Discord::ClearPresence();
		Discord::Shutdown();
		spoof_call_ex(jmp_rbx_0, FreeLibrary, DiscordLib);
	}

	void CDiscordRPC::Update()
	{
		if (!m_Loaded) { return; }

		if (!misc::discord_rpc) {
			if (m_IsActive) {
				Discord::ClearPresence();
				m_IsActive = false;
			}

			return;
		}

		static int64_t startTime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		DiscordRichPresence discordPresence = {};


	}
}