#pragma once
#include "Vector.h"
#include "Queue.h"

class Chessboard {
public:
	struct Position {
		int x;
		int y;
		Position() : x(0), y(0) {}
		Position(int _x, int _y) : x(_x), y(_y) {}
	};

private:
	int boardSize;
	int currJumps;
	const int dx[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };
	const int dy[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
	Vector<Vector<bool>> visited;
	Position start;
	Position target;

public:
	Chessboard();
	Chessboard(int boardSize_);
	bool isValid(int x, int y);
	Vector<Position> optimalPathBFS();
	Vector<Position> branchBoundPath();
	Vector<Position> feasiblePathDFS();
	Vector<Position> backtrack(Position curr, int jumps);
	int minJumpsBFS();
	void solve();
	void printChessboard(const Position& start, const Position& target, const Vector<Position>& path);
	void printPath(Vector<Position> path);
	void printJson(Vector<Position> path);
};


