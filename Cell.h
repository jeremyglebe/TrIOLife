#pragma once
#include <utility>
#include "Termio.h"

class Cell
{
    using CellIList = std::initializer_list<Cell *>;

public:
    Cell();
    Cell(CellIList neighbors);
    void check();
    bool isStable();
    void kill();
    void next();
    void print(bool simple = true);
    void setNeighbors(CellIList neighbors);
    void spawn();

private:
    // A cell is either alive or dead
    bool alive;
    // A dead cell that is spawning will become alive upon calling next()
    bool spawning;
    // A living cell that is dying will become dead upon calling next()
    bool dying;
    // A cell is stable when it is not changing status
    bool stable;
    // A Cell has an array of pointers to cells which are considered its
    // neighbors. A cell should have 8 neighbors.
    Cell **neighbors;
};