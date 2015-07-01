#include "FCameraManager.h"


FCameraManager::FCameraManager()
{
}


FCameraManager::~FCameraManager()
{
}

void FCameraManager::registerCameraComponent(FCameraComponent* comp)
{
	//Set the first camera to be the default camera by default.
	if (_camerasList.empty())
	{
		_viewportCamera = comp;
	}

	_camerasList.push_back(comp);
}

void FCameraManager::unregisterCameraComponent(FCameraComponent* comp)
{
	auto it = _camerasList.cbegin();
	while (it != _camerasList.cend())
	{
		if (*it == comp)
		{
			_camerasList.erase(it);
			return;
		}
	}
}

void FCameraManager::setViewportCamera(FCameraComponent* comp)
{
	if (comp != NULL)
	{
		_viewportCamera = comp;
	}
}
