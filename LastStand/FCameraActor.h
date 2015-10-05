#pragma once

#include "FActor.h"

#include "FCameraComponent.h"

class FCameraActor : public FActor
{
public:
	FCameraActor(std::string actorName);
	~FCameraActor();

	//Sets the camera projection mode. When changed the new projection will be set with the current projection configuration 
	//(i.e. if perspective mode is set the new projection will be configured with the camre current _FOV, _aspectRatio, etc values)
	void setProjectionMode(FCameraComponent::ProjectionModeEnum newProj);
	FCameraComponent::ProjectionModeEnum getProjectionMode();

	void setRenderingTarget(Texture* tex);
	bool hasRenderingTarget();
	Texture* getRendeingTargetPtr() const;

private:
	///In UE4 this is public... For now I will keep it private or my university teachers will get mad :O
	FCameraComponent* _cameraComponentPtr;
};

