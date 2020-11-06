#include "MinMax.h"

NodeTree::NodeTree() {
}
NodeTree::~NodeTree() {
}

void NodeTree::Init(Node& currentNode, int depth) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (currentNode.enemyPieces[i][j] != nullptr) {
				currentNode.enemyPieces[i][j]->Move(currentNode.enemyPlaceTaken, currentNode.placeTaken, currentNode.placeAttacked, currentNode.enemyPieces, currentNode.pieces);
				for (auto& action : currentNode.enemyPieces[i][j]->possibleActions)
					currentNode.placeAttackedByEnemy[action->coordonates[0]][action->coordonates[1]] = true;
			}
			else if (currentNode.pieces[i][j] != nullptr) {
				currentNode.pieces[i][j]->Move(currentNode.placeTaken, currentNode.enemyPlaceTaken, currentNode.placeAttackedByEnemy, currentNode.pieces, currentNode.enemyPieces);
				for (auto& action : currentNode.pieces[i][j]->possibleActions) {
					if (action != nullptr)
						currentNode.placeAttacked[action->coordonates[0]][action->coordonates[1]] = true;
				}
			}
		}
	}
	if (depth > 0)
		currentNode.hasChildren = true;
	if (currentNode.hasChildren) {
		/*for (int i = 0; i < 3; i++) {
			Node n;
			currentNode.children.push_back(n);
		}
		currentNode.value = 0;
		for (Node& child : currentNode.children) {
			Init(child, depth - 1);
		}*/
		if (depth % 2 == 0) {
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					if (currentNode.pieces[i][j] != nullptr) {
						currentNode.pieces[i][j]->Move(currentNode.placeTaken, currentNode.enemyPlaceTaken, currentNode.placeAttackedByEnemy, currentNode.pieces, currentNode.enemyPieces);
					}
				}
			}
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					if (currentNode.pieces[i][j] != nullptr) {
						for (auto& action : currentNode.pieces[i][j]->possibleActions) {
							if (action != nullptr) {
								Node n;
								n.pieces = currentNode.pieces;
								n.enemyPieces = currentNode.enemyPieces;
								n.pieces[action->coordonates[0]][action->coordonates[1]] = n.pieces[i][j], n.pieces[i][j] = nullptr;
								for (int i = 0; i < 8; i++)
									for (int j = 0; j < 8; j++) {
										n.placeTaken[i][j] = currentNode.placeTaken[i][j];
										n.enemyPlaceTaken[i][j] = currentNode.enemyPlaceTaken[i][j];
										n.placeAttacked[i][j] = n.placeAttackedByEnemy[i][j] = false;
									}
								n.placeTaken[action->coordonates[0]][action->coordonates[1]] = true, n.placeTaken[i][j] = false;
								if (n.enemyPlaceTaken[action->coordonates[0]][action->coordonates[1]]) {
									n.enemyPlaceTaken[action->coordonates[0]][action->coordonates[1]] = false;
									n.enemyPieces[action->coordonates[0]][action->coordonates[1]] = nullptr;
								}
								n.king = currentNode.king;
								n.enemyKing = currentNode.enemyKing;
								n.pieceToMove = currentNode.pieces[i][j];
								n.action = action;

								currentNode.children.push_back(n);
							}
						}
					}
				}
			}
		}
		else {
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					if (currentNode.enemyPieces[i][j] != nullptr) {
						for (auto& action : currentNode.enemyPieces[i][j]->possibleActions) {
							if (action != nullptr) {
								Node n;
								n.pieces = currentNode.pieces;
								n.enemyPieces = currentNode.enemyPieces;
								n.enemyPieces[action->coordonates[0]][action->coordonates[1]] = n.enemyPieces[i][j], n.enemyPieces[i][j] = nullptr;
								for (int i = 0; i < 8; i++)
									for (int j = 0; j < 8; j++) {
										n.enemyPlaceTaken[i][j] = currentNode.enemyPlaceTaken[i][j];
										n.placeTaken[i][j] = currentNode.placeTaken[i][j];
										n.placeAttacked[i][j] = n.placeAttackedByEnemy[i][j] = false;
									}
								n.enemyPlaceTaken[action->coordonates[0]][action->coordonates[1]] = true, n.enemyPlaceTaken[i][j] = false;
								if (n.placeTaken[action->coordonates[0]][action->coordonates[1]]) {
									n.placeTaken[action->coordonates[0]][action->coordonates[1]] = false;
									n.pieces[action->coordonates[0]][action->coordonates[1]] = nullptr;
								}
								n.king = currentNode.king;
								n.enemyKing = currentNode.enemyKing;
								n.pieceToMove = currentNode.enemyPieces[i][j];
								n.action = action;

								currentNode.children.push_back(n);
							}
						}
					}
				}
			}
		}
		currentNode.value = 0;
		for (Node& child : currentNode.children) {
			Init(child, depth - 1);
		}
	}
	else {
		//currentNode.value = rand() % 100 + 1; //Valeur pour l'exemple, ce ne sera pas cette valeur évidemment

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (currentNode.pieces[i][j] != nullptr) {
					if (currentNode.pieces[i][j]->isAttacked)
						currentNode.value-= currentNode.pieces[i][j]->attackingValue;
					if (currentNode.pieces[i][j]->isDefended)
						currentNode.value+= currentNode.pieces[i][j]->defendingValue;

					currentNode.value += currentNode.pieces[i][j]->value;
				}
				else if (currentNode.enemyPieces[i][j] != nullptr) {
					if (currentNode.enemyPieces[i][j]->isAttacked)
						currentNode.value+=currentNode.enemyPieces[i][j]->attackingValue;
					if (currentNode.enemyPieces[i][j]->isDefended)
						currentNode.value-=currentNode.enemyPieces[i][j]->defendingValue;

					currentNode.value -= currentNode.enemyPieces[i][j]->value;
				}

				/*if (currentNode.placeAttacked[i][j])
					currentNode.value+=10;
				if (currentNode.placeAttackedByEnemy[i][j])
					currentNode.value-=10;*/
			}
		}
		if (currentNode.placeAttacked[currentNode.enemyKing->coordonates[0]][currentNode.enemyKing->coordonates[1]]) {
			currentNode.value += 1000;
			if (currentNode.enemyKing->possibleActions.size() == 0)
				currentNode.value += 10'000'000;
		}
		else if (currentNode.placeAttackedByEnemy[currentNode.king->coordonates[0]][currentNode.enemyKing->coordonates[1]]) {
			currentNode.value -= 1000;
			if (currentNode.king->possibleActions.size() == 0)
				currentNode.value -= 10'000'000;
		}
	}
}

void NodeTree::Print(Node currentNode) {
	if (currentNode.hasChildren) {
		std::cout << "Value of the current Node : " << currentNode.value << "\nChilds :\n";
		for (Node& child : currentNode.children) {
			Print(child);
		}
	}
	else {
		std::cout << "Value of the Node : " << currentNode.value << "\n";
	}
}

void NodeTree::ClearTree(Node currentNode) {
	if (currentNode.hasChildren) {
		for (Node& child : currentNode.children) {
			ClearTree(child);
		}
		currentNode.pieces.clear();
		currentNode.enemyPieces.clear();
		currentNode.children.clear();
	}
}

int NodeTree::MinMax(Node& currentNode, int depth, /*int alpha, int beta, */bool maximizingPlayer) {
	if (depth == 0)
		return currentNode.value;
	if (maximizingPlayer) {
		currentNode.value = -HIGHNUMBER;
		for (Node& node : currentNode.children) {
			int eval = MinMax(node, depth - 1,/* alpha, beta, */false);
			currentNode.value = std::max(currentNode.value, eval);
			/*alpha = std::max(alpha, eval);
			if (beta <= alpha)
				break;*/
		}
		return currentNode.value;
	}
	else {
		currentNode.value = HIGHNUMBER;
		for (Node& node : currentNode.children) {
			int eval = MinMax(node, depth - 1,/* alpha, beta, */true);
			currentNode.value = std::min(currentNode.value, eval);
			/*beta = std::min(beta, eval);
			if (beta <= alpha)
				break;*/
		}
		return currentNode.value;
	}
}