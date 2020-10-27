#pragma once
#include "Pieces.h"
class Queen :
    public Pieces
{
public:
    Queen(std::shared_ptr<WindowManager> window, int x, int y);
    Queen(std::shared_ptr<WindowManager> window, int coordonates[2]);
    ~Queen();

    void Move(bool placeTaken[8][8], Pieces& piecesManager) override;

public:
    Vector2D dir[8];
};

