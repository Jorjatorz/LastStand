#include "FController.h"

#include "FPawn.h"

FController::FController()
	:_pawnPossessed(NULL)
{
}


FController::~FController()
{
}

void FController::possesses(FPawn* pawn)
{
	if (pawn)
	{
		//If we already posses one pawn, notify and unpossed it
		if (_pawnPossessed)
		{
			_pawnPossessed->unPossesses();
		}

		_pawnPossessed = pawn;
		_pawnPossessed->possesses(this);
	}
}

void FController::unPossesses()
{
	if (_pawnPossessed)
	{
		_pawnPossessed->unPossesses();
		_pawnPossessed = NULL;
	}
}
