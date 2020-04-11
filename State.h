#pragma once
#ifndef STATE_H_
#define STATE_H_

#include <stdlib.h>
#include <iostream>
#include <stack>
#include <random>
#include <vector>
#include <queue>
#include "Action.h"

using namespace std;

const int BOARDSIZE = 3;
const int NUMBER_OF_BLOCKS = 6;

class State {
public:
	int grid[BOARDSIZE][BOARDSIZE];
	//priority_queue<Action> legalActions;

	State();
	bool operator==(State s);
	void printBoard();
	void pushDown();
	int removeBlockFrom(int column);
	bool insertBlockTo(int column, int value);
	bool moveBlock(int source, int destination);
	bool isBlockAt(int block, int row, int col);
	void getBlockPosition(int block, int& row, int& col);
	bool isBlockOnTop(int block);
	int getTopOfColumn(int col);
	bool isColumnEmpty(int col);
	bool isColumnFull(int col);


};

#endif /* STATE_H_ */