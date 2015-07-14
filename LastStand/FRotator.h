#pragma once

class Quaternion;
class Vector3;

//Class representing a rotation (pitch, yaw, roll)
//All rotation information is stored in degrees
class FRotator
{
public:
	FRotator();
	FRotator(float pitch, float yaw, float roll);
	FRotator(const Vector3& yawPitchRollVector);
	FRotator(const Quaternion& quat); //To euler angles
	~FRotator();

	//Return a quaternion representing the rotation
	Quaternion toQuaternion();
	//Return a direction vector facing in the rotator direction
	Vector3 toVector3();
	//Return a vector with euler angles (in degrees)
	Vector3 toEuler();

	//Rotates a vector by this rotator
	Vector3 rotateVector(const Vector3& vec);

	float getPitch()
	{
		return _pitch;
	}
	float getYaw()
	{
		return _yaw;
	}
	float getRoll()
	{
		return _roll;
	}

private:
	float _pitch, _yaw, _roll;
};

