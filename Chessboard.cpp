#include <fstream>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <nlohmann/json.hpp>

#include "Chessboard.h"
#include "Vector.h"
#include "Queue.h"

using namespace std;
using json = nlohmann::json;

Chessboard::Chessboard() : boardSize(200), currJumps(INT_MAX) {}

Chessboard::Chessboard(int boardSize_) : boardSize(boardSize_), currJumps(INT_MAX) {}

bool Chessboard::isValid(int x, int y) {
	return (x >= 1 && x <= boardSize && y >= 1 && y <= boardSize);
}

Vector<Chessboard::Position> Chessboard::optimalPathBFS() {
	Vector<Vector<int>> board(boardSize + 1, Vector<int>(boardSize + 1, -1));
	Vector<Vector<Position>> parent(boardSize + 1, Vector<Position>(boardSize + 1, { -1, -1 }));
	board[start.x][start.y] = 0;

	Queue<Position> q;
	q.push(start);

	while (!q.empty()) {
		Position curr = q.front();
		q.pop();

		if (curr.x == target.x && curr.y == target.y) {
			Vector<Position> path;
			while (!(curr.x == start.x && curr.y == start.y)) {
				path.push_back(curr);
				curr = parent[curr.x][curr.y];
			}
			path.push_back(start);
			return path;
		}

		for (int i = 0; i < 8; i++) {
			int nextX = curr.x + dx[i];
			int nextY = curr.y + dy[i];

			if (isValid(nextX, nextY) && board[nextX][nextY] == -1) {
				board[nextX][nextY] = board[curr.x][curr.y] + 1;
				parent[nextX][nextY] = curr;
				q.push(Position(nextX, nextY));
			}
		}
	}

	return Vector<Position>();
}


Vector<Chessboard::Position> Chessboard::feasiblePathDFS() {
	visited = Vector<Vector<bool>>(boardSize + 1, Vector<bool>(boardSize + 1, false));
	return backtrack(start, currJumps);
}

Vector<Chessboard::Position> Chessboard::branchBoundPath() {
	Vector<Vector<int>> board(boardSize + 1, Vector<int>(boardSize + 1, -1));
	Vector<Vector<Position>> parent(boardSize + 1, Vector<Position>(boardSize + 1, { -1, -1 }));
	board[start.x][start.y] = 0;

	Queue<Position> q;
	q.push(start);

	while (!q.empty()) {
		Position curr = q.front();
		q.pop();

		if (curr.x == target.x && curr.y == target.y) {
			Vector<Position> path;
			while (!(curr.x == start.x && curr.y == start.y)) {
				path.push_back(curr);
				curr = parent[curr.x][curr.y];
			}
			path.push_back(start);
			return path;
		}

		for (int i = 0; i < 8; i++) {
			int nextX = curr.x + dx[i];
			int nextY = curr.y + dy[i];

			if (isValid(nextX, nextY) && board[nextX][nextY] == -1) {
				int nextJump = board[curr.x][curr.y] + 1;
				if (nextJump < board[target.x][target.y] || board[target.x][target.y] == -1) {
					board[nextX][nextY] = nextJump;
					parent[nextX][nextY] = curr;
					q.push(Position(nextX, nextY));
				}
			}
		}
	}

	return Vector<Position>();
}

Vector<Chessboard::Position> Chessboard::backtrack(Position curr, int jumps) {
	if (curr.x == target.x && curr.y == target.y) {
		Vector<Position> path;
		path.push_back(curr);
		return path;
	}

	if (jumps <= 0 || visited[curr.x][curr.y])
		return Vector<Position>();

	visited[curr.x][curr.y] = true;

	for (int i = 0; i < 8; i++) {
		int nextX = curr.x + dx[i];
		int nextY = curr.y + dy[i];

		if (isValid(nextX, nextY) && !visited[nextX][nextY]) {
			Vector<Position> path = backtrack(Position(nextX, nextY), jumps - 1);
			if (!path.empty()) {
				path.push_back(curr);
				return path;
			}
		}
	}

	visited[curr.x][curr.y] = false;

	return Vector<Position>();
}

int Chessboard::minJumpsBFS() {
	Queue<pair<Position, int>> q;
	q.push({ start, 0 });
	visited[start.x][start.y] = true;

	while (!q.empty()) {
		Position currPos = q.front().first;
		int currJumps = q.front().second;
		q.pop();

		if (currPos.x == target.x && currPos.y == target.y) {
			return currJumps;
		}

		for (int i = 0; i < 8; i++) {
			int nextX = currPos.x + dx[i];
			int nextY = currPos.y + dy[i];

			if (isValid(nextX, nextY) && !visited[nextX][nextY]) {
				q.push({ Position(nextX, nextY), currJumps + 1 });
				visited[nextX][nextY] = true;
			}
		}
	}

	return -1;
}

void Chessboard::solve() {
	ifstream inputFile("input.txt");
	ofstream outputFile("output.txt");
	ofstream outputJson("output.json");

	int startX, startY, targetX, targetY;
	inputFile >> startX >> startY >> targetX >> targetY;

	start = Position(startX, startY);
	target = Position(targetX, targetY);

	// 测量 optimalPathBFS() 函数的运行时间
	auto startBFS = chrono::high_resolution_clock::now();
	Vector<Position> path = optimalPathBFS();
	auto endBFS = chrono::high_resolution_clock::now();
	chrono::duration<double> durationBFS = endBFS - startBFS;
	cout << "寻找最优解函数 optimalPathBFS() 运行时间: " << durationBFS.count() << " 秒" << endl;
	outputFile << path.size() - 1 << endl;
	printPath(path);

	// 测量 branchBoundPath() 函数的运行时间
	auto startBB = chrono::high_resolution_clock::now();
	Vector<Position> path2 = branchBoundPath();
	auto endBB = chrono::high_resolution_clock::now();
	chrono::duration<double> durationBB = endBB - startBB;
	cout << "寻找最优解函数 branchBoundPath() 运行时间: " << durationBB.count() << " 秒" << endl;
	printPath(path2);

	Vector<Position> path_ = feasiblePathDFS();
	printPath(path_);
	
	if (path.empty()) {
		cout << "没有找到路径." << endl;
	} else {	
		json json_path;
		for (int i = path.size() - 1; i >= 0; i--) {
			const auto& pos = path[i];
			json_path.push_back({ {"x", pos.x}, {"y", pos.y} });
		}
		json result = { {"minJumps", path.size() - 1},
			{"start", {{"x", start.x}, {"y", start.y}}},
			{"target", {{"x", target.x}, {"y", target.y}}},
			{"path", json_path},
			{"boardSize", boardSize} };
		cout << "转换最短路径为JSON格式为: " << endl;
		cout << result.dump() << endl;
		outputJson << result.dump() << endl;
	}
	inputFile.close();
	outputFile.close();
	outputJson.close();
}

void Chessboard::printChessboard(const Position& start, const Position& target, const Vector<Position>& path) {
	Vector<Vector<int>> chessboard(boardSize, Vector<int>(boardSize, 0));

	for (int i = 0; i < path.size(); i++) {
		Position pos = path[i];
		chessboard[pos.x - 1][pos.y - 1] = path.size() - i - 1;
	}

	cout << "+";
	for (int i = 0; i < boardSize; i++) {
		cout << "--+";
	}
	cout << endl;

	for (int i = 0; i < boardSize; i++) {
		cout << "|";
		for (int j = 0; j < boardSize; j++) {
			if (start.x == i + 1 && start.y == j + 1) {
				cout << " S";
			} else if (target.x == i + 1 && target.y == j + 1) {
				cout << " T";
			} else if (chessboard[i][j] == 0) {
				cout << "  ";
			} else {
				cout << setw(2) << chessboard[i][j];
			}
			cout << "|";
		}
		cout << endl;

		cout << "+";
		for (int k = 0; k < boardSize; k++) {
			cout << "--+";
		}
		cout << endl;
	}
}

void Chessboard::printPath(Vector<Position> path) {
	if (path.empty()) {
		cout << "没有找到路径." << endl;
	} else {
		cout << "跳数: " << path.size() - 1 << endl;
		cout << "路径: ";
		for (int i = path.size() - 1; i >= 0; i--) {
			cout << "(" << path[i].x << ", " << path[i].y << ")";
			if (i != 0) {
				cout << " -> ";
			}
		}
		cout << endl;
		printChessboard(start, target, path);
	}
}
