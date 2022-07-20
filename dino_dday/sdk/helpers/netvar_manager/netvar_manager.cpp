#include "netvar_manager.h"

int c_netvar_manager::get(const char* const class_name, const char* const var_name) {
	for (client_class* cc = ints.base_client->get_all_classes(); cc; cc = cc->get_next()) {
		if (hash_fnv(cc->get_name()) == hash_fnv(class_name))
			return get_internal(cc->get_table(), var_name);
	}

	return 0;
}

int c_netvar_manager::get_internal(c_recv_table* table, const char* const var_name) {
	for (int n = 0; n < table->get_num_props(); n++) {
		c_recv_prop* prop = table->get_prop(n);

		if (!prop)
			continue;

		if (hash_fnv(prop->get_name()) == hash_fnv(var_name))
			return prop->get_offset();

		c_recv_table* data_table = prop->get_data_table();

		if (data_table) {
			const int off = get_internal(data_table, var_name);

			if (off)
				return (off + prop->get_offset());
		}
	}

	return 0;
}