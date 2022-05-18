#include "CBaseAI.h"
#include "../Monsters/CBaseMonster.h"
#include "../Action/CMoveOrAtack.h"

CActorAction* CBaseAI::actionActor()
{
    CBaseMonster* TMP = dynamic_cast<CBaseMonster*>(Owner);
    CPosition Vector = TMP->getPathFinder()->getVectorToGoal(TMP->getActorPosition(), TMP->getGoalPosition());
    
    if (Vector.getVectorLength() == 0)
        return new CActorAction{Owner, TypeOfAction::None};
    
    return new CMovementOrAtack{ Owner, Owner->getActorPosition(), Owner->getActorPosition() + Vector };
}
