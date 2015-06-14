#include "Entity.h"

Entity::Entity(std::string name)
	:FObject(name)
{
}

Entity::~Entity()
{
}

void Entity::setPosition(const Vector3& pos)
{
	Vector3 delta = pos - _rootTransformationObject.getWorldPosition();
	_rootTransformationObject.setLocalTransformation(delta, Quaternion(), Vector3(0.0));
}

void Entity::translate(const Vector3& delta)
{
	_rootTransformationObject.setLocalTransformation(delta, Quaternion(), Vector3(0.0));
}

void Entity::setOrientation(const Quaternion& delta)
{
	_rootTransformationObject.setLocalTransformation(Vector3(0.0), delta, Vector3(0.0));
}

void Entity::rotate(const Quaternion& delta)
{
	_rootTransformationObject.setLocalTransformation(Vector3(0.0), delta, Vector3(0.0));
}

void Entity::rotate(const Vector3& degreeDelta)
{
	_rootTransformationObject.setLocalTransformation(Vector3(0.0), Quaternion(degreeDelta), Vector3(0.0));
}

void Entity::setScale(const Vector3& scale)
{
	Vector3 delta = scale - _rootTransformationObject.getWorldScale();
	_rootTransformationObject.setLocalTransformation(Vector3(0.0), Quaternion(), delta);
}

void Entity::scale(const Vector3& delta)
{
	_rootTransformationObject.setLocalTransformation(Vector3(0.0), Quaternion(), delta);
}

