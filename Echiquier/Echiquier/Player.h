#pragma once
#include "PiecesManager.h"
#include "InputManager.h"

class Player
{

public:
	Player(std::shared_ptr<WindowManager> window, int player);
	~Player();

	void Init();
	void SelectPiece(InputManager* inputManager);
	void Move(InputManager* inputManager);
	void Update();

	inline std::shared_ptr<Pieces> GetKing() { return pieces->king; }
	inline bool GetTurn() { return pieces->turn; }
 

public:
	PiecesManager* pieces;
	bool actionSelected;
};
