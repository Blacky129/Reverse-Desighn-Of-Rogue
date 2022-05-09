#pragma once

#include "SDL.h"
#include "TextureManager.h"
#include "Map/CIndexMap.h"
#include "Map/CPosition.h"
#include "CActorsStack.h"
#undef main

#define DEFAULT_X_SIZE_WINDOW 1184
#define DEFAULT_Y_SIZE_WINDOW 448

class CScreen
{
public:
	CScreen();
	~CScreen();

	bool initSDL();

	//Render
	void updateWindow(CMap* Map, CActorStack* ActorsStack);

	void drawMap(CMap* Map, float ScaleX, float ScaleY);

	SDL_Window* getWindow();

	void drawHero(CPosition HeroPos, float ScaleX, float ScaleY);

private:
	//Windows
	SDL_Window* Window;

	SDL_Renderer* Renderer;

	CTextureManager* Textures;

	//Scale there
};

