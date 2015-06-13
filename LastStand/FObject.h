#pragma once

#include <string>

#include "FTransformationObject.h"

//Class that represents an object in the engine. Every object has a FTransformationObject and a name
class FObject
{
public:
	FObject(std::string name, FTransformationObject* parentTransformation = NULL);
	~FObject();

protected:
	std::string _name;
	FTransformationObject _rootTransformationObject;
};

