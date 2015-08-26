#pragma once

#include "FComponentProxy.h"

class FLightComponent;

//Proxy class used by the scene to render the lights
class FLightComponentProxy: public FComponentProxy
{
public:
	FLightComponentProxy(FLightComponent* target);
	~FLightComponentProxy();
};

