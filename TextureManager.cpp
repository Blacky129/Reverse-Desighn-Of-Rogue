#include "TextureManager.h"
#include "Map/CIndexMap.h"

CTextureManager::CTextureManager()
{
	HeroTex = nullptr;
	LeftRightWallTex = nullptr;
	TopDownWallTex = nullptr;
	DoorTex = nullptr;
	TopLeftCornerTex = nullptr;
	TopRightCornerTex = nullptr;
	DownLeftCornerTex = nullptr;
	DownRightCornerTex = nullptr;
	PathTex = nullptr;
	FloorTex = nullptr;
	EndOfLevelTex = nullptr;
}

CTextureManager::~CTextureManager()
{
	SDL_DestroyTexture(HeroTex);
	SDL_DestroyTexture(LeftRightWallTex);
	SDL_DestroyTexture(TopDownWallTex);
	SDL_DestroyTexture(DoorTex);
	SDL_DestroyTexture(TopLeftCornerTex);
	SDL_DestroyTexture(TopRightCornerTex);
	SDL_DestroyTexture(DownLeftCornerTex);
	SDL_DestroyTexture(DownRightCornerTex);
	SDL_DestroyTexture(PathTex);
	SDL_DestroyTexture(FloorTex);
	SDL_DestroyTexture(EndOfLevelTex);
}

bool CTextureManager::loadTextures(SDL_Renderer* Renderer)
{

	SDL_Surface* Image = nullptr;

	//Load Hero
	Image = SDL_LoadBMP("./assets/textures/Hero_Tex.bmp");
	if (!Image)
	{
		SDL_Log("Unable to load Image Hero: %s", SDL_GetError());
		return false;
	}

	this->HeroTex = SDL_CreateTextureFromSurface(Renderer, Image);
	if (this->HeroTex == nullptr)
	{
		SDL_Log("Unable to crete Hero Textre: %s", SDL_GetError());
		return false;
	}

	//Load RightLeftWall
	Image = SDL_LoadBMP("./assets/textures/LeftRightWall_Tex.bmp");
	if (!Image)
	{
		SDL_Log("Unable to load Image RightLeftWall: %s", SDL_GetError());
		return false;
	}

	this->LeftRightWallTex = SDL_CreateTextureFromSurface(Renderer, Image);
	if (this->LeftRightWallTex == nullptr)
	{
		SDL_Log("Unable to crete RightLeftWall Textre: %s", SDL_GetError());
		return false;
	}

	//Load TopDownWall
	Image = SDL_LoadBMP("./assets/textures/TopDownWall_Tex.bmp");
	if (!Image)
	{
		SDL_Log("Unable to load Image TopDownWall: %s", SDL_GetError());
		return false;
	}

	this->TopDownWallTex = SDL_CreateTextureFromSurface(Renderer, Image);
	if (this->TopDownWallTex == nullptr)
	{
		SDL_Log("Unable to crete TopDownWall Textre: %s", SDL_GetError());
		return false;
	}

	//Load TopLeftCornerWall
	Image = SDL_LoadBMP("./assets/textures/TopLeftCornerWall_Tex.bmp");
	if (!Image)
	{
		SDL_Log("Unable to load Image TopLeftCornerWall: %s", SDL_GetError());
		return false;
	}

	this->TopLeftCornerTex = SDL_CreateTextureFromSurface(Renderer, Image);
	if (this->TopLeftCornerTex == nullptr)
	{
		SDL_Log("Unable to crete TopLeftCornerWall Textre: %s", SDL_GetError());
		return false;
	}
	
	//Load TopRightCornerWall
	Image = SDL_LoadBMP("./assets/textures/TopRightCornerWall_Tex.bmp");
	if (!Image)
	{
		SDL_Log("Unable to load Image TopRightCornerWall: %s", SDL_GetError());
		return false;
	}

	this->TopRightCornerTex = SDL_CreateTextureFromSurface(Renderer, Image);
	if (this->TopRightCornerTex == nullptr)
	{
		SDL_Log("Unable to crete TopRightCornerWall Textre: %s", SDL_GetError());
		return false;
	}

	//Load DownRightCorner
	Image = SDL_LoadBMP("./assets/textures/DownRightCorner_Tex.bmp");
	if (!Image)
	{
		SDL_Log("Unable to load Image DownRightCorner: %s", SDL_GetError());
		return false;
	}

	this->DownRightCornerTex = SDL_CreateTextureFromSurface(Renderer, Image);
	if (this->DownRightCornerTex == nullptr)
	{
		SDL_Log("Unable to crete DownRightCorner Textre: %s", SDL_GetError());
		return false;
	}

	//Load DownLeftCorner
	Image = SDL_LoadBMP("./assets/textures/DownLeftCorner_Tex.bmp");
	if (!Image)
	{
		SDL_Log("Unable to load Image DownLeftCorner: %s", SDL_GetError());
		return false;
	}

	this->DownLeftCornerTex = SDL_CreateTextureFromSurface(Renderer, Image);
	if (this->DownLeftCornerTex == nullptr)
	{
		SDL_Log("Unable to crete DownLeftCorner Textre: %s", SDL_GetError());
		return false;
	}

	//Load Door
	Image = SDL_LoadBMP("./assets/textures/Door_Tex.bmp");
	if (!Image)
	{
		SDL_Log("Unable to load Image Door: %s", SDL_GetError());
		return false;
	}

	this->DoorTex = SDL_CreateTextureFromSurface(Renderer, Image);
	if (this->DoorTex == nullptr)
	{
		SDL_Log("Unable to crete Door Textre: %s", SDL_GetError());
		return false;
	}

	//Load Path
	Image = SDL_LoadBMP("./assets/textures/Path_Tex.bmp");
	if (!Image)
	{
		SDL_Log("Unable to load Image Path: %s", SDL_GetError());
		return false;
	}

	this->PathTex = SDL_CreateTextureFromSurface(Renderer, Image);
	if (this->PathTex == nullptr)
	{
		SDL_Log("Unable to crete Path Textre: %s", SDL_GetError());
		return false;
	}

	//Load End of Level
	Image = SDL_LoadBMP("./assets/textures/Exit_Tex.bmp");
	if (!Image)
	{
		SDL_Log("Unable to load Image EndOfLevel: %s", SDL_GetError());
		return false;
	}

	this->EndOfLevelTex = SDL_CreateTextureFromSurface(Renderer, Image);
	if (this->EndOfLevelTex == nullptr)
	{
		SDL_Log("Unable to crete EndOfLevl Textre: %s", SDL_GetError());
		return false;
	}

	//Load Floor
	Image = SDL_LoadBMP("./assets/textures/Floor_Tex.bmp");
	if (!Image)
	{
		SDL_Log("Unable to load Image Floor: %s", SDL_GetError());
		return false;
	}

	this->FloorTex = SDL_CreateTextureFromSurface(Renderer, Image);
	if (this->FloorTex == nullptr)
	{
		SDL_Log("Unable to crete Floor Textre: %s", SDL_GetError());
		return false;
	}

	//Load BaseMonster
	Image = SDL_LoadBMP("./assets/textures/BaseMonster_Tex.bmp");
	if (!Image)
	{
		SDL_Log("Unable to load Image Floor: %s", SDL_GetError());
		return false;
	}

	BaseMonsterTex = SDL_CreateTextureFromSurface(Renderer, Image);
	if (BaseMonsterTex == nullptr)
	{
		SDL_Log("Unable to crete Floor Textre: %s", SDL_GetError());
		return false;
	}

	SDL_FreeSurface(Image);

	return true;
}

SDL_Texture* CTextureManager::getTextureForMapIndex(CMap* Map, CPosition Position)
{
	switch (Map->getCellForRender(Position))
	{
	case TypeOfCell::Floor:
		return FloorTex;
	case TypeOfCell::Door:
		return DoorTex;
	case TypeOfCell::Path:
		return PathTex;
	case TypeOfCell::Exit:
		return EndOfLevelTex;
	case TypeOfCell::Wall:
		if (isWallOrDoor(Map->getTypeOfCell(CPosition{ Position.X,  Position.Y + 1})))
		{
			if (isWallOrDoor(Map->getTypeOfCell(CPosition{ Position.X - 1, Position.Y }))) return this->TopRightCornerTex;
			if (isWallOrDoor(Map->getTypeOfCell(CPosition{ Position.X + 1, Position.Y }))) return this->TopLeftCornerTex;
			return LeftRightWallTex;
		}
		else if (isWallOrDoor(Map->getTypeOfCell(CPosition{ Position.X, Position.Y - 1 })))
		{
			if (isWallOrDoor(Map->getTypeOfCell(CPosition{ Position.X - 1, Position.Y }))) return this->DownRightCornerTex;
			if (isWallOrDoor(Map->getTypeOfCell(CPosition{ Position.X + 1, Position.Y }))) return this->DownLeftCornerTex;
			return LeftRightWallTex;
		}
		else
			return TopDownWallTex;
	default:
		return nullptr;
	}
}

bool CTextureManager::isWallOrDoor(TypeOfCell Cell)
{
	if (Cell == TypeOfCell::Door || Cell == TypeOfCell::Wall)
		return true;
	return false;
}

SDL_Texture* CTextureManager::getHeroTex()
{
	return this->HeroTex;
}

SDL_Texture* CTextureManager::getLeftRightWall()
{
	return this->LeftRightWallTex;
}

SDL_Texture* CTextureManager::getTopDownWall()
{
	return this->TopDownWallTex;
}

SDL_Texture* CTextureManager::getDoor()
{
	return this->DoorTex;
}

SDL_Texture* CTextureManager::getTopLeftCorner()
{
	return this->TopLeftCornerTex;
}

SDL_Texture* CTextureManager::getTopRightCorner()
{
	return this->TopRightCornerTex;
}

SDL_Texture* CTextureManager::getDownLeftCorner()
{
	return this->DownLeftCornerTex;
}

SDL_Texture* CTextureManager::getDownRightCorner()
{
	return this->DownRightCornerTex;
}

SDL_Texture* CTextureManager::getPath()
{
	return this->PathTex;
}

SDL_Texture* CTextureManager::getMonsterTex()
{
	return BaseMonsterTex;
}
