#include <iostream>
#include <random>
#include <stdlib.h>
#include <time.h>
#include < stdlib.h >

using namespace std;

#include "State.h"
#include "Goal.h"
#include "Solver.h"
//#include "NumberGenerator.h"

Goal getAtomGoal();

int main() {
	char input = 'y';
	
	while (input == 'y')
	{
		cout << "Play game (y): ";
		cin >> input;

		system("CLS");

		srand(time(0));
		Goal goal = getAtomGoal();

		State* initial = new State();
		initial->printBoard();
		Solver solver = Solver(initial, goal);
		solver.solve();
	}
	return 0;
}


Goal getAtomGoal() {
	int block, col, row;
	cout << "Select a block for the goal state (1-6): ";
	cin >> block;
	while (block < 1 || block > 6) {
		cout << endl << "INVALID BLOCK" << endl;
		cout << "Enter a block between 1 and 6: ";
		cin >> block;
	}
	cout << endl << "Enter the row and column to acheive goal state (0-2): ";
	cin >> row >> col;
	while ((row < 0 || row > 2) || (col < 0 || col > 2)) {
		cout << endl << "INVALID ROW OR COLUMN" << endl;
		cout << "Enter a row and column between 0 and 2: ";
		cin >> row >> col;
	}
	cout << "Block " << block << " at row " << row << " and column " << col << " selected as goal state" << endl;

	Goal goal;
	goal.block = block;
	goal.row = row;
	goal.col = col;

	cout << endl;

	for (int i = 0; i < BOARDSIZE; i++)
	{
		for (int j = 0; j < BOARDSIZE; j++)
			if (i == BOARDSIZE - 1 - row && j == col)
				cout << " " << block << " ";
			else
				cout << " * ";;

		cout << endl;
	}


	return goal;
	
}