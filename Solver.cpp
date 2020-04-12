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
			cout << steps << " Steps taken\n";
			currentState->printBoard();
			return;
		}
		steps++;


		moves.push_back(*currentState);
		legalActions = getLegalActions(currentState);
		if (!legalActions.empty())
		{
			Action action = legalActions.top();
			currentState->moveBlock(action.fromCol, action.toCol);
		    currentState->printBoard();
		}
		else
			cout << "Error: No legal actions available.";
	}
	
	cout << "Steps exceeded 100 could not find goal\n";

}

priority_queue<Action> Solver::getLegalActions(State *state) {
	priority_queue<Action> legalActions;

	cout << "Legal actions for this state" << endl;

	for (int i = 0; i < BOARDSIZE; i++)
		for (int j = 0; j < BOARDSIZE; j++)
		{
			State *tempState = new State(*state);

			if (tempState->moveBlock(i, j))
			{
				double heuristic = calculateHeuristic(*tempState, *state);
				Action action = Action(i, j, heuristic);

				cout << "Move: column " << i << " to " << j << " with heuristic value " << heuristic << endl;
				legalActions.push(action);
			}
		}
			

	return legalActions;
}

// Calculates the herustic value of the parsed state
double Solver::calculateHeuristic(State &state, State &prevState) {

	// Check if move results in a previous state
	for (int x = 0; x < moves.size(); x++)
		if (moves[x] == state)
			return 0;


	int row, col;
	state.getBlockPosition(goal.block, row, col);

	int colTopNow, colTopOld;
	colTopNow = state.getTopIndexOfColumn(col);
	colTopOld = prevState.getTopIndexOfColumn(col);

	bool blockOnTop = state.isBlockOnTop(goal.block);


	// If goal state 1
	if (state.isBlockAt(goal.block, goal.row, goal.col))
		return 1;

	// add a check to see if making space on the goal column to move
	
	if (blockOnTop)
	{
		// if goal value is on top of column and goal column next empty space is goal row.
		if(state.getTopIndexOfColumn(goal.col) == goal.row && goal.col != col)
			return 0.9;

		if (col == goal.col) 
		{
			return 0.5; // Block is on top but in the goal column
		}
		else // block is on top but not in goal col
		{
			int goalTop = state.getTopIndexOfColumn(goal.col);
			int prevGoalTop = prevState.getTopIndexOfColumn(goal.col);
			if (goalTop > goal.row)
			{
				if (goalTop < prevGoalTop)
					return 0.7; // block is on top and making way on goal column
			}
			else if (goalTop < goal.row)
				if (goalTop > prevGoalTop)
					return 0.7;

				return 0.6; // Block is on top
		}
			
	}		
	else {
		if (col == goal.col)
		{
			if (colTopNow < colTopOld) // Check if making the column available to move 
				return 0.4;
			else
				return 0.3; // block is not on top
		}
	}

		
	return 0.1;
}

bool Solver::isGoalState(State state) {
	return state.isBlockAt(goal.block, goal.row, goal.col);
}