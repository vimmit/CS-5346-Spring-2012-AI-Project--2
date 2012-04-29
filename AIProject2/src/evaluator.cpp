/*
 * evaluator.cpp
 *
 *  Created on: Mar 30, 2012
 *      Author: dgodwin
 */

#include <vector>
#include <iostream>
#include "evaluator.h"

using namespace std;

struct winningRow {
	int a,b,c;
};

//Used to generate a vector of winningRows: 834, 816, 852, 159, 672, 357, 492, 456
void initWinningRows(vector<winningRow> &winningRows) {
	winningRow tmp;

	//1
	tmp.a = 8;
	tmp.b = 3;
	tmp.c = 4;
	winningRows.push_back(tmp);

	//2
	tmp.a = 8;
	tmp.b = 5;
	tmp.c = 2;
	winningRows.push_back(tmp);

	//3
	tmp.a = 8;
	tmp.b = 1;
	tmp.c = 6;
	winningRows.push_back(tmp);

	//4
	tmp.a = 3;
	tmp.b = 5;
	tmp.c = 7;
	winningRows.push_back(tmp);

	//5
	tmp.a = 4;
	tmp.b = 9;
	tmp.c = 2;
	winningRows.push_back(tmp);


	//6
	tmp.a = 1;
	tmp.b = 5;
	tmp.c = 9;
	winningRows.push_back(tmp);


	//7
	tmp.a = 4;
	tmp.b = 5;
	tmp.c = 6;
	winningRows.push_back(tmp);

	//8
	tmp.a = 6;
	tmp.b = 7;
	tmp.c = 2;
	winningRows.push_back(tmp);
}

int oppositePlayer2(int player) {
	//If player 1, return player 2.
	if (player == 1) return 2;
	//Otherwise, return player 1
	else return 1;
}

int checkWin(vector<int> board) {
	//Test all player 1 wins
	if (	(board[8] == 1 && board[3] == 1 && board[4] == 1) ||
			(board[8] == 1 && board[5] == 1 && board[2] == 1) ||
			(board[8] == 1 && board[1] == 1 && board[6] == 1) ||
			(board[3] == 1 && board[5] == 1 && board[7] == 1) ||
			(board[4] == 1 && board[9] == 1 && board[2] == 1) ||
			(board[1] == 1 && board[5] == 1 && board[9] == 1) ||
			(board[4] == 1 && board[5] == 1 && board[6] == 1) ||
			(board[6] == 1 && board[7] == 1 && board[2] == 1)
	) return 1;

	//Test all player 2 wins
	else if (	(board[8] == 2 && board[3] == 2 && board[4] == 2) ||
				(board[8] == 2 && board[5] == 2 && board[2] == 2) ||
				(board[8] == 2 && board[1] == 2 && board[6] == 2) ||
				(board[3] == 2 && board[5] == 2 && board[7] == 2) ||
				(board[4] == 2 && board[9] == 2 && board[2] == 2) ||
				(board[1] == 2 && board[5] == 2 && board[9] == 2) ||
				(board[4] == 2 && board[5] == 2 && board[6] == 2) ||
				(board[6] == 2 && board[7] == 2 && board[2] == 2)
		) return 2;
	return 0;
}

int Evaluator::evaluate(vector<int> board, int max, int evalFunction = 1) {
	int score;
	int min = oppositePlayer2(max);
	int minScore = 0;
	int maxScore = 0;

	int checkWinResult = checkWin(board);
	if (checkWinResult > 0) {
		//If Max has won
		if (checkWinResult == max) score = 999;
		//else Min has won
		else score = -999;
		return score;
	}

	switch (evalFunction) {
	case 2:
		//Simple Score
		for (int i=1; i < 10; i++) {
			//3 points for corners
			if ((i==8) || (i==4) || (i==6) || (i==2)) {
				if (board[i] == max) maxScore += 3;
				if (board[i] == min) minScore += 3;
			} else if (i==5) { //4 points for center
				if (board[i] == max) maxScore += 4;
				if (board[i] == min) minScore += 4;
			} else { //2 points for
				if (board[i] == max) maxScore += 2;
				if (board[i] == min) minScore += 2;
			}
		}
		score = maxScore - minScore;
		break;
	case 3:
		//TODO: Fill in
		score =0;
		break;
	case 4:
		//TODO: Fill in
		score = 0;
		break;

	default:
		vector<winningRow> winningRows;
		winningRows.clear();
		initWinningRows(winningRows);

		//Player 1 score = # Winning Vectors - rows killed by player 2.
		for (int i = 1; i < 10; i++) {
			if (board[i] == min) {
				vector<winningRow>::iterator it;
				for (it=winningRows.begin(); it < winningRows.end(); it++) {
					if (it->a == i || it->b == i || it->c == i) {
						if(it == winningRows.begin())
						{
							//handles case where it is pointing to first element
							winningRows.erase(it);
							it = winningRows.begin();
						}
						else
						{
							it--;
							winningRows.erase(it+1);
						}

						//handles case where all rows have been erased before
						//finishing loop
						if(winningRows.size() == 0)
							break;
					}
				}
			}
		}

		maxScore = (int) winningRows.size();
		//Reset winningRows
		winningRows.clear();
		initWinningRows(winningRows);

		//bool done = false;
		//Min score = # Winning Vectors - rows killed by max.
		for (int i = 1; i < 10; i++) {
			if (board[i] == max) {
				vector<winningRow>::iterator it;
				for (it=winningRows.begin(); it < winningRows.end(); it++) {
					if (it->a == i || it->b == i || it->c == i) {
						if(it == winningRows.begin())
						{
							//handles case where it is pointing to first element
							winningRows.erase(it);
							it = winningRows.begin();
						}
						else
						{
							it--;
							winningRows.erase(it+1);
						}
					}

					//handles case where all rows have been erased before
					//finishing loop
					if(winningRows.size() == 0)
						break;
				}
			}
		}
		minScore = (int) winningRows.size();

		//Score = MaxScore = MinScore
		score = maxScore - minScore;
		break;
	}
	return score;
}
