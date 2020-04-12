#include "State.h"

State::State() {

	vector<int> indexes;
	for (int i = 0; i < (3 * 3); i++)
		if (i < (3 * 3) - 3)
			indexes.push_back(i+1);
		else
			indexes.push_back(0);


	random_shuffle(std::begin(indexes), std::end(indexes));


	for (int i = 0, index = 0; i < BOARDSIZE; i++)
		for (int j = 0; j < BOARDSIZE; j++, index++)
			grid[i][j] = indexes[index];

	pushDown();
}

State::State(const State& state) {
	for (int i = 0; i < BOARDSIZE; i++)
		for (int j = 0; j < BOARDSIZE; j++)
			grid[i][j] = state.grid[i][j];
}

bool State::operator==(State s) {
	for (int i = 0; i < BOARDSIZE; i++)
		for (int j = 0; j < BOARDSIZE; j++)
			if (s.grid[i][j] != grid[i][j])
				return false;
	return true;
}

void State::printBoard() {
	cout << endl;

	for (int i = 0; i < BOARDSIZE; i++)
	{
		for (int j = 0; j < BOARDSIZE; j++)
			cout << " " << grid[BOARDSIZE - i - 1][j] << " ";

		cout << endl;
	}
}

void State::pushDown() {
	stack<int> s;
	for (int j = 0; j < BOARDSIZE; j++)
	{
		for (int i = BOARDSIZE - 1; i >= 0; i--)
			if (grid[i][j] != 0)
				s.push(grid[i][j]);

		for (int k = 0; k < BOARDSIZE; k++)
			if (!s.empty())
			{
				grid[k][j] = s.top();
				s.pop();
			}
			else
				grid[k][j] = 0;
	}
}

// Returns the value of the block from the top of the specified column and removes it
int State::removeBlockFrom(int column) {
	for (int i = 0; i <= BOARDSIZE; i++)
	{
		int blockValue = grid[BOARDSIZE - i - 1][column];
			if (blockValue != 0)
			{
				grid[BOARDSIZE - i - 1][column] = 0;
				return blockValue;
			}
	}


	return -1;
}

// Places the block with value to the top of the column and returns if valid
bool State::insertBlockTo(int column, int value) {
	// Start from bottom and move up til empty space
	for (int i = 0; i < BOARDSIZE - 1 ; i++)
	{
		int blockValue = grid[i][column];
		if (blockValue == 0) {
			grid[i][column] = value;
			return true;
		}
	}

	return false;
}

// Moves the block from the top of the source column to the destination column and returns if valid
bool State::moveBlock(int source, int destination) {
	if (source == destination)
		return false;

	int blockValue = removeBlockFrom(source);

	if (blockValue == -1)
		return false;

	return insertBlockTo(destination, blockValue);

}

// Finds the row and column the block is at
void State::getBlockPosition(int block, int& row, int& col)
{
	for (int i = 0; i < BOARDSIZE; i++)
	{
		for (int j = 0; j < BOARDSIZE; j++)
		{
			if (grid[i][j] == block)
			{
				row = i;
				col = j;
				return;
			}
		}
	}
}

// Check if block is on top of a column
bool State::isBlockOnTop(int block)
{
	int row, col;
	getBlockPosition(block, row, col);
	
	if (isColumnFull(col))
		return grid[BOARDSIZE - 1][col] == block;

	// Gets the top available spot for the column - 1 to see if it is the same as the blocks row position
	return (getTopIndexOfColumn(col)-1) == row;
}

// Return index for the top empty spot of column, if full return -1;
int State::getTopIndexOfColumn(int col)
{
	if (isColumnFull(col))
		return -1;

	// Move from bottom to top 
	for (int i = 0; i < BOARDSIZE; i++)
	{
		if (grid[i][col] == 0)
			return i;
	}
}

bool State::isColumnEmpty(int col) {
	return grid[0][col] == 0;
}

bool State::isColumnFull(int col) {
	return grid[BOARDSIZE-1][col] != 0;
}

bool State::isBlockAt(int block, int row, int col) {
	return grid[row][col] == block;
}