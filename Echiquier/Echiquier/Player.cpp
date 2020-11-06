#include "Player.h"

Player::Player(std::shared_ptr<WindowManager> window, int player) {
	pieces = new PiecesManager(window, player);
	actionSelected = false;

}

Player::~Player(){}


void Player::Init() {
	for (auto& piece : pieces->piecesList) {
		piece->isAttacked = piece->isDefended = false;
		piece->attackingValue = piece->defendingValue = 0;
		piece->Move(pieces->placeTaken, pieces->enemy->placeTaken, pieces->enemy->placeAttacked, pieces->pieces, pieces->enemy->pieces);
	}
}

void Player::SelectPiece(InputManager* inputManager) {
	if (!actionSelected && inputManager->GetMouseClick()) {
		for (auto& piece : pieces->piecesList) {
			if (inputManager->GetMouseXPos() == piece->coordonates[0] &&
				inputManager->GetMouseYPos() == piece->coordonates[1]) {
				piece->selection = true;
				for (auto& action : piece->possibleActions) {
					pieces->actionList.push_back(action);
				}
			}
			else {
				piece->selection = false;
				pieces->actionList.clear();
			}
		}
	}
}

void Player::Move(InputManager* inputManager) {
	for (auto& piece : pieces->piecesList) {
		if (piece->selection) {
			for (auto& action : piece->possibleActions) {
				if (action != nullptr) {
					if (inputManager->GetMouseXPos() == action->coordonates[0] &&
						inputManager->GetMouseYPos() == action->coordonates[1]) {
						actionSelected = true;
						if (inputManager->GetMouseClick()) {
							pieces->Move(piece, action);
							piece->selection = false;
							actionSelected = false;
							piece->Move(pieces->placeTaken, pieces->enemy->placeTaken, pieces->enemy->placeAttacked, pieces->pieces, pieces->enemy->pieces);
							break;
						}
					}
				}
			}
		}
	}
}

void Player::Update() {
	for (auto& piece : pieces->piecesList) {
		int iterator = 0;
		for (auto& action : piece->possibleActions) {
			if (piece->possibleActions[iterator] != nullptr && pieces->WillKingBeEndangered(piece, action)) {
				piece->possibleActions[iterator] = nullptr;
			}
			iterator++;
		}
	} 
}