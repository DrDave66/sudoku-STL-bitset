#pragma once
#ifndef _SUDOKU
#define _SUDOKU
#include <array>
#include <typeinfo>
#include <string>
#include <vector>
#include <set>
#include <iostream>     // std::cout
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <bitset>

using std::array;
using std::vector;
using std::set;
using std::cout;
using std::endl;
using std::setw;
using std::flush;
using std::stringstream;
using std::string;
using std::uint8_t;
using std::bitset;


#include "Guess.h"
#include "PrecisionTimeLapse.h"
#include "SudokuTypes.h"
#include "RowCol.h"

class Sudoku
{
public:
    Sudoku();
	Sudoku(string puzzle);
	void clearPuzzle();
	void createVectors(void);
    
	bool setPuzzle(string p);
    bool setValue(uint8_t row, uint8_t col, uint8_t bit);
    bool setValue(RowCol rc, bitset<9>);
    
	void printPuzzle(void);
	void printPuzzle(string title);
	void printAllowableValues(void);
	void printAllowableValues(string title);

	void solveOnes(void);
    bool isPuzzleSolved(void);
	bool removeGuess(RowCol, bitset<9>);
	bool guessesRemain(void);
	Guess getGuess();
	bool popGuess();
	void pushGuess(const Guess);
	bool solvePuzzle();
	bool startGuessing();
	void printGuessList();
	uint8_t singleBitSet(bitset<9> b);
//private:
    // these arrays are used for optimized iteration
    array<uint8_t,9> rows;
    array<uint8_t,9> cols;
	array<uint8_t,9> bits;

	// arrays for unitList, units and peers
	// 27 units to list, 9 entries in a unitlist
    array<array<RowCol, 9> ,27> unitList;
	// each cell belongs to 3 units, each having 9 cells
	array<array<array<array<RowCol, 9> ,3 > ,9> ,9> units;
	// each cell has 20 peers
    array<array<array<RowCol, 20> ,9> ,9> peers;

    SUDOKUTYPE puzzle;
    SUDOKUTYPE allowableValues;
	array<Guess, 81> guessList; // ordered list of guesses
	uint8_t guessNumber;
    Guess newGuess;
	array<bitset<9>, 9> bitMask;

};

// this is used to programmically populate cells, units, unitlists and peers
// it uses a vector because the return size is unknown
// crossProduct will take any two iterables
template <class T, class U>
vector<RowCol> crossProduct (T a, U b) {
    static vector<RowCol> v;
    v.clear();
    for(uint8_t aa : a) {
        for (uint8_t bb : b) {
            v.push_back(RowCol(aa,bb));
        }
    }
	return v;
}
#endif // _SUDOKU
