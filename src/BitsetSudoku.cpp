// vcSudoku.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <string>
#include <vector>
#include <iostream>
using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::min;
using std::max;

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

string p1 = "....1..75....8.6..9....5...4.2...561..1.2..9..9...1.32.7.1.2.8458.67...312.3.....";
string p2 = "5.7....61...76.8...6..8...4.....3....5..4...949.6.2..814..5...6.79........5.18..2";
string p3 = "6..4....5.92.3.....4.76.23.......37..6...1.2.329.......1.....829.3...5...7451...3";
string s1 = "248916375357284619916735248432897561861523497795461832673152984584679123129348756";
string s2 = "587324961914765823362189754821593647756841239493672518148257396279436185635918472";
string s3 = "631482795792135648845769231158296374467351829329847156516973482983624517274518963";


// Loaded 100 		puzzles in 0.784945 msec, 7.849450 usec/puzzle
// Loaded 1000 		puzzles in 2.524844 msec, 2.524844 usec/puzzle
// Loaded 10000 	puzzles in 16.981709 msec, 1.698171 usec/puzzle
// Loaded 100000 	puzzles in 113.327293 msec, 1.133273 usec/puzzle
// Loaded 1000000 	puzzles in 1011.960570 msec, 1.011961 usec/puzzle
// Loaded 10000000 	puzzles in 10631.764658 msec, 1.063176 usec/puzzle

// 100P 0 ..4.83..2.51..43......9671.12.8....6.4....5..83.6.79...6.3.9.4...7...2.5.9..5.8.3
#define SHORTMAIN
#ifdef SHORTMAIN
int main() {
	Puzzles p("../../sudoku-puzzles/10MP.txt");
	Puzzles sol("../../sudoku-puzzles/10MS.txt");
	printf("%d puzzles loaded\n", p.getNumberOfPuzzles());
	printf("%d solutions loaded\n", sol.getNumberOfPuzzles());
	
	Sudoku s;
	Sudoku sols;
	uint32_t matched = 0;
	uint32_t notmatched = 0;
	uint32_t i;
	for(i = 0; i < p.getNumberOfPuzzles() ; i++) {
		s.setPuzzle(p.getPuzzle(0));
		s.solvePuzzle();
		sols.setPuzzle(sol.getPuzzle(0));
		if( s.puzzle == sols.puzzle)
			matched++;
		else
			notmatched++;
		if ((i+1) % 50000 == 0)
			printf("%7d - %7d - %7d\n", i+1, matched, notmatched);
	}
	printf("done %7d puzzles- %7d matched - %7d not matched\n", i+1, matched, notmatched);
	
}

#else

int main()
{

	Puzzles p;
	Puzzles pf("../../sudoku-puzzles/1MP.txt");
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
//max time puzzle 140632 1.3599
//min time puzzle 644634 0.006723 
		minTime = min(minTime, time);
        maxTime = max(maxTime, time);
		if(time == minTime) cout << "min time puzzle " << i << " " << minTime*1000.0 << endl;
		if(time == maxTime) cout << "max time puzzle " << i << " " << maxTime*1000.0 << endl;
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
// 1MP old way			Min time: 0.021334 ms, Max time: 5.1635 ms, Average Time: 0.0305412 ms, Total: 66.192528 sec
// 1MP bit round 1 		Min time: 0.006958 ms, Max time: 12.3362 ms, Average Time: 0.00862062 ms, Total: 13.802928 sec
