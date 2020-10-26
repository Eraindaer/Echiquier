#include "Queen.h"

Queen::Queen(std::shared_ptr<WindowManager> window, int x, int y) {
	this->window = window;
	src = { 136, 2, 128, 128 };
	coordonates[0] = x, coordonates[1] = y;
	dir[0].SetVector(1, 0), dir[1].SetVector(-1, 0), dir[2].SetVector(0, 1), dir[3].SetVector(0, -1), dir[4].SetVector(1, 1), dir[5].SetVector(1, -1), dir[6].SetVector(-1, -1), dir[7].SetVector(-1, 1);
}
Queen::Queen(std::shared_ptr<WindowManager> window, int coordonates[2]) {
	this->window = window;
	src = { 136, 2, 128, 128 };
	this->coordonates[0] = coordonates[0], this->coordonates[1] = coordonates[1];
}

Queen::~Queen() {}

void Queen::Move(bool placeTaken[8][8]) {
	if (possibleActions.size() == 0) {
		for (int i = 1; i < 8; i++) {
			Vector2D v = i * dir[0];
			if (coordonates[0] + v.x < 8 && !placeTaken[coordonates[0] + v.x][coordonates[1]]) {
				std::shared_ptr<PossiblePlacements> action(new PossiblePlacements(coordonates[0] + v.x, coordonates[1]));
				possibleActions.push_back(action);
			}
			else
				break;
		}
		for (int i = 1; i < 8; i++) {
			Vector2D v = i * dir[1];
			if (coordonates[0] + v.x >= 0 && !placeTaken[coordonates[0] + v.x][coordonates[1]]) {
				std::shared_ptr<PossiblePlacements> action(new PossiblePlacements(coordonates[0] + v.x, coordonates[1]));
				possibleActions.push_back(action);
			}
			else
				break;
		}
		for (int i = 1; i < 8; i++) {
			Vector2D v = i * dir[2];
			if (coordonates[1] + v.y < 8 && !placeTaken[coordonates[0]][coordonates[1] + v.y]) {
				std::shared_ptr<PossiblePlacements> action(new PossiblePlacements(coordonates[0], coordonates[1] + v.y));
				possibleActions.push_back(action);
			}
			else
				break;
		}
		for (int i = 1; i < 8; i++) {
			Vector2D v = i * dir[3];
			if (coordonates[1] + v.y >= 0 && !placeTaken[coordonates[0]][coordonates[1] + v.y]) {
				std::shared_ptr<PossiblePlacements> action(new PossiblePlacements(coordonates[0], coordonates[1] + v.y));
				possibleActions.push_back(action);
			}
			else
				break;
		}
		for (int i = 1; i < 8; i++) {
			Vector2D v = i * dir[4];
			if (coordonates[0] + v.x < 8 && coordonates[1] + v.y < 8 && !placeTaken[coordonates[0] + v.x][coordonates[1] + v.y]) {
				std::shared_ptr<PossiblePlacements> action(new PossiblePlacements(coordonates[0] + v.x, coordonates[1] + v.y));
				possibleActions.push_back(action);
			}
			else
				break;
		}
		for (int i = 1; i < 8; i++) {
			Vector2D v = i * dir[5];
			if (coordonates[0] + v.x < 8 && coordonates[1] + v.y >= 0 && !placeTaken[coordonates[0] + v.x][coordonates[1] + v.y]) {
				std::shared_ptr<PossiblePlacements> action(new PossiblePlacements(coordonates[0] + v.x, coordonates[1] + v.y));
				possibleActions.push_back(action);
			}
			else
				break;
		}
		for (int i = 1; i < 8; i++) {
			Vector2D v = i * dir[6];
			if (coordonates[0] + v.x >= 0 && coordonates[1] + v.y >= 0 && !placeTaken[coordonates[0] + v.x][coordonates[1] + v.y]) {
				std::shared_ptr<PossiblePlacements> action(new PossiblePlacements(coordonates[0] + v.x, coordonates[1] + v.y));
				possibleActions.push_back(action);
			}
			else
				break;
		}
		for (int i = 1; i < 8; i++) {
			Vector2D v = i * dir[7];
			if (coordonates[0] + v.x >= 0 && coordonates[1] + v.y < 8 && !placeTaken[coordonates[0] + v.x][coordonates[1] + v.y]) {
				std::shared_ptr<PossiblePlacements> action(new PossiblePlacements(coordonates[0] + v.x, coordonates[1] + v.y));
				possibleActions.push_back(action);
			}
			else
				break;
		}
	}
}