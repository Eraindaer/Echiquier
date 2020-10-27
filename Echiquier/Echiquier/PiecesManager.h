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
	PiecesManager(std::shared_ptr<WindowManager> window, int player);
	~PiecesManager();

	void Event(InputManager* mouse);
	void Move(InputManager* mouse);
	void Draw();

	void SetEnemy(Pieces* enemy);

private:
	SDL_Texture* tex;
	SDL_Texture* dotTex;
	bool actionSelected;
	std::vector<std::shared_ptr<Pieces>> rooks;
};

