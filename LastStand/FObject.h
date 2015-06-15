#pragma once

#include <string>

#include "FTransformationObject.h"

//Class that represents an object in the engine. Every object has a FTransformationObject and a name
class FObject
{
public:
	FObject(std::string name);
	~FObject();

	std::string getName()
	{
		return _name;
	}
	FTransformationObject getTransformCopy()
	{
		return _rootTransformationObject;
	}
	FTransformationObject* const getTransformPtr()
	{
		return &_rootTransformationObject;
	}

	//Add a new parent to the Object
	void attachToParent(FObject* parent);
	//Return the parent of the object. NULL if it doesnt exist
	FObject* getParent()
	{
		return _parentObject;
	}
	//Add a new component to the object
	void addComponent(FObject* component);
	//Remove a component from the object
	void removeComponent(std::string name);

	//Renders the object into the GBuffer. Every subclass can overload it
	void renderComponentToGBuffer()
	{
	}

protected:
	std::string _name;
	FTransformationObject _rootTransformationObject;

	FObject* _parentObject; //Null if is a root object
	std::unordered_map<std::string, FObject*> _componentsList; //List containing all the components attached to the object
};

