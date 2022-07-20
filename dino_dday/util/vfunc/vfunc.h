#pragma once

#include "../pattern/pattern.h"

class c_vfunc {
public:
	template<typename fn>
	__inline fn get(void* inst, const unsigned int idx, const unsigned int off = 0u) {
		return static_cast<fn>(get_internal(inst, off)[idx]);
	}

private:
	void**&      get_internal(void* inst, const unsigned int off = 0u);
	const void** get_internal(const void* inst, const unsigned int off = 0u);
};