#include "CPlayerController.h"
#include "../Action/CMoveOrAtack.h"
#include "../CPlayer.h"

bool CPlayerController::initInput()
{
    Input = new CInputManager;
    return Input->initInput();
}

CPlayerController::CPlayerController(CPlayer* Player)
{
	Owner = Player;
	Input = nullptr;
}

CPosition getVector(InputType Input)
{
	CPosition Vector = { 0, 0 };

	switch (Input)
	{
	case InputType::MovementUp:
		Vector = {+0, -1};
		break;
	case InputType::MovementDown:
		Vector = { +0, +1};
		break;
	case InputType::MovementRight:
		Vector = { +1, +0};
		break;
	case InputType::MovementLeft:
		Vector = { -1, +0};
		break;
	case InputType::MovementUpRight:
		Vector = { +1, -1};
		break;
	case InputType::MovementUpLeft:
		Vector = { -1, -1 };
		break;
	case InputType::MovementDownRight:
		Vector = { +1, +1};
		break;
	case InputType::MovementDownLeft:
		Vector = { -1, +1};
		break;
	default:
		break;
	}
	return Vector;
}

CActorAction* CPlayerController::actionActor()
{
    InputType CurrentInput = Input->getInput();
	CActorAction* Result = new CActorAction(Owner, TypeOfAction::None);

	//CMovementOrAtack* TMP = new CMovementOrAtack(Owner, TypeOfAction::Movement);
	switch (CurrentInput)
	{
	case InputType::Quit:
		break;
	case InputType::ExitLevel:
		Result->changeType(TypeOfAction::ExitFromLevel);
		break;

	case InputType::MovementUp:
	case InputType::MovementDown:
	case InputType::MovementRight:
	case InputType::MovementLeft:
	case InputType::MovementUpRight:
	case InputType::MovementUpLeft:
	case InputType::MovementDownRight:
	case InputType::MovementDownLeft:
		Result = new CMovementOrAtack(Result, Owner->getActorPosition(), Owner->getActorPosition() + getVector(CurrentInput));
		break;
	default:
		break;
	}
	return Result;
}