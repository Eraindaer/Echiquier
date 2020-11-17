#include "Rook.h"

Rook::Rook(std::shared_ptr<WindowManager> window, int x, int y) {
	this->window = window;
	ID = 3;
	if (y == 7) {
		src = { 537, 2, 128, 128 };
		int pieceSquareValue[8][8] =
		{ {0,0,0,5,5,0,0,0},
		  {5,10,10,10,10,10,10,5},
		  {-5,0,0,0,0,0,0,-5},
		  {-5,0,0,0,0,0,0,-5},
		  {-5,0,0,0,0,0,0,-5},
		  {-5,0,0,0,0,0,0,-5},
		  {-5,0,0,0,0,0,0,-5},
		  {0,0,0,5,5,0,0,0} };
		
		for (int i = 0; i < 8; i++) {
			std::vector<int> line;
			for (int j = 0; j < 8; j++) {
				line.push_back(pieceSquareValue[i][j]);
			}
			pieceSquareTable.push_back(line);
		}
	}
	else {
		src = { 537, 138, 128, 128 };
		int pieceSquareValue[8][8] =
		{ {0,0,0,5,5,0,0,0},
		  {-5,0,0,0,0,0,0,-5},
		  {-5,0,0,0,0,0,0,-5},
		  {-5,0,0,0,0,0,0,-5},
		  {-5,0,0,0,0,0,0,-5},
		  {-5,0,0,0,0,0,0,-5},
		  {5,10,10,10,10,10,10,5},
		  {0,0,0,0,0,0,0,0} };
		
		for (int i = 0; i < 8; i++) {
			std::vector<int> line;
			for (int j = 0; j < 8; j++) {
				line.push_back(pieceSquareValue[i][j]);
			}
			pieceSquareTable.push_back(line);
		}
	}
	coordonates[0] = x, coordonates[1] = y;

	dir[0].SetVector(1, 0), dir[1].SetVector(-1, 0), dir[2].SetVector(0, 1), dir[3].SetVector(0, -1);
}

Rook::Rook(std::shared_ptr<WindowManager> window, int coordonates[2]) {
	this->window = window;
	if (coordonates[1] == 7) {
		src = { 537, 2, 128, 128 };
		int pieceSquareValue[8][8] =
		{ {0,0,0,0,0,0,0,0},
		  {0,0,0,0,0,0,0,0},
		  {0,0,0,0,0,0,0,0},
		  {0,0,0,0,0,0,0,0},
		  {0,0,0,0,0,0,0,0},
		  {0,0,0,0,0,0,0,0},
		  {0,0,0,0,0,0,0,0},
		  {0,0,0,0,0,0,0,0} };
		for (int i = 0; i < 8; i++) {
			std::vector<int> line;
			for (int j = 0; j < 8; j++) {
				line.push_back(pieceSquareValue[i][j]);
			}
			pieceSquareTable.push_back(line);
		}
	}
	else {
		src = { 537, 138, 128, 128 };
		int pieceSquareValue[8][8] =
		{ {0,0,0,0,0,0,0,0},
		  {0,0,0,0,0,0,0,0},
		  {0,0,0,0,0,0,0,0},
		  {0,0,0,0,0,0,0,0},
		  {0,0,0,0,0,0,0,0},
		  {0,0,0,0,0,0,0,0},
		  {0,0,0,0,0,0,0,0},
		  {0,0,0,0,0,0,0,0} };
		for (int i = 0; i < 8; i++) {
			std::vector<int> line;
			for (int j = 0; j < 8; j++) {
				line.push_back(pieceSquareValue[i][j]);
			}
			pieceSquareTable.push_back(line);
		}
	}
	this->coordonates[0]= coordonates[0], this->coordonates[1] = coordonates[1];
	dir[0].SetVector(1, 1), dir[1].SetVector(1, -1), dir[2].SetVector(-1, -1), dir[3].SetVector(-1, 1);
}

Rook::~Rook() {}

void Rook::Move(bool placeTaken[8][8], bool enemyPlaceTaken[8][8], bool placeAttackedByEnemy[8][8], std::vector<std::vector<std::shared_ptr<Pieces>>>& allyPieces, std::vector<std::vector<std::shared_ptr<Pieces>>>& enemyPieces) {
	possibleActions.clear();
	value = ROOKVALUE;
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
	/*if (piecesManager.king->isAttacked) {
		for (int i = 1; i < 8; i++) {
			Vector2D v = i * dir1;
			if (coordonates[0] + v.x < 8 && !placeTaken[coordonates[0] + v.x][coordonates[1]]) {
				std::shared_ptr<PossiblePlacements> action(new PossiblePlacements(coordonates[0] + v.x, coordonates[1]));
				possibleActions.push_back(action);
				if (piecesManager.enemy->placeTaken[coordonates[0] + v.x][coordonates[1]]) {
					piecesManager.enemy->pieces[coordonates[0] + v.x][coordonates[1]]->isAttacked = true;
					break;
				}
			}
			else
				break;
		}
		for (int i = 1; i < 8; i++) {
			Vector2D v = i * dir2;
			if (coordonates[0] + v.x >= 0 && !placeTaken[coordonates[0] + v.x][coordonates[1]]) {
				std::shared_ptr<PossiblePlacements> action(new PossiblePlacements(coordonates[0] + v.x, coordonates[1]));
				possibleActions.push_back(action);
				if (piecesManager.enemy->placeTaken[coordonates[0] + v.x][coordonates[1]]) {
					piecesManager.enemy->pieces[coordonates[0] + v.x][coordonates[1]]->isAttacked = true;
					break;
				}
			}
			else
				break;
		}
		for (int i = 1; i < 8; i++) {
			Vector2D v = i * dir3;
			if (coordonates[1] + v.y < 8 && !placeTaken[coordonates[0]][coordonates[1] + v.y]) {
				std::shared_ptr<PossiblePlacements> action(new PossiblePlacements(coordonates[0], coordonates[1] + v.y));
				possibleActions.push_back(action);
				if (piecesManager.enemy->placeTaken[coordonates[0]][coordonates[1] + v.y]) {
					piecesManager.enemy->pieces[coordonates[0]][coordonates[1] + v.y]->isAttacked = true;
					break;
				}
			}
			else
				break;
		}
		for (int i = 1; i < 8; i++) {
			Vector2D v = i * dir4;
			if (coordonates[1] + v.y >= 0 && !placeTaken[coordonates[0]][coordonates[1] + v.y]) {
				std::shared_ptr<PossiblePlacements> action(new PossiblePlacements(coordonates[0], coordonates[1] + v.y));
				possibleActions.push_back(action);
				if (piecesManager.enemy->placeTaken[coordonates[0]][coordonates[1] + v.y]) {
					piecesManager.enemy->pieces[coordonates[0]][coordonates[1] + v.y]->isAttacked = true;
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
						enemyPieces[coordonates[0] + v.x][coordonates[1] + v.y]->attackingValue += enemyPieces[coordonates[0] + v.x][coordonates[1] + v.y]->value/2;
						this->attackingValue -= enemyPieces[coordonates[0] + v.x][coordonates[1] + v.y]->value / 3;
						break;
					}
				}
				else {
					allyPieces[coordonates[0] + v.x][coordonates[1] + v.y]->isDefended = true;
					allyPieces[coordonates[0] + v.x][coordonates[1] + v.y]->defendingValue += value /3;
					//this->defendingValue += allyPieces[coordonates[0] + v.x][coordonates[1] + v.y]->value / 2;
					break;
				}
			}
			else
				break;
		}
	}
}