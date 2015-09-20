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

void FPointLightActor::setAttenuationRadius(float rad)
{
	static_cast<FPointLightComponent*>(_lightComponentPtr)->setAttenuationRadius(rad);
}

float FPointLightActor::getAttenuationRadius()
{
	return static_cast<FPointLightComponent*>(_lightComponentPtr)->getAttenuationRadius();
}
