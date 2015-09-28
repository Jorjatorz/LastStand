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

	void setLightColor(const Vector3& color);
	void setIntensity(float newIntensity);

	float getIntensity()
	{
		return _intensity;
	}
	Vector3 getLightColor()
	{
		return _lightColor;
	}
	//Return the direction the light is facing. (useless for Pointlights sources)
	Vector3 getLightDirection()
	{
		return (_worldTransform.getRotationQuaternion() * Vector3::UNIT_FORWARD).getNormalizedVector();
	}

	enum lightTypeEnum
	{
		DIRECTIONALLIGHT,
		POINTLIGHT,
		SPOTLIGHT
	};
	virtual lightTypeEnum getLightType() = 0;

	bool hasChanged()
	{
		return _hasChanged;
	}
	//Tells the light component that his light information has been processed and saved (send to GPU, etc)
	void lightDataProcessed()
	{
		_hasChanged = false;
	}

protected:
	//Intensity of the light source
	float _intensity;
	//Light color
	Vector3 _lightColor;

	//True if the light information has changed.
	bool _hasChanged;

	//Light proxy - Created and deleted bu the component when de/attached
	FLightComponentProxy* _proxyOfComponent;
	//Creates the proxy of the light component
	void createProxyOfMySelf();

	void onAttachedToComponent();
	void onRemovedFromComponent();

};

