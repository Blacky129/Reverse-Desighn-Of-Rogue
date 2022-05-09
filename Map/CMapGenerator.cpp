#include "CMapGenerator.h"
#include <time.h>

CMap* CMapGenerator::createNewLevel(int RoomsCount)
{
	SizeOfMap = RoomsCount;

	Map = new CMap;

	Map->IndexMap = new CIndexMap;

	Map->IndexMap->allocateMap(CPosition{ (MAX_SIZE_OF_ROOM_X + 2) * int(sqrt(RoomsCount)),
		(MAX_SIZE_OF_ROOM_Y + 2) * int(sqrt(RoomsCount)) });

	createRooms();

	createPathesBetweenRoom();

	feelLabirithm();

	generateStartPosition();

	generateExitFromLevel();

	return Map;
}

void CMapGenerator::createRooms()
{
	int CountOfNoRealRoom = 0;
	CRoomGenerator RoomGenerator;
		
	for (int index = 0; index < SizeOfMap; index++)
	{
		CRoom* NewRoom = RoomGenerator.createRoom(getPositionOfRoomByIndex(index));

		Map->RoomsOfLevel.push_back(NewRoom);
	}

	CountOfNoRealRoom = Random.generateIntergerInRange(1, 2);
	for (int i = 0; i < CountOfNoRealRoom; i++)
	{
		int IndexOfRoom;
		do
		{
			IndexOfRoom = Random.generateIntergerInRange(0, 8);
		} while (canRoomBeNotReal(IndexOfRoom) == false);
		
		RoomGenerator.changeRoomType(Map->RoomsOfLevel.at(IndexOfRoom));
	}

	for (CRoom* Room : Map->RoomsOfLevel)
	{

		if (Room->canPathTroughRoom())
			CountOfRoomWhereCanEnter++;

		if (Room->getTypeOfRoom() == TypeOfRoom::RealRoom)
			moveRoomToIndexMap(Room);
	}
}

void CMapGenerator::moveRoomToIndexMap(CRoom* Room)
{
	//Top and Bottom Wall
	for (int X = Room->getTopLeftCornerPosition().X; X <= Room->getSizeOfRoom().X + Room->getTopLeftCornerPosition().X - 1; X++)
	{
		Map->IndexMap->Map[Room->getTopLeftCornerPosition().Y][X].Type = TypeOfCell::Wall;
		Map->IndexMap->Map[Room->getTopLeftCornerPosition().Y + Room->getSizeOfRoom().Y - 1][X].Type = TypeOfCell::Wall;
	}

	//Left and Right Wall
	for (int Y = Room->getTopLeftCornerPosition().Y; Y < Room->getSizeOfRoom().Y + Room->getTopLeftCornerPosition().Y - 1; Y++)
	{
		Map->IndexMap->Map[Y][Room->getTopLeftCornerPosition().X].Type = TypeOfCell::Wall;
		Map->IndexMap->Map[Y][Room->getTopLeftCornerPosition().X + Room->getSizeOfRoom().X - 1].Type = TypeOfCell::Wall;
	}

	//Floor
	for (int Y = 1; Y < Room->getSizeOfRoom().Y - 1; Y++)
	{
		for (int X = 1; X < Room->getSizeOfRoom().X - 1; X++)
			Map->IndexMap->Map[Y + Room->getTopLeftCornerPosition().Y][X + Room->getTopLeftCornerPosition().X].Type = TypeOfCell::Floor;
	}
}

bool CMapGenerator::canRoomBeNotReal(int IndexOfRoom)
{
	switch (IndexOfRoom)
	{
	case 3:
	case 5:
		if (Map->isRoomReal(1) || Map->isRoomReal(7))
			return true;
		else
			return false;
	case 1:
	case 7:
		if (Map->isRoomReal(3) || Map->isRoomReal(5))
			return true;
		else
			return false;
	default:
		return true;
	}
}

void CMapGenerator::createPathesBetweenRoom()
{
	setPathesBeetwenRooms();

	createMinimalPathes();

	createAddtionalPathes();
}

void CMapGenerator::setPathesBeetwenRooms()
{
	for (int index = 0; index < Map->RoomsOfLevel.size(); index++)
	{
		CRoom* CurrentRoom = Map->RoomsOfLevel.at(index);
		CPosition RoomPosition = getPositionOfRoomByIndex(index);

		switch (RoomPosition.X)
		{
		case 0:
			CurrentRoom->getPath(PathDirection::Left)->setToOutOfBound();
			CurrentRoom->getPath(PathDirection::Right)->setDirection(Map->RoomsOfLevel.at(index + 1));
			break;
		case 1:
			CurrentRoom->getPath(PathDirection::Left)->setDirection(Map->RoomsOfLevel.at(index - 1));
			CurrentRoom->getPath(PathDirection::Right)->setDirection(Map->RoomsOfLevel.at(index + 1));
			break;
		case 2:
			CurrentRoom->getPath(PathDirection::Left)->setDirection(Map->RoomsOfLevel.at(index - 1));
			CurrentRoom->getPath(PathDirection::Right)->setToOutOfBound();
			break;
		}

		switch (RoomPosition.Y)
		{
		case 0:
			CurrentRoom->getPath(PathDirection::Up)->setToOutOfBound();
			CurrentRoom->getPath(PathDirection::Down)->setDirection(Map->RoomsOfLevel.at(index + int(sqrt(SizeOfMap))));
			break;
		case 1:
			CurrentRoom->getPath(PathDirection::Up)->setDirection(Map->RoomsOfLevel.at(index - int(sqrt(SizeOfMap))));
			CurrentRoom->getPath(PathDirection::Down)->setDirection(Map->RoomsOfLevel.at(index + int(sqrt(SizeOfMap))));
			break;
		case 2:
			CurrentRoom->getPath(PathDirection::Up)->setDirection(Map->RoomsOfLevel.at(index - int(sqrt(SizeOfMap))));
			CurrentRoom->getPath(PathDirection::Down)->setToOutOfBound();
			break;
		}
	}
}

void CMapGenerator::createMinimalPathes()
{
	int index = 0;

	while (Map->RoomsOfLevel.at(index)->canPathTroughRoom() == false)
		index++;

	CRoom* CurrentRoom = Map->RoomsOfLevel.at(index);
	std::vector<CRoom*> RoomsStack;

	for (index = 0; index < CountOfRoomWhereCanEnter - 1; index++)
	{
		RoomsStack.push_back(CurrentRoom);
		PathDirection Direction;
		int Delay = 0;
		while (isAroundRoomNeedPath(&Direction, CurrentRoom) == false)
		{
			Delay++;
			CurrentRoom = RoomsStack.at(RoomsStack.size() - Delay);
		}
		setupPath(CurrentRoom, Direction);
		CRoom* NextRoom = CurrentRoom->getPath(Direction)->getRoomDestination();
		if (NextRoom->getTypeOfRoom() == TypeOfRoom::NoPathes)
			continue;
		CurrentRoom = NextRoom;
	}
}

bool CMapGenerator::isAroundRoomNeedPath(PathDirection* Direction, CRoom* Room)
{
	PathDirection FirstDirection = PathDirection(Random.generateIntergerInRange(0,3));
	for (int Delay = 0; Delay < 4; Delay++)
	{
		PathDirection CurrentDirection = PathDirection((int(FirstDirection) + Delay) % 4);

		if (Room->getPath(CurrentDirection)->getStatus() != PathStatus::NoDoor)
			continue;
		
		switch (Room->getPath(CurrentDirection)->getRoomDestination()->getTypeOfRoom())
		{
		case TypeOfRoom::NoPathes:
		case TypeOfRoom::EndOfPath:
			continue;

		default:
			break;
		}

		if (Room->getPath(CurrentDirection)->getRoomDestination()->isNeedPath())
		{
			*Direction = CurrentDirection;
			return true;
		}
	}
	return false;
}

CPosition CMapGenerator::generateDoorPosition(CRoom* Room, PathDirection Direction)
{
	CPosition DoorPosition{};

	switch (Direction)
	{
	case PathDirection::Up:
		DoorPosition.Y = Room->getTopLeftCornerPosition().Y;
		DoorPosition.X = Random.generateIntergerInRange(1, Room->getSizeOfRoom().X - 2) + Room->getTopLeftCornerPosition().X;
		break;
	case PathDirection::Down:
		DoorPosition.Y = Room->getTopLeftCornerPosition().Y + Room->getSizeOfRoom().Y - 1;
		DoorPosition.X =  Random.generateIntergerInRange(1, Room->getSizeOfRoom().X - 2) + Room->getTopLeftCornerPosition().X;
		break;
	case PathDirection::Right:
		DoorPosition.Y = Random.generateIntergerInRange(1, Room->getSizeOfRoom().Y - 2) + Room->getTopLeftCornerPosition().Y;
		DoorPosition.X = Room->getTopLeftCornerPosition().X + Room->getSizeOfRoom().X - 1;
		break;
	case PathDirection::Left:
		DoorPosition.Y = Random.generateIntergerInRange(1, Room->getSizeOfRoom().Y - 2) + Room->getTopLeftCornerPosition().Y ;
		DoorPosition.X = Room->getTopLeftCornerPosition().X;
		break;
	}

	return DoorPosition;
}

void CMapGenerator::createAddtionalPathes()
{
	for (CRoom* Room : Map->RoomsOfLevel)
	{
		for (int Direction = 0; Direction < 4; Direction++)
		{
			if (Room->getPath(PathDirection(Direction))->getStatus() != PathStatus::NoDoor)
				continue;

			if (Room->getPath(PathDirection(Direction))->getRoomDestination()->getTypeOfRoom() == TypeOfRoom::NoPathes)
				continue;

			if (Random.generateIntergerInRange(1, 100) <= CHANCE_OF_ADDTIONAL_PATH)
				setupPath(Room, PathDirection(Direction));
		}
	}
}

void CMapGenerator::feelLabirithm()
{
	for (CRoom* Room : Map->RoomsOfLevel)
	{
		if (Room->getTypeOfRoom() != TypeOfRoom::Labirithm)
			continue;

		std::vector<PathDirection> Directions;
		for (int Direction = 0; Direction < 4; Direction++)
		{
			if (Room->getPath(PathDirection(Direction))->getStatus() == PathStatus::HasDoor)
				Directions.push_back(PathDirection(Direction));
		}

		TypeOfLabirithm Type;

		switch (Directions.size())
		{
		default:
			continue;
		case 3:
		case 2:
			Type = TypeOfLabirithm(Random.generateIntergerInRange(0,2));
			break;
		case 4:
			Type = TypeOfLabirithm(rand() % 2 + 1);
			break;
		}

		switch (Type)
		{
		case TypeOfLabirithm::HalfWallsAsPath:
			if (paintHalfWallsAsPath(Room, Directions))
				break;
		case TypeOfLabirithm::PointInRoom:
			paintPointInRoom(Room, Directions);
			break;
		case TypeOfLabirithm::AllWallsAsPath:
			paintAllWallsAsPath(Room);
			break;
		}
	}
}

void CMapGenerator::setupPath(CRoom* Room, PathDirection Direction)
{
	CPosition DoorPositionFrom = generateDoorPosition(Room, Direction);
	Room->getPath(Direction)->enableDoor(DoorPositionFrom);
	if (Room->getTypeOfRoom() == TypeOfRoom::RealRoom)
		Map->IndexMap->Map[DoorPositionFrom.Y][DoorPositionFrom.X].Type = TypeOfCell::Door;

	PathDirection OppoiteDirection = getOppositeDirection(Direction);
	CRoom* NextRoom = Room->getPath(Direction)->getRoomDestination();
	CPosition DoorPositionTo = generateDoorPosition(NextRoom, OppoiteDirection);
	NextRoom->getPath(OppoiteDirection)->enableDoor(DoorPositionTo);
	if (NextRoom->getTypeOfRoom() == TypeOfRoom::RealRoom)
		Map->IndexMap->Map[DoorPositionTo.Y][DoorPositionTo.X].Type = TypeOfCell::Door;

	movePathToIndexMap(DoorPositionFrom, DoorPositionTo, Direction);
}

void CMapGenerator::movePathToIndexMap(CPosition From, CPosition To, PathDirection Direction)
{
	bool NeedAngle = true;
	int DX, DY;
	switch (Direction)
	{
	case PathDirection::Up:
	case PathDirection::Down:
		DX = To.Y - From.Y;
		if (DX == 0)
			NeedAngle = false;
		moveVerticalPathToIndexMap(From, To, NeedAngle);
		break;
	case PathDirection::Right:
	case PathDirection::Left:
		DY = To.X - From.X;
		if (DY == 0)
			NeedAngle = false;
		moveHorizontalPathToIndexMap(From, To, NeedAngle);
		break;
	}

}

void CMapGenerator::moveHorizontalPathToIndexMap(CPosition From, CPosition To, bool NeedAngle)
{
	int DX = To.X - From.X;
	int DY = To.Y - From.Y;

	if (DX < 0)
		int a = 1;
	
	int AnglePositionX = Random.generateIntergerInRange(1, abs(DX) - 1) * abs(DX) / DX;
	int Y = 0;
	for (int X = abs(DX)/DX; abs(X) < abs(DX); X += abs(DX)/DX)
	{
		if (NeedAngle)
		{
			if (X == AnglePositionX)
			{
				for (;abs(Y) < abs(DY); Y += abs(DY) / DY)
					Map->IndexMap->Map[Y + From.Y][X + From.X].Type = TypeOfCell::Path;
			}
		}
		Map->IndexMap->Map[Y + From.Y][X + From.X].Type = TypeOfCell::Path;
	}
}

void CMapGenerator::moveVerticalPathToIndexMap(CPosition From, CPosition To, bool NeedAngle)
{
	int DX = To.X - From.X;
	int DY = To.Y - From.Y;

	if (DY < 0)
		int a = 1;
	
	int AnglePositionY = Random.generateIntergerInRange(1, abs(DY) - 1) * abs(DY) / DY;
	int X = 0;
	for (int Y = abs(DY) / DY; abs(Y) < abs(DY); Y += abs(DY) / DY)
	{
		if (NeedAngle)
		{
			if (Y == AnglePositionY)
			{
				for (; abs(X) < abs(DX); X += abs(DX) / DX)
					Map->IndexMap->Map[Y + From.Y][X + From.X].Type = TypeOfCell::Path;
			}
		}
		Map->IndexMap->Map[Y + From.Y][X + From.X].Type = TypeOfCell::Path;
	}
}

bool CMapGenerator::paintHalfWallsAsPath(CRoom* Room, std::vector<PathDirection> Directions)
{
	int Sum = 0;

	for (PathDirection Direction : Directions)
		Sum += int(Direction);

	if (Directions.size() == 2)
	{
		switch (Sum)
		{
		case 4:
			Sum += rand() % 2 * 2;
			break;
		case 2:
			Sum = 3 + rand() % 2 + 2;
			break;
		default:
			return false;
		}
	}

	CPosition TopPoint, DownPoint, LeftPoint, RightPoint;

	switch (Sum)
	{
	case 3:
		TopPoint = Room->getPath(PathDirection::Up)->getDoorPosition();
		DownPoint = Room->getPath(PathDirection::Down)->getDoorPosition();

		//Through Path on Right Wall
		for (int Y = Room->getTopLeftCornerPosition().Y; Y < Room->getSizeOfRoom().Y + Room->getTopLeftCornerPosition().Y; Y++)
			Map->IndexMap->Map[Y][Room->getTopLeftCornerPosition().X + Room->getSizeOfRoom().X - 1].Type = TypeOfCell::Path;
		//Through Path On Top
		for (int X = TopPoint.X; X < Room->getSizeOfRoom().X + Room->getTopLeftCornerPosition().X; X++)
			Map->IndexMap->Map[Room->getTopLeftCornerPosition().Y][X].Type = TypeOfCell::Path;
		//Trough Path on Down
		for (int X = DownPoint.X; X < Room->getSizeOfRoom().X + Room->getTopLeftCornerPosition().X; X++)
			Map->IndexMap->Map[Room->getTopLeftCornerPosition().Y + Room->getSizeOfRoom().Y - 1][X].Type = TypeOfCell::Path;
		break;
	case 4:
		LeftPoint = Room->getPath(PathDirection::Left)->getDoorPosition();
		RightPoint = Room->getPath(PathDirection::Right)->getDoorPosition();

		//Through Path on Top
		for (int X = Room->getTopLeftCornerPosition().X; X < Room->getSizeOfRoom().X + Room->getTopLeftCornerPosition().X; X++)
			Map->IndexMap->Map[Room->getTopLeftCornerPosition().Y][X].Type = TypeOfCell::Path;
		//Through Path On Right
		for (int Y = RightPoint.Y; Y >= Room->getTopLeftCornerPosition().Y; Y--)
			Map->IndexMap->Map[Y][Room->getTopLeftCornerPosition().X + Room->getSizeOfRoom().X - 1].Type = TypeOfCell::Path;
		//Trough Path on Left
		for (int Y = LeftPoint.Y; Y >= Room->getTopLeftCornerPosition().Y; Y--)
			Map->IndexMap->Map[Y][Room->getTopLeftCornerPosition().X].Type = TypeOfCell::Path;
		break;
	case 5:
		TopPoint = Room->getPath(PathDirection::Up)->getDoorPosition();
		DownPoint = Room->getPath(PathDirection::Down)->getDoorPosition();
		
		//Through Path on Left
		for (int Y = Room->getTopLeftCornerPosition().Y; Y < Room->getSizeOfRoom().Y + Room->getTopLeftCornerPosition().Y; Y++)
			Map->IndexMap->Map[Y][Room->getTopLeftCornerPosition().X].Type = TypeOfCell::Path;
		//Through Path On Top
		for (int X = TopPoint.X; X >= Room->getTopLeftCornerPosition().X; X--)
			Map->IndexMap->Map[Room->getTopLeftCornerPosition().Y][X].Type = TypeOfCell::Path;
		//Trough Path on Down
		for (int X = DownPoint.X; X >= Room->getTopLeftCornerPosition().X; X--)
			Map->IndexMap->Map[Room->getTopLeftCornerPosition().Y + Room->getSizeOfRoom().Y - 1][X].Type = TypeOfCell::Path;
		break;
	case 6:
		LeftPoint = Room->getPath(PathDirection::Left)->getDoorPosition();
		RightPoint = Room->getPath(PathDirection::Right)->getDoorPosition();

		//Through Path on Down
		for (int X = Room->getTopLeftCornerPosition().X; X < Room->getSizeOfRoom().X + Room->getTopLeftCornerPosition().X; X++)
			Map->IndexMap->Map[Room->getTopLeftCornerPosition().Y + Room->getSizeOfRoom().Y - 1][X].Type = TypeOfCell::Path;
		//Through Path On Right
		for (int Y = RightPoint.Y; Y < Room->getSizeOfRoom().Y + Room->getTopLeftCornerPosition().Y; Y++)
			Map->IndexMap->Map[Y][Room->getTopLeftCornerPosition().X + Room->getSizeOfRoom().X - 1].Type = TypeOfCell::Path;
		//Trough Path on Left
		for (int Y = LeftPoint.Y; Y < Room->getSizeOfRoom().Y + Room->getTopLeftCornerPosition().Y; Y++)
			Map->IndexMap->Map[Y][Room->getTopLeftCornerPosition().X].Type = TypeOfCell::Path;
		break;
	default:
		break;
	}
	return true;
}

void CMapGenerator::paintPointInRoom(CRoom* Room, std::vector<PathDirection> Directions)
{
	CPosition PointInRoom{};
	PointInRoom.X = rand() % (Room->getSizeOfRoom().X - 2) + Room->getTopLeftCornerPosition().X + 1;
	PointInRoom.Y = rand() % (Room->getSizeOfRoom().Y - 2) + Room->getTopLeftCornerPosition().Y + 1;

	Map->IndexMap->Map[PointInRoom.Y][PointInRoom.X].Type = TypeOfCell::Path;

	for (PathDirection Direction : Directions)
	{
		CPosition DoorPosition = Room->getPath(Direction)->getDoorPosition();
		Map->IndexMap->Map[DoorPosition.Y][DoorPosition.X].Type = TypeOfCell::Path;
		int DX, DY;
		bool NeedAngle;
		switch (Direction)
		{
		case PathDirection::Up:
			DY = DoorPosition.Y - PointInRoom.Y;
			DX = DoorPosition.X - PointInRoom.X;
			NeedAngle = (DX == 0) ? true : false;
			if (abs(DY) > 2)
				moveVerticalPathToIndexMap(PointInRoom, DoorPosition, NeedAngle);
			else
			{
				for (int X = PointInRoom.X; X != DoorPosition.X; X += abs(DX) / DX)
					Map->IndexMap->Map[PointInRoom.Y - 1][X].Type = TypeOfCell::Path;
				Map->IndexMap->Map[PointInRoom.Y - 1][DoorPosition.X].Type = TypeOfCell::Path;
			}
			break;
		case PathDirection::Right:
			DY = DoorPosition.Y - PointInRoom.Y;
			DX = DoorPosition.X - PointInRoom.X;
			NeedAngle = (DY == 0) ? true : false;
			if (abs(DX) > 2)
				moveHorizontalPathToIndexMap(PointInRoom, Room->getPath(Direction)->getDoorPosition(), NeedAngle);
			else
			{
				for (int Y = PointInRoom.Y; Y != DoorPosition.Y; Y += abs(DY) / DY)
					Map->IndexMap->Map[Y][PointInRoom.X + 1].Type = TypeOfCell::Path;
				Map->IndexMap->Map[DoorPosition.Y][PointInRoom.X + 1].Type = TypeOfCell::Path;
			}
			break;
		case PathDirection::Left:
			DY = DoorPosition.Y - PointInRoom.Y;
			DX = DoorPosition.X - PointInRoom.X;
			NeedAngle = (DY == 0) ? true : false;
			if (abs(DX) > 2)
				moveHorizontalPathToIndexMap(PointInRoom, Room->getPath(Direction)->getDoorPosition(), NeedAngle);
			else
			{
				for (int Y = PointInRoom.Y; Y != DoorPosition.Y; Y += abs(DY) / DY)
					Map->IndexMap->Map[Y][PointInRoom.X - 1].Type = TypeOfCell::Path;
				Map->IndexMap->Map[DoorPosition.Y][PointInRoom.X - 1].Type = TypeOfCell::Path;
			}
			break;
		case PathDirection::Down:
			DY = DoorPosition.Y - PointInRoom.Y;
			DX = DoorPosition.X - PointInRoom.X;
			NeedAngle = (DX == 0) ? true : false;
			if (abs(DY) > 2)
				moveVerticalPathToIndexMap(PointInRoom, Room->getPath(Direction)->getDoorPosition(), NeedAngle);
			else
			{
				for (int X = PointInRoom.X; X != DoorPosition.X; X += abs(DX) / DX)
					Map->IndexMap->Map[PointInRoom.Y + 1][X].Type = TypeOfCell::Path;
				Map->IndexMap->Map[PointInRoom.Y + 1][DoorPosition.X].Type = TypeOfCell::Path;
			}
			break;
		}
	}
}

void CMapGenerator::paintAllWallsAsPath(CRoom* Room)
{
	for (int X = Room->getTopLeftCornerPosition().X; X < Room->getTopLeftCornerPosition().X + Room->getSizeOfRoom().X; X++)
	{
		Map->IndexMap->Map[Room->getTopLeftCornerPosition().Y][X].Type = TypeOfCell::Path;
		Map->IndexMap->Map[Room->getTopLeftCornerPosition().Y + Room->getSizeOfRoom().Y - 1][X].Type = TypeOfCell::Path;
	}

	for (int Y = Room->getTopLeftCornerPosition().Y; Y < Room->getTopLeftCornerPosition().Y + Room->getSizeOfRoom().Y; Y++)
	{
		Map->IndexMap->Map[Y][Room->getTopLeftCornerPosition().X].Type = TypeOfCell::Path;
		Map->IndexMap->Map[Y][Room->getTopLeftCornerPosition().X + Room->getSizeOfRoom().X - 1].Type = TypeOfCell::Path;
	}
}

CPosition CMapGenerator::getRandomPositionInRoom(CRoom* Room)
{
	CPosition RandomPosition;

	RandomPosition.X = Random.generateIntergerInRange(Room->getTopLeftCornerPosition().X + 1, Room->getTopLeftCornerPosition().X + Room->getSizeOfRoom().X - 2);
	RandomPosition.Y = Random.generateIntergerInRange(Room->getTopLeftCornerPosition().Y + 1, Room->getTopLeftCornerPosition().Y + Room->getSizeOfRoom().Y - 2);

	return RandomPosition;
}

void CMapGenerator::generateStartPosition()
{
	do 
	{
		IndexOfStartRoom = Random.generateIntergerInRange(0, SizeOfMap - 1);
	
	} while (Map->RoomsOfLevel.at(IndexOfStartRoom)->getTypeOfRoom() != TypeOfRoom::RealRoom);

	Map->StartPosition = getRandomPositionInRoom(Map->RoomsOfLevel.at(IndexOfStartRoom));
}

void CMapGenerator::generateExitFromLevel()
{
	int IndexOfExitRoom;
	do
	{
		IndexOfExitRoom = Random.generateIntergerInRange(0, SizeOfMap - 1);

	} while (Map->RoomsOfLevel.at(IndexOfExitRoom)->getTypeOfRoom() != TypeOfRoom::RealRoom || IndexOfExitRoom == IndexOfStartRoom);

	Map->ExitFromLevel = getRandomPositionInRoom(Map->RoomsOfLevel.at(IndexOfExitRoom));
}

CPosition CMapGenerator::getPositionOfRoomByIndex(int index)
{
	CPosition RoomPos = {};
	RoomPos.X = int(index % int(sqrt(SizeOfMap)));
	RoomPos.Y = int(index / int(sqrt(SizeOfMap)));
	return RoomPos;
}