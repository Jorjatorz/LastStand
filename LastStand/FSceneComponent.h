#pragma once

#include <unordered_map>

#include "FComponent.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "Matrix4.h"

class FActor;

//Class that holds transformations. Can be attached to other FSceneComponents and also those can be attached to it.
//There are no shared components, if one component is child of other, it's only child of that one.
class FSceneComponent : public FComponent
{
public:
	//Updates world positions and REGISTER to parent (if exists)
	FSceneComponent(std::string name, FActor* parentActor);
	~FSceneComponent();

	//Overloaded setParent. Sets the nwe parent and register itself to the rootComponent of the new actor parent
	virtual void setParent(FActor* newParent) override;
	bool addChildrenComponent(FSceneComponent* children); //Adds childrens components to itself. Returns false if it already exists
	void removeChildrenComponent(std::string name); //Deletes a child.

	//Event
	virtual void onAttachedToComponent(); //Fired when the SceneComponent is attached to a new component paren
	virtual void onRemovedFromComponent(); //Fired when the SceneComponent is removed from a component

	//Modify the local transformation of the object. Updates the world transformation and notify to children.
	void setLocalTransformation(const Vector3& deltaPos, const Quaternion& deltaRot, const Vector3& deltaScale);
	//Sets the new local position of the component
	void setLocalPosition(const Vector3& pos);
	//Sets the new local orientation of the component
	void setLocalOrientation(const Quaternion& quat);
	//Sets the new local scale of the component
	void setLocalScale(const Vector3& scale);

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
	const Matrix4& getTransformationMatrix()
	{
		return _transformationMatrix;
	}

protected:
	//Parent of the FTransformationObject. Null if no parent
	FSceneComponent* _parentComponent;
	//Children map
	std::unordered_map<std::string, FSceneComponent*> _childrenComponentsList;

	void updateChildrensTransformationObjects(); //Updates all the childrens with the new transformations
	void getWorldTransformationsFromParent(); //Get the world transformation from the parent. If no parent then worldTrans = localTrans

	//Transformation attributes
	Vector3 _localPosition; //It's own position
	Vector3 _worldPosition; //Total position (localposition + parentposition)
	Quaternion _localRotationValue;
	Quaternion _worldRotationValue;
	Vector3 _localScaleValue;
	Vector3 _worldScaleValue;
	Matrix4 _transformationMatrix; //Matrix that represents the world transformations
};

