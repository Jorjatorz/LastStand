#include "FCameraActor.h"

#include "FCameraComponent.h"
#include "Quaternion.h"
#include "Vector3.h"

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
	_rootComponent.setLocalTransformation(_rootComponent.getWolrdOrientation() * Vector3(1.0, 1.0, -1.0) * delta, Quaternion(), Vector3(1.0));
}
