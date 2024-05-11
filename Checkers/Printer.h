#pragma once
#include <Windows.h>
#include "CellType.h"

class Printer
{
private:
	HANDLE hConsole;
	int defaultConsoleColor = 15;
	void PrintCell(const char* cellText, CellType cellType);
public:
	Printer();
	void PrintWhiteChecker();
	void PrintBlackChecker();
	void PrintWhiteEmptyCell();
	void PrintWhiteKingChecker();
	void PrintBlackEmptyCell();
	void PrintBlackKingChecker();
};

