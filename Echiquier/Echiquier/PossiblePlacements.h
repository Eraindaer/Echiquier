#pragma once
#include "WindowManager.h"
class PossiblePlacements
{
public:
	PossiblePlacements(int x, int y);
	~PossiblePlacements();

	inline void SetState(bool state) { isDeleted = state; }

public:
	int coordonates[2];
	bool isDeleted;
};

