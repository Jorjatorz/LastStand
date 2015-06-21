#pragma once

#include <string>


class FPrimitiveComponent;

//Proxy of a primitive component that contains all the information needed by the FScene
//Each primitive component has its own derived proxy class
//Each proxy is created by the component when its attached and is destroyed when its removed.
class FPrimitiveComponentProxy
{
public:
	FPrimitiveComponentProxy(FPrimitiveComponent* mTarget);
	~FPrimitiveComponentProxy();

	std::string getProxyName();

	//Proxy function. Calls this function in its primitiveCompoentPtr
	virtual void drawDynamicElements() = 0;

protected:
	FPrimitiveComponent* _primitiveComponentPtr;
};

