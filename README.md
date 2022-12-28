# TKSolve
A fast and versatile Rubik's Cube Solver

***

## Features:
- Solves over **1.5 million cubes per second** in testing
- `solve_cube()`: prints the solution to a cube given a cornerstate and edgestate
- `solve_corner()`: prints solution to UBL corner (buffer) given a cornerstate
- `solve_edge()`: prints solution to UR edge (buffer) given an edgestate

## Extreme Performance Demo:
- Comment out all four `printf`s in `cube_solver.c`
- Compile with `make`
- `./test_cube_solver` will generate every possible 2x2 scramble, solve them, and report solve speed.
  - On good hardware, `TKSolve` should solve around **1.7 million** cubes per second
  - This is equivalent to solving *every possible 2x2 cube* within **2.2 seconds**
