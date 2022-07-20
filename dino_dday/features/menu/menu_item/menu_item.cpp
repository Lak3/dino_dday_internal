#include "menu_item.h"

c_menu_item::c_menu_item() {
	m_var_addr = nullptr;
	m_type     = item_none;
	m_items    = nullptr;
}

c_menu_item::c_menu_item(void* addr, const itemtype_t type, std::vector<const wchar_t*>* items) {
	m_var_addr = addr;
	m_type     = type;
	m_items    = items;
}

void c_menu_item::render(int& x, int& y) {
	const color clr = is_hovered(x, y) ? color(15, 150, 150) : color_white;

	switch (m_type) {
		case item_bool: {
			c_var<bool>* var = reinterpret_cast<c_var<bool>*>(m_var_addr);

			helpers.draw->string(font_tahoma, x, y, clr, txt_default, L"%ws:", var->get_name());
			helpers.draw->string(font_tahoma, x + (menu_w - 3), y, clr, txt_left, var->get() ? L"on" : L"off");
			break;
		}
		case item_int: {
			c_var<int>* var = reinterpret_cast<c_var<int>*>(m_var_addr);

			helpers.draw->string(font_tahoma, x, y, clr, txt_default, L"%ws:", var->get_name());
			helpers.draw->string(font_tahoma, x + (menu_w - 3), y, clr, txt_left, L"%i", var->get());
			break;
		}
		case item_enum: {
			c_var<int>* var = reinterpret_cast<c_var<int>*>(m_var_addr);

			helpers.draw->string(font_tahoma, x, y, clr, txt_default, L"%ws:", var->get_name());
			helpers.draw->string(font_tahoma, x + (menu_w - 3), y, clr, txt_left, m_items->at(var->get()));
			break;
		}
		case item_float: {
			c_var<float>* var = reinterpret_cast<c_var<float>*>(m_var_addr);

			helpers.draw->string(font_tahoma, x, y, clr, txt_default, L"%ws:", var->get_name());
			helpers.draw->string(font_tahoma, x + (menu_w - 3), y, clr, txt_left, L"%.1f", var->get());
			break;
		}
		case item_float_hp: {
			c_var<float>* var = reinterpret_cast<c_var<float>*>(m_var_addr);

			helpers.draw->string(font_tahoma, x, y, clr, txt_default, L"%ws:", var->get_name());
			helpers.draw->string(font_tahoma, x + (menu_w - 3), y, clr, txt_left, L"%.4f", var->get());
			break;
		}
		case item_key: {
			c_var<int>* var = reinterpret_cast<c_var<int>*>(m_var_addr);

			helpers.draw->string(font_tahoma, x, y, clr, txt_default, L"%ws:", var->get_name());
			helpers.draw->string(font_tahoma, x + (menu_w - 3), y, clr, txt_left, util_get_vkey_name(var->get()).c_str());
			break;
		}
		default:
			break;
	}

	y += helpers.draw->get_font_height(font_tahoma);
}

void c_menu_item::think(const int x, const int y, const bool dragged) {
	if (is_hovered(x, y) && !dragged) {
		if (m_type == item_key) {
			move_left(); //hackhack...
		}
		else {
			if (helpers.input->is_pressed(1))
				move_left();
			else if (helpers.input->is_pressed(2))
				move_right();
		}
	}
}

void c_menu_item::move_left() {
	switch (m_type) {
		case item_bool: {
			c_var<bool>* var = reinterpret_cast<c_var<bool>*>(m_var_addr);
	
			var->set(!var->get());
			break;
		}
		case item_int: {
			c_var<int>* var = reinterpret_cast<c_var<int>*>(m_var_addr);

			var->set(util.math->clamp((var->get() - var->get_step()), var->get_min(), var->get_max()));
			break;
		}
		case item_enum: {
			c_var<int>* var = reinterpret_cast<c_var<int>*>(m_var_addr);

			var->set(util.math->clamp((var->get() - 1), 0, (static_cast<int>(m_items->size()) - 1)));
			break;
		}
		case item_float:
		case item_float_hp: {
			c_var<float>* var = reinterpret_cast<c_var<float>*>(m_var_addr);

			var->set(util.math->clamp((var->get() - var->get_step()), var->get_min(), var->get_max()));
			break;
		}
		case item_key: {
			int v_key;
			if (helpers.input->is_any_key_pressed(v_key) && (v_key != 45)) //don't allow insert...
				reinterpret_cast<c_var<int>*>(m_var_addr)->set((v_key == 27) ? 0 : v_key); //esc = 0 / none

			break;
		}
		default:
			break;
	}
}

void c_menu_item::move_right() {
	switch (m_type) {
		case item_bool: {
			c_var<bool>* var = reinterpret_cast<c_var<bool>*>(m_var_addr);

			var->set(!var->get());
			break;
		}
		case item_int: {
			c_var<int>* var = reinterpret_cast<c_var<int>*>(m_var_addr);

			var->set(util.math->clamp((var->get() + var->get_step()), var->get_min(), var->get_max()));
			break;
		}
		case item_enum: {
			c_var<int>* var = reinterpret_cast<c_var<int>*>(m_var_addr);

			var->set(util.math->clamp((var->get() + 1), 0, (static_cast<int>(m_items->size()) - 1)));
			break;
		}
		case item_float:
		case item_float_hp: {
			c_var<float>* var = reinterpret_cast<c_var<float>*>(m_var_addr);

			var->set(util.math->clamp((var->get() + var->get_step()), var->get_min(), var->get_max()));
			break;
		}
		case item_key: {
			//this logic has bee written in move_left.
			break;
		}
		default:
			break;
	}
}

bool c_menu_item::is_hovered(const int x, const int y) const {
	static const int s_item_height = (helpers.draw->get_font_height(font_tahoma) + 1);
	return (helpers.input->cursor_x() > x && helpers.input->cursor_x() < (x + menu_w) && helpers.input->cursor_y() > y && helpers.input->cursor_y() < (y + s_item_height));
}