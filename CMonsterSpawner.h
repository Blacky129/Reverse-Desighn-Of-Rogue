#pragma once

#include "Map/CMap.h"
#include "CActorsStack.h"
#include "Actor/Monsters/CBaseMonster.h"

class CMonsterSpawner
{
public:
	CBaseMonster* spawnMonster(CMap* Map, CActorStack* ActorStack);
private:

};