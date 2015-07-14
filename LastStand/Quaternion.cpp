#include "Quaternion.h"

#include "Vector3.h"
#include "FRotator.h"

Quaternion::Quaternion()
	:_GLMQuat()
{
}

Quaternion::Quaternion(float w, float x, float y, float z)
	: _GLMQuat(w, x, y, z)
{
}

Quaternion::Quaternion(float degrees, const Vector3& normalizedAxis)
{
	glm::vec3 eulerA(normalizedAxis.x, normalizedAxis.y, normalizedAxis.z);

	_GLMQuat = glm::angleAxis(degrees, eulerA);
}

Quaternion::Quaternion(const Vector3& eulerAngle)
	:_GLMQuat(glm::radians(glm::vec3(eulerAngle.x, eulerAngle.y, eulerAngle.z)))
{
}

Quaternion::~Quaternion()
{
}

std::ostream& operator<<(std::ostream& out, Quaternion& quat)
{
	out << "W: " << quat.getW() << " X: " << quat.getX() << " Y: " << quat.getY() << " Z: " << quat.getZ();

	return out;
}

std::ostream& operator<<(std::ostream& out, const Quaternion& quat)
{
	out << "W: " << quat.getW() << " X: " << quat.getX() << " Y: " << quat.getY() << " Z: " << quat.getZ();

	return out;
}

Quaternion& Quaternion::operator=(const Quaternion& other)
{
	_GLMQuat = other._GLMQuat;

	return *this;
}

bool Quaternion::operator==(const Quaternion& other) const
{
	return _GLMQuat == other._GLMQuat;
}

bool Quaternion::operator!=(const Quaternion& other) const
{
	return _GLMQuat != other._GLMQuat;
}

Quaternion Quaternion::operator+(const Quaternion& other)
{
	Quaternion quat;
	quat._GLMQuat = _GLMQuat + other._GLMQuat;
	return quat;
}

Quaternion Quaternion::operator*(const Quaternion& other)
{
	Quaternion quat;
	quat._GLMQuat = _GLMQuat * other._GLMQuat;
	return quat;
}

Quaternion Quaternion::operator*(const Quaternion& other) const
{
	Quaternion quat;
	quat._GLMQuat = _GLMQuat * other._GLMQuat;
	return quat;
}

Vector3 Quaternion::operator*(const Vector3& other)
{
	glm::vec3 aux(other.x, other.y, other.z);

	glm::vec3 ret = _GLMQuat * aux;

	return Vector3(ret.x, ret.y, ret.z);
}

Vector3 Quaternion::operator*(const Vector3& other) const
{
	glm::vec3 aux(other.x, other.y, other.z);

	glm::vec3 ret = _GLMQuat * aux;

	return Vector3(ret.x, ret.y, ret.z);
}

Quaternion Quaternion::operator-()
{
	Quaternion newQuat;

	newQuat._GLMQuat = -_GLMQuat;

	return newQuat;
}

void Quaternion::normalize()
{
	_GLMQuat = glm::normalize(_GLMQuat);
}

Quaternion Quaternion::getNormalizedQuaternion()
{
	Quaternion toRet;
	toRet._GLMQuat = glm::normalize(_GLMQuat);

	return toRet;
}

Vector3 Quaternion::toEuler() const
{
	glm::vec3 eulerA = glm::eulerAngles(_GLMQuat);

	return Vector3(eulerA.x, eulerA.y, eulerA.z);
}

Quaternion Quaternion::SLERP(const Quaternion& quat1, const Quaternion& quat2, float amount)
{
	Quaternion toRet;

	toRet._GLMQuat = glm::mix(quat1._GLMQuat, quat2._GLMQuat, amount);

	return toRet;
}

Quaternion Quaternion::conjugate(const Quaternion& quat)
{
	Quaternion toRet;
	toRet._GLMQuat = glm::conjugate(quat._GLMQuat);
	return toRet;
}

float Quaternion::dot(const Quaternion& quat1, const Quaternion& quat2)
{
	return glm::dot(quat1._GLMQuat, quat2._GLMQuat);
}

FRotator Quaternion::toRotator()
{
	return FRotator(*this);
}
