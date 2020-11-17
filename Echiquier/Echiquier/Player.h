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
	void Move(InputManager* inputManager, std::vector<std::shared_ptr<Pieces>>& piecesMoved, std::vector<std::shared_ptr<PossiblePlacements>>& actionsDone);
	void Update();

	inline std::shared_ptr<Pieces> GetKing() { return pieces->king; }
	inline bool GetTurn() { return pieces->turn; }
 

public:
	PiecesManager* pieces;
	std::shared_ptr<Pieces> pieceSelected;
	std::shared_ptr<PossiblePlacements> actionSelected;
	bool actionBoard[8][8];
};
