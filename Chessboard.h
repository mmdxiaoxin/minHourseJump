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
	const int dx[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };
	const int dy[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };

public:
	Chessboard();
	Chessboard(int boardSize_);

	bool isValid(int x, int y);

	Vector<Position> minJumps(Position start, Position target);

	void solve();
};


