#pragma once
#include "Player.h"

class RandomPlayer : public Player {
public:
	RandomPlayer();
	virtual ~RandomPlayer();
	virtual bool MakeMove();
};