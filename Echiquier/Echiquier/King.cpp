#include "King.h"

King::King(std::shared_ptr<WindowManager>window, int x, int y, std::shared_ptr<Pieces>& rook1, std::shared_ptr<Pieces> rook2) {
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

King::King(std::shared_ptr<WindowManager> window, int coordonates[2], std::shared_ptr<Pieces>& rook1, std::shared_ptr<Pieces> rook2) {
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

void King::Move(bool placeTaken[8][8], Pieces& piecesManager) {
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
	for (int i = 0; i < 8; i++) {
		/*for (auto& piece : piecesManager.enemy->pieces) {
			for (auto& action : piece->possibleActions) {*/
					if (coordonates[0] + dir[i].x >= 0 &&
						coordonates[0] + dir[i].x < 8 &&
						coordonates[1] + dir[i].y >= 0 &&
						coordonates[1] + dir[i].y < 8 &&
						!placeTaken[coordonates[0] + dir[i].x][coordonates[1] + dir[i].y]/* &&
						coordonates[0] + dir[i].x != action->coordonates[0] &&
						coordonates[1] + dir[i].y != action->coordonates[1]*/) {
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
		//}
	}

void King::SetCoordonates(int x, int y, Pieces& boolean) {
	if (!hasMoved)
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
	if (std::abs(x - coordonates[0]) == 2) {
		if (std::abs(rook1->coordonates[0] - x) == 2) {
			rook1->SetCoordonates(x + 1, rook1->coordonates[1], boolean);
		}
		else {
			rook2->SetCoordonates(x - 1, rook2->coordonates[1], boolean);
		}
	}
	this->coordonates[0] = x, this->coordonates[1] = y;
	boolean.selection = false;
	boolean.turn = false, boolean.enemy->turn = true;
}