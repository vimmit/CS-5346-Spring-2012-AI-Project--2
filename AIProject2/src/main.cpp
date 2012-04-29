/*
 * main.cpp
 *
 *  Created on: Mar 25, 2012
 *      Author: dgodwin
 */
#include <string>
#include <vector>
#include <iostream>
#include <stack>
#include <time.h>
#include "minmaxAB.h"
#include "AB_search.h"
#include "helper.h"

using namespace std;

//Test to see if a player has won, and if so, return that player (otherwise 0)
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

//Used by displayBoard
//If a tile is set to 0 and there is a human player, show the # of the square so the user can choose their move
//If the tile is set to 1, show X
//If the tile is set to 2, show O
//Otherwise, return an empty space
string showTile(string tile, int value, bool human = false) {
	if (value == 0 && human) return tile;
	if (value == 1) return "X";
	if (value == 2) return "O";
	return " ";
}

//Displays the current board after each round (and for human player move selection)
void displayBoard(vector<int> board, bool human=false) {
	cout << "  " << showTile("8",board[8],human) << "  |" << "  " << showTile("3",board[3],human) << "  |" << "  " << showTile("4",board[4],human) << endl;
	cout << "-----------------" << endl;
	cout << "  " << showTile("1",board[1],human) << "  |" << "  " << showTile("5",board[5],human) << "  |" << "  " << showTile("9",board[9],human) << endl;
	cout << "-----------------" << endl;
	cout << "  " << showTile("6",board[6],human) << "  |" << "  " << showTile("7",board[7],human) << "  |" << "  " << showTile("2",board[2],human) << endl << endl;
	}

//Returns the opposite player
int opposite(int player) {
	if (player == 1) return 2;
	return 1;
}

int main() {
	//Play Tic Tac Toe

	vector<int> board(10,0); //Board
	int turn = 1; // Turn
	int choice = 1; //User's default choice
	int move; //Human Player move
	bool humanPlayer = false; //If there is a human player. Human players are always Player 1 or X
	bool useRichAlgorithm = true; // Which algorithm to use
	int evaluationFunction; // 1 -4 corresponding to heuristic functions
	int maxDepth =0; //Max Depth used in deepEnough
	int nodeCount=0;

	cout << "*************************************************************************" << endl;
	cout << "*************************************************************************" << endl;
	cout << "********************* WELCOME TO TIC TAC TOE ****************************" << endl;
	cout << "*************************************************************************" << endl;
	cout << "*************************************************************************" << endl << endl;

	//Choose between CPU vs CPU or P1 vs CPU
	cout << "Choose Player 1:" << endl;
	cout << "1. Computer - DEFAULT" << endl;;
	cout << "2. Human" << endl;
	cout << "Choice:";
	cin >> choice;
	cout << endl;
	if (choice == 2) humanPlayer = true;

	//Choose Algorithm
	cout << "Choose Algorithm:" << endl;
	cout << "1. MINMAX-A-B (Rich & Knight) - DEFAULT" << endl;;
	cout << "2. ALPHA-BETA-SEARCH (Russell & Norvig)" << endl;
	cout << "Choice:";
	cin >> choice;
	cout << endl;
	if (choice == 2) useRichAlgorithm = false;

	//Choose evaluation/heuristic
	cout << "Choose Heuristic:" << endl;
	cout << "1. Luger - DEFAULT" << endl;
	//TODO:INSERT NAMES OF ADDITIONAL EVAL FUNCTIONS
	cout << "2. Simple Score" << endl;
	cout << "3. " << endl;
	cout << "4. " << endl;

	cout << "Choice:";
	cin >> evaluationFunction;
	cout << endl;
	if (evaluationFunction < 0 || evaluationFunction > 4) evaluationFunction = 1;

	while (maxDepth < 2 || maxDepth > 10) {
		cout << "Choose Maximum Depth (2-10):";
		cin >> maxDepth;
	}

	srand ( time(NULL) );
	int first = (rand() % (2))+1;
	cout << "Player " << first << " goes first!" << endl << endl;
	int player = first;

	while (turn < 10 && hasWon(board) == 0) {
		int depth = 0;
		result res;
		cout << "Turn #" << turn << endl << endl;
		while (res.path.empty()) {
			if (player ==  1 && humanPlayer) {
				move =0;
				displayBoard(board,humanPlayer);
				while (move < 1 || move > 9) {
					cout << "Enter your move (1-9):";
					cin >> move;
					cout << endl;
				}
				res.path.push(move);
			} else {
				if (useRichAlgorithm) res = minMaxABAlg::minMaxAB(board, depth, player, 999,-999, nodeCount,evaluationFunction, maxDepth);
				else {
					AB_search abSearch(board, player, evaluationFunction,maxDepth);
					result absearchresult = abSearch.evaluate(nodeCount);
					//cout << "AB result:" << absearchresult.path.top() << "|" << endl;
					res.path.push(absearchresult.path.top());
				}
				depth++;
			}
		}
		board[res.path.top()] = player;
		//else turn = 999; //board[firstAvailableMove(board)] = player;
		//Display Board
		cout << "Total Nodes: " << nodeCount;
		if (res.bestDepth > 0) cout << " | Depth: " << res.bestDepth << endl;
		else cout << endl;
		displayBoard(board);
		player = opposite(player);
		turn++;
		nodeCount = 0;
	}

	if (turn > 900) cout << "Sorry. There was an error"<< endl;
	else if (hasWon(board) > 0) cout << "Player: " << hasWon(board) << " Wins!" << endl;
	else cout << "Tie Game!" << endl;

	return 0;
}
