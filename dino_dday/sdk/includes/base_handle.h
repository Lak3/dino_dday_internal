#pragma once

#include "handle_entity.h"

class c_base_entity;

class c_base_handle {
public:
	c_base_handle() {
		m_index = invalid_ehandle_index;
	}

	c_base_handle(const c_base_handle& o) {
		m_index = o.m_index;
	}

	c_base_handle(const unsigned long val) {
		m_index = val;
	}

public:
	c_base_entity* get();

private:
	unsigned long m_index;
};