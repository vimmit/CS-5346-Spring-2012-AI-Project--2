#ifndef AB_SEARCH_H
#define AB_SEARCH_H

class AB_search{
	private:
		vector<int> board;
		int player;
		static const int DEPTH = 4;

		//helper functions
		//bool deepEnough(vector<int> position, int depth);
		int curr_player();
		int heuristic(vector<int> state);
		int min(int val1, int val2);
		int max(int val1, int val2);
		int utility(vector<int> state, int heuristic_num);

		vector<int>& result(int player, int action_value);
		vector<int> actions(vector<int> state);

		int max_value(vector<int> state, int _alpha, int _beta, int heuristic_num);
		int min_value(vector<int> state, int _alpha, int _beta, int heuristic_num);

	public:

		AB_search(vector<int>&, int);
		int evaluate();

};
#endif
