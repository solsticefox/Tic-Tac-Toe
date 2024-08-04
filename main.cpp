#include <iostream>
#include "SDL.h"
#include "draw.hpp"
#include <SDL_image.h>
#include "gamelogic.hpp"

#define BOARDX 480
#define BOARDY 100
#define BOARDSPACE 210
#define BOARDSIZE 200

int main(int argc, char* argv[])
{
	SDL_Window* window;
	window = SDL_CreateWindow("TicTacToe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1600, 900, NULL);
	bool gameRunning = true;

	SDL_Event event;

	SDL_Renderer* renderer;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_Rect RECTANGLE;

	SDL_Rect xRect;
	SDL_Rect oRect;

	SDL_Rect spotRect;

	setRect(&xRect, 0, 0, 200, 200);
	setRect(&oRect, 200, 200, 200, 200);

	setRect(&spotRect, NULL, NULL, 200, 200);

	//Load assets
	SDL_Surface* xsurface = IMG_Load("images/xtic.png");
	SDL_Surface* osurface = IMG_Load("images/otoe.png");

	if (xsurface == NULL)
	{
		std::cout << "Not loaded properly" << std::endl;
	}

	if (osurface == NULL)
	{
		std::cout << "Not loaded properly" << std::endl;
	}

	//Loads textures
	SDL_Texture* xtexture = SDL_CreateTextureFromSurface(renderer, xsurface);
	SDL_Texture* otexture = SDL_CreateTextureFromSurface(renderer, osurface);

	//Create board array
	int boardArr[9] = {};

	//Create mouse cords
	int Mousex = NULL;
	int Mousey = NULL;

	//Tracks the current move
	int currentMove = -1;

	//Tracks current player 
	int player = 1;

	while (gameRunning)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				gameRunning = false;
			}
			else if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					Mousex = event.button.x;
					Mousey = event.button.y;
				}
			}
		}

		//Update/Game events

		currentMove = squareposition(Mousex, Mousey, BOARDX, BOARDY, BOARDSIZE, BOARDSPACE);
		
		if (currentMove != -1)
		std::cout << currentMove << std::endl;

		//Puts click into the array

		if (boardFiller(currentMove, boardArr, player))
			player *= -1;

		//Resets important variables
		Mousex = NULL;
		Mousey = NULL;
		currentMove = -1;

		if (winCheck(boardArr) != 0)
			std::cout << winCheck(boardArr) << " wins!!\n";

		//Display stuff

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

		SDL_RenderClear(renderer);

		drawBoard(renderer, &RECTANGLE, BOARDSIZE, BOARDSPACE, BOARDX, BOARDY);

		drawTiles(renderer, &spotRect, otexture, xtexture, boardArr, BOARDX, BOARDY, BOARDSIZE, BOARDSPACE);

		SDL_RenderPresent(renderer);

	}

	//Destroy everything
	SDL_FreeSurface(xsurface);
	SDL_DestroyTexture(xtexture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}