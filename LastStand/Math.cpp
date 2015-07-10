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



Matrix4 Math::getRotationMatrixFromQuaternion(const Quaternion& quat)
{
	Matrix4 mat;
	mat._GLMMatrix = glm::toMat4(quat._GLMQuat);

	return mat;
}


