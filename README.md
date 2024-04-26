# LETTRIS - A tettris with letters

Lettris is a tetris game with letters. The goal is to form words with the falling letters. The game is written in c++2b and uses the SFML library version 2.6.1.

## IMPORTANT

The game has been entirely developped in a windows environment on VSCode using MinGW-W64-builds-5.0.0 with c++2b and SFML-2.6.1. The game has not been tested on other platforms. The game has not been tested on other compilers. The game has not been tested on other versions of SFML. The game has not been tested on other versions of c++. The game has not been tested on other IDEs.

### Prerequisites

You need to have the correct version and build of MinGW-W64 to compile the game.
The MinGW build used in developpement is : [`x86_64-13.1.0-release-posix-seh-msvcrt-rt_v11-rev1`](https://github.com/niXman/mingw-builds-binaries/releases/download/13.1.0-rt_v11-rev1/x86_64-13.1.0-release-posix-seh-msvcrt-rt_v11-rev1.7z)

The SFML libraries are included in the repository. You don't need to download them.

### Setup

After downloading the MinGW build, extract the contents of mingw64 to `C:\MinGW\` .

Alternatively, you can extract the contents of mingw64 to another location and change the path of the compiler in the  [`c_cpp_properties.json`](https://github.com/FluffLescure/mini-proj/blob/main/.vscode/c_cpp_properties.json) and [`tasks.json`](https://github.com/FluffLescure/mini-proj/blob/main/.vscode/tasks.json) files.

## Documentation

The documentation of the front-end design is available in the [`doc`](https://github.com/FluffLescure/mini-proj/blob/main/doc) folder.
The game logic is not documented but has been heavily inspired by the online lettris game available at [`https://langue-francaise.tv5monde.com/jouer/jeux/lettris`](https://https://langue-francaise.tv5monde.com/jouer/jeux/lettris).



