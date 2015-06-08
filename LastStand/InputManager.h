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


	void pollInputEvents();
};

