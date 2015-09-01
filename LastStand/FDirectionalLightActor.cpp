#include "FDirectionalLightActor.h"

#include "FDirectionalLightComponent.h"

FDirectionalLightActor::FDirectionalLightActor(std::string actorName)
	:FLightActor(actorName)
{
	_lightComponentPtr = addComponent<FDirectionalLightComponent>("DefaultDirectionalLightComponent_" + _name);
}


FDirectionalLightActor::~FDirectionalLightActor()
{
}
