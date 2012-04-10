#include <iostream>
#include <vector>
#include <climits>

using namespace std;

#include "AB_search.h"
#include "helper.h"

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
int AB_search::evaluate()
{
	return max_value(board, INT_MIN, INT_MAX, player);
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
vector<int>& AB_search::result(int player, int action_value)
{
	//board[0]++;	//counts the number of plays
	board[action_value] = player;
	return board;
}

//returns a vector of all legal moves available for a player to occupy
vector<int> AB_search::actions(vector<int> state)
{
	vector<int> legal_moves;
	for(int i = 1; i <= 9; ++i)
		if(board[i] == 0)
			legal_moves.push_back(i);
	return legal_moves;
}

//identifies which heuristic to use when evaluating board for optimal play
int AB_search::utility(vector<int> state, int heuristic_num)
{
	if(heuristic_num == 1) return heuristic(state);

	//stub
	return 0;
}

//stub
int AB_search::heuristic(vector<int> state)
{
	//stub
	return 0;
}

//determines optimal play for max player (player 1)
int AB_search::max_value(vector<int> state, int _alpha, int _beta, int heuristic_num)
{
	int value;
	vector<int> l_m;

	//determines if lowest evaluated level has been reached and returns utility value
	if(deepEnough(state, DEPTH)) return utility(state, heuristic_num);

	//initialize
	value = INT_MIN;
	l_m = actions(board);

	//loop through to find optimal move for max
	for(unsigned int i = 0; i < l_m.size(); ++i)
	{
		value = max(value, min_value(result(curr_player(), l_m[i]), _alpha, _beta, heuristic_num));

		//compares value to beta
		if(value >= _beta)
			return value;
		_alpha = max(_alpha, value);
	}
	return value;
}

//determines optimal play for min player (player 2)
int AB_search::min_value(vector<int> state, int _alpha, int _beta, int heuristic_num)
{
	int value;
	vector<int> l_m;

	//determines if lowest evaluated level has been reached and returns utility value
	if(deepEnough(state, DEPTH)) return utility(state, heuristic_num);

	//initialize
	value = INT_MAX;
	l_m = actions(board);

	//loop through to find optimal for min
	for(unsigned int i = 0; i < l_m.size(); ++i)
	{
		value = min(value, max_value(result(curr_player(), l_m[i]), _alpha, _beta, heuristic_num));

		//compares value to alpha
		if(value <= _alpha)
			return value;
		_beta = max(_beta, value);
	}
	return value;
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
