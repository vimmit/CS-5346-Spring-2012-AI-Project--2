/*
 * main.cpp
 *
 *  Created on: Mar 25, 2012
 *      Author: dgodwin
 */

#include <vector>
#include <iostream>
using namespace std;

int hasWon(vector<int> board) {
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
		if (	(board[8] == 2 && board[3] == 2 && board[4] == 2) ||
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

void initBoard(vector<int> &board) {
	for (int j = 1; j < 10; j++) { board[j] = 0; }
}

void displayBoard(vector<int> board) {
	cout << "  " << board[8] << "  |  " << "  " << board[3] << "  |  " << "  " << board[4] << endl;
	cout << "-------------------" << endl;
	cout << "  " << board[8] << "  |  " << "  " << board[3] << "  |  " << "  " << board[4] << endl;
	cout << "-------------------" << endl;
	cout << "  " << board[8] << "  |  " << "  " << board[3] << "  |  " << "  " << board[4] << endl;
}

int main() {
	//Play Tic Tac Toe

	vector<int> board;
	initBoard(board);
	string x;

	int turn = 1;
	while (turn < 10) {
		cout << "Turn #" << turn << endl;
		//Display Board
		displayBoard(board);
		//Player 1 moves

		//Player 2 moves

		turn++;
		if (hasWon(board) > 0) turn = 99;
	}

	if (turn == 99) cout << "Player: " << hasWon(board) << " Wins!" << endl;
	else cout << "Tie Game!" << endl;
	cin >> x;
	return 0;
}
