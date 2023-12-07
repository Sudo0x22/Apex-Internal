#pragma once
#include <type_traits>

// https://github.com/juniorjacob/ret_addr_spoofer

#pragma section(".text")
__declspec(allocate(".text")) const unsigned char jmpRdx[] = { 0xFF, 0x27 };//ReturnSpoof

namespace ReturnAddressSpoofer {
	extern "C" void* SpooferStub();
	template <typename Ret, typename... Args>
	__forceinline static Ret Helper(const void* shell, Args... args)
	{
		auto fn = (Ret(*)(Args...))(shell);
		return fn(args...);
	}

	template <std::size_t Argc, typename>
	struct Remapper
	{
		// At least 5 params
		template< typename Ret, typename First, typename Second, typename Third, typename Fourth, typename... Pack>
		__forceinline static Ret Call(const void* shell, void* shellParam, First first, Second second, Third third, Fourth fourth, Pack... pack)
		{
			return Helper<Ret, First, Second, Third, Fourth, void*, void*, Pack...>(shell, first, second, third, fourth, shellParam, nullptr, pack...);
		}
	};

	template <std::size_t Argc>
	struct Remapper<Argc, std::enable_if_t<Argc <= 4>>
	{
		// 4 or less params
		template<typename Ret, typename First = void*, typename Second = void*, typename Third = void*, typename Fourth = void*>
		__forceinline static Ret Call(const void* shell, void* shellParam, First first = First{}, Second second = Second{}, Third third = Third{}, Fourth fourth = Fourth{})
		{
			return Helper<Ret, First, Second, Third, Fourth, void*, void*>(shell, first, second, third, fourth, shellParam, nullptr);
		}
	};
};

template <typename result, typename... arguments>
__forceinline static result SpoofReturn(result(*fn)(arguments...), arguments... args)
{
	return fn(args...);

	
	/*struct shell_params
	{
		const void* trampoline;
		void* function;
		void* register_; // originally rbx, currently rdx
	};
	//printf("Calling SpoofReturn from %s\n", __FUNCTION__);
	shell_params params{ jmpRdx, reinterpret_cast<void*>(fn) };
	using mapper = ReturnAddressSpoofer::Remapper<sizeof...(arguments), void>;
	return mapper::template Call<result, arguments...>((const void*)&ReturnAddressSpoofer::SpooferStub, &params, args...);*/
	
}

#include <type_traits>

namespace detail
{
	extern "C" void* _spoofer_stub();

	template <typename Ret, typename... Args>
	static inline auto shellcode_stub_helper(
		const void* shell,
		Args... args
	) -> Ret
	{
		auto fn = (Ret(*)(Args...))(shell);
		return fn(args...);
	}

	template <std::size_t Argc, typename>
	struct argument_remapper
	{
		// At least 5 params
		template<
			typename Ret,
			typename First,
			typename Second,
			typename Third,
			typename Fourth,
			typename... Pack
		>
		static auto do_call(
			const void* shell,
			void* shell_param,
			First first,
			Second second,
			Third third,
			Fourth fourth,
			Pack... pack
		) -> Ret
		{
			return shellcode_stub_helper<
				Ret,
				First,
				Second,
				Third,
				Fourth,
				void*,
				void*,
				Pack...
			>(
				shell,
				first,
				second,
				third,
				fourth,
				shell_param,
				nullptr,
				pack...
			);
		}
	};

	template <std::size_t Argc>
	struct argument_remapper<Argc, std::enable_if_t<Argc <= 4>>
	{
		// 4 or less params
		template<
			typename Ret,
			typename First = void*,
			typename Second = void*,
			typename Third = void*,
			typename Fourth = void*
		>
		static auto do_call(
			const void* shell,
			void* shell_param,
			First first = First{},
			Second second = Second{},
			Third third = Third{},
			Fourth fourth = Fourth{}
		) -> Ret
		{
			return shellcode_stub_helper<
				Ret,
				First,
				Second,
				Third,
				Fourth,
				void*,
				void*
			>(
				shell,
				first,
				second,
				third,
				fourth,
				shell_param,
				nullptr
			);
		}
	};
}

template <typename Ret, typename... Args>
static inline auto spoof_call_ex(
	const void* trampoline,
	Ret(*fn)(Args...), 
	Args... args 
) -> Ret
{
	struct shell_params
	{
		const void* trampoline;
		void* function;
		void* rbx;
	};

	shell_params p{ trampoline, reinterpret_cast<void*>(fn) };
	using mapper = detail::argument_remapper<sizeof...(Args), void>;
	return mapper::template do_call<Ret, Args...>((const void*)&detail::_spoofer_stub, &p, args...);
}