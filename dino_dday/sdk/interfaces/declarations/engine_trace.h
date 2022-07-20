#pragma once

#include "engine_client.h"

class c_engine_trace {
public:
	__inline void trace_ray(const ray_t& r, const unsigned int mask, c_trace_filter* fltr, trace_t* tr) {
		util.vfunc->get<void(__thiscall*)(c_engine_trace*, const ray_t&, unsigned int, c_trace_filter*, trace_t*)>(this, 5u)(this, r, mask, fltr, tr);
	}
};