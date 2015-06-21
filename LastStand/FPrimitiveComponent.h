#pragma once

#include "FSceneComponent.h"

class FPrimitiveComponentProxy;

//Component that has a rendering and physics representation.
class FPrimitiveComponent : public FSceneComponent
{
public:
	FPrimitiveComponent(std::string name, FActor* actor);
	~FPrimitiveComponent();

	//Renders the information to the Buffer
	//Warning!! should be called from the Proxy from the render
	virtual void drawDynamicElements() = 0;

	virtual void onAttachedToComponent();

	virtual void onRemovedFromComponent();

protected:
	FPrimitiveComponentProxy* _proxyOfComponent;
	//Creates the proxy
	virtual void createProxyOfMySelf() = 0;

};

