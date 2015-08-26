#pragma once

#include "FLightComponent.h"

//Component that creates a directional light. This light illuminates in a direction from an infinite source point.
class FDirectionalLightComponent: public FLightComponent
{
public:
	FDirectionalLightComponent(std::string name, FActor* actor);
	~FDirectionalLightComponent();

	virtual void createProxyOfMySelf();

	virtual void onAttachedToComponent();
	virtual void onRemovedFromComponent();

};

