#pragma once

#include "declarations/surface.h"

class c_interfaces {
public:
	c_interfaces();
	~c_interfaces();

public:
	bool initialize();

public:
	c_base_client*        base_client   = nullptr;
	c_engine_client*      engine_client = nullptr;
	c_engine_trace*       engine_trace  = nullptr;
	c_engine_vgui*        engine_vgui   = nullptr;
	c_client_entity_list* entity_list   = nullptr;
	c_game_movement*      game_movement = nullptr;
	c_model_info_client*  model_info    = nullptr;
	c_move_helper*        move_helper   = nullptr;
	c_vgui_panel*         panel         = nullptr;
	c_prediction*         prediction    = nullptr;
	c_vgui_surface*       surface       = nullptr;
	c_globalvars_base*    global_vars   = nullptr;
};

inline c_interfaces ints;