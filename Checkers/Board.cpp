#include "Board.h"
#include <Windows.h>
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
			cells[i][j] = CellType_White;
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
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole, CellType_Black);
	std::cout << "  ";
	SetConsoleTextAttribute(hConsole, CellType_White);
	std::cout << "  ";
	SetConsoleTextAttribute(hConsole, CellType_WhiteChecker);
	std::cout << "()";
	SetConsoleTextAttribute(hConsole, CellType_White);
	std::cout << "  ";
	SetConsoleTextAttribute(hConsole, CellType_BlackChecker);
	std::cout << "[]";
	SetConsoleTextAttribute(hConsole, CellType_White);
	std::cout << "  " << std::endl << std::endl;

	SetConsoleTextAttribute(hConsole, defaultConsoleColour);

	int countCheckers = 0;
	int countTiles = 0;

	std::cout << "  ";
	
	char rowId = 'A';
	for (int j = 0; j < this->tiles.size(); j++) {
		std::cout << rowId++ << " ";
	}
	std::cout << std::endl;


	
	for (int row = 0; row < this->tiles.size(); row++)
	{
		std::cout << row + 1 << " ";

		for (int col = 0; col < this->tiles[row].size(); col++) {
			this->PrintCell(row, col);
		}

		std::cout << std::endl;
	}

}

void Board::PrintCell(int row, int col) {
	BoardTile tile = this->tiles[row][col];

	if (tile == White) {
		this->printer.PrintWhiteChecker();
		return;
	}
	else if (tile == Black) {
		this->printer.PrintBlackChecker();
		return;
	}
	else if (tile == Empty) {
		if ((row + col) % 2 == 0) {
			this->printer.PrintWhiteEmptyCell();
		}
		else {
			this->printer.PrintBlackEmptyCell();
		}
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
		if (this->cells[row][i] == CellType_BlackChecker)
		{
			numO++;
		}
		if (this->cells[row][i] == CellType_WhiteChecker)
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
		if (this->cells[i][col] == CellType_BlackChecker)
		{
			numO++;
		}
		if (this->cells[i][col] == CellType_WhiteChecker)
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
		if (this->cells[i][i] == CellType_BlackChecker)
		{
			numO++;
		}
		if (this->cells[i][i] == CellType_WhiteChecker)
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
		if (this->cells[i][this->boardSize - i - 1] == CellType_BlackChecker)
		{
			numO++;
		}
		if (this->cells[i][this->boardSize - i - 1] == CellType_WhiteChecker)
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
			if (this->cells[i][j] == CellType_BlackChecker)
			{
				numO++;
			}
			if (this->cells[i][j] == CellType_WhiteChecker)
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
