#pragma once

#include <iostream>
#include <glm\glm.hpp>

//Warp class for glm vector
class Vector3
{
public:
	Vector3();
	Vector3(const float& xyz);
	Vector3(const float& x, const float& y, const float& z);
	~Vector3();

	//Operator overloading
	friend std::ostream& operator<<(std::ostream& out, const Vector3& vec);

	Vector3& operator=(const Vector3& other);
	bool operator==(const Vector3& other) const;
	bool operator!=(const Vector3& other) const;

	bool operator>(const Vector3& other) const;
	bool operator>(float value) const;
	bool operator>=(const Vector3& other) const;
	bool operator>=(float value) const;
	bool operator<(const Vector3& other) const;
	bool operator<(float value) const;
	bool operator<=(const Vector3& other) const;
	bool operator<=(float value) const;

	Vector3& operator+=(const Vector3& other);
	Vector3& operator-=(const Vector3& other);

	Vector3 operator+(const Vector3& other);
	Vector3 operator-(const Vector3& other);
	Vector3 operator*(const Vector3& other);
	const Vector3 operator*(const Vector3& other) const;
	Vector3 operator/(const Vector3& other);

	Vector3 operator+(const float& n);
	Vector3 operator-(const float& n);
	Vector3 operator*(const float& n);
	Vector3 operator/(const float& n);

	Vector3 operator-();

	//Return the constant address of the first element of the vector
	const float* getValuePtr() const;

	//Vector components (same value different name)
	union{ float x, r, s;};
	union{ float y, g, t; };
	union{ float z, b, p; };

	friend class Math;

};

