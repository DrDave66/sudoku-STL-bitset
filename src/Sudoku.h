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
	//bool setValue(string square, string value);
    bool setValue(uint8_t row, uint8_t col, uint8_t bit);
    bool setValue(RowCol rc, uint8_t bit);
    
	void printPuzzle(void);
	void printPuzzle(string title);
	void printAllowableValues(void);
	void printAllowableValues(string title);
	bool solveOnes(void);
	
    bool isPuzzleSolved(void);
	bool removeGuess(RowCol, char);
	bool guessesRemain(void);
	Guess getGuess();
	bool popGuess();
	void pushGuess(const Guess);
	bool solvePuzzle();
	bool startGuessing();
	void printGuessList();
	void test();
//private:
    
    static const uint8_t numRows = 9;
    static const uint8_t numCols = 9;
    array<uint8_t,9> rows = {0,1,2,3,4,5,6,7,8};
    array<uint8_t,9> cols = {0,1,2,3,4,5,6,7,8};
	array<uint8_t,9> bits = {0,1,2,3,4,5,6,7,8};
    
	string digitsText = "123456789";

    array<array<RowCol, 9> ,27> rcUnitList;
    array<array<array<array<RowCol, 9> ,3 > ,9> ,9> rcUnits;
    array<array<array<RowCol, 20> ,9> ,9> rcPeers;

    set<string> digitSet = { "1","2","3","4","5","6","7","8","9" };
	char digits[10] = "123456789";
    SUDOKUTYPE puzzle;
    SUDOKUTYPE allowableValues;
	array<Guess, 81> guessList; // ordered list of guesses
	uint8_t guessNumber;
    Guess newGuess;
	array<bitset<9>, 9> bitMask;
	uint8_t numberOfBitsSet(bitset<9> b);
	uint8_t singleBitSet(bitset<9> b);
};


// crossProduct will take any two iterables
template <class T, class U>
vector<RowCol> crossProduct (T a, U b) {
    static vector<RowCol> v;
    v.clear();
    RowCol rc;
    for(uint8_t aa : a) {
        for (uint8_t bb : b) {
            rc.set(aa,bb);
            v.push_back(rc);
        }
    }
	return v;
}
#endif // _SUDOKU
