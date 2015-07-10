#include "FSceneComponent.h"

#include "FEngine.h"
#include "FLog.h"
#include "FActor.h"
#include "Math.h"

FSceneComponent::FSceneComponent(std::string name, FActor* parentActor)
	:FComponent(name, parentActor),
	_localPosition(0.0),
	_worldPosition(0.0),
	_localRotationValue(),
	_worldRotationValue(),
	_localScaleValue(1.0),
	_worldScaleValue(1.0),
	_transformationMatrix(1.0)
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
		it.second->getWorldTransformationsFromParent();
	}
}

void FSceneComponent::getWorldTransformationsFromParent()
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

	//Update the transformation matrix
	_transformationMatrix = Matrix4(1.0);
	_transformationMatrix.translate(_worldPosition);
	_transformationMatrix = _transformationMatrix * Math::getRotationMatrixFromQuaternion(_worldRotationValue);
	_transformationMatrix.scale(_worldScaleValue);

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
		children->getWorldTransformationsFromParent();
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

void FSceneComponent::setLocalTransformation(const Vector3& deltaPos, const Quaternion& deltaRot, const Vector3& deltaScale)
{
	float deltaTime = FEngine::getInstance()->getDeltaTime() / 1000.0f; //delta time in seconds

	if (deltaTime != 0.0)
	{
		_localPosition += deltaPos * deltaTime;
		_localRotationValue = deltaRot * _localRotationValue* deltaTime;
		_localScaleValue = _localScaleValue * deltaScale;/// *deltaTime;

		//Update _world transformations
		getWorldTransformationsFromParent();
	}
}


void FSceneComponent::setLocalPosition(const Vector3& pos)
{
	_localPosition = pos;

	//Update _world transformations
	getWorldTransformationsFromParent();
}

void FSceneComponent::setLocalOrientation(const Quaternion& quat)
{
	_localRotationValue = quat;

	//Update _world transformations
	getWorldTransformationsFromParent();
}

void FSceneComponent::setLocalScale(const Vector3& scale)
{
	_localScaleValue = scale;

	//Update _world transformations
	getWorldTransformationsFromParent();
}
