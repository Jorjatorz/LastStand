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

	Vector3 getLightColor();

protected:
	FLightComponent* _lightComponentPtr;
};

