#include "FObject.h"


#include "FLog.h"

FObject::FObject(std::string name)
	:_name(name),
	_rootTransformationObject(name)
{
}


FObject::~FObject()
{
	for (auto it : _componentsList)
	{
		it.second->_parentObject = NULL;
	}
	_componentsList.clear();

	if (_parentObject)
	{
		_parentObject->removeComponent(_name);
	}
}

void FObject::attachToParent(FObject* parent)
{
	if (_parentObject)
	{
		_parentObject->removeComponent(_name);
	}
	_parentObject = parent;
	_parentObject->addComponent(this);
}

void FObject::addComponent(FObject* component)
{
	if (_componentsList.find(component->getName()) != _componentsList.end())
	{
		FLog(FLog::WARNING, "Component already exists in " + _name + ", can't add it: %s", component->getName().c_str());
		return;
	}
	_componentsList.insert(std::make_pair(component->getName(), component));

	_rootTransformationObject.addChildrenTranformationObject(component->getTransformPtr());
}

void FObject::removeComponent(std::string name)
{
	auto it = _componentsList.find(name);
	if (it != _componentsList.end())
	{
		//Transformation has same name as component
		_rootTransformationObject.removeChildrenTransformationObject(name);
		it->second->_parentObject = NULL;

		_componentsList.erase(it);
	}
	else
	{
		FLog(FLog::WARNING, "Cannot delete component at " + _name + ", doesn't exists: %s", name.c_str());
	}
}

