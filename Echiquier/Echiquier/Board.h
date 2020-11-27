#pragma once
#include "Player.h"
#include "Computer.h"
#define DEPTH 1
#define DEPTHTWO 1

class Board
{
public:
	Board(std::shared_ptr<WindowManager> window);
	~Board();

	void Event(InputManager* inputManager);
	void Update(InputManager* inputManager);
	void DrawPieces();
	
	inline bool CheckMate() { return (cpu->pieces->CheckMate() || player->pieces->CheckMate()); }
	inline bool Restart() { return restart; }

private:
	bool restart;
	SDL_Texture* tex;
	std::shared_ptr<WindowManager> window;

public:
	Player* player;
	//Computer* player;
	//Player* cpu;
	Computer* cpu;
	SDL_Rect destCheckMate;
	SDL_Rect destText1;
	SDL_Rect destText2;
	SDL_Rect destRestartText;
	SDL_Rect destExitText;
	SDL_Texture* finishTex;
	SDL_Texture* checkMateText;
	SDL_Texture* playerWinText;
	SDL_Texture* computerWinText;
	SDL_Texture* restartText;
	SDL_Texture* exitText;
	std::vector<std::shared_ptr<Pieces>> piecesMoved;
	std::vector<std::shared_ptr<PossiblePlacements>> actionsDone;
};

