#include "Knight.h"

Knight::Knight(std::shared_ptr<WindowManager> window, int x, int y) {
	this->window = window;
	value = KNIGHTVALUE;
	if (y == 7)
		src = { 404, 2, 128, 128 };
	else
		src = { 404, 138, 128, 128 };
	coordonates[0] = x, coordonates[1] = y;

	dir[0].SetVector(2, 1), dir[1].SetVector(2, -1), dir[2].SetVector(-2, -1), dir[3].SetVector(-2, 1),
	dir[4].SetVector(1, 2), dir[5].SetVector(-1, 2), dir[6].SetVector(-1, -2), dir[7].SetVector(1, -2);
}

Knight::Knight(std::shared_ptr<WindowManager> window, int coordonates[2]) {
	this->window = window;
	value = KNIGHTVALUE;
	if (coordonates[1] == 7)
		src = { 404, 2, 128, 128 };
	else
		src = { 404, 138, 128, 128 };
	this->coordonates[0] = coordonates[0], this->coordonates[1] = coordonates[1];
	dir[0].SetVector(2, 1), dir[1].SetVector(2, -1), dir[2].SetVector(-2, -1), dir[3].SetVector(-2, 1),
	dir[4].SetVector(1, 2), dir[5].SetVector(-1, 2), dir[6].SetVector(-1, -2), dir[7].SetVector(1, -2);
}

Knight::~Knight() {}

void Knight::Move(bool placeTaken[8][8], bool enemyPlaceTaken[8][8], bool placeAttackedByEnemy[8][8], std::vector<std::vector<std::shared_ptr<Pieces>>>& allyPieces, std::vector<std::vector<std::shared_ptr<Pieces>>>& enemyPieces) {
	possibleActions.clear();
	/*for (auto& piece : piecesManager.enemy->pieces) {
		if (
		)
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
	/*if (!piecesManager.king->isAttacked) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (((std::abs(i - coordonates[0]) == 2 && std::abs(j - coordonates[1]) == 1) || (std::abs(i - coordonates[0]) == 1 && std::abs(j - coordonates[1]) == 2)) && (!placeTaken[i][j])) {
					std::shared_ptr<PossiblePlacements> action(new PossiblePlacements(i, j));
					possibleActions.push_back(action);
				}
			}
		}
	}*/
		for (int j = 0; j < 8; j++) {
			if (coordonates[0] + dir[j].x < 8 && coordonates[0] + dir[j].x >= 0 &&
				coordonates[1] + dir[j].y < 8 && coordonates[1] + dir[j].y >= 0) {

				if (!placeTaken[coordonates[0] + dir[j].x][coordonates[1] + dir[j].y]) {
					std::shared_ptr<PossiblePlacements> action(new PossiblePlacements(coordonates[0] + dir[j].x, coordonates[1] + dir[j].y));
					possibleActions.push_back(action);
					if (enemyPlaceTaken[coordonates[0] + dir[j].x][coordonates[1] + dir[j].y]) {
						enemyPieces[coordonates[0] + dir[j].x][coordonates[1] + dir[j].y]->isAttacked = true;
						enemyPieces[coordonates[0] + dir[j].x][coordonates[1] + dir[j].y]->attackingValue -= value / 3;
						this->attackingValue += enemyPieces[coordonates[0] + dir[j].x][coordonates[1] + dir[j].y]->value / 3;
					}
				}
				else
					allyPieces[coordonates[0] + dir[j].x][coordonates[1] + dir[j].y]->isDefended = true,
					allyPieces[coordonates[0] + dir[j].x][coordonates[1] + dir[j].y]->defendingValue += value / 3;
					//this->defendingValue += allyPieces[coordonates[0] + dir[j].x][coordonates[1] + dir[j].y]->value / 2;
			}
		}
	}