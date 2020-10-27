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

	void Draw(SDL_Texture* tex, SDL_Texture* dotTex);
	virtual void Move(bool placeTaken[8][8], Pieces& enemy);
	virtual void SetCoordonates(int x, int y, Pieces& boolean);
	void SetDirection(int direction);

public:
	short int coordonates[2];
	std::shared_ptr<WindowManager> window;
	SDL_Rect src;
	SDL_Rect dotSrc;
	bool isAttacked;
	bool selection;
	bool hasMoved;
	bool turn;
	int side;
	int direction;
	std::vector<std::shared_ptr<PossiblePlacements>> possibleActions;
	std::vector<std::shared_ptr<Pieces>> piecesList;
	std::vector<std::vector<std::shared_ptr<Pieces>>> pieces;
	bool placeTaken[8][8];
	Pieces* enemy;
	std::shared_ptr<Pieces> king;
};
