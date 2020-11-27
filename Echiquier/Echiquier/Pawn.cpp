#include "Pawn.h"

Pawn::Pawn(std::shared_ptr<WindowManager> window, int x, int y) {
	this->window = window;
	ID = 0;
	coordonates[0] = x, coordonates[1] = y;
	if (y == 6) {
		dir.SetVector(0, -1);
		attackDir1.SetVector(-1, -1), attackDir2.SetVector(1, -1);
		src = { 667, 2 , 128, 128 };
		int pieceSquareValue[8][8] =
		{ {0,0,0,0,0,0,0,0},
		  {50,50,50,50,50,50,50,50},
		  {10,10,20,30,30,20,10,10},
		  {5,5,10,25,25,10,5,5},
		  {0,0,0,20,20,0,0,0},
		  {5,-5,-10,0,0,-10,-5,5},
		  {5,10,10,-20,-20,10,10,5},
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
		dir.SetVector(0, 1);
		attackDir1.SetVector(-1, 1), attackDir2.SetVector(1, 1);
		src = { 667, 138, 128, 128 };
		int pieceSquareValue[8][8] =
		{ {0,0,0,0,0,0,0,0},
		  {5,10,10,-20,-20,10,10,5},
		  {5,-5,-10,0,0,-10,-5,5},
		  {0,0,0,20,20,0,0,0},
		  {5,5,10,25,25,10,5,5},
		  {10,10,20,30,30,20,10,10},
		  {50,50,50,50,50,50,50,50},
		  {0,0,0,0,0,0,0,0} };
		

		for (int i = 0; i < 8; i++) {
			std::vector<int> line;
			for (int j = 0; j < 8; j++) {
				line.push_back(pieceSquareValue[i][j]);
			}
			pieceSquareTable.push_back(line);
		}
	}
}

Pawn::Pawn(std::shared_ptr<WindowManager> window, int coordonates[2]) {
	this->window = window;
	if (coordonates[1] == 6) {
		dir.SetVector(0, -1);
		attackDir1.SetVector(-1, -1), attackDir2.SetVector(1, -1);
		src = { 667, 2 , 128, 128 };
		int pieceSquareValue[8][8] =
		{ {0,0,0,0,0,0,0,0},
		  {5,10,10,-20,-20,10,10,5},
		  {5,-5,-10,0,0,-10,-5,5},
		  {0,0,0,20,20,0,0,0},
		  {5,5,10,25,25,10,5,5},
		  {10,10,20,30,30,20,10,10},
		  {50,50,50,50,50,50,50,50},
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
		dir.SetVector(0, 1);
		attackDir1.SetVector(-1, 1), attackDir2.SetVector(1, 1);
		src = { 667, 138, 128, 128 };
		int pieceSquareValue[8][8] =
		{ {0,0,0,0,0,0,0,0},
		  {50,50,50,50,50,50,50,50},
		  {10,10,20,30,30,20,10,10},
		  {5,5,10,25,25,10,5,5},
		  {0,0,0,20,20,0,0,0},
		  {5,-5,-10,0,0,-10,-5,5},
		  {5,10,10,-20,-20,10,10,5},
		  {0,0,0,0,0,0,0,0} };

		for (int i = 0; i < 8; i++) {
			std::vector<int> line;
			for (int j = 0; j < 8; j++) {
				line.push_back(pieceSquareValue[i][j]);
			}
			pieceSquareTable.push_back(line);
		}
	}
	this->coordonates[0] = coordonates[0], this->coordonates[1] = coordonates[1];
}

Pawn::~Pawn() {

}

void Pawn::Move(bool placeTaken[8][8], bool enemyPlaceTaken[8][8], bool placeAttackedByEnemy[8][8], std::vector<std::vector<std::shared_ptr<Pieces>>>& allyPieces, std::vector<std::vector<std::shared_ptr<Pieces>>>& enemyPieces) {
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
	/*if (!piecesManager.king->isAttacked) {
		if (coordonates[0] + attackDir1.x < 8 &&
			coordonates[0] + attackDir1.x >= 0 &&
			coordonates[1] + attackDir1.y < 8 &&
			coordonates[1] + attackDir1.y >= 0 &&
			piecesManager.enemy->placeTaken[coordonates[0] + attackDir1.x][coordonates[1] + attackDir1.y]) {
			std::shared_ptr<PossiblePlacements> action(new PossiblePlacements(coordonates[0] + attackDir1.x, coordonates[1] + attackDir1.y));
			possibleActions.push_back(action);
			piecesManager.enemy->pieces[coordonates[0] + attackDir1.x][coordonates[1] + attackDir1.y]->isAttacked = true;
		}
		if (coordonates[0] + attackDir2.x < 8 &&
			coordonates[0] + attackDir2.x >= 0 &&
			coordonates[1] + attackDir2.y < 8 &&
			coordonates[1] + attackDir2.y >= 0 && 
			piecesManager.enemy->placeTaken[coordonates[0] + attackDir2.x][coordonates[1] + attackDir2.y]) {
			std::shared_ptr<PossiblePlacements> action(new PossiblePlacements(coordonates[0] + attackDir2.x, coordonates[1] + attackDir2.y));
			possibleActions.push_back(action);
			piecesManager.enemy->pieces[coordonates[0] + attackDir2.x][coordonates[1] + attackDir2.y]->isAttacked = true;
		}

		if (!hasMoved) {
			for (int i = 1; i <= 2; i++) {
				Vector2D v = i * dir;
				if (!placeTaken[coordonates[0]][coordonates[1] + v.y]) {
					if (piecesManager.enemy->placeTaken[coordonates[0]][coordonates[1] + v.y])
						break;
					std::shared_ptr<PossiblePlacements> action(new PossiblePlacements(coordonates[0], coordonates[1] + v.y));
					possibleActions.push_back(action);

				}
				else
					break;
			}
		}
		else {
			if (!placeTaken[coordonates[0]][coordonates[1] + dir.y] && !piecesManager.enemy->placeTaken[coordonates[0]][coordonates[1] + dir.y]) {
				std::shared_ptr<PossiblePlacements> action(new PossiblePlacements(coordonates[0], coordonates[1] + dir.y));
				possibleActions.push_back(action);
			}
		}
	}*/
    
	value = PAWNVALUE;

	if (!hasMoved) {
		for (int i = 1; i <= 2; i++) {
			Vector2D v = i * dir;
			if (coordonates[1] + v.y < 8 && coordonates[1] + v.y >= 0 && !placeTaken[coordonates[0]][coordonates[1] + v.y]) {
				if (enemyPlaceTaken[coordonates[0]][coordonates[1] + v.y])
					break;
				std::shared_ptr<PossiblePlacements> action(new PossiblePlacements(coordonates[0], coordonates[1] + v.y));
				action->isDeleted = false;
				possibleActions.push_back(action);

			}
			else
				break;
		}
	}
	else {
		if (coordonates[1] + dir.y < 8 && coordonates[1] + dir.y >= 0 && !placeTaken[coordonates[0]][coordonates[1] + dir.y] && !enemyPlaceTaken[coordonates[0]][coordonates[1] + dir.y]) {
			std::shared_ptr<PossiblePlacements> action(new PossiblePlacements(coordonates[0], coordonates[1] + dir.y));
			action->isDeleted = false;
			possibleActions.push_back(action);
		}
	}
	
	if (coordonates[0] + attackDir1.x < 8 && coordonates[0] + attackDir1.x >= 0 && coordonates[1] + attackDir1.y < 8 && coordonates[1] + attackDir1.y >= 0) {
		if (enemyPlaceTaken[coordonates[0] + attackDir1.x][coordonates[1] + attackDir1.y]) {
			std::shared_ptr<PossiblePlacements> action(new PossiblePlacements(coordonates[0] + attackDir1.x, coordonates[1] + attackDir1.y));
			action->isDeleted = false;
			possibleActions.push_back(action);
			enemyPieces[coordonates[0] + attackDir1.x][coordonates[1] + attackDir1.y]->isAttacked = true, enemyPieces[coordonates[0] + attackDir1.x][coordonates[1] + attackDir1.y]->attackingValue += enemyPieces[coordonates[0] + attackDir1.x][coordonates[1] + attackDir1.y]->value/2,
			this->attackingValue -= enemyPieces[coordonates[0] + attackDir1.x][coordonates[1] + attackDir1.y]->value / 3;
		}
		else if (placeTaken[coordonates[0] + attackDir1.x][coordonates[1] + attackDir1.y])
			allyPieces[coordonates[0] + attackDir1.x][coordonates[1] + attackDir1.y]->isDefended = true,
			allyPieces[coordonates[0] + attackDir1.x][coordonates[1] + attackDir1.y]->defendingValue += value / 3;
			//this->defendingValue += allyPieces[coordonates[0] + attackDir1.x][coordonates[1] + attackDir1.y]->value / 2;
	}

	if (coordonates[0] + attackDir2.x < 8 && coordonates[0] + attackDir2.x >= 0 && coordonates[1] + attackDir2.y < 8 && coordonates[1] + attackDir2.y >= 0) {
		if (enemyPlaceTaken[coordonates[0] + attackDir2.x][coordonates[1] + attackDir2.y]) {
			std::shared_ptr<PossiblePlacements> action(new PossiblePlacements(coordonates[0] + attackDir2.x, coordonates[1] + attackDir2.y));
			action->isDeleted = false;
			possibleActions.push_back(action);
			enemyPieces[coordonates[0] + attackDir2.x][coordonates[1] + attackDir2.y]->isAttacked = true, enemyPieces[coordonates[0] + attackDir2.x][coordonates[1] + attackDir2.y]->attackingValue += enemyPieces[coordonates[0] + attackDir2.x][coordonates[1] + attackDir2.y]->value/2,
			this->attackingValue -= enemyPieces[coordonates[0] + attackDir2.x][coordonates[1] + attackDir2.y]->value / 3;
		}
		else if (placeTaken[coordonates[0] + attackDir2.x][coordonates[1] + attackDir2.y])
			allyPieces[coordonates[0] + attackDir2.x][coordonates[1] + attackDir2.y]->isDefended = true,
			allyPieces[coordonates[0] + attackDir2.x][coordonates[1] + attackDir2.y]->defendingValue += value / 3;
			//this->defendingValue += allyPieces[coordonates[0] + attackDir2.x][coordonates[1] + attackDir2.y]->value / 2;
	}
}
