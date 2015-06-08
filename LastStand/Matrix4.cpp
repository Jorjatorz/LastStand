#include "Matrix4.h"

#include "Vector3.h"

Matrix4::Matrix4()
	:_GLMMatrix(1.0)
{
}

Matrix4::Matrix4(float diagonalValue)
	: _GLMMatrix(diagonalValue)
{

}


Matrix4::~Matrix4()
{
}

Matrix4& Matrix4::operator=(const Matrix4& other)
{
	_GLMMatrix = other._GLMMatrix;

	return *this;
}

bool Matrix4::operator==(const Matrix4& other) const
{
	return _GLMMatrix == other._GLMMatrix;
}

Matrix4 Matrix4::operator+(const Matrix4& other)
{
	Matrix4 newM;
	newM._GLMMatrix = _GLMMatrix + other._GLMMatrix;
	return newM;
}

Matrix4 Matrix4::operator-(const Matrix4& other)
{
	Matrix4 newM;
	newM._GLMMatrix = _GLMMatrix - other._GLMMatrix;
	return newM;
}

Matrix4 Matrix4::operator*(const Matrix4& other)
{
	Matrix4 newM;
	newM._GLMMatrix = _GLMMatrix * other._GLMMatrix;
	return newM;
}

const Matrix4 Matrix4::operator*(const Matrix4& other) const
{
	Matrix4 newM;
	newM._GLMMatrix = _GLMMatrix * other._GLMMatrix;
	return newM;
}

Matrix4 Matrix4::operator/(const Matrix4& other)
{
	Matrix4 newM;
	newM._GLMMatrix = _GLMMatrix / other._GLMMatrix;
	return newM;
}

Matrix4 Matrix4::getInverseMatrix()
{
	Matrix4 newM;
	newM._GLMMatrix = glm::inverse(_GLMMatrix);
	return newM;
}

Matrix4 Matrix4::getTransposeMatrix()
{
	Matrix4 newM;
	newM._GLMMatrix = glm::transpose(_GLMMatrix);
	return newM;
}



void Matrix4::translate(const Vector3& transVec)
{
	_GLMMatrix = glm::translate(_GLMMatrix, glm::vec3(transVec.x, transVec.y, transVec.z));
}

void Matrix4::rotate(float angle, const Vector3& rotVec)
{
	_GLMMatrix = glm::rotate(_GLMMatrix, angle, glm::vec3(rotVec.x, rotVec.y, rotVec.z));
}

void Matrix4::rotate(const Vector3& rotVec)
{
	_GLMMatrix = glm::rotate(_GLMMatrix, (float)1.0, glm::vec3(rotVec.x, rotVec.y, rotVec.z));
}

void Matrix4::scale(const Vector3& scaleVec)
{
	_GLMMatrix = glm::scale(_GLMMatrix, glm::vec3(scaleVec.x, scaleVec.y, scaleVec.z));
}

const float* Matrix4::getValuePtr() const
{
	return &_GLMMatrix[0].x;
}