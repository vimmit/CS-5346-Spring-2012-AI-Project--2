/*
 * helper.cpp
 *
 *  Created on: Apr 10, 2012
 *      Author: dgodwin
 */

#include "helper.h"
#include <vector>
using namespace std;

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

bool deepEnough(vector<int> position, int depth, int maxDepth) {
	//Just a stub. Depth hardcoded @ 3
	if (depth > maxDepth)	return true;
	if (hasWinner(position)) return true;
	return false;
}
