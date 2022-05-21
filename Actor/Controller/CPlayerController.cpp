#include "CPlayerController.h"
#include "../Action/CMoveOrAtack.h"
#include "../CPlayer.h"

bool CPlayerController::initInput()
{
    Input = new CInputManager;
    return Input->initInput();
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
	bool RerenderEvent = false;
	InputType CurrentInput;
	do
	{
		CurrentInput = Input->getInput();

		if (CurrentInput == InputType::WindowChanges)
			notify(EVENT_TYPE::RERENDER_EVENT);
	} while (CurrentInput == InputType::WindowChanges);
	CActorAction* Result = new CActorAction(Owner, TypeOfAction::None);
	
	switch (CurrentInput)
	{
	case InputType::WindowChanges:

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