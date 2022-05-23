#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "RenderWindow.hpp"
#include "Math.hpp"

using namespace std;

class Button
{
public:
	Button(int y, int scale, RenderWindow p_window);
	void drawButton(SDL_Texture* &b_tex);
private:
	SDL_Rect src, dst;
	RenderWindow window;
	int scale;
};