cmake_minimum_required(VERSION 3.0.0)
project(sudoku VERSION 0.1.0)

# comment
add_executable(
    sudoku 
    src/Guess.cpp 
    src/PrecisionTimeLapse.cpp 
    src/Puzzles.cpp 
    src/RowCol.cpp 
    src/Sudoku.cpp 
    src/BitsetSudoku.cpp)

