#pragma once
#include "WindowManager.h"
#include "PossiblePlacements.h"
#include "Vector2D.h"
#include <vector>
class Pieces
{
public:
	Pieces();
	~Pieces();

	void Draw(SDL_Texture* tex);
	virtual void Move(bool placeTaken[8][8]);
	void SetCoordonates(int x, int y);

public:
	short int coordonates[2];
	std::shared_ptr<WindowManager> window;
	SDL_Rect src;
	bool selection;
	std::vector<std::shared_ptr<PossiblePlacements>> possibleActions;
};
