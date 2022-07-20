#include "interfaces.h"

#define failed_to_find_interface nullptr

c_interfaces::c_interfaces() {
	base_client   = nullptr;
	engine_client = nullptr;
	engine_trace  = nullptr;
	engine_vgui   = nullptr;
	entity_list   = nullptr;
	game_movement = nullptr;
	model_info    = nullptr;
	move_helper   = nullptr;
	panel         = nullptr;
	prediction    = nullptr;
	surface       = nullptr;
	global_vars   = nullptr;
}

c_interfaces::~c_interfaces() {
	base_client   = nullptr;
	engine_client = nullptr;
	engine_trace  = nullptr;
	engine_vgui   = nullptr;
	entity_list   = nullptr;
	game_movement = nullptr;
	model_info    = nullptr;
	move_helper   = nullptr;
	panel         = nullptr;
	prediction    = nullptr;
	surface       = nullptr;
	global_vars   = nullptr;
}

bool c_interfaces::initialize() {
	base_client = util.iface->get<c_base_client*>("client.dll", "VClient016");
	xassertf(base_client == failed_to_find_interface);

	engine_client = util.iface->get<c_engine_client*>("engine.dll", "VEngineClient015");
	xassertf(engine_client == failed_to_find_interface);

	engine_trace = util.iface->get<c_engine_trace*>("engine.dll", "EngineTraceClient004");
	xassertf(engine_trace == failed_to_find_interface);

	engine_vgui = util.iface->get<c_engine_vgui*>("engine.dll", "VEngineVGui001");
	xassertf(engine_vgui == failed_to_find_interface);

	entity_list = util.iface->get<c_client_entity_list*>("client.dll", "VClientEntityList003");
	xassertf(entity_list == failed_to_find_interface);

	game_movement = util.iface->get<c_game_movement*>("client.dll", "GameMovement001");
	xassertf(game_movement == failed_to_find_interface);

	model_info = util.iface->get<c_model_info_client*>("engine.dll", "VModelInfoClient004");
	xassertf(model_info == failed_to_find_interface);

	panel = util.iface->get<c_vgui_panel*>("vgui2.dll", "VGUI_Panel009");
	xassertf(panel == failed_to_find_interface);

	prediction = util.iface->get<c_prediction*>("client.dll", "VClientPrediction001");
	xassertf(prediction == failed_to_find_interface);

	surface = util.iface->get<c_vgui_surface*>("vguimatsurface.dll", "VGUI_Surface031");
	xassertf(surface == failed_to_find_interface);
	
	//other shenanigans, these from mactec
	{
		unsigned long* client_table = *reinterpret_cast<unsigned long**>(base_client);
		unsigned long* input = *reinterpret_cast<unsigned long**>(reinterpret_cast<unsigned long*>(client_table[15] + 2u));
		input = *reinterpret_cast<unsigned long**>(input);
		xassertf(input == failed_to_find_interface);

		unsigned long* input_table = *reinterpret_cast<unsigned long**>(input);
		global_vars = *reinterpret_cast<c_globalvars_base**>(reinterpret_cast<unsigned long*>(input_table[3] + 273u));
		global_vars = *reinterpret_cast<c_globalvars_base**>(global_vars);
		xassertf(global_vars == failed_to_find_interface);
	}

	console_msg("c_interfaces::initialize() finished successfully.\n");
	return true;
}