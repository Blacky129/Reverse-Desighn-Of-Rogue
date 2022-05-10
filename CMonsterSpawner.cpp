#include "CMonsterSpawner.h"

CBaseMonster* CMonsterSpawner::spawnMonster(CMap* Map, CActorStack* ActorStack)
{
    CBaseMonster* Monster = new CBaseMonster;

    CPosition MonsterPosition;
    do
    {
        MonsterPosition = Map->getPositionForSpawn(ActorStack->getPlayerPosition());
    } while (ActorStack->isAnyoneInPosition(MonsterPosition) == true);

    Monster->setActorPosition(MonsterPosition);

    //Monster->setActorPosition(ActorStack->getPlayerPosition() + CPosition{ 1,0 }); //TODO Delete

    return Monster;
}
