#pragma once

class FPawn;

//A controller is a non-physical actor that acts as interface between the input and the FPawn that it possesses.
//There are two main typed of controllers, the player and the AI controller.
//A controller can only possesses one Pawn
class FController
{
public:
	FController();
	~FController();

	void possesses(FPawn* pawn);
	void unPossesses();

	//Called every frame. Ticks the  controller.
	virtual void tick(int deltaTime) = 0;

protected:
	FPawn* _pawnPossessed;
};

