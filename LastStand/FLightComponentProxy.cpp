#include "FLightComponentProxy.h"

#include "FLightComponent.h"
#include "FPointLightComponent.h"

FLightComponentProxy::FLightComponentProxy(FLightComponent* target)
	:FComponentProxy(target)
{

}


FLightComponentProxy::~FLightComponentProxy()
{
}

float FLightComponentProxy::getIntensity()
{
	return static_cast<FLightComponent*>(_componentTarget)->getIntensity();
}

Vector3 FLightComponentProxy::getLightColor()
{
	return static_cast<FLightComponent*>(_componentTarget)->getLightColor();
}

Vector3 FLightComponentProxy::getLightDirection()
{
	return static_cast<FLightComponent*>(_componentTarget)->getLightDirection();
}

Vector3 FLightComponentProxy::getLightPosition()
{
	return static_cast<FLightComponent*>(_componentTarget)->getWorldPosition();
}

unsigned short int FLightComponentProxy::getLightType()
{
	return static_cast<FLightComponent*>(_componentTarget)->getLightType();
}

float FLightComponentProxy::getAttenuationRadius()
{
	///In here it should return 0 if the light is not  a point light. For now is faster to just leave it like that.
	return static_cast<FPointLightComponent*>(_componentTarget)->getAttenuationRadius();
}
