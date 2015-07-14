#pragma once

#include "Vector3.h"
#include "Quaternion.h"

class Matrix4;

//Holds a position, orientation and scale information
class FTransform
{
public:
	FTransform();
	FTransform(const Vector3& position, const Quaternion& rotation, const Vector3& scale);
	~FTransform();

	void translate(const Vector3& delta);
	void rotate(const Quaternion& delta);
	void scale(const Vector3& delta);
	
	void setPosition(const Vector3& pos);
	void setRotation(const Quaternion& quat);
	void setScale(const Vector3& scale);

	//Accumulate another transform with this one.
	void accumulate(const FTransform& other);

	Vector3 getPosition()
	{
		return _postion;
	}
	Quaternion getRotationQuaternion()
	{
		return _rotation;
	}
	Vector3 getScale()
	{
		return _scale;
	}
	Matrix4 getTransformationMatrix();

private:
	Vector3 _postion;
	Quaternion _rotation;
	Vector3 _scale;
};

