#include "hooks/hooks.h"

#include <fstream>

#define failed_to_initialize false

static bool load_module() {
	xassertf(util.offsets->initialize() == failed_to_initialize);
	xassertf(ints.initialize() == failed_to_initialize);
	xassertf(helpers.draw->initialize() == failed_to_initialize);
	xassertf(hooks.initialize() == failed_to_initialize);

	//this should not fail...
	features.menu->initialize();

	//if we arrive here, we managed to initialize everything above successfully.
	return true;
}

int __stdcall DllMain(hmodule hinstdll, unsigned long reason, void* reserved) {
	static bool has_attached = false;

	DisableThreadLibraryCalls(hinstdll);

	if ((reason == 1) && !has_attached)
	{
		if (!load_module()) {
			FreeLibraryAndExitThread(hinstdll, 1); //1 == EXIT_FAILURE.
			return 0;
		}

		has_attached = true;
	}

	return 1;
}