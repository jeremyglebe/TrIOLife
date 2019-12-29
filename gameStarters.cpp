#include <fstream>
#include <string>
#include "Cell.h"

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
