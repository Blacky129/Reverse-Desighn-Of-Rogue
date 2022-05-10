#pragma once

#include "CMoveOrAtack.h"

class CAtack : public CMovementOrAtack
{
protected:
	CActor* _ToWhom;
	int _Damage;
public:
	CAtack(CMovementOrAtack* Action, CActor* ToWhom, int Damage);
private:
};