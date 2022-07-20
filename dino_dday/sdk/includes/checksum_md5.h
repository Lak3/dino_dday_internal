#pragma once

#include "checksum_crc.h"

#define md5_digest_length 16
#define md5_bit_length (md5_digest_length * sizeof(unsigned char))

struct md5value_t {
public:
	void zero();
	bool is_zero() const;

public:
	bool operator==(const md5value_t& o) const;
	bool operator!=(const md5value_t& o) const;

public:
	unsigned char bits[md5_digest_length];
};

struct md5context_t {
	unsigned int buf[4];
	unsigned int bits[2];
	unsigned char in[64];
};

class c_md5 {
public:
	void initialize(md5context_t* ctx);
	void update(md5context_t* ctx, unsigned char const* buf, unsigned int len);
	void finish(unsigned char digest[md5_digest_length], md5context_t* ctx);
	void process_single_buffer(const void* p, int len, md5value_t& result);
	void transform(unsigned int buf[4], unsigned int const in[16]);
	unsigned int pseudo_random(unsigned int seed);
	bool compare(const md5value_t& f, const md5value_t& compare);
};

inline c_md5 md5;