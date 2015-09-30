#include "FCameraActor.h"

#include "Quaternion.h"
#include "Vector3.h"
#include "FEngine.h"
#include "Math.h"

FCameraActor::FCameraActor(std::string actorName)
	:FActor(actorName)
{
	//We create a new camera and insert it. It is set as root component
	_cameraComponentPtr = addComponent<FCameraComponent>(actorName + "_DefaultCameraComponent");;
}


FCameraActor::~FCameraActor()
{
}

void FCameraActor::setProjectionMode(FCameraComponent::ProjectionModeEnum newProj)
{
	static_cast<FCameraComponent*>(_cameraComponentPtr)->setProjectionMode(newProj);
}

FCameraComponent::ProjectionModeEnum FCameraActor::getProjectionMode()
{
	return static_cast<FCameraComponent*>(_cameraComponentPtr)->getProjectionMode();
}
