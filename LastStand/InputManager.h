#pragma once

#include "Singleton.h"

/*
* Singleton class that is in charge of handling the Hardware Input of the application
*/
class InputManager : public Singleton<InputManager>
{
public:
	InputManager();
	~InputManager();

	//Function which is called every frame and poll the hardware input events
	void pollInputEvents();
};

