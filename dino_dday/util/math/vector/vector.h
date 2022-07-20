#pragma once

#include "../../interface/interface.h"

#define m_radpi		57.2957795131f
#define m_pi		3.14159265359f

#define deg2rad(x)	(static_cast<float>(x) * 0.01745329251f)
#define rad2deg(x)	(static_cast<float>(x) * 57.2957795131f)

#define deg2radf(f)	((f) * 0.01745329251f)
#define rad2degf(f)	((f) * 57.2957795131f)

class vector
{
public:
	vector(const float _x = 0.0f, const float _y = 0.0f, const float _z = 0.0f) {
		x = _x; y = _y; z = _z;
	}

	vector(const vector& v) {
		x = v.x; y = v.y; z = v.z;
	}

public:
	vector& operator+=(const vector& v) {
		x += v.x; y += v.y; z += v.z; return *this;
	}

	vector& operator-=(const vector& v) {
		x -= v.x; y -= v.y; z -= v.z; return *this;
	}

	vector& operator/=(const vector& v) {
		x /= v.x; y /= v.y; z /= v.z; return *this;
	}

	vector& operator*=(const vector& v) {
		x *= v.x; y *= v.y; z *= v.z; return *this;
	}

	vector& operator+=(const float f) {
		x += f; y += f; z += f; return *this;
	}

	vector& operator-=(const float f) {
		x -= f; y -= f; z -= f; return *this;
	}

	vector operator+(const vector& v) const {
		return vector(x + v.x, y + v.y, z + v.z);
	}

	vector operator-(const vector& v) const {
		return vector(x - v.x, y - v.y, z - v.z);
	}

	vector operator+(const float f) const {
		return vector(x + f, y + f, z + f);
	}

	vector operator-(const float f) const {
		return vector(x - f, y - f, z - f);
	}

	vector operator*(const float f) const {
		return vector(x * f, y * f, z * f);
	}

	vector operator/(const float f) const {
		return vector(x / f, y / f, z / f);
	}

public:
	__inline float length() const {
		return ::sqrtf(x * x + y * y + z * z);
	}

	__inline float length2d() const {
		return ::sqrtf(x * x + y * y);
	}

	__inline float length_sqr() const {
		return (x * x + y * y + z * z);
	}

	__inline float length2d_sqr() const {
		return (x * x + y * y);
	}

	__inline float normalize() {
		const float len_normal = (1.0f / (std::numeric_limits<float>::epsilon() + length()));

		x = (x * len_normal);
		y = (y * len_normal);
		z = (z * len_normal);

		return length(); //return new length.
	}

	__inline float dist_to(const vector v) const {
		return (*this - v).length();
	}

	__inline float dot(const vector v) const {
		return (x * v.x + y * v.y + z * v.z);
	}

public:
	float x = 0.0f, y = 0.0f, z = 0.0f;
};

class vector2d
{
public:


public:
	float x = 0.0f, y = 0.0f;
};

class vector4d
{
public:


public:
	float x = 0.0f, y = 0.0f, z = 0.0f, w = 0.0f;
};

class __declspec(align(16)) vector_aligned : public vector
{
public:
	__inline vector_aligned() {

	}

	__inline vector_aligned(const float _x, const float _y, const float _z) {
		x = _x; y = _y; z = _z;
	}

	explicit vector_aligned(const vector& v) {
		x = v.x; y = v.y; z = v.z;
	}

public:
	vector_aligned& operator=(const vector& v) {
		x = v.x; y = v.y; z = v.z; return *this;
	}

public:
	float w = 0.0f;
};