//AB_search.cpp
//Author: Michael Grayson
//This file contains the implementation of the AB_search class

#include <iostream>
#include <vector>
#include <climits>

using namespace std;

#include "AB_search.h"
#include "helper.h"
#include "evaluator.h"

/***************************************************************
constructors
******************************************************************/
AB_search::AB_search(vector<int>& _board, int _player, int heuristic_num, int _maxDepth)
{
	//initialize data
	board.clear();
	for(unsigned int i = 0; i < _board.size(); ++i)
		board.push_back(_board[i]);

	player = _player;
	heuristic_number = heuristic_num;
	maxDepth = _maxDepth;
}
/***************************************************************
member function
******************************************************************/
result AB_search::evaluate()
{
	return max_value(board, -999, 999, heuristic_number, 0);
}


/***************************************************************
helper functions
******************************************************************/
//returns the minimum value
int AB_search::min(int val1, int val2)
{
	if(val1 < val2)
		return val1;
	else
		return val2;
}

//returns the maximum value
int AB_search::max(int val1, int val2)
{
	if(val1 > val2)
		return val1;
	else
		return val2;
}

//returns a vector of all legal moves available for a player to occupy
vector<int> AB_search::actions(vector<int> state)
{
	vector<int> legal_moves;
	if (hasWinner(state)) return legal_moves;

	for(int i = 1; i <= 9; ++i)
		if(board[i] == 0)
			legal_moves.push_back(i);
	return legal_moves;
}

//determines optimal play for max player
result AB_search::max_value(vector<int> state, int _alpha, int _beta, int heuristic_num, int depth)
{
	int value;
	vector<vector <int> > possible_actions;
	result res;

	//determines if lowest evaluated level has been reached and returns utility value
	if(deepEnough(state, depth, maxDepth)) {
		res.score = Evaluator::evaluate(state, player, heuristic_num);
		res.path.push(state[0]);
		return res;
	}

	//initialize
	res.score = -999;
	possible_actions = moveGen(state, player);

	//loop through all legal moves
	for (vector<vector <int> >::iterator it = possible_actions.begin(); it != possible_actions.end(); ++it) {

		//select min value
		value = min_value(*it, _alpha, _beta, heuristic_num, depth+1).score;
		if (res.score < value) {
			res.score = value;
			res.path.push(it->at(0));
		}

		if(res.score >= _beta){
			return res;
		}
		_alpha = max(_alpha, res.score);
	}
	return res;
}

//determines optimal play for min player
result AB_search::min_value(vector<int> state, int _alpha, int _beta, int heuristic_num, int depth)
{
	int value;
	result res;
	vector<vector <int> > possible_actions;

	if(deepEnough(state, depth, maxDepth)) {
			res.score = Evaluator::evaluate(state, player, heuristic_num);
			res.path.push(state[0]);
			return res;
	}

	//initialize
	res.score = 999;
	value = 999;
	possible_actions = moveGen(state, player);

	//loop through all legal moves
	for (vector<vector <int> >::iterator it = possible_actions.begin(); it != possible_actions.end(); ++it) {

		//select max value
		value = max_value(*it, _alpha, _beta, heuristic_num, depth+1).score;

		if (res.score > value) {
			res.score = value;
			res.path.push(it->at(0));
		}

		if(res.score <= _alpha)
			return res;
		_beta = max(_beta, res.score);
	}
	return res;
}

//toggles between player 1 and player 2
int AB_search::curr_player()
{
	if(player == 1)
		player = 2;
	else
		player = 1;

	return player;
}
