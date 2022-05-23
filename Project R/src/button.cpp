#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "RenderWindow.hpp"
#include "Math.hpp"
#include "Button.hpp"

using namespace std;

Button::Button(int y, int scale, RenderWindow p_window)
:window(p_window), scale(scale)
{
	src.w = 600; src.h = 200;
	src.x = src.y = 0;
	dst.w = src.w*scale/100; dst.h = src.h*scale/100;
	dst.x = 32*24-dst.w/2; dst.y = 32*15-dst.h/2+y;
}

void Button::drawButton(SDL_Texture* &b_tex)
{
	window.draw(b_tex, src, dst);
}