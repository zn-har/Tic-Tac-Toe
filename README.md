# Tic-Tac-Toe in C++ with SDL2

## Overview
This is a simple Tic-Tac-Toe game implemented in C++ using SDL2 and SDL_ttf for rendering graphics and text. Players take turns placing Xs and Os on a 3x3 grid until one player wins or the game ends in a draw.


## Prerequisites
Ensure you have the following installed on your system:
- C++ compiler
- SDL2
- SDL2_ttf

## Installation
1. Install SDL2 and SDL_ttf:
   ```bash
   sudo apt-get install libsdl2-dev libsdl2-ttf-dev   # Debian/Ubuntu
   brew install sdl2 sdl2_ttf                         # macOS (Homebrew)
   ```
2. Clone this repository:
   ```bash
   git clone https://github.com/yourusername/tic-tac-toe-sdl.git
   cd tic-tac-toe-sdl
   ```
3. Compile the program:
   ```bash
   g++ main.cpp -lSDL2 -lSDL2_ttf -lm
   ```
4. Run the game:
   ```bash
   ./a.out
   ```

## How to Play
1. Click on an empty cell to place your mark (X or O).
2. The game will check for a winner after each move.
3. If a player wins or the game ends in a draw, the result will be displayed.
4. Press `R` to reset the game and play again.
5. Close the window to exit.

## Controls
- **Mouse Click**: Place X or O in an empty cell
- **R Key**: Restart the game
- **Close Window**: Exit the game

## File Structure
```
/
├── main.cpp       # Main game logic and SDL2 rendering
├── font.ttf       # Font file for text rendering
├── README.md      # Documentation
```

## Known Issues
- The font file (`font.ttf`) should be placed in the same directory as the executable.
- Ensure SDL2 and SDL_ttf libraries are installed before running the program.

## License
This project is open-source and available under the MIT License.

---
**Enjoy playing Tic-Tac-Toe!**

