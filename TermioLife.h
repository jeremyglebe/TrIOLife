#include <string>
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