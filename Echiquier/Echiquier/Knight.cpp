#include "Knight.h"

Knight::Knight(std::shared_ptr<WindowManager> window, int x, int y) {
	this->window = window;
	if (y == 7)
		src = { 404, 2, 128, 128 };
	else
		src = { 404, 138, 128, 128 };
	coordonates[0] = x, coordonates[1] = y;}

Knight::Knight(std::shared_ptr<WindowManager> window, int coordonates[2]) {
	this->window = window;
	if (coordonates[1] == 7)
		src = { 404, 2, 128, 128 };
	else
		src = { 404, 138, 128, 128 };
	this->coordonates[0] = coordonates[0], this->coordonates[1] = coordonates[1];
}

Knight::~Knight() {}

void Knight::Move(bool placeTaken[8][8], Pieces& piecesManager) {
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
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (((std::abs(i - coordonates[0]) == 2 && std::abs(j - coordonates[1]) == 1) || (std::abs(i - coordonates[0]) == 1 && std::abs(j - coordonates[1]) == 2)) && (!placeTaken[i][j])) {
					std::shared_ptr<PossiblePlacements> action(new PossiblePlacements(i, j));
					possibleActions.push_back(action);
				}
			}
		}
	}
}