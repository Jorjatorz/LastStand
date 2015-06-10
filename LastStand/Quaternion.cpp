#include "Quaternion.h"

#include "Vector3.h"

Quaternion::Quaternion()
	:_GLMQuat()
{
}

Quaternion::Quaternion(float w, float x, float y, float z)
	: _GLMQuat(w, x, y, z)
{
}

Quaternion::Quaternion(const Vector3& eulerAngles)
{

	glm::vec3 eulerA(eulerAngles.x, eulerAngles.y, eulerAngles.z);
	_GLMQuat = glm::quat(glm::radians(eulerA));
}

Quaternion::Quaternion(float degrees, const Vector3& normalizedAxis)
{
	glm::vec3 eulerA(normalizedAxis.x, normalizedAxis.y, normalizedAxis.z);

	_GLMQuat = glm::angleAxis(degrees, eulerA);
}

Quaternion::~Quaternion()
{
}

std::ostream& operator<<(std::ostream& out, Quaternion& quat)
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