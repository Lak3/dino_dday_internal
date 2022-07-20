#pragma once

#include "minhook/MinHook.h"
#include <memory>

//simple error message, pops up a messagebox if the condition is met.
#define xassert(x) if (x) MessageBoxW(0, L#x, L"fatal error!", MB_ICONERROR)

//a simple error message, also returns false if the condition is met.
#define xassertf(x) if (x) { MessageBoxW(0, L#x, L"fatal error!", MB_ICONERROR); return false; }

class c_detour {
public:
	__inline bool initialize(void* func, void* new_func) {
		return (mh_createhook(func, new_func, &m_original) == 0);
	}

	template<typename fn>
	__inline fn original() const {
		return reinterpret_cast<fn>(m_original);
	}

private:
	void* m_original = nullptr;
};

#define failed_to_hook false

#define create_hook(name, addr, type, conv, ...) namespace hooked \
{ \
namespace name \
{ \
inline c_detour detour; \
using fn = type(conv*)(__VA_ARGS__); \
type conv func(__VA_ARGS__); \
__inline bool initialize() { \
return detour.initialize(reinterpret_cast<void*>(addr), &func); } \
} \
}

#define define_hook(name, type, conv, ...) type conv hooked::name::func(__VA_ARGS__)