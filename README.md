# Lab6_Vector_Lab

## Description
This program lets users create, store, list, and manage 3D vectors. It also supports saving and loading vectors using files.

## How to Build
Compile the program using GCC:

make

## How to Run

./vector


## Commands
- `list` - Lists stored vectors.
- `clear` - Clears stored vectors.
- `name = x y z` - Creates a vector.
- `load` - Loads vectors from a file.
- `save` - Saves vectors to a file.
- `quit` - Exits the program.

## Dynamic Memory
The program uses dynamic memory to store vectors. It tracks the number of vectors and available capacity. The `free()` function releases allocated memory when it is no longer needed.

## File I/O
The program can save vectors to files and load them later.