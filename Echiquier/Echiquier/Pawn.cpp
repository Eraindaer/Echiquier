#include "Pawn.h"

Pawn::Pawn(std::shared_ptr<WindowManager> window, int x, int y) {
	this->window = window;
	src = { 667, 2 , 128, 128 };
	coordonates[0] = startingPoint[0] = x, coordonates[1] = startingPoint[1] = y;
}

Pawn::Pawn(std::shared_ptr<WindowManager> window, int coordonates[2]) {
	this->window = window;
	src = { 667, 2 , 128, 128 };
	this->coordonates[0] = startingPoint[0] = coordonates[0], this->coordonates[1] = startingPoint[1] = coordonates[1];
}

Pawn::~Pawn() {

}

void Pawn::Move(bool placeTaken[8][8]) {
	if (possibleActions.size() == 0) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if ((!placeTaken[i][j])) {
					if (coordonates[1] == startingPoint[1] && (coordonates[1] - j <= 2 && coordonates[1] - j > 0)) {
						std::shared_ptr<PossiblePlacements> action(new PossiblePlacements(coordonates[0], j));
						possibleActions.push_back(action);
					}
					else {
						std::shared_ptr<PossiblePlacements> action(new PossiblePlacements(coordonates[0], coordonates[1] - 1));
						possibleActions.push_back(action);
					}
				}
			}
		}
	}
}