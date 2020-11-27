#include "Board.h"

Board::Board(std::shared_ptr<WindowManager> window) {
	this->window = window;
	player = new Player(window, 1);
	//player = new Computer(window, 1);
	//cpu = new Player(window, 2);
	cpu = new Computer(window, 2);
	this->window->GetTextureManager()->InitTexture("assets/chessBoard.png", this->window->GetRenderer(), tex);
	this->window->GetTextureManager()->InitTexture("assets/finish.png", this->window->GetRenderer(), finishTex);
	this->window->GetTextureManager()->InitText("CHECKMATE !", this->window->GetRenderer(), this->window->GetFont(), checkMateText, destCheckMate);
	this->window->GetTextureManager()->InitText("PLAYER       WINS", this->window->GetRenderer(), this->window->GetFont(), playerWinText, destText1);
	this->window->GetTextureManager()->InitText("COMPUTER        WINS", this->window->GetRenderer(), this->window->GetFont(), computerWinText, destText2);
	this->window->GetTextureManager()->InitText("PRESS    F1    TO      RESTART", this->window->GetRenderer(), this->window->GetFont(), restartText, destRestartText);
	this->window->GetTextureManager()->InitText("PRESS    ESCAPE    TO    EXIT", this->window->GetRenderer(), this->window->GetFont(), exitText, destExitText);
	destCheckMate.x = (this->window->GetWindowWidth() - destCheckMate.w) / 2, destCheckMate.y = (this->window->GetWindowHeight() - 160) / 2 + 30;
	destText1.x = (this->window->GetWindowHeight() - destText1.w) / 2, destText1.y = destCheckMate.y + 25;
	destText2.x = (this->window->GetWindowHeight() - destText2.w) / 2, destText2.y = destText1.y;
	destRestartText.x = (this->window->GetWindowHeight() - destRestartText.w) / 2, destRestartText.y = destText2.y + 40;
	destExitText.x = destRestartText.x, destExitText.y = destRestartText.y + 20;
	player->pieces->SetEnemy(cpu->pieces);	
	cpu->pieces->SetEnemy(player->pieces);

	restart = false;
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
	/*if (player->GetKing()->isAttacked)
		std::cout << "Roi du joueur attaqué \n";
	else
		std::cout << "Roi du joueur non attaqué \n";

	if (cpu->GetKing()->isAttacked)
		std::cout << "Roi de l'ordinateur attaqué \n";
	else
		std::cout << "Roi de l'ordinateur non attaqué \n";*/


	if (player->GetTurn() || cpu->GetTurn()) {
		player->Init();
		cpu->Init();
		player->pieces->CheckAttackedPlace();
		cpu->pieces->CheckAttackedPlace();
		if (player->GetTurn() && !cpu->GetTurn()) {
			player->Update();
			if (CheckMate()) {
				player->pieces->turn = cpu->pieces->turn = false;
			}
			else {
				player->Move(inputManager, piecesMoved, actionsDone);
				/*player->Prediction(DEPTHTWO);
				player->Move(DEPTHTWO);
				piecesMoved.push_back(player->pieceToMove);
				actionsDone.push_back(player->action);
				player->predictionTree->ClearTree(player->predictionNode);*/
			}
		}
		else if (!player->GetTurn() && cpu->GetTurn()) {

			cpu->Update();
			if (CheckMate()) {
				player->pieces->turn = cpu->pieces->turn = false;
			}
			else {
				//cpu->Move(inputManager, piecesMoved, actionsDone);
				cpu->Prediction(DEPTH);
				cpu->Move(DEPTH);
				piecesMoved.push_back(cpu->pieceToMove);
				actionsDone.push_back(cpu->action);
				cpu->predictionTree->ClearTree(cpu->predictionNode);
			}
		}
	}
	else {
		if (inputManager->GetButtonPressed([](SDL_KeyCode button, std::shared_ptr<WindowManager> window)
			{ if (window->GetEvent().type == SDL_KEYDOWN && window->GetEvent().key.keysym.sym == button) { return true; } return false; }, SDLK_F1)) {
				restart = true;
		}
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
	else {
		player->pieces->Draw();
		cpu->pieces->Draw();
		window->GetTextureManager()->DrawTexture(window->GetRenderer(), finishTex, { 0, 0, 200, 80 }, { (window->GetWindowWidth() - 400) / 2, (window->GetWindowHeight() - 160) / 2, 400, 160 });
		window->GetTextureManager()->DrawCharacters(window->GetRenderer(), checkMateText, destCheckMate);
		if (player->pieces->CheckMate()) {
			window->GetTextureManager()->DrawCharacters(window->GetRenderer(), computerWinText, destText2);
		}
		else if (cpu->pieces->CheckMate()) {
			window->GetTextureManager()->DrawCharacters(window->GetRenderer(), playerWinText, destText1);
		}
		window->GetTextureManager()->DrawCharacters(window->GetRenderer(), restartText, destRestartText);
		window->GetTextureManager()->DrawCharacters(window->GetRenderer(), exitText, destExitText);
	}
}