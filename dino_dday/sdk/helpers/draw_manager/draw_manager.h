#pragma once

#include "../control_variables/control_variables.h"

#define txt_default		(1 << 0)
#define txt_left		(1 << 1)
#define txt_top			(1 << 2)
#define txt_centerx		(1 << 3)
#define txt_centery		(1 << 4)
#define txt_centerxy	(txt_centerx | txt_centery)

enum fonts_t {
	font_debug = 0,
	font_esp,
	font_esp_name,
	font_esp_weapon,
	font_esp_pickups,
	font_tahoma,
	font_consolas,
	font_verdana,
	font_arial,
	font_max
};

struct screen_t {
public:
	screen_t() {
		x = 0;
		y = 0;
	}

	screen_t(const int _x, const int _y) {
		x = _x;
		y = _y;
	}

public:
	int x;
	int y;
};

class c_draw_manager {
public:
	c_draw_manager();
	~c_draw_manager();

private:
	struct font_t {
		const char* m_name;
		int m_tall;
		int m_weight;
		int m_flags;
		hfont m_font;
	};

public:
	bool initialize();

public:
	void string(const fonts_t fnt, int x, int y, const color clr, const short align, const char* const str, ...);
	void string(const fonts_t fnt, int x, int y, const color clr, const short align, const wchar_t* const str, ...);
	void line(const int x, const int y, const int x1, const int y1, const color clr);
	void rect(const int x, const int y, const int w, const int h, const color clr);
	void outlined_rect(const int x, const int y, const int w, const int h, const color clr);

public:
	int get_font_height(const fonts_t fnt) const;

	bool w2s(const vector wpos, screen_t& s);
	bool w2s(const vector wpos, vector2d& s);

	int screen_width() const;
	int screen_height() const;

private:
	std::map<fonts_t, font_t> m_fonts = { };

	int m_screen_w = 0;
	int m_screen_h = 0;

	bool m_initialized_once = false;
};