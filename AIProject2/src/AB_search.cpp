//AB_search.cpp
//Author: Michael Grayson
//This file contains the implementation of the AB_search class

#include <iostream>
#include <vector>
#include <climits>

#include "AB_search.h"
#include "helper.h"
#include "evaluator.h"

using namespace std;

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
	num_of_nodes = 0;
}

/***************************************************************
member function
******************************************************************/
result AB_search::evaluate(int& nodeCount)
{
	result tmp;
	tmp = max_value(board, -999, 999, heuristic_number, 0, nodeCount);
	tmp.num_of_nodes = num_of_nodes;
	return tmp;
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
result AB_search::max_value(vector<int> state, int _alpha, int _beta, int heuristic_num, int depth, int& nodeCount)
{
	int value;
	vector<vector <int> > possible_actions;
	result res;

	//captures number of nodes generated based on the amound of function calls
	//num_of_nodes++;

	//determines if lowest evaluated level has been reached and returns utility value
	if(deepEnough(state, depth, maxDepth)) {
		res.score = Evaluator::evaluate(state, player, heuristic_num);
		res.path.push(state[0]);
		if (depth <= maxDepth) res.bestDepth = depth;
		else res.bestDepth = maxDepth;
		return res;
	}

	//initialize
	res.score = -999;
	value = -999;
	possible_actions = moveGen(state, player, nodeCount);

	//loop through all legal moves
	for (vector<vector <int> >::iterator it = possible_actions.begin(); it != possible_actions.end(); ++it) {

		//select min value
		value = min_value(*it, _alpha, _beta, heuristic_num, depth+1,nodeCount).score;

		if (res.score < value) {
			res.score = value;
			res.path.push(it->at(0));
			res.bestDepth = depth+1;
		}
		else
			if(res.path.empty())
				res.path.push(it->at(0));

		if(res.score >= _beta){
			return res;
		}
		_alpha = max(_alpha, res.score);
	}
	return res;
}

//determines optimal play for min player
result AB_search::min_value(vector<int> state, int _alpha, int _beta, int heuristic_num, int depth, int& nodeCount)
{
	int value;
	result res;
	vector<vector <int> > possible_actions;

	//captures number of nodes generated based on the amound of function calls
	num_of_nodes++;

	if(deepEnough(state, depth, maxDepth)) {
		res.score = Evaluator::evaluate(state, player, heuristic_num);
		res.path.push(state[0]);
		return res;
	}

	//initialize
	res.score = 999;
	value = 999;
	possible_actions = moveGen(state, oppositePlayer(), nodeCount);

	//loop through all legal moves
	for (vector<vector <int> >::iterator it = possible_actions.begin(); it != possible_actions.end(); ++it) {

		//select max value
		value = max_value(*it, _alpha, _beta, heuristic_num, depth+1, nodeCount).score;

		if (value < res.score) {
			res.score = value;
			res.path.push(it->at(0));
			res.bestDepth = depth+1;
		}
		else
			if(res.path.empty())
				res.path.push(it->at(0));

		if(res.score <= _alpha)
			return res;
		_beta = min(_beta, res.score);
	}
	return res;
}

//returns opposite of current player
int AB_search::oppositePlayer()
{
	if(player == 1)
		return 2;
	else
		return 1;
}
