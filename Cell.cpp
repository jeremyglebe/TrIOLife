#include "Cell.h"

Cell::Cell()
{
    // Initialize data
    this->neighbors = NULL;
    this->alive = false;
    this->spawning = false;
    this->dying = false;
}

Cell::Cell(CellIList neighbors)
{
    // Initialize data
    this->alive = false;
    this->spawning = false;
    this->dying = false;
    // Setup neighbors
    setNeighbors(neighbors);
}

void Cell::check()
{
    // Count the number of live neighbors (of 8 total)
    int live_neighbors = 0;
    for (int i = 0; i < 8; i++)
    {
        if (neighbors[i]->alive)
        {
            live_neighbors++;
        }
    }
    // Cell with fewer than two live neighbours dies (exposure)
    if (alive && live_neighbors < 2)
    {
        kill();
    }
    // Cell with more than three live neighbours dies (overcrowding)
    if (alive && live_neighbors > 3)
    {
        kill();
    }
    // Dead cell with exactly three live neighbours will come to life.
    if (!alive && live_neighbors == 3)
    {
        spawn();
    }
    // Cell with two or three live neighbours lives, unchanged
    return;
}

void Cell::spawn()
{
    if (!alive)
    {
        spawning = true;
    }
}

void Cell::kill()
{
    if (alive)
    {
        dying = true;
    }
}

void Cell::next()
{
    if (alive && dying)
    {
        spawning = false;
        dying = false;
        alive = false;
    }
    else if (!alive && spawning)
    {
        spawning = false;
        dying = false;
        alive = true;
    }
}

void Cell::print()
{
    Term::IO io;
    if (spawning)
    {
        io << Term::Color(Term::WHITE) << "█";
    }
    else if (dying)
    {
        io << Term::Color(Term::RED) << "█";
    }
    else if (alive)
    {
        io << Term::Color(Term::GREEN) << "█";
    }
    else
    {
        io << Term::Color(Term::BLACK) << "█";
    }
}

void Cell::setNeighbors(CellIList neighbors)
{
    // Initialize data
    this->neighbors = new Cell *[8];
    // Setup neighbors
    int i = 0;
    for (Cell *c : neighbors)
    {
        this->neighbors[i] = c;
        i++;
    }
}