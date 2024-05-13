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
	this->printer.PrintTilesInfo();

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
	/*if ((xpos < 0) || (ypos < 0) || (xpos > this->boardSize - 1) || (ypos > this->boardSize - 1))
	{
		return false;
	}*/
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

int Board::CheckIfSomeoneWon() {
	if (this->score.player1 == 12) {
		return 1;
	}
	else if (this->score.player2) {
		return 2;
	}

	return 0;
}

bool Board::IsValidPlaceToMove(int row, int col) {
	if (!this->CheckIfPositionOnBoard(col, row)) return false;

	Tile* tile = this->cells[row][col];
	if (typeid(*tile) == typeid(EmptyCell)) return true;

	return false;
}

bool Board::CheckIfPositionOnBoard(int x, int y) {
	int boardYSize = this->cells.size();
	int boardXSize = this->cells[0].size();
	if (y > (boardYSize - 1) || x > (boardYSize - 1) || y < 0 || x < 0) {
		return false;
	}
	return true;
}

void Board::RemoveChecker(Checker* checker) {
	if (checker->player == 1) {
		this->score.player2 += 1;
	}
	if (checker->player == 2) {
		this->score.player1 += 1;
	}

	int checkerCol = checker->position.first;
	int checkerRow = checker->position.second;
	EmptyCell* emptyCell = new EmptyCell(checkerRow, checkerCol, this);
	this->cells[checkerRow][checkerCol] = emptyCell;
	
	for (int i = 0; i < this->checkers.size(); i++) {
		if (checker == this->checkers[i]) {
			if (i == 0) {
				this->checkers.erase(this->checkers.begin());
			} else {
				this->checkers.erase(std::next(this->checkers.begin(), i));
			}
			break;
		}
	}
	this->emptyCells.push_back(emptyCell);

	int playerWon = this->CheckIfSomeoneWon();
	if (playerWon) {
		std::cout << "Player " << playerWon << " won!!!" << std::endl;
	}
}


void Board::CheckIfJumpExists() {
	this->jumpExist = false;
	this->continuousJump = false;
}