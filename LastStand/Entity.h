#pragma once

#include <unordered_map>

#include "FObject.h"

//Class that represents an object with a 3D mesh and a material
class Entity : public FObject
{
public:
	Entity(std::string name);
	~Entity();

	//Transformations
	void setPosition(const Vector3& pos);
	void translate(const Vector3& delta);
	void setOrientation(const Quaternion& delta);
	void rotate(const Quaternion& delta);
	void rotate(const Vector3& degreeDelta);
	void setScale(const Vector3& scale);
	void scale(const Vector3& delta);
};

