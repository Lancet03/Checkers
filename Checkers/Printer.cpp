#include "Printer.h"
#include <iostream>

Printer::Printer() {
	this->hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}

void Printer::PrintWhiteChecker() {
	SetConsoleTextAttribute(hConsole, CellType_WhiteChecker);
	std::cout << "()";
	SetConsoleTextAttribute(hConsole, defaultConsoleColor);
}

void Printer::PrintBlackChecker() {
	SetConsoleTextAttribute(hConsole, CellType_BlackChecker);
	std::cout << "()";
	SetConsoleTextAttribute(hConsole, defaultConsoleColor);
}

void Printer::PrintWhiteKingChecker() {

}

void Printer::PrintWhiteEmptyCell() {
	SetConsoleTextAttribute(hConsole, CellType_White);
	std::cout << "  ";
	SetConsoleTextAttribute(hConsole, defaultConsoleColor);
}

void Printer::PrintBlackEmptyCell() {
	SetConsoleTextAttribute(hConsole, CellType_Black);
	std::cout << "  ";
	SetConsoleTextAttribute(hConsole, defaultConsoleColor);
}