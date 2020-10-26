#include "PiecesManager.h"

PiecesManager::PiecesManager(std::shared_ptr<WindowManager> window) {
	this->window = window;
	this->window->GetTextureManager()->InitTexture("assets/chess_sprites.png", this->window->GetRenderer(), tex);
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (j == 6) {
				std::shared_ptr<Pieces> piece(new Pawn(this->window, i, j));
				pieces.push_back(piece);
				placeTaken[i][j] = true;
			}
			else if (j == 7) {
				if (i == 0 || i == 7) {
					std::shared_ptr<Pieces> piece(new Rook(this->window, i, j));
					pieces.push_back(piece);
				}
				else if (i == 1 || i == 6) {
					std::shared_ptr<Pieces> piece(new Knight(this->window, i, j));
					pieces.push_back(piece);
				}
				else if (i == 2 || i == 5) {
					std::shared_ptr<Pieces> piece(new Bishop(this->window, i, j));
					pieces.push_back(piece);
				}
				else if (i == 3) {
					std::shared_ptr<Pieces> piece(new Queen(this->window, i, j));
					pieces.push_back(piece);
				}
				else {
					std::shared_ptr<Pieces> piece(new King(this->window, i, j));
					pieces.push_back(piece);
				}
				placeTaken[i][j] = true;
			}
			else {
				placeTaken[i][j] = false;
			}
		}
	}
}
PiecesManager::~PiecesManager() {
	pieces.clear();
}

void PiecesManager::Event(InputManager* mouse) {
	if (mouse->GetMouseClick()) {
		for (auto& piece : pieces) {
			
			if (mouse->GetMouseXPos() == piece->coordonates[0] &&
				mouse->GetMouseYPos() == piece->coordonates[1]) {
				piece->selection = true;
			}
		}
	}

}

void PiecesManager::Move(InputManager* mouse) {		

		for (auto& piece : pieces) {
			piece->Move(placeTaken);
			if (piece->selection) {
				for (auto& action : piece->possibleActions) {
					if (mouse->GetMouseClick()) {
					if (mouse->GetMouseXPos() == action->coordonates[0] &&
						mouse->GetMouseYPos() == action->coordonates[1]) {
						placeTaken[piece->coordonates[0]][piece->coordonates[1]] = false;
						piece->SetCoordonates(action->coordonates[0], action->coordonates[1]);
						placeTaken[piece->coordonates[0]][piece->coordonates[1]] = true;
						piece->possibleActions.clear();
						piece->selection = false;
						break;
					}
				}
			}
		}
	}
}

void PiecesManager::Draw() {
	for (auto& piece : pieces) {
		piece->Draw(tex);
	}
}