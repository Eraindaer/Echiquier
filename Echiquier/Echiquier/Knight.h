#pragma once
#include "Pieces.h"
class Knight :
    public Pieces
{
public:
    Knight(std::shared_ptr<WindowManager> window, int x, int y);
    Knight(std::shared_ptr<WindowManager> window, int coordonates[2]);
    ~Knight();

    void Move(bool placeTaken[8][8]) override;
};

