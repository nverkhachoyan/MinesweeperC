# Minesweeper

This program implements a basic version of the Minesweeper game.
It includes functions for creating a new game, displaying the game board, 
and handling user commands like uncovering Cells and flagging mines.

## Features

- Customizable grid size and mine count.
- Command-line based user interface.
- Commands to uncover cells, flag potential mines, and start new game.

## Getting Started

### Prerequisites

- A C compiler (like GCC)
- Make (optional for build automation)

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/nverkhachoyan/Minesweeper.git
   ```
2. Navigate to the cloned directory:
   ```bash
   cd Minesweeper
   ```
3. Compile the project. If you have `make` installed:
   ```bash
   make
   ```
   Alternatively, you can compile manually:
   ```bash
   gcc -o Minesweeper src/*.c -I include
   ```

### Running the Game

After compiling, run the game using:

```bash
./Minesweeper
```

## How to Play

- Start a new game by typing `new [rows] [columns] [mines]`.
- Uncover a cell with `uncover [row] [column]`.
- Flag a cell with `flag [row] [column]`.
- Unflag a cell with `unflag [row] [column]`.
- Display the current state of the board with `show`.
- Exit the game with `quit`.

## Contributing

Contributions to the Minesweeper project are welcome. Please feel free to fork the repository, make your changes, and create a pull request.

## Acknowledgments

- This was a project assignment for COMP 222 at California State University.



