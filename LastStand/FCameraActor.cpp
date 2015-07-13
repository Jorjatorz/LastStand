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
	_rootComponent.translate(_rootComponent.getLocalRotation() * Vector3(delta.x, delta.y, -delta.z));
}

void FCameraActor::pitch(float degrees)
{
	//Calculate the new forward and if its Y axis si bigger than 0.999 (almost 1) we dont rotate (looking up or down, that why i use the absolute value)
	auto newForward = Quaternion(degrees * FEngine::getInstance()->getDeltaTime() / 1000.0f, _rootComponent.getWorldRotation() * Vector3(1.0, 0.0, 0.0)) * _rootComponent.getWorldRotation() * Vector3(0.0, 0.0, -1.0);
	if (abs(newForward.y)  < 0.999)
		rotate_LocalSpace(degrees, Vector3(1.0, 0.0, 0.0));
}
