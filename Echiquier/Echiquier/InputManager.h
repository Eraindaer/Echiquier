#pragma once
#include "WindowManager.h"

class InputManager
{
public:
	InputManager(std::shared_ptr<WindowManager> window);
	~InputManager();

	bool GetMouseClick();
	inline int  GetMouseXPos() { return window->GetEvent().button.x / 62; }
	inline int  GetMouseYPos() { return window->GetEvent().button.y / 62; }

private:
	std::shared_ptr<WindowManager> window;
};

