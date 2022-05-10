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

bool CActorStack::isAnyoneInPosition(CPosition Position)
{
    if (Player->getActorPosition() == Position)
        return true;
    
    //TODO iterac stack
    return false;
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
