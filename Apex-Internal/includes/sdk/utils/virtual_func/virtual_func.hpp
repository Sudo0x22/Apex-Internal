#pragma once
#include<Windows.h>

class virtual_func
{
public:
	__inline void**& GetVTable(void* inst, size_t offset = 0) {
		return *reinterpret_cast<void***>(reinterpret_cast<size_t>(inst) + offset);
	}
	__inline const void** GetVTable(const void* inst, size_t offset = 0) {
		return *reinterpret_cast<const void***>(reinterpret_cast<size_t>(inst) + offset);
	}
public:
	template<typename type>
	__inline type GetVFunc(const void* inst, size_t index, size_t offset = 0) {
		return reinterpret_cast<type>(this->GetVTable(inst, offset)[index]);
	}
};