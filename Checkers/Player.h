#pragma once
#include "Board.h"
#include <string>
#include "BoardTile.h"

class Player
{
	Board* board;
	std::string name;
public:
	BoardTile cellType;
	Player();
	virtual ~Player();
	void SetupPlayer(std::string name, BoardTile cellType);
	void SetBoard(Board* board);
	bool MakeMove();
	std::string GetName();
};

