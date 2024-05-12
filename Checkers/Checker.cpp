#include "Checker.h"
#include "Board.h"

Checker::Checker(int row, int col, int player, Board* board) {
	this->position.first = row;
	this->position.second = col;

	this->player = player;
	this->board = board;
}