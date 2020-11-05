#pragma once
#include "Pieces.h"
class Rook :
    public Pieces
{
public:
    Rook(std::shared_ptr<WindowManager> window, int x, int y);
    Rook(std::shared_ptr<WindowManager> window, int coordonates[2]);
    ~Rook();

    void Move(bool placeTaken[8][8], bool enemyPlaceTaken[8][8], bool placeAttackedByEnemy[8][8], std::vector<std::vector<std::shared_ptr<Pieces>>>& allyPieces, std::vector<std::vector<std::shared_ptr<Pieces>>>& enemyPieces) override;


public:
    Vector2D dir[4];
};

