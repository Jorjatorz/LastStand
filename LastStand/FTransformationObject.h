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
	//Updates world positions and REGISTER to parent (if exists)
	FTransformationObject(std::string name);
	~FTransformationObject();

	void addChildrenTranformationObject(FTransformationObject* children);
	void removeChildrenTransformationObject(std::string name);

	//Modify the local transformation of the object. Updates the world transformation and notify to children.
	void setLocalTransformation(const Vector3& deltaPos, const Quaternion& deltaRot, const Vector3& deltaScale);

	Vector3 getLocalPosition()
	{
		return _localPosition;
	}
	Vector3 getWorldPosition()
	{
		return _worldPosition;
	}
	Quaternion getLocalOrientation()
	{
		return _localRotationValue;
	}
	Quaternion getWolrdOrientation()
	{
		return _worldRotationValue;
	}
	Vector3 getLocalScale()
	{
		return _localScaleValue;
	}
	Vector3 getWorldScale()
	{
		return _worldScaleValue;
	}

private:
	//Name of the FTransformationObject
	std::string _name;
	//Parent of the FTransformationObject. Null if no parent
	FTransformationObject* _parentTransformationObject;
	//Children map
	std::unordered_map<std::string, FTransformationObject*> _childrenTransformationObjectsList;
	void updateChildrensTransformationObjects(); //Updates all the childrens with the new transformations
	void getWorldTransformationsFromParent(); //Get the world transformation from the parent. If no parent then worldTrans = localTrans

	//Transformation attributes
	Vector3 _localPosition; //It's own position
	Vector3 _worldPosition; //Total position (localposition + parentposition)
	Quaternion _localRotationValue;
	Quaternion _worldRotationValue;
	Vector3 _localScaleValue;
	Vector3 _worldScaleValue;
};

