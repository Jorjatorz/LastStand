#pragma once

#include <iostream>
#include <glm\glm.hpp>
#include <glm\gtc\quaternion.hpp>
#include <glm\gtx\quaternion.hpp>

//Forward declaration
class Vector3;

class Quaternion
{
public:
	//Unit quaternion constructor
	Quaternion();
	//Constructor with the components of the quaternion as arguments
	Quaternion(float w, float x, float y, float z);
	//Creates a quaternion given euler angles vector (in degrees)
	Quaternion(const Vector3& eulerAngles);
	//Builds a quaternion from an angle and a NORMALIZED axis
	Quaternion(float degrees, const Vector3& normalizedAxis);
	~Quaternion();


	//Operator overloading
	friend std::ostream& operator<<(std::ostream& out, Quaternion& quat);

	Quaternion& operator=(const Quaternion& other);
	bool operator==(const Quaternion& other) const;
	bool operator!=(const Quaternion& other) const;

	Quaternion operator+(const Quaternion& other);
	Quaternion operator*(const Quaternion& other);
	Quaternion operator*(const Quaternion& other) const;

	Quaternion operator-();

	//Normalize the quaternion
	void normalize();

	float getX()
	{
		return _GLMQuat.x;
	}
	float getY()
	{
		return _GLMQuat.y;
	}
	float getZ()
	{
		return _GLMQuat.z;
	}
	float getW()
	{
		return _GLMQuat.w;
	}

private:
	//GLM quaternion, incharge of all the operations.
	glm::quat _GLMQuat;
};

