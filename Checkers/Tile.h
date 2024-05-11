#pragma once
#include <utility>

class Tile
{
public:
	Tile() {};
	virtual ~Tile() {};
	std::pair<int, int> position;
};

