#pragma once

#include "Actor/CActor.h"
#include "Actor/CPlayer.h"
#include <vector>

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
	//Stack Of Monsters
public:
	//Player methods
	bool createPlayer();

	void setPlayerPosition(CPosition NewPosition);

	bool isAnyoneInPosition(CPosition Position);

	//CPlayer* getPlayer(); TODO maybe delete

	CActorAction* getPlayerAction();

	CPosition getPlayerPosition();

	std::vector<MonsterPositionForRender> getMonstersPosition();
private:

};
