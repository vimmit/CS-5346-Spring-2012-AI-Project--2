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
AB_search::AB_search(vector<int>& _board, int _player)
{
	//initialize data
	board.clear();
	for(unsigned int i = 0; i < _board.size(); ++i)
		board.push_back(_board[i]);

	player = _player;
}
/***************************************************************
member function
******************************************************************/
result AB_search::evaluate()
{
	return max_value(board, -999, 999, player,0);
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

//updates the board state based on current players play and returns board state
/*vector<int>& AB_search::get_result(int player, int action_value)
{
	//board[0]++;	//counts the number of plays
	board[action_value] = player;
	board[0] = action_value;
	return board;
} */

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

//identifies which heuristic to use when evaluating board for optimal play
/*int AB_search::utility(vector<int> state, int heuristic_num)
{
	if(heuristic_num == 1) return heuristic(state);

	//stub
	return 0;


//stub
int AB_search::heuristic(vector<int> state)
{
	//stub
	return 0;
}
}*/
//determines optimal play for max player (player 1)
result AB_search::max_value(vector<int> state, int _alpha, int _beta, int heuristic_num, int depth)
{
	int value;
	vector<int> l_m;
	vector<vector <int> > possible_actions;
	result res;

	//determines if lowest evaluated level has been reached and returns utility value
	if(deepEnough(state, depth)) {
		res.score = Evaluator::evaluate(state, player, heuristic_num);//utility(state, heuristic_num);
		res.path.push(state[0]);
		return res;
	}

	//initialize
	//value = -999;
	res.score = -999;
	l_m = actions(board);
	possible_actions = moveGen(state, player);

	//loop through to find optimal move for max
	for (vector<vector <int> >::iterator it = possible_actions.begin(); it != possible_actions.end(); ++it) {
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

	//loop through to find optimal move for max
	/*for(unsigned int i = 0; i < l_m.size(); ++i)
	{
		value = max(value,min_value(get_result(curr_player(), l_m[i]), _alpha, _beta, heuristic_num, depth+1).score);
		//value = max(value, min_value(result(curr_player(), l_m[i]), _alpha, _beta, heuristic_num));
		//compares value to beta
		if(value >= _beta)
			return value;
		_alpha = max(_alpha, value);
	} */
	return res;
}

//determines optimal play for min player (player 2)
result AB_search::min_value(vector<int> state, int _alpha, int _beta, int heuristic_num, int depth)
{
	int value;
	vector<int> l_m;
	result res;
	vector<vector <int> > possible_actions;
	//determines if lowest evaluated level has been reached and returns utility value
	//if(deepEnough(state, depth)) return Evaluator::evaluate(state, player, heuristic_num);//utility(state, heuristic_num);
	if(deepEnough(state, depth)) {
			res.score = Evaluator::evaluate(state, player, heuristic_num);//utility(state, heuristic_num);
			res.path.push(state[0]);
			return res;
	}

	//initialize
	res.score = 999;
	value = 999;
	l_m = actions(board);
	possible_actions = moveGen(state, player);

	for (vector<vector <int> >::iterator it = possible_actions.begin(); it != possible_actions.end(); ++it) {
		value = max_value(*it, _alpha, _beta, heuristic_num, depth+1).score;

		if (res.score > value) {
			res.score = value;
			res.path.push(it->at(0));
		}

		//compares value to alpha
		if(res.score <= _alpha)
			return res;
		_beta = max(_beta, res.score);
	}

	//loop through to find optimal for min
	/*for(unsigned int i = 0; i < l_m.size(); ++i)
	{
		value = min(value, max_value(get_result(curr_player(), l_m[i]), _alpha, _beta, heuristic_num, depth+1).score);

		//compares value to alpha
		if(value <= _alpha)
			return value;
		_beta = max(_beta, value);
	}*/
	return res;
}

//determines lowest depth to evaluated by utility function
/*bool AB_search::deepEnough(vector<int> position, int depth) {
	//Just a stub. Depth hardcoded @ 4
	if (depth > DEPTH)	return true;
	return false;
}*/

//toggles between player 1 and player 2
int AB_search::curr_player()
{
	if(player == 1)
		player = 2;
	else
		player = 1;

	return player;
}
