#pragma once

#pragma once
#include "CellType.h"
#include "BoardTile.h"
#include "Printer.h"

#include <vector>

struct Point {
	int x;
	int y;
};

class Board
{
private:
	int boardSize;
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
	CellType** cells;
	Printer printer;
	bool isVictory;
	bool IsRowMade(unsigned int row);
	bool IsColumnMade(unsigned int col);
	bool IsDiagMade();
	bool IsBoardFull();

	int defaultConsoleColour = 15;
public:
	Board(unsigned int size);
	virtual ~Board();
	void Show();
	void SetSell(unsigned int xpos, unsigned int ypos, CellType ct);
	bool CheckLegal(unsigned int xpos, unsigned int ypos);
	bool CheckEndCondition();
	bool IsVictory();

	void PrintCell(int row, int col);
};

