#include "Viewport.h"

#include <gl\gl.h>

#include "Math.h"

Viewport::Viewport(const int& x, const int& y, const int& width, const int& height)
	:_originX(x),
	_originY(y),
	_width(width),
	_height(height),
	_isDirty(true),
	_clearColor(0.5), //Black
	_projectionMatrix(Math::createPerspectiveMatrix(45.0f, width / height, 0.1f))
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
		glClearColor(_clearColor.r, _clearColor.g, _clearColor.b, 1.0);

		_isDirty = false;
	}


	//Update the matrix camera
	//mAttachedCamera->processViewMatrix();

}

void Viewport::setClearColor(const Vector3& newColor)
{
	_clearColor = newColor;
	_isDirty = true;
}

void Viewport::getViewportProjectionandViewMatrix(Matrix4& projectionM, Matrix4& viewM)
{
	projectionM = _projectionMatrix;
	///DEBUG
	viewM.translate(Vector3(0.0, 0.0, -5.0));
}
