#include "Vector3.h"

Vector3::Vector3()
	:x(0.0),
	y(0.0),
	z(0.0)
{
}

Vector3::Vector3(const float& xyz)
	:x(xyz),
	y(xyz),
	z(xyz)
{

}
Vector3::Vector3(const float& x, const float& y, const float& z)
	:x(x),
	y(y),
	z(z)
{
}


Vector3::~Vector3()
{
}

std::ostream& operator<<(std::ostream& out, const Vector3& vec)
{
	out << "X: " << vec.x << " Y: " << vec.y << " Z: " << vec.z;

	return out;
}

Vector3& Vector3::operator=(const Vector3& other)
{
	x = other.x;
	y = other.y;
	z = other.z;

	return *this;
}

bool Vector3::operator == (const Vector3& other) const
{
	return ((x == other.x) && (y == other.y) && (z == other.z));
}

bool Vector3::operator!=(const Vector3& other) const
{
	return !(*this == other);
}

bool Vector3::operator>(const Vector3& other) const
{
	return ((x > other.x) && (y > other.y) && (z > other.z));
}

bool Vector3::operator>(float value) const
{
	return ((x > value) && (y > value) && (z > value));
}

bool Vector3::operator>=(const Vector3& other) const
{
	return ((x >= other.x) && (y >= other.y) && (z >= other.z));
}

bool Vector3::operator>=(float value) const
{
	return ((x >= value) && (y >= value) && (z >= value));
}

bool Vector3::operator<(const Vector3& other) const
{
	return ((x < other.x) && (y < other.y) && (z < other.z));
}

bool Vector3::operator<(float value) const
{
	return ((x < value) && (y < value) && (z < value));
}

bool Vector3::operator<=(const Vector3& other) const
{
	return ((x <= other.x) && (y <= other.y) && (z <= other.z));
}

bool Vector3::operator<=(float value) const
{
	return ((x <= value) && (y <= value) && (z <= value));
}

Vector3& Vector3::operator+=(const Vector3& other)
{
	x = x + other.x;
	y = y + other.y;
	z = z + other.z;

	return *this;
}

Vector3& Vector3::operator-=(const Vector3& other)
{
	x = x - other.x;
	y = y - other.y;
	z = z - other.z;

	return *this;
}


Vector3 Vector3::operator+(const Vector3& other)
{
	Vector3 result;
	result.x = x + other.x;
	result.y = y + other.y;
	result.z = z + other.z;
	return result;
}
Vector3 Vector3::operator-(const Vector3& other)
{
	Vector3 result;
	result.x = x - other.x;
	result.y = y - other.y;
	result.z = z - other.z;
	return result;
}
Vector3 Vector3::operator*(const Vector3& other)
{
	Vector3 result;
	result.x = x * other.x;
	result.y = y * other.y;
	result.z = z * other.z;
	return result;
}

const Vector3 Vector3::operator*(const Vector3& other) const
{
	Vector3 result;
	result.x = x * other.x;
	result.y = y * other.y;
	result.z = z * other.z;
	return result;
}

Vector3 Vector3::operator/(const Vector3& other)
{
	Vector3 result;
	result.x = x / other.x;
	result.y = y / other.y;
	result.z = z / other.z;
	return result;
}

Vector3 Vector3::operator+(const float& n)
{
	Vector3 result;
	result.x = x + n;
	result.y = y + n;
	result.z = z + n;
	return result;
}
Vector3 Vector3::operator-(const float& n)
{
	Vector3 result;
	result.x = x - n;
	result.y = y - n;
	result.z = z - n;
	return result;
}
Vector3 Vector3::operator*(const float& n)
{
	Vector3 result;
	result.x = x * n;
	result.y = y * n;
	result.z = z * n;
	return result;
}
Vector3 Vector3::operator/(const float& n)
{
	Vector3 result;
	result.x = x / n;
	result.y = y / n;
	result.z = z / n;
	return result;
}

const float* Vector3::getValuePtr() const
{
	return &x;
}

Vector3 Vector3::operator-()
{
	Vector3 newVec(-x, -y, -z);
	return newVec;
}