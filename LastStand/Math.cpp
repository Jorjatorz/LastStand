#include "Math.h"

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "Matrix4.h"

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
