#include "../hooks.h"

long __stdcall hooked::wndproc::func(HWND hwnd, unsigned int msg, unsigned int w_param, long l_param) {
	return features.menu->is_open() ? 1ul : CallWindowProcW(wnd_proc, hwnd, msg, w_param, l_param);
}

bool hooked::wndproc::initialize() {
	window = FindWindowW(nullptr, L"Dino D-Day");

	if (!window)
		return false;
		
	wnd_proc = reinterpret_cast<WNDPROC>(SetWindowLongW(window, -4, reinterpret_cast<long>(func)));
	
	return (wnd_proc != nullptr);
}