#pragma once

#include "CActorsStack.h"
#include "Map/CMap.h"
#include "Actor/Action/CMoveOrAtack.h"
#include "Actor/Action/CAtack.h"

class CGameLogic
{
private:
public:
	void playPlayer(CActorStack* ActorsStack, CMap* Map, bool* PlayerExitFromLevel);

	void playMonstersTurn(CActorStack* ActorsStack, CMap* Map);
private:
	bool canProvideAction(CActorAction* Action, CMap* Map);

	bool canMove(CMovementOrAtack* Action, CMap* Map);

	bool canExit(CActor* Actor, CMap* Map);

	void provideAction(CActorAction* Action, CMap* Map, bool* PlayerExit, CActorStack* ActorStack);

	void provideAtack(CMovementOrAtack* Action, CActorStack* ActorStack, CPosition ZoneOfAtack);

	void provideMovement(CMovementOrAtack* Action);
};