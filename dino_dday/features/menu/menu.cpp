#include "menu.h"

c_menu::c_menu() {
	m_menu_x = 190;
	m_menu_y = 201;
	m_item_x = 0;
	m_item_y = 0;
	m_open   = false;
	m_drag   = false;

	m_aimbot_modes      = { L"plain", L"smooth", L"silent" };
	m_aimbot_priorities = { L"closest to crosshair", L"smallest distance" };
	m_health_items      = { L"off", L"text", L"bar", L"both" };
	m_aimbot_positions  = { L"head", L"body" };
}

c_menu::~c_menu() {
	m_menu_x = 0;
	m_menu_y = 0;
	m_item_x = 0;
	m_item_y = 0;
	m_open   = false;
	m_drag   = false;

	m_aimbot_modes.clear();
	m_aimbot_priorities.clear();
	m_health_items.clear();
	m_aimbot_positions.clear();

	for (size_t n = 0; n < m_items.size(); n++)
		m_items[n].reset();

	m_items.clear();
}

void c_menu::initialize() {
	add_item(&helpers.cvar->m_aimbot_enabled, item_bool);
	add_item(&helpers.cvar->m_aimbot_ignore_team, item_bool);
	add_item(&helpers.cvar->m_aimbot_key, item_key);
	add_item(&helpers.cvar->m_aimbot_position, item_enum, &m_aimbot_positions);
	add_item(&helpers.cvar->m_aimbot_fov, item_float);
	add_item(&helpers.cvar->m_aimbot_mode, item_enum, &m_aimbot_modes);
	add_item(&helpers.cvar->m_aimbot_priority, item_enum, &m_aimbot_priorities);
	add_item(&helpers.cvar->m_aimbot_smooth, item_float_hp);
	add_item(&helpers.cvar->m_aimbot_hitscan, item_bool);

	add_item(&helpers.cvar->m_esp_enabled, item_bool);
	add_item(&helpers.cvar->m_esp_ignore_team, item_bool);
	add_item(&helpers.cvar->m_esp_name, item_bool);
	add_item(&helpers.cvar->m_esp_box, item_bool);
	add_item(&helpers.cvar->m_esp_conditions, item_bool);
	add_item(&helpers.cvar->m_esp_active_weapon, item_bool);
	add_item(&helpers.cvar->m_esp_health, item_enum, &m_health_items);
	add_item(&helpers.cvar->m_esp_alpha, item_float_hp);

	add_item(&helpers.cvar->m_misc_bhop, item_bool);
	add_item(&helpers.cvar->m_misc_novis_recoil, item_bool);
	add_item(&helpers.cvar->m_misc_norecoil, item_bool);
	add_item(&helpers.cvar->m_misc_nospread, item_bool);
	add_item(&helpers.cvar->m_misc_speed_key, item_key);
	add_item(&helpers.cvar->m_misc_speed_amount, item_int);
	add_item(&helpers.cvar->m_misc_setinfo_null, item_bool);

	add_item(&helpers.cvar->m_core_debug, item_bool);

	console_msg("c_menu::initialize() finished successfully.\n");
}

void c_menu::think() {
	if (helpers.input->is_pressed(45)) {
		if (!(m_open = !m_open)) //menu was closed, save latest settings.
			helpers.cvar->save();
	}

	if (!m_open)
		return;

	static const int item_height    = helpers.draw->get_font_height(font_tahoma);
	static const size_t item_amount = m_items.size();

	handle_drag();

	m_menu_x = util.math->clamp(m_menu_x, 0, (helpers.draw->screen_width() - menu_w));
	m_menu_y = util.math->clamp(m_menu_y, 0, (helpers.draw->screen_height() - (item_height * static_cast<int>(item_amount))));

	m_item_x = (m_menu_x + 2);
	m_item_y = m_menu_y;

	helpers.draw->rect(m_item_x - 2, m_item_y, menu_w, 5, { 15, 150, 150 });
	m_item_y += 5;

	helpers.draw->rect(m_item_x - 2, m_item_y, menu_w, (item_height * static_cast<int>(item_amount)) + 1, { 69, 69, 69, 211 });

	for (size_t n = 0; n < item_amount; n++) {
		m_items[n]->think(m_item_x, m_item_y, m_drag);
		m_items[n]->render(m_item_x, m_item_y);
	}
}

bool c_menu::is_open() const {
	return m_open;
}

void c_menu::add_item(void* var_addr, const itemtype_t type, std::vector<const wchar_t*>* items) {
	m_items.push_back(std::make_unique<c_menu_item>(var_addr, type, items));
}

//idk where this originates from lmao.
void c_menu::handle_drag() {
	static screen_t delta = { };
	static bool s_move    = false;

	const bool is_held    = (helpers.input->is_held(1) || helpers.input->is_held(2));

	if ((helpers.input->cursor_x() > m_menu_x && helpers.input->cursor_x() < m_menu_x + menu_w && helpers.input->cursor_y() > m_menu_y && helpers.input->cursor_y() < m_menu_y + 5) && is_held) {
		m_drag = true;

		if (!s_move) {
			delta.x = (helpers.input->cursor_x() - m_menu_x);
			delta.y = (helpers.input->cursor_y() - m_menu_y);
			s_move  = true;
		}
	}

	if (m_drag) {
		m_menu_x = (helpers.input->cursor_x() - delta.x);
		m_menu_y = (helpers.input->cursor_y() - delta.y);
	}

	if (!is_held) {
		m_drag = false;
		s_move = false;
	}
}