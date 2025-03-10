# Depth-First Search Sudoku Generator

A C++ implementation of a Sudoku puzzle generator that uses the Depth-First Search algorithm to create valid puzzles.

## Project Overview

This application generates Sudoku puzzles using a depth-first search algorithm. The program works by filling a 9x9 grid according to Sudoku rules (each row, column, and 3x3 subgrid must contain all digits 1-9 without repetition).

## Requirements

- Visual Studio 2019 or newer
- Windows platform
- C++ compiler support for C++11 or later

## Building the Project

### Using Visual Studio IDE

1. Open [Sudoku.sln](Sudoku.sln) in Visual Studio
2. Select the desired build configuration:
   - Platform: x86 (Win32) or x64
   - Configuration: Debug or Release
3. Build the solution (Ctrl+Shift+B or Build → Build Solution)

### Output Files

- Debug build: 
  - 32-bit: `Debug/Sudoku.exe`
  - 64-bit: `x64/Debug/Sudoku.exe`
- Release build: 
  - 32-bit: `Release/Sudoku.exe`
  - 64-bit: `x64/Release/Sudoku.exe`

## Project Structure

- [Source.cpp](Sudoku/Source.cpp): Main implementation file containing the Sudoku generation algorithm
- [sudokuTest.txt](Sudoku/sudokuTest.txt): Test file used for input/output testing

## How It Works

The Depth-First Search algorithm works by:
1. Starting with an empty 9x9 grid
2. Recursively trying to fill each cell with a valid digit
3. Backtracking when a constraint violation is detected
4. Continuing until a complete valid solution is found

## Usage

After building the project, run the executable. The program may read from the sudokuTest.txt file for input or generate puzzles from scratch depending on the implementation details.

## License

This project is open for educational and personal use.
