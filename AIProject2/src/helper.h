/*
 * helper.h
 *
 *  Created on: Apr 10, 2012
 *      Author: dgodwin
 */

#ifndef HELPER_H_
#define HELPER_H_

#include <vector>
using namespace std;

vector<vector <int> > moveGen(vector<int> position, int player);
bool hasWinner(vector<int> board);
bool deepEnough(vector<int> position, int depth);


#endif /* HELPER_H_ */
