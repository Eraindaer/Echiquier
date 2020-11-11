#pragma once
#include "MinMax.h"

class Computer
{
public:
	Computer(std::shared_ptr<WindowManager> window, int player);
	~Computer();

	void Init();
	void Prediction(int depth);
	void Move(int depth);
	void Update();

	inline std::shared_ptr<Pieces> GetKing() { return pieces->king; }
	inline bool GetTurn() { return pieces->turn; }

public:
	PiecesManager* pieces;
	NodeTree* predictionTree;
	std::shared_ptr<Pieces> pieceToMove;
	std::shared_ptr<PossiblePlacements> action;
	Node predictionNode;
};
