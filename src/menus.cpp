#include <string>
#include "trio.hpp"

std::string runModeMenu()
{
    trio::IO io;
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
    io.clear() << trio::Point(0, 0) << menuModel;
    do
    {
        if (option == "random")
        {
            io << trio::Point(2, 0) << "┃  ☛ Random    ┃";
            io << trio::Point(3, 0) << "┃    File      ┃" << trio::Point(0, 0);
        }
        else if (option == "file")
        {
            io << trio::Point(2, 0) << "┃    Random    ┃";
            io << trio::Point(3, 0) << "┃  ☛ File      ┃" << trio::Point(0, 0);
        }
        io >> btn;
        if (option == "random" && btn == 's')
            option = "file";
        if (option == "file" && btn == 'w')
            option = "random";
    } while (btn != ' ');
    io.clear() << trio::Point(0, 0);
    return option;
}

std::string runFilePicker()
{
    trio::IO io;
    std::string menuModel = "";

    menuModel += "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n";
    menuModel += "┃&60Enter file name:&00                              ┃\n";
    menuModel += "┃                &60‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾&00┃\n";
    menuModel += "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n";

    std::string file;
    io.clear() << trio::Point(0, 0) << menuModel;
    io << trio::Point(1, 18);
    std::cin >> file;
    io.clear() << trio::Point(0, 0);
    return file;
}

int runNumInput(std::string prompt)
{
    trio::IO io;
    std::string menu = "";
    int sz = prompt.size();
    std::string borderFill = "";
    for (int i = 0; i < sz; i++)
    {
        borderFill += "━";
    }

    menu += "┏━" + borderFill + "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n";
    menu += "┃&60" + prompt + ":&00                              ┃\n";
    menu += "┃ " + std::string(sz, ' ') + "&60‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾&00┃\n";
    menu += "┗━" + borderFill + "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n";

    int num;
    io.clear() << trio::Point(0, 0) << menu;
    io << trio::Point(1, 3 + sz);
    std::cin >> num;
    io.clear() << trio::Point(0, 0);
    return num;
}
