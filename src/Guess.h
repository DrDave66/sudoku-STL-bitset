#pragma once
#ifndef _GUESS
#define _GUESS

#include <string>
#include <bitset>
#include <cstring>

using std::bitset;
using std::string;

#include "RowCol.h"
#include "SudokuTypes.h"

class Sudoku;

class Guess
{
public:
    Guess() {};
    Guess(RowCol _square, bitset<9> _bit, SUDOKUTYPE _puzzle, SUDOKUTYPE _allowableValues);

	Guess(const Guess&);
	Guess& operator=(const Guess& cpy) ;
	string toString();

// members kept public to reduce stack hits
    SUDOKUTYPE puzzle;
    SUDOKUTYPE allowableValues;
	RowCol square;
	bitset<9> guess;
};

#endif // _GUESS

