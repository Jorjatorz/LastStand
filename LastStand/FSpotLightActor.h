#pragma once

#include "FLightActor.h"

class FSpotLightActor : public FLightActor
{
public:
	FSpotLightActor(std::string actorName);
	~FSpotLightActor();
};

