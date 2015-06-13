#include "FTransformationObject.h"

FTransformationObject::FTransformationObject(std::string name, FTransformationObject* parent /*= NULL*/)
	:_name(name),
	_parentTransformationObject(parent),
	_localPosition(0.0),
	_localRotationValue(),
	_localScaleValue(1.0)
{
	//If a parent exist register to it
	if (_parentTransformationObject)
	{
		_parentTransformationObject->addChildrenTranformationObject(this);
	}
	getWorldTransformationsFromParent();
}


FTransformationObject::~FTransformationObject()
{
}

void FTransformationObject::setLocalTransformation(const Vector3& deltaPos, const Quaternion& deltaRot, const Vector3& deltaScale)
{
	_localPosition += deltaPos;
	_localRotationValue = deltaRot * _localRotationValue;
	_localScaleValue = _localScaleValue * deltaScale;

	//Update _world transformations
	getWorldTransformationsFromParent();
	updateChildrensTransformationObjects();
}


void FTransformationObject::updateChildrensTransformationObjects()
{
	for (auto it: _childrenTransformationObjectsList)
	{
		it.second->getWorldTransformationsFromParent();
	}
}

void FTransformationObject::getWorldTransformationsFromParent()
{
	if (_parentTransformationObject)
	{
		_worldPosition = _parentTransformationObject->_worldPosition;
		_worldRotationValue = _parentTransformationObject->_worldRotationValue;
		_worldScaleValue = _parentTransformationObject->_worldScaleValue;
	}
	else
	{
		_worldPosition = _localPosition;
		_worldRotationValue = _localRotationValue;
		_worldScaleValue = _localScaleValue;
	}
}

void FTransformationObject::addChildrenTranformationObject(FTransformationObject* children)
{
	if (children)
		_childrenTransformationObjectsList.insert(std::make_pair(children->_name, children));
}

void FTransformationObject::removeChildrenTransformationObject(std::string name)
{
	_childrenTransformationObjectsList.erase(name);
}
