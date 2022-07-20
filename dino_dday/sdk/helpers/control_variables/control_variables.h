#pragma once

#include "../../interfaces/interfaces.h"

template<typename t> 
class c_var {
public:
	c_var(const t v, const wchar_t* const name) {
		m_var = v;
		m_name = name;
	}

	c_var(const t v, const t step, const t min, const t max, const wchar_t* const name) {
		m_var  = v;
		m_step = step;
		m_min  = min;
		m_max  = max;
		m_name = name;
	}

public:
	__inline t get() const {
		return m_var;
	}
	
	__inline void set(const t v) {
		m_var = v;
	}

	__inline const wchar_t* get_name() const {
		return m_name;
	}

	__inline t get_step() const {
		return m_step;
	}

	__inline t get_min() const {
		return m_min;
	}

	__inline t get_max() const {
		return m_max;
	}

private:
	t m_var  = { };
	t m_min  = { };
	t m_max  = { };
	t m_step = { };

	const wchar_t* m_name = L"";
};

class c_control_variables {
public:
	void save();
	void load();

public:
	c_var<bool> m_aimbot_enabled     = { true, L"aimbot_enabled" };
	c_var<float> m_aimbot_fov        = { 60.0f, 1.0f, 1.0f, 180.0f, L"aimbot_fov" };
	c_var<int> m_aimbot_key          = { 6, L"aimbot_key" };
	c_var<bool> m_aimbot_ignore_team = { true, L"aimbot_ignore_team" };
	c_var<int> m_aimbot_mode         = { 2, L"aimbot_mode" }; //0 - plain, 1 - smooth, 2 - silent
	c_var<float> m_aimbot_smooth     = { 5.0f, 0.1f, 1.0f, 15.0f, L"aimbot_smooth" };
	c_var<int> m_aimbot_priority     = { 0, L"aimbot_priority" }; //0 - closest to crosshair, 1 - smallest distance
	c_var<bool> m_aimbot_hitscan     = { true, L"aimbot_hitscan" };
	c_var<int> m_aimbot_position     = { 0, L"aimbot_position" }; //0 - head, 1 - body
	c_var<bool> m_aimbot_auto_shoot  = { true, L"aimbot_auto_shoot" };

	c_var<bool> m_esp_enabled       = { true, L"esp_enabled" };
	c_var<bool> m_esp_ignore_team   = { false, L"esp_ignore_team" };
	c_var<bool> m_esp_name          = { true, L"esp_name" };
	c_var<bool> m_esp_box           = { true, L"esp_box" };
	c_var<bool> m_esp_active_weapon = { true, L"esp_active_weapon" };
	c_var<bool> m_esp_conditions    = { true, L"esp_conditions" };
	c_var<int> m_esp_health         = { 3, L"esp_health" }; //0 - off, 1 - text, 2 - bar, 3 - both
	c_var<bool> m_esp_world         = { true, L"esp_world_world" };
	c_var<float> m_esp_alpha        = { 1.0f, 0.1f, 0.1f, 1.0f, L"esp_alpha" };

	c_var<bool> m_misc_bhop          = { true, L"misc_bunnyhop" };
	c_var<bool> m_misc_nospread      = { true, L"misc_nospread" };
	c_var<bool> m_misc_norecoil      = { true, L"misc_norecoil" };
	c_var<int> m_misc_speed_key      = { 5, L"misc_speed_key" };
	c_var<int> m_misc_speed_amount   = { 5, 1, 1, 13, L"misc_speed_amount" };
	c_var<bool> m_misc_novis_recoil  = { true, L"misc_no_visual_recoil" };
	c_var<bool> m_misc_setinfo_null  = { false, L"misc_null_setinfo" };

	c_var<bool> m_core_debug    = { false, L"core_debug" };
};