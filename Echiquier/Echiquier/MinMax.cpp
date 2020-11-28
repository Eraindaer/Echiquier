#include "MinMax.h"

Node::Node() {
	value = 0;
	finishingNode = false;
	isCheckMate = enemyIsCheckMate = false;
	previousPosition[0] = previousPosition[1] = enemyPreviousPosition[0] = enemyPreviousPosition[1] = -1;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			placeTaken[i][j] = enemyPlaceTaken[i][j] = placeAttacked[i][j] = placeAttackedByEnemy[i][j] = false;
			placeValue[i][j] = 0;
		}
	}
}
Node::~Node() {

}

bool Node::CheckMate(bool isComputer) {
	if (isComputer) {
		std::cout << "Test Ordinateur : \n";
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
				if (pieces[i][j] != nullptr)
					for (auto& action : pieces[i][j]->possibleActions)
						if (action != nullptr)
							return false;
	}
	else {
		std::cout << "Test Joueur : \n";
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
				if (enemyPieces[i][j] != nullptr)
					for (auto& action : enemyPieces[i][j]->possibleActions)
						if (action != nullptr)
							return false;

	}
	return true;
}

bool Node::WillThisPieceBeEndangered(std::shared_ptr<Pieces> pieceToMove) {
	if (!pieceToMove->isDefended)
		return true;
	return false;
}


NodeTree::NodeTree() {
	iterations = 0;  
	int test = 0;
}
NodeTree::~NodeTree() {
}

void NodeTree::Init(Node& currentNode, int depth, bool isComputer) {
	iterations++;
	/*for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (currentNode.enemyPieces[i][j] != nullptr) {
				currentNode.enemyPieces[i][j]->attackingValue = currentNode.enemyPieces[i][j]->defendingValue = 0;
				currentNode.enemyPieces[i][j]->isAttacked = currentNode.enemyPieces[i][j]->isDefended = false;
			}
			else if (currentNode.pieces[i][j] != nullptr) {
				currentNode.pieces[i][j]->attackingValue = currentNode.pieces[i][j]->defendingValue = 0;
				currentNode.pieces[i][j]->isAttacked = currentNode.pieces[i][j]->isDefended = false;
			}
		}
	}*/

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (currentNode.enemyPieces[i][j] != nullptr) {
				currentNode.enemyPieces[i][j]->Move(currentNode.enemyPlaceTaken, currentNode.placeTaken, currentNode.placeAttacked, currentNode.enemyPieces, currentNode.pieces);
				for (auto& action : currentNode.enemyPieces[i][j]->possibleActions)
					if (action != nullptr && action->coordonates[0] >= 0 && action->coordonates[0] < 8 && action->coordonates[1] >= 0 && action->coordonates[1] < 8) {
						/*if (WillKingBeEndangered(currentNode, currentNode.enemyPieces[i][j], action, 0))
							action = nullptr;
						else*/
							currentNode.placeAttackedByEnemy[action->coordonates[0]][action->coordonates[1]] = true;
					}
			}
			else if (currentNode.pieces[i][j] != nullptr) {
				currentNode.pieces[i][j]->Move(currentNode.placeTaken, currentNode.enemyPlaceTaken, currentNode.placeAttackedByEnemy, currentNode.pieces, currentNode.enemyPieces);
				for (auto& action : currentNode.pieces[i][j]->possibleActions) {
					if (action != nullptr && action->coordonates[0] >= 0 && action->coordonates[0] < 8 && action->coordonates[1] >= 0 && action->coordonates[1] < 8) {
						/*if (WillKingBeEndangered(currentNode, currentNode.pieces[i][j], action, 1))
							action = nullptr;
						else*/
							currentNode.placeAttacked[action->coordonates[0]][action->coordonates[1]] = true;
					}
				}
			}
		}
	}
	
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (currentNode.enemyPieces[i][j] != nullptr) {
				int iterator = 0;
				for (auto& action : currentNode.enemyPieces[i][j]->possibleActions) {
					if (action != nullptr)
						if (WillKingBeEndangered(currentNode, currentNode.enemyPieces[i][j], action, 0)) {
							action.get()->SetState(true);
							std::cout << "Action supprimée joueur " << action->coordonates[0] << " , " << action->coordonates[1] << "\n";
							int test = 0;
						}
					iterator++;
				}
			}
			else if (currentNode.pieces[i][j] != nullptr) {
				int iterator = 0;
				for (auto& action : currentNode.pieces[i][j]->possibleActions) {
					if (action != nullptr)
						if (WillKingBeEndangered(currentNode, currentNode.pieces[i][j], action, 1)) {
							std::cout << "Action supprimée ordi " << action->coordonates[0] << " , " << action->coordonates[1] << "\n";
							action.get()->SetState(true);
							int test = 0;
						}
					iterator++;
				}
			}
		}
	}

	for(int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++) {
			if (currentNode.enemyPieces[i][j] != nullptr) {
				int iterator = 0;
				for (auto& action : currentNode.enemyPieces[i][j]->possibleActions) {
					if (action.get()->isDeleted)
						std::cout << "Nullptrrrr  \n";
					iterator++;
				}
			}
			else if (currentNode.pieces[i][j] != nullptr) {
				int iterator = 0;
				for (auto& action : currentNode.pieces[i][j]->possibleActions) {
					if (action.get()->isDeleted)
						std::cout << "Nullptrrrrrr \n";
					iterator++;
				}
			}
		}

	if (isCheckmated(currentNode, 0)) {
		currentNode.finishingNode = true;
		currentNode.enemyIsCheckMate = true;
	}
	if (isCheckmated(currentNode, 1)) {
		currentNode.finishingNode = true;
		currentNode.isCheckMate = true;
	}


	//if (currentNode.pieceToMove != nullptr && !currentNode.WillThisPieceBeEndangered(currentNode.pieceToMove))
		//return;

	/*if (currentNode.CheckMate(isComputer)) {
		currentNode.finishingNode = true;
		std::cout << "Echec et mat \n";
	}
	else {
		std::cout << "Pas echec et mat \n";
	}**/

	if (!currentNode.finishingNode) {
		/*for (int i = 0; i < 3; i++) {
			Node n;
			currentNode.children.push_back(n);
		}
		currentNode.value = 0;
		for (Node& child : currentNode.children) {
			Init(child, depth - 1);
		}*/
		if (isComputer) {
			/*for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					if (currentNode.pieces[i][j] != nullptr) {
						currentNode.pieces[i][j]->Move(currentNode.placeTaken, currentNode.enemyPlaceTaken, currentNode.placeAttackedByEnemy, currentNode.pieces, currentNode.enemyPieces);
					}
				}
			}*/
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					if (currentNode.pieces[i][j] != nullptr) {
						for (auto& action : currentNode.pieces[i][j]->possibleActions) {
							if (!action.get()->isDeleted) {
								Node n;
								n.pieces = currentNode.pieces;
								n.enemyPieces = currentNode.enemyPieces;
								n.previousPosition[0] = currentNode.pieces[i][j]->coordonates[0], n.previousPosition[1] = currentNode.pieces[i][j]->coordonates[1];
								n.enemyPreviousPosition[0] = currentNode.enemyPreviousPosition[0], n.enemyPreviousPosition[1] = currentNode.enemyPreviousPosition[1];
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
								n.window = currentNode.window;
								n.pawns = currentNode.pawns;
								n.enemyPawns = currentNode.enemyPawns;
								n.rooks = currentNode.rooks;
								n.enemyRooks = currentNode.enemyRooks;
								n.king = currentNode.king;
								n.enemyKing = currentNode.enemyKing;
								n.pieceToMove = currentNode.pieces[i][j];
								n.action = action;
								int iterator = 0;
								for (auto& pawn : n.pawns) {
									if (pawn->coordonates[1] + 1 > 7 || pawn->coordonates[1] - 1 < 0) {
										pawn.reset(new Queen(n.window, pawn->coordonates[0], 7 - pawn->coordonates[1]));
										pawn->SetCoordonates(pawn->coordonates[0], pawn->coordonates[1]);
										pawn->SetKing(n.king);
										n.pieces[pawn->coordonates[0]][pawn->coordonates[1]] = pawn;
										n.pawns.erase(n.pawns.begin() + iterator);
										break;
									}
									iterator++;
								}

								if (depth - 1 == 0) 
									n.finishingNode = true;
								/*if (WillEnemyBeCheckmated(n, currentNode.pieces[i][j], action, true))
									n.finishingNode = true, n.enemyIsCheckMate = true;*/

								currentNode.children.push_back(n);
								}
						}
					}
				}
			}
			currentNode.value = 0;
			for (Node& child : currentNode.children) {
				Init(child, depth - 1, false);
				/*if (child.WillThisPieceBeEndangered(child.pieceToMove)) {
					child.value = -1000000;
					child.finishingNode = true;
				}*/
			}
		}
		else {
			/*for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					if (currentNode.enemyPieces[i][j] != nullptr) {
						currentNode.enemyPieces[i][j]->Move(currentNode.enemyPlaceTaken, currentNode.placeTaken, currentNode.placeAttacked, currentNode.enemyPieces, currentNode.pieces);
					}
				}
			}*/
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					if (currentNode.enemyPieces[i][j] != nullptr) {
						for (auto& action : currentNode.enemyPieces[i][j]->possibleActions) {
							if (!action.get()->isDeleted) {
									Node n;
									n.pieces = currentNode.pieces;
									n.enemyPieces = currentNode.enemyPieces;
									n.enemyPreviousPosition[0] = currentNode.enemyPieces[i][j]->coordonates[0], n.enemyPreviousPosition[1] = currentNode.enemyPieces[i][j]->coordonates[1];
									n.previousPosition[0] = currentNode.previousPosition[0], n.previousPosition[1] = currentNode.previousPosition[1];
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
									n.window = currentNode.window;
									n.pawns = currentNode.pawns;
									n.enemyPawns = currentNode.enemyPawns;
									n.rooks = currentNode.rooks;
									n.enemyRooks = currentNode.enemyRooks;
									n.king = currentNode.king;
									n.enemyKing = currentNode.enemyKing;
									n.pieceToMove = currentNode.enemyPieces[i][j];
									n.action = action;
									int iterator = 0;
									for (auto& pawn : n.enemyPawns) {
										if (pawn->coordonates[1] + 1 > 7 || pawn->coordonates[1] - 1 < 0) {
											pawn.reset(new Queen(n.window, pawn->coordonates[0], 7 - pawn->coordonates[1]));
											pawn->SetCoordonates(pawn->coordonates[0], pawn->coordonates[1]);
											pawn->SetKing(n.enemyKing);
											n.enemyPieces[pawn->coordonates[0]][pawn->coordonates[1]] = pawn;
											n.enemyPawns.erase(n.enemyPawns.begin() + iterator);
											break;
										}
										iterator++;
									}

									if (depth - 1 == 0)
										n.finishingNode = true;
									/*if (WillEnemyBeCheckmated(n, currentNode.enemyPieces[i][j], action, false))
										n.finishingNode = true, n.isCheckMate = true;*/

									currentNode.children.push_back(n);
							}
						}
					}
				}
			}

			currentNode.value = 0;
			for (Node& child : currentNode.children) {
				Init(child, depth - 1, false);
				/*if (child.WillThisPieceBeEndangered(child.pieceToMove)) {
					child.value = 1000000;
					child.finishingNode = true;
				}*/
			}
		}
	}
	else {

		int numberOfPieces[2] = { 0, 0 };
		int numberOfMoves[2] = { 0, 0 };
		int numberOfKingMoves[2] = { 0, 0 };
		int pieces[2][6] = { {0,0,0,0,0,0},{0,0,0,0,0,0} };
		//int pawnState[2][3] = { {0,0,0} , {0,0,0} }; //0 : computer, 1 : player | 0 : doubled, 1 : blocked, 2 : isolated
		//int column[2][8] = { { 0, 0, 0, 0, 0, 0, 0, 0 },{0, 0, 0, 0, 0, 0, 0, 0 } };
		/*for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (currentNode.pieces[i][j] != nullptr) {
					if (currentNode.pieces[i][j]->isAttacked)
						currentNode.value-= currentNode.pieces[i][j]->attackingValue;
					if (currentNode.pieces[i][j]->isDefended)
						currentNode.value+= currentNode.pieces[i][j]->defendingValue;

					currentNode.value += currentNode.pieces[i][j]->value * (std::abs(currentNode.pieces[i][j]->coordonates[1] - currentNode.king->coordonates[1])) ;
					for (auto& action : currentNode.pieces[i][j]->possibleActions) {
						currentNode.placeValue[action->coordonates[0]][action->coordonates[1]] += currentNode.pieces[i][j]->value / 4;
					}
				}
				else if (currentNode.enemyPieces[i][j] != nullptr) {
					if (currentNode.enemyPieces[i][j]->isAttacked)
						currentNode.value+=currentNode.enemyPieces[i][j]->attackingValue;
					if (currentNode.enemyPieces[i][j]->isDefended)
						currentNode.value-=currentNode.enemyPieces[i][j]->defendingValue;

					currentNode.value -= currentNode.enemyPieces[i][j]->value * (std::abs(currentNode.enemyPieces[i][j]->coordonates[1] - currentNode.enemyKing->coordonates[1]));
					for (auto& action : currentNode.enemyPieces[i][j]->possibleActions) {
						currentNode.placeValue[action->coordonates[0]][action->coordonates[1]] -= currentNode.enemyPieces[i][j]->value / 4;
					}
				}

				if (currentNode.placeAttacked[i][j])
					currentNode.value+=15;
				if (currentNode.placeAttackedByEnemy[i][j])
					currentNode.value-=15;
			}
		}

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				currentNode.value += currentNode.placeValue[i][j];
			}
		}*/
		/*if (GetKingMoves(currentNode.king) == 0 && currentNode.king->isAttacked) {
			for (int i = 0; i < 8; i++)
				for (int j = 0; j < 8; j++)
					if (currentNode.pieces[i][j] != nullptr)
						currentNode.pieces[i][j]->checkMate = true;
		}
		else if (GetKingMoves(currentNode.enemyKing) == 0 && currentNode.enemyKing->isAttacked) {
			for (int i = 0; i < 8; i++)
				for (int j = 0; j < 8; j++)
					if (currentNode.enemyPieces[i][j] != nullptr)
						currentNode.enemyPieces[i][j]->checkMate = true;
		}*/

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (currentNode.pieces[i][j] != nullptr) {
					pieces[0][currentNode.pieces[i][j]->ID]++;
					numberOfPieces[0]+= currentNode.pieces[i][j]->value;
					//currentNode.value += currentNode.pieces[i][j]->value;
					//currentNode.value += currentNode.pieces[i][j]->defendingValue;
					//currentNode.value -= currentNode.pieces[i][j]->attackingValue;
					/*if (currentNode.king->isAttacked)
						pieces[0][5]--;
					else {
						
					}*/
					for (auto& action : currentNode.pieces[i][j]->possibleActions) {
							if (!action.get()->isDeleted) {
								numberOfMoves[0]++;
							}
						}
				}
				else if (currentNode.enemyPieces[i][j] != nullptr) {
					pieces[1][currentNode.enemyPieces[i][j]->ID]++;
					numberOfPieces[1]+= currentNode.enemyPieces[i][j]->value;
					//currentNode.value -= currentNode.enemyPieces[i][j]->value;
					//currentNode.value -= currentNode.enemyPieces[i][j]->defendingValue;
					//currentNode.value += currentNode.enemyPieces[i][j]->attackingValue;
					/*if (currentNode.enemyKing->isAttacked)
						pieces[1][5]--;
					else {
						
					}*/
					for (auto& action : currentNode.enemyPieces[i][j]->possibleActions) {
							if (!action.get()->isDeleted) {
								numberOfMoves[1]++;
								
							}
						}
				}
			}
		}
		for (auto& action : currentNode.king->possibleActions) {
			if (!action.get()->isDeleted)
				numberOfKingMoves[0]++;
		}
		for (auto& action : currentNode.enemyKing->possibleActions) {
			if (!action.get()->isDeleted)
				numberOfKingMoves[1]++;
		}

		if (numberOfKingMoves[0] == 0)
			pieces[0][5] = 0;
		if (numberOfKingMoves[1] == 0)
			pieces[1][5] = 0;

		/*for (auto& pawn : currentNode.pawns) {
			int actions = 0;
			int occupatedPlacesAround = 0;
			column[0][pawn->coordonates[0]]++;
			for (auto& action : pawn->possibleActions) {
				if (action != nullptr)
					actions++;
			}
			if (actions == 0)
				pawnState[0][1]++;
			for (int i = -1; i <= 1; i++) {
				for (int j = -1; j <= 1; j++) {
					if (std::abs(i + j) != 0) {
						Vector2D dir(i, j);
						if (pawn->coordonates[0] + dir.x < 8 && pawn->coordonates[0] >= 0 && pawn->coordonates[1] + dir.y < 8 && pawn->coordonates[1] + dir.y >= 0 &&
							currentNode.placeTaken[pawn->coordonates[0] + dir.x][pawn->coordonates[1] + dir.y]) {
							occupatedPlacesAround++;
						}
					}
				}
			}

			if (occupatedPlacesAround == 0)
				pawnState[0][2]++;

		}
		for (auto& pawn : currentNode.enemyPawns) {
			int actions = 0;
			int occupatedPlacesAround = 0;
			column[1][pawn->coordonates[0]]++;
			for (auto& action : pawn->possibleActions) {
				if (action != nullptr)
					actions++;
			}
			if (actions == 0)
				pawnState[1][1]++;
			for (int i = -1; i <= 1; i++) {
				for (int j = -1; j <= 1; j++) {
					if (std::abs(i + j) != 0) {
						Vector2D dir(i, j);
						if (pawn->coordonates[0] + dir.x < 8 && pawn->coordonates[0] >= 0 && pawn->coordonates[1] + dir.y < 8 && pawn->coordonates[1] + dir.y >= 0 &&
							currentNode.enemyPlaceTaken[pawn->coordonates[0] + dir.x][pawn->coordonates[1] + dir.y]) {
							occupatedPlacesAround++;
						}
					}
				}
			}

			if (occupatedPlacesAround == 0)
				pawnState[1][2]++;
		}

		for (int& i : column[0]) {
			if (i > 1)
				pawnState[0][0]++;
		}
		for (int& i : column[1]) {
			if (i > 1)
				pawnState[1][0]++;
		}*/

		currentNode.value += /*KINGVALUE * (pieces[0][5] - pieces[1][5])
						   + QUEENVALUE * (pieces[0][4] - pieces[1][4])
					       + ROOKVALUE * (pieces[0][3] - pieces[1][3])
						   + BISHOPVALUE * (pieces[0][2] - pieces[1][2])
						   + KNIGHTVALUE * (pieces[0][1] - pieces[1][1])
						   + PAWNVALUE * (pieces[0][0] - pieces[0][0])
						   - 0.5 * (pawnState[0][0] - pawnState[1][0] + pawnState[0][1] - pawnState[1][1] + pawnState[0][2] - pawnState[1][2])
						   + 10 * (numberOfKingMoves[0] - numberOfKingMoves[1])
						   + 0.1 * (numberOfMoves[0] - numberOfMoves[1]);*/
						   (numberOfPieces[0] - numberOfPieces[1]) + 10 * (numberOfKingMoves[0] - numberOfKingMoves[1]) + 0.1* (numberOfMoves[0] - numberOfMoves[1]);

		//std::cout << "Coups ordi : " << numberOfMoves[0] << "\nCoups joueur :" << numberOfMoves[1] << "\n";


		/*if (currentNode.king->isAttacked)
			currentNode.value -= 200'000;
		else if (currentNode.enemyKing->isAttacked)
			currentNode.value += 200'000;*/

		if (currentNode.isCheckMate)
			currentNode.value = -HIGHNUMBER;
		else if (currentNode.enemyIsCheckMate)
			currentNode.value = HIGHNUMBER;
		/*for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (currentNode.pieces[i][j] != nullptr) {
					currentNode.value += currentNode.pieces[i][j]->value;
					if (currentNode.pieces[i][j]->isAttacked)
						currentNode.value -= currentNode.pieces[i][j]->attackingValue;
					if (currentNode.pieces[i][j]->isDefended)
						currentNode.value += currentNode.pieces[i][j]->defendingValue;

					for (auto& action : currentNode.pieces[i][j]->possibleActions) {
						if (action != nullptr) {
							currentNode.value++;
						}
					}
				}
				else if (currentNode.enemyPieces[i][j] != nullptr) {
					currentNode.value -= currentNode.enemyPieces[i][j]->value;
					if (currentNode.enemyPieces[i][j]->isAttacked)
						currentNode.value += currentNode.enemyPieces[i][j]->attackingValue;
					if (currentNode.enemyPieces[i][j]->isDefended)
						currentNode.value -= currentNode.enemyPieces[i][j]->defendingValue;

					for (auto& action : currentNode.enemyPieces[i][j]->possibleActions) {
						if (action != nullptr) {
							currentNode.value++;
						}
					}
				}
				/*if (currentNode.placeTaken[i][j]) {
					currentNode.value += std::abs(currentNode.king->coordonates[1] - j);
				}
				if (currentNode.enemyPlaceTaken[i][j]) {
					currentNode.value -= std::abs(currentNode.enemyKing->coordonates[1] - j);
				}

				/*if (currentNode.placeAttacked[i][j]) {
					currentNode.value++;
				}
				if (currentNode.placeAttackedByEnemy[i][j]) {
					currentNode.value--;
				}*/
		/*	}
		}

		for (auto& action : currentNode.king->possibleActions) {
			currentNode.value += 50;
		}
		for (auto& action : currentNode.enemyKing->possibleActions) {
			currentNode.value -= 50;
		}

		if (currentNode.enemyKing->isAttacked) {
			currentNode.value += 3 * KINGVALUE;
			for (auto& action : currentNode.enemyKing->possibleActions) {
				if (action != nullptr) {
					break;
				}
				else if (currentNode.enemyKing->possibleActions[currentNode.enemyKing->possibleActions.size() - 1] == nullptr) {
					currentNode.value += 10'000'000;
				}
			}
		}
		else if (currentNode.king->isAttacked) {
			currentNode.value -= 3 * KINGVALUE;
			for (auto& action : currentNode.king->possibleActions) {
				if (action != nullptr) {
					break;
				}
				else if (currentNode.king->possibleActions[currentNode.king->possibleActions.size() - 1] == nullptr) {
					currentNode.value -= 10'000'000;
				}
			}
		}*/
	}
}

void NodeTree::Print(Node currentNode) {
	/*if (currentNode.hasChildren) {
		std::cout << "Value of the current Node : " << currentNode.value << "\nChilds :\n";
		for (Node& child : currentNode.children) {
			Print(child);
		}
	}
	else {
		std::cout << "Value of the Node : " << currentNode.value << "\n";
	}*/
}

void NodeTree::ClearTree(Node& currentNode) {
	if (iterations != 0)
		std::cout << "Iterations : " << iterations << "\n";
	iterations = 0;
	if (!currentNode.finishingNode) {
		for (Node& child : currentNode.children) {
			ClearTree(child);
		}
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (currentNode.pieces[i][j] != nullptr) {
					currentNode.pieces[i][j]->possibleActions.clear();
				}
				else if (currentNode.enemyPieces[i][j] != nullptr) {
					currentNode.enemyPieces[i][j]->possibleActions.clear();
				}
			}
		}
		currentNode.pieces.clear();
		currentNode.enemyPieces.clear();
		currentNode.children.clear();
	}
}

float NodeTree::MinMax(Node& currentNode, int depth, /*int alpha, int beta, */bool maximizingPlayer) {
	if (currentNode.finishingNode)
		return currentNode.value;
	if (maximizingPlayer) {
		currentNode.value = -INFINITY;
		for (Node& node : currentNode.children) {
			float eval = MinMax(node, depth - 1,/* alpha, beta, */false);
			currentNode.value = std::max(currentNode.value, eval);
			/*std::cout << "Computer eval : ";
			std::cout << currentNode.value << "\n";
			/*std::cout << "ID : " << node.pieceToMove->ID << " Base coordonates : " << node.pieceToMove->coordonates[0] << " " << node.pieceToMove->coordonates[1] << "\n";
			std::cout << "New coordonates : " << node.action->coordonates[0] << " " << node.action->coordonates[1] << "\n";
			/*alpha = std::max(alpha, eval);
			if (beta <= alpha)
				break;*/
		}
		return currentNode.value;
	}
	else {
		currentNode.value = INFINITY;
		for (Node& node : currentNode.children) {
			float eval = MinMax(node, depth - 1,/* alpha, beta, */true);
			currentNode.value = std::min(currentNode.value, eval);
			/*std::cout << "Player eval :";
			std::cout << currentNode.value << "\n";
			/*std::cout << "ID : " << node.pieceToMove->ID << " Base coordonates : " << node.pieceToMove->coordonates[0] << " " << node.pieceToMove->coordonates[1] << "\n";
			std::cout << "New coordonates : " << node.action->coordonates[0] << " " << node.action->coordonates[1] << "\n";
			/*beta = std::min(beta, eval);
			if (beta <= alpha)
				break;*/
		}
		return currentNode.value;
	}
}

bool NodeTree::WillKingBeEndangered(Node currentNode, std::shared_ptr<Pieces> currentPiece, std::shared_ptr<PossiblePlacements> eventualAction, bool side) {
	bool predictionPlaces[8][8];
	bool predictionEnemyPlaces[8][8];
	bool placeAttackedByEnemy[8][8];
 	std::shared_ptr<Pieces> predictionKing;
	std::vector<std::vector<std::shared_ptr<Pieces>>> predictionPieces;
	std::vector<std::vector<std::shared_ptr<Pieces>>> predictionEnemyPieces;
	if (side & 1) {
		predictionPieces = currentNode.pieces;
		predictionEnemyPieces = currentNode.enemyPieces;
		predictionKing = currentNode.king;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				predictionPlaces[i][j] = currentNode.placeTaken[i][j];
				predictionEnemyPlaces[i][j] = currentNode.enemyPlaceTaken[i][j];
				placeAttackedByEnemy[i][j] = currentNode.placeAttackedByEnemy[i][j];
			}
		}
	}
	else {
		predictionPieces = currentNode.enemyPieces;
		predictionEnemyPieces = currentNode.pieces;
		predictionKing = currentNode.enemyKing;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				predictionPlaces[i][j] = currentNode.enemyPlaceTaken[i][j];
				predictionEnemyPlaces[i][j] = currentNode.placeTaken[i][j];
				placeAttackedByEnemy[i][j] = currentNode.placeAttacked[i][j];
			}
		}
	}

	predictionPlaces[currentPiece->coordonates[0]][currentPiece->coordonates[1]] = false, predictionPlaces[eventualAction->coordonates[0]][eventualAction->coordonates[1]] = true;
	predictionPieces[currentPiece->coordonates[0]][currentPiece->coordonates[1]] = nullptr, predictionPieces[eventualAction->coordonates[0]][eventualAction->coordonates[1]] = currentPiece;
	predictionKing->isAttacked = false;
	
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (predictionPieces[i][j] != nullptr) {
				predictionPieces[i][j]->SetKing(predictionKing);
			}
		}
	}

	if (predictionEnemyPlaces[eventualAction->coordonates[0]][eventualAction->coordonates[1]]) {
		predictionEnemyPieces[eventualAction->coordonates[0]][eventualAction->coordonates[1]] = nullptr;
		predictionEnemyPlaces[eventualAction->coordonates[0]][eventualAction->coordonates[1]] = false;
	}

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (predictionEnemyPieces[i][j] != nullptr) {
				predictionEnemyPieces[i][j]->possibleActions.clear();
				predictionEnemyPieces[i][j]->Move(predictionEnemyPlaces, predictionPlaces, placeAttackedByEnemy, predictionEnemyPieces, predictionPieces);
			}
		}
	}

	if (predictionPieces[eventualAction->coordonates[0]][eventualAction->coordonates[1]]->king->isAttacked) {
		predictionPieces.clear();
		predictionEnemyPieces.clear();
		return true;
	}
	predictionPieces.clear();
	predictionEnemyPieces.clear();
	return false;
}

bool NodeTree::isCheckmated(Node currentNode, bool side) {
	int iterator = 0;
	if (side) {
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					if (currentNode.pieces[i][j] != nullptr) {
						for (auto& action : currentNode.pieces[i][j]->possibleActions) {
							if (!action.get()->isDeleted){
								iterator++;
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
							if (!action.get()->isDeleted) {
								iterator++;
							}
						}
					}
				}
			}
	}
	if (side)
		std::cout << iterator << "\n";
	if (iterator == 0) {
		std::cout << "Echec et mat \n";
		return true;
	}
	return false;
}