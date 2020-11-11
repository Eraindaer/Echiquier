#include "Pieces.h"

Pieces::Pieces() {
	coordonates[0] = coordonates[1] = 0;
	value = attackingValue = defendingValue = 0;
	isAttacked = isDefended = isCastling = false;
	hasMoved = false;
	selection = false;
	src = { 0,0,0,0 };
	dotSrc = { 0, 0, 31, 31 };
}

Pieces::~Pieces(){}

void Pieces::Draw(SDL_Texture* tex, SDL_Texture* dotTex) {
	window->GetTextureManager()->DrawTexture(window->GetRenderer(), tex, src, { coordonates[0] * (window->GetWindowWidth() / 8), coordonates[1] * (window->GetWindowHeight() / 8) , (window->GetWindowWidth() / 8), (window->GetWindowHeight() / 8) });
	if (selection) {
		for (auto& piece : possibleActions) {
			if (piece != nullptr) {
				window->GetTextureManager()->DrawTexture(window->GetRenderer(), dotTex, dotSrc, { piece->coordonates[0] * (window->GetWindowWidth() / 8) + (window->GetWindowWidth() / 24), piece->coordonates[1] * (window->GetWindowHeight() / 8) + (window->GetWindowHeight() / 24), (window->GetWindowWidth() / 24), (window->GetWindowHeight() / 24) });
			}
		}
	}
}

void Pieces::Move(bool placeTaken[8][8], bool enemyPlaceTaken[8][8], bool placeAttackedByEnemy[8][8], std::vector<std::vector<std::shared_ptr<Pieces>>>& allyPieces, std::vector<std::vector<std::shared_ptr<Pieces>>>& enemyPieces) {
}

void Pieces::SetCoordonates(int x, int y) {
	/*
	if (boolean.enemy->placeTaken[x][y]) {
		boolean.enemy->placeTaken[x][y] = false;
		int iterator = 0;
		for (auto& piece : boolean.enemy->piecesList) {
			if (x == piece->coordonates[0] &&
				y == piece->coordonates[1]) {
				boolean.enemy->piecesList.erase(boolean.enemy->piecesList.begin() + iterator);
				break;
			}
			iterator++;
		}
	}
	boolean.pieces[x][y] = boolean.pieces[coordonates[0]][coordonates[1]];
	boolean.pieces[coordonates[0]][coordonates[1]] = nullptr;
	boolean.placeTaken[coordonates[0]][coordonates[1]] = false, boolean.placeTaken[x][y] = true;
	boolean.selection = false;
	boolean.turn = false, boolean.enemy->turn = true;*/
	if (!hasMoved)
		hasMoved = true;
	this->coordonates[0] = x, this->coordonates[1] = y;
}

void Pieces::SetKing(std::shared_ptr<Pieces> king) {
	this->king = *&king;
}