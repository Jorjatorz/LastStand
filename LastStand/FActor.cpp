#include "FActor.h"

#include "FInputComponent.h"
#include "FLog.h"

FActor::FActor(std::string name)
	:FObject(name),
	_rootComponent(NULL),
	_inputComponent(NULL),
	_actorCanTick(false)
{
}


FActor::~FActor()
{
	if (_rootComponent)
	{
		_rootComponent->onRemovedFromComponent();
		delete _rootComponent;
	}

	disableInput();
}

void FActor::addComponent(FSceneComponent* component)
{
	if (_rootComponent)
		_rootComponent->addChildrenComponent(component);
	else
	{
		_rootComponent = component;
		_rootComponent->onAttachedToComponent();
	}
}

void FActor::removeComponent(std::string name)
{
	if (_rootComponent)
		_rootComponent->removeChildrenComponent(name);
	else
		FLog(FLog::WARNING, "Root Component doesn't exists in " + _name + ", can't remove %s from it", name.c_str());
}

void FActor::setPosition(const Vector3& pos)
{
	if (_rootComponent)
		_rootComponent->setLocalPosition(pos);
	else
		FLog(FLog::WARNING, "Root Component doesn't exists in " + _name + ", can't set position to it");

}

void FActor::translate(const Vector3& delta)
{
	if (_rootComponent)
		_rootComponent->translate(delta);
	else
		FLog(FLog::WARNING, "Root Component doesn't exists in " + _name + ", can't translate it");
}

void FActor::setRotation(const Quaternion& quat)
{
	if (_rootComponent)
		_rootComponent->setLocalRotation(quat);
	else
		FLog(FLog::WARNING, "Root Component doesn't exists in " + _name + ", can't set orientation to it");
}

void FActor::setRotation(const FRotator& rotator)
{
	if (_rootComponent)
		_rootComponent->setLocalRotation(rotator);
	else
		FLog(FLog::WARNING, "Root Component doesn't exists in " + _name + ", can't set orientation to it");
}

void FActor::setRotation(const Vector3& euler)
{
	if (_rootComponent)
		_rootComponent->setLocalRotation(euler);
	else
		FLog(FLog::WARNING, "Root Component doesn't exists in " + _name + ", can't set orientation to it");
}

void FActor::setOrientation(const Vector3& direction)
{
	if (_rootComponent)
		_rootComponent->setLocalOrientation(direction);
	else
		FLog(FLog::WARNING, "Root Component doesn't exists in " + _name + ", can't set orientation to it");
}

void FActor::rotate_WorldSpace(const Quaternion& delta)
{
	if (_rootComponent)
		_rootComponent->rotate_WorldSpace(delta);
	else
		FLog(FLog::WARNING, "Root Component doesn't exists in " + _name + ", can't rotate it");
}

void FActor::rotate_WorldSpace(float degrees, const Vector3& axisVector)
{
	if (_rootComponent)
		_rootComponent->rotate_WorldSpace(degrees, axisVector);
	else
		FLog(FLog::WARNING, "Root Component doesn't exists in " + _name + ", can't rotate it");
}

void FActor::rotate_LocalSpace(float degrees, const Vector3& axisVector)
{
	if (_rootComponent)
		_rootComponent->rotate_LocalSpace(degrees, axisVector);
	else
		FLog(FLog::WARNING, "Root Component doesn't exists in " + _name + ", can't rotate it");
}

void FActor::setScale(const Vector3& scale)
{

	if (_rootComponent)
		_rootComponent->setLocalScale(scale);
	else
		FLog(FLog::WARNING, "Root Component doesn't exists in " + _name + ", can't set scale to it");
}

void FActor::scale(const Vector3& delta)
{

	if (_rootComponent)
		_rootComponent->scale(delta);
	else
		FLog(FLog::WARNING, "Root Component doesn't exists in " + _name + ", can't set orientation to it");
}

void FActor::addOwnedComponent(FComponent* ownedComp)
{
	_ownedComponents.push_back(ownedComp);
}

void FActor::removeOwnedComponent(FComponent* ownedComp)
{
	auto it = _ownedComponents.cbegin();

	while (it != _ownedComponents.cend())
	{
		if (*it == ownedComp)
		{
			_ownedComponents.erase(it);
			break;
		}

		it++;
	}
}

FInputComponent* FActor::enableInput()
{
	if (!_inputComponent)
	{
		_inputComponent = new FInputComponent("DefaultInputComponent", this);
	}

	return _inputComponent;
}

void FActor::disableInput()
{
	if (_inputComponent)
	{
		delete _inputComponent;
		_inputComponent = NULL;
	}
}

void FActor::pitch(float degrees)
{
	if (_rootComponent)
		_rootComponent->rotate_WorldSpace(degrees, Vector3(1.0, 0.0, 0.0));
	else
		FLog(FLog::WARNING, "Root Component doesn't exists in " + _name + ", can't rotate it");
}

void FActor::yaw(float degrees)
{

	if (_rootComponent)
		_rootComponent->rotate_WorldSpace(degrees, Vector3(0.0, 1.0, 0.0));
	else
		FLog(FLog::WARNING, "Root Component doesn't exists in " + _name + ", can't rotate it");
}

void FActor::roll(float degrees)
{

	if (_rootComponent)
		_rootComponent->rotate_WorldSpace(degrees, Vector3(0.0, 0.0, 1.0));
	else
		FLog(FLog::WARNING, "Root Component doesn't exists in " + _name + ", can't rotate it");
}

void FActor::tickActor(float deltaTime)
{
	//Call the virtual function. For custom behaviour override it.
	FObject::tickObject(deltaTime);

	//Call tick and all its components
	for (auto const &component : _ownedComponents)
	{
		if (component->canComponentTick())
		{
			component->tickComponent(deltaTime);
		}
	}
}

void FActor::setActorCanTick(bool canTick)
{
	_actorCanTick = canTick;
}
