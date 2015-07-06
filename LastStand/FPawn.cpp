#include "FPawn.h"


FPawn::FPawn(std::string actorName)
	:FActor(actorName),
	_controllerPossessingMe(NULL)
{
}


FPawn::~FPawn()
{
}

void FPawn::possesses(FController* possessor)
{
	_controllerPossessingMe = possessor;
}

void FPawn::unPossesses()
{
	_controllerPossessingMe = NULL;
}

void FPawn::addMovementInput(const Vector3& normalizedWorldDirection, float scale)
{
	translate(normalizedWorldDirection * scale);
}
