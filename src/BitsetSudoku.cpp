// vcSudoku.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <string>
#include <vector>
using namespace std;
#include "Puzzles.h"
#include "Sudoku.h"
#include "PrecisionTimeLapse.h"
#include "SudokuTypes.h"
#include "RowCol.h"
#include "Guess.h"
// solved with ones/peers
string grid1 =   "..3.2.6..9..3.5..1..18.64....81.29..7.......8..67.82....26.95..8..2.3..9..5.1.3..";
string grid3 =   "8.2.5.7.1..7.8246..1.9.....6....18325.......91843....6.....4.2..9561.3..3.8.9.6.7";
// not solved with ones/peers
string easy505 = "1..92....524.1...........7..5...81.2.........4.27...9..6...........3.945....71..6";
string grid2 =   "4.....8.5.3..........7......2.....6.....8.4......1.......6.3.7.5..2.....1.4......";
string hard1 =   ".....6....59.....82....8....45........3........6..3.54...325..6..................";
string easy506 = ".43.8.25.6.............1.949....4.7....6.8....1.2....382.5.............5.34.9.71.";
string blank =   ".................................................................................";
// solved puzzles
string solved1 = "431829765276513984598467312389251647642378591157946238964785123723194856815632479";
string solved2 = "687942351591376284342158769465239178138567942279814635853791426924683517716425893";
string solved3 = "523846917961537428487219653154693782632478195798152346879324561316985274245761839";
string solved4 = "152483679697152348438976251314765892869241735275398164786524913941837526523619487";
string solved5 = "176923584524817639893654271957348162638192457412765398265489713781236945349571826";

void printPuzzleText(Sudoku ss) {
    string s;
    for(int r = 0 ; r < 9 ; r++) {
        for (int c = 0 ; c < 9 ; c++) {
            cout << ss.puzzle[r][c];
        }
    }
    cout << endl;
}

#define SHORTMAIN
// Loaded 100 		puzzles in 0.784945 msec, 7.849450 usec/puzzle
// Loaded 1000 		puzzles in 2.524844 msec, 2.524844 usec/puzzle
// Loaded 10000 	puzzles in 16.981709 msec, 1.698171 usec/puzzle
// Loaded 100000 	puzzles in 113.327293 msec, 1.133273 usec/puzzle
// Loaded 1000000 	puzzles in 1011.960570 msec, 1.011961 usec/puzzle
// Loaded 10000000 	puzzles in 10631.764658 msec, 1.063176 usec/puzzle
array<uint8_t,9> ll = {0,1,2,3,4,5,6,7,8};
#ifdef SHORTMAIN
int main() {
	Sudoku s(solved1);
	s.clearPuzzle();
	s.printPuzzle();
	s.printAllowableValues();
	for(auto r:ll) {
		for(auto c:ll) {
			s.allowableValues[r][c].set();
			s.puzzle[r][c].reset();
			s.puzzle[r][c].set((r+c)%9);
		}
		s.printPuzzle();
		s.printAllowableValues();
	}
	s.printPuzzle();
	s.printAllowableValues();
	bitset<9> a;
	bitset<9> b;
	a=511;
	b=33;
	bitset<9> c;
	c = a ^ b;
	
	cout << a << endl;
	cout << b << endl;
	cout << c << endl;
}

#else
int main()
{

	Puzzles p;
	Puzzles pf("../sudoku-puzzles/1MP.txt");
	cout << pf.getNumberOfPuzzles() << " puzzles loaded" << endl << endl << endl;
	if (pf.getNumberOfPuzzles() == 0)
		return 1;
	Sudoku s;
	PrecisionTimeLapse total;
	PrecisionTimeLapse ptl;
	uint32_t numPuzzles = pf.getNumberOfPuzzles();
	int solved = 0;
	double minTime = 100000.0;
	double maxTime = 0.0;
	double sumTime =  0.0;
	double time;
	total.start();
	uint16_t onePercent = (uint16_t)(pf.getNumberOfPuzzles()/100);
	for (uint32_t i = 0; i < pf.getNumberOfPuzzles(); i++) {
#ifdef PRINTING
        cout << i+1 << " ";
#endif
		s.setPuzzle(pf.getPuzzle(i));
		ptl.start();
		s.solvePuzzle();
		ptl.stop();
		if (s.isPuzzleSolved() == true)
		{
   			solved += 1;
#ifdef PRINTING
			cout << "SOLVED\n";
#endif
			//s.printPuzzle();
		}
		else {
#ifdef PRINTING
			cout << "NOTSOLVED \n";
#endif
		}
		time = ptl.elapsed();

		minTime = min(minTime, time);
		maxTime = max(maxTime, time);
		sumTime += time;
		//cout << time << " " << sumTime << "  ";
		//cout << "Total time: " << ptl.elapsedString() << " solved " << solved << " out of " << i+1 << endl;
		if (i % onePercent == 0) {
			printf("%6.2f%%   \n", (double)i/(double)numPuzzles * 100);
			
		}
	}
	total.stop();
    //cout << " Total time: " << total.elapsed() << " seconds" << endl;
    cout << "Solved " << solved << " out of " << pf.getNumberOfPuzzles() << " puzzles\n";
	cout << "Min time: " << minTime*1000.0 << " ms, Max time: " << maxTime*1000.0 << " ms, Average Time: " << (double)sumTime / (double)solved * 1000 << " ms, Total: " << total.elapsedString(SEC) << " sec" << endl;

}

#endif
//  time to solve is 40 usec.  non stl is 30 usec

// 10MP-Failed.txt      Min time: 0.107397 ms, Max time: 180.694 ms, Average Time: 0.963753 ms, Total: 364.072973 sec
// 1MP.txt              Min time: 0.035211 ms, Max time: 7.05304 ms, Average Time: 0.0410138 ms, Total: 55.709054 sec

