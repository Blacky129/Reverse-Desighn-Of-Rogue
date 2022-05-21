#pragma once

#include "Actor/CActor.h"
#include "Actor/CPlayer.h"
#include "Actor/Monsters/CBaseMonster.h"
#include "CPathFinder.h"
#include <vector>

class CMap;
//class IObserver;
struct MonsterPositionForRender
{
	CPosition Position;
	//TODO Type Of Monster
};

class CActorStack
{
private:
	CPlayer* _Player;

	CPathFinder* _PathFinder;

	std::vector<CBaseMonster*> _StackOfMonster;

	int _MonsterTurn;
public:
	void setPathFinder(CPathFinder* PathFinder);

	bool createPlayer(IObserver* NewObserver);

	void addMonster(CMap* Map);

	void setPlayerPosition(CPosition NewPosition);

	CActor* getActorInThisPosition(CPosition Position);

	CActorAction* getPlayerAction();

	CActorAction* getMonsterAction(bool* LastMonster);

	CPosition getPlayerPosition();

	std::vector<MonsterPositionForRender> getMonstersPosition();
private:

};
