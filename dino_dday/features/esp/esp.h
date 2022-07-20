#pragma once

#include "../engine_prediction/engine_prediction.h"

class c_esp {
public:
	c_esp();
	~c_esp();

public:
	void think();
	void level_init_post_entity();

private:
	bool get_dynamic_bounds(c_base_entity* base_ent, int& x, int& y, int& w, int& h);
	bool is_ammo(const int model_index) const;
	bool is_health(const int model_index) const;

	std::wstring convert_utf8_to_wide(const std::string str) const;
	color get_health_color(const int health, const int max_health);
	color get_team_color(const int team_num);

private:
	int m_ammo_crate_axis   = 0;
	int m_ammo_crate_allies = 0;
	int m_goat              = 0;

	std::vector<int> m_ammo   = { };
	std::vector<int> m_health = { };
};