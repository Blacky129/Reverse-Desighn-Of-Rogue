#pragma once

#include "Actor/CActor.h"
#include "Actor/CPlayer.h"
#include "Actor/Monsters/CBaseMonster.h"
#include <vector>

class CMap;

struct MonsterPositionForRender
{
	CPosition Position;
	//TODO Type Of Monster
};

class CPlayer;

class CActorStack
{
private:
	CPlayer* Player;

	std::vector<CBaseMonster*> StackOfMonster;
public:
	bool createPlayer();

	void addMonster(CMap* Map);

	void setPlayerPosition(CPosition NewPosition);

	CActor* getActorInThisPosition(CPosition Position);

	CActorAction* getPlayerAction();

	CPosition getPlayerPosition();

	std::vector<MonsterPositionForRender> getMonstersPosition();
private:

};
