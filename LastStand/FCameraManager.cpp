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
		setViewportCamera(comp);
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
		_viewportCameraRotation = _viewportCamera->getWorldRotation();
	}
}

void FCameraManager::addMovementToViewportCamera(const Vector3 &delta)
{
	if (_viewportCamera)
	{
		_viewportCamera->translate(_viewportCamera->getWorldRotationQuaternion() * Vector3(delta.x, delta.y, -delta.z));
	}
	else
	{
		FLog(FLog::FAILURE, "There is no Viewport Camera set");
		assert(0);
	}
}

void FCameraManager::addRotationToViewportCamera(FRotator deltaRot)
{
	if (_viewportCamera)
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

		_viewportCamera->setLocalRotation(_viewportCameraRotation.toQuaternion());
	}
	else
	{
		FLog(FLog::FAILURE, "There is no Viewport Camera set");
		assert(0);
	}
}

FCameraComponent* const FCameraManager::getViewportCamera() const
{
	if (_viewportCamera)
	{
		return _viewportCamera;
	}
	else
	{
		FLog(FLog::FAILURE, "There is no Viewport Camera set");
		assert(0);
		return NULL;
	}
}
