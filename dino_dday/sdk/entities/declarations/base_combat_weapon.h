#pragma once

#include "ddd_player.h"

class c_base_combat_weapon : public c_base_animating {
public:
	__inline bool can_primary_attack() const {
		return (get_next_primary_attack() <= ints.global_vars->curtime);
	}

	__inline bool can_secondary_attack() const {
		return (get_next_secondary_attack() <= ints.global_vars->curtime);
	}

public:
	m_netvar(get_primary_ammo_type, int, "CBaseCombatWeapon", "m_iPrimaryAmmoType");
	m_netvar(get_secondary_ammo_type, int, "CBaseCombatWeapon", "m_iSecondaryAmmoType");
	m_netvar(get_next_primary_attack, float, "CBaseCombatWeapon", "m_flNextPrimaryAttack");
	m_netvar(get_next_secondary_attack, float, "CBaseCombatWeapon", "m_flNextSecondaryAttack");
	m_netvar(get_state, int, "CBaseCombatWeapon", "m_iState");
	m_netvar(get_owner, unsigned long, "CBaseCombatWeapon", "m_hOwner");
};