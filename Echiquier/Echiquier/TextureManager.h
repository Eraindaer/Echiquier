#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
class TextureManager
{
public:
	TextureManager();
	~TextureManager();

	void InitTexture(const char* path, SDL_Renderer* renderer, SDL_Texture* &tex);
	void InitFont(const char* path, TTF_Font*& font);
	void InitText(const char* text, SDL_Renderer* renderer, TTF_Font* font, SDL_Texture*& fontTex, SDL_Rect& dest);
	void DrawTexture(SDL_Renderer* renderer, SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);
	void DrawCharacters(SDL_Renderer* renderer, SDL_Texture* text, SDL_Rect dest);
};

