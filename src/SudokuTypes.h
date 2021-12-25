#pragma once
#ifndef _SUDOKUTYPES
#define _SUDOKUTYPES

#include <cstdint>
#include <array>
#include <bitset>

using std::array;
using std::bitset;

// this type is used for puzzle and allowableValues
// it's in a separate header beause it used to be more than just a typedef
typedef array<array<bitset<9>, 9> ,9> SUDOKUTYPE;

#endif // _SUDOKUTYPES_H