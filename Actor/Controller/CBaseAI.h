#pragma once

#include "./CController.h"

class CBaseAI : public CController
{
private:

public:
	using CController::CController;

	CActorAction* actionActor();

private:

};