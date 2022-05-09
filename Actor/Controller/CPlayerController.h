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

	CPlayer* Owner;
public:
	CPlayerController(CPlayer* Owner);

	CActorAction* actionActor();

	bool initInput();
private:
};

