#pragma once

#include "base_handle.h"

typedef unsigned int crc32_t;

class c_crc32 {
public:
	void init(crc32_t* pul_crc);
	void process_buffer(crc32_t* pul_crc, const void* p, int len);
	void finish(crc32_t* pul_crc);
	crc32_t get_table_entry(unsigned int slot);
	crc32_t process_single_buffer(const void* p, int len);
};

inline c_crc32 crc32;