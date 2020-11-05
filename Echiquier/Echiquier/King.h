#pragma once
#include "Pieces.h"
class King :
    public Pieces
{
public:
    King(std::shared_ptr<WindowManager> window, int x, int y, std::shared_ptr<Pieces>& rook1, std::shared_ptr<Pieces>& rook2);
    King(std::shared_ptr<WindowManager> window, int coordonates[2], std::shared_ptr<Pieces>& rook1, std::shared_ptr<Pieces>& rook2);
    ~King();

    void Move(bool placeTaken[8][8], bool enemyPlaceTaken[8][8], bool placeAttackedByEnemy[8][8], std::vector<std::vector<std::shared_ptr<Pieces>>>& allyPieces, std::vector<std::vector<std::shared_ptr<Pieces>>>& enemyPieces) override;
    void SetCoordonates(int x, int y) override;

public:
    Vector2D dir[8];
    std::shared_ptr<Pieces> rook1;
    std::shared_ptr<Pieces> rook2;
    std::vector<std::vector<std::shared_ptr<Pieces>>> allyPieces;
};

