#include "Solver.h"

void Solver::solve() {
	currentState = initialState;
	priority_queue<Action> legalActions;

	if (isGoalState(*initialState))
		return;

	int steps = 0;
	while (steps < 100)
	{
		legalActions = getLegalActions(currentState, 0);
		Action action = legalActions.top();
		currentState->moveBlock(action.fromCol, action.toCol);
		if (isGoalState(*currentState))
		{
			cout << "GOAL FOUND\n";
			currentState->printBoard();
			return;
		}
		steps++;
	}
	
	cout << "Steps exceeded 100 could not find goal\n";

}

priority_queue<Action> Solver::getLegalActions(State *state, int level) {
	priority_queue<Action> legalActions;

	cout << "Legal actions for this state" << endl;

	for (int i = 0; i < BOARDSIZE; i++)
		for (int j = 0; j < BOARDSIZE; j++)
			if (state->moveBlock(i, j))
			{
				double heuristic = calculateHeuristic(state);
				Action action = Action(i, j, heuristic);

				cout << "Move: column " << i << " to " << j << " with heuristic value " << heuristic << endl;
				legalActions.push(action);
				state->moveBlock(j, i);
			}

	return legalActions;
}

// Calculates the herustic value of the parsed state
double Solver::calculateHeuristic(State *state) {
	// Check how far away from goal state we are 
	// If goal state 1
	// if goal value is on top of column and goal column top is goal row .9


	return 1;
}

bool Solver::isGoalState(State state) {
	return state.isBlockAt(goal.block, goal.row, goal.col);
}