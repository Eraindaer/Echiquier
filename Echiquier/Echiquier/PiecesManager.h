#pragma once
#include "King.h"
#include "Queen.h"
#include "Bishop.h"
#include "Knight.h"
#include "Rook.h"
#include "Pawn.h"
#include "InputManager.h"

class PiecesManager : public Pieces
{
public:
	PiecesManager(std::shared_ptr<WindowManager> window);
	~PiecesManager();

	void Event(InputManager* mouse);
	void Move(InputManager* mouse);
	void Draw();

private:
	std::vector<std::shared_ptr<Pieces>> pieces;
	SDL_Texture* tex;
	bool placeTaken[8][8];
	bool actionSelected;
};

