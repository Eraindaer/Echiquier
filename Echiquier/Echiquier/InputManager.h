#pragma once
#include "WindowManager.h"

class InputManager
{
public:
	InputManager(std::shared_ptr<WindowManager> window);
	~InputManager();

	bool GetMouseClick();
	bool GetButtonPressed(bool f(SDL_KeyCode, std::shared_ptr<WindowManager>), SDL_KeyCode button);
	int  GetMouseXPos(); 
	int  GetMouseYPos();

private:
	std::shared_ptr<WindowManager> window;
};

