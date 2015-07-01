#include "Viewport.h"

#include <gl\gl.h>

#include "Math.h"

Viewport::Viewport(const int& x, const int& y, const int& width, const int& height)
	:_originX(x),
	_originY(y),
	_width(width),
	_height(height),
	_isDirty(true),
	_clearColor(0.5) //Black
{
}


Viewport::~Viewport()
{
}

void Viewport::updateViewport()
{
	if (_isDirty)
	{
		glScissor(_originX, _originY, _width, _height);
		glViewport(_originX, _originY, _width, _height);
		glClearColor(_clearColor.r, _clearColor.g, _clearColor.b, 1.0);

		_isDirty = false;
	}

}

void Viewport::setClearColor(const Vector3& newColor)
{
	_clearColor = newColor;
	_isDirty = true;
}