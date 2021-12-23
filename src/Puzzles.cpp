
#include <stdio.h>
#include <stdlib.h>

#include "Puzzles.h"

Puzzles::Puzzles()
{
	numPuzzles = 0;
	filename = "";
}

Puzzles::Puzzles(string fname)
{
	loadFromFile(fname);
}
// Loaded 100 		puzzles in 0.784945 msec, 7.849450 usec/puzzle
// Loaded 1000		puzzles in 2.524844 msec, 2.524844 usec/puzzle
// Loaded 10000 	puzzles in 16.981709 msec, 1.698171 usec/puzzle
// Loaded 100000 	puzzles in 113.327293 msec, 1.133273 usec/puzzle
// Loaded 1000000 	puzzles in 1011.960570 msec, 1.011961 usec/puzzle
// Loaded 10000000 	puzzles in 10631.764658 msec, 1.063176 usec/puzzle
//
// no parsing 
// Loaded 98 		puzzles in 0.200389 msec, 2.044786 usec/puzzle
// Loaded 1000 		puzzles in 0.492581 msec, 0.492581 usec/puzzle
// Loaded 10000 	puzzles in 3.780550 msec, 0.378055 usec/puzzle
// Loaded 100000 	puzzles in 46.391303 msec, 0.463913 usec/puzzle
// Loaded 1000000 	puzzles in 490.999241 msec, 0.490999 usec/puzzle
// Loaded 10000000 	puzzles in 3356.943211 msec, 0.335694 usec/puzzle
uint32_t Puzzles::loadFromFile(string fname)
{
	filename = fname;
	fstream file;
	file.open(filename, ios::in);
	if (file.is_open()) {
		puzzles.clear();
	 	string str;
	 	while (getline(file, str)) {
	 		puzzles.push_back(str);
	 	}
	} else {
	 	printf("File %s does not exist\n", fname.c_str());
		filename = "";
		numPuzzles = 0;
	}
	numPuzzles = (uint32_t)puzzles.size();
	return numPuzzles;
}

uint32_t Puzzles::getNumberOfPuzzles(void)
{
	return numPuzzles;
}

string Puzzles::getPuzzle(uint32_t num)
{
	return puzzles[num];
}
