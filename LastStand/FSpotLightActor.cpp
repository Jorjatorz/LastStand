#include "FSpotLightActor.h"

#include "FSpotLightComponent.h"

FSpotLightActor::FSpotLightActor(std::string actorName)
	:FLightActor(actorName)
{
	_lightComponentPtr = addComponent<FSpotLightComponent>("DefaultSpotLightComponent_" + _name);
}


FSpotLightActor::~FSpotLightActor()
{
}
