#pragma once

#include "FLightComponent.h"

class FPointLightComponent: public FLightComponent
{
public:
	FPointLightComponent(std::string name, FActor* actor);
	~FPointLightComponent();

	virtual lightTypeEnum getLightType();

};

