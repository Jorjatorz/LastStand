#pragma once

#include "FSceneComponent.h"

class FPrimitiveComponentProxy;

//Component that has a rendering and physics representation. (It can be rendered and collide)
class FPrimitiveComponent : public FSceneComponent
{
public:
	FPrimitiveComponent(std::string name, FActor* actor);
	~FPrimitiveComponent();

	//Renders the information to the Buffer
	//Warning!! should be called from the Proxy from the render
	virtual void drawDynamicElements() = 0;

	virtual void onAttachedToComponent() override;

	virtual void onRemovedFromComponent() override;

protected:
	//Light proxy - Created and deleted bu the component when de/attached
	FPrimitiveComponentProxy* _proxyOfComponent;
	//Creates the proxy
	virtual void createProxyOfMySelf() = 0;

};

