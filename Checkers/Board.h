#pragma once

#pragma once
#include "CellType.h"

class Board
{
private:
	int boardSize;
	CellType** cells;
	bool isVictory;
	bool IsRowMade(unsigned int row);
	bool IsColumnMade(unsigned int col);
	bool IsDiagMade();
	bool IsBoardFull();
public:
	Board(unsigned int size);
	virtual ~Board();
	void Show();
	void SetSell(unsigned int xpos, unsigned int ypos, CellType ct);
	bool CheckLegal(unsigned int xpos, unsigned int ypos);
	bool CheckEndCondition();
	bool IsVictory();
};

