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

	//Type of projection that the camera uses.
	enum ProjectionModeEnum
	{
		PERSPECTIVE,
		ORTHOGRAPHIC
	};
	//Sets the camera projection mode. When changed the new projection will be set with the current projection configuration 
	//(i.e. if perspective mode is set the new projection will be configured with the camre current _FOV, _aspectRatio, etc values)
	void setProjectionMode(ProjectionModeEnum newProj);
	ProjectionModeEnum getProjectionMode();


	//Sets the rendering target of the camera
	void setRenderingTarget(Texture* texture2DTarget);
	bool hasRenderingTarget()
	{
		return _renderTargetPtr;
	}
	Texture* getRendeingTargetPtr() const
	{
		return _renderTargetPtr;
	}

	//Returns the projection, view matrix and the rendering camera position
	void getCameraProjectionAndViewMatricesPtr(Matrix4* &projM, Matrix4* &viewM, Vector3& cameraPosition);

	//Sets the camera as the viewport camera
	void setAsViewportCamera();

private:
	//Rendering target
	Texture* _renderTargetPtr;

	//Rendering properties
	ProjectionModeEnum _projectionMode; //Type of projection, by default perspective
	Matrix4 _projectionCameraMatrix;
	//Perspective projection information ////////////////////////////////////////////////////////////////////////////
	float _FOV;
	float _aspectRatio;
	//Ortographic projection information ////////////////////////////////////////////////////////////////////
	float _orthoWidth;
	float _orthoHeight;
	//Variables controlling the maximum and minimum render distance for a perspective projection
	const float _minimumRenderDistance;
	const float _maximumRenderDistance;
	//Creates the new projection matrix depending on the current projection;
	void setupProjectionMatrix();

	Matrix4 _viewCameraMatrix;
};

