#include "CMonsterSpawner.h"

CBaseMonster* CMonsterSpawner::spawnMonster(CMap* Map, CActorStack* ActorStack)
{
    CBaseMonster* Monster = new CBaseMonster;

    CPosition MonsterPosition;
    do
    {
        MonsterPosition = Map->getPositionForSpawn(ActorStack->getPlayerPosition());
    } while (ActorStack->getActorInThisPosition(MonsterPosition) != nullptr);

    Monster->setActorPosition(MonsterPosition);

    return Monster;
}
