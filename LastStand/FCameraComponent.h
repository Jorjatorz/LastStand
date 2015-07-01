#pragma once

#include "FSceneComponent.h"
#include "Matrix4.h"
#include "Texture.h"

//Component that represents a point of view (camera) from which can renderer the scene. This scene can be rendered to a viewport (attached to one) or to a texture.
//Warning! The camera will render the scene ONLY if it has a Renderin Target or is the viewPot camera
class FCameraComponent : public FSceneComponent
{
public:
	FCameraComponent(std::string name, FActor* actor);
	~FCameraComponent();

	//Sets the rendering target of the camera
	void addRenderingTarget(Texture* texture2DTarget);
	bool hasRenderingTarget()
	{
		return _renderTargetPtr;
	}
	Texture* getRendeingTargetPtr() const
	{
		return _renderTargetPtr;
	}

	//Returns the projection and view matrix
	void getCameraProjectionAndViewMatricesPtr(Matrix4* &projM, Matrix4* &viewM);

	//Sets the camera as the viewport camera
	void setAsViewportCamera();

private:
	//Rendering target
	Texture* _renderTargetPtr;

	//Rendering properties
	enum ProjectionModeEnum
	{
		PERSPECTIVE,
		ORTHOGRAPHIC
	};
	ProjectionModeEnum _projectionMode; //Type of projection, by default perspective
	Matrix4 _projectionCameraMatrix;
	float _FOV;
	float _aspectRatio;
	Matrix4 _viewCameraMatrix;
};

