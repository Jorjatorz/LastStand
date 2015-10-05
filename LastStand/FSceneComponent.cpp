#include "FSceneComponent.h"

#include "FLog.h"
#include "FActor.h"
#include "Matrix4.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "Math.h"

FSceneComponent::FSceneComponent(std::string name, FActor* parentActor)
	:FComponent(name, parentActor),
	_localTransform(),
	_worldTransform()
{
}


FSceneComponent::~FSceneComponent()
{
	//Each component is in charge of deleting its childrens
	for (auto &it : _childrenComponentsList)
	{
		it.second->onRemovedFromComponent();
		delete it.second;
	}
	_childrenComponentsList.clear();

	_parentComponent = NULL;
}

void FSceneComponent::getWorldTransformationFromParent()
{
	if (_parentComponent)
	{
		FTransform aux;
		aux.setRotation(_parentComponent->getWorldRotationQuaternion() * _localTransform.getRotationQuaternion());
		aux.setScale(_localTransform.getScale() * _parentComponent->getWorldScale());
		//Change position based on parent orientation and scale
		aux.setPosition(_parentComponent->getWorldRotationQuaternion() * (_parentComponent->getWorldScale() * _localTransform.getPosition()));
		aux.setPosition(aux.getPosition() + _parentComponent->getWorldPosition());

		_worldTransform = aux;
	}
	else
	{
		_worldTransform = _localTransform;		
	}

	updateChildrensTransformationObjects();
}

void FSceneComponent::updateChildrensTransformationObjects()
{
	for (auto const &it : _childrenComponentsList)
	{
		it.second->getWorldTransformationFromParent();
	}
}

void FSceneComponent::setOwner(FActor* newParent)
{
	if (_ownerActor->getRootComponentPtr() == this)
	{
		FLog(FLog::FAILURE, "Can't set a new parent to a root component: %s", _name.c_str());
		assert(0);
	}
	//If we have a parent component remove this component from it as we are hanging of actor.
	if (_parentComponent)
	{
		_parentComponent->removeChildrenComponent(_name);
	}
	//Register in the FActor
	newParent->addComponent(this);
	FComponent::setOwner(newParent); //Update our parent reference.
}

bool FSceneComponent::addChildrenComponent(FSceneComponent* children)
{
	auto it = _childrenComponentsList.find(children->_name);

	if (it == _childrenComponentsList.end())
	{
		_childrenComponentsList.insert(std::make_pair(children->_name, children));
		children->_parentComponent = this;

		//Update children location
		children->getWorldTransformationFromParent();
		//Fire attached event
		children->onAttachedToComponent();
	}
	else
	{
		FLog(FLog::WARNING, "Component already exists in " + _name + ", can't add it: %s", children->getName().c_str());
		return false;
	}

	return true;
}

void FSceneComponent::removeChildrenComponent(std::string name)
{
	auto it = _childrenComponentsList.find(name);

	if (it != _childrenComponentsList.end())
	{
		//Fire onRemovedFromComponent before deleting the component
		it->second->onRemovedFromComponent();
		//As components are not shared if we remove it we have to delete it.
		delete it->second;
		_childrenComponentsList.erase(name);
	}
	else
	{
		FLog(FLog::WARNING, "Component doesn't exists in " + _name + ", can't remove it: %s", name.c_str());
	}
}


void FSceneComponent::onAttachedToComponent()
{
}

void FSceneComponent::onRemovedFromComponent()
{
}

void FSceneComponent::setLocalPosition(const Vector3& pos)
{
	_localTransform.setPosition(pos);

	//Update _world transformations
	getWorldTransformationFromParent();
}

void FSceneComponent::setLocalRotation(const Quaternion& quat)
{
	_localTransform.setRotation(quat);

	//Update _world transformations
	getWorldTransformationFromParent();
}

void FSceneComponent::setLocalRotation(const FRotator& rotator)
{
	_localTransform.setRotation(rotator.toQuaternion());

	//Update _world transformations
	getWorldTransformationFromParent();
}

void FSceneComponent::setLocalRotation(const Vector3& euler)
{
	_localTransform.setRotation(Quaternion(euler));

	//Update _world transformations
	getWorldTransformationFromParent();
}

void FSceneComponent::setLocalOrientation(const Vector3& newDirection)
{
	/*///TODO - Corregir lo de detectar si son iguales, no funciona.
	//The default orientation is (0, 0, -1) which is represented by the Identity Quaternion
	Vector3 currentDirection = (getWorldRotationQuaternion() * Vector3::UNIT_FORWARD).getNormalizedVector();
	Vector3 newDirectionNormalized = newDirection.getNormalizedVector();
	//Check if the curernt orientation and new direction are the same.
	//If they are not, rotate.
	if ((Vector3::length(currentDirection - newDirectionNormalized) > 0.000009f))
	{
		//Angle between the directions
		float angle = Math::arcCos(Vector3::dot(currentDirection, newDirectionNormalized));
		//Get the rotation axis, which will be a vector perpendicular to both directions
		Vector3 rotationAxis;
		if (angle > 179.00009f)
		{
			//Special case in which the rotation is of 180, infinite posibilities so we choose one.
			rotationAxis = Vector3::cross(Vector3(0.0, 0.0, 1.0), newDirectionNormalized);
			//We choose bad axis to do the cross, try with another
			if (rotationAxis == Vector3(0.0, 0.0, 0.0))
			{
				rotationAxis = Vector3::cross(Vector3(1.0, 0.0, 0.0), newDirectionNormalized);
			}
		}
		else
		{
			rotationAxis = Vector3::cross(currentDirection, newDirectionNormalized);
		}

		setComponentRotation(Quaternion(angle, rotationAxis.getNormalizedVector()));
	}*/

	Vector3 normalizedNewDirection = newDirection.getNormalizedVector();
	if (normalizedNewDirection != Vector3::UNIT_FORWARD)
	{
		//Angle between the directions
		float angle = Math::arcCos(Vector3::dot(Vector3::UNIT_FORWARD, normalizedNewDirection));
		//Get the rotation axis, which will be a vector perpendicular to both directions
		Vector3 rotationAxis;
		if (angle > 179.00009f)
		{
			//Special case in which the rotation is of 180, infinite posibilities so we choose one.
			rotationAxis = Vector3::cross(Vector3(0.0, 0.0, 1.0), normalizedNewDirection);
			//We choose bad axis to do the cross, try with another
			if (rotationAxis == Vector3(0.0, 0.0, 0.0))
			{
				rotationAxis = Vector3::cross(Vector3(1.0, 0.0, 0.0), normalizedNewDirection);
			}
		}
		else
		{
			rotationAxis = Vector3::cross(Vector3::UNIT_FORWARD, normalizedNewDirection);
		}

		setComponentRotation(Quaternion(angle, rotationAxis.getNormalizedVector()));
	}
	else
	{
		//Identity quaternion
		setComponentRotation(Quaternion());
	}
}

void FSceneComponent::setLocalScale(const Vector3& scale)
{
	_localTransform.setScale(scale);

	//Update _world transformations
	getWorldTransformationFromParent();
}

void FSceneComponent::setPitchAngle(float degrees)
{
	FRotator rot(_localTransform.getRotationQuaternion());
	rot.setPitch(degrees);

	_localTransform.setRotation(rot.toQuaternion());

	//Update _world transformations
	getWorldTransformationFromParent();
}

void FSceneComponent::setYawAngle(float degrees)
{
	FRotator rot(_localTransform.getRotationQuaternion());
	rot.setYaw(degrees);

	_localTransform.setRotation(rot.toQuaternion());

	//Update _world transformations
	getWorldTransformationFromParent();
}

void FSceneComponent::setRollAngle(float degrees)
{
	FRotator rot(_localTransform.getRotationQuaternion());
	rot.setRoll(degrees);

	_localTransform.setRotation(rot.toQuaternion());

	//Update _world transformations
	getWorldTransformationFromParent();
}


const Matrix4& FSceneComponent::getTransformationMatrix()
{
	return _worldTransform.getTransformationMatrix();
}

void FSceneComponent::translate(const Vector3& delta)
{
	_localTransform.translate(delta);

	//Update _world transformations
	getWorldTransformationFromParent();
}

void FSceneComponent::rotate_WorldSpace(float degrees, const Vector3& axisVector_WorldSpace)
{
	Quaternion deltaQuat(degrees,  axisVector_WorldSpace);
	deltaQuat.normalize();
	if (deltaQuat != Quaternion(1.0, 0.0, 0.0, 0.0))
	{
		setComponentRotation(_localTransform.getRotationQuaternion() * getWorldRotationQuaternion().inverse() * deltaQuat * getWorldRotationQuaternion());
	}
}

void FSceneComponent::rotate_WorldSpace(const Quaternion& quat)
{
	if (quat != Quaternion(1.0, 0.0, 0.0, 0.0))
	{
		setComponentRotation(_localTransform.getRotationQuaternion() * getWorldRotationQuaternion().inverse() * quat * getWorldRotationQuaternion());
	}

}

void FSceneComponent::rotate_LocalSpace(float degrees, const Vector3& axisVector_WorldSpace)
{
	Quaternion deltaQuat(degrees, axisVector_WorldSpace);
	deltaQuat.normalize();	
	if (deltaQuat != Quaternion(1.0, 0.0, 0.0, 0.0))
	{
		setComponentRotation(_localTransform.getRotationQuaternion() * deltaQuat);
	}
}

void FSceneComponent::setComponentRotation(const Quaternion& newRot)
{
	if (newRot != _worldTransform.getRotationQuaternion())
	{
		_localTransform.setRotation(newRot);
	}

	//Update _world transformations
	getWorldTransformationFromParent();
}

void FSceneComponent::scale(const Vector3& delta)
{
	_localTransform.scale(delta);

	//Update _world transformations
	getWorldTransformationFromParent();
}