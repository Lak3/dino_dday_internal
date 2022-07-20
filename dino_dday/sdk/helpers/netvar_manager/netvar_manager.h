#pragma once

#include "../input/input.h"

class c_netvar_manager {
public:
	int get(const char* const class_name, const char* const var_name);

private:
	int get_internal(c_recv_table* table, const char* const var_name);
};