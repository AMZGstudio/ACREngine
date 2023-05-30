#include "Types.hpp"

v2i::v2i()
{
	x = 0, y = 0;
}

v2i::v2i(int x, int y) : x(x), y(y) {}

v2i::v2i(const v2i& other) : x(other.x), y(other.y) {}

v2i v2i::operator+(const v2i& other) const
{
	return v2i(x + other.x, y + other.y);
}

v2i v2i::operator-(const v2i& other) const
{
	return v2i(x - other.x, y - other.y);
}

v2i v2i::operator*(int c) const
{
	return v2i(x * c, y * c);
}

v2i v2i::operator/(int c) const
{
	return v2i(x / c, y / c);
}

v2f::v2f()
{ x = 0, y = 0; }

v2f::v2f(double x, double y) : x(x), y(y) {}

v2f::v2f(const v2f& other)
	: x(other.x), y(other.y) {}

v2f v2f::operator+(const v2f& other) const
{
	return v2f(x + other.x, y + other.y);
}

v2f v2f::operator-(const v2f& other) const
{
	return v2f(x - other.x, y - other.y);
}

v2f v2f::operator*(double c) const
{
	return v2f(x * c, y * c);
}

v2f v2f::operator/(double c) const
{
	return v2f(x / c, y / c);
}

v2f::operator v2i()
{
	return v2i(x, y);
}

v2i::operator v2f()
{
	return v2f(x, y);
}