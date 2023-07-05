#include <iostream>
#include <fstream>

#include "Vector.h"
#include "Queue.h"

using namespace std;

class Chessboard {
public:
    struct Position {
        int x;
        int y;
        Position(int _x, int _y) : x(_x), y(_y) {}
    };

private:
    int boardSize;
    Position startPosition;
    Position targetPosition;
    Vector<Vector<bool>> visited;
    const int dx[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };
    const int dy[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };

public:
    Chessboard(int size, Position start, Position target)
        : boardSize(size), startPosition(start), targetPosition(target) {
        visited.resize(boardSize + 1, Vector<bool>(boardSize + 1, false));
    }

    bool isValid(int x, int y) {
        return (x >= 1 && x <= boardSize && y >= 1 && y <= boardSize);
    }

    int minJumps() {
        Queue<pair<Position, int>> q;
        q.push({ startPosition, 0 });
        visited[startPosition.x][startPosition.y] = true;

        while (!q.empty()) {
            Position currPos = q.front().first;
            int currJumps = q.front().second;
            q.pop();

            if (currPos.x == targetPosition.x && currPos.y == targetPosition.y) {
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

    int solve() {
        int minJumpsRequired = minJumps();
        cout << "×îÐ¡ÌøÊý: " << minJumpsRequired << endl;

        return minJumpsRequired;
    }
};

int main() {
	ifstream inputFile("input.txt");
	ofstream outputFile("output.txt");

	int startX, startY, targetX, targetY;
	inputFile >> startX >> startY >> targetX >> targetY;

    Chessboard::Position start(startX, startY);
    Chessboard::Position target(targetX, targetY);

    Chessboard chessboard(200, start, target);

    int result = chessboard.solve();
    outputFile << result << endl;

	inputFile.close();
	outputFile.close();

	return 0;
}
