/*
 * evaluator.h
 *
 *  Created on: Mar 30, 2012
 *      Author: dgodwin
 */

#ifndef EVALUATOR_H_
#define EVALUATOR_H_

#include <vector>

using namespace std;

class Evaluator {
	public:
		static int evaluate(vector<int> board, int player);
};

#endif /* EVALUATOR_H_ */
