#pragma once

#include <list>

#include "SingleInstance.h"

class FCameraComponent;

//Class incharge of keeping track of all the camera components and pass them to the Renderer
class FCameraManager : public SingleInstance<FCameraManager>
{
public:
	FCameraManager();
	~FCameraManager();
	
	//Registers a camera to be use in the rendering pipeline
	void registerCameraComponent(FCameraComponent* comp);
	//Unregisters a camera
	void unregisterCameraComponent(FCameraComponent* comp);

	//Return the camera list (this is called by the scene each frame to render)
	const std::list<FCameraComponent*>& getCameraComponentsList()
	{
		return _camerasList;
	}


	//Sets the viewport camera
	void setViewportCamera(FCameraComponent* comp);
	//Return the viewport camera
	FCameraComponent* const getViewportCamera() const
	{
		return _viewportCamera;
	}

private:
	//List with all the cameras
	std::list<FCameraComponent*> _camerasList;

	//Viewport camera. The main camera from which the scene is captured, it will be displayed in the viewport.
	//This is the camera which is modified directly from the Player controler
	FCameraComponent* _viewportCamera;
};

