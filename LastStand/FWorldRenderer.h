#pragma once

#include "SingleInstance.h"

class FWorld;
class Matrix4;

//Class incharge of rendering all the FObjects in the world.
class FWorldRenderer
{
public:
	FWorldRenderer();
	~FWorldRenderer();


	//Main function. Renders all the objects in the worlds that are visible.
	void renderObjectsInTheWorld(FWorld* currentWorld, const Matrix4& projectionViewMatrix);
};

