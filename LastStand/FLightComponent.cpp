#include "FLightComponent.h"

FLightComponent::FLightComponent(std::string name, FActor* actor)
	:FSceneComponent(name, actor),
	_intensity(10.0),
	_lightColor(1.0)
{

}


FLightComponent::~FLightComponent()
{
}
