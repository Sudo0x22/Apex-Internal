#pragma once
#include<Windows.h>
#include<cstdint>

class IBaseClientDLL
{
private:
	virtual bool ClientAuthInterface() = 0;
	virtual bool InitClientAuth() = 0;
public:

};