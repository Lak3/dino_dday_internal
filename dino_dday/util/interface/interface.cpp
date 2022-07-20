#include "interface.h"

using farproc = FARPROC;

void* c_interface::get_internal(const hmodule hmod, const char* const obj) {
	const farproc create_addr = GetProcAddress(hmod, "CreateInterface");

	if (!create_addr)
		return nullptr;

	const auto create_interface = reinterpret_cast<void* (*)(const char*, int*)>(create_addr);

	if (!create_interface)
		return nullptr;

	return create_interface(obj, nullptr);
}