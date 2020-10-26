#pragma once
#include "PiecesManager.h"

class Player
{

public:
	Player(std::shared_ptr<WindowManager> window);
	~Player();

	void Move();

public:
	PiecesManager* pieces;
	char pieceList[8][8];
};

