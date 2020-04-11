#pragma once
struct Action {
	int fromCol;
	int toCol;
	double heuristic;

	Action(int f, int t, double h) :fromCol(f), toCol(t), heuristic(h) {}

	bool operator<(const Action& a) const {
		return heuristic < a.heuristic;
	}
};