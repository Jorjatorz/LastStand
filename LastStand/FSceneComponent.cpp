#include "FSceneComponent.h"

#include "FLog.h"
#include "FActor.h"
#include "Matrix4.h"
#include "Vector3.h"
#include "Quaternion.h"

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

void FSceneComponent::setParent(FActor* newParent)
{
	if (_parentActor->getRootComponentPtr() == this)
	{
		FLog(FLog::ERROR, "Can't set a new parent to a root component: %s", _name.c_str());
		assert(0);
	}
	//If we have a parent component remove this component from it as we are hanging of actor.
	if (_parentComponent)
	{
		_parentComponent->removeChildrenComponent(_name);
	}
	//Register in the FActor
	newParent->addComponent(this);
	FComponent::setParent(newParent); //Update our parent reference.
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
		rotateComponent(_localTransform.getRotationQuaternion() * getWorldRotationQuaternion().inverse() * deltaQuat * getWorldRotationQuaternion());
	}
}

void FSceneComponent::rotate_WorldSpace(const Quaternion& quat)
{
	if (quat != Quaternion(1.0, 0.0, 0.0, 0.0))
	{
		rotateComponent(_localTransform.getRotationQuaternion() * getWorldRotationQuaternion().inverse() * quat * getWorldRotationQuaternion());
	}

}

void FSceneComponent::rotate_LocalSpace(float degrees, const Vector3& axisVector_WorldSpace)
{
	Quaternion deltaQuat(degrees, axisVector_WorldSpace);
	deltaQuat.normalize();	
	if (deltaQuat != Quaternion(1.0, 0.0, 0.0, 0.0))
	{
		rotateComponent(_localTransform.getRotationQuaternion() * deltaQuat);
	}
}

void FSceneComponent::rotateComponent(const Quaternion& newRot)
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
