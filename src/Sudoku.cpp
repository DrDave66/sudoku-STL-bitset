/**
 * @file Sudoku.cpp
 * @author Dave Landis
 * @brief Implements a Sudoku puzzle solver
 * @version 0.1
 * @date 2021-12-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "Sudoku.h"

#define noPRINTVECTORS
/**
 * @brief Construct a new Sudoku:: Sudoku object
 * 
 */
Sudoku::Sudoku() {
	createVectors();
	clearPuzzle();
    //seed PRNG
	srand((uint32_t)time(NULL));
}

/**
 * @brief Construct a new Sudoku:: Sudoku object given a puzzle string
 * 
 * @param puzzle 
 */
Sudoku::Sudoku(string puzzle) {
	createVectors();
	setPuzzle(puzzle);
    // seed PRNG
	srand((uint32_t)time(NULL));
}

#define noPRINTVECTORS
/**
 * @brief constructs all of the RowCol arrays we need for later looping
 *          
 * This is a difficult implementation to follow.  I had a nice implmentation
 * in Python that worked.  Rather an fully reimplement it, i used the concepts
 * from the Python verison (which referred to cells (e.g. "A1") as string for 
 * use as keys in map variables) rather than reimplement from scratch.
 */
void Sudoku::createVectors(void) {
	uint8_t i;
    for(i = 0 ; i < 9 ;i++) {
        rows[i] = i;
        cols[i] = i;
        bits[i] = i;
    }
    vector<RowCol> rcv;
    for(auto b:bits) {
        bitMask[b].reset();
        bitMask[b].set(b);
    }
    // init the puzzle and allowableValues array
    for (auto r:rows) {
        for (auto c:cols) {
            puzzle[r][c].reset();
            allowableValues[r][c].set();
        }
    }
    // create unitlist array
	vector<RowCol> temp;
	uint8_t ul = 0;
    array<RowCol,9> ts;
    vector<uint8_t> v1;
    ul = 0;
  	// for each col across the rows
    // crossProduct routine needs two iterables, so create a one element vector
	for (auto c : cols) {
        v1.clear();
        v1.push_back(c);
		temp = crossProduct(rows, v1);
        i = 0;
        for (RowCol s : temp) {
            unitList[ul][i] = s;
            i++;
        }
        ul++;
	}
// for each row across the cols
	for (auto r : rows) {
        v1.clear();
        v1.push_back(r);
		temp = crossProduct(v1, rows);
        i = 0;
        for (RowCol s : temp) {
            unitList[ul][i] = s;
            i++;
        }
        ul++;
    }
    // for each 3x3 square
	vector<vector<uint8_t> > sr;
    vector<vector<uint8_t> > sc;
    sr.push_back(vector<uint8_t> {0,1,2});
	sr.push_back(vector<uint8_t> {3,4,5});
	sr.push_back(vector<uint8_t> {6,7,8});
	sc.push_back(vector<uint8_t> {0,1,2});
	sc.push_back(vector<uint8_t> {3,4,5});
	sc.push_back(vector<uint8_t> {6,7,8});
	for (vector<uint8_t> r : sr) {
		for (vector<uint8_t> c : sc) {
            i = 0;
            temp = crossProduct(r,c);
            for (RowCol s : temp) {
                unitList[ul][i] = s;
                i++;
            }
            ul++;
        }
	}
#ifdef PRINTVECTORS
    cout << endl << "UnitList" << endl;
    for(uint8_t j = 0 ; j < 27 ; j++) {
        for (i = 0 ; i < 9 ;i++) {
            cout << unitList[j][i] << " ";
        }
        cout << endl;
    }
    cout << endl << endl;
#endif
//  create units
    RowCol sq;
	uint8_t unum = 0;
    for(auto r : rows) {
        for (auto c : cols) {
            unum = 0;
            sq.set(r,c);
            for (array<RowCol,9> ul : unitList){
                for(i = 0 ; i < 9 ; i++) {
                    if (ul[i] == sq) {
                        units[r][c][unum] = ul;
                        unum++;
                    }
                }
            }
        }
    }
#ifdef PRINTVECTORS
    cout << endl << endl;
    for (auto r : rows) {
        for (auto c : cols) {
            sq.set(r,c);
            cout << "New Unit Dict: " << sq << " " << endl;
            for ( int unum = 0 ; unum < 3 ; unum++) {
                for (i = 0 ; i < 9 ; i++) {
                    cout << units[r][c][unum][i] << " ";
                }
                cout << endl;
            }
            cout << endl;
        }
    }
#endif
// make peer array
    int pnum = 0;
    // use a set so that each value can only appear once
    set<RowCol> peerSet;
    for(auto r : rows) {
        for (auto c : cols) {
            pnum = 0;
            peerSet.clear();
            sq.set(r,c);
            for(array<RowCol,9> ul : units[r][c]) {
                for(RowCol u : ul) {
                    if (u != sq) {
                        peerSet.insert((const RowCol)u);
                    }
                }
            }
            for(RowCol ps : peerSet) {
                peers[r][c][pnum] = ps;
                pnum++;
            }
        }
    }

#ifdef PRINTVECTORS
    for (auto r:rows) {
        for(auto c:cols) {
            cout << RowCol(r,c) << " - ";
            for(RowCol p:peers[r][c]) {
                cout << p.toString() << " ";
            }
            cout << endl;
        }
    }
#endif
}

/**
 * @brief Clears the puzzle and allowableValue members
 * 
 */
void Sudoku::clearPuzzle(void) {
    for(auto r:rows) {
        for(auto c:cols) {
            puzzle[r][c].reset();
            allowableValues[r][c].set();
        }
    }
}

/**
 * @brief Sets a puzzle from a string
 * 
 * @param string Text string of 81 or more characters
 * @return true if successful
 * @return false if conflict
 * 
 * use a '.' character to represent a blank cell
 * example: "..3.2.6..9..3.5..1..18.64....81.29..7.......8..67.82....26.95..8..2.3..9..5.1.3.."
 */
bool Sudoku::setPuzzle(string p) {
    char v;
    uint8_t b;
    if(p.size() < 81)
        return false;
    clearPuzzle();

    for(auto r:rows) {
        for(auto c:cols) {
            v = p[c + r*9];
            if (v == '.')
                b = 10;
            else
                b = (v - '1') ;
            if(setValue(r,c,b) == false) {
                return false;
            }
        }
    }
	return true;
}

/**********************************************************
**********   Printing Functions ***************************
***********************************************************/

/**
 * @brief Print a puzzle with a title
 * 
 * @param string Title for the puzzle
 */
void Sudoku::printPuzzle(string title) {
	cout << endl << title;
	printPuzzle();
}

/**
 * @brief Prints a formatted puzzle representation
 * 
 */
void Sudoku::printPuzzle(void) {
	string header = "     1   2   3    4   5   6    7   8   9";
	string top = "  =========================================";
	string row_sep = "  || --------- || --------- || --------- ||";
	string col_sep = "||";
	string num_sep = "|";
	cout << endl << header << endl;
	cout << top << endl;
	uint32_t col_num = -1;
	uint32_t row_num = -1;
	string index;
	for (auto r : rows) {
		cout << (char)('A' + r) << " " << col_sep;
		for (auto c : cols) {
			if (puzzle[r][c].none()) {
				cout << " .";
			}
			else {
				for(auto b:bits) {
					if(puzzle[r][c].test(b)) {
						cout << " " << b+1;
					}
				}
			}
			if (col_num > 0 && (col_num - 1) % 3 == 0) {
				cout << " " << col_sep;
			}
			else {
				cout << " " << num_sep;
			}
			col_num++;
		}
		row_num++;
		cout << endl;
		if (row_num == 8) {
			cout << top << endl;
		}
		else if ((row_num + 1) % 3 == 0) {
			cout << row_sep << endl;
		}
    }
}

/**
 * @brief prints a formatted allowable value matrix
 * 
 */
void Sudoku::printAllowableValues(void) {
	string header = "         1           2           3            4           5           6            7           8           9";
	string top = "  =================================================================================================================";
	string row_sep = "  || --------------------------------- || --------------------------------- || --------------------------------- ||";
	string col_sep = "||";
	string num_sep = "|";
	cout << endl << header << endl;
	cout << top << endl;
	uint32_t col_num = -1;
	uint32_t row_num = -1;
	string outstr;
	for (auto r : rows) {
		cout << (char)('A' + r) << " " << col_sep;
		for (auto c : cols) {
			if (puzzle[r][c].any()) {
				outstr = " ";
			}
			else {
                stringstream ss;
                for(auto b:bits) {
                    if(allowableValues[r][c].test(b)) {
                        ss << int(b+1);
                    }
                }
                outstr = ss.str();
			}
            cout << setw(10);
            cout <<  outstr;
            cout << setw(1);
			if (col_num > 0 && (col_num - 1) % 3 == 0) {
				cout << " " << col_sep;
			}
			else {
				cout << " " << num_sep;
			}
			col_num++;
		}
		row_num++;
		cout << endl;
		if (row_num == 8) {
			cout << top << endl;
		}
		else if ((row_num + 1) % 3 == 0) {
			cout << row_sep << endl;
		}

	}
}

/**
 * @brief Prints formatted allowable value matrix with title   
 * 
 * @param string The title for the allowable value matrix 
 */
void Sudoku::printAllowableValues(string title) {
	cout << endl << title;
	printAllowableValues();
}

/**********************************************************
 **********   Solving Functions ***************************
***********************************************************/

/**
 * @brief Sets the value of a cell in a puzzle
 * 
 * @param r the cell's row
 * @param c the cell's column
 * @param bb a bitmask of the value to be set, 1 indicates bit to be set. send a value of 10 to indicate blank cell
 * @return true if successful
 * @return false if fails
 */
bool Sudoku::setValue(uint8_t r, uint8_t c, uint8_t bb) {
    RowCol rc(r,c);
	uint8_t rr,cc;
    if (bb == 10) { // if value is empty
        puzzle[r][c].reset();
        return true;
    } else { // if value is real
        // make sure the value is allowed to be set
        if (allowableValues[r][c].test(bb) == false ) {
            // if not, return value
            return false;
        }
        // set value and clear allowableValues
        puzzle[r][c] = bitMask[bb];
        allowableValues[r][c] = 0;
    }
    // propagate value to all peers, removing it from their allowable values
	for (RowCol p : peers[r][c]) {
        rr = p.row;
        cc = p.col;
        allowableValues[rr][cc].reset(bb);
    }
	return true;
}

/**
 * @brief set value using RowCol and a bitset<9> for the value (comes from guessing)
 * 
 * @param rc RowCol of cell
 * @param bit bitset indicating which bit to set
 * @return true if successful
 * @return false if failed
 */
bool Sudoku::setValue(RowCol rc, bitset<9> bit) {
    return setValue(rc.row, rc.col, singleBitSet(bit));
}

/**
 * @brief solves for cells with a single available value, then for units
 * with only one occurance of a particular value
 * 
 */
void Sudoku::solveOnes(void) {
 	bool solvedSome = true; // set to true to allow one iteration
	while (solvedSome == true ) { // we don't want to keep doing this if we are not finding solutions
        while(solvedSome == true) {
            solvedSome = false; // set to false.  will be set to true if a value is set
            // find squares with only one available value
            for (auto r:rows){
                for (auto c:cols) {
                    if (allowableValues[r][c].count() == 1) { // if cell has only one available value
                        solvedSome = true; // set flag to repeat loop
                        setValue(r, c, singleBitSet(allowableValues[r][c])); // set the value
                    }
                }
            }
        }
        if(isPuzzleSolved() == true) // if solved, return true
            return;
        // now look through all units for a value that has only one occurance
        uint8_t bitCount;
        for(auto b:bits) { // loop through all digits
            for (array<RowCol,9> ul : unitList) { // loop through all unitlists
                bitCount = 0;
                for(RowCol rc:ul) { // loops through all RowCols in each unit
                    bitCount += allowableValues[rc.row][rc.col][b]; // add up number of times bit it set
                    if(bitCount > 1) {
                        break;
                    }
                }
                if (bitCount == 1) { // if bit is only set once
                    for(RowCol rc:ul) {
                        if(allowableValues[rc.row][rc.col].test(b) == 1) { // find where the bit was set
                            setValue(rc.row, rc.col,b); // and set the value
                            solvedSome = true; // flag to repeat loop
                        }
                    }
                }
            }
        }
	}
    return;
}

/**
 * @brief determine if a puzzle is solved.  each unit should have all possible values
 * 
 * @return true 
 * @return false 
 */
bool Sudoku::isPuzzleSolved(void) {
// a puzzle is solved if each unit in unitlist contains values of 1-9
    bitset<9> bs = 0; // an accumulator for the bits set
	for (array<RowCol, 9> ul : unitList) { // for each unit in the unitlist
        bs.reset(); // clear accumulator
		for (RowCol rc : ul) { // for each cell in the unit
			bs |= puzzle[rc.row][rc.col]; // or its set bit
		}
        if(bs != 0b11'1111'1111) // if all bits are not set, return false
            return false;
	}
    return true; // if we get here, all bits were set in all units
}

/**
 * @brief removes a potential guess because it was found to be not allowable
 * 
 * @param rc RowCol of guess
 * @param b Value of guess
 * @return true if successful
 * @return false if the allowableValue element does not permit that bit to be guessed (never happens)
 */
bool Sudoku::removeGuess(RowCol rc, bitset<9> b){
    if((allowableValues[rc.row][rc.col] & b) == 0) // if guess is not allowable, return value
        return false;
    else {
        allowableValues[rc.row][rc.col] &= b.flip(); // clear the bit for the value that was guessed
        return true;
    }
}

/**
 * @brief determines if guesses remain in the puzzle
 * 
 * @return bool true if yes, false if no
 */
bool Sudoku::guessesRemain(void) {
    for(auto r:rows) {
        for (auto c:cols) {
            if(allowableValues[r][c].count() > 1)
                return true;
        }
	}
	return false;
}

/**
 * @brief returns a new guess
 * 
 * @return Guess the guess that was made, includes row, col, value, and puzzle state
 */
Guess Sudoku::getGuess() { // returns square, value
	// guess is returned as square,value in an array of bits
	uint8_t minCount = 9;
	// iterate through squares and get lowest count > 1
	uint8_t len;
    for(auto r:rows) {
        for (auto c:cols) {
            len = (uint8_t)allowableValues[r][c].count();
            if ( len > 1 ) {
                if (len < minCount)
                {
                    minCount = len;
                }
            }
        }
	}
    // now that we have minCount, find all cells with that count
    // must be a vector as we don't know the size
	vector<RowCol> subset;
    for(auto r:rows) {
        for (auto c:cols) {
            if (allowableValues[r][c].count() == minCount) {
                subset.push_back(RowCol(r,c));
            }
        }
    }
	// select random vector
	RowCol square = subset[rand() % subset.size()];
    // select random bit
    vector<uint8_t> vBits;
    for(auto b:bits) {
        if(allowableValues[square.row][square.col].test(b) == true) {
            vBits.push_back(b);
        }
    }
    // pick random bit
    uint8_t t = vBits[rand() % vBits.size()];
	return Guess(square, bitMask[t], puzzle, allowableValues);
}

/**
 * @brief remove a guess from the list, restore puzzle state, and remove guess from allowableValues
 * 
 * @return bool false if stack is empty, true otherwise
 */
bool Sudoku::popGuess() {
    if(guessNumber == 0)
        return false;
    guessNumber--;
    Guess lastGuess;
    lastGuess = guessList[guessNumber];
    puzzle = lastGuess.puzzle;
    allowableValues = lastGuess.allowableValues;
    removeGuess(lastGuess.square, lastGuess.guess);
	return true;
}

/**
 * @brief adds a guess to the guess list
 * 
 * @param guess Guess class representing the guess, includes puzzle state
 */
void Sudoku::pushGuess(const Guess guess) {
	guessList[guessNumber] = guess;
    guessNumber++;
}

/**
 * @brief prints out a guess list
 * 
 */
void Sudoku::printGuessList() {
    if (guessNumber == 0)
        cout << "Empty";
    else {
        for(uint8_t i = 0 ; i < guessNumber ; i++) {
            cout << guessList[i].square << ":" << guessList[i].guess << " ";
        }
    }
	cout << endl << flush;
}

/**
 * @brief main routine for solving a puzzle.  
 * 
 * @return bool true if puzzle solved, false otherwise
 */
bool Sudoku::solvePuzzle() {
	solveOnes();
	if (isPuzzleSolved())
		return true;
	else {
        startGuessing();
    }
	return isPuzzleSolved();
}

/**
 * @brief implements guessing loop
 * 
 * @return bool returns if puzle was solved
 */
bool Sudoku::startGuessing() {
	while(!isPuzzleSolved()) { // while puzzle is not solved
		while (guessesRemain()) { // while there are guesses
			Guess g = getGuess(); // make a guess
			pushGuess(g); // store it on the guess list
			setValue(g.square, g.guess); // set the value
			solveOnes(); // solve for unique answers or unique in set
			if (isPuzzleSolved() == false && guessesRemain() == false) { // if we are out of guesses
				popGuess(); // remove last guess
			}
		}
        // after removing a guess, if no guesses remain, we must remove another guess.  this
        // propagates back up the binary tree for searching
		if (isPuzzleSolved() == false) {
			if(popGuess() == false) {
				return false;
			}
		}
	}
	return isPuzzleSolved();
}

/**
 * @brief called after we determine only one bit is set, and returns the set bit
 * 
 * @param bs a bitset<9>
 * @return uint8_t which bit is set
 */
uint8_t Sudoku::singleBitSet(bitset<9> bs) {
	for(auto b:bits) {
		if(bs.test(b)) return b;
	}
	return 0;
}
