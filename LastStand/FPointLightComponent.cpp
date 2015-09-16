#include "FPointLightComponent.h"


FPointLightComponent::FPointLightComponent(std::string name, FActor* actor)
	:FLightComponent(name, actor)
{
}


FPointLightComponent::~FPointLightComponent()
{
}

FLightComponent::lightTypeEnum FPointLightComponent::getLightType()
{
	return FLightComponent::POINTLIGHT;
}
