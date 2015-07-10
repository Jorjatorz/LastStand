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
	_rootComponent.setLocalTransformation(delta, Quaternion(), Vector3(1.0));
}

void FActor::setOrientation(const Quaternion& delta)
{
	_rootComponent.setLocalTransformation(Vector3(0.0), delta, Vector3(1.0));
}

void FActor::rotate(const Quaternion& delta)
{
	_rootComponent.setLocalTransformation(Vector3(0.0), delta, Vector3(1.0));
}

void FActor::rotate(const Vector3& degreeDelta)
{
	_rootComponent.setLocalTransformation(Vector3(0.0), Quaternion(degreeDelta), Vector3(1.0));
}

void FActor::setScale(const Vector3& scale)
{
	Vector3 delta = scale - _rootComponent.getWorldScale();
	_rootComponent.setLocalTransformation(Vector3(0.0), Quaternion(), delta);
}

void FActor::scale(const Vector3& delta)
{
	_rootComponent.setLocalTransformation(Vector3(0.0), Quaternion(), delta);
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
