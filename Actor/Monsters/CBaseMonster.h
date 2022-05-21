#pragma once

#include "../CActor.h"
#include "../Controller/CBaseAI.h"
#include "../../CPathFinder.h"

class CBaseMonster : public CActor
{
protected:
	CPathFinder* _PathFinder;

	CActor* _Goal;

	bool _isActive;
public:
	CBaseMonster();

	void setGoal(CActor* NewGoal);
	
	CPosition getGoalPosition();

	CPathFinder* getPathFinder();

	void activateMonster();

	bool getActive();

	void setPathFinder(CPathFinder* PathFinder);
private:

};
