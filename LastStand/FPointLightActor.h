#pragma once

#include "FLightActor.h"

class FPointLightActor : public FLightActor
{
public:
	FPointLightActor(std::string actorName);
	~FPointLightActor();

	void setAttenuationRadius(float rad);
	float getAttenuationRadius();
};

