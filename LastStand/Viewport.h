#pragma once

#include "Matrix4.h"
#include "Vector3.h"

class Viewport
{
public:
	Viewport(const int& x, const int& y, const int& width, const int& height);
	~Viewport();

	//Check if the viewport is dirty and if it's update it.
	void updateViewport();

	//Return the viewmatrix of the camera attached to the viewport
	void getViewportProjectionandViewMatrix(Matrix4& projectionM, Matrix4& viewM);

	//Change the clear color
	void setClearColor(const Vector3& newColor);

private:
	//Size variables
	int _originX; //Top left X origin
	int _originY; //Top left Y origin
	int _width; //Biggest X (range 0 - 1)
	int _height; //Biggest Y (range 0 - 1)

	//True if the viewport has change and needs an update
	bool _isDirty;
	//Clear color
	Vector3 _clearColor;

	//Projection matrix of the viewport
	Matrix4 _projectionMatrix;
};

