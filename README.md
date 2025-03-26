# Klotski Problem Solver

This project is a Klotski problem solver using Depth-First Search (DFS). It was developed as part of a college class assignment.

## Introduction

Klotski is a sliding block puzzle where the objective is to move a specific block to a target location. This solver uses DFS to explore possible moves and prints the first solution found, within `MAX_DEPTH` moves.

## Features

- Allocates and deallocates matrices dynamically
- Copies and manipulates matrices to simulate moves
- Converts matrices to and from string representations
- Hashes matrices for state comparison
- Checks boundaries and valid moves
- Calculates distances for heuristic purposes
- Implements a binary search tree for efficient state management

## Files

- `main.c`: Contains the main logic for the Klotski solver.
- `matrix.h` and `matrix.c`: Functions for matrix operations.
- `binarysearchtree.h` and `binarysearchtree.c`: Functions for binary search tree operations.
- `shape.h` and `shape.c`: Functions for shape operations.

## Usage

1. Compile the project using a C compiler.
2. Run the executable to solve a Klotski puzzle.

## Compilation

To compile the project, use the following command:
```sh
make
```
or
```sh
gcc -o klotski_solver main.c matrix.c binarysearchtree.c -I.
```
> note: CMAKE was used in development, but it is not necessary for compilation.

## Execution

To run the solver, use the following command:

```sh
./klotski_solver
```

## License

This project is licensed under the MIT License.
