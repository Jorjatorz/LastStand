#include "FSpotLightComponent.h"


FSpotLightComponent::FSpotLightComponent(std::string name, FActor* actor)
	:FLightComponent(name, actor)
{
}


FSpotLightComponent::~FSpotLightComponent()
{
}

FLightComponent::lightTypeEnum FSpotLightComponent::getLightType()
{
	return FLightComponent::SPOTLIGHT;
}
