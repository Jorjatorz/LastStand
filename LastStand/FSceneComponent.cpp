#include "FSceneComponent.h"

#include "FEngine.h"
#include "FLog.h"
#include "FActor.h"
#include "Matrix4.h"

FSceneComponent::FSceneComponent(std::string name, FActor* parentActor)
	:FComponent(name, parentActor),
	_localPosition(0.0),
	_localRotation(),
	_localScale(1.0),
	_worldTransform()
{
}


FSceneComponent::~FSceneComponent()
{
	//Each component is in charge of deleting its childrens
	for (auto &it : _childrenComponentsList)
	{
		delete it.second;
	}
	_childrenComponentsList.clear();

	_parentComponent = NULL;
}

void FSceneComponent::updateChildrensTransformationObjects()
{
	for (auto const &it : _childrenComponentsList)
	{
		it.second->getWorldTransformationFromParent();
	}
}

void FSceneComponent::getWorldTransformationFromParent()
{
	if (_parentComponent)
	{
		FTransform aux;
		aux.accumulate(FTransform(_localPosition, _localRotation.toQuaternion(), _localScale));
		aux.accumulate(_parentComponent->_worldTransform);

		_worldTransform = aux;
	}
	else
	{
		_worldTransform = FTransform(_localPosition, _localRotation.toQuaternion(), _localScale);
	}

	updateChildrensTransformationObjects();
}

void FSceneComponent::setParent(FActor* newParent)
{
	if (_parentActor->getRootComponentPtr() == this)
	{
		FLog(FLog::ERROR, "Can't set a new parent to a root component: %s", _name.c_str());
		assert(0);
	}

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
	_localPosition = pos;

	//Update _world transformations
	getWorldTransformationFromParent();
}

void FSceneComponent::setLocalRotation(const Quaternion& quat)
{
	_localRotation = FRotator(quat);

	//Update _world transformations
	getWorldTransformationFromParent();
}

void FSceneComponent::setLocalScale(const Vector3& scale)
{
	_localScale = scale;

	//Update _world transformations
	getWorldTransformationFromParent();
}

const Matrix4& FSceneComponent::getTransformationMatrix()
{
	return _worldTransform.getTransformationMatrix();
}

void FSceneComponent::translate(const Vector3& delta)
{
	_localPosition += delta * (FEngine::getInstance()->getDeltaTime() / 1000.0f);

	//Update _world transformations
	getWorldTransformationFromParent();
}

void FSceneComponent::rotate_WorldSpace(float degrees, const Vector3& axisVector_WorldSpace)
{
	Quaternion deltaQuat(degrees * (FEngine::getInstance()->getDeltaTime() / 1000.0f), axisVector_WorldSpace);

	if (deltaQuat != Quaternion(1.0, 0.0, 0.0, 0.0))
	{
		_localRotation = (deltaQuat * _localRotation.toQuaternion()).toRotator();

		//Update _world transformations
		getWorldTransformationFromParent();
	}
}

void FSceneComponent::rotate_WorldSpace(const Quaternion& quat)
{
	if (quat != Quaternion(1.0, 0.0, 0.0, 0.0))
	{
		_localRotation = (quat * _localRotation.toQuaternion()).toRotator();

		//Update _world transformations
		getWorldTransformationFromParent();
	}

}

void FSceneComponent::rotate_LocalSpace(float degrees, const Vector3& axisVector_WorldSpace)
{
	Quaternion deltaQuat(degrees * (FEngine::getInstance()->getDeltaTime() / 1000.0f), _worldTransform.getRotationQuaternion() * axisVector_WorldSpace);
	
	if (deltaQuat != Quaternion(1.0, 0.0, 0.0, 0.0))
	{
		_localRotation = deltaQuat * _localRotation.toQuaternion();

		//Update _world transformations
		getWorldTransformationFromParent();
	}
}

void FSceneComponent::pitch(float degrees)
{
	_localRotation.addPitch(degrees * (FEngine::getInstance()->getDeltaTime() / 1000.0f));

	//Update _world transformations
	getWorldTransformationFromParent();
}

void FSceneComponent::yaw(float degrees)
{
	_localRotation.addYaw(degrees * (FEngine::getInstance()->getDeltaTime() / 1000.0f));

	//Update _world transformations
	getWorldTransformationFromParent();
}

void FSceneComponent::roll(float degrees)
{
	_localRotation.addRoll(degrees * (FEngine::getInstance()->getDeltaTime() / 1000.0f));

	//Update _world transformations
	getWorldTransformationFromParent();
}

void FSceneComponent::scale(const Vector3& delta)
{
	_localScale += delta; ///DElta time

	//Update _world transformations
	getWorldTransformationFromParent();
}
