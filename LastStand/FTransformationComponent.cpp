#include "FTransformationComponent.h"

#include "FLog.h"
#include "FActor.h"

FTransformationComponent::FTransformationComponent(std::string name, FActor* parentActor)
	:FComponent(name, parentActor),
	_localPosition(0.0),
	_localRotationValue(),
	_localScaleValue(1.0)
{
	getWorldTransformationsFromParent(); //Update variables
}


FTransformationComponent::~FTransformationComponent()
{
	//Each component is in charge of deleting its childrens
	for (auto it : _childrenComponentsList)
	{
		delete it.second;
	}
	_childrenComponentsList.clear();

	_parentComponent = NULL;
}

bool FTransformationComponent::addChildrenComponent(FTransformationComponent* children)
{
	auto it = _childrenComponentsList.find(children->_name);

	if (it == _childrenComponentsList.end())
	{
		_childrenComponentsList.insert(std::make_pair(children->_name, children));
		children->_parentComponent = this;
	}
	else
	{
		FLog(FLog::WARNING, "Component already exists in " + _name + ", can't add it: %s", children->getName().c_str());
		return false;
	}

	return true;
}

void FTransformationComponent::removeChildrenComponent(std::string name)
{
	auto it = _childrenComponentsList.find(name);

	if (it != _childrenComponentsList.end())
	{
		//As components are not shared if we remove it we have to delete it or return it. We return it.
		delete it->second;
		_childrenComponentsList.erase(name);
	}
	else
	{
		FLog(FLog::WARNING, "Component doesn't exists in " + _name + ", can't remove it: %s", name.c_str());
	}
}


void FTransformationComponent::setLocalTransformation(const Vector3& deltaPos, const Quaternion& deltaRot, const Vector3& deltaScale)
{
	_localPosition += deltaPos;
	_localRotationValue = deltaRot * _localRotationValue;
	_localScaleValue = _localScaleValue * deltaScale;

	//Update _world transformations
	getWorldTransformationsFromParent();
}


void FTransformationComponent::updateChildrensTransformationObjects()
{
	for (auto it : _childrenComponentsList)
	{
		it.second->getWorldTransformationsFromParent();
	}
}

void FTransformationComponent::getWorldTransformationsFromParent()
{
	if (_parentComponent)
	{
		_worldPosition = _parentComponent->_worldPosition + _localPosition;
		_worldRotationValue = _parentComponent->_worldRotationValue * _localRotationValue;
		_worldScaleValue = _parentComponent->_worldScaleValue * _localScaleValue;
	}
	else
	{
		_worldPosition = _localPosition;
		_worldRotationValue = _localRotationValue;
		_worldScaleValue = _localScaleValue;
	}

	updateChildrensTransformationObjects();
}

void FTransformationComponent::setParent(FActor* newParent)
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
	newParent->addComponentToRootComponent(this);
	FComponent::setParent(newParent); //Update our parent reference.
}
