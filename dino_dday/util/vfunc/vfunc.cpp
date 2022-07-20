#include "vfunc.h"

void**& c_vfunc::get_internal(void* inst, const unsigned int off) {
	return *reinterpret_cast<void***>(reinterpret_cast<unsigned int>(inst) + off);
}

const void** c_vfunc::get_internal(const void* inst, const unsigned int off) {
	return *reinterpret_cast<const void***>(reinterpret_cast<unsigned int>(inst) + off);
}