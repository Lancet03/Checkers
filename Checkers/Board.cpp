#include "Board.h"
#include <iostream>

Board::Board(unsigned int size)
{
	this->boardSize = size;
	cells = new CellType * [size];
	for (unsigned int i = 0; i < size; i++)
	{
		cells[i] = new CellType[size];
	}
	for (unsigned int i = 0; i < size; i++)
	{
		for (unsigned int j = 0; j < size; j++)
		{
			cells[i][j] = CellType_Empty;
		}
	}
}

Board::~Board()
{
	for (unsigned int i = 0; i < this->boardSize; i++)
	{
		delete[]cells[i];
	}
	delete[]cells;
}

void Board::Show()
{
	std::cout << "  ";
	for (unsigned int j = 0; j < this->boardSize; j++) {
		std::cout << j << " ";
	}
	std::cout << std::endl;

	for (unsigned int i = 0; i < this->boardSize; i++)
	{
		std::cout << i << " ";
		for (unsigned int j = 0; j < this->boardSize; j++)
		{
			switch (cells[i][j])
			{
			case CellType_X:
			{
				std::cout << "X";
				break;
			}
			case CellType_O:
			{
				std::cout << "O";
				break;
			}
			case CellType_Empty:
			{
				std::cout << "-";
				break;
			}
			}
			std::cout << " ";

		}
		std::cout << std::endl;
	}
}

void Board::SetSell(unsigned int xpos, unsigned int ypos, CellType ct)
{
	cells[ypos][xpos] = ct;
}

bool Board::CheckLegal(unsigned int xpos, unsigned int ypos)
{
	if ((xpos < 0) || (ypos < 0) || (xpos > this->boardSize - 1) || (ypos > this->boardSize - 1))
	{
		return false;
	}
	return true;
}

bool Board::IsRowMade(unsigned int row)
{
	int numX = 0, numO = 0;
	for (unsigned int i = 0; i < this->boardSize; i++)
	{
		if (this->cells[row][i] == CellType_O)
		{
			numO++;
		}
		if (this->cells[row][i] == CellType_X)
		{
			numX++;
		}
	}

	if ((numX == this->boardSize) || (numO == this->boardSize))
	{
		this->isVictory = true;
		return true;
	}


	return false;
}

bool Board::IsColumnMade(unsigned int col)
{
	int numX = 0, numO = 0;
	for (unsigned int i = 0; i < this->boardSize; i++)
	{
		if (this->cells[i][col] == CellType_O)
		{
			numO++;
		}
		if (this->cells[i][col] == CellType_X)
		{
			numX++;
		}

	}

	if ((numX == this->boardSize) || (numO == this->boardSize)) {
		this->isVictory = true;
		return true;
	}

	return false;
}

bool Board::IsDiagMade()
{
	int numX = 0, numO = 0;
	for (unsigned int i = 0; i < this->boardSize; i++)
	{
		if (this->cells[i][i] == CellType_O)
		{
			numO++;
		}
		if (this->cells[i][i] == CellType_X)
		{
			numX++;
		}

	}

	if ((numX == this->boardSize) || (numO == this->boardSize)) {
		this->isVictory = true;
		return true;
	}

	numX = numO = 0;

	for (unsigned int i = 0; i < this->boardSize; i++)
	{
		if (this->cells[i][this->boardSize - i - 1] == CellType_O)
		{
			numO++;
		}
		if (this->cells[i][this->boardSize - i - 1] == CellType_X)
		{
			numX++;
		}

	}

	if ((numX == this->boardSize) || (numO == this->boardSize)) {
		this->isVictory = true;
		return true;
	}

	return false;
}

bool Board::IsBoardFull()
{
	int numX = 0, numO = 0;
	for (unsigned int i = 0; i < this->boardSize; i++)
	{
		for (unsigned int j = 0; j < this->boardSize; j++) {
			if (this->cells[i][j] == CellType_O)
			{
				numO++;
			}
			if (this->cells[i][j] == CellType_X)
			{
				numX++;
			}
		}
	}

	if ((numX + numO) == (this->boardSize * this->boardSize)) {
		return true;
	}

	return false;
}

bool Board::CheckEndCondition()
{
	for (unsigned int i = 0; i < this->boardSize; i++) {
		if (this->IsRowMade(i) || this->IsColumnMade(i)) {
			return true;
		}
	}
	if (this->IsDiagMade() || this->IsBoardFull()) {
		return true;
	}

	return false;
}

bool Board::IsVictory() {
	return this->isVictory;
}
