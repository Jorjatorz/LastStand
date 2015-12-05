#pragma once

#include "FController.h"

#include <list>

class FInputComponent;
class FActionMappingEvent;
class FCameraManager;
class Vector3;
class FUIManager;

//Controller that represents the human player
//This controller resides in the Fworld.
class FPlayerController: public FController
{
public:
	FPlayerController();
	~FPlayerController();

	void showMouseCursor(bool mouseS);
	bool isMouseCursorDisplayed();

	//Registers an input component into the inputCList
	//It will be placed on the top of the stack (end of the list)
	//Warning! This is called automatically in the inputComponent constructor
	void registerInputComponent(FInputComponent* comp);
	//Remove a component from a list.
	//Warning! this is called automatically from the InputComponent desructor
	void unregisterInputComponent(FInputComponent* comp);

	//Sends the input event to all the inputComponentsList in a Chain of Responsability pattern way
	//It also cheacks if this input event is also an Axis Mapping 
	void inputEventProduced(const FActionMappingEvent& eventTriggered);

	//Return a pointer to the camera manager
	FCameraManager* const getCameraManagerPtr() const
	{
		return _FCameraManagerPtr;
	}

	//Returns a pointer to the UI manaher
	FUIManager* const getUIManager() const
	{
		return _FUIManagerPtr;
	}

	//Adds a movement inout to the camera
	void addMovementInput(const Vector3& delta);
	//Adds a yaw input to the viewport camera
	void addYawInput(float degrees);
	//Adds a pitch inout to the viewport camera
	void addPitchInput(float degrees);

	//Returns the player world position
	Vector3 getPlayerWorldPosition();

	//Called every frame, it checks for axisMapping inputs
	virtual void tick(int deltaTime) override;

private:
	bool _showMouseCursor;

	//List containing all the inputComponents of the actors that can recive input
	//It is treated as a stack
	std::list<FInputComponent*> _inputComponentsList;

	//Pointer to the camera Manager
	FCameraManager* _FCameraManagerPtr;

	//UI Manager pointer
	FUIManager* _FUIManagerPtr;
};

