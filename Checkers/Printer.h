#pragma once
#include <Windows.h>
#include "CellType.h"

class Printer
{
private:
	HANDLE hConsole;
	int defaultConsoleColor = 15;
public:
	Printer();
	void PrintWhiteChecker();
	void PrintBlackChecker();
	void PrintWhiteKingChecker();
	void PrintWhiteEmptyCell();
	void PrintBlackEmptyCell();
};

