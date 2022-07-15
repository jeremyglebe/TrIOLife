# TrIOLife (Tree O' Life)
Conway's Game of Life implemented using my TrIO console library - with some extra features!

This is a simple C++ project that mostly serves to demonstrate the fun console features enabled by TrIO.

## Starters
The game allows for you to start with a file input. Some file input examples are provided in the starters folder. Make sure, when running the game, to specify file names relative to the folder you are running the game from. (This might be weird in Visual Studio - you may consider simply copying the contents of a starter into a file you create in the project)


## Running TrIOLife
TrIOLife is a C++ program. You can compile it yourself or run it online using [Replit](https://replit.com/@jeremyglebe/TrIOLife). I have embedded the replit project below.

<iframe frameborder="0" width="100%" height="500px" src="https://replit.com/@jeremyglebe/TrIOLife?embed=true&lite=true&outputonly=true"></iframe>

_In the README on GitHub this will just appear to be an HTML tag. You must be on my website to actually run it._

If you compile using command line, you should be able to do so from the `src/` folder with a simple `*.cpp` parameter. (Make sure to include C++ 11 features if you aren't using them by default)

Examples:
```sh
# G++ (on Linux, Mac, or Windows with MinGW)
g++ *.cpp
# Clang (on Mac)
clang++ -std=c++11 *.cpp
# Visual Studio Developer Command Prompt (on Windows)
cl *.cpp
```

There is also a Visual Studio project included in the repository (`vs-proj/`) for Windows users to run if they prefer.
