#include "CActorsStack.h"
#include "CMonsterSpawner.h"

bool CActorStack::createPlayer()
{ 
    Player = new CPlayer;
    return Player->initInput();
}

void CActorStack::addMonster(CMap* Map)
{
    CMonsterSpawner Spawner;
    StackOfMonster.push_back(Spawner.spawnMonster(Map, this));
}

void CActorStack::setPlayerPosition(CPosition NewPosition)
{
    Player->setActorPosition(NewPosition);
}

CActor* CActorStack::getActorInThisPosition(CPosition Position)
{
    if (Player->getActorPosition() == Position)
        return Player;

    for (CBaseMonster* Monster : StackOfMonster)
    {
        if (Monster->getActorPosition() == Position)
            return Monster;
    }

    return nullptr;
}

CActorAction* CActorStack::getPlayerAction()
{
    return Player->playActor();
}

CPosition CActorStack::getPlayerPosition()
{
    return Player->getActorPosition();
}

std::vector<MonsterPositionForRender> CActorStack::getMonstersPosition()
{
    std::vector<MonsterPositionForRender> Vector;
    for (CBaseMonster* Monster : StackOfMonster)
    {
        Vector.push_back(MonsterPositionForRender{ Monster->getActorPosition() });
    }
    return Vector;
}
