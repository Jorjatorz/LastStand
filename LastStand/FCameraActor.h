#pragma once

#include "FActor.h"

class FCameraComponent;

class FCameraActor : public FActor
{
public:
	FCameraActor(std::string actorName);
	~FCameraActor();

private:
	///In UE4 this is public... For now I will keep it private or my university teachers will get mad :O
	FCameraComponent* _cameraComponentPtr;
};

