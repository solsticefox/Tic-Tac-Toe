#include "gamelogic.hpp"

int squareposition(int MX, int MY, int boardx, int boardy, int boardsize, int boardspace)
{

	int column = NULL;
	int row = NULL;
	int position = -1;
	int primeposition = NULL;
	if (MX > boardx && MX < (boardx + boardsize))
	{
		column = 1;
	}
	else if (MX > (boardx + boardspace) && MX < (boardx + boardspace + boardsize))
	{
		column = 2;
	}
	else if (MX > (boardx + 2 * boardspace) && MX < (boardx + 2 * boardspace + boardsize))
	{
		column = 3;
	}

	if (column != 0)
		//std::cout << column << std::endl;

	//Check row
	if (MY > boardy && MY < (boardy + boardsize))
	{
		row = 5;
	}
	else if (MY > (boardy + boardspace) && MY < (boardy + boardspace + boardsize))
	{
		row = 7;
	}
	else if (MY > (boardy + 2 * boardspace) && MY < (boardy + 2 * boardspace + boardsize))
	{
		row = 11;
	}

	if (row != 0)
		//std::cout << row << std::endl;

	primeposition = column * row;

	switch (primeposition)
	{
	case 5:
		position = 0;
		break;
	case 10:
		position = 1;
		break;
	case 15:
		position = 2;
		break;
	case 7:
		position = 3;
		break;
	case 14:
		position = 4;
		break;
	case 21:
		position = 5;
		break;
	case 11:
		position = 6;
		break;
	case 22:
		position = 7;
		break;
	case 33:
		position = 8;
		break;
	default:
		break;
	}

	return position;
}

bool boardFiller(int cPosition, int board[], int player)
{
	bool successfulFill = false;
	if (cPosition != -1)
	{
		if (board[cPosition] == 0)
		{
			board[cPosition] = player;
			successfulFill = true;
		}
		else
		{
			std::cout << "Spot number " << cPosition + 1 << " is taken by player " << player << std::endl;
		}
	}

	return successfulFill;
}