#pragma once
#include <iostream>

int squareposition(int MX, int MY, int boardx, int boardy, int boardsize, int boardspace);

bool boardFiller(int cPosition, int board[], int player);

int winCheck(int board[]);