#include "Board.h"

Board::Board(std::shared_ptr<WindowManager> window) {
	this->window = window;
	player = new Player(window, 1);
	//player = new Computer(window, 1);
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
	/*else if (cpu->GetTurn() && !player->GetTurn())
		cpu->SelectPiece(inputManager);*/
}

void Board::Update(InputManager* inputManager){
	player->Init();
	cpu->Init();
	player->pieces->CheckAttackedPlace();
	cpu->pieces->CheckAttackedPlace();
	if (player->GetTurn() && !cpu->GetTurn()){
		player->Update();
		player->Move(inputManager, piecesMoved, actionsDone);
		/*player->Prediction(DEPTHTWO);
		player->Move(DEPTHTWO);
		piecesMoved.push_back(player->pieceToMove);
		actionsDone.push_back(player->action);
		player->predictionTree->ClearTree(player->predictionNode);*/
	}
	else if (!player->GetTurn() && cpu->GetTurn()) {		
		
		cpu->Update();
		//cpu->Move(inputManager, piecesMoved, actionsDone);
		cpu->Prediction(DEPTH);
		cpu->Move(DEPTH);
		piecesMoved.push_back(cpu->pieceToMove);
		actionsDone.push_back(cpu->action);
		cpu->predictionTree->ClearTree(cpu->predictionNode);
	}

}

void Board::DrawPieces() {
	window->GetTextureManager()->DrawTexture(window->GetRenderer(), tex, { 0, 0, 200, 200 }, { 0, 0, window->GetWindowWidth(), window->GetWindowHeight() });
	if (player->GetTurn()) {
		cpu->pieces->Draw();
		player->pieces->Draw();
	}
	else if (cpu->GetTurn()) {
		player->pieces->Draw();
		cpu->pieces->Draw();
	}
}