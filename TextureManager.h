#pragma once

#include "SDL.h"
#include "Map/CMap.h"

class CTextureManager
{
public:
	CTextureManager();
	~CTextureManager();



	/*
	* Try to load images
	* True: if success
	* False: if cannot load. Call SDL_Error
	*/
	bool loadTextures(SDL_Renderer* Renderer);

	/*
	* Return Texture of cell in [X, Y] by Catetory of this cell 
	*/
	SDL_Texture* getTextureForMapIndex(CMap* Map,CPosition Position);

	bool isWallOrDoor(TypeOfCell Cell);
	//Getters Start
	SDL_Texture* getHeroTex();

	SDL_Texture* getLeftRightWall();

	SDL_Texture* getTopDownWall();

	SDL_Texture* getDoor();

	SDL_Texture* getTopLeftCorner();

	SDL_Texture* getTopRightCorner();

	SDL_Texture* getDownLeftCorner();

	SDL_Texture* getDownRightCorner();

	SDL_Texture* getPath();

	SDL_Texture* getMonsterTex();

	//Getters End
private:

	//List of Textures
	SDL_Texture* HeroTex;

	SDL_Texture* LeftRightWallTex;

	SDL_Texture* TopDownWallTex;
	
	SDL_Texture* DoorTex;
	
	SDL_Texture* TopLeftCornerTex;
	
	SDL_Texture* TopRightCornerTex;
	
	SDL_Texture* DownLeftCornerTex;
	
	SDL_Texture* DownRightCornerTex;

	SDL_Texture* PathTex;

	SDL_Texture* FloorTex;

	SDL_Texture* EndOfLevelTex;

	SDL_Texture* BaseMonsterTex;
		
};
