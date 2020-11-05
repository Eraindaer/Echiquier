#include "Bishop.h"

Bishop::Bishop(std::shared_ptr<WindowManager> window, int x, int y) {
	this->window = window;
	if (y == 7)
		src = { 269, 2 ,128, 128 };
	else
		src = { 269, 138, 128, 128 };
	coordonates[0] = x, coordonates[1] = y;
	dir[0].SetVector(1, 1), dir[1].SetVector(1, -1), dir[2].SetVector(-1, -1), dir[3].SetVector(-1, 1);
}

Bishop::Bishop(std::shared_ptr<WindowManager> window, int coordonates[2]) {
	this->window = window;
	if (coordonates[1] == 7)
		src = { 269, 2 ,128, 128 };
	else
		src = { 269, 138, 128, 128 };
	this->coordonates[0] = coordonates[0], this->coordonates[1] = coordonates[1];
	dir[0].SetVector(1, 1), dir[1].SetVector(1, -1), dir[2].SetVector(-1, -1), dir[3].SetVector(-1, 1);
}

Bishop::~Bishop() {

}

void Bishop::Move(bool placeTaken[8][8], bool enemyPlaceTaken[8][8], bool placeAttackedByEnemy[8][8], std::vector<std::vector<std::shared_ptr<Pieces>>>& allyPieces, std::vector<std::vector<std::shared_ptr<Pieces>>>& enemyPieces) {
	possibleActions.clear();
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
	/*if (king->isAttacked) {
		for (int i = 1; i < 8; i++) {
			Vector2D v = i * dir1;
			if (coordonates[0] + v.x < 8 && coordonates[1] + v.y < 8 && !placeTaken[coordonates[0] + v.x][coordonates[1] + v.y]) {
				std::shared_ptr<PossiblePlacements> action(new PossiblePlacements(coordonates[0] + v.x, coordonates[1] + v.y));
				possibleActions.push_back(action);
				if (enemyPlaceTaken[coordonates[0] + v.x][coordonates[1] + v.y]) {
					piecesManager.enemy->pieces[coordonates[0] + v.x][coordonates[1] + v.y]->isAttacked = true;
					break;
				}
			}
			else
				break;
		}
		for (int i = 1; i < 8; i++) {
			Vector2D v = i * dir2;
			if (coordonates[0] + v.x < 8 && coordonates[1] + v.y >= 0 && !placeTaken[coordonates[0] + v.x][coordonates[1] + v.y]) {
				std::shared_ptr<PossiblePlacements> action(new PossiblePlacements(coordonates[0] + v.x, coordonates[1] + v.y));
				possibleActions.push_back(action);
				if (piecesManager.enemy->placeTaken[coordonates[0] + v.x][coordonates[1] + v.y]) {
					piecesManager.enemy->pieces[coordonates[0] + v.x][coordonates[1] + v.y]->isAttacked = true;
					break;
				}
			}
			else
				break;
		}
		for (int i = 1; i < 8; i++) {
			Vector2D v = i * dir3;
			if (coordonates[0] + v.x >= 0 && coordonates[1] + v.y >= 0 && !placeTaken[coordonates[0] + v.x][coordonates[1] + v.y]) {
				std::shared_ptr<PossiblePlacements> action(new PossiblePlacements(coordonates[0] + v.x, coordonates[1] + v.y));
				possibleActions.push_back(action);
				if (piecesManager.enemy->placeTaken[coordonates[0] + v.x][coordonates[1] + v.y]) {
					piecesManager.enemy->pieces[coordonates[0] + v.x][coordonates[1] + v.y]->isAttacked = true;
					break;
				}
			}
			else
				break;
		}
		for (int i = 1; i < 8; i++) {
			Vector2D v = i * dir4;
			if (coordonates[0] + v.x >= 0 && coordonates[1] + v.y < 8 && !placeTaken[coordonates[0] + v.x][coordonates[1] + v.y]) {
				std::shared_ptr<PossiblePlacements> action(new PossiblePlacements(coordonates[0] + v.x, coordonates[1] + v.y));
				possibleActions.push_back(action);
				if (piecesManager.enemy->placeTaken[coordonates[0] + v.x][coordonates[1] + v.y]) {
					piecesManager.enemy->pieces[coordonates[0] + v.x][coordonates[1] + v.y]->isAttacked = true;
					break;
				}
			}
			else
				break;
		}
	}*/
	for (int i = 0; i < 4; i++) {
		for (int j = 1; j < 8; j++) {
			Vector2D v = j * dir[i];
			if (coordonates[0] + v.x < 8 && coordonates[0] + v.x >= 0 &&
				coordonates[1] + v.y < 8 && coordonates[1] + v.y >= 0) {

				if (!placeTaken[coordonates[0] + v.x][coordonates[1] + v.y]) {
					std::shared_ptr<PossiblePlacements> action(new PossiblePlacements(coordonates[0] + v.x, coordonates[1] + v.y));
					possibleActions.push_back(action);
					if (enemyPlaceTaken[coordonates[0] + v.x][coordonates[1] + v.y]) {
						enemyPieces[coordonates[0] + v.x][coordonates[1] + v.y]->isAttacked = true;
						break;
					}
				}
				else {
					allyPieces[coordonates[0] + v.x][coordonates[1] + v.y]->isDefended = true;
					break;
				}
			}
			else
					break;
		}
	}
}
