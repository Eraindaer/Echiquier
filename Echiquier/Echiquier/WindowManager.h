#pragma once
#include "TextureManager.h"
#include <memory>
class WindowManager
{
public:
	WindowManager(const char* title, int xPos, int yPos, int width, int height, SDL_Color color);
	~WindowManager();

	void								   FrameEvents();

	inline void                            SetRunState(bool state) { isRunning = state; }
	inline bool							   GetRunState() { return isRunning;}
	inline SDL_Event					   GetEvent() { return event; }
	inline SDL_Window*					   GetWindow() { return window; }
	inline SDL_Renderer*				   GetRenderer() { return windowRenderer; }
	inline TTF_Font*					   GetFont() { return font; }
	inline std::shared_ptr<TextureManager> GetTextureManager() { return textureManager; }
	inline int                             GetWindowWidth() { return width; }
	inline int                             GetWindowHeight() { return height; }

private:
	int                                    width;
	int                                    height;
	bool							       isRunning;
	SDL_Event							   event;
	SDL_Window*							   window;
	SDL_Renderer*						   windowRenderer;
	TTF_Font*							   font;
	std::shared_ptr<TextureManager>		   textureManager;
};