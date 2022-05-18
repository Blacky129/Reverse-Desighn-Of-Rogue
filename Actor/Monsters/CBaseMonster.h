#pragma once

#include "../CActor.h"
#include "../Controller/CBaseAI.h"
#include "../../CPathFinder.h"

class CBaseMonster : public CActor
{
protected:
	CPathFinder* _PathFinder;

	CActor* _Goal;
public:
	CBaseMonster();

	void setGoal(CActor* NewGoal);
	
	CPosition getGoalPosition();

	CPathFinder* getPathFinder();

	void setPathFinder(CPathFinder* PathFinder);
private:

};
