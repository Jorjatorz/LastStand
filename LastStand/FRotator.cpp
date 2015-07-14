#include "FRotator.h"


#include "Vector3.h"
#include "Quaternion.h"

FRotator::FRotator()
	:_pitch(0),
	_yaw(0),
	_roll(0)
{
}

FRotator::FRotator(float pitch, float yaw, float roll)
	:_pitch(pitch),
	_yaw(yaw),
	_roll(roll)
{
}

FRotator::FRotator(const Vector3& yawPitchRollVector)
	:_pitch(yawPitchRollVector.x),
	_yaw(yawPitchRollVector.y),
	_roll(yawPitchRollVector.z)
{
}

FRotator::FRotator(const Quaternion& quat)
{
	Vector3 euler = quat.getEulerAnglesVector();

	_pitch = euler.x;
	_yaw = euler.y;
	_roll = euler.z;
}


FRotator::~FRotator()
{
}

Quaternion FRotator::toQuaternion()
{
	return Quaternion(toEuler());
}

Vector3 FRotator::toVector3()
{	
	return toEuler().getNormalizedVector();
}

Vector3 FRotator::toEuler()
{
	return Vector3(_pitch, _yaw, _roll);
}

Vector3 FRotator::rotateVector(const Vector3& vec)
{
	auto rotQuat = toQuaternion();

	return rotQuat * vec;
}
