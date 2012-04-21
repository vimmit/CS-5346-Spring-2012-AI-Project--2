//AB_search.h
//Author: Michael Grayson
//This file contains the declaration of the AB_search class

#ifndef AB_SEARCH_H
#define AB_SEARCH_H

#include "helper.h"

using namespace std;

class AB_search{
	private:
		vector<int> board;		//holds the board state
		int player;				//holds the current player
		int heuristic_number;	//holds the number for the heuristic that will be used
		int maxDepth;			//holds the max depth for deepEnough evaluation

		//helper functions
		int curr_player();
		int min(int val1, int val2);
		int max(int val1, int val2);

		vector<int> actions(vector<int> state);

		result max_value(vector<int> state, int _alpha, int _beta, int heuristic_num, int depth);
		result min_value(vector<int> state, int _alpha, int _beta, int heuristic_num, int depth);

	public:
		//constructor
		AB_search(vector<int>& board, int player, int heuristic_number, int maxDepth);

		//public method
		result evaluate();

};
#endif
