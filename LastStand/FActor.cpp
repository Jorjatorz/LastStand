#include "FActor.h"

#include "FInputComponent.h"

FActor::FActor(std::string name)
	:FObject(name),
	_rootComponent("DefaultRootSceneComponent", this),
	_inputComponent(NULL)
{
	addOwnedComponent(&_rootComponent);
}


FActor::~FActor()
{ //Root element deleted automatically here
	disableInput();
}

void FActor::addComponent(FSceneComponent* component)
{
	_rootComponent.addChildrenComponent(component);
}

void FActor::removeComponent(std::string name)
{
	_rootComponent.removeChildrenComponent(name);
}

void FActor::setPosition(const Vector3& pos)
{
	_rootComponent.setLocalPosition(pos);
}

void FActor::translate(const Vector3& delta)
{
	_rootComponent.translate(delta);
}

void FActor::setOrientation(const Quaternion& quat)
{
	_rootComponent.setLocalRotation(quat);
}

void FActor::rotate_WorldSpace(const Quaternion& delta)
{
	_rootComponent.rotate_WorldSpace(delta);
}

void FActor::rotate_WorldSpace(float degrees, const Vector3& axisVector)
{
	_rootComponent.rotate_WorldSpace(degrees, axisVector);
}

void FActor::rotate_LocalSpace(float degrees, const Vector3& axisVector)
{
	_rootComponent.rotate_LocalSpace(degrees, axisVector);
}

void FActor::setScale(const Vector3& scale)
{
	_rootComponent.setLocalScale(scale);
}

void FActor::scale(const Vector3& delta)
{
	_rootComponent.scale(delta);
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

void FActor::enableInput()
{
	if (!_inputComponent)
	{
		_inputComponent = new FInputComponent("DefaultInputComponent", this);
	}
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
	_rootComponent.rotate_WorldSpace(degrees, Vector3(1.0, 0.0, 0.0));
}

void FActor::yaw(float degrees)
{
	_rootComponent.rotate_WorldSpace(degrees, Vector3(0.0, 1.0, 0.0));
}

void FActor::roll(float degrees)
{
	_rootComponent.rotate_WorldSpace(degrees, Vector3(0.0, 0.0, 1.0));
}
