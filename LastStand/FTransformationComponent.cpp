#include "FTransformationComponent.h"

FTransformationComponent::FTransformationComponent(std::string name)
	:_name(name),
	_parentTransformationObject(NULL),
	_localPosition(0.0),
	_localRotationValue(),
	_localScaleValue(1.0)
{
}


FTransformationComponent::~FTransformationComponent()
{
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
	for (auto it: _childrenTransformationObjectsList)
	{
		it.second->getWorldTransformationsFromParent();
	}
}

void FTransformationComponent::getWorldTransformationsFromParent()
{
	if (_parentTransformationObject)
	{
		_worldPosition = _parentTransformationObject->_worldPosition + _localPosition;
		_worldRotationValue = _parentTransformationObject->_worldRotationValue * _localRotationValue;
		_worldScaleValue = _parentTransformationObject->_worldScaleValue * _localScaleValue;
	}
	else
	{
		_worldPosition = _localPosition;
		_worldRotationValue = _localRotationValue;
		_worldScaleValue = _localScaleValue;
	}

	updateChildrensTransformationObjects();
}

void FTransformationComponent::addChildrenTranformationObject(FTransformationComponent* children)
{
	auto it = _childrenTransformationObjectsList.find(children->_name);

	if (it == _childrenTransformationObjectsList.end())
	{
		_childrenTransformationObjectsList.insert(std::make_pair(children->_name, children));
		children->_parentTransformationObject = this;
		children->getWorldTransformationsFromParent();
	}
}

void FTransformationComponent::removeChildrenTransformationObject(std::string name)
{
	auto it = _childrenTransformationObjectsList.find(name);

	if (it != _childrenTransformationObjectsList.end())
	{
		it->second->_parentTransformationObject = NULL;
		_childrenTransformationObjectsList.erase(name);
	}
}
