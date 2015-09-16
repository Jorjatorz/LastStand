#pragma once

#include "FLightComponent.h"

//Component that creates a spot light. This light illuminates in a direction from a discrete source point in world.
class FSpotLightComponent : public FLightComponent
{
public:
	FSpotLightComponent(std::string name, FActor* actor);
	~FSpotLightComponent();

	virtual lightTypeEnum getLightType();

};

