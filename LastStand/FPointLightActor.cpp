#include "FPointLightActor.h"

#include "FPointLightComponent.h"

FPointLightActor::FPointLightActor(std::string actorName)
	:FLightActor(actorName)
{
	_lightComponentPtr = addComponent<FPointLightComponent>("DefaultPointLightComponent_" + _name);
}


FPointLightActor::~FPointLightActor()
{
}
