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

	//Ticks the component every frame. Can do some logic inside it. 
	//By default is empty.
	virtual void tick(float deltaTime)
	{}

	//Sets the new parent. But this method does not register the component inside the parent (This is done by the overloaded setParent at FTransformationComponent or manually)
	virtual void setParent(FActor* newParent);

protected:
	//Actor that the component is attached to
	FActor* _parentActor;

};

