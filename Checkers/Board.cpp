#include "Board.h"
#include <Windows.h>
#include <iostream>
#include <typeinfo>
#include "Checker.h"
#include "EmptyCell.h"

Board::Board()
{
	int size = this->tiles.size();

	for (int row = 0; row < this->tiles.size(); row++) {
		std::vector<Tile*> tilesInLine;
		
		for (int col = 0; col < this->tiles.size(); col++) {
			BoardTile tile = this->tiles[row][col];

			if (tile == Empty) {
				EmptyCell* emptyCell = new EmptyCell(row, col, this);
				tilesInLine.push_back(emptyCell);
				this->emptyCells.push_back(emptyCell);
			}
			else {
				Checker* checker = new Checker(row, col, tile, this);
				tilesInLine.push_back(checker);
				this->checkers.push_back(checker);
			}
		}

		this->cells.push_back(tilesInLine);
	}
}

Board::~Board()
{
	for (unsigned int i = 0; i < this->cells.size(); i++)
	{
		for (int j = 0; j < this->cells[i].size(); j++) {
			delete cells[i][j];
		}
	}
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
	Tile* tile = this->cells[row][col];
	

	if (typeid(*tile) == typeid(Checker)) {
		Checker* checker = (Checker*)tile;
		if (checker->player == White) {
			this->printer.PrintWhiteChecker();
			return;
		}
		else if (checker->player == Black) {
			this->printer.PrintBlackChecker();
			return;
		}
		
	}
	else if (typeid(*tile) == typeid(EmptyCell)) {
		if ((tile->position.first + tile->position.second) % 2 == 0) {
			this->printer.PrintWhiteEmptyCell();
		}
		else {
			this->printer.PrintBlackEmptyCell();
		}
	}
}

void Board::SetSell(unsigned int xpos, unsigned int ypos, CellType ct)
{
	// cells[ypos][xpos] = ct;
}

bool Board::CheckLegal(unsigned int xpos, unsigned int ypos)
{
	if ((xpos < 0) || (ypos < 0) || (xpos > this->boardSize - 1) || (ypos > this->boardSize - 1))
	{
		return false;
	}
	return true;
}


bool Board::CheckEndCondition()
{
	/*for (unsigned int i = 0; i < this->boardSize; i++) {
		if (this->IsRowMade(i) || this->IsColumnMade(i)) {
			return true;
		}
	}
	if (this->IsDiagMade() || this->IsBoardFull()) {
		return true;
	}*/

	return false;
}

bool Board::IsVictory() {
	return this->isVictory;
}
