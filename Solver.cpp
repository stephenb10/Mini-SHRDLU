#include "Solver.h"

void Solver::solve() {
	currentState = initialState;
	priority_queue<Action> legalActions;
	

	if (isGoalState(*initialState))
		return;

	int steps = 0;
	while (steps < 100)
	{
		if (isGoalState(*currentState))
		{
			cout << "GOAL FOUND\n";
			currentState->printBoard();
			return;
		}
		steps++;


		moves.push_back(*currentState);
		legalActions = getLegalActions(currentState, 0);
		Action action = legalActions.top();
		currentState->moveBlock(action.fromCol, action.toCol);
		currentState->printBoard();
	}
	
	cout << "Steps exceeded 100 could not find goal\n";

}

priority_queue<Action> Solver::getLegalActions(State *s, int level) {
	priority_queue<Action> legalActions;

	cout << "Legal actions for this state" << endl;

	for (int i = 0; i < BOARDSIZE; i++)
		for (int j = 0; j < BOARDSIZE; j++)
		{
			State state = State(*s);

			if (state.moveBlock(i, j))
			{
				for (int x = 0; x < moves.size(); x++)
					if (moves[x] == state)
						continue;

				double heuristic = calculateHeuristic(state);
				Action action = Action(i, j, heuristic);

				cout << "Move: column " << i << " to " << j << " with heuristic value " << heuristic << endl;
				legalActions.push(action);
			}
		}
			

	return legalActions;
}

// Calculates the herustic value of the parsed state
double Solver::calculateHeuristic(State &state) {

	int row, col;
	state.getBlockPosition(goal.block, row, col);

	
	// If goal state 1
	if (state.isBlockAt(goal.block, goal.row, goal.col))
		return 1;

	// if goal value is on top of column and goal column next empty space is goal row.
	if (state.isBlockOnTop(goal.block) &&
		state.getTopIndexOfColumn(goal.col) == goal.row)
		return 0.9;


	return 0;
}

bool Solver::isGoalState(State state) {
	return state.isBlockAt(goal.block, goal.row, goal.col);
}