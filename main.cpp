#include <iostream>

#include "Vector.h"
#include "Queue.h"
#include "Chessboard.h"

int main(int argc, char* argv[]) {
	Chessboard chessboard(32);
	chessboard.solve();

	return 0;
}
