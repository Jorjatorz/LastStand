#include "Math.h"

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "Matrix4.h"
#include "Quaternion.h"
#include "Vector3.h"

Math::Math()
{
}


Math::~Math()
{
}

Matrix4 Math::createPerspectiveMatrix(float fov, float aspectRatio, float zNear, float zFar)
{
	Matrix4 perspectiveM;
	if (zFar > 0.0)
	{
		perspectiveM._GLMMatrix = glm::perspective(fov, aspectRatio, zNear, zFar);
	}
	else
	{
		perspectiveM._GLMMatrix = glm::infinitePerspective(fov, aspectRatio, zNear);
	}

	return perspectiveM;
}

Matrix4 Math::getRotationMatrixFromQuaternion(const Quaternion& quat)
{
	Matrix4 mat;
	mat._GLMMatrix = glm::toMat4(quat._GLMQuat);

	return mat;
}

Matrix4 Math::createLookAtMatrix(const Vector3& eye, const Vector3& center, const Vector3& up)
{
	Matrix4 mat;
	mat._GLMMatrix = glm::lookAt(glm::vec3(eye.x, eye.y, eye.z), glm::vec3(center.x, center.y, center.z), glm::vec3(up.x, up.y, up.z));

	return mat;
}

Vector3 Math::cross(const Vector3& a, const Vector3& b)
{
	glm::vec3 a1(a.x, a.y, a.z);
	glm::vec3 b1(b.x, b.y, b.z);

	glm::vec3 c = glm::cross(a1, b1);

	return Vector3(c.x, c.y, c.z);
}
