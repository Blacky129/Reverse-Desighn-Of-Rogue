#include "Screen.h"
#include <iostream>

CScreen::CScreen()
{
	this->Window = nullptr;
	this->Renderer = nullptr;
	this->Textures = new CTextureManager;
}


CScreen::~CScreen()
{
	SDL_DestroyWindow(Window);
	SDL_DestroyRenderer(Renderer);
	delete Textures;
	SDL_Quit();
}


bool CScreen::initSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	Window = SDL_CreateWindow("Rogue", 1000, 500, 720, 720, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (Window == nullptr)
	{
		SDL_Log("Unable to create Window: %s", SDL_GetError());
		return false;
	}

	Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
	if (this->Renderer == nullptr)
	{
		SDL_Log("Unable to create Renderer: %s", SDL_GetError());
		return false;
	}
	
	if (!this->Textures->loadTextures(Renderer))
	{
		return false;
	}

	return true;
}

void CScreen::updateWindow(CMap* Map, CActorStack* ActorsStack)
{
	//Scale of textures
	int ScreenHieght = 0;
	int ScreenWide = 0;

	float ScaleX, ScaleY;

	SDL_GetWindowSize(Window, &ScreenWide, &ScreenHieght);

	ScaleX = ScreenWide / 1184.0f;

	ScaleY = ScreenHieght / 448.0f;

	SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);

	SDL_RenderClear(Renderer);

	drawMap(Map, ScaleX, ScaleY);

	drawMonsters(ActorsStack->getMonstersPosition(), Map, ScaleX, ScaleY);

	drawHero(ActorsStack->getPlayerPosition(), ScaleX, ScaleY);

	Map->clearHeroVision();

	SDL_RenderPresent(Renderer);
}

void CScreen::drawMap(CMap* Map, float ScaleX, float ScaleY)
{
	for (int Y = 0; Y < Map->getSizeOfMap().Y; Y++)
	{
		for (int X = 0; X < Map->getSizeOfMap().X; X++)
		{
			SDL_Rect Position{ std::round((X + 1) * ScaleX * 16), std::round((Y + 1) * ScaleY * 16), std::round(16 * ScaleX), std::round(16 * ScaleY) };
			SDL_Texture* TextureForThisCell = Textures->getTextureForMapIndex(Map, CPosition{ X, Y });
			SDL_RenderCopy(Renderer, TextureForThisCell, NULL, &Position);
		}
	}
}

SDL_Window* CScreen::getWindow()
{
	return Window;
}

void CScreen::drawHero(CPosition HeroPos, float ScaleX, float ScaleY)
{
	SDL_Rect Position{ std::round((HeroPos.X + 1) * ScaleX * 16), std::round((HeroPos.Y + 1) * ScaleY * 16), std::round(16 * ScaleX), std::round(16 * ScaleY) };
	SDL_RenderCopy(this->Renderer, this->Textures->getHeroTex(), NULL, &Position);
}

void CScreen::drawMonsters(std::vector<MonsterPositionForRender> MonstersPosition, CMap* Map, float ScaleX, float ScaleY)
{
	for (MonsterPositionForRender Monster : MonstersPosition)
	{
		if (Map->isInHeroVision(Monster.Position) == false)
			continue;
		SDL_Rect Position{ std::round((Monster.Position.X + 1) * ScaleX * 16), std::round((Monster.Position.Y + 1) * ScaleY * 16), std::round(16 * ScaleX), std::round(16 * ScaleY) };
		SDL_RenderCopy(this->Renderer, Textures->getMonsterTex(), NULL, &Position);
	}
}
