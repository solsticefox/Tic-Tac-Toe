#include "draw.hpp"

void setRect(SDL_Rect* rect, int xcord, int ycord, int width, int height)
{
	rect->x = xcord;
	rect->y = ycord;
	rect->w = width;
	rect->h = height;
}

void drawSolidRect(SDL_Renderer* ren, SDL_Rect* rect, int redness, int greenness, int blueness, int intensity)
{
	SDL_SetRenderDrawColor(ren, redness, greenness, blueness, intensity);
	SDL_RenderFillRect(ren, rect);
}

void drawBoard(SDL_Renderer* ren, SDL_Rect* rect, int squaresize, int squarespace, int squarex, int squarey)
{
	int xpos = squarex;
	int ypos = squarey;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			setRect(rect, xpos, ypos, squaresize, squaresize);
			drawSolidRect(ren, rect, 200, 150, 100, 255);

			ypos += squarespace;

			//std::cout << "Y cord: " << ypos << std::endl;
		}

		xpos += squarespace;
		ypos = squarey;

		//std::cout << "X cord: " << xpos << std::endl;
	}
}

void drawTiles(SDL_Renderer* renderer, SDL_Rect* spotRect, SDL_Texture* otexture, SDL_Texture* xtexture, int boardArr[], int BOARDX, int BOARDY, int BOARDSIZE, int BOARDSPACE)
{
	for (int i = 0; i <= 8; i++)
	{
		switch (i)
		{
		case 0:
			spotRect->x = BOARDX + (BOARDSIZE - 200);
			spotRect->y = BOARDY + (BOARDSIZE - 200);
			break;
		case 1:
			spotRect->x = BOARDX + (2 * BOARDSIZE - 200 + (BOARDSPACE - BOARDSIZE));
			spotRect->y = BOARDY + (BOARDSIZE - 200);
			break;
		case 2:
			spotRect->x = BOARDX + (3 * BOARDSIZE - 200 + 2 * (BOARDSPACE - BOARDSIZE));
			spotRect->y = BOARDY + (BOARDSIZE - 200);
			break;
		case 3:
			spotRect->x = BOARDX + (BOARDSIZE - 200);
			spotRect->y = BOARDY + (2 * BOARDSIZE - 200 + (BOARDSPACE - BOARDSIZE));
			break;
		case 4:
			spotRect->x = BOARDX + (2 * BOARDSIZE - 200 + (BOARDSPACE - BOARDSIZE));
			spotRect->y = BOARDY + (2 * BOARDSIZE - 200 + (BOARDSPACE - BOARDSIZE));
			break;
		case 5:
			spotRect->x = BOARDX + (3 * BOARDSIZE - 200 + 2 * (BOARDSPACE - BOARDSIZE));
			spotRect->y = BOARDY + (2 * BOARDSIZE - 200 + (BOARDSPACE - BOARDSIZE));
			break;
		case 6:
			spotRect->x = BOARDX + (BOARDSIZE - 200);
			spotRect->y = BOARDY + (3 * BOARDSIZE - 200 + 2 * (BOARDSPACE - BOARDSIZE));
			break;
		case 7:
			spotRect->x = BOARDX + (2 * BOARDSIZE - 200 + (BOARDSPACE - BOARDSIZE));
			spotRect->y = BOARDY + (3 * BOARDSIZE - 200 + 2 * (BOARDSPACE - BOARDSIZE));
			break;
		case 8:
			spotRect->x = BOARDX + (3 * BOARDSIZE - 200 + 2 * (BOARDSPACE - BOARDSIZE));
			spotRect->y = BOARDY + (3 * BOARDSIZE - 200 + 2 * (BOARDSPACE - BOARDSIZE));
			break;
		default:
			break;
		}

		if (boardArr[i] == 1)
		{
			SDL_RenderCopy(renderer, otexture, NULL, spotRect);
		}
		else if (boardArr[i] == -1)
		{
			SDL_RenderCopy(renderer, xtexture, NULL, spotRect);
		}
	}
}