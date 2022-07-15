#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include "trio.hpp"
#include "Cell.h"
#include "TrIOLife.h"

int main()
{
    trio::IO io;
    Cell **grid;
    int rows, cols;
    // Get the mode to run in (file or random)
    std::string mode = runModeMenu();
    int gens;
    if (mode == "file")
    {
        loadFile(runFilePicker(), grid, rows, cols);
        // Get the number of iterations to run through
        gens = runNumInput("Generations to View (if not stabilized)");
        printGrid(grid, rows, cols);
        nextGen(grid, rows, cols);
    }
    else if (mode == "random")
    {
        // Get the percentage to fill the random world
        int perc = runNumInput("Percent chance of a cell starting alive");
        // Get the number of iterations to run through
        gens = runNumInput("Generations to View (if not stabilized)");
        srand(time(NULL));
        randGame(grid, rows, cols, perc);
        printGrid(grid, rows, cols);
        nextGen(grid, rows, cols);
    }
    else {
        exit(1);
    }
    connectNeighbors(grid, rows, cols);
    io << trio::Point(rows, 0) << "Gen #1";

    // run the generations
    bool stabilized = false;
    for (int i = 1; i < gens && !stabilized; i++)
    {
        trio::sleep_ms(50);
        stabilized = checkGrid(grid, rows, cols);
        printGrid(grid, rows, cols, true);
        io << trio::Point(rows, 0) << "Gen #" << i + 1;
        nextGen(grid, rows, cols);
    }
}

void printGrid(Cell **grid, int rows, int cols, bool skipStable)
{
    trio::IO io;
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            if (!skipStable || !grid[r][c].isStable())
            {
                io << trio::Point(r, c);
                grid[r][c].print(false);
            }
        }
    }
}

void connectNeighbors(Cell **grid, int rows, int cols)
{
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            // Define directions relative to the current cell
            int up, down, left, right;
            if (r == 0)
            {
                up = rows - 1;
            }
            else
            {
                up = r - 1;
            }
            down = (r + 1) % rows;
            if (c == 0)
            {
                left = cols - 1;
            }
            else
            {
                left = c - 1;
            }
            right = (c + 1) % cols;
            // Assign all 8 neighbors
            grid[r][c].setNeighbors({
                &grid[up][left],
                &grid[up][c],
                &grid[up][right],
                &grid[r][left],
                &grid[r][right],
                &grid[down][left],
                &grid[down][c],
                &grid[down][right],
            });
        }
    }
}

bool checkGrid(Cell **grid, int rows, int cols)
{
    bool stable = true;
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            grid[r][c].check();
            if (!grid[r][c].isStable())
                stable = false;
        }
    }
    // return whether the entire grid is stable yet
    return stable;
}

void nextGen(Cell **grid, int rows, int cols)
{
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            grid[r][c].next();
        }
    }
}