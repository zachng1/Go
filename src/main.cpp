#include <iostream>
#include "board.h"

void printHelper(std::vector<std::vector<bool>> helper);

int main(int argc, char *argv[]) {
	Board b(5);

	int mode = BLACK;

	b.printBoard();

	while (true) {
		int x, y;
		mode ? std::cout << "WHITE" << std::endl : std::cout << "BLACK" << std::endl;
		std::cout << "Place stone at [x y]:";
		std::cin >> x >> y; 
		std::cout << std::endl;

		if (b.placeStone(mode, x, y) < 0) {
			//clear screen
			std::cout << "\033[2J\033[1;1H"; 
			b.printBoard();
			std::cout << "Invalid position" << std::endl;
			continue;
		}
		//set mode so that next placement will be for other color
		mode = !mode;

		//clear screen
		std::cout << "\033[2J\033[1;1H"; 
		b.printBoard();
	}

	b.placeStone(BLACK, 2, 2);
	b.placeStone(BLACK, 3, 2);
	b.placeStone(BLACK, 4, 2);
	b.placeStone(BLACK, 3, 1);
	b.placeStone(WHITE, 2, 0);
	b.printBoard();

	std::vector<std::vector<bool>> h(5, std::vector<bool>(5));

	int alive = b.checkAlive(BLACK, 3, 2, h);
	std::cout << alive << std::endl; 
	printHelper(h);

	return 0;
}

void printHelper(std::vector<std::vector<bool>> helper) {
	for (uint i = 0; i < helper.size(); i++) {
		for (uint j = 0; j < helper.size(); j++) {
			switch (helper[j][i]) {
				case true:
				printf("!");
				break;
				case false:
				printf("-");
				break;
			}
		}
		printf("\n");
	}
}