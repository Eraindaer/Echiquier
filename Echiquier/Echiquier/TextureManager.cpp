#include "TextureManager.h"

TextureManager::TextureManager() {}

TextureManager::~TextureManager(){}

void TextureManager::InitTexture(const char* path, SDL_Renderer* renderer, SDL_Texture*& tex) {
	SDL_Surface* tempSurface = IMG_Load(path);
	tex = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
}

void TextureManager::InitFont(const char* path, TTF_Font*& font) {
	TTF_Init();
	font = TTF_OpenFont(path, 25);
}

void TextureManager::InitText(const char* text, SDL_Renderer* renderer, TTF_Font* font, SDL_Texture*& fontTex, SDL_Rect& dest) {
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, { 0, 0, 0 });
	fontTex = SDL_CreateTextureFromSurface(renderer, textSurface);
	if (textSurface != nullptr)
		dest.w = textSurface->w, dest.h = textSurface->h;
	SDL_FreeSurface(textSurface);
}

void TextureManager::DrawTexture(SDL_Renderer* renderer, SDL_Texture* tex, SDL_Rect src, SDL_Rect dest) {
	SDL_RenderCopy(renderer, tex, &src, &dest);
}

void TextureManager::DrawCharacters(SDL_Renderer* renderer, SDL_Texture* text, SDL_Rect dest) {
	SDL_RenderCopy(renderer, text, NULL, &dest);
}