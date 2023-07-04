#include <iostream>
#include "Vector.h"
#include "Queue.h"

using namespace std;

// ��������ƶ�����
const int dx[] = { 1, 2, 2, 1, -1, -2, -2, -1 };
const int dy[] = { 2, 1, -1, -2, -2, -1, 1, 2 };

// �������̴�С
const int BOARD_SIZE = 200;

// ������������ṹ��
struct Position {
    int x;
    int y;
    Position(int _x, int _y) : x(_x), y(_y) {}
};

// ��������Ƿ������̷�Χ��
bool isValid(int x, int y) {
    return (x >= 1 && x <= BOARD_SIZE && y >= 1 && y <= BOARD_SIZE);
}

// ������ӵ�ǰλ�õ�Ŀ��λ�õ���������
int minJumps(Position start, Position target) {
    // ��ʼ�����̺�����
    Vector<Vector<int>> board(BOARD_SIZE + 1, Vector<int>(BOARD_SIZE + 1, -1));
    board[start.x][start.y] = 0;

    // ʹ�ù������������������������
    Queue<Position> q;
    q.push(start);

    while (!q.empty()) {
        Position curr = q.front();
        q.pop();

        if (curr.x == target.x && curr.y == target.y) {
            // �ҵ�Ŀ��λ��
            return board[curr.x][curr.y];
        }

        // ������İ˸�������ƶ�
        for (int i = 0; i < 8; i++) {
            int nextX = curr.x + dx[i];
            int nextY = curr.y + dy[i];

            if (isValid(nextX, nextY) && board[nextX][nextY] == -1) {
                board[nextX][nextY] = board[curr.x][curr.y] + 1;
                q.push(Position(nextX, nextY));
            }
        }
    }

    // û���ҵ�Ŀ��λ��
    return -1;
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
