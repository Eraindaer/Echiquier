#pragma once
#include "Pieces.h"
class Bishop :
    public Pieces
{
public:
    Bishop(std::shared_ptr<WindowManager>window, int x, int y);
    Bishop(std::shared_ptr<WindowManager> window, int coordonates[2]);
    ~Bishop();

    void Move(bool placeTaken[8][8], bool enemyPlaceTaken[8][8], bool placeAttackedByEnemy[8][8], std::vector<std::vector<std::shared_ptr<Pieces>>>& allyPieces, std::vector<std::vector<std::shared_ptr<Pieces>>>& enemyPiecess) override;

public:
    Vector2D dir[4];
};

