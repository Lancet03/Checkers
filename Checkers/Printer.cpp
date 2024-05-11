#include "Printer.h"
#include <iostream>

Printer::Printer() {
	this->hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}

void Printer::PrintWhiteChecker() {
	this->PrintCell("()", CellType_WhiteChecker);
}

void Printer::PrintWhiteKingChecker() {
	this->PrintCell("[]", CellType_WhiteChecker);
}

void Printer::PrintBlackChecker() {
	this->PrintCell("()", CellType_BlackChecker);
}

void Printer::PrintBlackKingChecker() {
	this->PrintCell("()", CellType_BlackChecker);
}

void Printer::PrintWhiteEmptyCell() {
	this->PrintCell("  ", CellType_White);
}

void Printer::PrintBlackEmptyCell() {
	this->PrintCell("  ", CellType_Black);
}

void Printer::PrintCell(const char* cellText, CellType cellType) {
	SetConsoleTextAttribute(hConsole, cellType);
	std::cout << cellText;
	SetConsoleTextAttribute(hConsole, defaultConsoleColor);
}
