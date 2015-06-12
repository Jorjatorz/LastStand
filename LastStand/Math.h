#pragma once

class Vector3;
class Matrix4;
class Quaternion;

class Math
{
public:
	Math();
	~Math();

	//Matrix functions
	//Creates a perspective matrix, if zFar is set to 0 its an infinite perspective
	static Matrix4 createPerspectiveMatrix(float fov, float aspectRatio, float zNear, float zFar = 0.0);
};

