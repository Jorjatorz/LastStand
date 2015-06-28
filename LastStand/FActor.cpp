#include "FActor.h"

FActor::FActor(std::string name)
	:FObject(name),
	_rootComponent(name, this)
{
}


FActor::~FActor()
{ //Root element deleted automatically here
}

void FActor::addComponentToRootComponent(FSceneComponent* component)
{
	_rootComponent.addChildrenComponent(component);
}

void FActor::removeComponentFromRootComponent(std::string name)
{
	_rootComponent.removeChildrenComponent(name);
}

void FActor::setPosition(const Vector3& pos)
{
	Vector3 delta = pos - _rootComponent.getWorldPosition();
	_rootComponent.setLocalTransformation(delta, Quaternion(), Vector3(1.0));
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
	}
}

