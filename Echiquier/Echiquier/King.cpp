#include "King.h"

King::King(std::shared_ptr<WindowManager>window, int x, int y, std::shared_ptr<Pieces>& rook1, std::shared_ptr<Pieces>& rook2) {
	this->window = window;
	if (y == 7)
		src = { 3, 2, 128, 128 };
	else
		src = { 3, 138, 128, 128 };
	coordonates[0] = x, coordonates[1] = y;
	this->rook1 = *&rook1;
	this->rook2 = *&rook2;
	dir[0].SetVector(1, 0), dir[1].SetVector(-1, 0), dir[2].SetVector(0, 1), dir[3].SetVector(0, -1), dir[4].SetVector(1, 1), dir[5].SetVector(1, -1), dir[6].SetVector(-1, -1), dir[7].SetVector(-1, 1);
}

King::King(std::shared_ptr<WindowManager> window, int coordonates[2], std::shared_ptr<Pieces>& rook1, std::shared_ptr<Pieces>& rook2) {
	this->window = window;
	if (coordonates[1] == 7)
		src = { 3, 2, 128, 128 };
	else
		src = { 3, 138, 128, 128 };
	this->coordonates[0] = coordonates[0], this->coordonates[1] = coordonates[1];
	this->rook1 = *&rook1;
	this->rook2 = *&rook2;
	dir[0].SetVector(1, 0), dir[1].SetVector(-1, 0), dir[2].SetVector(0, 1), dir[3].SetVector(0, -1), dir[4].SetVector(1, 1), dir[5].SetVector(1, -1), dir[6].SetVector(-1, -1), dir[7].SetVector(-1, 1);
}

King::~King() {}

void King::Move(bool placeTaken[8][8], bool enemyPlaceTaken[8][8], bool placeAttackedByEnemy[8][8], std::vector<std::vector<std::shared_ptr<Pieces>>>& allyPieces, std::vector<std::vector<std::shared_ptr<Pieces>>>& enemyPieces) {
	possibleActions.clear();
	this->allyPieces = *&allyPieces;
	/*for (auto& piece : piecesManager.enemy->pieces) {
		if (isAttacked)
			break;
		for (auto& action : piece->possibleActions) {
			if (action->coordonates[0] == coordonates[0] &&
				action->coordonates[1] == coordonates[1]) {
				isAttacked = true;
				break;
			}
			else {
				isAttacked = false;
			}
		}
	}*/
	/*for (int i = 0; i < 8; i++) {
		/*for (auto& piece : piecesManager.enemy->pieces) {
			for (auto& action : piece->possibleActions) {
					if (coordonates[0] + dir[i].x >= 0 &&
						coordonates[0] + dir[i].x < 8 &&
						coordonates[1] + dir[i].y >= 0 &&
						coordonates[1] + dir[i].y < 8 &&
						!placeTaken[coordonates[0] + dir[i].x][coordonates[1] + dir[i].y]/* &&
						coordonates[0] + dir[i].x != action->coordonates[0] &&
						coordonates[1] + dir[i].y != action->coordonates[1]) {
						std::shared_ptr<PossiblePlacements> action(new PossiblePlacements(coordonates[0] + dir[i].x, coordonates[1] + dir[i].y));
						possibleActions.push_back(action);
						if (piecesManager.enemy->pieces[coordonates[0] + dir[i].x][coordonates[1] + dir[i].y] != nullptr) {
							piecesManager.enemy->pieces[coordonates[0] + dir[i].x][coordonates[1] + dir[i].y]->isAttacked = true;
						}
					}
				}
				if (!rook1->hasMoved && !hasMoved && !placeTaken[1][coordonates[1]] && !placeTaken[2][coordonates[1]] && !placeTaken[3][coordonates[1]]) {
					std::shared_ptr<PossiblePlacements> action(new PossiblePlacements(2, coordonates[1]));
					possibleActions.push_back(action);
				}
				if (!rook2->hasMoved && !hasMoved && !placeTaken[5][coordonates[1]] && !placeTaken[6][coordonates[1]]) {
					std::shared_ptr<PossiblePlacements> action(new PossiblePlacements(6, coordonates[1]));
					possibleActions.push_back(action);
				}
			//}
		//}*/
	for (int j = 0; j < 8; j++) {
		if (coordonates[0] + dir[j].x < 8 && coordonates[0] + dir[j].x >= 0 &&
			coordonates[1] + dir[j].y < 8 && coordonates[1] + dir[j].y >= 0){

			if (!placeTaken[coordonates[0] + dir[j].x][coordonates[1] + dir[j].y]) {
				std::shared_ptr<PossiblePlacements> action(new PossiblePlacements(coordonates[0] + dir[j].x, coordonates[1] + dir[j].y));
				possibleActions.push_back(action);
				if (enemyPlaceTaken[coordonates[0] + dir[j].x][coordonates[1] + dir[j].y]) {
					enemyPieces[coordonates[0] + dir[j].x][coordonates[1] + dir[j].y]->isAttacked = true;
					if (enemyPieces[coordonates[0] + dir[j].x][coordonates[1] + dir[j].y]->isDefended)
						possibleActions.pop_back();
				}
			}
			else
				allyPieces[coordonates[0] + dir[j].x][coordonates[1] + dir[j].y]->isDefended = true;
		}
	}
	if (!placeAttackedByEnemy[4][coordonates[1]]) {
		if (!rook1->hasMoved && !hasMoved && !placeTaken[1][coordonates[1]] && !placeTaken[2][coordonates[1]] && !placeTaken[3][coordonates[1]] &&
			!enemyPlaceTaken[1][coordonates[1]] && !enemyPlaceTaken[2][coordonates[1]] && !enemyPlaceTaken[3][coordonates[1]] &&
			!placeAttackedByEnemy[0][coordonates[1]] && !placeAttackedByEnemy[1][coordonates[1]] && !placeAttackedByEnemy[2][coordonates[1]] && !placeAttackedByEnemy[3][coordonates[1]]) {
			std::shared_ptr<PossiblePlacements> action(new PossiblePlacements(2, coordonates[1]));
			possibleActions.push_back(action);
		}
		if (!rook2->hasMoved && !hasMoved && !placeTaken[5][coordonates[1]] && !placeTaken[6][coordonates[1]] &&
			!enemyPlaceTaken[5][coordonates[1]] && !enemyPlaceTaken[6][coordonates[1]] &&
			!placeAttackedByEnemy[5][coordonates[1]] && !placeAttackedByEnemy[6][coordonates[1]] && !placeAttackedByEnemy[7][coordonates[1]]) {
			std::shared_ptr<PossiblePlacements> action(new PossiblePlacements(6, coordonates[1]));
			possibleActions.push_back(action);
		}
	}
}

void King::SetCoordonates(int x, int y) {
	if (!hasMoved)
		hasMoved = true;
	this->coordonates[0] = x, this->coordonates[1] = y;
	if (std::abs(x - coordonates[0]) <= 2) {
		if (std::abs(rook1->coordonates[0] - x) == 2) {
			allyPieces[x + 1][rook1->coordonates[1]] = allyPieces[rook1->coordonates[0]][rook1->coordonates[1]];
			allyPieces[rook1->coordonates[0]][rook1->coordonates[1]] = nullptr;
			rook1->SetCoordonates(x + 1, rook1->coordonates[1]);
		}
		else if(std::abs(rook2->coordonates[0] - x) == 1) {
			allyPieces[x - 1][rook2->coordonates[1]] = allyPieces[rook2->coordonates[0]][rook2->coordonates[1]];
			allyPieces[rook2->coordonates[0]][rook2->coordonates[1]] = nullptr;
			rook2->SetCoordonates(x - 1, rook2->coordonates[1]);
		}
	}
	/*if (!hasMoved)
		hasMoved = true;
	if (boolean.enemy->placeTaken[x][y]) {
		boolean.enemy->placeTaken[x][y] = false;
		int iterator = 0;
		for (auto& piece : boolean.enemy->piecesList) {
			if (x == piece->coordonates[0] &&
				y == piece->coordonates[1]) {
				boolean.enemy->pieces.erase(boolean.enemy->pieces.begin() + iterator);
				break;
			}
			iterator++;
		}
	}
	boolean.placeTaken[coordonates[0]][coordonates[1]] = false, boolean.placeTaken[x][y] = true;
	
	this->coordonates[0] = x, this->coordonates[1] = y;
	boolean.selection = false;
	boolean.turn = false, boolean.enemy->turn = true;*/
}