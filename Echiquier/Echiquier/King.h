#pragma once
#include "Pieces.h"
class King :
    public Pieces
{
public:
    King(std::shared_ptr<WindowManager> window, int x, int y, std::shared_ptr<Pieces>& rook1, std::shared_ptr<Pieces> rook2);
    King(std::shared_ptr<WindowManager> window, int coordonates[2], std::shared_ptr<Pieces>& rook1, std::shared_ptr<Pieces> rook2);
    ~King();

    void Move(bool placeTaken[8][8], Pieces& piecesManager) override;
    void SetCoordonates(int x, int y, Pieces& boolean) override;

public:
    Vector2D dir[8];
    std::shared_ptr<Pieces> rook1;
    std::shared_ptr<Pieces> rook2;
};

