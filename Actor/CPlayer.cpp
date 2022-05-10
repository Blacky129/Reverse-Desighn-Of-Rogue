#include "CPlayer.h"

CPlayer::CPlayer()
{
    Controller = nullptr;
    Type = TypeOfActor::Rogue;
}

bool CPlayer::initInput()
{
    Controller = new CPlayerController(this);
    return dynamic_cast<CPlayerController*>(Controller)->initInput();
}
