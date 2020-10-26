#pragma once
#include "Pieces.h"
class King :
    public Pieces
{
public:
    King(std::shared_ptr<WindowManager> window, int x, int y);
    King(std::shared_ptr<WindowManager> window, int coordonates[2]);
    ~King();

    void Move(bool placeTaken[8][8]) override;

public:
    bool hasMoved;
};

