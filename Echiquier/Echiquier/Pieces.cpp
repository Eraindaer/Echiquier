#include "Pieces.h"

Pieces::Pieces() {
	coordonates[0] = coordonates[1] = 0;
	selection = false;
	src = { 0,0,0,0 };
}

Pieces::~Pieces(){}

void Pieces::Draw(SDL_Texture* tex) {
	window->GetTextureManager()->DrawTexture(window->GetRenderer(), tex, src, {coordonates[0] * 62, coordonates[1] * 62, 62, 62 });
	if (selection) {
		for (auto& piece : possibleActions) {
			window->GetTextureManager()->DrawTexture(window->GetRenderer(), tex, src, { piece->coordonates[0] * 62, piece->coordonates[1] * 62, 62, 62 });
		}
	}
}

void Pieces::Move(bool placeTaken[8][8]) {
}

void Pieces::SetCoordonates(int x, int y) {
	this->coordonates[0] = x, this->coordonates[1] = y;
}