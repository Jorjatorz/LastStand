#pragma once

#include "Singleton.h"

#include <unordered_map>
#include <set>

class Vector3;
class FPlayerController;

/*
* Singleton class that is in charge of handling the Hardware Input of the application
*/
class FInputManager : public Singleton<FInputManager>
{
public:
	//Corresponds to the SDL scancodes
	enum keyTypeEnum
	{
		UNKNOWN = 0,

		MOUSE_LEFT_BUTTON = 251,
		MOUSE_MIDDLE_BUTTON = 252,
		MOUSE_RIGHT_BUTTON = 253,
		MOUSE_X = 254, //Movement of mouse in X axis
		MOUSE_Y = 255,//Movement of mouse in Y axis

		A = 4,
		B = 5,
		C = 6,
		D = 7,
		E = 8,
		F = 9,
		G = 10,
		H = 11,
		I = 12,
		J = 13,
		K = 14,
		L = 15,
		M = 16,
		N = 17,
		O = 18,
		P = 19,
		Q = 20,
		R = 21,
		S = 22,
		T = 23,
		U = 24,
		V = 25,
		W = 26,
		X = 27,
		Y = 28,
		Z = 29,

		NUM_1 = 30,
		NUM_2 = 31,
		NUM_3 = 32,
		NUM_4 = 33,
		NUM_5 = 34,
		NUM_6 = 35,
		NUM_7 = 36,
		NUM_8 = 37,
		NUM_9 = 38,
		NUM_0 = 39,

		RETURN = 40,
		ESCAPE = 41,
		BACKSPACE = 42,
		TAB = 43,
		SPACE = 44
	};

	FInputManager();
	~FInputManager();

	//Function which is called every frame and poll the hardware input events
	void pollInputEvents();

	//Adds new Action Mapping string to a key
	void addActionMapping(std::string actionName, keyTypeEnum keyCode);
	//Adds new Axis Mapping string to a key
	void addAxisMapping(std::string axisName, keyTypeEnum keyCode, float scale);
	//Returns the scale of the mapping
	float getAxisValue(std::string axisName);

	//Return the position of the mouse
	Vector3 getMousePosition();

private:
	//Mouse positions
	float _mouseX;
	float _mouseY;

	//Action mapping map. (key, binding name)
	std::unordered_map<int, std::set<std::string>> _actionMappingMap;
	//Axis mapping map. (key, <bindingName, scale>)
	std::unordered_map<int, std::pair<std::set<std::string>, float>> _axisMappingMap;
	std::unordered_map<std::string, float> _axisMappingCurrentScaleValueMap;

	//Calculate and sends the input event information to the playerController (from the action and axis mapping)
	void informAboutInputEventProduced_Pressed(int key, FPlayerController* currentController);
	void informAboutInputEventProduced_Released(int key, FPlayerController* currentController);
	//Sets the correct axis mappings values for mouseX and mouseY axis mappings.
	void handleAxisMappingsForMouseMotion(int relativeMovementX, int relativeMovementY);
};

