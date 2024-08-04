#include <iostream>
#include "SDL.h"
#include "draw.hpp"
#include <SDL_image.h>
#include "gamelogic.hpp"

#define BOARDX 490
#define boardy 150
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

	SDL_Rect winRect;

	SDL_Rect spotRect;

	setRect(&spotRect, NULL, NULL, 200, 200);
	setRect(&winRect, 625, 80, 350, 150);

	//Load assets
	SDL_Surface* xsurface = IMG_Load("images/xtic.png");
	SDL_Surface* osurface = IMG_Load("images/otoe.png");
	SDL_Surface* xwins = IMG_Load("images/xwins.png");
	SDL_Surface* owins = IMG_Load("images/owins.png");

	if (xsurface == NULL)
	{
		std::cout << "Not loaded properly" << std::endl;
	}

	if (osurface == NULL)
	{
		std::cout << "Not loaded properly" << std::endl;
	}

	if (xwins == NULL)
	{
		std::cout << "Not loaded properly" << std::endl;
	}

	if (owins == NULL)
	{
		std::cout << "Not loaded properly" << std::endl;
	}

	//Loads textures
	SDL_Texture* xtexture = SDL_CreateTextureFromSurface(renderer, xsurface);
	SDL_Texture* otexture = SDL_CreateTextureFromSurface(renderer, osurface);
	SDL_Texture* owinstexture = SDL_CreateTextureFromSurface(renderer, owins);
	SDL_Texture* xwinstexture = SDL_CreateTextureFromSurface(renderer, xwins);

	//Create board array
	int boardArr[9] = {};

	//Create mouse cords
	int Mousex = NULL;
	int Mousey = NULL;

	//Tracks the current move
	int currentMove = -1;

	//Tracks current player 
	int player = 1;

	//Notes that play continues
	bool canPlay = true;

	//Initial board y
	int BOARDY = boardy;

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

		if (canPlay)
		currentMove = squareposition(Mousex, Mousey, BOARDX, BOARDY, BOARDSIZE, BOARDSPACE);
		
		//if (currentMove != -1)
		//std::cout << currentMove << std::endl;

		//Puts click into the array

		if (boardFiller(currentMove, boardArr, player))
			player *= -1;

		//Resets important variables
		Mousex = NULL;
		Mousey = NULL;
		currentMove = -1;

		if (winCheck(boardArr) != 0)
		{
			canPlay = false;
			BOARDY = 250;
		}

		//Display stuff

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

		SDL_RenderClear(renderer);

		if (winCheck(boardArr) == 1)
		{
			SDL_RenderCopy(renderer, owinstexture, NULL, &winRect);
		}
		else if (winCheck(boardArr) == -1)
		{
			SDL_RenderCopy(renderer, xwinstexture, NULL, &winRect);
		}

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