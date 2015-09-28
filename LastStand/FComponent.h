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

	//Ticks the component every frame. Only called if _objectCanTick is true
	//By default is empty.
	void tickComponent(float deltaTime);
	//Sets if the component cant tick per frame or not
	void setComponentTick(bool canTick);
	bool canComponentTick()
	{
		return _componentCanTick;
	}

	//Sets the new owner actor. But this method does not register the component inside the parent (This is done by the overloaded setParent at FSceneComponent or manually)
	virtual void setOwner(FActor* newOwner);
	//Return the owner actor
	FActor* getOwner()
	{
		return _ownerActor;
	}

protected:
	//Actor that the component is attached to
	FActor* _ownerActor;

	//True if the component can tick per frame. False by default.
	bool _componentCanTick;

};

