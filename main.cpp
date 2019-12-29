#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include "Termio.h"
#include "Cell.h"

std::string runModeMenu();
std::string runFilePicker();
int runNumInput(std::string);
void loadFile(std::string, Cell **&, int &, int &);
void randGame(Cell **&, int &, int &, int perc);
void printGrid(Cell **grid, int rows, int cols, bool skipStable = false);
void connectNeighbors(Cell **, int, int);
void checkGrid(Cell **, int, int);
void nextGen(Cell **, int, int);

int main()
{
    Term::IO io;
    Cell **grid;
    int rows, cols;
    // Get the mode to run in (file or random)
    std::string mode = runModeMenu();
    // Get the number of iterations to run through
    int gens = runNumInput("Generations to View (if not stabilized)");
    if (mode == "file")
    {
        loadFile(runFilePicker(), grid, rows, cols);
        printGrid(grid, rows, cols);
        nextGen(grid, rows, cols);
    }
    else if (mode == "random")
    {
        // Get the percentage to fill the random world
        int perc = runNumInput("Percent chance of a cell starting alive");
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

void loadFile(std::string file, Cell **&grid, int &rows, int &cols)
{
    std::ifstream in;
    char x;
    in.open(file);

    in >> rows >> cols;
    in.ignore(1000, '\n');
    grid = new Cell *[rows];
    for (int r = 0; r < rows; r++)
    {
        grid[r] = new Cell[cols];
        for (int c = 0; c < cols; c++)
        {
            x = in.get();
            if (x == 'X')
            {
                grid[r][c].spawn();
            }
        }
        in.ignore(1000, '\n');
    }
}

void randGame(Cell **&grid, int &rows, int &cols, int perc)
{
    rows = (rand() % 30) + 1;
    cols = (rand() % 80) + 1;

    grid = new Cell *[rows];
    for (int r = 0; r < rows; r++)
    {
        grid[r] = new Cell[cols];
        for (int c = 0; c < cols; c++)
        {
            if (rand() % 100 + 1 < perc)
            {
                grid[r][c].spawn();
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