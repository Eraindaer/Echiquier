#include "PiecesManager.h"

PiecesManager::PiecesManager(std::shared_ptr<WindowManager> window, int player) {
	this->window = window;
	switch (player)
	{
	case 1:
		side = 7;
		direction = -1;
		turn = true;
		break;
	case 2:
		side = 0;
		direction = 1;
		turn = false;
	default:
		break;
	}
	this->window->GetTextureManager()->InitTexture("assets/chess_sprites.png", this->window->GetRenderer(), tex);
	if (player == 1)
		this->window->GetTextureManager()->InitTexture("assets/dot.png", this->window->GetRenderer(), dotTex);
	else
		this->window->GetTextureManager()->InitTexture("assets/black_dot.png", this->window->GetRenderer(), dotTex);
	actionSelected = false;

	
	for (int i = 0; i < 8; i++) {			
		std::vector<std::shared_ptr<Pieces>> line;
		for (int j = 0; j < 8; j++) {
			if (j == side + direction) {
				std::shared_ptr<Pieces> piece(new Pawn(this->window, i, j));
				piecesList.push_back(piece);
				line.push_back(piece);
				placeTaken[i][j] = true;
			}
			else if (j == side) {
				if (i == 0 || i == 7) {
					std::shared_ptr<Pieces> piece(new Rook(this->window, i, j));
					piecesList.push_back(piece);
					line.push_back(piece);
					rooks.push_back(piece);
				}
				else if (i == 1 || i == 6) {
					std::shared_ptr<Pieces> piece(new Knight(this->window, i, j));
					piecesList.push_back(piece);
					line.push_back(piece);
				}
				else if (i == 2 || i == 5) {
					std::shared_ptr<Pieces> piece(new Bishop(this->window, i, j));
					piecesList.push_back(piece);
					line.push_back(piece);
				}
				else if (i == 3) {
					std::shared_ptr<Pieces> piece(new Queen(this->window, i, j));
					piecesList.push_back(piece);
					line.push_back(piece);
				}
				else {
					line.push_back(nullptr);
				}
				placeTaken[i][j] = true;
			}
			else {
				line.push_back(nullptr);
				placeTaken[i][j] = false;
			}
		}
		pieces.push_back(line);
	}
	std::shared_ptr<Pieces> piece(new King(this->window, 4, side, rooks[0], rooks[1]));
	king = *&piece;
	pieces[side][4] = king;
	piecesList.push_back(king);
}

PiecesManager::~PiecesManager() {
	pieces.clear();
}

void PiecesManager::Event(InputManager* mouse) {
	if (!actionSelected && mouse->GetMouseClick()) {
		for (auto& piece : piecesList) {
			
			if (mouse->GetMouseXPos() == piece->coordonates[0] &&
				mouse->GetMouseYPos() == piece->coordonates[1]) {
				piece->selection = true;
			}
			else {
				piece->selection = false;
			}
		}
	}

}

void PiecesManager::Move(InputManager* mouse) {		
	for (auto& piece : piecesList) {
			piece->Move(placeTaken, *this);
			if (piece->selection) {
				for (auto& action : piece->possibleActions) {
					if (mouse->GetMouseXPos() == action->coordonates[0] &&
						mouse->GetMouseYPos() == action->coordonates[1]) {	

						actionSelected = true;
						if (mouse->GetMouseClick()) {
						piece->SetCoordonates(action->coordonates[0], action->coordonates[1], *this);

						piece->possibleActions.clear();
						piece->selection = false;
						actionSelected = false;
						break;
					}
				}
			}
		}
	}
}

void PiecesManager::Draw() {
	for (auto& piece : piecesList) {
		piece->Draw(tex, dotTex);
	}
}

void PiecesManager::SetEnemy(Pieces* enemy) {
	this->enemy = *&enemy;
}