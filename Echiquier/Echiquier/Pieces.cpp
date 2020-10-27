#include "Pieces.h"

Pieces::Pieces() {
	coordonates[0] = coordonates[1] = 0;
	isAttacked = false;
	hasMoved = false;
	selection = false;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			placeTaken[i][j] = false;
	src = { 0,0,0,0 };
	dotSrc = { 0, 0, 31, 31 };
	direction = side = 0;
}

Pieces::~Pieces(){}

void Pieces::Draw(SDL_Texture* tex, SDL_Texture* dotTex) {
	window->GetTextureManager()->DrawTexture(window->GetRenderer(), tex, src, {coordonates[0] * 62, coordonates[1] * 62, 62, 62 });
	if (selection) {
		for (auto& piece : possibleActions) {
			window->GetTextureManager()->DrawTexture(window->GetRenderer(), dotTex, dotSrc, { piece->coordonates[0] * 62+23, piece->coordonates[1] * 62+25, 20, 20 });
		}
	}
}

void Pieces::Move(bool placeTaken[8][8], Pieces& enemy) {
}

void Pieces::SetCoordonates(int x, int y, Pieces& boolean) {
	if (!hasMoved)
		hasMoved = true;
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
	this->coordonates[0] = x, this->coordonates[1] = y;
	boolean.selection = false;
	boolean.turn = false, boolean.enemy->turn = true;
}
void Pieces::SetDirection(int direction){
	this->direction = direction;
}
