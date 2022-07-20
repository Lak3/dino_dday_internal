#pragma once

#include "../../helpers/helpers.h"

class c_client_unknown : public c_handle_entity {
public:

};

class c_client_thinkable {
public:

};

class c_client_renderable {
public:

};

class c_client_networkable {
public:

};

class c_client_entity : public c_client_unknown, public c_client_renderable, public c_client_networkable, public c_client_thinkable {
public: //networkable, todo: move to their own classes
	__inline client_class* get_client_class() {
		void* net = reinterpret_cast<void*>(reinterpret_cast<unsigned long>(this) + 8u);
		return net ? util.vfunc->get<client_class* (__thiscall*)(void*)>(net, 2u)(net) : nullptr;
	}

	__inline bool is_dormant() {
		void* net = reinterpret_cast<void*>(reinterpret_cast<unsigned long>(this) + 8u);
		return net ? util.vfunc->get<bool(__thiscall*)(void*)>(net, 9u)(net) : true;
	}

	__inline int entindex() {
		void* net = reinterpret_cast<void*>(reinterpret_cast<unsigned long>(this) + 8u);
		return net ? util.vfunc->get<int(__thiscall*)(void*)>(net, 10u)(net) : 0;
	}

public: //renderable, todo: move to their own classes
	__inline const model_t* get_model() {
		void* rend = reinterpret_cast<void*>(reinterpret_cast<unsigned long>(this) + 4u);
		return rend ? util.vfunc->get<const model_t* (__thiscall*)(void*)>(rend, 8u)(rend) : nullptr;
	}

	__inline bool setup_bones(matrix3x4_t* b2w, const int max, const int mask, const float curtime) {
		void* rend = reinterpret_cast<void*>(reinterpret_cast<unsigned long>(this) + 4u);
		return rend ? util.vfunc->get<bool(__thiscall*)(void*, matrix3x4_t*, int, int, float)>(rend, 13u)(rend, b2w, max, mask, curtime) : false;
	}

	__inline const matrix3x4_t& renderable_to_world_transform() {
		static const matrix3x4_t null_matrix = { };

		void* rend = reinterpret_cast<void*>(reinterpret_cast<unsigned long>(this) + 4u);
		return rend ? util.vfunc->get<const matrix3x4_t& (__thiscall*)(void*)>(rend, 32u)(rend) : null_matrix;
	}

public: //other	
	template<typename t>
	__inline t as() {
		return static_cast<t>(this);
	}
};