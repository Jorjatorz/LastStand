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
}

FRotator::FRotator(const Vector3& yawPitchRollVector)
	:_pitch(yawPitchRollVector.x),
	_yaw(yawPitchRollVector.y),
	_roll(yawPitchRollVector.z)
{
}

FRotator::FRotator(const Quaternion& quat)
{
	Vector3 euler = quat.toEuler();

	_pitch = euler.x;
	_yaw = euler.y;
	_roll = euler.z;

	normalize();
}


FRotator::~FRotator()
{
}

Quaternion FRotator::toQuaternion() const
{
	return Quaternion(toEuler());
}

Vector3 FRotator::toVector3() const
{	
	return toEuler().getNormalizedVector();
}

Vector3 FRotator::toEuler() const
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
}

void FRotator::addYaw(float degrees)
{
	_yaw += degrees;
}

void FRotator::addRoll(float degrees)
{
	_roll += degrees;
}

FRotator& FRotator::operator+=(const FRotator& other)
{
	_pitch += other._pitch;
	_yaw += other._yaw;
	_roll += other._roll;

	return *this;
}

FRotator FRotator::clamp()
{
	return FRotator(clampAxis(_pitch), clampAxis(_yaw), clampAxis(_roll));
}

void FRotator::setPitch(float degrees)
{
	_pitch = degrees;
}

void FRotator::setYaw(float degrees)
{
	_yaw = degrees;
}

void FRotator::setRoll(float degrees)
{
	_roll = degrees;
}

float FRotator::clampAxis(float degrees)
{
	//Get the angle in a range of (-360, 360)
	float angle = Math::fmod(degrees, 360.0f);

	if (angle < 0.0f)
	{
		//Shift angle to [0,360) range
		angle += 360.0f;
	}

	return angle;
}

float FRotator::normalizeAxis(float degrees)
{
	//Get the angle in [0, 360]
	float angle = clampAxis(degrees);

	if (angle > 180.0f)
	{
		//Shift angle to (-180,180]
		angle -= 360.f;
	}

	return angle;
}

void FRotator::normalize()
{
	_pitch = normalizeAxis(_pitch);
	_yaw = normalizeAxis(_yaw);
	_roll = normalizeAxis(_roll);
}

std::ostream& operator<<(std::ostream& out, FRotator& rotator)
{
	out << "Pitch: " << rotator.getPitch() << " Yaw: " << rotator.getYaw() << " Roll: " << rotator.getRoll();

	return out;
}

std::ostream& operator<<(std::ostream& out, const FRotator& rotator)
{
	out << "Pitch: " << rotator.getPitch() << " Yaw: " << rotator.getYaw() << " Roll: " << rotator.getRoll();

	return out;
}