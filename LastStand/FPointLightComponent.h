#pragma once

#include "FLightComponent.h"

class FPointLightComponent: public FLightComponent
{
public:
	FPointLightComponent(std::string name, FActor* actor);
	~FPointLightComponent();

	virtual lightTypeEnum getLightType();

	void setAttenuationRadius(float radius);
	float getAttenuationRadius() const
	{
		return _attenuationRadius;
	}

private:
	//Defines the radius that defines the light volume. (Bigger radius more expensive the light is)
	float _attenuationRadius;

};

