#include "FPointLightComponent.h"


FPointLightComponent::FPointLightComponent(std::string name, FActor* actor)
	:FLightComponent(name, actor),
	_attenuationRadius(1.0f)
{
}


FPointLightComponent::~FPointLightComponent()
{
}

FLightComponent::lightTypeEnum FPointLightComponent::getLightType()
{
	return FLightComponent::POINTLIGHT;
}

void FPointLightComponent::setAttenuationRadius(float radius)
{
	_attenuationRadius = radius;
}
