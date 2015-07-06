#pragma once

#include "FComponent.h"

//Input components are components that auto registers to the current PlayerController and handles the input events received from this one.
//This input event can be accepted and terminated or accepted and passed to the next input component on the playerController stack (similar to the Chain of Responsibility's pattern)
class FInputComponent: public FComponent
{
public:
	FInputComponent(std::string componentName, FActor* actor);
	~FInputComponent();

	void bindActionMapping();
	void bindAxisMapping();

	//Checks for Axis input events each frame
	virtual void tick(float deltaTime);

};

