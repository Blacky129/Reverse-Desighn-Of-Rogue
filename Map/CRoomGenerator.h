#pragma once

#include "CRoom.h"
#include "../CRandomGenrator.h"

#define MAX_SIZE_OF_ROOM_X 22
#define MAX_SIZE_OF_ROOM_Y 6
#define MIN_SIZE_OF_ROOM_X 4
#define MIN_SIZE_OF_ROOM_Y 4

class CRoomGenerator
{
private:
	CRandomGenrator Random;

	CRoom* NewRoom = nullptr;

	const int CHANCE_OF_LIGHT = 90;
public:
	CRoom* createRoom(CPosition RoomPos);

	void changeRoomType(CRoom* Room);

private:
	void generateRoomSize();

	void generateTopLeftCornerPosition(CPosition RoomPosition);

	void setupLightInRoom();
};

