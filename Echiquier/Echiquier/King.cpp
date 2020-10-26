#include "King.h"

King::King(std::shared_ptr<WindowManager>window, int x, int y) {
	this->window = window;
	src = {3, 2, 128, 128};
	hasMoved = false;
	coordonates[0] = x, coordonates[1] = y;
}

King::King(std::shared_ptr<WindowManager> window, int coordonates[2]) {
	this->window = window;
	src = {3, 2, 128, 128};
	hasMoved = false;
	this->coordonates[0] = coordonates[0], this->coordonates[1] = coordonates[1];
}

King::~King() {}

void King::Move(bool placeTaken[8][8]) {
	if (possibleActions.size() == 0) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (((std::abs(i - this->coordonates[0]) == 1 && std::abs(j - this->coordonates[1]) == 1) || 
					(std::abs(i - coordonates[0]) == 1 && j == coordonates[1]) || 
					(std::abs(j - coordonates[1]) == 1 && i == coordonates[0])) && (!placeTaken[i][j])) {
					std::shared_ptr<PossiblePlacements> action(new PossiblePlacements(i, j));
					possibleActions.push_back(action);
				}
			}
		}
	}
}