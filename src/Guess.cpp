#include "Guess.h"

Guess::Guess(RowCol _square, bitset<9> _guess,SUDOKUTYPE _puzzle, SUDOKUTYPE _allowableValues) {
    puzzle = _puzzle;
    allowableValues = _allowableValues;
    square = _square;
	guess = _guess;
}
array<uint8_t,9> ii = {0,1,2,3,4,5,6,7,8};
Guess::Guess() {
//    for(auto r:ii) {
//        for(auto c:ii) {
//            puzzle[r][c] = 0;
//            allowableValues[r][c] = 511;
//        }
//        
//    }
//	square = RowCol();
//	guess = '\0';
}

Guess::Guess(const Guess& g) {
    puzzle = g.puzzle;
    allowableValues = g.allowableValues;
	square = g.square;
	guess = g.guess;
}

Guess& Guess::operator=(const Guess& cpy) {
    puzzle = cpy.puzzle;
    allowableValues = cpy.allowableValues;
	square = cpy.square;
	guess = cpy.guess;
	return *this;
}

string Guess::toString() {
	char ss[1000];
    sprintf(ss,"Square: %s, Guess: %s,\n",square.toString().c_str(), guess.to_string().c_str());
	string retval;
	return retval;
}