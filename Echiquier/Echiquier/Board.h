#pragma once
#include "Player.h"

class Board
{
public:
	Board(std::shared_ptr<WindowManager> window);
	~Board();

	void Event(InputManager* inputManager);
	void Update(InputManager* inputManager);
	void DrawPieces();

private:
	SDL_Texture* tex;
	std::shared_ptr<WindowManager> window;

public:
	Player* player;
	Player* cpu;
};

