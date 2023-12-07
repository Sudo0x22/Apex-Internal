#pragma once
#include<Windows.h>
#include<cstdint>

enum class SignonState : int32_t {
	None,
	Challenge,
	Connected,
	StateNew,
	Prespawn,
	GettingData,
	Spawn,
	FirstSnap,
	Full,
	ChangeLevel,
};

class ClientClass;
