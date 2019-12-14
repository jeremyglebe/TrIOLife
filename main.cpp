#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include "Termio.h"
#include "Cell.h"

std::string runMenu();
std::string runFilePicker();
void loadFile(std::string, Cell **&, int &, int &);
void randGame(Cell **&, int &, int &);
void printGrid(Cell **, int, int);

int main()
{
    Cell **grid;
    int rows, cols;
    std::string mode = runMenu();
    if (mode == "file")
    {
        loadFile(runFilePicker(), grid, rows, cols);
        printGrid(grid, rows, cols);
    }
    else if (mode == "random")
    {
        srand(time(NULL));
        randGame(grid, rows, cols);
        printGrid(grid, rows, cols);
    }
}

std::string runMenu()
{
    Term::IO io;
    std::string menuModel = "";
    menuModel += "┏━━━━━━━━━━━━━━┓\n";
    menuModel += "┃ &40Game of Life&00 ┃\n";
    menuModel += "┃    Random    ┃\n";
    menuModel += "┃    File      ┃\n";
    menuModel += "┃              ┃\n";
    menuModel += "┃ Menu Control ┃\n";
    menuModel += "┃ W: ▲         ┃\n";
    menuModel += "┃ S: ▼         ┃\n";
    menuModel += "┃ Confirm with ┃\n";
    menuModel += "┃  [SPACEBAR]  ┃\n";
    menuModel += "┗━━━━━━━━━━━━━━┛\n";

    char btn;
    std::string option = "random";
    io << Term::clear << Term::Point(0, 0) << menuModel;
    do
    {
        if (option == "random")
            io << Term::Point(2, 3) << "☛" << Term::Point(3, 3) << " " << Term::Point(0, 0);
        else if (option == "file")
            io << Term::Point(2, 3) << " " << Term::Point(3, 3) << "☛" << Term::Point(0, 0);
        io >> btn;
        if (option == "random" && btn == 's')
            option = "file";
        if (option == "file" && btn == 'w')
            option = "random";
    } while (btn != ' ');
    io << Term::clear << Term::Point(0, 0);
    return option;
}

std::string runFilePicker()
{
    Term::IO io;
    std::string menuModel = "";

    menuModel += "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n";
    menuModel += "┃&60Enter file name:&00                              ┃\n";
    menuModel += "┃                &60‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾&00┃\n";
    menuModel += "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n";

    std::string file;
    io << Term::clear << Term::Point(0, 0) << menuModel;
    io << Term::Point(1, 18);
    std::cin >> file;
    io << Term::clear << Term::Point(0, 0);
    return file;
}

void printGrid(Cell **grid, int rows, int cols)
{
    Term::IO io;
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            grid[r][c].print();
        }
        io << '\n';
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

void randGame(Cell **&grid, int &rows, int &cols)
{
    rows = (rand() % 30) + 1;
    cols = (rand() % 80) + 1;

    grid = new Cell *[rows];
    for (int r = 0; r < rows; r++)
    {
        grid[r] = new Cell[cols];
        for (int c = 0; c < cols; c++)
        {
            if (rand() % 100 < 10)
            {
                grid[r][c].spawn();
            }
        }
    }
}