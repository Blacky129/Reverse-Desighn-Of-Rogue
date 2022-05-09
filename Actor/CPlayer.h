#pragma once

#include "CActor.h"
#include "Controller/CPlayerController.h"
#include "Action/CActorAction.h"

class CPlayerController;
class CActorAction;
class CController;

class CPlayer : public CActor
{
private:
	CPlayerController* Controller;
public:
	CPlayer();

	CActorAction* playPlayer();

	bool initInput();
private:
};

