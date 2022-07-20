#pragma once

#include "vector/vector.h"
#include <cmath>

#undef min
#undef max

using quaternion  = vector4d;
using matrix3x4_t = float[3][4];

class c_vmatrix {
public:
	__inline const matrix3x4_t& as_3x4() const {
		return *((const matrix3x4_t*)this);
	}

private:
	vector m[4][4];
};

class c_math {
public:
	void sin_cos(const float r, float& s, float& c);
	void vector_transform(const vector in, const matrix3x4_t m, vector& out);
	void build_transformed_box(vector* v2, const vector bbmin, const vector bbmax, const matrix3x4_t& m);
	void points_from_box(const vector mins, const vector maxs, vector* points);
	void vector_angles(const vector fward, vector& ang);
	void angle_vectors(const vector ang, vector* forward, vector* right, vector* up);

	float normalize_angle(const float ang);
	float remap_val_clamped(const float val, const float a, const float b, const float c, const float d);
	float get_fov_between(const vector src, const vector dst);

	vector get_angle_to_pos(const vector from, const vector to);
	vector clamp_angles(const vector in);

public:
	template<typename t>
	inline t clamp(const t val, const t min, const t max) {
		const t ret = (val < min) ? min : val;
		return (ret > max) ? max : ret;
	}

	template<typename t>
	inline t min(const t a, const t b) {
		return ((a > b) * b) + ((a <= b) * a);
	}

	template<typename t>
	inline t max(const t a, const t b) {
		return ((a > b) * a) + ((a <= b) * b);
	}
};