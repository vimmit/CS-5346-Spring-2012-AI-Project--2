/*
 * minmaxAB.h
 *
 *  Created on: Mar 30, 2012
 *      Author: dgodwin
 */

#ifndef MINMAXAB_H_
#define MINMAXAB_H_

#include <iostream>
#include <vector>
#include <stack>
#include "evaluator.h"

using namespace std;

struct result {
	int score;
	stack<int> path;
};

class minMaxABAlg {
	public:
		static result minMaxAB(vector<int> position, int depth, int player, int useThresh, int passThresh);
};

#endif /* MINMAXAB_H_ */
