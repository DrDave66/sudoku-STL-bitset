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

## Allowable Values
There are two basic conditions that are employed to solve the vast majority of Sudoku puzzles.  Both are assisted by the maintenance of an ***allowable values*** matrix.  This matrix mirrors the Sudoku puzzle, but contains the list of allowable values for each cell. The puzzle begins with all values being allowed to be placed in every cell.  But once a number is placed into a cell, that number is excluded as an allowable value for all of that cells peers.  

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
Notice that every value is allowed to be placed in every cell at this point.  

If we assign cell E5 a value of 3, the puzzle and allowable value matrices are now:
```
    1   2   3    4   5   6    7   8   9
  =========================================
A || . | . | . || . | . | . || . | . | . ||
B || . | . | . || . | . | . || . | . | . ||
C || . | . | . || . | . | . || . | . | . ||
  || --------- || --------- || --------- ||
D || . | . | . || . | . | . || . | . | . ||
E || . | . | . || . | 3 | . || . | . | . ||
F || . | . | . || . | . | . || . | . | . ||
  || --------- || --------- || --------- ||
G || . | . | . || . | . | . || . | . | . ||
H || . | . | . || . | . | . || . | . | . ||
I || . | . | . || . | . | . || . | . | . ||
  =========================================

         1           2           3            4           5           6            7           8           9
  =================================================================================================================
A || 123456789 | 123456789 | 123456789 || 123456789 |  12456789 | 123456789 || 123456789 | 123456789 | 123456789 ||
B || 123456789 | 123456789 | 123456789 || 123456789 |  12456789 | 123456789 || 123456789 | 123456789 | 123456789 ||
C || 123456789 | 123456789 | 123456789 || 123456789 |  12456789 | 123456789 || 123456789 | 123456789 | 123456789 ||
  || --------------------------------- || --------------------------------- || --------------------------------- ||
D || 123456789 | 123456789 | 123456789 ||  12456789 |  12456789 |  12456789 || 123456789 | 123456789 | 123456789 ||
E ||  12456789 |  12456789 |  12456789 ||  12456789 |           |  12456789 ||  12456789 |  12456789 |  12456789 ||
F || 123456789 | 123456789 | 123456789 ||  12456789 |  12456789 |  12456789 || 123456789 | 123456789 | 123456789 ||
  || --------------------------------- || --------------------------------- || --------------------------------- ||
G || 123456789 | 123456789 | 123456789 || 123456789 |  12456789 | 123456789 || 123456789 | 123456789 | 123456789 ||
H || 123456789 | 123456789 | 123456789 || 123456789 |  12456789 | 123456789 || 123456789 | 123456789 | 123456789 ||
I || 123456789 | 123456789 | 123456789 || 123456789 |  12456789 | 123456789 || 123456789 | 123456789 | 123456789 ||
  =================================================================================================================
```
Notice that the value of 3 has been removed from all of the peers of cell E5, and cell E5 no longer has any allowable values, since it's value has been assigned.

## Solution Strategy
Let's begin with a real puzzle.  The puzzle and allowable value matrices are:
```
     1   2   3    4   5   6    7   8   9
  =========================================
A || . | . | 3 || . | 2 | . || 6 | . | . ||
B || 9 | . | . || 3 | . | 5 || . | . | 1 ||
C || . | . | 1 || 8 | . | 6 || 4 | . | . ||
  || --------- || --------- || --------- ||
D || . | . | 8 || 1 | . | 2 || 9 | . | . ||
E || 7 | . | . || . | . | . || . | . | 8 ||
F || . | . | 6 || 7 | . | 8 || 2 | . | . ||
  || --------- || --------- || --------- ||
G || . | . | 2 || 6 | . | 9 || 5 | . | . ||
H || 8 | . | . || 2 | . | 3 || . | . | 9 ||
I || . | . | 5 || . | 1 | . || 3 | . | . ||
  =========================================

         1           2           3            4           5           6            7           8           9
  =================================================================================================================
A ||        45 |      4578 |           ||        49 |           |       147 ||           |      5789 |        57 ||
B ||           |     24678 |        47 ||           |        47 |           ||        78 |       278 |           ||
C ||        25 |       257 |           ||           |        79 |           ||           |     23579 |      2357 ||
  || --------------------------------- || --------------------------------- || --------------------------------- ||
D ||       345 |       345 |           ||           |      3456 |           ||           |     34567 |     34567 ||
E ||           |    123459 |        49 ||       459 |     34569 |         4 ||         1 |     13456 |           ||
F ||      1345 |     13459 |           ||           |      3459 |           ||           |      1345 |       345 ||
  || --------------------------------- || --------------------------------- || --------------------------------- ||
G ||       134 |      1347 |           ||           |       478 |           ||           |      1478 |        47 ||
H ||           |      1467 |        47 ||           |       457 |           ||        17 |      1467 |           ||
I ||        46 |      4679 |           ||         4 |           |        47 ||           |     24678 |      2467 ||
  =================================================================================================================
  ```
  #### Step 1:
  First we search through the puzzle and find cells with only a single allowable value.  For example, cell I4 can only have a value of 4.  So we immediately assign cell I4 to 4. We search through all the cells this way and solve as many as we can.  

  #### Step 2:
  The second step is searching through each unit and finding any values that can appear in only one cell.  In the example above, we see that in Column 1, the value of 2 can only appear in cell C1.  In column 3, the value of 9 can only appear in cell E3. In Column 4, the value of 5 can only appear in cell E4. We loop through all of the units, see if any value can appear only once, and place that value.  

  If either Step 1 or Step 2 places a value, we repeat Step 1 and Step 2 again since placing a value changes the available value matrix.  For ~97% of puzzles in the 10 million puzzle set that i test with are solved this way.  In the 1 million puzzle set, all puzzles are solved with this technique alone. But not every puzzle is solved with these two step.  For the ones that are not solved, we must use a binary tree search.

  ## Guessing
  Guessing a sudoku solution is hard, **VERY** hard. we have 81 cells, with 9 possible values.  That leads to a total of 1.5E17 possible solutions.  To put that into perspective, the age of the universe (13.8 billion years, or 7000 years if your are a bible-humping young earth creationst moron) is 4.3E17 seconds.

  Random guessing is **NOT** the way that you want to approach solving Sudoku.  After Steps 1 and 2 above, we have little recourse but to start guessing at solutions.  But let's not be totally random about our guesses.

  Here's a starting puzzle, and how it sits after Steps 1 and 2.
  ```
       1   2   3    4   5   6    7   8   9
  =========================================
A || 1 | . | . || 9 | 2 | . || . | . | . ||
B || 5 | 2 | 4 || . | 1 | . || . | . | . ||
C || . | . | . || . | . | . || . | 7 | . ||
  || --------- || --------- || --------- ||
D || . | 5 | . || . | . | 8 || 1 | . | 2 ||
E || . | . | . || . | . | . || . | . | . ||
F || 4 | . | 2 || 7 | . | . || . | 9 | . ||
  || --------- || --------- || --------- ||
G || . | 6 | . || . | . | . || . | . | . ||
H || . | . | . || . | 3 | . || 9 | 4 | 5 ||
I || . | . | . || . | 7 | 1 || . | . | 6 ||
  =========================================

         1           2           3            4           5           6            7           8           9
  =================================================================================================================
A ||           |       378 |      3678 ||           |           |     34567 ||     34568 |      3568 |       348 ||
B ||           |           |           ||       368 |           |       367 ||       368 |       368 |       389 ||
C ||      3689 |       389 |      3689 ||     34568 |      4568 |      3456 ||    234568 |           |     13489 ||
  || --------------------------------- || --------------------------------- || --------------------------------- ||
D ||      3679 |           |      3679 ||       346 |       469 |           ||           |        36 |           ||
E ||     36789 |     13789 |    136789 ||    123456 |      4569 |    234569 ||    345678 |      3568 |      3478 ||
F ||           |       138 |           ||           |        56 |       356 ||      3568 |           |        38 ||
  || --------------------------------- || --------------------------------- || --------------------------------- ||
G ||     23789 |           |    135789 ||      2458 |      4589 |      2459 ||      2378 |      1238 |      1378 ||
H ||       278 |       178 |       178 ||       268 |           |        26 ||           |           |           ||
I ||      2389 |      3489 |      3589 ||      2458 |           |           ||       238 |       238 |           ||
  =================================================================================================================
```
After Steps 1 and 2 have exhausted their possibilities:
```
     1   2   3    4   5   6    7   8   9
  =========================================
A || 1 | . | . || 9 | 2 | . || . | . | . ||
B || 5 | 2 | 4 || . | 1 | 7 || . | . | 9 ||
C || . | . | . || . | . | . || 2 | 7 | 1 ||
  || --------- || --------- || --------- ||
D || . | 5 | . || . | . | 8 || 1 | . | 2 ||
E || . | . | . || 1 | . | 2 || . | . | . ||
F || 4 | 1 | 2 || 7 | . | . || . | 9 | . ||
  || --------- || --------- || --------- ||
G || . | 6 | . || . | . | 9 || . | 1 | . ||
H || . | . | 1 || . | 3 | 6 || 9 | 4 | 5 ||
I || . | 4 | . || . | 7 | 1 || . | 2 | 6 ||
  =========================================

         1           2           3            4           5           6            7           8           9
  =================================================================================================================
A ||           |       378 |      3678 ||           |           |       345 ||     34568 |      3568 |       348 ||
B ||           |           |           ||       368 |           |           ||       368 |       368 |           ||
C ||      3689 |       389 |      3689 ||     34568 |      4568 |       345 ||           |           |           ||
  || --------------------------------- || --------------------------------- || --------------------------------- ||
D ||      3679 |           |      3679 ||       346 |       469 |           ||           |        36 |           ||
E ||     36789 |      3789 |     36789 ||           |      4569 |           ||    345678 |      3568 |      3478 ||
F ||           |           |           ||           |        56 |        35 ||      3568 |           |        38 ||
  || --------------------------------- || --------------------------------- || --------------------------------- ||
G ||      2378 |           |      3578 ||      2458 |       458 |           ||       378 |           |       378 ||
H ||       278 |        78 |           ||        28 |           |           ||           |           |           ||
I ||       389 |           |      3589 ||        58 |           |           ||        38 |           |           ||
  =================================================================================================================
```



