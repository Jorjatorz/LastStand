#pragma once

#include "FActor.h"

class FLightComponent;
class Vector3;

//Abstract Base class for the different types of lights actors
class FLightActor: public FActor
{
public:
	FLightActor(std::string actorName);
	~FLightActor();

	void setLightColor(const Vector3& color);
	void setIntensity(float intensity);

	Vector3 getLightColor();
	float getIntensity();

protected:
	FLightComponent* _lightComponentPtr;
};

