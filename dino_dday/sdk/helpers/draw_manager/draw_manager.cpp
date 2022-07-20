#include "draw_manager.h"

c_draw_manager::c_draw_manager() {
	m_screen_h = 0;
	m_screen_w = 0;
	m_initialized_once = false;

	m_fonts.clear();
}

c_draw_manager::~c_draw_manager() {
	m_screen_h = 0;
	m_screen_w = 0;
	m_initialized_once = false;

	m_fonts.clear();
}

bool c_draw_manager::initialize() {
	m_screen_w = ints.base_client->get_screen_width();
	m_screen_h = ints.base_client->get_screen_height();

	//only init the map once, after that when we call this from screensize changed just create new fonts and set glyph sets.
	if (!m_initialized_once) {
		m_fonts[font_debug]       = { "Consolas", 16, 0,    fontflag_outline };
		m_fonts[font_esp]         = { "Tahoma",   11, 0,    fontflag_outline };
		m_fonts[font_esp_name]    = { "Arial",    14, 0,    fontflag_outline };
		m_fonts[font_esp_pickups] = { "Verdana",  14, 400, (fontflag_dropshadow | fontflag_antialias) };
		m_fonts[font_esp_weapon]  = { "Verdana",  12, 0,    fontflag_outline };
		m_fonts[font_tahoma]      = { "Tahoma",   12, 0,    fontflag_outline };
		m_fonts[font_consolas]    = { "Consolas", 12, 0,    fontflag_outline };
		m_fonts[font_verdana]     = { "Verdana",  12, 0,    fontflag_outline };
		m_fonts[font_arial]       = { "Arial",    12, 0,    fontflag_outline };

		m_initialized_once = true;
	}

	for (std::pair<const fonts_t, font_t>& f : m_fonts) {
		if (!ints.surface->set_font_glyph_set(f.second.m_font = ints.surface->create_font(), f.second.m_name, f.second.m_tall, f.second.m_weight, 0, 0, f.second.m_flags))
			return false;
	}

	console_msg("c_draw_manager::initialize() finished successfully.\n");
	return true;
}

void c_draw_manager::string(const fonts_t fnt, int x, int y, const color clr, const short align, const char* const str, ...) {
	va_list valist;
	char    cbuff[1024]  = { '\0' };
	wchar_t wsbuff[1024] = { '\0' };

	va_start(valist, str);
	vsprintf_s(cbuff, str, valist);
	va_end(valist);

	wsprintfW(wsbuff, L"%hs", cbuff);

	const hfont font = m_fonts[fnt].m_font;

	if (align) {
		int w = 0, h = 0;
		ints.surface->get_text_size(font, wsbuff, w, h);

		if (align & txt_left)
			x -= w;

		if (align & txt_top)
			y -= h;

		if (align & txt_centerx)
			x -= (w / 2);

		if (align & txt_centery)
			y -= (h / 2);
	}

	ints.surface->draw_set_text_pos(x, y);
	ints.surface->draw_set_text_font(font);
	ints.surface->draw_set_text_color(clr);
	ints.surface->draw_print_text(wsbuff, ::wcslen(wsbuff));
}

void c_draw_manager::string(const fonts_t fnt, int x, int y, const color clr, const short align, const wchar_t* const str, ...) {
	va_list valist;
	wchar_t wsbuff[1024] = { '\0' };

	va_start(valist, str);
	vswprintf_s(wsbuff, str, valist);
	va_end(valist);

	const hfont font = m_fonts[fnt].m_font;

	if (align) {
		int w = 0, h = 0;
		ints.surface->get_text_size(font, wsbuff, w, h);

		if (align & txt_left)
			x -= w;

		if (align & txt_top)
			y -= h;

		if (align & txt_centerx)
			x -= (w / 2);

		if (align & txt_centery)
			y -= (h / 2);
	}

	ints.surface->draw_set_text_pos(x, y);
	ints.surface->draw_set_text_font(font);
	ints.surface->draw_set_text_color(clr);
	ints.surface->draw_print_text(wsbuff, ::wcslen(wsbuff));
}

void c_draw_manager::line(const int x, const int y, const int x1, const int y1, const color clr) {
	ints.surface->draw_set_color(clr);
	ints.surface->draw_line(x, y, x1, y1);
}

void c_draw_manager::rect(const int x, const int y, const int w, const int h, const color clr) {
	ints.surface->draw_set_color(clr);
	ints.surface->draw_filled_rect(x, y, w, h);
}

void c_draw_manager::outlined_rect(const int x, const int y, const int w, const int h, const color clr) {
	ints.surface->draw_set_color(clr);
	ints.surface->draw_outlined_rect(x, y, w, h);
}

int c_draw_manager::get_font_height(const fonts_t fnt) const {
	return m_fonts.at(fnt).m_tall;
}

bool c_draw_manager::w2s(const vector wpos, screen_t& s) {
	const matrix3x4_t& ws = ints.engine_client->world_to_screen_matrix();

	const float w = (ws[3][0] * wpos.x + ws[3][1] * wpos.y + ws[3][2] * wpos.z + ws[3][3]);

	if (w > 0.001f) {
		const float flsw   = static_cast<float>(m_screen_w);
		const float flsh   = static_cast<float>(m_screen_h);
		const float fl1dbw = (1.0f / w);

		s.x = static_cast<int>((flsw / 2.0f) + (0.5f * ((ws[0][0] * wpos.x + ws[0][1] * wpos.y + ws[0][2] * wpos.z + ws[0][3]) * fl1dbw) * flsw + 0.5f));
		s.y = static_cast<int>((flsh / 2.0f) - (0.5f * ((ws[1][0] * wpos.x + ws[1][1] * wpos.y + ws[1][2] * wpos.z + ws[1][3]) * fl1dbw) * flsh + 0.5f));
	
		return true;
	}

	return false;
}

bool c_draw_manager::w2s(const vector wpos, vector2d& s) {
	const matrix3x4_t& ws = ints.engine_client->world_to_screen_matrix();

	const float w = (ws[3][0] * wpos.x + ws[3][1] * wpos.y + ws[3][2] * wpos.z + ws[3][3]);

	if (w > 0.001f) {
		const float flsw = static_cast<float>(m_screen_w);
		const float flsh = static_cast<float>(m_screen_h);
		const float fl1dbw = (1.0f / w);

		s.x = ((flsw / 2.0f) + (0.5f * ((ws[0][0] * wpos.x + ws[0][1] * wpos.y + ws[0][2] * wpos.z + ws[0][3]) * fl1dbw) * flsw + 0.5f));
		s.y = ((flsh / 2.0f) - (0.5f * ((ws[1][0] * wpos.x + ws[1][1] * wpos.y + ws[1][2] * wpos.z + ws[1][3]) * fl1dbw) * flsh + 0.5f));

		return true;
	}

	return false;
}

int c_draw_manager::screen_width() const {
	return m_screen_w;
}

int c_draw_manager::screen_height() const {
	return m_screen_h;
}