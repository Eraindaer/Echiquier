#include "Player.h"

Player::Player(std::shared_ptr<WindowManager> window, int player) {
	pieces = new PiecesManager(window, player);
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			actionBoard[i][j] = false;
	pieceSelected = nullptr;
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
	if (inputManager->GetMouseClick()) {
		if (pieceSelected != nullptr && actionBoard[inputManager->GetMouseXPos()][inputManager->GetMouseYPos()]) {
			for (auto& action : pieceSelected->possibleActions) {
				if (action != nullptr && inputManager->GetMouseXPos() == action->coordonates[0] && inputManager->GetMouseYPos() == action->coordonates[1]) {
					actionSelected = *&action;
					break;
				}
			}
		}
		else if (!actionBoard[inputManager->GetMouseXPos()][inputManager->GetMouseYPos()]) {
			pieces->actionList.clear();
			if (pieceSelected != nullptr)
				pieceSelected->selection = false;
			pieceSelected = *&pieces->pieces[inputManager->GetMouseXPos()][inputManager->GetMouseYPos()];
			for (int i = 0; i < 8; i++)
				for (int j = 0; j < 8; j++)
					actionBoard[i][j] = false;
			if (pieceSelected != nullptr)
				for (auto& action : pieceSelected->possibleActions) {
					pieces->actionList.push_back(action);
					if (action != nullptr)
						actionBoard[action->coordonates[0]][action->coordonates[1]] = true;
				}
		}
	}
	
	if (pieceSelected != nullptr)
		pieceSelected->selection = true;

 }

 void Player::Move(InputManager* inputManager, std::vector<std::shared_ptr<Pieces>>& piecesMoved, std::vector<std::shared_ptr<PossiblePlacements>>& actionsDone) {
	 if (pieceSelected != nullptr && actionSelected != nullptr) {
		 pieces->Move(pieceSelected, actionSelected);
		 pieceSelected->selection = false;
		 for (int i = 0; i < 8; i++)
			 for (int j = 0; j < 8; j++)
				 actionBoard[i][j] = false;
		 pieceSelected->Move(pieces->placeTaken, pieces->enemy->placeTaken, pieces->enemy->placeAttacked, pieces->pieces, pieces->enemy->pieces);
		 pieceSelected = nullptr, actionSelected = nullptr;
	 }
	 if (pieces->enemy->CheckMate()) {
		 pieces->turn = false;
		 pieces->enemy->turn = false;
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