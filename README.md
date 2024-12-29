# Minesweeper Project

This is a Minesweeper game implementation, developed as a project for APCS (CS161) in 2023. The project received a perfect score of 10/10.

## Overview
This project simulates the classic Minesweeper game using advanced programming techniques such as Depth-First Search (DFS) for board traversal. The game runs in a console environment and uses the `console.h` library for its user interface.

## Features
- **Interactive Gameplay**: Play Minesweeper directly from the console.
- **DFS Algorithm**: Efficient implementation for uncovering cells.
- **Custom Board Logic**: Fully implemented game rules, including bomb placement and cell adjacency logic.
- **Modular Design**: Clean separation of concerns using different source files for the board, cells, and utilities.

## File Structure
The main files and directories are structured as follows:

- **Board.cpp**: Contains the logic for creating and managing the Minesweeper board.
- **Cell.cpp**: Handles individual cell behavior, such as revealing or flagging.
- **CS161Project.cpp**: The main entry point of the program.
- **GetCell.cpp**: Manages cell-related operations.
- **Headers/**: Contains header files defining class interfaces and constants.
- **Resources/**: Additional assets or configuration files.

## How to Run
### Prerequisites
- A Windows environment with Visual Studio installed.
- The `console.h` library.

### Steps
1. Open the `CS161Project.sln` file in Visual Studio.
2. Build the solution to generate the executable.
3. Run the program from Visual Studio or execute `CS161Project.exe` directly.

## Algorithms Used
The project leverages the Depth-First Search (DFS) algorithm to efficiently reveal multiple cells when a blank cell is uncovered. This ensures the game behaves as expected in scenarios with large open spaces.

## Acknowledgment
- **Libraries**: `console.h` for console interface management.

## Future Improvements
- Add graphical user interface (GUI) support.
- Implement additional difficulty levels.
- Optimize performance for larger board sizes.

## License
This project is for educational purposes and is not distributed under any specific license. Contact the author for permissions or inquiries.
