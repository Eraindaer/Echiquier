#pragma once
#include <vector>
#include <iostream>
#include "PiecesManager.h"
#define HIGHNUMBER 1000000000

class Node {
public:
	Node();
	~Node();

	bool CheckMate(bool side);
	bool WillThisPieceBeEndangered(std::shared_ptr<Pieces> pieceToMove);

public:

	float												 value;
	int                                                  previousPosition[2];
	int                                                  enemyPreviousPosition[2];
	int                                                  placeValue[8][8];                      
	bool												 finishingNode;
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

	void Init(Node& currentNode, int depth, bool isComputer);
	void Print(Node currentNode);
	void ClearTree(Node& currentNode);

	float  MinMax(Node& currentNode, int depth,/* int alpha, int beta,*/ bool maximizingPlayer);
	bool WillKingBeEndangered(Node currentNode, std::shared_ptr<Pieces> currentPiece, std::shared_ptr<PossiblePlacements> eventualAction, bool side);
	int  GetKingMoves(std::shared_ptr<Pieces> king);

private:	
	int													 iterations;
	bool predictionPlaces[8][8];
	bool predictionEnemyPlaces[8][8];
	bool placeAttackedByEnemy[8][8];
	std::shared_ptr<Pieces> predictionKing;
	std::vector<std::vector<std::shared_ptr<Pieces>>> predictionPieces;
	std::vector<std::vector<std::shared_ptr<Pieces>>> predictionEnemyPieces;

};

