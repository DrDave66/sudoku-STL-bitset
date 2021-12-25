# sudoku-STL-bitset
Hello. And welcome to my Sudoku puzzle solver.  Let's start with some nomenclature that will help you understand the rest of the description. My nomenclature may not matching any official standard, if one exists, but it is consistent throughout the documentation.

## Puzzle
A Sudoku puzzle is a 9x9 square will cells in which the numbers 1-9 can be placed. The sudoku ***grid*** is the 9x9 matrix of individual Sudoku ***cells***. Cells are index by their alphabetic *row* and numeric *column*.  The puzzle also contains 9 3x3 ***blocks***.  For example, the cells A1, A2, A3, B1, B2, B3, C1, C2, C3 comprise a single ***block***.

Here is an example empty Sudoku grid
```
     1   2   3    4   5   6    7   8   9
  =========================================  
A || . | . | . || . | . | . || . | . | . ||  
B || . | . | . || . | . | . || . | . | . ||  
C || . | . | . || . | . | . || . | . | . ||  
  || --------- || --------- || --------- ||  
D || . | . | . || . | . | . || . | . | . ||  
E || . | . | . || . | . | . || . | . | . ||  
F || . | . | . || . | . | . || . | . | . ||  
  || --------- || --------- || --------- ||  
G || . | . | . || . | . | . || . | . | . ||  
H || . | . | . || . | . | . || . | . | . ||  
I || . | . | . || . | . | . || . | . | . ||  
  =========================================  
```
*Note: empty cells  are indicated by filling them with a '.' character to make the grid easier to read*

And a solved grid:
```
     1   2   3    4   5   6    7   8   9
  =========================================  
A || 5 | 7 | 4 || 6 | 1 | 3 || 9 | 8 | 2 ||  
B || 8 | 3 | 9 || 5 | 7 | 2 || 4 | 1 | 6 ||  
C || 2 | 1 | 6 || 4 | 8 | 9 || 7 | 5 | 3 ||  
  || --------- || --------- || --------- ||  
D || 3 | 9 | 2 || 1 | 5 | 8 || 6 | 7 | 4 ||  
E || 7 | 4 | 1 || 9 | 2 | 6 || 5 | 3 | 8 ||  
F || 6 | 8 | 5 || 3 | 4 | 7 || 1 | 2 | 9 ||  
  || --------- || --------- || --------- ||  
G || 4 | 2 | 7 || 8 | 6 | 1 || 3 | 9 | 5 ||  
H || 9 | 5 | 8 || 7 | 3 | 4 || 2 | 6 | 1 ||  
I || 1 | 6 | 3 || 2 | 9 | 5 || 8 | 4 | 7 ||  
  =========================================
  ```
> Grid - a entire Sudoku puzzle  
> Cell - an single location for a number  
> Row - specified by a letter, a single row across a puzzle  
> Column - indicated by a number, a single column down a puzzle  

## Rules  
In solving a Sudoku puzzle, you are given a partially complete grid.  Your task is to complete the grid with the following constraints:  
1. Each cell is filled with a single number
2. Each row must be filled with each digit 1-9, and each digit must appear exactly once
3. Each coumn must be filled with each digit 1-9, and each digit must appear exactly once
4. Each block must be filled with each digit 1-9, and each digit must appear exactly once.

## Units and Peers
A Sudoku ***unit*** is a row, a column, or a block.  A sudoku puzzle consists of exactly 27 units.  
```
A1 B1 C1 D1 E1 F1 G1 H1 I1  -- rows
A2 B2 C2 D2 E2 F2 G2 H2 I2 
A3 B3 C3 D3 E3 F3 G3 H3 I3 
A4 B4 C4 D4 E4 F4 G4 H4 I4 
A5 B5 C5 D5 E5 F5 G5 H5 I5 
A6 B6 C6 D6 E6 F6 G6 H6 I6 
A7 B7 C7 D7 E7 F7 G7 H7 I7 
A8 B8 C8 D8 E8 F8 G8 H8 I8 
A9 B9 C9 D9 E9 F9 G9 H9 I9 
A1 A2 A3 A4 A5 A6 A7 A8 A9  -- columns
B1 B2 B3 B4 B5 B6 B7 B8 B9 
C1 C2 C3 C4 C5 C6 C7 C8 C9 
D1 D2 D3 D4 D5 D6 D7 D8 D9 
E1 E2 E3 E4 E5 E6 E7 E8 E9 
F1 F2 F3 F4 F5 F6 F7 F8 F9 
G1 G2 G3 G4 G5 G6 G7 G8 G9 
H1 H2 H3 H4 H5 H6 H7 H8 H9 
I1 I2 I3 I4 I5 I6 I7 I8 I9 
A1 A2 A3 B1 B2 B3 C1 C2 C3 -- blocks
A4 A5 A6 B4 B5 B6 C4 C5 C6 
A7 A8 A9 B7 B8 B9 C7 C8 C9 
D1 D2 D3 E1 E2 E3 F1 F2 F3 
D4 D5 D6 E4 E5 E6 F4 F5 F6 
D7 D8 D9 E7 E8 E9 F7 F8 F9 
G1 G2 G3 H1 H2 H3 I1 I2 I3 
G4 G5 G6 H4 H5 H6 I4 I5 I6 
G7 G8 G9 H7 H8 H9 I7 I8 I9 
```
Each cell belongs to exactly 3 units.  The row, the column and the block that contains it.  Here are the units that cell E5 belongs to:
```
New Unit Dict: E5 
A5 B5 C5 D5 E5 F5 G5 H5 I5 - column 5
E1 E2 E3 E4 E5 E6 E7 E8 E9 - row E
D4 D5 D6 E4 E5 E6 F4 F5 F6 - E5's block
```
The final term used is ***peer***.  A cells peers is all of the cells in the list of units the cell belongs to, minus the cell itself.  Every cell has exactly 20 peers.  Taking E5 as the example again, the list of E5 peers is:
```
E5 - A5 B5 C5 D5 F5 G5 H5 I5 E1 E2 E3 E4 E6 E7 E8 E9 D4 D6 F4 F6 
     |------row------------| |--------col----------| |--block--|    

     1   2   3    4   5   6    7   8   9
  =========================================  
A || . | . | . || . | X | . || . | . | . ||  
B || . | . | . || . | X | . || . | . | . ||  
C || . | . | . || . | X | . || . | . | . ||  
  || --------- || --------- || --------- ||  
D || . | . | . || X | X | X || . | . | . ||  
E || X | X | X || X | X | X || X | X | X ||  
F || . | . | . || X | X | X || . | . | . ||  
  || --------- || --------- || --------- ||  
G || . | . | . || . | X | . || . | . | . ||  
H || . | . | . || . | X | . || . | . | . ||  
I || . | . | . || . | X | . || . | . | . ||  
  =========================================  
```
The concept of peers is vital in the solution strategy of a puzzle.  If a number is placed in a cell, it is *excluded from being a possible value in all of that cell's peers*.

## Solution Strategy
There are two basic conditions that are employed to solve the vast majority of Sudoku puzzles.  Both are assisted by the maintenance of an ***allowable values*** matrix.  This matrix mirrors the Sudoku puzzle, but contains the list of allowable values for each cell. The puzzle begins with all values being allowed to be placed in every cell.  But once a number is placed into a cell, that number is excluded as an allowableValue for all of that cells peers.  

With an empty puzzle, the puzzle and allowable value matrices are:
```
    1   2   3    4   5   6    7   8   9
  =========================================
A || . | . | . || . | . | . || . | . | . ||
B || . | . | . || . | . | . || . | . | . ||
C || . | . | . || . | . | . || . | . | . ||
  || --------- || --------- || --------- ||
D || . | . | . || . | . | . || . | . | . ||
E || . | . | . || . | . | . || . | . | . ||
F || . | . | . || . | . | . || . | . | . ||
  || --------- || --------- || --------- ||
G || . | . | . || . | . | . || . | . | . ||
H || . | . | . || . | . | . || . | . | . ||
I || . | . | . || . | . | . || . | . | . ||
  =========================================
         1           2           3            4           5           6            7           8           9
  =================================================================================================================
A || 123456789 | 123456789 | 123456789 || 123456789 | 123456789 | 123456789 || 123456789 | 123456789 | 123456789 ||
B || 123456789 | 123456789 | 123456789 || 123456789 | 123456789 | 123456789 || 123456789 | 123456789 | 123456789 ||
C || 123456789 | 123456789 | 123456789 || 123456789 | 123456789 | 123456789 || 123456789 | 123456789 | 123456789 ||
  || --------------------------------- || --------------------------------- || --------------------------------- ||
D || 123456789 | 123456789 | 123456789 || 123456789 | 123456789 | 123456789 || 123456789 | 123456789 | 123456789 ||
E || 123456789 | 123456789 | 123456789 || 123456789 | 123456789 | 123456789 || 123456789 | 123456789 | 123456789 ||
F || 123456789 | 123456789 | 123456789 || 123456789 | 123456789 | 123456789 || 123456789 | 123456789 | 123456789 ||
  || --------------------------------- || --------------------------------- || --------------------------------- ||
G || 123456789 | 123456789 | 123456789 || 123456789 | 123456789 | 123456789 || 123456789 | 123456789 | 123456789 ||
H || 123456789 | 123456789 | 123456789 || 123456789 | 123456789 | 123456789 || 123456789 | 123456789 | 123456789 ||
I || 123456789 | 123456789 | 123456789 || 123456789 | 123456789 | 123456789 || 123456789 | 123456789 | 123456789 ||
  =================================================================================================================
  ```


