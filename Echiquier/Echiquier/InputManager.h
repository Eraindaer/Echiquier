#pragma once
#include "WindowManager.h"

class InputManager
{
public:
	InputManager(std::shared_ptr<WindowManager> window);
	~InputManager();

	bool GetMouseClick();
	int  GetMouseXPos(); 
	int  GetMouseYPos();

private:
	std::shared_ptr<WindowManager> window;
};

