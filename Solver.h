#pragma once
#include "State.h"
#include "Goal.h"

class Solver {
public:
	State *initialState;
	State *currentState;
	Goal goal;

	Solver(State *is, Goal g) {
		initialState = is;
		goal = g;
	}
	void solve();
	priority_queue<Action> getLegalActions(State* state, int level);
	bool isGoalState(State state);
	double calculateHeuristic(State* state);
};