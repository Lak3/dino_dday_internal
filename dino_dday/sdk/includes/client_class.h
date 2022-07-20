#pragma once

#include "checksum_md5.h"

class client_class {
public:
	__inline char* get_name() const {
		return m_network_name;
	}

	__inline c_recv_table* get_table() const {
		return m_recv_table;
	}

	__inline client_class* get_next() const {
		return m_next;
	}

	__inline int get_class_id() const {
		return m_class_id;
	}

private:
	void* m_create_fn;
	void* m_create_event_fn;
	char* m_network_name;
	c_recv_table* m_recv_table;
	client_class* m_next;
	int m_class_id;
};