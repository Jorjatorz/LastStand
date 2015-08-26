#include "FLightComponent.h"

FLightComponent::FLightComponent(std::string name, FActor* actor)
	:FSceneComponent(name, actor),
	_intensity(5000.0),
	_lightColor(1.0),
	_proxyOfComponent(NULL)
{

}


FLightComponent::~FLightComponent()
{
}
