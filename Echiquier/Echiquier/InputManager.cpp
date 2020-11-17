#include "InputManager.h"

InputManager::InputManager(std::shared_ptr<WindowManager> window) {
	this->window = window;
}

InputManager::~InputManager(){}

bool InputManager::GetMouseClick() {
	SDL_Delay(10);
	if (window->GetEvent().type == SDL_MOUSEBUTTONDOWN) {
		if (window->GetEvent().button.button == SDL_BUTTON_LEFT)
			return true;
	}
	return false;
}

int InputManager::GetMouseXPos() {
	return window->GetEvent().button.x / (window->GetWindowWidth() / 8);
}

int InputManager::GetMouseYPos() {
	return window->GetEvent().button.y / (window->GetWindowHeight() / 8);
}