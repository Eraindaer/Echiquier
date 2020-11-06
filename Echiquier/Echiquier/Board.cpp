#include "Board.h"

Board::Board(std::shared_ptr<WindowManager> window) {
	this->window = window;
	player = new Player(window, 1);
	//cpu = new Player(window, 2);
	cpu = new Computer(window, 2);
	this->window->GetTextureManager()->InitTexture("assets/chessBoard.png", this->window->GetRenderer(), tex);
	player->pieces->SetEnemy(cpu->pieces);	
	cpu->pieces->SetEnemy(player->pieces);
}

Board::~Board() {

}

void Board::Event(InputManager* inputManager) {
	if (player->GetTurn() && !cpu->GetTurn())
		player->SelectPiece(inputManager);
	//else if (cpu->GetTurn() && !player->GetTurn())
		//cpu->SelectPiece(inputManager);
}

void Board::Update(InputManager* inputManager){
	player->Init();
	cpu->Init();
	player->pieces->CheckAttackedPlace();
	cpu->pieces->CheckAttackedPlace();
	if (player->GetTurn() && !cpu->GetTurn()){
		player->Update();
		player->Move(inputManager);
	}
	else if (!player->GetTurn() && cpu->GetTurn()) {
		cpu->Update();
		cpu->Prediction(2);
		cpu->Move(2);
		cpu->predictionTree->ClearTree(cpu->predictionNode);
		//cpu->Move(inputManager);
	}

	bool test1 = player->pieces->CheckMate();
	bool test2 = cpu->pieces->CheckMate();
}

void Board::DrawPieces() {
	window->GetTextureManager()->DrawTexture(window->GetRenderer(), tex, { 0, 0, 200, 200 }, { 0, 0, window->GetWindowWidth(), window->GetWindowHeight() });
	player->pieces->Draw();
	cpu->pieces->Draw();
}