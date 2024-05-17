#include <Windows.h>
#include <iostream>
#include <typeinfo>
#include <string>

#include "Board.h"
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
			if (checker->king) {
				this->printer.PrintWhiteKingChecker();
			}
			else {
				this->printer.PrintWhiteChecker();
			}

			return;
		}
		else if (checker->player == Black) {
			if (checker->king) {
				this->printer.PrintBlackKingChecker();
			}
			else {
				this->printer.PrintBlackChecker();
			}
			
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

Checker* Board::GetChecker(int x, int y) {
	if (this->CheckIfPositionOnBoard(x, y) && this->CheckIfCheckerOnPosition(x, y)) {
		Checker* checker = (Checker*)this->cells[y][x];

		return checker;
	}

	return nullptr;
}

EmptyCell* Board::GetEmptyCell(int x, int y) {
	if (this->CheckIfPositionOnBoard(x, y)) {
		EmptyCell* emptyCell = (EmptyCell*)this->cells[y][x];

		return emptyCell;
	}

	return nullptr;
}


bool Board::CheckLegal(int xpos, int ypos)
{
	return this->CheckIfPositionOnBoard(xpos, ypos);
}


bool Board::CheckEndCondition()
{
	if (this->CheckIfSomeoneWon() != 0) {
		return true;
	}

	return false;
}

bool Board::IsVictory() {
	return this->isVictory;
}

int Board::CheckIfSomeoneWon() {
	if (this->score.player1 == 12) {
		return 1;
	}
	else if (this->score.player2 == 12) {
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

	if (y > (boardYSize - 1) || x > (boardXSize - 1) || y < 0 || x < 0) {
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
			}
			else {
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
	for (int i = 0; i < this->checkers.size(); i++) {
		Checker* checker = this->checkers[i];
		checker->allowedToMove = false;
		if (checker->player == this->playerTurn && checker->CanJumpAny()) {
			this->jumpExist = true;
			checker->allowedToMove = true;
		}
	}

	if (!this->jumpExist) {
		for (int i = 0; i < this->checkers.size(); i++) {
			this->checkers[i]->allowedToMove = true;
		}
	}
}

bool Board::CheckIfCheckerOnPosition(int x, int y) {
	if (this->CheckIfPositionOnBoard(x, y)) {
		Tile* possibleChecker = this->cells[y][x];

		if (typeid(*possibleChecker) == typeid(Checker)) {
			return true;
		}
	}

	return false;
}

bool Board::CheckIfEmptyCellOnPosition(int x, int y) {
	if (this->CheckIfPositionOnBoard(x, y)) {
		Tile* possibleEmptyCell = this->cells[y][x];

		if (typeid(*possibleEmptyCell) == typeid(EmptyCell)) {
			return true;
		}
	}

	return false;
}

bool Board::CheckIfPositionIsCorrect(std::string position) {
	if (position.length() != 2) {
		std::cout << "Введена слишком длинная строка" << std::endl;
		return false;
	}

	std::pair<int, int> coords = this->ParsePosition(position);

	if (!this->CheckIfPositionOnBoard(coords.first, coords.second)) {
		std::cout << "Координата была введена неверно!" << std::endl;
		return false;
	}

	return true;
}

std::pair<int, int> Board::ParsePosition(std::string position) {
	std::pair<int, int> coords;
	coords.first = position[0] - 'A';
	coords.second = position[1] - '1';

	return coords;
}

void Board::ChangePlayerTurn() {
	if (this->playerTurn == 1) {
		this->playerTurn = 2;
	}
	else {
		this->playerTurn = 1;
	}
	this->CheckIfJumpExists();
}

bool Board::CheckIfPlayerHasSelectedCheckers() {
	for (int i = 0; i < this->checkers.size(); i++) {
		Checker* checker = this->checkers[i];
		if (checker->player == this->playerTurn && checker->selected) {
			return true;
		}
	}
	
	return false;
}
Checker* Board::GetSelectedChecker() {
	for (int i = 0; i < this->checkers.size(); i++) {
		Checker* checker = this->checkers[i];
		if (checker->player == this->playerTurn && checker->selected) {
			return checker;
		}
	}

	return nullptr;
}

void Board::DeselectAllCheckers() {
	for (int i = 0; i < this->checkers.size(); i++) {
		Checker* checker = this->checkers[i];
		checker->selected = false;
	}
}