#pragma once

class CActor;

enum class TypeOfAction
{
	Movement,
	Atack,
	ExitFromLevel,
	None
};

class CActorAction
{
protected:
	CActor* WhoDoIt;

	TypeOfAction Type;
public:
	CActorAction();
	CActorAction(CActor* Actor, TypeOfAction ActionType);

	virtual ~CActorAction() {};

	void changeType(TypeOfAction NewType);

	TypeOfAction getType();

	CActor* getWhoDoIt();
private:
};

