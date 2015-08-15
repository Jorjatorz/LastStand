#pragma once

#include "FController.h"

#include <list>

class FInputComponent;
class FActionMappingEvent;
class FCameraManager;

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
	virtual void tick(int deltaTime) override;

	//Sends the input event to all the inputComponentsList in a Chain of Responsability pattern way
	//It also cheacks if this input event is also an Axis Mapping 
	void inputEventProduced(const FActionMappingEvent& eventTriggered);

	//Return a pointer to the camera manager
	FCameraManager* const getCameraManagerPtr() const
	{
		return _FCameraManagerPtr;
	}

	//Adds a yaw input to the viewport camera
	void addYawInput(float degrees);
	//Adds a pitch inout to the viewport camera
	void addPitchInput(float degrees);

private:
	//List containing all the inputComponents of the actors that can recive input
	//It is treated as a stack
	std::list<FInputComponent*> _inputComponentsList;

	//Pointer to the camera Manager
	FCameraManager* _FCameraManagerPtr;

};

