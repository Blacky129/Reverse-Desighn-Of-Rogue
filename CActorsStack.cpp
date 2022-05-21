#include "CActorsStack.h"
#include "CMonsterSpawner.h"

void CActorStack::setPathFinder(CPathFinder* PathFinder)
{
    if (_PathFinder == nullptr)
        _PathFinder = PathFinder;
}

bool CActorStack::createPlayer(IObserver* NewObserver)
{ 
    _Player = new CPlayer;
    
    if (_Player->initInput() == false)
        return false;

    _Player->addObserverForController(NewObserver);
    return true;
}

void CActorStack::addMonster(CMap* Map)
{
    CMonsterSpawner Spawner;
    CBaseMonster* NewMonster = Spawner.spawnMonster(Map, this);
    _StackOfMonster.push_back(NewMonster);
    NewMonster->setPathFinder(_PathFinder);
    NewMonster->setGoal(_Player);
    _MonsterTurn = 0;
}

CActorAction* CActorStack::getMonsterAction(bool* LastMonster, CMap* Map)
{
    CActorAction* Action;

    if (_StackOfMonster[_MonsterTurn]->getActive() == true)
    {
        Action = _StackOfMonster[_MonsterTurn]->playActor();
    }
    else
    {
        if (Map->isInSameRoom(_Player->getActorPosition(), _StackOfMonster[_MonsterTurn]->getActorPosition()))
            _StackOfMonster[_MonsterTurn]->activateMonster();
        
        Action = new CActorAction{ _StackOfMonster[_MonsterTurn], TypeOfAction::None};
    }

    if (_MonsterTurn == _StackOfMonster.size() - 1)
        *LastMonster = true;

    return Action;
}

void CActorStack::setPlayerPosition(CPosition NewPosition)
{
    _Player->setActorPosition(NewPosition);
}

CActor* CActorStack::getActorInThisPosition(CPosition Position)
{
    if (_Player->getActorPosition() == Position)
        return _Player;

    for (CBaseMonster* Monster : _StackOfMonster)
    {
        if (Monster->getActorPosition() == Position)
            return Monster;
    }

    return nullptr;
}

CActorAction* CActorStack::getPlayerAction()
{
    return _Player->playActor();
}

CPosition CActorStack::getPlayerPosition()
{
    return _Player->getActorPosition();
}

std::vector<MonsterPositionForRender> CActorStack::getMonstersPosition()
{
    std::vector<MonsterPositionForRender> Vector;
    for (CBaseMonster* Monster : _StackOfMonster)
    {
        Vector.push_back(MonsterPositionForRender{ Monster->getActorPosition() });
    }
    return Vector;
}
