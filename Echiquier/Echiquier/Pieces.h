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
	virtual void Move(bool placeTaken[8][8], bool enemyPlaceTaken[8][8], bool placeAttackedByEnemy[8][8], std::vector<std::vector<std::shared_ptr<Pieces>>>& allyPieces, std::vector<std::vector<std::shared_ptr<Pieces>>>& enemyPieces);
	virtual void SetCoordonates(int x, int y);

	void SetKing(std::shared_ptr<Pieces> king);

public:
	short int coordonates[2];
	std::shared_ptr<WindowManager> window;
	SDL_Rect src;
	SDL_Rect dotSrc;
	bool isAttacked;
	bool isDefended;
	bool selection;
	bool hasMoved;
	
	
	std::vector<std::shared_ptr<PossiblePlacements>> possibleActions;
	
	std::shared_ptr<Pieces> king;
};
