/*
 * minmaxAB.cpp
 *
 *  Created on: Mar 25, 2012
 *      Author: dgodwin
 */

#include <iostream>
#include <vector>
#include <stack>
#include "evaluator.h"
#include "minMaxAB.h"

using namespace std;

vector<int> position;

bool hasWinner(vector<int> board) {
	//Test all player 1 wins
	if (	(board[8] == 1 && board[3] == 1 && board[4] == 1) ||
			(board[8] == 1 && board[5] == 1 && board[2] == 1) ||
			(board[8] == 1 && board[1] == 1 && board[6] == 1) ||
			(board[3] == 1 && board[5] == 1 && board[7] == 1) ||
			(board[4] == 1 && board[9] == 1 && board[2] == 1) ||
			(board[1] == 1 && board[5] == 1 && board[9] == 1) ||
			(board[4] == 1 && board[5] == 1 && board[6] == 1) ||
			(board[6] == 1 && board[7] == 1 && board[2] == 1) ||
			(board[8] == 2 && board[3] == 2 && board[4] == 2) ||
			(board[8] == 2 && board[5] == 2 && board[2] == 2) ||
			(board[8] == 2 && board[1] == 2 && board[6] == 2) ||
			(board[3] == 2 && board[5] == 2 && board[7] == 2) ||
			(board[4] == 2 && board[9] == 2 && board[2] == 2) ||
			(board[1] == 2 && board[5] == 2 && board[9] == 2) ||
			(board[4] == 2 && board[5] == 2 && board[6] == 2) ||
			(board[6] == 2 && board[7] == 2 && board[2] == 2)
		) return true;
	return false;
}

bool deepEnough(vector<int> position, int depth) {
	//Just a stub. Depth hardcoded @ 3
	if (depth > 5)	return true;
	if (hasWinner(position)) return true;
	return false;
}

vector<vector <int> > moveGen(vector<int> position, int player) {
	//Return a vector of all possible moves for evaluation
	vector<vector <int> > results;
	results.clear();
	if (hasWinner(position)) return results;

	//Scan through the current position. For every blank square, add that potential move to the results
	for (int i = 1; (int) i < 10; i++) {
		if (position[i] == 0) {
			//Make a copy of the board, set the move and add to the
			vector<int> boardCopy = position;
			boardCopy[0] = i;
			boardCopy[i] = player;
			results.push_back(boardCopy);
		}
	}
	return results;
}

int oppositePlayer(int player) {
	//If player 1, return player 2.
	if (player == 1) return 2;
	//Otherwise, return player 1
	else return 1;
}

result minMaxABAlg::minMaxAB(vector<int> position, int depth, int player, int useThresh, int passThresh, int evalFunction = 1) {
//result minMaxAB(vector<int> position, int depth, int player, int useThresh, int passThresh) {
	//cout << "In MinMaxAB. depth: " << depth << " player:" << player << " UseThresh:" << useThresh << " PassThresh:" <<passThresh << endl;
	result res;
	stack<int> bestPath;
	//bestPath.push(position[0]);

	/* 1. If DEEP-ENOUGH(Position, Depth), then return the structure
        	VALUE = STATlC (Position, Player);
        	PATH = nil
	 */
	if (deepEnough(position, depth)) {
		//cout << "deep enough" << endl;
		res.score = Evaluator::evaluate(position, player, evalFunction);
		res.path.push(position[0]);
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
		//cout << "no successors" << endl;
		res.score = Evaluator::evaluate(position, player, evalFunction);
		res.path.push(position[0]);
		return res;
	}
	/*4. If SUCCESSORS is not empty, then go through it, examining each element and keeping track of the best
	 * one. This is done as follows.
	 * For each element SUCC of SUCCESSORS:
	 */
	//cout << "looping through successors" << endl;
	for (vector<vector <int> >::iterator it = successors.begin(); it != successors.end(); ++it) {
		//(a) Set RESULT-SUCC to MINIMAX-A-B(SUCC, Depth + 1, OPPOSlTE (Player),- Pass-Thresh, - Use-Thresh).
		result resultSucc = minMaxAB(*it, depth+1, oppositePlayer(player), passThresh*-1, useThresh*-1);

		//(b) Set NEW-VALUE to - VALUE(RESULT-SUCC).
		int newValue = resultSucc.score * -1;

		//(c) If NEW-VALUE> Pass-Thresh, then we have found a successor that is better than any that have
		// been examined so far. Record this by doing the following.
		//if ((newValue > passThresh && depth > 0) || (newValue >= passThresh && depth == 0)) {
		if (newValue > passThresh) {
		//cout << "Updating passThresh from: "<< passThresh << " to: " << newValue << endl;
			//(i) Set Pass-Thresh to NEW-VALUE.
			passThresh = newValue;

			/*(ii) The best known path is now from CURRENT to SUCC and then on to the appropriate path
           from SUCC as determined by the recursive call to MINIMAX-A-B. So set BEST-PATH to
           the result of attaching SUCC to the front of PATH(RESULT-SUCC).
			 */
			bestPath = resultSucc.path;
			bestPath.push(it->at(0));
			//cout << bestPath.top();
		}

		/*(d) If Pass-Thresh (reflecting the current best value) is not better than Use-Thresh, then we should
           stop examining this branch. But both thresholds and values have been inverted. So if Pass-Thresh
           >= Use-Thresh, then return immediately with the value
                     VALUE = Pass-Thresh
                     PATH = BEST-PATH
		 */
		if (passThresh >= useThresh) {
			//cout << "returning here!";
			res.score = passThresh;
			res.path = bestPath;
			res.path.push(it->at(0));
			return res;
		}
	}
	//cout << "done looping" << endl;
	/*5. Return the structure
     VALUE = Pass-Thresh
     PATH = BEST-PATH
     */
	res.score = passThresh;
	//if (bestPath.empty()) bestPath.push(successors.begin()->at(0));
	res.path = bestPath;
	//if (res.path.top() == 0) cout << "path is 0 in 5!! Score is : " << res.score << endl;
	return res;
}

