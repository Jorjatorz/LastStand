#include "Math.h"

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\random.hpp>
#include <cmath>

#include "Matrix4.h"
#include "Quaternion.h"
#include "Vector3.h"

Math::Math()
{
}


Math::~Math()
{
}



Matrix4 Math::getRotationMatrixFromQuaternion(const Quaternion& quat)
{
	Matrix4 mat;
	mat._GLMMatrix = glm::toMat4(quat._GLMQuat);

	return mat;
}

float Math::fmod(float number, float divider)
{
	return std::fmod(number, divider);
}

float Math::clamp(float num, float min, float max)
{
	return glm::clamp(num, min, max);
}

Vector3 Math::clamp(const Vector3& vec, float min, float max)
{
	return Vector3(clamp(vec.x, min, max), clamp(vec.y, min, max), clamp(vec.z, min, max));
}

float Math::arcCos(float num)
{
	return glm::degrees(glm::acos(num));
}

int Math::randomInteger(int min, int max)
{
	return glm::linearRand(min, max);
}

float Math::randomFloat(float min, float max)
{
	return glm::linearRand(min, max);
}

Vector3 Math::randomVector(float min, float max)
{
	glm::vec3 aux =  glm::linearRand(glm::vec3(min), glm::vec3(max));

	return Vector3(aux.x, aux.y, aux.z);
}
