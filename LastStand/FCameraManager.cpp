#include "FCameraManager.h"

#include "Vector3.h"
#include "Math.h"
#include "FCameraComponent.h"

FCameraManager::FCameraManager()
	:_viewportCamera(NULL),
	_viewportCameraRotation(),
	_pitchRotationLimitMax(89.9f),
	_pitchRotationLimitMin(-89.9f),
	_yawRotationLimitMax(359.9f),
	_yawRotationLimitMin(0.0f),
	_rollRotationLimitMax(89.9f),
	_rollRotationLimitMin(-89.9f)
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

void FCameraManager::addRotationToViewportCamera(FRotator deltaRot)
{
	_viewportCameraRotation += deltaRot;

	Vector3 aux = _viewportCameraRotation.toEuler();
	//Clamp pitch Pitch
	aux.x = Math::clamp(aux.x, _pitchRotationLimitMin, _pitchRotationLimitMax);

	//Set back yaw to 0 if it exceeds 360
	if (aux.y > 359.9f || aux.y < -359.9f)
	{
		aux.y = 0;
	}

	_viewportCameraRotation = FRotator(aux);

	std::cout << _viewportCameraRotation << std::endl;

	_viewportCamera->setLocalRotation(_viewportCameraRotation.toQuaternion());
}