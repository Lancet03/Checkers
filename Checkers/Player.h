#pragma once
#include "Board.h"
#include <string>

class Player
{
	Board* board;
	CellType cellType;
	std::string name;
public:
	Player();
	virtual ~Player();
	void SetupPlayer(std::string name, CellType cellType);
	void SetBoard(Board* board);
	bool MakeMove();
	std::string GetName();
};

