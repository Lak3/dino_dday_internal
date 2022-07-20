#pragma once

#include "../hash/hash.h"

using hmodule = HMODULE;

class c_interface {
public:
	template<typename fn>
	__inline fn get(const char* const mod, const char* const obj) {
		const hmodule hmod = GetModuleHandleA(mod);

		if (!hmod)
			return 0;

		void* ret = get_internal(hmod, obj);

		return ret ? static_cast<fn>(ret) : 0;
	}

private:
	void* get_internal(const hmodule mod, const char* const obj);
};

