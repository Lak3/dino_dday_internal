#pragma once

#include "base_animating.h"

class c_base_combat_character : public c_base_flex {
public:
	__inline bool can_attack() const {
		return (ints.global_vars->curtime >= get_next_attack());
	}

public:
	m_netvar(get_next_attack, float, "CBaseCombatCharacter", "m_flNextAttack");
	m_netvar(get_my_weapons, void*, "CBaseCombatCharacter", "m_hMyWeapons");
	m_netvar(get_active_weapon, unsigned long, "CBaseCombatCharacter", "m_hActiveWeapon");
};