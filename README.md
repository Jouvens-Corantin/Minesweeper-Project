# Minesweeper (SFML & C++)

## Overview
This is a desktop implementation of the classic Minesweeper game, developed using C++ and the SFML (Simple and Fast Multimedia Library). The game features a graphical interface where players can interact with a grid of tiles, reveal empty spaces, flag mines, and track their progress through a game clock and mine counter.

## Features
- **Graphical Interface**: Fully rendered UI using SFML.
- **Recursive Tile Clearing**: Automated reveal of empty neighbor tiles when a '0' tile is clicked.
- **Game Status Tracking**: Includes win/loss conditions and a reset mechanism.
- **Flagging System**: Ability to mark potential mines using right-click.
- **Leaderboard**: Completion times are taken and stored in a .txt file.

## Memory Management
A critical aspect of this project is the robust management of system resources.
- **RAII Principles**: Resource Acquisition Is Initialization (RAII) is utilized to manage SFML textures, fonts, and sprites, ensuring that memory is allocated and deallocated correctly with the lifecycle of the objects.
- **Smart Pointers & Containers**: Standard library containers (such as `std::vector` and `std::map`) are used to store game data, leveraging their internal memory management to prevent leaks.
- **Explicit Cleanup**: Where dynamic allocation is necessary, careful attention is paid to the destructor logic to ensure every `new` has a corresponding `delete`, maintaining a zero-leak footprint during long play sessions.

## How to Run

### Option 1: Using an IDE
1. Ensure SFML is installed and correctly linked in your IDE (e.g., Visual Studio, CLion, or VS Code).
2. Open the project folder.
3. Locate and run `main.cpp`.
4. The IDE will compile the source files and launch the game window.

### Option 2: Building to an Executable (.exe)
To build the project into a standalone executable using the backend structure:
1. Ensure that `Project II Back-end.h` is included in the project directory.
2. Use your compiler (e.g., g++) to link the SFML libraries and the backend header.
3. Compile the source code to generate the executable:
   - On Windows: `g++ main.cpp -o Minesweeper.exe -lsfml-graphics -lsfml-window -lsfml-system`
4. Run the generated `Minesweeper.exe`.
