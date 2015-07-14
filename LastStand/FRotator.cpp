#include "FRotator.h"

#include "Math.h"
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
	clamp();
}

FRotator::FRotator(const Vector3& yawPitchRollVector)
	:_pitch(yawPitchRollVector.x),
	_yaw(yawPitchRollVector.y),
	_roll(yawPitchRollVector.z)
{
	clamp();
}

FRotator::FRotator(const Quaternion& quat)
{
	Vector3 euler = quat.toEuler();

	_pitch = euler.x;
	_yaw = euler.y;
	_roll = euler.z;

	clamp();
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

void FRotator::addPitch(float degrees)
{
	_pitch += degrees;

	clamp();
}

void FRotator::addYaw(float degrees)
{
	_yaw += degrees;

	clamp();
}

void FRotator::addRoll(float degrees)
{
	_roll += degrees;

	clamp();
}

FRotator& FRotator::operator+=(const FRotator& other)
{
	_pitch += other._pitch;
	_yaw += other._yaw;
	_roll += other._roll;

	clamp();

	return *this;
}

void FRotator::clamp()
{
	_pitch = Math::fmod(_pitch, 360.0f);
	_yaw = Math::fmod(_yaw, 360.0f);
	_roll = Math::fmod(_roll, 360.0f);
}
