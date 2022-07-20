#pragma once

#include "studio.h"

class c_game_trace;
class c_base_entity;

typedef c_game_trace trace_t;

enum trace_type_t {
	trace_everything = 0,
	trace_world_only,
	trace_entities_only,
	trace_everything_filter_props
};

struct cplate_t {
public:
	vector normal;
	float dist;
	unsigned char type;
	unsigned char sign_bits;

private:
	unsigned char __pad00[2];
};

struct csurface_t {
public:
	const char* name;
	short surface_props;
	unsigned short flags;
};

class c_base_trace {
public:
	c_base_trace() {

	}

public:
	vector start_pos;
	vector end_pos;
	cplate_t plane;
	float fraction;
	int contents;
	unsigned short disp_flags;
	bool all_solid;
	bool start_solid;
};

class c_game_trace : public c_base_trace {
public:
	c_game_trace() {

	}

public:
	__inline bool did_hit() const {
		return ((fraction < 1.0f) || all_solid || start_solid);
	}

public:
	float fraction_left_solid;
	csurface_t surface;
	int hitgroup;
	short physics_bone;
	unsigned short world_surface_index;
	c_base_entity* hit_entity;
	int hitbox;
};

class c_trace_filter {
public:
	virtual bool should_hit_entity(c_handle_entity* ent, int contents_mask) = 0;
	virtual trace_type_t get_trace_type() const = 0;
};

class c_trace_filter_world_and_props_only : public c_trace_filter {
public:
	bool should_hit_entity(c_handle_entity* ent, int contents_mask) {
		return false;
	}

	virtual trace_type_t get_trace_type() const {
		return trace_everything;
	}
};

struct ray_t {
public:
	ray_t() {

	}

	ray_t(const vector s, const vector e) {
		delta = vector_aligned(e - s);
		is_swept = (delta.length_sqr() != 0.0f);
		extents = { };
		world_axis_transform = nullptr;
		is_ray = true;
		start_offset = { };
		start = s;
	}

public:
	vector_aligned start;
	vector_aligned delta;
	vector_aligned start_offset;
	vector_aligned extents;
	const matrix3x4_t* world_axis_transform;
	bool is_ray;
	bool is_swept;
};