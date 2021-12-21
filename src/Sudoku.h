#pragma once
#ifndef _SUDOKU
#define _SUDOKU
#include <array>
#include <typeinfo>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <limits>
#include <iomanip>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std;

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
	//vector<string> crossProduct(string a, string b);
    vector<RowCol> crossProductRC(vector<uint8_t>, vector<uint8_t>);
    
	bool setPuzzle(string p);
	//bool setValue(string square, string value);
    bool setValue(uint8_t row, uint8_t col, char value);
    bool setValue(RowCol rc, char value);
    
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
    vector<uint8_t> rows = {0,1,2,3,4,5,6,7,8};
    vector<uint8_t> cols = {0,1,2,3,4,5,6,7,8};
	vector<uint8_t> bits = {0,1,2,3,4,5,6,7,8};
    
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

};

#endif // _SUDOKU
