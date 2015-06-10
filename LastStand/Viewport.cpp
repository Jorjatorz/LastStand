#include "Viewport.h"

#include <gl\gl.h>

Viewport::Viewport(const int& x, const int& y, const int& width, const int& height)
	:_originX(x),
	_originY(y),
	_width(width),
	_height(height),
	_isDirty(true),
	mClearColor(0.5) //Gray
{
}


Viewport::~Viewport()
{
}

void Viewport::updateViewport()
{
	/*if (mAttachedCamera == NULL)
	{
		FE_LOG(FE_LOG::ERR, "No camera attached to the viewport");
		assert(0);
	}*/

	if (_isDirty)
	{
		glScissor(_originX, _originY, _width, _height);
		glViewport(_originX, _originY, _width, _height);
		glClearColor(mClearColor.r, mClearColor.g, mClearColor.b, 1.0);

		_isDirty = false;
	}


	//Update the matrix camera
	//mAttachedCamera->processViewMatrix();

}

void Viewport::setClearColor(const Vector3& newColor)
{
	mClearColor = newColor;
	_isDirty = true;
}

Matrix4 Viewport::getViewportViewMatrix()
{
	/*if (mAttachedCamera == NULL)
	{
		FE_LOG(FE_LOG::ERR, "No camera attached to the viewport");
		assert(0);
	}

	return mAttachedCamera->getViewMatrix();*/

	return Matrix4();
}