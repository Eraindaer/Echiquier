#pragma once
#include "WindowManager.h"
#include "PossiblePlacements.h"
#include "Vector2D.h"
#include <vector>
#define PAWNVALUE 100
#define ROOKVALUE 320
#define KNIGHTVALUE 330
#define BISHOPVALUE 500
#define QUEENVALUE 900
#define KINGVALUE 20000
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
	bool isCastling;
	bool checkMate;
	std::shared_ptr<Pieces> rookCastling;
	int value;
	int ID;
	
	int attackingValue, defendingValue;
	std::vector<std::shared_ptr<PossiblePlacements>> possibleActions;
	std::vector<std::vector<int>> pieceSquareTable;
	
	std::shared_ptr<Pieces> king;
};
