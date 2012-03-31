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

void displayBoard2(vector<int> board) {
	cout << "  " << board[8] << "  |" << "  " << board[3] << "  |" << "  " << board[4] << endl;
	cout << "-----------------" << endl;
	cout << "  " << board[1] << "  |" << "  " << board[5] << "  |" << "  " << board[9] << endl;
	cout << "-----------------" << endl;
	cout << "  " << board[6] << "  |" << "  " << board[7] << "  |" << "  " << board[2] << endl << endl;
}

int Evaluator::evaluate(vector<int> board, int player1) {
	//cout << "Evaluating..." << endl;
	//displayBoard2(board);
	vector<winningRow> winningRows;
	initWinningRows(winningRows);

	//Player 1 score = # Winning Vectors - rows killed by player 2.
	for (int i = 1; i < 10; i++) {
		if (board[i] == oppositePlayer2(player1)) {
			vector<winningRow>::iterator it;
			for (it=winningRows.begin(); it < winningRows.end(); it++) {
				if (it->a == i || it->b == i || it->c == i) {
					winningRows.erase(it);
					it--;
				}
			}
		}
	}
	int player1Score;
	player1Score = (int) winningRows.size();

	//Reset winningRows
	winningRows.clear();
	initWinningRows(winningRows);

	//Player 2 score = # Winning Vectors - rows killed by player 1.
	for (int i = 1; i < 10; i++) {
		if (board[i] == player1) {
			//cout << "i: " << i << " | " << board[i] << endl;
			vector<winningRow>::iterator it;

			for (it=winningRows.begin(); it < winningRows.end(); it++) {
				//cout << "Checking: " << it->a << it->b << it->c <<endl;
				if (it->a == i || it->b == i || it->c == i) {
					//cout << "Erasing: " << it->a << it->b << it->c <<endl;
					winningRows.erase(it);
					it--;
				}
			}
		}
	}

		int player2Score;
		player2Score = (int) winningRows.size();
		//cout << "P1 = " << player1Score << " P2 = " << player2Score << " Final:" << player1Score - player2Score << endl;
		return player1Score - player2Score;
}



