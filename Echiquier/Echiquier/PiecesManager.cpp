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
	std::shared_ptr<Pieces> kingPiece(new King(this->window, 4, side, rooks[0], rooks[1]));
	pieces[4][side] = *&kingPiece;
	piecesList.push_back(*&kingPiece);
	king = *&kingPiece;

	for (auto& piece : piecesList) {
		piece->SetKing(kingPiece);
	}
}

PiecesManager::~PiecesManager() {
	pieces.clear();
}

//void PiecesManager::Event() {
	/*if (!actionSelected && mouse->GetMouseClick()) {
		for (auto& piece : piecesList) {
			
			if (mouse->GetMouseXPos() == piece->coordonates[0] &&
				mouse->GetMouseYPos() == piece->coordonates[1]) {
				piece->selection = true;
				for (auto& action : piece->possibleActions) {
					actionList.push_back(action);
				}
			}
			else {
				piece->selection = false;
				actionList.clear();
			}
		}
	}
	*/

void PiecesManager::Move(std::shared_ptr<Pieces> pieceToMove, std::shared_ptr<PossiblePlacements> newPosition) {
	if (enemy->placeTaken[newPosition->coordonates[0]][newPosition->coordonates[1]]) {
		enemy->placeTaken[newPosition->coordonates[0]][newPosition->coordonates[1]] = false;
		int iterator = 0;
		for (auto& piece : enemy->piecesList) {
			if (newPosition->coordonates[0] == piece->coordonates[0] &&
				newPosition->coordonates[1] == piece->coordonates[1]) {
				enemy->piecesList.erase(enemy->piecesList.begin() + iterator);
				break;	
			}
			iterator++;	
		}	
	}
	pieces[newPosition->coordonates[0]][newPosition->coordonates[1]] = pieces[pieceToMove->coordonates[0]][pieceToMove->coordonates[1]];
	pieces[pieceToMove->coordonates[0]][pieceToMove->coordonates[1]] = nullptr;
	placeTaken[pieceToMove->coordonates[0]][pieceToMove->coordonates[1]] = false, placeTaken[newPosition->coordonates[0]][newPosition->coordonates[1]] = true;
	pieceToMove->SetCoordonates(newPosition->coordonates[0], newPosition->coordonates[1]);
	turn = false, enemy->turn = true;
	pieceToMove->possibleActions.clear();
}

void PiecesManager::Draw() {
	for (auto& piece : piecesList) {
		piece->Draw(tex, dotTex);
	}
}

void PiecesManager::SetEnemy(PiecesManager* enemy) {
	this->enemy = *&enemy;
	enemyKing = *&enemy->piecesList[0]->king;
}

bool PiecesManager::WillKingBeEndangered(std::shared_ptr<Pieces> currentPiece, std::shared_ptr<PossiblePlacements> eventualAction) {
	/*int iterator = 0;
	for (auto& piece : piecesList) {
		int actionIterator = 0;
		predictionPieces.push_back(piecesList[iterator]);
		for (auto& action : piece->possibleActions) {
			for (int i = 0; i < 8; i++)
				for (int j = 0; j < 8; j++)
					predictionPlaces[i][j] = placeTaken[i][j];
			predictionPieces[iterator]->SetCoordonates(action->coordonates[0], action->coordonates[1]);
			predictionPlaces[piece->coordonates[0]][piece->coordonates[1]] = false, predictionPlaces[action->coordonates[0]][action->coordonates[1]] = true;
			for (auto& enemyPiece : enemy->piecesList) {
				for (auto& enemyAction : enemyPiece->possibleActions) {
					if (predictionPieces[iterator]->king->coordonates[0] == enemyAction->coordonates[0] && predictionPieces[iterator]->king->coordonates[1] == enemyAction->coordonates[1]) {
						predictionPieces[iterator]->king->isAttacked = true;
						break;
					}
				}
				if (predictionPieces[iterator]->king->isAttacked)
					break;
			}
			if (predictionPieces[iterator]->king->isAttacked) {
				piece->possibleActions.erase(piece->possibleActions.begin() + actionIterator);
				break;
			}
			actionIterator++;
		}
		iterator++;
	}*/
	
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++) {
			predictionPlaces[i][j] = placeTaken[i][j];
			predictionEnemyPlaces[i][j] = enemy->placeTaken[i][j];
		}
	predictionPlaces[currentPiece->coordonates[0]][currentPiece->coordonates[1]] = false, predictionPlaces[eventualAction->coordonates[0]][eventualAction->coordonates[1]] = true;
	predictionPieces = pieces;
	predictionPieces[currentPiece->coordonates[0]][currentPiece->coordonates[1]] = nullptr, predictionPieces[eventualAction->coordonates[0]][eventualAction->coordonates[1]] = currentPiece;
	predictionKing = piecesList[0]->king;
	predictionKing->isAttacked = false;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (predictionPieces[i][j] != nullptr) {
				predictionPieces[i][j]->SetKing(predictionKing);
			}
		}
	}
	predictionEnemyPiecesList = enemy->piecesList;
	predictionEnemyPieces = enemy->pieces;
	if (predictionEnemyPlaces[eventualAction->coordonates[0]][eventualAction->coordonates[1]]) {
		predictionEnemyPieces[eventualAction->coordonates[0]][eventualAction->coordonates[1]] = nullptr;
		predictionEnemyPlaces[eventualAction->coordonates[0]][eventualAction->coordonates[1]] = false;
		int iterator = 0;
		for (auto& piece : predictionEnemyPiecesList) {
			if (eventualAction->coordonates[0] == piece->coordonates[0] && eventualAction->coordonates[1] == piece->coordonates[1]) {
				predictionEnemyPiecesList.erase(predictionEnemyPiecesList.begin() + iterator);
				break;
			}
			iterator++;
		}
	}

	for (auto& enemyPiece : predictionEnemyPiecesList) {
		enemyPiece->Move(predictionEnemyPlaces, predictionPlaces, placeAttacked, predictionEnemyPieces, predictionPieces);
	}
	
	
	if (predictionPieces[eventualAction->coordonates[0]][eventualAction->coordonates[1]]->king->isAttacked)
		return true;
	return false;
}

void PiecesManager::CheckAttackedPlace() {
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			placeAttacked[i][j] = false;
	for (auto& piece : piecesList) {
		for (auto& action : piece->possibleActions) {
			placeAttacked[action->coordonates[0]][action->coordonates[1]] = true;
		}
	}
}

bool PiecesManager::CheckMate() {
	int actionPossible = 0;
	for (auto& piece : piecesList) {
		for (auto& action : piece->possibleActions) {
			if (action != nullptr)
				actionPossible++;
		}
	}

	if (actionPossible == 0 && enemy->placeAttacked[king->coordonates[0]][king->coordonates[1]])
		return true;

	return false;
}