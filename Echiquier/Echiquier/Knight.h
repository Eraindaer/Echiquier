#pragma once
#include "Pieces.h"
class Knight :
    public Pieces
{
public:
    Knight(std::shared_ptr<WindowManager> window, int x, int y);
    Knight(std::shared_ptr<WindowManager> window, int coordonates[2]);
    ~Knight();

    void Move(bool placeTaken[8][8], bool enemyPlaceTaken[8][8], bool placeAttackedByEnemy[8][8], std::vector<std::vector<std::shared_ptr<Pieces>>>& allyPieces, std::vector<std::vector<std::shared_ptr<Pieces>>>& enemyPieces) override;

public:
    Vector2D dir[8];
};

