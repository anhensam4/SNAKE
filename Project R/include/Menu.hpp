#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "RenderWindow.hpp"
#include "Math.hpp"
#include "Button.hpp"

using namespace std;

class Menu
{
public:
	Menu(RenderWindow p_window);
	void loadMenu();
	void drawMenu();
	int index;

private:
	RenderWindow window;
	SDL_Texture* start_tex;
	SDL_Texture* exit_tex;

	SDL_Texture* start_col_tex;
	SDL_Texture* exit_col_tex;

	SDL_Texture* bg;

	SDL_Rect bg_src, bg_dst;
};