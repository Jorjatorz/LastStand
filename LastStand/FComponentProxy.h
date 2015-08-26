#pragma once

#include <string>

class FComponent;

//Base class that represents a proxy of a component
class FComponentProxy
{
public:
	FComponentProxy(FComponent* proxyTarget);
	~FComponentProxy();

	//Returns the name of the proxy. (Which is the same as the name of the component)
	std::string getProxyName();

protected:
	FComponent* _componentTarget;
};

