#pragma once

#include <iostream>

class Quaternion;
class Vector3;

//Class representing a rotation (pitch, yaw, roll)
//All rotation information is stored in degrees
class FRotator
{
public:
	FRotator();
	explicit FRotator(float pitch, float yaw, float roll);
	explicit FRotator(const Vector3& yawPitchRollVector);
	explicit FRotator(const Quaternion& quat); //To euler angles
	~FRotator();

	FRotator& operator +=(const FRotator& other);

	//Return a quaternion representing the rotation
	Quaternion toQuaternion() const;
	//Return a direction vector facing in the rotator direction
	Vector3 toVector3() const;
	//Return a vector with euler angles (in degrees)
	Vector3 toEuler() const;

	//Rotates a vector by this rotator
	Vector3 rotateVector(const Vector3& vec);

	//Return a copy of the rotator clampled in a range of [0, 360]
	FRotator clamp();
	//Normalize the rotator to [-180, 180]
	void normalize();

	void addPitch(float degrees);
	void addYaw(float degrees);
	void addRoll(float degrees);

	void setPitch(float degrees);
	void setYaw(float degrees);
	void setRoll(float degrees);

	float getPitch() const
	{
		return _pitch;
	}
	float getYaw() const
	{
		return _yaw;
	}
	float getRoll() const
	{
		return _roll;
	}

	friend std::ostream& operator<<(std::ostream& out, FRotator& rotator);
	friend std::ostream& operator<<(std::ostream& out, const FRotator& rotator);

private:
	float _pitch, _yaw, _roll;

	//Takes an axis rotation and clamps it to [0, 360]
	float clampAxis(float degrees);
	//Clamps the axis to [-180, 180]
	float normalizeAxis(float degrees);
};

