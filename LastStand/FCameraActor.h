#pragma once


#include "FActor.h"

class FCameraActor : public FActor
{
public:
	FCameraActor(std::string actorName);
	~FCameraActor();

	virtual void translate(const Vector3& delta) override;
	//Using camera ptich must be done in lcoal space
	virtual void pitch(float degrees) override;


};

