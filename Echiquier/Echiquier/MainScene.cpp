#include "MainScene.h"

MainScene::MainScene(WindowManager* window) {
	this->window = window;
	textureManager = window->GetTextureManager();
	frameStart = frameTime = 0;

	soundManager = new SoundManager();

	soundManager->InitMusic("assets/", music);

	/*
		Initialiser les diff�rents �l�ments de la sc�ne
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
		Update des diff�rents �l�ments de la sc�ne
	*/
}

void MainScene::Draw() {
	SDL_RenderClear(window->GetRenderer());
	/*
		Objets � rendre
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