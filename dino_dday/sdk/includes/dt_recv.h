#pragma once

#include "dt_common.h"

class c_recv_table;
class c_recv_prop;

class c_recv_proxy_data {
	const c_recv_prop* m_recv_prop;
	c_dvariant m_value;
	int m_element_num;
	int m_object_id;
};

class c_recv_prop {
public:
	__inline const char* get_name() const {
		return m_var_name;
	}

	__inline c_recv_prop* get_array_prop() const {
		return m_array_prop;
	}

	__inline c_recv_table* get_data_table() const {
		return m_data_table;
	}

	__inline send_prop_type get_type() const {
		return m_recv_type;
	}

	__inline int get_offset() const {
		return m_offset;
	}

	__inline int get_num_elements() const {
		return m_num_elements;
	}

private:
	char* m_var_name;
	send_prop_type m_recv_type;
	int m_flags;
	int m_string_buffer_size;
	bool m_inside_array;
	const void* m_extra_data;
	c_recv_prop* m_array_prop;
	void* m_array_len_proxy;
	void* m_proxy_fn;
	void* m_data_table_proxy_fn;
	c_recv_table* m_data_table;
	int m_offset;
	int m_element_stride;
	int m_num_elements;
	const char* m_parent_array_prop_name;
};

class c_recv_table {
public:
	__inline c_recv_prop* get_prop(const int idx) const {
		return &m_props[idx];
	}

	__inline int get_num_props() const {
		return m_num_props;
	}

	__inline const char* get_name() const {
		return m_net_table_name;
	}

private:
	c_recv_prop* m_props;
	int m_num_props;
	void* m_decoder;
	char* m_net_table_name;
	bool m_initialized;
	bool m_in_main_list;
};