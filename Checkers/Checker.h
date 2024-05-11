#pragma once
#include "Tile.h"
#include "BoardTile.h"

class Checker :
    public Tile
{
    bool allowedToMove = true;
    bool king = false;
public:
    int player;
    Checker(int row, int col, int player);
    void MakeKing();
    bool Move(int x, int y);
    bool CanJumpAny();
    bool CanOpponentJump(int x, int y);
    bool OpponentJump(int x, int y);
    bool Remove();
};

