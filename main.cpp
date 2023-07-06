#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

#include "Vector.h"
#include "Queue.h"
#include "Chessboard.h"



int main() {
	Chessboard chessboard;
	chessboard.solve();

	return 0;
}
