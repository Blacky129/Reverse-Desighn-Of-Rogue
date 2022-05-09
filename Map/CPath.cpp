#include "CPath.h"
#include <stdlib.h>

CRoom* CPath::getRoomDestination()
{
    if (Status == PathStatus::OutOfBound)
        return nullptr;

    return RoomDestination;
}

PathStatus CPath::getStatus()
{
    return Status;
}

CPosition CPath::getDoorPosition()
{
    if (Status != PathStatus::HasDoor)
        exit(1);

    return DoorPositionInHomeRoom;
}

void CPath::enableDoor(CPosition DoorPos)
{
    if (DoorPos.X < 0 || DoorPos.Y < 0 || 
        Status != PathStatus::NoDoor)
        return;

    Status = PathStatus::HasDoor;
    DoorPositionInHomeRoom = DoorPos;
}

void CPath::setDirection(CRoom* Destination)
{
    if (Destination == nullptr)
        return;

    Status = PathStatus::NoDoor;
    RoomDestination = Destination;
}

void CPath::setToOutOfBound()
{
    RoomDestination = nullptr;
    Status = PathStatus::OutOfBound;
    DoorPositionInHomeRoom = { -1, -1 };
}
