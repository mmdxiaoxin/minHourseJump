﻿#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <nlohmann/json.hpp>
#include <opencv2/opencv.hpp>

#include "Chessboard.h"
#include "Vector.h"
#include "Queue.h"

using namespace std;
using namespace cv;
using json = nlohmann::json;

/**
* 默认构造函数。设置棋盘大小为200，当前跳数为无穷大。
*/
Chessboard::Chessboard() : boardSize(200), currJumps(INT_MAX) {}

/**
* 构造函数。根据给定的棋盘大小，初始化棋盘和当前跳数。
*
* @param boardSize_ 棋盘大小
*/
Chessboard::Chessboard(int boardSize_) : boardSize(boardSize_), currJumps(INT_MAX) {}

/**
* 检查坐标是否在合法的范围内。
*
* @param x 横坐标
* @param y 纵坐标
* @return 如果坐标在合法范围内，则返回 true，否则返回 false
*/
bool Chessboard::isValid(int x, int y) {
	return (x >= 1 && x <= boardSize && y >= 1 && y <= boardSize);
}

/**
* 使用广度优先搜索算法寻找最优路径。
*
* @return 最优路径的位置列表
*/
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

/**
* 使用深度优先搜索算法寻找可行路径。
*
* @return 可行路径的位置列表
*/
Vector<Chessboard::Position> Chessboard::feasiblePathDFS() {
	visited = Vector<Vector<bool>>(boardSize + 1, Vector<bool>(boardSize + 1, false));
	return backtrack(start, currJumps);
}

/**
* 使用分支限界法寻找最优路径。
*
* @return 最优路径的位置列表
*/
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

/**
* 使用广度优先搜索算法计算最小跳数。
*
* @return 最小跳数
*/
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
	printJson(path);
	displayPath(path);

	// 测量 feasiblePathDFS() 函数的运行时间
	auto startDFS = chrono::high_resolution_clock::now();
	Vector<Position> path3 = feasiblePathDFS();
	auto endDFS = chrono::high_resolution_clock::now();
	chrono::duration<double> durationDFS = endDFS - startDFS;
	cout << "寻找可行解函数 feasiblePathDFS() 运行时间: " << durationDFS.count() << " 秒" << endl;
	printPath(path3);

	inputFile.close();
	outputFile.close();
}

/**
* 打印棋盘，标记起始位置、目标位置和路径。
*
* @param start 起始位置
* @param target 目标位置
* @param path 路径位置列表
*/
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
	cout << endl;
}

/**
* 打印路径的 JSON 格式。
*
* @param path 路径位置列表
*/
void Chessboard::printJson(Vector<Position> path) {
	ofstream outputJson("output.json");
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
		cout << endl;
		outputJson << result.dump() << endl;
	}
	outputJson.close();
}

/**
* 在图像窗口中展示路径。
*
* @param path 路径位置列表
*/
void Chessboard::displayPath(Vector<Position>& path) {
	const int Size = 15;  // 棋盘格子的大小
	const int Menu = Size / 2;  // 路径线的宽度

	int ROWS = boardSize;  // 棋盘的行数
	int COLS = boardSize;  // 棋盘的列数

	// 计算图像窗口的大小
	int imgWidth = COLS * Size;
	int imgHeight = ROWS * Size;

	Mat img(imgHeight, imgWidth, CV_8UC3, Scalar(255, 255, 255));  // 创建图像窗口，背景颜色为白色
	Point left_up, right_bottom;
	Point point_first, point_second;

	// 绘制中间路径点，颜色为黄色
	for (int i = 0; i < path.size(); i++) {
		left_up.x = path[i].y * Size;
		left_up.y = path[i].x * Size;
		right_bottom.x = left_up.x + Size;
		right_bottom.y = left_up.y + Size;
		rectangle(img, left_up, right_bottom, Scalar(0, 255, 255), -1, 8, 0);
	}

	// 绘制起点，颜色为蓝色，终点，颜色为红色
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			left_up.x = j * Size;
			left_up.y = i * Size;
			right_bottom.x = left_up.x + Size;
			right_bottom.y = left_up.y + Size;
			if (i == start.x && j == start.y)
				rectangle(img, left_up, right_bottom, Scalar(255, 0, 0), -1, 8, 0);
			else if (i == target.x && j == target.y)
				rectangle(img, left_up, right_bottom, Scalar(0, 0, 255), -1, 8, 0);
		}
	}

	// 绘制中间线，颜色为黄色
	for (int i = 1; i < COLS; i++) {
		point_first.x = i * Size;
		point_first.y = 1 * Size;
		point_second.x = i * Size;
		point_second.y = (ROWS - 1) * Size;
		line(img, point_first, point_second, Scalar(141, 238, 238), 2, 2);
	}
	for (int i = 1; i < ROWS; i++) {
		point_first.x = 1 * Size;
		point_first.y = i * Size;
		point_second.x = (COLS - 1) * Size;
		point_second.y = i * Size;
		line(img, point_first, point_second, Scalar(141, 238, 238), 2, 2);
	}

	// 绘制路径线，颜色为黄色
	point_first.x = target.y * Size + Menu;
	point_first.y = target.x * Size + Menu;
	for (int i = 0; i < path.size(); i++) {
		left_up.y = path[i].x * Size;
		left_up.x = path[i].y * Size;
		point_second.x = left_up.x + Menu;
		point_second.y = left_up.y + Menu;
		line(img, point_first, point_second, Scalar(0, 0, 0), 2, 4);
		point_first = point_second;
	}

	// 调整图像窗口的大小以适应实际尺寸
	namedWindow("ChessBoard", WINDOW_NORMAL);
	resizeWindow("ChessBoard", imgWidth, imgHeight);

	imshow("ChessBoard", img);
	waitKey(0);
}

/**
* 打印路径的详细信息，包括跳数和位置坐标。
*
* @param path 路径位置列表
*/
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
