#pragma once
#ifndef _PUZZLES
#define _PUZZLES

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <bitset>

using std::vector;
using std::string;
using std::fstream;
using std::ios;
using std::bitset;

/**
 * @brief used to load files that contain puzzles
 * 
 */
class Puzzles
{
public:
	Puzzles();
	Puzzles(string fname);
	uint32_t getNumberOfPuzzles(void);
	string getPuzzle(uint32_t num);
	uint32_t loadFromFile(string fname);
private:
	string filename;
	vector<string> puzzles;
	uint32_t numPuzzles;
};

#endif //_PUZZLES