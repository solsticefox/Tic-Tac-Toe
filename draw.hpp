#pragma once

#include <SDL.h>

void setRect(SDL_Rect* rect, int xcord, int ycord, int width, int height);

void drawSolidRect(SDL_Renderer* ren, SDL_Rect* rect, int redness, int greenness, int blueness, int intensity = 255);

void drawBoard(SDL_Renderer* ren, SDL_Rect* rect, int squaresize, int squarespace, int squarex, int squarey);

void drawTiles(SDL_Renderer* renderer, SDL_Rect* spotRect, SDL_Texture* otexture, SDL_Texture* xtexture, int boardArr[], int BOARDX, int BOARDY, int BOARDSIZE, int BOARDSPACE);