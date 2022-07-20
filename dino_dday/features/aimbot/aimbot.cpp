#include "aimbot.h"

c_aimbot::c_aimbot() {
	m_targets.clear();
	m_hitboxes.clear();
}

c_aimbot::~c_aimbot() {
	m_targets.clear();
	m_hitboxes.clear();
}

void c_aimbot::think(c_user_cmd* cmd) {
	if (!helpers.cvar->m_aimbot_enabled.get() || !ints.engine_client->is_connected() || !ints.engine_client->is_in_game())
		return;

	if (helpers.cvar->m_aimbot_key.get() && !helpers.input->is_held(helpers.cvar->m_aimbot_key.get()))
		return;

	c_ddd_player* local_player = get_local();

	if (!local_player || local_player->get_deadflag() || !local_player->can_attack())
		return;

	c_weapon_ddd_base* weapon = get_entity_from_handle(local_player->get_active_weapon())->as<c_weapon_ddd_base*>();

	if (!weapon)
		return;

	target_t target;
	if (!get_target(local_player, cmd, target))
		return;

	set_angles(weapon, cmd, target);

	if (helpers.cvar->m_aimbot_auto_shoot.get()) {
		cmd->buttons |= in_attack;

		if (should_auto_pistol(weapon)) {
			static bool s_flip = false;

			if (s_flip = !s_flip)
				cmd->buttons &= ~in_attack;
		}
	}
}

void c_aimbot::fix_movement(const vector ang, c_user_cmd* cmd) {
	const vector move = { cmd->forwardmove, cmd->sidemove, cmd->upmove };

	vector dir;
	util.math->vector_angles(move, dir);

	const float len = move.length2d();
	const float yaw = deg2radf(ang.y - cmd->viewangles.y + dir.y);
	
	cmd->forwardmove = (::cosf(yaw) * len);
	cmd->sidemove    = (::sinf(yaw) * len);
}

void c_aimbot::set_angles(c_weapon_ddd_base* local_weapon, c_user_cmd* cmd, const target_t target) {
	vector target_angle = util.math->clamp_angles(target.m_angle);

	if (helpers.cvar->m_aimbot_mode.get() == 1) {
		//todo: tj too väbä to write 2 lines of smooth
	}

	if (helpers.cvar->m_aimbot_mode.get() == 2) {
		fix_movement(target_angle, cmd);
	}

	cmd->viewangles = target_angle;

	if (helpers.cvar->m_aimbot_mode.get() < 2) {
		ints.engine_client->set_view_angles(target_angle);
	}
}

bool c_aimbot::get_target(c_ddd_player* local_player, c_user_cmd* cmd, target_t& out) {
	m_targets.clear();

	const int local_team   = local_player->get_team_num();
	const int local_index  = ints.engine_client->get_local_player();
	const int max_clients  = (ints.engine_client->get_max_clients() + 1);

	const vector shoot_pos = (local_player->get_view_offset() + local_player->get_origin());

	for (int n = 1; n < max_clients; n++) {
		if (n == local_index)
			continue;

		c_base_entity* ent = get_entity(n);

		if (!ent || ent->is_dormant())
			continue;

		c_ddd_player* player = ent->as<c_ddd_player*>();

		if (!player || player->get_deadflag() || player->get_is_invulnerable())
			continue;

		if (helpers.cvar->m_aimbot_ignore_team.get() && (player->get_team_num() == local_team))
			continue;

		vector hitbox_pos;
		if (!get_hitbox_position_by_name(player, (helpers.cvar->m_aimbot_position.get() == 0) ? "head" : "pelvis", hitbox_pos))
			continue;

		const vector angle_to = util.math->get_angle_to_pos(shoot_pos, hitbox_pos);

		const float distance = shoot_pos.dist_to(hitbox_pos);
		const float fov      = util.math->get_fov_between(cmd->viewangles, angle_to);

		if ((helpers.cvar->m_aimbot_priority.get() == 0) && (fov > helpers.cvar->m_aimbot_fov.get()))
			continue;

		m_targets.push_back({ player, target_player, hitbox_pos, angle_to, distance, fov });
	}

	if (m_targets.empty())
		return false;

	std::sort(m_targets.begin(), m_targets.end(), [&](const target_t& a, const target_t& b) -> bool {
		return (helpers.cvar->m_aimbot_priority.get() == 0) ? (a.m_fov < b.m_fov) : (a.m_distance < b.m_distance);
	});

	for (target_t& target : m_targets) {
		if (!is_point_visible(shoot_pos, target.m_position)) {
			if (helpers.cvar->m_aimbot_hitscan.get() && (target.m_type == target_player)) {
				c_ddd_player* player = target.m_entity->as<c_ddd_player*>();

				if (!player)
					continue;

				vector new_pos = { };
				bool found_new = false;

				for (int n = 0; n < player->get_hitbox_count(); n++) {
					if (player->get_hitbox_position(n, new_pos) && is_point_visible(shoot_pos, new_pos)) {
						target.m_position = new_pos;
						target.m_angle    = util.math->get_angle_to_pos(shoot_pos, new_pos);

						found_new = true;
						break;
					}
				}

				if (!found_new)
					continue;
			}
			else {
				continue;
			}
		}

		out = target;
		return true;
	}

	return false;
}

bool c_aimbot::is_point_visible(const vector from, const vector to) {
	constexpr unsigned int mask = 1174421515u; //(mask_shot | contents_grate)

	ray_t r                                  = { from, to };
	trace_t tr                               = { };
	c_trace_filter_world_and_props_only fltr = { };

	ints.engine_trace->trace_ray(r, mask, &fltr, &tr);

	return (!tr.did_hit());
}

//smth fucked so hitbox name dont workings idk and idc.
//so, just as a logical real man, instead of fixing anything, we find the hitbox via the bone name.
bool c_aimbot::get_hitbox_position_by_name(c_ddd_player* player, const char* const name, vector& out) {
	const unsigned long name_hash = hash_fnv(name);
	const int player_class        = player->get_special_class();

	int n; const int size = static_cast<int>(m_hitboxes.size());
	for (n = 0; n < size; n++) {
		if ((m_hitboxes[n].m_special_class == player_class) && (m_hitboxes[n].m_hashed_name == name_hash))
			return player->get_hitbox_position(m_hitboxes[n].m_hitbox, out);
	}

	const model_t* mdl = player->get_model();

	if (!mdl)
		return false;

	const studiohdr_t* hdr = ints.model_info->get_studio_model(mdl);

	if (!hdr)
		return false;

	int bone_index = -1;
	for (n = 0; n < hdr->numbones; n++) {
		const mstudiobone_t* bone = hdr->get_bone(n);

		if (bone) {
			std::string bone_name = { bone->get_name() };

			std::transform(bone_name.begin(), bone_name.end(), bone_name.begin(),
				[](unsigned char c) { return std::tolower(c); });

			if (bone_name.find(name) != std::string::npos) {
				bone_index = n;
				break;
			}
		}
	}

	if (bone_index == -1)
		return false;

	const mstudiohitboxset_t* set = hdr->get_hitbox_set(player->get_hitbox_set());

	if (!set)
		return false;

	for (n = 0; n < set->numhitboxes; n++) {
		const mstudiobbox_t* box = set->get_hitbox(n);

		if (box && (box->bone == bone_index) && (box->bone < maxstudiobones) && (box->bone >= 0)) {
			m_hitboxes.push_back({ player_class, n, name_hash });
			break;
		}
	}

	return false; //we cached the hitbox index, but did not get the position of it.
}

bool c_aimbot::should_auto_pistol(c_weapon_ddd_base* local_weapon) {
	client_class* cc = local_weapon->get_client_class();

	if (!cc)
		return false;

	switch (cc->get_class_id()) {
		case cweaponcarbine:
		case cweapongarand:
		case cweaponpistol:
		case cweaponshotgun:
		case cweapontokarev:
		case cweaponmosin:
		case cweaponp38:
		case cweaponk98:
		case cweaponluger:
		case cweaponk98sniper:
			return true;
		default: 
			break;
	}

	return false;
}