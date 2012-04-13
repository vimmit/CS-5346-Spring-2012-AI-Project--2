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
#include "helper.h"

using namespace std;

class minMaxABAlg {
	public:
		static result minMaxAB(vector<int> position, int depth, int player, int useThresh, int passThresh, int evalFunction);
};

#endif /* MINMAXAB_H_ */
