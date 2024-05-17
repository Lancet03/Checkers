#pragma once
#include <string>
#include "Tile.h"
#include "BoardTile.h"

class Checker :
    public Tile
{
public:
    bool allowedToMove = true;
    bool selected = false;
    bool king = false;
    int player;
    Checker(int row, int col, int player, Board* board);
    void MakeKing();
    bool Move(int x, int y);
    bool CanJumpAny();
    Checker* CanOpponentJump(int x, int y);
    bool OpponentJump(int x, int y);
    void Remove();

    std::string GetTextPosition();
};

