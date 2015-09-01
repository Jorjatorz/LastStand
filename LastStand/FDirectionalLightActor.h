#pragma once

#include "FLightActor.h"

class FDirectionalLightComponent;

class FDirectionalLightActor: public FLightActor
{
public:
	FDirectionalLightActor(std::string actorName);
	~FDirectionalLightActor();

};

