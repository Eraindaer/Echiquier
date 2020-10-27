#include "Pawn.h"

Pawn::Pawn(std::shared_ptr<WindowManager> window, int x, int y) {
	this->window = window;
	coordonates[0] = startingPoint[0] = x, coordonates[1] = startingPoint[1] = y;
	if (y == 6) {
		dir.SetVector(0, -1);
		attackDir1.SetVector(-1, -1), attackDir2.SetVector(1, -1);
		src = { 667, 2 , 128, 128 };
	}
	else {
		dir.SetVector(0, 1);
		attackDir1.SetVector(-1, 1), attackDir2.SetVector(1, 1);
		src = { 667, 138, 128, 128 };
	}
}

Pawn::Pawn(std::shared_ptr<WindowManager> window, int coordonates[2]) {
	this->window = window;
	if (coordonates[1] == 6) {
		dir.SetVector(0, -1);
		attackDir1.SetVector(-1, -1), attackDir2.SetVector(1, -1);
		src = { 667, 2 , 128, 128 };
	}
	else {
		dir.SetVector(0, 1);
		attackDir1.SetVector(-1, 1), attackDir2.SetVector(1, 1);
		src = { 667, 138, 128, 128 };
	}
	this->coordonates[0] = startingPoint[0] = coordonates[0], this->coordonates[1] = startingPoint[1] = coordonates[1];
}

Pawn::~Pawn() {

}

void Pawn::Move(bool placeTaken[8][8], Pieces& piecesManager) {
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
	if (!piecesManager.king->isAttacked) {
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
	}
}
