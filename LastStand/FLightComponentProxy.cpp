#include "FLightComponentProxy.h"

#include "FLightComponent.h"

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
