#pragma once

#include "entities/entities.h"

#define get_local() c_base_entity::instance(ints.engine_client->get_local_player())->as<c_ddd_player*>()
#define get_entity(n) c_base_entity::instance(n)
#define get_entity_from_handle(h) ints.entity_list->get_client_entity_from_handle(h)

#define tick_interval     (ints.global_vars->interval_per_tick)
#define time_to_ticks(dt) ((0.5f + static_cast<float>(dt)) / tick_interval);
#define ticks_to_time(t)  (tick_interval * static_cast<float>(t))