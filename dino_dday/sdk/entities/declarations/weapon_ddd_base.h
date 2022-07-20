#pragma once

#include "base_combat_weapon.h"

class c_weapon_ddd_base : public c_base_combat_weapon {
public:
	__inline float get_spread() {
		return util.vfunc->get<float(__thiscall*)(void*)>(this, 393u)(this);
	}

public:
	m_netvar(get_decrease_shots_fired, float, "CWeaponDDDBase", "m_flDecreaseShotsFired");
	m_netvar(get_is_sighted, bool, "CWeaponDDDBase", "m_bIsSighted");
	m_netvar(get_enemy_position, int, "CWeaponDDDBase", "m_iEnemyPosition");
	m_netvar(get_holstered, bool, "CWeaponDDDBase", "m_bHolstered");
	m_netvar(get_can_go_out_of_iron_sight, bool, "CWeaponDDDBase", "m_bCanGoOutOfIronsight");
	m_netvar(get_sighted_timer, float, "CWeaponDDDBase", "m_flSightedTimer");
};