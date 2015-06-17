#pragma once

#include <string>

#include "FObject.h"

class FActor;

//Base class for all components
class FComponent : public FObject
{
public:
	FComponent(std::string name, FActor* actorP);
	~FComponent();

	//Sets the new parent. But this not register the component to the parent. (This is done by the overloaded setParent at FTransformationComponent or manually)
	virtual void setParent(FActor* newParent);

protected:
	//Actor that the component is attached to
	FActor* _parentActor;

};

