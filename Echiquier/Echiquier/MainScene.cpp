#include "MainScene.h"

MainScene::MainScene(std::shared_ptr<WindowManager> window) {
	this->window = window;
	frameStart = frameTime = 0;
	soundManager->InitMusic("assets/", music);

	inputManager = new InputManager(window);
	chessBoard = new Board(window);
}

MainScene::~MainScene() {
}

void MainScene::Events() {
	frameStart = SDL_GetTicks();
	window->FrameEvents();
	chessBoard->Event(inputManager);
}

void MainScene::Update() {
	chessBoard->Update(inputManager);	
	if (chessBoard->Restart()) {
		chessBoard = nullptr;
		delete(chessBoard);
		chessBoard = new Board(window);
	}
}

void MainScene::Draw() {
	SDL_RenderClear(window->GetRenderer());
	chessBoard->DrawPieces();
	SDL_RenderPresent(window->GetRenderer());
}

void MainScene::SoundEffects() {
	soundManager->PlayMusic(music);
}

void MainScene::Delay() {
	frameTime = SDL_GetTicks() - frameStart;
	if (frameTime < FRAMEDELAY) {
		SDL_Delay(FRAMEDELAY - frameTime);
	}
}

void MainScene::Clear() {
	SDL_Quit();
}