#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <vector>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Math.hpp"
#include "Map.hpp"
#include "Menu.hpp"

using namespace std;

int checkCpos(Vector2f c_pos, int map[15][24])
{
	int c_row = c_pos.y/32, c_col = c_pos.x/32;
	return map[c_row][c_col];
}

int checkNpos(Vector2f n_pos, int map[15][24])
{
	int n_row = n_pos.y/32, n_col = n_pos.x/32;
	return map[n_row][n_col];
}

int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
	{
		cout << "VIDEO ERROR : " << SDL_GetError() << endl;
	}
	if (!(IMG_Init(IMG_INIT_PNG)))
	{
		cout << "IMG ERROR : " << SDL_GetError() << endl;
	}

	unsigned int width	= 32*24*2, height = 32*15*2;
	RenderWindow window("Game v1.0", width, height);

	vector<char> move;

	const int FPS = 60, frameDelay = 1000/FPS, moveDelay = 500;
	int frameTime, moveTime, moveIndex = 0, lvlIndex = 0;
	Uint32 frameStart, moveStart;
	Vector2f newPos, startPos;
	string lvl[] = {"res/dev/lvl1.txt",
					"res/dev/lvl2.txt",
					"res/dev/lvl3.txt",
					"res/dev/lvl4.txt",
					"res/dev/lvl6.txt"};

	newPos.x = newPos.y = startPos.x = startPos.y = 32;

	SDL_Texture* Robot = window.loadTexture("res/gfx/Box2.png");
	Entity robot(startPos, Robot);
	Map cmap(window);
	Menu mainMenu(window);

	SDL_Texture* tuto = window.loadTexture("res/gfx/Tutorial.png");
	SDL_Rect tuto_src, tuto_dst;
	SDL_QueryTexture(tuto, NULL, NULL, &tuto_src.w, &tuto_src.h);
	tuto_src.x = tuto_src.y = 0; tuto_dst.x = tuto_src.y = 0;
	tuto_dst.w = 32*24*2 ; tuto_dst.h = 32*15*2;

	bool tutoloaded = false;
	bool menuloaded = false;
	bool reloadmenu = true;
	bool gameRunning = true;
	bool maploaded = false;
	bool reloadLvl = false;
	bool firstTimeLoad = false;
	bool clear = false;
	bool newLvl = false;

	SDL_Event event; 

	while(gameRunning)
	{

		frameStart = SDL_GetTicks();

		if(!menuloaded && reloadmenu)
		{
			mainMenu.loadMenu();
			menuloaded = 1;
			reloadmenu = 0;
			cout << "menuloaded" << endl;
		}

		if(!maploaded && reloadLvl)
		{
			cmap.loadMap(lvl[lvlIndex], startPos);
			cout << startPos.x/32 << ' ' << startPos.y/32 << endl;
			newPos = startPos;
			maploaded = 1;
			if(reloadLvl){reloadLvl = 0;}
			if(newLvl){firstTimeLoad = 0; newLvl = 0;}
			cout << "maploaded" << endl;
		}

		int currentType = checkCpos(robot.getPos(), cmap.cmap);


		//EVENT HANDLING START

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				gameRunning = false;
			}
			if(event.type == SDL_KEYDOWN)
			{
				if(maploaded && firstTimeLoad == 1 && currentType == 3)
				{
					if(event.key.keysym.sym == SDLK_UP)
					{
						newPos.y-=32;
						move.push_back('u');
					}
					if(event.key.keysym.sym == SDLK_DOWN)
					{
						newPos.y+=32;
						move.push_back('d');
					}
					if(event.key.keysym.sym == SDLK_LEFT)
					{
						newPos.x-=32;
						move.push_back('l');
					}
					if(event.key.keysym.sym == SDLK_RIGHT)
					{
						newPos.x+=32;
						move.push_back('r');
					}
					if(event.key.keysym.sym == SDLK_ESCAPE)
					{
						maploaded = 0;
						reloadmenu = 1;
					}
					for(int i=0; i<move.size(); i++)
					{
						cout << move[i] << ' ';
					}
					cout << endl;
				}
				if(tutoloaded)
				{
					if(event.key.keysym.sym == SDLK_ESCAPE)
					{
						tutoloaded = 0;
						reloadmenu = 1;
					}
					if(event.key.keysym.sym == SDLK_RETURN)
					{
						tutoloaded = 0;
						reloadLvl = 1;
					}
				}
				if(menuloaded)
				{
					if(event.key.keysym.sym == SDLK_UP)
					{
						mainMenu.index--;
					}
					if(event.key.keysym.sym == SDLK_DOWN)
					{
						mainMenu.index++;
					}
					if(mainMenu.index > 1){mainMenu.index = 0;}
					if(mainMenu.index < 0){mainMenu.index = 2;}
					if(mainMenu.index == 0 && event.key.keysym.sym == SDLK_RETURN){menuloaded = 0; tutoloaded = 1;}
					if(mainMenu.index == 1 && event.key.keysym.sym == SDLK_RETURN){gameRunning = false;}
				}
			}
		}

		if(firstTimeLoad == 1 && (currentType == 3 || currentType == 4 || currentType == 1))
		{
			if(clear == 1 || currentType == 4 || currentType == 1)
			{
				move.clear();
				clear = 0;
				moveIndex = 0;
				moveStart = SDL_GetTicks();
			}
			if(currentType == 1)
			{
				firstTimeLoad = 0;
				maploaded = 0;
				reloadLvl = 1;
			}
			if(currentType == 4)
			{
				if(lvlIndex < 4)
				{
					lvlIndex++;
					newLvl = 1;
					maploaded = 0;
					reloadLvl = 1;
				}
				else
				{
					maploaded = 0;
					reloadmenu = 1;
				}
			}
		}

		if(maploaded)
		{
			if(firstTimeLoad == 1 && currentType == 0)
			{
				moveStart = SDL_GetTicks();

				if(move[moveIndex] == 'u')
				{
					newPos.y-=32;
				}
				if(move[moveIndex] == 'd')
				{
					newPos.y+=32;
				}
				if(move[moveIndex] == 'l')
				{
					newPos.x-=32;
				}
				if(move[moveIndex] == 'r')
				{
					newPos.x+=32;
				}
				moveIndex++;
				if(moveIndex > move.size() - 1){moveIndex = 0;}
				if(clear == 0){clear = 1;}
			}

			moveTime = SDL_GetTicks() - moveStart;

			if(moveDelay > moveTime)
			{
				SDL_Delay(moveDelay - moveTime);
			}
		}

		//EVENT HANDLING END

		window.clear();
  

		// GAME UPDATE START

		int newType = checkNpos(newPos, cmap.cmap);

		if(firstTimeLoad == 1 && newType == 2)
		{
			newPos = robot.getPos();
		}

		//GAME UPDATE END


		//GAME RENDER START

		if(maploaded)
		{
			cmap.drawMap();

			robot.setPos(newPos);
			window.render(robot);
		}

		if(menuloaded)
		{
			mainMenu.drawMenu();
		}

		if(tutoloaded)
		{
			window.draw(tuto,tuto_src,tuto_dst);
		}
		//GAME RENDER END



		frameTime = SDL_GetTicks() - frameStart;

		if(frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}

		window.display();

		if(firstTimeLoad == 0 && (maploaded))
		{
			firstTimeLoad = 1;
		}
	}

	window.cleanUp();
	SDL_Quit();

	return 0;
}