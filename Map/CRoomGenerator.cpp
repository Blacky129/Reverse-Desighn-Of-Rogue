#include "CRoomGenerator.h"
#include <stdlib.h>
#include <time.h>

CRoom* CRoomGenerator::createRoom(CPosition RoomPosistion)
{
	NewRoom = new CRoom;

	srand(time(0));

	for (int i = 0; i < 4; i++)
	{
		CPath* NewPath = new CPath;
		NewRoom->Pathes.push_back(NewPath);
	}

	generateRoomSize();

	generateTopLeftCornerPosition(RoomPosistion);

	setupLightInRoom();

	NewRoom->Type = TypeOfRoom::RealRoom;

	return NewRoom;
}


void CRoomGenerator::generateRoomSize()
{
	NewRoom->SizeOfRoom.X = Random.generateIntergerInRange(MIN_SIZE_OF_ROOM_X, MAX_SIZE_OF_ROOM_X);
	NewRoom->SizeOfRoom.Y = Random.generateIntergerInRange(MIN_SIZE_OF_ROOM_Y, MAX_SIZE_OF_ROOM_Y);
}

void CRoomGenerator::generateTopLeftCornerPosition(CPosition RoomPosition)
{
	if (NewRoom->SizeOfRoom.X == 0 || NewRoom->SizeOfRoom.Y == 0)
		return;

	NewRoom->TopLeftCornerPosition.X = Random.generateIntergerInRange(1, MAX_SIZE_OF_ROOM_X - NewRoom->getSizeOfRoom().X + 1) + RoomPosition.X * (MAX_SIZE_OF_ROOM_X + 2);
	NewRoom->TopLeftCornerPosition.Y = Random.generateIntergerInRange(1, MAX_SIZE_OF_ROOM_Y - NewRoom->getSizeOfRoom().Y + 1) + RoomPosition.Y * (MAX_SIZE_OF_ROOM_Y + 2);
}

void CRoomGenerator::setupLightInRoom()
{
	if (Random.generateIntergerInRange(1,100) <= CHANCE_OF_LIGHT)//MAGIC Number
		NewRoom->HasLight = true;
	else
		NewRoom->HasLight = false;
}

void CRoomGenerator::changeRoomType(CRoom* Room)
{

	int Type = Random.generateIntergerInRange(0, 2);
	switch (Type)
	{
	case 0:
		Room->Type = TypeOfRoom::NoPathes;
		break;
	case 1:
		Room->Type = TypeOfRoom::Labirithm;
		break;
	case 2:
		Room->Type = TypeOfRoom::EndOfPath;
		break;
	default:
		break;
	}
}

