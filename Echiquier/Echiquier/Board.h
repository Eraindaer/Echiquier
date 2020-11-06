#pragma once
#include "Player.h"
#include "Computer.h"

class Board
{
public:
	Board(std::shared_ptr<WindowManager> window);
	~Board();

	void Event(InputManager* inputManager);
	void Update(InputManager* inputManager);
	void DrawPieces();
	
	inline bool CheckMate() { return (cpu->pieces->CheckMate() || player->pieces->CheckMate()); }

private:
	SDL_Texture* tex;
	std::shared_ptr<WindowManager> window;

public:
	Player* player;
	//Player* cpu;
	Computer* cpu;
};

