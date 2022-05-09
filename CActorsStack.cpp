#include "CActorsStack.h"

bool CActorStack::createPlayer()
{ 
    Player = new CPlayer;
    return Player->initInput();
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
    return Player->playPlayer();
}

CPosition CActorStack::getPlayerPosition()
{
    return Player->getActorPosition();
}
