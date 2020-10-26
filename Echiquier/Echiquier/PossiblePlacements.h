#pragma once
#include "WindowManager.h"
class PossiblePlacements
{
public:
	PossiblePlacements(int x, int y);
	~PossiblePlacements();

public:
	int coordonates[2];
	SDL_Texture* tex;
	std::shared_ptr<WindowManager> window;
	SDL_Rect src;
};

