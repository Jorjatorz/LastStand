#pragma once

#include <string>

#include "FComponentProxy.h"

class FPrimitiveComponent;

//Proxy of a primitive component that contains all the information needed by the FScene
//Each primitive component has its own derived proxy class
//Each proxy is created by the component when its attached and is destroyed when its removed.
class FPrimitiveComponentProxy : public FComponentProxy
{
public:
	FPrimitiveComponentProxy(FPrimitiveComponent* mTarget);
	~FPrimitiveComponentProxy();

	//Proxy function. Calls this function in its primitiveCompoentPtr
	virtual void drawDynamicElements() = 0;
};

