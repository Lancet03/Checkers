#pragma once
#include "Board.h"
#include <string>
#include "BoardTile.h"
#include "Checker.h"

class Player
{
	Board* board;
	std::string name;
	Checker* SelectChecker();
	bool SelectWhereCheckerWillGo(Checker* selectedChecker);
public:
	BoardTile cellType;
	Player();
	virtual ~Player();
	void SetupPlayer(std::string name, BoardTile cellType);
	void SetBoard(Board* board);
	bool MakeMove();
	std::string GetName();
};

