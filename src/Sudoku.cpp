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

#define NOTIMING
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
 */
void Sudoku::createVectors(void) {
	uint8_t i;
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

void Sudoku::clearPuzzle(void) {
    for(auto r:rows) {
        for(auto c:cols) {
            puzzle[r][c].reset();
            allowableValues[r][c].set();
        }
    }
}

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
            setValue(r,c,b);
        }
    }
	return true;
}

/**********************************************************
**********   Printing Functions ***************************
***********************************************************/

void Sudoku::printPuzzle(string title) {
	cout << endl << title;
	printPuzzle();
}

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

void Sudoku::printAllowableValues(string title) {
	cout << endl << title;
	printAllowableValues();
}

/**********************************************************
 **********   Solving Functions ***************************
***********************************************************/

bool Sudoku::setValue(uint8_t r, uint8_t c, uint8_t bb) {
#ifdef TIMING
	PrecisionTimeLapse ptl;
	ptl.start();
#endif 	
    RowCol rc(r,c);
	uint8_t rr,cc;
    if (bb == 10) {
        puzzle[r][c].reset();
        return true;
    } else {
        if (allowableValues[r][c].test(bb) == false ) {
            return false;
        }
        allowableValues[r][c] = 0;
        puzzle[r][c] = bitMask[bb];
    }
	for (RowCol p : peers[r][c]) {
        rr = p.row;
        cc = p.col;
        allowableValues[rr][cc].reset(bb);
    }
// #ifdef TIMING
// 	ptl.stop();
// 	cout << "setValue," << ptl.elapsedString() << endl;
// #endif
	return true;
}

bool Sudoku::setValue(RowCol rc, bitset<9> bit) {
    return setValue(rc.row, rc.col, singleBitSet(bit));
}

void Sudoku::solveOnes(void) {
#ifdef TIMING	
	PrecisionTimeLapse ptl;
	ptl.start();
#endif	
 	bool solvedSome = true;
	while (solvedSome == true ) {
        while(solvedSome == true) {
            solvedSome = false;
            // find squares with only one available value
            for (auto r:rows){
                for (auto c:cols) {
                    if (allowableValues[r][c].count() == 1) {
                        // and set the value
                        solvedSome = true;
                        setValue(r, c, singleBitSet(allowableValues[r][c]));
                    }
                }
            }
        }
        if(isPuzzleSolved() == true)
            return;
        uint8_t bitCount;
        for(auto b:bits) {
            for (array<RowCol,9> ul : unitList) {
                bitCount = 0;
                for(RowCol rc:ul) {
                    bitCount += allowableValues[rc.row][rc.col][b];
                    if(bitCount > 1) {
                        break;
                    }
                }
                if (bitCount == 1) {
                    for(RowCol rc:ul) {
                        if(allowableValues[rc.row][rc.col].test(b) == 1) {
                            setValue(rc.row, rc.col,b);
                            solvedSome = true;
                        }
                    }
                }
            }
        }
	}
#ifdef TIMING
	ptl.stop();
	cout << "solveOnes,"  << ptl.elapsedString() << endl;
#endif
    return;
}

bool Sudoku::isPuzzleSolved(void) {
// a puzzle is solved if each unit in unitlist contains values of 1-9
    bitset<9> bs = 0;
	for (array<RowCol, 9> ul : unitList) {
        bs.reset();
		for (RowCol rc : ul) {
			bs |= puzzle[rc.row][rc.col];
		}
        if(bs != 0b11'1111'1111)
            return false;
	}
    return true;
}

bool Sudoku::removeGuess(RowCol rc, bitset<9> b){
    if((allowableValues[rc.row][rc.col] & b) == 0)
        return false;
    else {
        allowableValues[rc.row][rc.col] &= b.flip();
        return true;
    }
}

bool Sudoku::guessesRemain(void) {
    for(auto r:rows) {
        for (auto c:cols) {
            if(allowableValues[r][c].count() > 1)
                return true;
        }
	}
	return false;
}

Guess Sudoku::getGuess() { // returns square, value
	// guess is returned as square,value in an array
	uint8_t minCount = 9;
	// iterate through squares and get lowest count > 1
	size_t len;
//    printAllowableValues();
//    printGuessList();
    for(auto r:rows) {
        for (auto c:cols) {
            len = allowableValues[r][c].count();
            if ( len > 1 ) {
                if (len < minCount)
                {
                    minCount = (uint8_t)len;
                }
            }
        }
	}
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
    uint8_t t = vBits[rand() % vBits.size()];
	//newGuess = Guess(square, string(1,t), puzzle, allowableValues);
	return Guess(square, bitMask[t], puzzle, allowableValues);
}


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

void Sudoku::pushGuess(const Guess guess) {
	guessList[guessNumber] = guess;
    guessNumber++;
    //printGuessList();
}

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

bool Sudoku::solvePuzzle() {
	solveOnes();
	if (isPuzzleSolved())
		return true;
	else 
		startGuessing();
	return isPuzzleSolved();
}

bool Sudoku::startGuessing() {
	guessNumber = 0;
	while(!isPuzzleSolved()) {
		while (guessesRemain()) {
			Guess g = getGuess();
			pushGuess(g);
			setValue(g.square, g.guess);
			solveOnes();
			if (isPuzzleSolved() == false && guessesRemain() == false) {
				popGuess();
			}
		}
		if (isPuzzleSolved() == false) {
			if (guessList.size() == 0) {
			}
			if(popGuess() == false) {
				return false;
			}
		}
			
	}
	return isPuzzleSolved();
}

uint8_t Sudoku::numberOfBitsSet(bitset<9> bs) {
    //return (uint8_t)bs.count();
	uint8_t retval = 0;
	 for(auto b:bits) {
	 	if(bs.test(b)) 
	 		retval++;
	 }
	 return retval;
}

uint8_t Sudoku::singleBitSet(bitset<9> bs) {
	for(auto b:bits) {
		if(bs.test(b)) return b;
	}
	return 0;
}
void Sudoku::test(void) {

 }
