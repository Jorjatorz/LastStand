#pragma once

#include <string>
#include <unordered_map>

#include "Vector3.h"
#include "Quaternion.h"

//Class that holds transformations. Can be attached to other FTransformationObjects and also those can be attached to it.
//Every entity has one FTransformationObject. No FTransformationObject can go alone. Due to this property all FTransformationObject will have the same name as its attached entity.
class FTransformationObject
{
public:
	FTransformationObject(std::string name, FTransformationObject* parent = NULL);
	~FTransformationObject();

private:
	//Name of the FTransformationObject
	std::string _name;
	//Parent of the FTransformationObject. Null if no parent
	FTransformationObject* _parentTransformationObject;
	//Children map
	std::unordered_map<std::string, FTransformationObject> _childrenTransformationObjectsList;

	//Transformation attributes
	Vector3 _localPosition; //It's own position
	Vector3 _worldPosition; //Total position (localposition + parentposition)
	Quaternion _rotationValue;
	Vector3 _scaleValue;
};

