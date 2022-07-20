#include "sdk.h"

c_base_entity* c_base_handle::get() {
	c_client_entity* ent = ints.entity_list->get_client_entity_from_handle(*this);

	return ent ? ent->as<c_base_entity*>() : nullptr;
}