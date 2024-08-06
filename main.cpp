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

	SDL_Rect resetRect;

	SDL_Rect loadingRect;

	SDL_Rect playRect;

	setRect(&resetRect, 50, 50, 175, 75);
	setRect(&spotRect, NULL, NULL, 200, 200);
	setRect(&winRect, 625, 80, 350, 150);
	setRect(&loadingRect, 0, 0, 1600, 900);
	setRect(&playRect, 255, 680, 500, 150);

	//Load assets
	SDL_Surface* xsurface = IMG_Load("images/xtic.png");
	SDL_Surface* osurface = IMG_Load("images/otoe.png");
	SDL_Surface* xwins = IMG_Load("images/xwins.png");
	SDL_Surface* owins = IMG_Load("images/owins.png");
	SDL_Surface* reset = IMG_Load("images/reset.png");
	SDL_Surface* tie = IMG_Load("images/tie.png");
	SDL_Surface* loadingScreen = IMG_Load("images/loadingscreen.png");
	SDL_Surface* playButton = IMG_Load("images/playbutton.png");

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

	if (reset == NULL)
	{
		std::cout << "Not loaded properly" << std::endl;
	}

	if (tie == NULL)
	{
		std::cout << "Not loaded properly" << std::endl;
	}

	if (loadingScreen == NULL)
	{
		std::cout << "Not loaded properly" << std::endl;
	}

	if (playButton == NULL)
	{
		std::cout << "Not loaded properly" << std::endl;
	}

	//Loads textures
	SDL_Texture* xtexture = SDL_CreateTextureFromSurface(renderer, xsurface);
	SDL_Texture* otexture = SDL_CreateTextureFromSurface(renderer, osurface);
	SDL_Texture* owinstexture = SDL_CreateTextureFromSurface(renderer, owins);
	SDL_Texture* xwinstexture = SDL_CreateTextureFromSurface(renderer, xwins);
	SDL_Texture* resetTexture = SDL_CreateTextureFromSurface(renderer, reset);
	SDL_Texture* tietexture = SDL_CreateTextureFromSurface(renderer, tie);
	SDL_Texture* loadingScreenTexture = SDL_CreateTextureFromSurface(renderer, loadingScreen);
	SDL_Texture* playButtonTexture = SDL_CreateTextureFromSurface(renderer, playButton);

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

	//Game state
	int gameState = 0;

	//Buffer variable
	int buffer = 0;

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


		if (gameState == 0)
		{
			SDL_RenderCopy(renderer, loadingScreenTexture, NULL, &loadingRect);
			SDL_RenderCopy(renderer, playButtonTexture, NULL, &playRect);

			if (Mousex > 255 && Mousex < 755 && Mousey > 680 && Mousey < 830)
			{
				gameState = 1;
				buffer = 1;
			}
		}


		if (gameState == 1)
		{//Update/Game events

			if (buffer == 1)
			{
				Mousex = NULL;
				Mousey = NULL;
				buffer = 0;
			}

			if (canPlay)
				currentMove = squareposition(Mousex, Mousey, BOARDX, BOARDY, BOARDSIZE, BOARDSPACE);

			//if (currentMove != -1)
			//std::cout << currentMove << std::endl;

			if (Mousex > 50 && Mousex < 225 && Mousey > 50 && Mousey < 125)
			{
				for (int i = 0; i < 9; i++)
				{
					boardArr[i] = 0;
				}

				BOARDY = 150;

				canPlay = true;
			}

			//Puts click into the array

			if (boardFiller(currentMove, boardArr, player))
				player *= -1;

			//Resets important variables
			
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
			else if (winCheck(boardArr) == 2)
			{
				SDL_RenderCopy(renderer, tietexture, NULL, &winRect);
			}

			SDL_RenderCopy(renderer, resetTexture, NULL, &resetRect);

			drawBoard(renderer, &RECTANGLE, BOARDSIZE, BOARDSPACE, BOARDX, BOARDY);

			drawTiles(renderer, &spotRect, otexture, xtexture, boardArr, BOARDX, BOARDY, BOARDSIZE, BOARDSPACE);
		}

		Mousex = NULL;
		Mousey = NULL;

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