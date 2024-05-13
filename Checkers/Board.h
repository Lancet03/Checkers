#pragma once

#include "CellType.h"
#include "BoardTile.h"
#include "Printer.h"
#include "EmptyCell.h"
#include "Checker.h"

#include <vector>

class Tile;

struct Score {
	int player1 = 0;
	int player2 = 0;
};

class Board
{
private:
	std::vector <std::vector<BoardTile>> tiles{
		{Empty, White, Empty, White, Empty, White, Empty, White},
		{White, Empty, White, Empty, White, Empty, White, Empty},
		{Empty, White, Empty, White, Empty, White, Empty, White},
		{Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty},
		{Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty},
		{Black, Empty, Black, Empty, Black, Empty, Black, Empty},
		{Empty, Black, Empty, Black, Empty, Black, Empty, Black},
		{Black, Empty, Black, Empty, Black, Empty, Black, Empty}
	};


	Printer printer;

	bool isVictory;
	Score score;
	int playerTurn = 1;
	bool jumpExist = false;
	bool continuousJump = false;

	int defaultConsoleColour = 15;
public:
	Board();
	virtual ~Board();

	std::vector <std::vector<Tile*>> cells;
	std::vector <EmptyCell*> emptyCells;
	std::vector <Checker*> checkers;
	
	void Show();
	void SetSell(unsigned int xpos, unsigned int ypos, CellType ct);
	bool CheckLegal(unsigned int xpos, unsigned int ypos);
	bool CheckEndCondition();
	bool IsVictory();

	void PrintCell(int row, int col);

	bool IsValidPlaceToMove(int row, int col);
	void ChangePlayerTurn();
	int CheckIfSomeoneWon();
	void Clear();
	void CheckIfJumpExists();
	bool CheckIfPositionOnBoard(int x, int y);

	void RemoveChecker(Checker* checker);
};

