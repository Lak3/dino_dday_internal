#pragma once

#include "client_entity.h"

class c_base_entity : public c_client_entity {
public:
	__inline vector world_space_center() const {
		const vector origin = get_origin();
		return { origin.x, origin.y, (origin.z + ((get_mins().z + get_maxs().z) / 2.0f)) };
	}

	static void set_prediction_random_seed(c_user_cmd* cmd) {
		reinterpret_cast<void(*)(c_user_cmd*)>(util.offsets->m_set_pred_rand_seed)(cmd);
	}

	static c_base_entity* instance(const int idx) {
		return reinterpret_cast<c_base_entity* (*)(int)>(util.offsets->m_instance)(idx);
	}

public:
	m_netvar(get_animtime, float, "CBaseEntity", "m_flAnimTime");
	m_netvar(get_smulation_time, float, "CBaseEntity", "m_flSimulationTime");
	m_netvar(get_origin, vector, "CBaseEntity", "m_vecOrigin");
	m_netvar(get_model_index, int, "CBaseEntity", "m_nModelIndex");
	m_netvar(get_team_num, int, "CBaseEntity", "m_iTeamNum");
	m_netvar(get_collision_group, int, "CBaseEntity", "m_CollisionGroup");
	m_netvar(get_owner_entity, unsigned long, "CBaseEntity", "m_hOwnerEntity");
	m_netvar(get_name, int, "CBaseEntity", "m_iName");
	m_netvar(get_mins, vector, "CBaseEntity", "m_vecMins");
	m_netvar(get_maxs, vector, "CBaseEntity", "m_vecMaxs");
	m_netvar(get_solid_type, int, "CBaseEntity", "m_nSolidType");
	m_netvar(get_solid_flags, unsigned short, "CBaseEntity", "m_usSolidFlags");
};