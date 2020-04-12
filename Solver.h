#pragma once
#include "State.h"
#include "Goal.h"

class Solver {
public:
	State *initialState;
	State *currentState;
	Goal goal;
	vector<State> moves;

	Solver(State *is, Goal g) {
		initialState = is;
		goal = g;
	}
	void solve();
	priority_queue<Action> getLegalActions(State* s, int level);
	bool isGoalState(State state);
	double calculateHeuristic(State &state);
};