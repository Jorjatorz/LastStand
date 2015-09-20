#include "FDirectionalLightComponent.h"


FDirectionalLightComponent::FDirectionalLightComponent(std::string name, FActor* actor)
	:FLightComponent(name, actor)
{
	setLocalOrientation(Vector3(0.0, -0.5, -0.5));
}


FDirectionalLightComponent::~FDirectionalLightComponent()
{
}

FLightComponent::lightTypeEnum FDirectionalLightComponent::getLightType()
{
	return FLightComponent::DIRECTIONALLIGHT;
}
