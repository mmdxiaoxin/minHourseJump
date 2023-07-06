#include <iostream>

#include "Vector.h"
#include "Queue.h"
#include "Chessboard.h"

int main() {
	Chessboard chessboard(16);
	chessboard.solve();

	return 0;
}
