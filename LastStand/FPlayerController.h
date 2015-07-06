#pragma once

#include "FController.h"

#include <list>

class FInputComponent;

//Controller that represents the human player
//This controller resides in the Fworld.
class FPlayerController: public FController
{
public:
	FPlayerController();
	~FPlayerController();

	//Registers an input component into the inputCList
	//It will be placed on the top of the stack (end of the list)
	//Warning! This is called automatically in the inputComponent constructor
	void registerInputComponent(FInputComponent* comp);
	//Remove a component from a list.
	//Warning! this is called automatically from the InputComponent desructor
	void unregisterInputComponent(FInputComponent* comp);

	//Called every frame, it checks for axisMapping inputs
	virtual void tick(int deltaTime);

private:
	//List containing all the inputComponents of the actors that can recive input
	//It is treated as a stack
	std::list<FInputComponent*> _inputComponentsList;

};

