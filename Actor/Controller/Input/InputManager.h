#pragma once
#include "SDL.h"

enum class InputType
{
	Null,

	WindowChanges,

	Quit,

	ExitLevel,

	MovementUp,
	MovementDown,
	MovementRight,
	MovementLeft,
	MovementUpRight,
	MovementUpLeft,
	MovementDownRight,
	MovementDownLeft
};

class CInputManager
{
public:
	~CInputManager();

	bool initInput();

	InputType getInput();

private:
	SDL_Event* Input;
};

