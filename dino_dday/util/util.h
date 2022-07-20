#pragma once

#include "offsets/offsets.h"

#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <thread>
#include <map>

class c_util {
public:
	c_util();
	~c_util();

public:
	std::unique_ptr<c_interface> iface   = { };
	std::unique_ptr<c_math>      math    = { };
	std::unique_ptr<c_pattern>   pattern = { };
	std::unique_ptr<c_vfunc>     vfunc   = { };
	std::unique_ptr<c_offsets>   offsets = { };
};

inline c_util util;

static void console_msg(const char* const msg, ...) {
	static const auto s_fn = reinterpret_cast<void(_cdecl*)(const char*, va_list)>(GetProcAddress(GetModuleHandleW(L"tier0.dll"), "Msg"));

	char cbuff[256];
	va_list valist;
	va_start(valist, msg);
	vsprintf_s(cbuff, msg, valist);
	va_end(valist);

	s_fn(cbuff, valist);
}

static std::wstring util_get_vkey_name(const int v_key) {
	switch (v_key) {
		case 0: return L"none";
		case 1: return L"left mouse";
		case 2: return L"right mouse";
		case 3: return L"cancel";
		case 4: return L"middle mouse";
		case 5: return L"xbutton 1";
		case 6: return L"xbutton 2";
		case 46: return L"delete";
		default: break;
	}

	wchar_t wbuff[16] = { L"\0" };

	if (GetKeyNameTextW(MapVirtualKeyW(v_key, 0) << 16, wbuff, 16)) {
		std::wstring key_name = wbuff;

		std::transform(key_name.begin(), key_name.end(), key_name.begin(),
			[](wchar_t c) { return ::towlower(c); });

		return key_name;
	}

	return L"unknown key";
}