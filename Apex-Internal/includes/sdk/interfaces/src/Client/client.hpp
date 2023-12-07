#include"../../../../features/overlay/overlay.hpp"
#include"../../../apex_src/apex_src.hpp"
#include"../../../utils/utils.hpp"
#include"../../../../features/anti_aim/anti_aim.hpp"


/*namespace client
{
	inline hook::table Table;

	namespace override_view
	{
		using Fn = bool(__fastcall*)(void*, void*, void*);
		constexpr unsigned int nIndex = 18u;
		bool __fastcall detour(void* ecx, void* edx, void* eax);
	}

	namespace create_move
	{
		using Fn = bool(__fastcall*)(void*,int,float,bool);
		constexpr unsigned int nIndex = 21u;
		bool __fastcall detour(void* ecx, int number, float frametime, bool active)
		{

			return Table.Original<Fn>(nIndex)(ecx, number, frametime, active);
		}
	}

	namespace get_view_module_fov
	{
		using Fn = float(__fastcall*)(void*, void*);
		constexpr unsigned int nIndex = 34u;
		float __fastcall detour(void* ecx, void* edx)
		{

			return Table.Original<Fn>(nIndex)(ecx, edx);
		}
	}

	void create_hook();
}*/