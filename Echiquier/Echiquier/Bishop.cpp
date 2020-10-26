#include "Bishop.h"

Bishop::Bishop(std::shared_ptr<WindowManager> window, int x, int y) {
	this->window = window;
	src = {269, 2 ,128, 128};
	coordonates[0] = x, coordonates[1] = y;
	dir1.SetVector(1, 1), dir2.SetVector(1, -1), dir3.SetVector(-1, -1), dir4.SetVector(-1, 1);
}

Bishop::Bishop(std::shared_ptr<WindowManager> window, int coordonates[2]) {
	this->window = window;
	src = {269, 2 ,128, 128};
	this->coordonates[0] = coordonates[0], this->coordonates[1] = coordonates[1];
}

Bishop::~Bishop() {

}

void Bishop::Move(bool placeTaken[8][8]) {
	if (possibleActions.size() == 0) {
		for (int i = 1; i < 8; i++) {
			Vector2D v = i * dir1;
			if (coordonates[0] + v.x < 8 && coordonates[1] + v.y < 8 && !placeTaken[coordonates[0] + v.x][coordonates[1] + v.y]) {
				std::shared_ptr<PossiblePlacements> action(new PossiblePlacements(coordonates[0] + v.x, coordonates[1] + v.y));
				possibleActions.push_back(action);
			}
			else
				break;
		}
		for (int i = 1; i < 8; i++) {
			Vector2D v = i * dir2;
			if (coordonates[0] + v.x < 8 && coordonates[1] + v.y >= 0 && !placeTaken[coordonates[0] + v.x][coordonates[1] + v.y]) {
				std::shared_ptr<PossiblePlacements> action(new PossiblePlacements(coordonates[0] + v.x, coordonates[1] + v.y));
				possibleActions.push_back(action);
			}
			else
				break;
		}
		for (int i = 1; i < 8; i++) {
			Vector2D v = i * dir3;
			if (coordonates[0] + v.x >= 0 && coordonates[1] + v.y >= 0 && !placeTaken[coordonates[0] + v.x][coordonates[1] + v.y]) {
				std::shared_ptr<PossiblePlacements> action(new PossiblePlacements(coordonates[0] + v.x, coordonates[1] + v.y));
				possibleActions.push_back(action);
			}
			else
				break;
		}
		for (int i = 1; i < 8; i++) {
			Vector2D v = i * dir4;
			if (coordonates[0] + v.x >= 0 && coordonates[1] + v.y < 8 && !placeTaken[coordonates[0] + v.x][coordonates[1] + v.y]) {
				std::shared_ptr<PossiblePlacements> action(new PossiblePlacements(coordonates[0] + v.x, coordonates[1] + v.y));
				possibleActions.push_back(action);
			}
			else
				break;
		}
	}
}