#include "esp.h"

c_esp::c_esp() {
	m_ammo_crate_axis   = 0;
	m_ammo_crate_allies = 0;
	m_goat              = 0;
	
	m_ammo.clear();
	m_health.clear();
}

c_esp::~c_esp() {
	m_ammo_crate_axis   = 0;
	m_ammo_crate_allies = 0;
	m_goat              = 0;

	m_ammo.clear();
	m_health.clear();
}

void c_esp::think() {
	if (!helpers.cvar->m_esp_enabled.get()  ||
		!ints.engine_client->is_in_game()   ||
		!ints.engine_client->is_connected() ||
		ints.engine_vgui->is_game_ui_visible())
		return;

	const int local_index  = ints.engine_client->get_local_player();

	c_ddd_player* local_player = get_entity(local_index)->as<c_ddd_player*>();

	if (!local_player)
		return;

	int n, x, y, w, h;
	const int max_clients  = (ints.engine_client->get_max_clients() + 1);
	const int max_entities = ints.entity_list->get_highest_entity_index();

	screen_t s       = { };
	player_info_t pi = { };

	if (helpers.cvar->m_core_debug.get()) {
		for (n = 1; n < max_entities; n++) {
			c_base_entity* ent = get_entity(n);

			if (!ent || ent->is_dormant())
				continue;

			client_class* cc = ent->get_client_class();

			if (!cc)
				continue;

			if (!helpers.draw->w2s(ent->get_origin(), s))
				continue;

			helpers.draw->string(font_debug, s.x, s.y, color_grey, txt_centerxy, "%s: %i", cc->get_name(), cc->get_class_id());
			s.y += helpers.draw->get_font_height(font_debug);

			const model_t* model = ent->get_model();

			if (!model)
				continue;

			helpers.draw->string(font_debug, s.x, s.y, color_grey, txt_centerxy, ints.model_info->get_model_name(model));
			s.y += helpers.draw->get_font_height(font_debug);
		}

		if (!local_player->get_deadflag()) {
			for (int n = 0; n < local_player->get_hitbox_count(); n++) {
				vector pos;
				if (local_player->get_hitbox_position(n, pos) && helpers.draw->w2s(pos, s))
					helpers.draw->string(font_debug, s.x, s.y, color_white, txt_centerxy, L"%i", n);
			}
		}

		return;
	}

	//store old alpha, set custom alpha
	const float old_alpha = ints.surface->get_alpha_multiplier();
	ints.surface->set_alpha_multiplier(helpers.cvar->m_esp_alpha.get());

	//other than player entities.
	for (n = max_clients; n < max_entities; n++) {
		c_base_entity* ent = get_entity(n);

		if (!ent || ent->is_dormant())
			continue;

		client_class* cc = ent->get_client_class();

		if (!cc)
			continue;

		switch (cc->get_class_id()) {
			case cbaseanimating: {
				c_base_animating* base_animating = ent->as<c_base_animating*>();

				if (!base_animating)
					break;

				const int model_index = base_animating->get_model_index();

				if (is_ammo(model_index) && helpers.draw->w2s(base_animating->world_space_center(), s))
					helpers.draw->string(font_esp_pickups, s.x, s.y, color_grey, txt_centerxy, L"ammo");
				else if (is_health(model_index) && helpers.draw->w2s(base_animating->world_space_center(), s))
					helpers.draw->string(font_esp_pickups, s.x, s.y, color_green, txt_centerxy, L"health");

				break;
			}
			case cdynamicprop: {
				c_base_animating* base_animating = ent->as<c_base_animating*>();
			
				if (!base_animating)
					break;

				const int model_index = base_animating->get_model_index();

				if ((model_index == m_ammo_crate_allies) && helpers.draw->w2s(base_animating->world_space_center(), s))
					helpers.draw->string(font_esp_pickups, s.x, s.y, color_grey, txt_centerxy, L"allies_ammo_crate");
				else if ((model_index == m_ammo_crate_axis) && helpers.draw->w2s(base_animating->world_space_center(), s))
					helpers.draw->string(font_esp_pickups, s.x, s.y, color_grey, txt_centerxy, L"axis_ammo_crate");

				break;
			}
			case cai_basenpc: {
				c_base_animating* base_animating = ent->as<c_base_animating*>();

				if (!base_animating)
					break;

				if ((base_animating->get_model_index() == m_goat) && helpers.draw->w2s(base_animating->world_space_center(), s))
					helpers.draw->string(font_esp_name, s.x, s.y, color_white, txt_centerxy, L"*MOTHERFUCKING GOAT*");

				break;
			}
			default:
				break;
		}
	}

	//player entitites, render after world so they draw on top of pickups etc.
	const int local_team = local_player->get_team_num();
	for (n = 1; n < max_clients; n++) {
		if (n == local_index)
			continue;

		c_base_entity* ent = get_entity(n);

		if (!ent || ent->is_dormant())
			continue;

		c_ddd_player* player = ent->as<c_ddd_player*>();

		if (!player || player->get_deadflag())
			continue;

		const int team_num = player->get_team_num();

		if ((helpers.cvar->m_esp_ignore_team.get() && (team_num == local_team)) || !get_dynamic_bounds(player, x, y, w, h))
			continue;

		const int health     = player->get_health();
		const int max_health = player->get_max_health();

		const color clr_render = get_team_color(team_num);
		const color clr_health = get_health_color(health, max_health);

		if (helpers.cvar->m_esp_box.get()) {
			helpers.draw->outlined_rect(x, y, w, h, clr_render);
			helpers.draw->outlined_rect((x - 1), (y - 1), (w + 2), (h + 2), color_black);
			helpers.draw->outlined_rect((x + 1), (y + 1), (w - 2), (h - 2), color_black);
		}

		if (helpers.cvar->m_esp_name.get() && ints.engine_client->get_player_info(n, &pi)) {
			std::wstring player_name = convert_utf8_to_wide(pi.name);

			std::transform(player_name.begin(), player_name.end(), player_name.begin(),
				[](wchar_t c) { return ::towlower(c); });

			helpers.draw->string(font_esp_name,
				x + (w / 2),
				y - (helpers.draw->get_font_height(font_esp_name) + 2),
				color_white,
				txt_centerx,
				player_name.c_str());
		}

		const int draw_x = (x + (w + 3));
		int draw_y = y;

		if ((helpers.cvar->m_esp_health.get() == 1) || (helpers.cvar->m_esp_health.get() == 3)) {
			helpers.draw->string(font_esp, draw_x, draw_y, clr_health, txt_default, L"%i/%i", health, max_health);
			draw_y += helpers.draw->get_font_height(font_esp);
		}

		if (helpers.cvar->m_esp_conditions.get()) {
			if (player->get_is_invulnerable()) {
				helpers.draw->string(font_esp, draw_x, draw_y, color_yellow, txt_default, L"invulnerable");
				draw_y += helpers.draw->get_font_height(font_esp);
			}

			if (player->get_is_baited()) {
				helpers.draw->string(font_esp, draw_x, draw_y, color_yellow, txt_default, L"baited");
				draw_y += helpers.draw->get_font_height(font_esp);
			}

			if (player->get_is_being_healed()) {
				helpers.draw->string(font_esp, draw_x, draw_y, color_yellow, txt_default, L"being healed");
				draw_y += helpers.draw->get_font_height(font_esp);
			}

			if (player->get_is_berserk()) {
				helpers.draw->string(font_esp, draw_x, draw_y, color_yellow, txt_default, L"berserk");
				draw_y += helpers.draw->get_font_height(font_esp);
			}

			if (player->get_is_capturing()) {
				helpers.draw->string(font_esp, draw_x, draw_y, color_yellow, txt_default, L"capturing");
				draw_y += helpers.draw->get_font_height(font_esp);
			}

			if (player->get_is_carrying_satchel()) {
				helpers.draw->string(font_esp, draw_x, draw_y, color_yellow, txt_default, L"carrying satchel");
				draw_y += helpers.draw->get_font_height(font_esp);
			}

			if (player->get_is_defusing_satchel()) {
				helpers.draw->string(font_esp, draw_x, draw_y, color_yellow, txt_default, L"defusing satchel");
				draw_y += helpers.draw->get_font_height(font_esp);
			}

			if (player->get_is_feeding()) {
				helpers.draw->string(font_esp, draw_x, draw_y, color_yellow, txt_default, L"feeding");
				draw_y += helpers.draw->get_font_height(font_esp);
			}

			if (player->get_is_healer()) {
				helpers.draw->string(font_esp, draw_x, draw_y, color_yellow, txt_default, L"healer");
				draw_y += helpers.draw->get_font_height(font_esp);
			}

			if (player->get_is_healing()) {
				helpers.draw->string(font_esp, draw_x, draw_y, color_yellow, txt_default, L"healing");
				draw_y += helpers.draw->get_font_height(font_esp);
			}

			if (player->get_is_legendary()) {
				helpers.draw->string(font_esp, draw_x, draw_y, color_yellow, txt_default, L"legendary");
				draw_y += helpers.draw->get_font_height(font_esp);
			}

			if (player->get_is_ready()) {
				helpers.draw->string(font_esp, draw_x, draw_y, color_yellow, txt_default, L"ready");
				draw_y += helpers.draw->get_font_height(font_esp);
			}

			if (player->get_is_red_baron()) {
				helpers.draw->string(font_esp, draw_x, draw_y, color_yellow, txt_default, L"red baron");
				draw_y += helpers.draw->get_font_height(font_esp);
			}

			if (player->get_is_sprinting()) {
				helpers.draw->string(font_esp, draw_x, draw_y, color_yellow, txt_default, L"sprinting");
				draw_y += helpers.draw->get_font_height(font_esp);
			}

			if (player->get_is_victim()) {
				helpers.draw->string(font_esp, draw_x, draw_y, color_yellow, txt_default, L"victim");
				draw_y += helpers.draw->get_font_height(font_esp);
			}

			if (player->get_poisoned()) {
				helpers.draw->string(font_esp, draw_x, draw_y, color_yellow, txt_default, L"poisoned");
				draw_y += helpers.draw->get_font_height(font_esp);
			}

			if (player->get_poisoning()) {
				helpers.draw->string(font_esp, draw_x, draw_y, color_yellow, txt_default, L"poisoning");
				draw_y += helpers.draw->get_font_height(font_esp);
			}
		}

		if (helpers.cvar->m_esp_active_weapon.get()) {
			c_base_combat_weapon* weapon = get_entity_from_handle(player->get_active_weapon())->as<c_base_combat_weapon*>();

			if (weapon) {
				client_class* cc = weapon->get_client_class();

				if (cc) {
					std::string weapon_name = cc->get_name();

					std::transform(weapon_name.begin(), weapon_name.end(), weapon_name.begin(),
						[](unsigned char c) { return std::tolower(c); });

					helpers.draw->string(font_esp_weapon,
						x + (w / 2),
						y + (h + 2),
						color_grey,
						txt_centerx,
						weapon_name.c_str());
				}
			}
		}

		if (helpers.cvar->m_esp_health.get() > 1) {
			x -= 1;

			const float fl_maxhp = static_cast<float>(max_health);
			const float fl_hp    = util.math->clamp(static_cast<float>(health), 1.0f, fl_maxhp);

			constexpr int bar_w = 2;
			const int height    = (h + ((fl_hp < fl_maxhp) ? 2 : 1));

			const float r = (fl_hp / fl_maxhp);
			helpers.draw->rect(static_cast<int>(((x - bar_w) - 2)), static_cast<int>((y + height - (height * r))), bar_w, static_cast<int>((height* r)), clr_health);
			helpers.draw->outlined_rect(static_cast<int>(((x - bar_w) - 2) - 1), static_cast<int>((y + height - (height * r)) - 1), bar_w + 2, static_cast<int>((height* r) + 1), color_black);

			x += 1;
		}
	}

	//resore original alpha
	ints.surface->set_alpha_multiplier(old_alpha);
}

void c_esp::level_init_post_entity() {
	m_ammo_crate_allies = 0;
	m_ammo_crate_axis   = 0;
	m_goat              = 0;

	//todo: find other ammo pickups
	m_ammo.clear(); {
		m_ammo.push_back(ints.model_info->get_model_index("models/props/ammocan_small.mdl"));
	}

	//todo: find other health pickups
	m_health.clear(); {
		m_health.push_back(ints.model_info->get_model_index("models/props/medkit_large.mdl"));
	}

	m_ammo_crate_allies = ints.model_info->get_model_index("models/props/ammocrate/alliesammocrate.mdl");
	m_ammo_crate_axis   = ints.model_info->get_model_index("models/props/ammocrate/axisammocrate.mdl");
	m_goat              = ints.model_info->get_model_index("models/npcs/animals/goat.mdl");
}

bool c_esp::get_dynamic_bounds(c_base_entity* base_ent, int& x, int& y, int& w, int& h) {
	vector points[8];
	util.math->build_transformed_box(points, base_ent->get_mins(), base_ent->get_maxs(), base_ent->renderable_to_world_transform());

	vector2d flb, brt, blb, frt, frb, brb, blt, flt;

	if (helpers.draw->w2s(points[3], flb) && helpers.draw->w2s(points[5], brt)
		&& helpers.draw->w2s(points[0], blb) && helpers.draw->w2s(points[4], frt)
		&& helpers.draw->w2s(points[2], frb) && helpers.draw->w2s(points[1], brb)
		&& helpers.draw->w2s(points[6], blt) && helpers.draw->w2s(points[7], flt)
		&& helpers.draw->w2s(points[6], blt) && helpers.draw->w2s(points[7], flt))
	{
		const vector2d arr[8] = { flb, brt, blb, frt, frb, brb, blt, flt };

		float left   = flb.x;
		float top    = flb.y;
		float righ   = flb.x;
		float bottom = flb.y;

		for (int n = 1; n < 8; n++)
		{
			if (left > arr[n].x)
				left = arr[n].x;

			if (top < arr[n].y)
				top = arr[n].y;

			if (righ < arr[n].x)
				righ = arr[n].x;

			if (bottom > arr[n].y)
				bottom = arr[n].y;
		}

		x = static_cast<int>(left);
		y = static_cast<int>(bottom);
		w = static_cast<int>((righ - left));
		h = static_cast<int>((top - bottom));

		return !((x > helpers.draw->screen_width()) || ((x + w) < 0) || (y > helpers.draw->screen_height()) || ((y + h) < 0));
	}

	return false;
}

bool c_esp::is_ammo(const int model_index) const {
	static const size_t s_size = m_ammo.size(); //size of this wont change.

	for (size_t n = 0; n < s_size; n++) {
		if (m_ammo.at(n) == model_index)
			return true;
	}

	return false;
}

bool c_esp::is_health(const int model_index) const {
	static const size_t s_size = m_health.size(); //size of this wont change.

	for (size_t n = 0; n < s_size; n++) {
		if (m_health.at(n) == model_index)
			return true;
	}

	return false;
}

std::wstring c_esp::convert_utf8_to_wide(const std::string str) const {
	const int n = MultiByteToWideChar(65001, 0, str.data(), str.length(), 0, 0);

	std::wstring s(n, 0);
	MultiByteToWideChar(65001, 0, str.data(), str.length(), &s[0], n);

	return s;
}

color c_esp::get_health_color(const int health, const int max_health) {
	if (health > max_health)
		return { 15, 150, 150 };

	const int hp = util.math->max(0, util.math->min(health, max_health));

	return {
		static_cast<unsigned char>(util.math->min((510 * (max_health - hp)) / max_health, 200)),
		static_cast<unsigned char>(util.math->min((510 * hp) / max_health, 200)),
		0
	};
}

color c_esp::get_team_color(const int team_num) {
	if (team_num == 3)
		return { 150, 150, 15 };

	if (team_num == 2)
		return { 15, 150, 150 };

	return color_white;
}