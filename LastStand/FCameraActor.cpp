#include "FCameraActor.h"

#include "FCameraComponent.h"

FCameraActor::FCameraActor(std::string actorName)
	:FActor(actorName)
{
	//We create a new camera and insert it
	addComponentToRootComponent<FCameraComponent>(actorName + "_Camera");
}


FCameraActor::~FCameraActor()
{
}
