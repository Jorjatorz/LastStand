#include "FCameraComponent.h"

#include "FEngine.h"
#include "FCameraManager.h"
#include "Math.h"
#include "FPlayerController.h"


FCameraComponent::FCameraComponent(std::string name, FActor* actor)
	:FSceneComponent(name, actor),
	_renderTargetPtr(NULL),
	_FOV(90.0),
	_aspectRatio(FEngine::getInstance()->getRenderingWindow_Width() / (float)FEngine::getInstance()->getRenderingWindow_Height()),
	_orthoWidth(1),
	_orthoHeight(1),
	_projectionMode(PERSPECTIVE),
	_minimumRenderDistance(0.001),
	_maximumRenderDistance(-1.0),
	_viewCameraMatrix(1.0),
	_projectionCameraMatrix(1.0)
{
	//Set the projection matrix
	setupProjectionMatrix();
	//Register to the camera manager
	FEngine::getInstance()->getPlayerController()->getCameraManagerPtr()->registerCameraComponent(this);
}


FCameraComponent::~FCameraComponent()
{
	//Unregister to the camera manager
	FEngine::getInstance()->getPlayerController()->getCameraManagerPtr()->unregisterCameraComponent(this);
}

void FCameraComponent::setRenderingTarget(Texture* texture2DTarget)
{
	_renderTargetPtr = texture2DTarget;
}

void FCameraComponent::getCameraProjectionAndViewMatricesPtr(Matrix4* &projM, Matrix4* &viewM, Vector3& cameraPosition)
{
	projM = &_projectionCameraMatrix;

	//Get the rotation matrix of the conjugate of the rotation quaternion and translate it by the negative position
	_viewCameraMatrix = Math::getRotationMatrixFromQuaternion(_worldTransform.getRotationQuaternion().conjugate());
	_viewCameraMatrix.translate(-_worldTransform.getPosition());
	
	viewM = &_viewCameraMatrix;

	cameraPosition = _worldTransform.getPosition();
}

void FCameraComponent::setAsViewportCamera()
{
	FEngine::getInstance()->getPlayerController()->getCameraManagerPtr()->setViewportCamera(this);
}

void FCameraComponent::setProjectionMode(ProjectionModeEnum newProj)
{
	_projectionMode = newProj;

	setupProjectionMatrix();
}

FCameraComponent::ProjectionModeEnum FCameraComponent::getProjectionMode()
{
	return _projectionMode;
}

void FCameraComponent::setupProjectionMatrix()
{
	if (_projectionMode == PERSPECTIVE)
	{
		if (_maximumRenderDistance <= 0)
		{
			_projectionCameraMatrix = Matrix4::createPerspectiveMatrix(_FOV, _aspectRatio, _minimumRenderDistance);
		}
		else
		{
			_projectionCameraMatrix = Matrix4::createPerspectiveMatrix(_FOV, _aspectRatio, _minimumRenderDistance, _maximumRenderDistance);
		}
	}
	else
	{
		///TODO - Meter una variable solo para el zfar del ortografico??
		_projectionCameraMatrix = Matrix4::createOrthoMatrix(_orthoWidth, _orthoHeight, _minimumRenderDistance, 1000.0f);
	}
}
