#pragma once
#include "Board.h"
#include <string>
#include "BoardTile.h"

class Player
{
	Board* board;
	BoardTile cellType;
	std::string name;
public:
	Player();
	virtual ~Player();
	void SetupPlayer(std::string name, BoardTile cellType);
	void SetBoard(Board* board);
	bool MakeMove();
	std::string GetName();
};

