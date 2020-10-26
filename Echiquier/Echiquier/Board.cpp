#include "Board.h"

Board::Board(std::shared_ptr<WindowManager> window) {
	this->window = window;
	player = new Player(window);
	this->window->GetTextureManager()->InitTexture("assets/chessBoard.png", this->window->GetRenderer(), tex);
}

Board::~Board() {

}

void Board::LoadPieces(){}

void Board::DrawPieces() {
	window->GetTextureManager()->DrawTexture(window->GetRenderer(), tex, { 0, 0, 300, 300 }, { 0, 0, 500, 500 });
	player->pieces->Draw();
}