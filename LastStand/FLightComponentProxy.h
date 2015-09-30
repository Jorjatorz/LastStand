#pragma once

#include "FComponentProxy.h"

class FLightComponent;
class Vector3;

//Proxy class used by the scene to render the lights
class FLightComponentProxy: public FComponentProxy
{
public:
	FLightComponentProxy(FLightComponent* target);
	~FLightComponentProxy();

	bool hasChanged();
	void lightDataProcessed();

	float getIntensity();
	Vector3 getLightColor();
	Vector3 getLightDirection();
	Vector3 getLightPosition();
	///TODO - Pensar si incluir el componente y devovler la enumeracio en vez del entero
	unsigned short int getLightType();
	//Only for pointLights
	float getAttenuationRadius();
	

};

