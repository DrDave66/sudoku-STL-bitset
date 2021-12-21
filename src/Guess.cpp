#include "Guess.h"

Guess::Guess(RowCol _square, char _guess,SUDOKUTYPE _puzzle, SUDOKUTYPE _allowableValues) {
    puzzle = _puzzle;
    allowableValues = _allowableValues;
    square = _square;
	guess = _guess;
}

Guess::Guess() {
    for(int16_t r = 0 ; r < 9 ; r++) {
        for(int16_t c = 0 ; c < 9 ; c++) {
            puzzle[r][c] = '\0';
            allowableValues[r][c] = '\0';
        }
        
    }
	square = RowCol();
	guess = '\0';
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
    sprintf(ss,"Square: %s, Guess: %c,\n",square.toString().c_str(), guess);
	string retval;
	return retval;
}