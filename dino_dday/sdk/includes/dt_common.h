#pragma once

#include "const.h"

#define max_datatables 1024
#define max_datatable_props 4096
#define max_array_elements 2048
#define high_default -121121.121121f
#define bits_fullres -1
#define bits_worldcoord -2
#define dt_max_string_bits 9
#define max_string_buffersize (1 << dt_max_string_bits)

#define sprop_unsigned (1 << 0)
#define sprop_coord (1 << 1)
#define sprop_noscale (1 << 2)
#define sprop_round_down (1 << 3)
#define sprop_round_up (1 << 4)
#define sprop_normal (1 << 5)
#define sprop_exclude (1 << 6)
#define sprop_xyze (1 << 7)
#define sprop_inside_array (1 << 8)
#define sprop_proxy_always_yes (1 << 9)
#define sprop_changes_often (1 << 10)
#define sprop_is_a_vector_elem (1 << 11)
#define sprop_collapsible (1 << 12)
#define sprop_coord_mp (1 << 13)
#define sprop_coord_mp_low_precision (1 << 14)
#define sprop_coord_mp_integral (1 << 15)
#define sprop_num_flag_bits_networked 16
#define sprop_encoded_against_tickcount (1 << 16)
#define sprop_num_flag_bits 17
#define sizeof_ignore -1

enum send_prop_type {
	dpt_int = 0,
	dpt_float,
	dpt_vector,
	dpt_string,
	dpt_array,
	dpt_data_table,
	dpt_num_send_prop_types
};

class c_dvariant
{
public:
	c_dvariant() {
		m_type = dpt_float;
	}

	c_dvariant(const float val) {
		m_type = dpt_float;
		m_float = val;
	}

public:
	union {
		float m_float;
		long m_int;
		char* m_string;
		void* m_data;
		float m_vector[3];
	};

	send_prop_type m_type;
};

__inline int num_bits_for_count(int max_elements) {
	int bits = 0;

	while (max_elements) {
		bits++;
		max_elements >>= 1;
	}

	return bits;
}