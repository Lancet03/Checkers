#pragma once
#include <utility>

class Board;

class Tile
{
protected:
	Board* board;
public:
	Tile() {};
	virtual ~Tile() {};
	std::pair<int, int> position;
};

