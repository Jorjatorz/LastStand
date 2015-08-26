#pragma once

#include "FSceneComponent.h"
#include "Vector3.h"

class FLightComponentProxy;

//Base Class component representing a light source.
class FLightComponent: public FSceneComponent
{
public:
	FLightComponent(std::string name, FActor* actor);
	~FLightComponent();

	void setLightColor(const Vector3& color)
	{
		_lightColor = color;
	}
	void setIntensity(float newIntensity)
	{
		_intensity = newIntensity;
	}

	float getIntensity()
	{
		return _intensity;
	}
	Vector3 getLightColor()
	{
		return _lightColor;
	}

protected:
	//Intensity of the light source
	float _intensity;
	//Light color
	Vector3 _lightColor;

	//Light proxy - Created and deleted bu the component when de/attached
	FLightComponentProxy* _proxyOfComponent;
	//Creates the proxy
	virtual void createProxyOfMySelf() = 0;
};

