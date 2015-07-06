#pragma once

#include "FActor.h"

class FController;

//A Pawn is a normal actor but it can be possessed by a controller (human or AI)
class FPawn : public FActor
{
public:
	FPawn(std::string actorName);
	~FPawn();

	//Function that attach a controller to the pawn.
	//WARNING!! This should only be called by the controller
	void possesses(FController* possessor);
	void unPossesses();

	//Movement methods
	//Adds a movement to the root component given a worldDirection (normalized) and a scale
	void addMovementInput(const Vector3& normalizedWorldDirection, float scale);

private:
	//Pointer to the controller that possesses the pawn;
	FController* _controllerPossessingMe;
};

