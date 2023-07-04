#include <iostream>
#include <nlohmann/json.hpp>

#include "Vector.h"
#include "Queue.h"

using namespace std;
using json = nlohmann::json;

// ��������ƶ�����
const int dx[] = { 1, 2, 2, 1, -1, -2, -2, -1 };
const int dy[] = { 2, 1, -1, -2, -2, -1, 1, 2 };

// �������̴�С
const int BOARD_SIZE = 200;

// ������������ṹ��
struct Position {
	int x;
	int y;
	Position() : x(0), y(0) {}
	Position(int _x, int _y) : x(_x), y(_y) {}
};

// ��������Ƿ������̷�Χ��
bool isValid(int x, int y) {
	return (x >= 1 && x <= BOARD_SIZE && y >= 1 && y <= BOARD_SIZE);
}

// ʹ�ù������������������������
Vector<Position> minJumps(Position start, Position target) {
	// ��ʼ�����̺�����
	Vector<Vector<int>> board(BOARD_SIZE + 1, Vector<int>(BOARD_SIZE + 1, -1));
	Vector<Vector<Position>> parent(BOARD_SIZE + 1, Vector<Position>(BOARD_SIZE + 1, { -1, -1 }));
	board[start.x][start.y] = 0;

	Queue<Position> q;
	q.push(start);

	while (!q.empty()) {
		Position curr = q.front();
		q.pop();

		if (curr.x == target.x && curr.y == target.y) {
			// �ҵ�Ŀ��λ�ã�����·��
			Vector<Position> path;
			while (!(curr.x == start.x && curr.y == start.y)) {
				path.push_back(curr);
				curr = parent[curr.x][curr.y];
			}
			path.push_back(start);
			return path;
		}

		// ������İ˸�������ƶ�
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

	// û���ҵ�Ŀ��λ�ã����ؿ�·��
	return Vector<Position>();
}

int main() {
	int startX, startY, targetX, targetY;
	cin >> startX >> startY >> targetX >> targetY;

	Position start(startX, startY);
	Position target(targetX, targetY);

	Vector<Position> path = minJumps(start, target);
	if (path.empty()) {
		cout << "û���ҵ�·��." << endl;
	} else {
		cout << "��������: " << path.size() - 1 << endl;
		cout << "·��: ";
		for (int i = path.size() - 1; i >= 0; i--) {
			cout << "(" << path[i].x << ", " << path[i].y << ")";
			if (i != 0) {
				cout << " -> ";
			}
		}
		cout << endl;

		// ��� json ��ʽ��·��
		json json_path;
		for (const auto& pos : path) {
			json_path.push_back({ pos.x, pos.y });
		}
		json result = { {"minJumps", path.size() - 1}, {"path", json_path} };
		cout << result.dump() << endl;
	}

	return 0;
}