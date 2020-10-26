#pragma once
#include "Player.h"
#include "Computer.h"

class Board
{
public:
	Board(std::shared_ptr<WindowManager> window);
	~Board();

	void LoadPieces();
	void DrawPieces();

private:
	SDL_Texture* tex;
	std::shared_ptr<WindowManager> window;

public:
	Player* player;
	Computer* cpu;
};

