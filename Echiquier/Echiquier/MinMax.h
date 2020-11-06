#pragma once
#include <vector>
#include <iostream>
#include "PiecesManager.h"
#define HIGHNUMBER 1000000000

struct Node {
	int												     value = 0;
	bool												 hasChildren = false;
	bool                                                 placeTaken[8][8];
	bool                                                 enemyPlaceTaken[8][8];
	bool                                                 placeAttacked[8][8];
	bool                                                 placeAttackedByEnemy[8][8];
	std::vector<Node>									 children;
	std::shared_ptr<Pieces>                              king;
	std::shared_ptr<Pieces>								 enemyKing;
	std::shared_ptr<Pieces>                              pieceToMove;
	std::shared_ptr<PossiblePlacements>                  action;
	std::vector<std::vector<std::shared_ptr<Pieces>>>    pieces;
	std::vector<std::vector<std::shared_ptr<Pieces>>>    enemyPieces;
};

class NodeTree
{
public:
	NodeTree();
	~NodeTree();

	void Init(Node& currentNode, int depth);
	void Print(Node currentNode);
	void ClearTree(Node currentNode);

	int  MinMax(Node& currentNode, int depth,/* int alpha, int beta,*/ bool maximizingPlayer);
};

