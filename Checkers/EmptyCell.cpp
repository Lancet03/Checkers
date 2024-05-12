#include "EmptyCell.h"

EmptyCell::EmptyCell(int row, int col, Board* board) {
	this->position.first = row;
	this->position.second = col;
	this->board = board;
}
