#include "Player.h"

Player::Player(std::shared_ptr<WindowManager> window) {
	pieces = new PiecesManager(window);
}