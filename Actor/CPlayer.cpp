#include "CPlayer.h"

CPlayer::CPlayer()
{
    Controller = nullptr;
    Type = TypeOfActor::Rogue;
}

CActorAction* CPlayer::playPlayer()
{
    return Controller->actionActor();
}

bool CPlayer::initInput()
{
    Controller = new CPlayerController(this);
    return Controller->initInput();
}
