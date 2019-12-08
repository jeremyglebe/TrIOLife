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
    void spawn();
    void kill();
    void next();
    void print();
    void setNeighbors(CellIList neighbors);

private:
    bool alive;
    bool spawning;
    bool dying;
    Cell **neighbors;
};