#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "RenderWindow.hpp"
#include "Math.hpp"
#include "Button.hpp"
#include "Menu.hpp"

using namespace std;

Menu::Menu(RenderWindow p_window)
:index(0), window(p_window)
{}

void Menu::loadMenu()
{
	start_tex = window.loadTexture("res/gfx/Start Button.png");
	setting_tex = window.loadTexture("res/gfx/Settings Button.png");
	exit_tex = window.loadTexture("res/gfx/Exit Button.png");

	start_col_tex = window.loadTexture("res/gfx/Col Start Button.png");
	setting_col_tex = window.loadTexture("res/gfx/Col Settings Button.png");
	exit_col_tex = window.loadTexture("res/gfx/Col Exit Button.png");

	bg = window.loadTexture("res/gfx/Background.png");

	SDL_QueryTexture(bg, NULL, NULL, &bg_src.w, &bg_src.h);
	bg_src.x = bg_src.y = 0; bg_dst.x = bg_src.y = 0;
	bg_dst.w = 32*24*2 ; bg_dst.h = 32*15*2;
}

void Menu::drawMenu()
{
	Button start(-200, 50, window);
	Button setting(0, 50, window);
	Button exit(200, 50, window);
	
	window.draw(bg, bg_src, bg_dst);

	if(index == 0){start.drawButton(start_col_tex);}
	else{start.drawButton(start_tex);}
	if(index == 1){setting.drawButton(setting_col_tex);}
	else{setting.drawButton(setting_tex);}
	if(index == 2){exit.drawButton(exit_col_tex);}
	else{exit.drawButton(exit_tex);}
}