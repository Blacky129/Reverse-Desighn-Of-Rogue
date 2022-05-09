#pragma once

#include "CMoveOrAtack.h"

class CAtack : public CMovementOrAtack
{
protected:
	CActor* ToWhom;
	int Damage;
public:
	CAtack(CMovementOrAtack* Action, CActor* ToWhom, int Damage);
private:
};