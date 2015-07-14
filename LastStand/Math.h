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
	

	//Quaternion functions
	static Matrix4 getRotationMatrixFromQuaternion(const Quaternion& quat);

	//Vectors function

	//Others
	static float fmod(float number, float divider);

};

