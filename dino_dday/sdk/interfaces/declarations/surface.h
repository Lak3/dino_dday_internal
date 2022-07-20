#pragma once

#include "prediction.h"

typedef unsigned long hfont;
constexpr hfont invalid_font = 0;

enum font_draw_type_t {
	font_draw_default = 0,
	font_draw_non_additive,
	font_draw_additive,
	font_draw_type_count = 2
};

enum font_flag_t {
	fontflag_none,
	fontflag_italic = 0x001,
	fontflag_underline = 0x002,
	fontflag_strikeout = 0x004,
	fontflag_symbol = 0x008,
	fontflag_antialias = 0x010,
	fontflag_gaussianblur = 0x020,
	fontflag_rotary = 0x040,
	fontflag_dropshadow = 0x080,
	fontflag_additive = 0x100,
	fontflag_outline = 0x200,
	fontflag_custom = 0x400,
	fontflag_bitmap = 0x800
};

class c_vgui_surface {
public:
	__inline void draw_set_color(const color clr) {
		util.vfunc->get<void(__thiscall*)(c_vgui_surface*, color)>(this, 13u)(this, clr);
	}

	__inline void draw_filled_rect(const int x, const int y, const int w, const int h) {
		util.vfunc->get<void(__thiscall*)(c_vgui_surface*, int, int, int, int)>(this, 15u)(this, x, y, (x + w), (y + h));
	}

	__inline void draw_outlined_rect(const int x, const int y, const int w, const int h) {
		util.vfunc->get<void(__thiscall*)(c_vgui_surface*, int, int, int, int)>(this, 17u)(this, x, y, (x + w), (y + h));
	}

	__inline void draw_line(const int x0, const int y0, const int x1, const int y1) {
		util.vfunc->get<void(__thiscall*)(c_vgui_surface*, int, int, int, int)>(this, 18u)(this, x0, y0, x1, y1);
	}

	__inline void draw_set_text_font(const hfont fnt) {
		util.vfunc->get<void(__thiscall*)(c_vgui_surface*, hfont)>(this, 22u)(this, fnt);
	}

	__inline void draw_set_text_color(const color clr) {
		util.vfunc->get<void(__thiscall*)(c_vgui_surface*, color)>(this, 23u)(this, clr);
	}

	__inline void draw_set_text_pos(const int x, const int y) {
		util.vfunc->get<void(__thiscall*)(c_vgui_surface*, int, int)>(this, 25u)(this, x, y);
	}

	__inline void draw_print_text(const wchar_t* const str, const int len, const font_draw_type_t type = font_draw_default) {
		util.vfunc->get<void(__thiscall*)(c_vgui_surface*, const wchar_t*, int, font_draw_type_t)>(this, 27u)(this, str, len, type);
	}

	//does this fucking shit even exist?????
	__inline void set_cursor_always_visible(const bool state) {
		util.vfunc->get<void(__thiscall*)(c_vgui_surface*, bool)>(this, 55u)(this, state);
	}

	__inline bool is_within(const int x, const int y) {
		return util.vfunc->get<bool(__thiscall*)(c_vgui_surface*, int, int)>(this, 60u)(this, x, y);
	}

	__inline void unlock_cursor() {
		util.vfunc->get<void(__thiscall*)(c_vgui_surface*)>(this, 64u)(this);
	}

	__inline void lock_cursor() {
		util.vfunc->get<void(__thiscall*)(c_vgui_surface*)>(this, 65u)(this);
	}

	__inline hfont create_font() {
		return util.vfunc->get<hfont(__thiscall*)(c_vgui_surface*)>(this, 69u)(this);
	}

	__inline bool set_font_glyph_set(const hfont fnt, const char* const name, const int tall, const int weight, const int blur, const int scanlines, const int flags, const int rangemin = 0, const int rangemax = 0) {
		return util.vfunc->get<bool(__thiscall*)(c_vgui_surface*, hfont, const char*, int, int, int, int, int, int, int)>(this, 70u)(this, fnt, name, tall, weight, blur, scanlines, flags, rangemin, rangemax);
	}

	__inline void get_text_size(const hfont fnt, const wchar_t* const str, int& w, int& h) {
		util.vfunc->get<void(__thiscall*)(c_vgui_surface*, hfont, const wchar_t*, int&, int&)>(this, 77u)(this, fnt, str, w, h);
	}

	__inline void get_cursor_position(int& x, int& y) {
		util.vfunc->get<void(__thiscall*)(c_vgui_surface*, int&, int&)>(this, 98u)(this, x, y);
	}

	__inline void set_alpha_multiplier(const float alpha) {
		util.vfunc->get<void(__thiscall*)(c_vgui_surface*, float)>(this, 111u)(this, alpha);
	}

	__inline float get_alpha_multiplier() {
		return util.vfunc->get<float(__thiscall*)(c_vgui_surface*)>(this, 112u)(this);
	}

public:
	__inline void start_drawing() {
		reinterpret_cast<void(__thiscall*)(c_vgui_surface*)>(util.offsets->m_start_drawing)(this);
	}

	__inline void finish_drawing() {
		reinterpret_cast<void(__thiscall*)(c_vgui_surface*)>(util.offsets->m_finish_drawing)(this);
	}
};