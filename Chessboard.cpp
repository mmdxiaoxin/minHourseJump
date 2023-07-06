#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

#include "Chessboard.h"
#include "Vector.h"
#include "Queue.h"

using namespace std;
using json = nlohmann::json;

Chessboard::Chessboard() : boardSize(200) {}

Chessboard::Chessboard(int boardSize_) : boardSize(boardSize_) {}

bool Chessboard::isValid(int x, int y) {
	return (x >= 1 && x <= boardSize && y >= 1 && y <= boardSize);
}

Vector<Chessboard::Position> Chessboard::minJumpsPath() {
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

int Chessboard::minJumps() {
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

	Vector<Position> path = minJumpsPath();
	if (path.empty()) {
		cout << "没有找到路径." << endl;
	} else {
		cout << "最少跳数: " << path.size() - 1 << endl;
		outputFile << path.size() - 1 << endl;
		cout << "路径: ";
		for (int i = path.size() - 1; i >= 0; i--) {
			cout << "(" << path[i].x << ", " << path[i].y << ")";
			if (i != 0) {
				cout << " -> ";
			}
		}
		cout << endl;

		json json_path;
		for (const auto& pos : path) {
			json_path.push_back({ {"x", pos.x}, {"y", pos.y} });
		}
		json result = { {"minJumps", path.size() - 1}, {"start", {{"x", start.x}, {"y", start.y}}}, {"target", {{"x", target.x}, {"y", target.y}}}, {"path", json_path} };
		cout << result.dump() << endl;
		outputJson << result.dump() << endl;
	}
	inputFile.close();
	outputFile.close();
	outputJson.close();
}
