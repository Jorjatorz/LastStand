#pragma once

#include "FSceneComponent.h"
#include "Vector3.h"

//Base Class component representing a light source.
class FLightComponent: public FSceneComponent
{
public:
	FLightComponent(std::string name, FActor* actor);
	~FLightComponent();

private:
	//Intensity of the light source
	float _intensity;
	//Light color
	Vector3 _lightColor;
};

