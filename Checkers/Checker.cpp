#include "Checker.h"


Checker::Checker(int row, int col, int player) {
	this->position.first = row;
	this->position.second = col;

	this->player = player;
}