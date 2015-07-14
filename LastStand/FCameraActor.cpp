#include "FCameraActor.h"

#include "FCameraComponent.h"
#include "Quaternion.h"
#include "Vector3.h"
#include "FEngine.h"

FCameraActor::FCameraActor(std::string actorName)
	:FActor(actorName)
{
	//We create a new camera and insert it
	addComponent<FCameraComponent>(actorName + "_Camera");
}


FCameraActor::~FCameraActor()
{
}

void FCameraActor::translate(const Vector3& delta)
{
	_rootComponent.translate(_rootComponent.getLocalRotationQuaternion() * Vector3(delta.x, delta.y, -delta.z));
}

void FCameraActor::pitch(float degrees)
{
	//rotate_LocalSpace(degrees, Vector3(1.0, 0.0, 0.0));
	_rootComponent.pitch(degrees);
}
