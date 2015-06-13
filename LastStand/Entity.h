#pragma once

#include <unordered_map>

#include "FObject.h"

class Entity : public FObject
{
public:
	Entity(std::string name);
	Entity(std::string name, Entity* parent);
	~Entity();

	void setPosition(const Vector3& pos);
	void translate(const Vector3& delta);
	void setOrientation(const Quaternion& delta);
	void rotate(const Quaternion& delta);
	void rotate(const Vector3& degreeDelta);
	void setScale(const Vector3& scale);
	void scale(const Vector3& delta);

	FTransformationObject getTransform()
	{
		return _rootTransformationObject;
	}
private:
	Entity* _parentEntity; //Null if is a root entity
	std::unordered_map<std::string, FObject> _componentsList; //List containing all the components attached to the entity
};

