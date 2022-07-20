#pragma once

#include "../../util/util.h"

class color
{
public:
	color() {
		*reinterpret_cast<int*>(this) = 0;
	}

	color(const int _r, const int _g, const int _b, const int _a = 255) {
		_color[0] = static_cast<unsigned char>(_r);
		_color[1] = static_cast<unsigned char>(_g);
		_color[2] = static_cast<unsigned char>(_b);
		_color[3] = static_cast<unsigned char>(_a);
	}

public:
	unsigned char& operator[](int index)
	{
		return _color[index];
	}

	const unsigned char& operator[](int index) const
	{
		return _color[index];
	}

	bool operator == (const color& rhs) const
	{
		return (*((int*)this) == *((int*)&rhs));
	}

	bool operator != (const color& rhs) const
	{
		return !(operator==(rhs));
	}

	color& operator=(const color& rhs)
	{
		set_raw_color(rhs.get_raw_color());
		return *this;
	}

public:
	__inline int get_raw_color() const {
		return *((int*)this);
	}

	__inline void set_raw_color(const int clr32) {
		*reinterpret_cast<int*>(this) = clr32;
	}

private:
	unsigned char _color[4] = { };
};