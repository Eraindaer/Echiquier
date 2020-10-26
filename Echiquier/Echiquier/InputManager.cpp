#include "InputManager.h"

InputManager::InputManager(std::shared_ptr<WindowManager> window) {
	this->window = window;
}

InputManager::~InputManager(){}

bool InputManager::GetMouseClick() {
	if (window->GetEvent().type == SDL_MOUSEBUTTONDOWN) {
		if (window->GetEvent().button.button == SDL_BUTTON_LEFT)
			return true;
	}
	return false;
}