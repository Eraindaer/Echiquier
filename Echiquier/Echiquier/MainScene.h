#pragma once
#include "WindowManager.h"
#include "SoundManager.h"
#include "InputManager.h"
#include "Board.h"
#define FPS 60
#define FRAMEDELAY (1000/FPS)
class MainScene
{
public:
	MainScene(std::shared_ptr<WindowManager> window);
	~MainScene();

	void			                Events();
	void			                Update();
	void			                Draw();
	void                            SoundEffects();
	void			                Delay();

	void			                Clear();

private:
	Mix_Music* music;
	Uint32			                frameStart;
	int				                frameTime;
	std::shared_ptr<WindowManager>  window;
	std::shared_ptr<SoundManager>   soundManager;
	Board*							chessBoard;
	InputManager*                   inputManager;

};