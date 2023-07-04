#include <iostream>
#include "Vector.h"
#include "Queue.h"

using namespace std;

// 定义马的移动方向
const int dx[] = { 1, 2, 2, 1, -1, -2, -2, -1 };
const int dy[] = { 2, 1, -1, -2, -2, -1, 1, 2 };

// 定义棋盘大小
const int BOARD_SIZE = 200;

// 定义棋盘坐标结构体
struct Position {
    int x;
    int y;
    Position() : x(0), y(0) {}
    Position(int _x, int _y) : x(_x), y(_y) {}
};

// 检查坐标是否在棋盘范围内
bool isValid(int x, int y) {
    return (x >= 1 && x <= BOARD_SIZE && y >= 1 && y <= BOARD_SIZE);
}

// 计算马从当前位置到目标位置的最少跳数，并返回路径
Vector<Position> minJumps(Position start, Position target) {
    // 初始化棋盘和跳数
    Vector<Vector<int>> board(BOARD_SIZE + 1, Vector<int>(BOARD_SIZE + 1, -1));
    Vector<Vector<Position>> parent(BOARD_SIZE + 1, Vector<Position>(BOARD_SIZE + 1, {-1, -1}));
    board[start.x][start.y] = 0;

    // 使用广度优先搜索来计算最少跳数
    Queue<Position> q;
    q.push(start);

    while (!q.empty()) {
        Position curr = q.front();
        q.pop();

        if (curr.x == target.x && curr.y == target.y) {
            // 找到目标位置，构建路径
            Vector<Position> path;
            while (!(curr.x == start.x && curr.y == start.y)) {
                path.push_back(curr);
                curr = parent[curr.x][curr.y];
            }
            path.push_back(start);
            return path;
        }

        // 尝试马的八个方向的移动
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

    // 没有找到目标位置，返回空路径
    return Vector<Position>();
}

int main() {
    int startX, startY, targetX, targetY;
    cin >> startX >> startY >> targetX >> targetY;

    Position start(startX, startY);
    Position target(targetX, targetY);

    Vector<Position> path = minJumps(start, target);
    if (path.empty()) {
        cout << "No path found." << endl;
    } else {
        cout << "Minimum jumps required: " << path.size() - 1 << endl;
        cout << "Path: ";
        for (int i = path.size() - 1; i >= 0; i--) {
            cout << "(" << path[i].x << ", " << path[i].y << ")";
            if (i != 0) {
                cout << " -> ";
            }
        }
        cout << endl;
    }

    return 0;
}