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
	static Vector3 clamp(const Vector3& vec, float min, float max);

	//Others
	static float fmod(float number, float divider);
	static float clamp(float num, float min, float max);
	
	//Trigonometry
	//Retuns the arcCosine of a number. Returns in degrees.
	static float arcCos(float num);

	//Random
	//Generates a random integer - Linear distribution
	static int randomInteger(int min = 0, int max = 1);
	//Generates a random float - Linear distribution
	static float randomFloat(float min = 0.0, float max = 1.0);
	//Generates a random vector - Linear distribution
	static Vector3 randomVector(float min = 0.0, float max = 1.0);

};

