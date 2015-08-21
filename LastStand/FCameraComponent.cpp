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
	_projectionMode(PERSPECTIVE),
	_viewCameraMatrix(1.0)
{
	//Set the projection matrix
	_projectionCameraMatrix = Matrix4::createPerspectiveMatrix(_FOV, _aspectRatio, 0.001);
	//Register to the camera manager
	FEngine::getInstance()->getPlayerController()->getCameraManagerPtr()->registerCameraComponent(this);
}


FCameraComponent::~FCameraComponent()
{
	//Unregister to the camera manager
	FEngine::getInstance()->getPlayerController()->getCameraManagerPtr()->unregisterCameraComponent(this);
}

void FCameraComponent::addRenderingTarget(Texture* texture2DTarget)
{
	_renderTargetPtr = texture2DTarget;
}

void FCameraComponent::getCameraProjectionAndViewMatricesPtr(Matrix4* &projM, Matrix4* &viewM)
{
	projM = &_projectionCameraMatrix;

	//Get the rotation matrix of the conjugate of the rotation quaternion and translate it by the negative position
	_viewCameraMatrix = Math::getRotationMatrixFromQuaternion(_worldTransform.getRotationQuaternion().conjugate());
	_viewCameraMatrix.translate(-_worldTransform.getPosition());
	
	viewM = &_viewCameraMatrix;
}

void FCameraComponent::setAsViewportCamera()
{
	FEngine::getInstance()->getPlayerController()->getCameraManagerPtr()->setViewportCamera(this);
}