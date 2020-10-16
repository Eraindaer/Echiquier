#include "MainScene.h"

MainScene::MainScene(WindowManager* window) {
	this->window = window;
	textureManager = window->GetTextureManager();
	frameStart = frameTime = 0;

	soundManager = new SoundManager();

	soundManager->InitMusic("assets/", music);

	/*
		Initialiser les différents éléments de la scène
	*/
}

MainScene::~MainScene() {
	delete(soundManager);
}

void MainScene::Events() {
	frameStart = SDL_GetTicks();
	window->FrameEvents();
}

void MainScene::Update() {
	/*
		Update des différents éléments de la scène
	*/
}

void MainScene::Draw() {
	SDL_RenderClear(window->GetRenderer());
	/*
		Objets à rendre
	*/
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