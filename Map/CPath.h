#pragma once

#include "CPosition.h"

class CRoom;

enum class PathStatus
{
	HasDoor,
	NoDoor,
	OutOfBound
};

class CPath
{
public:
	CRoom* getRoomDestination();

	PathStatus getStatus();

	CPosition getDoorPosition();

	void enableDoor(CPosition DoorPos);

	void setDirection(CRoom* Destination);

	void setToOutOfBound();
private:
	CRoom* RoomDestination;

	PathStatus Status;

	CPosition DoorPositionInHomeRoom;
};

