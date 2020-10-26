#pragma once
#include "Pieces.h"
class Bishop :
    public Pieces
{
public:
    Bishop(std::shared_ptr<WindowManager>window, int x, int y);
    Bishop(std::shared_ptr<WindowManager> window, int coordonates[2]);
    ~Bishop();

    void Move(bool placeTaken[8][8]) override;

public:
    Vector2D dir1, dir2, dir3, dir4;
};

