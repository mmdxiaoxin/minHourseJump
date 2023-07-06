#include <iostream>
#include <nlohmann/json.hpp>

#include "Vector.h"
#include "Queue.h"

using namespace std;
using json = nlohmann::json;

class Chessboard {
public:
    struct Position {
        int x;
        int y;
        Position() : x(0), y(0) {}
        Position(int _x, int _y) : x(_x), y(_y) {}
    };

private:
    const int boardSize = 200;
    const int dx[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };
    const int dy[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };

public:
    bool isValid(int x, int y) {
        return (x >= 1 && x <= boardSize && y >= 1 && y <= boardSize);
    }

    Vector<Position> minJumps(Position start, Position target) {
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

    void solve() {
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

            json json_path;
            for (const auto& pos : path) {
                json_path.push_back({ {"x", pos.x}, {"y", pos.y} });
            }
            json result = { {"minJumps", path.size() - 1}, {"start", {{"x", start.x}, {"y", start.y}}}, {"target", {{"x", target.x}, {"y", target.y}}}, {"path", json_path} };
            cout << result.dump() << endl;
        }
    }
};

int main() {
    Chessboard chessboard;
    chessboard.solve();

    return 0;
}
