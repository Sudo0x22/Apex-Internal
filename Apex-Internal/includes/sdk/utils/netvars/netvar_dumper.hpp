#pragma once
#include"netvars.hpp"

namespace NetVarOffsets
{
	namespace DT_BasePlayer
	{
		uintptr_t m_iTeamNum;
		uintptr_t m_iHealth;
	}

	namespace DT_BaseEntity
	{


	}
}

class NetVarManager
{
public:
	std::vector<recv_table*> GetTables()
	{
		std::vector<recv_table*> tables;
		//ClientClass* clientClass = InterfacesEx::Client->GetAllClasses();

	}
	recv_table* GetTable(std::vector< recv_table*> tables, const char* tableName);
	int GetOffset(std::vector< recv_table*> tables, const char* tableName, const char* propName);
	int GetRecvProp(std::vector< recv_table*> tables, const char* tableName, const char* propName, RecvProp** prop = 0);
	int GetRecvProp(std::vector<recv_table*> tables, recv_table* recvTable, const char* propName, RecvProp** prop = 0);
};

class NetVars
{
public:
	void Initialize();
};