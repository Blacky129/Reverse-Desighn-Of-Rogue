#pragma once

class CController;

#include "CController.h"
#include "Input/InputManager.h"
#include "../Action/CActorAction.h"

class CPlayer;
class CActorAction;

class CPlayerController : public CController
{
private:
	CInputManager* Input;

public:
	using CController::CController;

	CActorAction* actionActor();

	bool initInput();
private:
};

