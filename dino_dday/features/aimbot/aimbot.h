#pragma once

#include "../../sdk/sdk.h"

class c_aimbot {
public:
	c_aimbot();
	~c_aimbot();

public:
	void think(c_user_cmd* cmd);

private:
	enum targettype_t {
		target_unknown = -1,
		target_player,
		target_other
	};

	struct target_t {
		c_base_entity* m_entity = nullptr;
		targettype_t m_type     = target_unknown;
		vector m_position       = { };
		vector m_angle          = { };
		float m_distance        = 0.0f;
		float m_fov             = 0.0f;
	};

	struct hitbox_t {
		int m_special_class         = -1;
		int m_hitbox                = -1;
		unsigned long m_hashed_name = 0u;
	};

private:
	void fix_movement(const vector ang, c_user_cmd* cmd);
	void set_angles(c_weapon_ddd_base* local_weapon, c_user_cmd* cmd, const target_t target);

	bool get_target(c_ddd_player* local_player, c_user_cmd* cmd, target_t& out);
	bool is_point_visible(const vector from, const vector to);
	bool get_hitbox_position_by_name(c_ddd_player* player, const char* const name, vector& out);
	bool should_auto_pistol(c_weapon_ddd_base* local_weapon);

private:
	std::vector<target_t> m_targets     = { };
	std::vector<hitbox_t> m_hitboxes    = { };
};