/*
 * minmaxAB.cpp
 *
 *  Created on: Mar 25, 2012
 *      Author: dgodwin
 */

#include <iostream>
#include <vector>
using namespace std;

vector<int> position;

struct result {
	int score;
	string path;
};

bool deepEnough(vector<int> position, int depth) {
	//Just a stub
	return true;
}

vector<vector <int> > moveGen(vector<int> position, int player) {
	//Just a stub
	vector<vector <int> > results;
	return results;
}

int oppositePlayer(int player) {
	//Just a stub
	return 1;
}

result minMaxAB(vector<int> position, int depth, int player, int useThresh, int passThresh) {
	result res;
	string bestPath = '';
	/* 1. If DEEP-ENOUGH(Position, Depth), then return the structure
        	VALUE = STATlC (Position, Player);
        	PATH = nil
	 */
	if (deepEnough(position, depth)) {
		res.score = 0; //Evaluate(Position, Player)
		res.path = '';
		return res;
	}

	/* 2. Otherwise, generate one more ply of the tree by calling the function MOVE-GEN(Position, Player)
	 * and setting SUCCESSORS to the list it returns.
	 */
	vector<vector <int> > successors;
	successors = moveGen(position, player);

	/* 3.If SUCCESSORS is empty, there are no moves to be made;
	 * return the same structure that 	would have been returned if DEEP-ENOUGH had returned TRUE.
	 */
	if ((int) successors.empty()) {
		res.score = 0; //Evaluate(Position, Player)
		res.path = '';
		return res;
	}
	/*4. If SUCCESSORS is not empty, then go through it, examining each element and keeping track of the best
	 * one. This is done as follows.
	 * For each element SUCC of SUCCESSORS:
	 */
	for (vector<vector <int> >::iterator it = successors.begin(); it != successors.end(); ++it) {
		//(a) Set RESULT-SUCC to MINIMAX-A-B(SUCC, Depth + 1, OPPOSlTE (Player),- Pass-Thresh, - Use-Thresh).
		result resultSucc = minMaxAB(*it, depth+1, oppositePlayer(player), useThresh*-1, passThresh*-1);

		//(b) Set NEW-VALUE to - VALUE(RESULT-SUCC).
		int newValue = resultSucc.score * -1;

		//(c) If NEW-VALUE> Pass-Thresh, then we have found a successor that is better than any that have
		// been examined so far. Record this by doing the following.
		if (newValue > passThresh) {
			//(i) Set Pass-Thresh to NEW-VALUE.
			passThresh = newValue;

			/*(ii) The best known path is now from CURRENT to SUCC and then on to the appropriate path
           from SUCC as determined by the recursive call to MINIMAX-A-B. So set BEST-PATH to
           the result of attaching SUCC to the front of PATH(RESULT-SUCC).
			 */
			bestPath = resultSucc.path; //Not correct. Need to figure out how to deal with the path.
		}

		/*(d) If Pass-Thresh (reflecting the current best value) is not better than Use-Thresh, then we should
           stop examining this branch. But both thresholds and values have been inverted. So if Pass-Thresh
           >= Use-Thresh, then return immediately with the value
                     VALUE = Pass-Thresh
                     PATH = BEST-PATH
		 */
		if (passThresh >= useThresh) {
			res.score = passThresh;
			res.path = bestPath;
			return res;
		}
	}
	/*5. Return the structure
     VALUE = Pass-Thresh
     PATH = BEST-PATH
     */
	res.score = passThresh;
	res.path = bestPath;
	return res;
}

