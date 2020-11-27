#include "Computer.h"


Computer::Computer(std::shared_ptr<WindowManager> window, int player) {
	pieces = new PiecesManager(window, player);
	predictionTree = new NodeTree();
	
}

Computer::~Computer() {
	delete(pieces);
	delete(predictionTree);
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
	predictionNode.pawns = *&pieces->pawns;
	predictionNode.enemyPawns = *&pieces->enemy->pawns;
	predictionNode.rooks = *&pieces->rooks;
	predictionNode.enemyRooks = *&pieces->enemy->rooks;
	predictionNode.window = *&pieces->window;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			predictionNode.placeTaken[i][j] = pieces->placeTaken[i][j];
			predictionNode.enemyPlaceTaken[i][j] = pieces->enemy->placeTaken[i][j];
		}
	}
	predictionTree->Init(predictionNode, depth, true);
}

void Computer::Move(int depth) {
	float value = predictionTree->MinMax(predictionNode, depth, /*-HIGHNUMBER, HIGHNUMBER,*/ true);
	std::cout << "Maximum : " << value << "\n";
	for (Node& node : predictionNode.children) {
		if (node.value == value) {
			pieceToMove = node.pieceToMove, action = node.action;
			std::cout << "ID : " << pieceToMove->ID << " Base coordonates : "<< pieceToMove->coordonates[0] << " " <<pieceToMove->coordonates[1] << "\n";
			std::cout << "New coordonates : " << action->coordonates[0] << " " << action->coordonates[1] << "\n";
			break;
		}
	}
	pieces->Move(pieceToMove, action);
	pieceToMove->Move(pieces->placeTaken, pieces->enemy->placeTaken, pieces->enemy->placeAttacked, pieces->pieces, pieces->enemy->pieces);
	if (pieces->enemy->CheckMate()) {
		pieces->turn = false;
		pieces->enemy->turn = false;
	}
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