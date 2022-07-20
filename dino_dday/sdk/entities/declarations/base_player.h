#pragma once

#include "base_combat_character.h"

class c_base_player : public c_base_combat_character {
public:
	__inline void set_punch_angle(const vector v) {
		static const int s_off = helpers.netvar->get("CBasePlayer", "m_vecPunchAngle");
		*reinterpret_cast<vector*>(reinterpret_cast<unsigned long>(this) + s_off) = v;
	}

	__inline void set_tick_base(const int tick_base) {
		static const int s_off = helpers.netvar->get("CBasePlayer", "m_nTickBase");
		*reinterpret_cast<int*>(reinterpret_cast<unsigned long>(this) + s_off) = tick_base;
	}

	__inline void set_flags(const int flags) {
		static const int s_off = helpers.netvar->get("CBasePlayer", "m_fFlags");
		*reinterpret_cast<int*>(reinterpret_cast<unsigned long>(this) + s_off) = flags;
	}

	__inline void update_button_state(const int mask) {
		reinterpret_cast<void(__thiscall*)(c_base_player*, int)>(util.offsets->m_update_button_state)(this, mask);
	}

	__inline void set_current_command(c_user_cmd* cmd) {
		static const int s_off = (helpers.netvar->get("CBasePlayer", "m_hConstraintEntity") - 12);
		*reinterpret_cast<c_user_cmd**>(reinterpret_cast<unsigned long>(this) + s_off) = cmd;
	}

public:
	m_netvar(get_ducked, bool, "CBasePlayer", "m_bDucked");
	m_netvar(get_ducking, bool, "CBasePlayer", "m_bDucking");
	m_netvar(get_fall_velocity, float, "CBasePlayer", "m_flFallVelocity");
	m_netvar(get_punch_angle, vector, "CBasePlayer", "m_vecPunchAngle");
	m_netvar(get_punch_angle_vel, vector, "CBasePlayer", "m_vecPunchAngleVel");
	m_netvar(get_view_offset, vector, "CBasePlayer", "m_vecViewOffset[0]");
	m_netvar(get_tick_base, int, "CBasePlayer", "m_nTickBase");
	m_netvar(get_velocity, vector, "CBasePlayer", "m_vecVelocity[0]");
	m_netvar(get_base_velocity, vector, "CBasePlayer", "m_vecBaseVelocity");
	m_netvar(get_constraint_entity, unsigned long, "CBasePlayer", "m_hConstraintEntity");
	m_netvar(get_constraint_center, vector, "CBasePlayer", "m_vecConstraintCenter");
	m_netvar(get_constraint_radius, float, "CBasePlayer", "m_flConstraintRadius");
	m_netvar(get_constraint_width, float, "CBasePlayer", "m_flConstraintWidth");
	m_netvar(get_constraint_speed_factor, float, "CBasePlayer", "m_flConstraintSpeedFactor");
	m_netvar(get_constraint_past_radius, bool, "CBasePlayer", "m_bConstraintPastRadius");
	m_netvar(get_water_level, unsigned char, "CBasePlayer", "m_nWaterLevel");
	m_netvar(get_deadflag, int, "CBasePlayer", "deadflag");
	m_netvar(get_use_entity, unsigned long, "CBasePlayer", "m_hUseEntity");
	m_netvar(get_ground_entity, unsigned long, "CBasePlayer", "m_hGroundEntity");
	m_netvar(get_health, int, "CBasePlayer", "m_iHealth");
	m_netvar(get_max_health, int, "CBasePlayer", "m_iMaxHealth");
	m_netvar(get_life_state, unsigned char, "CBasePlayer", "m_lifeState");
	m_netvar(get_max_speed, float, "CBasePlayer", "m_flMaxspeed");
	m_netvar(get_flags, int, "CBasePlayer", "m_fFlags");
	m_netvar(get_observer_mode, int, "CBasePlayer", "m_iObserverMode");
	m_netvar(get_observer_target, unsigned long, "CBasePlayer", "m_hObserverTarget");
	m_netvar(get_ladder_normal, vector, "CBasePlayer", "m_vecLadderNormal");
};