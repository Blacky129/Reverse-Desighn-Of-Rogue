#pragma once

#include "CActor.h"
#include "Controller/CPlayerController.h"
#include "Action/CActorAction.h"

class CPlayerController;
class CController;
class IObserver;

class CPlayer : public CActor
{
private:
public:
	CPlayer();

	bool initInput();

	void addObserverForController(IObserver* NewObserver);
private:
};

