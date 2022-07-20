#pragma once

#include "netvar_manager/netvar_manager.h"

class c_helpers {
public:
	c_helpers();
	~c_helpers();

public:
	std::unique_ptr<c_control_variables> cvar   = { };
	std::unique_ptr<c_draw_manager>      draw   = { };
	std::unique_ptr<c_input>             input  = { };
	std::unique_ptr<c_netvar_manager>    netvar = { };
};

inline c_helpers helpers;

#define m_netvar(name, type, table, var_name) __inline type name() const { \
static const int off = helpers.netvar->get(table, var_name); \
return *reinterpret_cast<type*>(reinterpret_cast<DWORD>(this) + off); \
}