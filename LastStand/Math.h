#pragma once

class Vector3;
class Matrix4;
class Quaternion;

//Auxiliary class that contains math functions
class Math
{
public:
	Math();
	~Math();

	//Matrix functions
	//Creates a perspective matrix, if zFar is set to 0 its an infinite perspective
	static Matrix4 createPerspectiveMatrix(float fov, float aspectRatio, float zNear, float zFar = 0.0);
	static Matrix4 createLookAtMatrix(const Vector3& eye, const Vector3& center, const Vector3& up);

	//Quaternion functions
	static Matrix4 getRotationMatrixFromQuaternion(const Quaternion& quat);

	//Vectors function
	static Vector3 cross(const Vector3& a, const Vector3& b);
	static float dot(const Vector3& a, const Vector3& b);
};

