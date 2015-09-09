#pragma once

#include <unordered_map>

#include "FComponent.h"
#include "FTransform.h"
#include "FRotator.h"

class Matrix4;
class Vector3;
class Quaternion;

//Class that holds transformations. Can be attached to other FSceneComponents and also those can be attached to it.
//There are no shared components, if one component is child of other, it's only child of that one.
class FSceneComponent : public FComponent
{
public:
	//Updates world positions and REGISTER to parent (if exists)
	FSceneComponent(std::string name, FActor* parentActor);
	~FSceneComponent();

	//Overloaded setParent. Sets the nwe parent and register itself to the rootComponent of the new actor parent
	virtual void setOwner(FActor* newParent) override;
	bool addChildrenComponent(FSceneComponent* children); //Adds childrens components to itself. Returns false if it already exists
	void removeChildrenComponent(std::string name); //Deletes a child.

	//Event
	virtual void onAttachedToComponent(); //Fired when the SceneComponent is attached to a new component paren
	virtual void onRemovedFromComponent(); //Fired when the SceneComponent is removed from a component

	//Modify the local transformation of the object. Updates the world transformation and notify to children.
	void translate(const Vector3& delta);
	void rotate_WorldSpace(const Quaternion& quat); //Rotates the component in world coordinates
	void rotate_WorldSpace(float degrees, const Vector3& axisVector_WorldSpace); //Rotates the component given an angle and an axisVector in global space
	void rotate_LocalSpace(float degrees, const Vector3& axisVector_WorldSpace); //Rotates the component given an angle and an axisVector given in global space. Then this axis vector in translated into a local space axis.
	void scale(const Vector3& delta); //World space

	//Sets the new local position of the component
	void setLocalPosition(const Vector3& pos);
	//Sets the new local orientation of the component from a quaternion
	void setLocalRotation(const Quaternion& quat);
	//Sets the new local orientation of the component from a FRotator
	void setLocalRotation(const FRotator& rotator);
	//Sets the new local orientation of the component from an Euler angles Vector
	void setLocalRotation(const Vector3& euler);
	//Set Local Orientation - Makes the object face in a given direction (unit vector), similar to a LookAt
	void setLocalOrientation(const Vector3& newDirection);
	//Sets new axis value
	void setPitchAngle(float degrees);
	void setYawAngle(float degrees);
	void setRollAngle(float degrees);
	//Sets the new local scale of the component
	void setLocalScale(const Vector3& scale);

	Vector3 getLocalPosition()
	{
		return _localTransform.getPosition();
	}
	Vector3 getWorldPosition()
	{
		return _worldTransform.getPosition();
	}
	Quaternion getLocalRotationQuaternion()
	{
		return _localTransform.getRotationQuaternion();
	}
	FRotator getLocalRotation()
	{
		return _localTransform.getRotationQuaternion().toRotator();
	}
	Quaternion getWorldRotationQuaternion()
	{
		return _worldTransform.getRotationQuaternion();
	}
	FRotator getWorldRotation()
	{
		return _worldTransform.getRotationQuaternion().toRotator();
	}
	Vector3 getLocalScale()
	{
		return _localTransform.getScale();
	}
	Vector3 getWorldScale()
	{
		return _worldTransform.getScale();
	}
	const Matrix4& getTransformationMatrix();

protected:
	//Parent of the FTransformationObject. Null if no parent
	FSceneComponent* _parentComponent;
	//Children map
	std::unordered_map<std::string, FSceneComponent*> _childrenComponentsList;

	void updateChildrensTransformationObjects(); //Updates all the childrens with the new transformations
	void getWorldTransformationFromParent(); //Get the world transformation from the parent. If no parent then worldTrans = localTrans

	//Transformation attributes
	FTransform _localTransform;

	FTransform _worldTransform; //Represents the component world transform

	//Override for custom
	virtual void setComponentRotation(const Quaternion& newRot);
};

