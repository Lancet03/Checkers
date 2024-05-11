#pragma once
#include "Tile.h"
#include "Checker.h"

class EmptyCell :
    public Tile
{
public:
    EmptyCell(int row, int col);
    int inRange(Checker checker);
};

