#include <string>
#include "Termio.h"
#include "Cell.h"

std::string runMenu();

int main()
{
    runMenu();
}

std::string runMenu()
{
    Term::IO io;
    std::string menuModel = "";
    menuModel += "┏━━━━━━━━━━━━━━┓\n";
    menuModel += "┃ &40Game of Life&00 ┃\n";
    menuModel += "┃  X Random    ┃\n";
    menuModel += "┃   X File     ┃\n";
    menuModel += "┃              ┃\n";
    menuModel += "┃ Menu Control ┃\n";
    menuModel += "┃ W: ▲         ┃\n";
    menuModel += "┃ S: ▼         ┃\n";
    menuModel += "┃ Confirm with ┃\n";
    menuModel += "┃  [SPACEBAR]  ┃\n";
    menuModel += "┗━━━━━━━━━━━━━━┛\n";

    char btn;
    std::string option = "random";
    io << Term::clear << Term::Point(0, 0);
    do
    {
        io << menuModel;
        if (option == "random")
            io << Term::Point(2, 3) << "☛" << Term::Point(3, 4) << " " << Term::Point(0, 0);
        else if (option == "file")
            io << Term::Point(2, 3) << " " << Term::Point(3, 4) << "☛" << Term::Point(0, 0);
        io >> btn;
        if (option == "random" && btn == 's')
            option = "file";
        if (option == "file" && btn == 'w')
            option = "random";
    } while (btn != ' ');
    io << Term::clear << Term::Point(0, 0);
    return option;
}