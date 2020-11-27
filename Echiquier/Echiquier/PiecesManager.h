#pragma once
#include "King.h"
#include "Queen.h"
#include "Bishop.h"
#include "Knight.h"
#include "Rook.h"
#include "Pawn.h"

class PiecesManager
{
public:
	PiecesManager(std::shared_ptr<WindowManager> window, int player);
	~PiecesManager();

	void Move(std::shared_ptr<Pieces> pieceToMove, std::shared_ptr<PossiblePlacements> newPosition);
	void Promotion(int ID);
	void Draw();
	bool WillKingBeEndangered(std::shared_ptr<Pieces> currentPiece, std::shared_ptr<PossiblePlacements> eventualAction);
	void CheckAttackedPlace();
	void SetEnemy(PiecesManager* enemy);

	bool CheckMate();

public:
	SDL_Texture* tex;
	SDL_Texture* dotTex;
	std::vector<std::shared_ptr<Pieces>> rooks;
	std::vector<std::shared_ptr<Pieces>> pawns;
	PiecesManager* enemy;
	std::shared_ptr<WindowManager> window;
	bool turn;
	int side;
	int direction;
	std::vector<std::shared_ptr<PossiblePlacements>> actionList;
	std::vector<std::shared_ptr<Pieces>> piecesList;
	std::vector<std::shared_ptr<Pieces>> predictionEnemyPiecesList;
	std::vector<std::vector<std::shared_ptr<Pieces>>> pieces;
	std::vector<std::vector<std::shared_ptr<Pieces>>> predictionPieces;
	std::vector<std::vector<std::shared_ptr<Pieces>>> predictionEnemyPieces;
	bool predictionPlaces[8][8];
	bool predictionEnemyPlaces[8][8];
	std::shared_ptr<Pieces> king;
	std::shared_ptr<Pieces> predictionKing;
	std::shared_ptr<Pieces> enemyKing;
	bool placeTaken[8][8];
	bool placeAttacked[8][8];
};

