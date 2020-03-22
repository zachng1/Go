#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include "board.h"

void printHelper(std::vector<std::vector<bool>> helper);
int getCoords(int &x, int &y);
void invalidPosition(Board b);
void resetHelper(std::vector<std::vector<bool>> &h);
void checkAndRemove(Board &b, int mode, int x, int y, std::vector<std::vector<bool>> &h);

int main_old() {
	//fix
	int size;
	std::cout << "Board size:";
	std::cin >> size; 
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	
	Board b(size);
	
	b.printBoard();
	std::vector<std::vector<bool>> h(size, std::vector<bool>(size, false));

	int mode = BLACK;
	while (true) {
		resetHelper(h);
		int x, y;

		mode ? std::cout << "WHITE" << std::endl : std::cout << "BLACK" << std::endl;
		std::cout << "Place stone at [x y]:";
		if (getCoords(x, y) < 0) {
			invalidPosition(b);
			continue;
		}
		else if (x < 0 || x >= size || y < 0 || y >= size) {
			invalidPosition(b);
			continue;
		}

		if (b.placeStone(mode, x, y) < 0) {
			invalidPosition(b);
			continue;
		}

		if (b.checkAlive(mode, x, y, h) != 0) {
			invalidPosition(b);
			std::cout << "Would kill own group" << std::endl;
			b.placeStone(EMPTY, x, y);
			continue;
		} 
		resetHelper(h);

		//check all adjacent groups and remove
		if (x + 1 < size) {
			checkAndRemove(b, !mode, x + 1, y, h);
			resetHelper(h);
		}
		if (x - 1 >= 0) {
			checkAndRemove(b, !mode, x - 1, y, h);
			resetHelper(h);
		}
		if (y + 1 < size) {
			checkAndRemove(b, !mode, x, y + 1, h);
			resetHelper(h);
		}
		if (y - 1 >= 0) {
			checkAndRemove(b, !mode, x, y - 1, h);
			resetHelper(h);
		}

		//set mode so that next placement will be for other color
		mode = !mode;

		//clear screen
		std::cout << "\033[2J\033[1;1H"; 
		b.printBoard();
		std::cout << std::endl;
	}
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

int getCoords(int &x, int &y) {
	while (true) {
		std::string converter;
		std::stringstream ss;
		std::getline(std::cin, converter);
		ss << converter;
		if (ss >> x >> y) {
			std::string remaining;
			if (ss >> remaining) {
				return -1;
			}
		}
		else {
			return -1;
		}
		return 0;
	}
}

void invalidPosition(Board b) {
	std::cout << "\033[2J\033[1;1H"; 
	b.printBoard();
	std::cout << "Invalid position" << std::endl;
}

void resetHelper(std::vector<std::vector<bool>> &h) {
	size_t size = h.size();
	for (uint i = 0; i < size; i++) {
		for (uint j = 0; j < size; j++) {
			h[j][i] = false;
		}
	}
}

void checkAndRemove(Board &b, int mode, int x, int y, std::vector<std::vector<bool>> &h) {
	if (b.checkPosStatus(mode, x, y)) {
		if (b.checkAlive(mode, x, y, h) != 0) {
			b.removeGroup(h);
		}
	}
}
