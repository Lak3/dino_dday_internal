#include "util.h"

c_util::c_util() {
	iface   = std::make_unique<c_interface>();
	math    = std::make_unique<c_math>();
	pattern = std::make_unique<c_pattern>();
	vfunc   = std::make_unique<c_vfunc>();
	offsets = std::make_unique<c_offsets>();

	console_msg("c_util::c_util() initialized utility pointers.\n");
}

c_util::~c_util() {
	iface.reset();
	math.reset();
	pattern.reset();
	vfunc.reset();
	offsets.reset();
}