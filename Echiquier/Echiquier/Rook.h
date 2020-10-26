#pragma once
#include "Pieces.h"
class Rook :
    public Pieces
{
public:
    Rook(std::shared_ptr<WindowManager> window, int x, int y);
    Rook(std::shared_ptr<WindowManager> window, int coordonates[2]);
    ~Rook();

    void Move(bool placeTaken[8][8]) override;

public:
    bool hasMoved;
    Vector2D dir1, dir2, dir3, dir4;
};

