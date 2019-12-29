#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include "Termio.h"
#include "Cell.h"
#include "TermioLife.h"

int main()
{
    Term::IO io;
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
    connectNeighbors(grid, rows, cols);

    // run the generations
    for (int i = 0; i < gens; i++)
    {
        io << Term::sleep(50);
        checkGrid(grid, rows, cols);
        printGrid(grid, rows, cols, true);
        nextGen(grid, rows, cols);
    }
}

void printGrid(Cell **grid, int rows, int cols, bool skipStable)
{
    Term::IO io;
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            if (!skipStable || !grid[r][c].isStable())
            {
                io << Term::Point(r, c);
                grid[r][c].print();
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

void checkGrid(Cell **grid, int rows, int cols)
{
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            grid[r][c].check();
        }
    }
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