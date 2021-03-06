#include "FLightActor.h"

#include "FLightComponent.h"

FLightActor::FLightActor(std::string actorName)
	:FActor(actorName)
{
}


FLightActor::~FLightActor()
{
}

void FLightActor::setLightColor(const Vector3& color)
{
	_lightComponentPtr->setLightColor(color);
}

Vector3 FLightActor::getLightColor()
{
	return _lightComponentPtr->getLightColor();
}

void FLightActor::setIntensity(float intensity)
{
	_lightComponentPtr->setIntensity(intensity);
}

float FLightActor::getIntensity()
{
	return _lightComponentPtr->getIntensity();
}
