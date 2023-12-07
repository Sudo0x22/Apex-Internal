#pragma once

#include <Windows.h>
#include <Tlhelp32.h>
#include <psapi.h>
#include <thread>
#include <iostream>
#include <mutex>
#include <vector>
#include<stdio.h>
#include<fstream>
#include<sstream>
#include<filesystem>


#include"xorstr.h"
#include"lazy_importer.h"
#include"memory.h"
#include"hidecall.h"
#include"umium.h"
#include"SkCrypt.h"

template<typename t>
inline t vfunc(DWORD_PTR* pTable, int index)
{
	DWORD_PTR* VTableFunctionBase = *(DWORD_PTR**)pTable;
	DWORD_PTR dwAddress = VTableFunctionBase[index];
	return (t)(dwAddress);
}
