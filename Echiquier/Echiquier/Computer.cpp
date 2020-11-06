#include "Computer.h"


Computer::Computer(std::shared_ptr<WindowManager> window, int player) {
	pieces = new PiecesManager(window, player);
	
}

Computer::~Computer() {
	delete(pieces);
}

void Computer::Init() {
	predictionNode.king = pieces->king;
	predictionNode.enemyKing = pieces->enemyKing;
	for (auto& piece : pieces->piecesList) {
		piece->isAttacked = piece->isDefended = false;
		piece->attackingValue = piece->defendingValue = 0;
		//piece->Move(pieces->placeTaken, pieces->enemy->placeTaken, pieces->enemy->placeAttacked, pieces->pieces, pieces->enemy->pieces);
	}
}

void Computer::Prediction(int depth) {
	predictionNode.pieces.clear();
	predictionNode.enemyPieces.clear();
	predictionNode.pieces = *&pieces->pieces;
	predictionNode.enemyPieces = *&pieces->enemy->pieces;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			predictionNode.placeTaken[i][j] = pieces->placeTaken[i][j];
			predictionNode.enemyPlaceTaken[i][j] = pieces->enemy->placeTaken[i][j];
		}
	}
	predictionTree->Init(predictionNode, depth);
}

void Computer::Move(int depth) {
	predictionTree->MinMax(predictionNode, depth, /*-HIGHNUMBER, HIGHNUMBER,*/ true);
	for (Node& node : predictionNode.children) {
		if (node.value == predictionNode.value) {
			pieceToMove = node.pieceToMove, action = node.action;
		}
	}
	pieces->Move(pieceToMove, action);
	pieceToMove->Move(pieces->placeTaken, pieces->enemy->placeTaken, pieces->enemy->placeAttacked, pieces->pieces, pieces->enemy->pieces);
}

void Computer::Update() {
	for (auto& piece : pieces->piecesList) {
		int iterator = 0;
		for (auto& action : piece->possibleActions) {
			if (piece->possibleActions[iterator] != nullptr && pieces->WillKingBeEndangered(piece, action)) {
				piece->possibleActions[iterator] = nullptr;
			}
			iterator++;
		}
	}
}