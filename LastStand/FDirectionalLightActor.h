#pragma once

#include "FLightActor.h"

class FDirectionalLightActor: public FLightActor
{
public:
	FDirectionalLightActor(std::string actorName);
	~FDirectionalLightActor();

};

