#include <iostream>

using namespace std;

// 定义棋盘大小
const int BOARD_SIZE = 200;

// 定义棋盘坐标结构体
struct Position {
	int x;
	int y;
	Position() : x(0), y(0) {}
	Position(int _x, int _y) : x(_x), y(_y) {}
};

// 定义自定义队列
class Queue {
private:
	int front;
	int rear;
	int size;
	Position* data;

public:
	Queue(int maxSize) {
		front = 0;
		rear = -1;
		size = 0;
		data = new Position[maxSize];
	}

	~Queue() {
		delete[] data;
	}

	void enqueue(Position value) {
		data[++rear] = value;
		size++;
	}

	Position dequeue() {
		size--;
		return data[front++];
	}

	bool isEmpty() {
		return size == 0;
	}
};

// 检查坐标是否在棋盘范围内
bool isValid(int x, int y) {
	return (x >= 1 && x <= BOARD_SIZE && y >= 1 && y <= BOARD_SIZE);
}

// 计算马从当前位置到目标位置的最少跳数
int minJumps(Position start, Position target) {
	// 初始化棋盘和跳数
	int** board = new int* [BOARD_SIZE + 1];
	for (int i = 0; i <= BOARD_SIZE; i++) {
		board[i] = new int[BOARD_SIZE + 1];
		for (int j = 0; j <= BOARD_SIZE; j++) {
			board[i][j] = -1;
		}
	}

	board[start.x][start.y] = 0;

	// 使用自定义队列来进行广度优先搜索
	Queue q(BOARD_SIZE * BOARD_SIZE);
	q.enqueue(start);

	while (!q.isEmpty()) {
		Position curr = q.dequeue();

		if (curr.x == target.x && curr.y == target.y) {
			// 找到目标位置
			break;
		}

		// 尝试马的八个方向的移动
		const int dx[] = { 1, 2, 2, 1, -1, -2, -2, -1 };
		const int dy[] = { 2, 1, -1, -2, -2, -1, 1, 2 };

		for (int i = 0; i < 8; i++) {
			int nextX = curr.x + dx[i];
			int nextY = curr.y + dy[i];

			if (isValid(nextX, nextY) && board[nextX][nextY] == -1) {
				board[nextX][nextY] = board[curr.x][curr.y] + 1;
				q.enqueue(Position(nextX, nextY));
			}
		}
	}

	int minJumpsRequired = board[target.x][target.y];

	// 释放内存
	for (int i = 0; i <= BOARD_SIZE; i++) {
		delete[] board[i];
	}
	delete[] board;

	return minJumpsRequired;
}

int main() {
	int startX, startY, targetX, targetY;
	cin >> startX >> startY >> targetX >> targetY;

	Position start(startX, startY);
	Position target(targetX, targetY);

	int minJumpsRequired = minJumps(start, target);
	cout << minJumpsRequired << endl;

	return 0;
}
