#pragma once
#include "Player.h"
#include "Computer.h"
#define DEPTH 2

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
	//Computer* player;
	Computer* cpu;
	std::vector<std::shared_ptr<Pieces>> piecesMoved;
	std::vector<std::shared_ptr<PossiblePlacements>> actionsDone;
};

