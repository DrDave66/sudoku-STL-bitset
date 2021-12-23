#pragma once
#ifndef _SUDOKUTYPES
#define _SUDOKUTYPES

#include <cstdint>
#include <array>
#include <bitset>

using std::array;
using std::bitset;

typedef array<array<bitset<9>, 9> ,9> SUDOKUTYPE;

#endif // _SUDOKUTYPES_H