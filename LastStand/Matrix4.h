#pragma once

#include <glm\glm.hpp>

//Forward declaration
class Vector3;

class Matrix4
{
public:
	//Identity matrix constructor
	Matrix4();
	//Creates a diagonal matrix given a diagonalvalue
	Matrix4(float diagonalValue);

	~Matrix4();

	//Operator overloading
	Matrix4& operator=(const Matrix4& other);
	bool operator==(const Matrix4& other) const;
	Matrix4 operator+(const Matrix4& other);
	Matrix4 operator-(const Matrix4& other);
	Matrix4 operator*(const Matrix4& other);
	const Matrix4 operator*(const Matrix4& other) const;
	Matrix4 operator/(const Matrix4& other);

	//Return a matrix that is the inverse of itself
	Matrix4 getInverseMatrix() const;
	//Return a matrix that is the transpose of itself
	Matrix4 getTransposeMatrix() const;
	//Return a matrix that is the transpose of the inverse of itself (same as transppose(inverse(matrix))
	Matrix4 getInverseTransposeMatrix() const;

	//Translates the matrix by a given vector
	void translate(const Vector3& transVec);
	//Rotates the matrix by a given an angle and a vector
	void rotate(float angle, const Vector3& axisVector);
	//Scales the matrix by a given vector value
	void scale(const Vector3& scaleVec);

	//Return the constant pointer to the first element of the vector
	const float* getValuePtr() const;

private:
	//Real matrix. Use GLM to do matrix calculations
	glm::mat4 _GLMMatrix;


	friend class Math;
};

