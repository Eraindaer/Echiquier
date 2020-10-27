#include "Board.h"

Board::Board(std::shared_ptr<WindowManager> window) {
	this->window = window;
	player = new PiecesManager(window, 1);
	cpu = new PiecesManager(window, 2);
	this->window->GetTextureManager()->InitTexture("assets/chessBoard.png", this->window->GetRenderer(), tex);
}

Board::~Board() {

}

void Board::Event(InputManager* inputManager) {
	if (player->turn && !cpu->turn)
		player->Event(inputManager);
	else if (cpu->turn && !player->turn)
		cpu->Event(inputManager);
}

void Board::Update(InputManager* inputManager){
	player->SetEnemy(cpu);	
	cpu->SetEnemy(player);
	player->Move(inputManager);
	cpu->Move(inputManager);
}

void Board::DrawPieces() {
	window->GetTextureManager()->DrawTexture(window->GetRenderer(), tex, { 0, 0, 300, 300 }, { 0, 0, 500, 500 });
	player->Draw();
	cpu->Draw();
}