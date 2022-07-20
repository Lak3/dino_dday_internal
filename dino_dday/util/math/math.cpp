#include "math.h"

void c_math::sin_cos(const float r, float& s, float& c) {
	s = ::sinf(r);
	c = ::cosf(r);
}

void c_math::vector_transform(const vector in, const matrix3x4_t m, vector& out) {
	out.x = (in.dot({ m[0][0], m[0][1], m[0][2] }) + m[0][3]);
	out.y = (in.dot({ m[1][0], m[1][1], m[1][2] }) + m[1][3]);
	out.z = (in.dot({ m[2][0], m[2][1], m[2][2] }) + m[2][3]);
}

void c_math::build_transformed_box(vector* v2, const vector bbmin, const vector bbmax, const matrix3x4_t& m) {
	vector v[8];
	points_from_box(bbmin, bbmax, v);

	vector_transform(v[0], m, v2[0]);
	vector_transform(v[1], m, v2[1]);
	vector_transform(v[2], m, v2[2]);
	vector_transform(v[3], m, v2[3]);
	vector_transform(v[4], m, v2[4]);
	vector_transform(v[5], m, v2[5]);
	vector_transform(v[6], m, v2[6]);
	vector_transform(v[7], m, v2[7]);
}

void c_math::points_from_box(const vector mins, const vector maxs, vector* points) {
	points[0].x = mins.x;
	points[0].y = mins.y;
	points[0].z = mins.z;

	points[1].x = mins.x;
	points[1].y = mins.y;
	points[1].z = maxs.z;

	points[2].x = mins.x;
	points[2].y = maxs.y;
	points[2].z = mins.z;

	points[3].x = mins.x;
	points[3].y = maxs.y;
	points[3].z = maxs.z;

	points[4].x = maxs.x;
	points[4].y = mins.y;
	points[4].z = mins.z;

	points[5].x = maxs.x;
	points[5].y = mins.y;
	points[5].z = maxs.z;

	points[6].x = maxs.x;
	points[6].y = maxs.y;
	points[6].z = mins.z;

	points[7].x = maxs.x;
	points[7].y = maxs.y;
	points[7].z = maxs.z;
}

void c_math::vector_angles(const vector fward, vector& ang) {
	float yaw, pitch;

	if ((fward.x == 0.0f) && (fward.y == 0.0f)) {
		yaw   = 0.0f;
		pitch = 90.0f + (180.0f * (fward.z > 0.0f));
	}
	else {
		yaw = rad2degf(::atan2f(fward.y, fward.x));
		yaw += 360.0f * (yaw < 0.0f);

		pitch = rad2degf(::atan2f(-fward.z, fward.length2d()));
		pitch += 360.0f * (pitch < 0.0f);
	}

	ang.x = pitch;
	ang.y = yaw;
	ang.z = 0.0f;
}

void c_math::angle_vectors(const vector ang, vector* forward, vector* right, vector* up) {
	float sr, sp, sy, cr, cp, cy;

	sin_cos(deg2radf(ang.y), sy, cy);
	sin_cos(deg2radf(ang.x), sp, cp);
	sin_cos(deg2radf(ang.z), sr, cr);

	if (forward) {
		forward->x = cp * cy;
		forward->y = cp * sy;
		forward->z = -sp;
	}

	if (right) {
		right->x = (-1 * sr * sp * cy + -1 * cr * -sy);
		right->y = (-1 * sr * sp * sy + -1 * cr * cy);
		right->z = -1 * sr * cp;
	}

	if (up) {
		up->x = (cr * sp * cy + -sr * -sy);
		up->y = (cr * sp * sy + -sr * cy);
		up->z = cr * cp;
	}
}

float c_math::normalize_angle(const float ang) {
	return ::remainderf(ang, 360.0f) * (::isfinite(ang));
}

float c_math::remap_val_clamped(const float val, const float a, const float b, const float c, const float d) {
	return (a == b) ? ((val >= b) ? d : c) : (c + (d - c) * clamp(((val - a) / (b - a)), 0.0f, 1.0f));
}

float c_math::get_fov_between(const vector src, const vector dst) {
	vector v_src;
	angle_vectors(src, &v_src, nullptr, nullptr);

	vector v_dst;
	angle_vectors(dst, &v_dst, nullptr, nullptr);

	const float result = rad2degf(::acosf(v_dst.dot(v_src) / v_dst.length_sqr()));

	return (!::isfinite(result) || isinf(result) || isnan(result)) ? std::numeric_limits<float>::max() : result;
}

vector c_math::get_angle_to_pos(const vector from, const vector to) {
	const vector d = (from - to);

	return { (::atanf(d.z / d.length2d()) * m_radpi), (::atanf(d.y / d.x) * m_radpi) + (180.0f * (d.x >= 0.0f)), (0.0f) };
}

vector c_math::clamp_angles(const vector in) {
	return { (max(-89.0f, min(89.0f, normalize_angle(in.x)))), (normalize_angle(in.y)), (0.0f) };
}