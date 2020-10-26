#include "PossiblePlacements.h"

PossiblePlacements::PossiblePlacements(int x, int y) {
	coordonates[0] = x, coordonates[1] = y;
	src = { 0, 0, 35, 35 };
	this->window = window;
}

PossiblePlacements::~PossiblePlacements(){}