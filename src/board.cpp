#include "board.h"

Board::Board() : board(std::vector<std::vector<int>> (19, std::vector<int> (19, EMPTY))), size(19) {};

Board::Board(int size) : board(std::vector<std::vector<int>> (size, std::vector<int> (size, EMPTY))), size(size) {};

Board::~Board() {};

void Board::printBoard() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int c = board[j][i];
            if (c == BLACK) std::cout << 'b';
            else if (c == WHITE) std::cout << 'w';
            else std::cout << '-';
        }
        std::cout << std::endl;

    }
}

int Board::placeStone(int COLOUR, int x, int y) {
    if (x * y < 0) return -1; //no negative coords
    if (x >= size || y >= size) return -1; //must be within size
        
    switch (COLOUR) {
        case BLACK:
        case WHITE: break;
        default: return -1; //have to place black or white
    }

    switch (board[x][y]) {
        case EMPTY: break;
        default: return -1; //can't place on already existing spot
    }

    board[x][y] = COLOUR;
    return 0;
};

//return 0 if group is alive, 1 if dead, and -1 if you are checking an empty group
//if group is dead, helper will be set with co-ords of stones to kill
//helper MUST be reset before calling again
int Board::checkAlive(int GROUPCOLOUR, int x, int y, std::vector<std::vector<bool>> &helper) {
    if (GROUPCOLOUR != WHITE && GROUPCOLOUR != BLACK) return -1; //shouldn't be checking non w/b group
    if (board[x][y] == EMPTY) return 0; //if empty reached: alive!

    helper[x][y] = true; //mark as checked so w e don't get stuck in recursion loop

    //look to all left right up down for empty space, only if not already checked and if not opposite colour
    //these are ugly i know -- but had to separate the first if statement to avoid out of bounds access on board
    if (x + 1 < size) {
        if (board[x + 1][y] != !GROUPCOLOUR && !helper[x+1][y]) {
            if (!checkAlive(GROUPCOLOUR, x + 1, y, helper)) return 0;
        }
    }
    if (x - 1 >= 0) {
        if (board[x - 1][y] != !GROUPCOLOUR && !helper[x-1][y]) {
            if (!checkAlive(GROUPCOLOUR, x - 1, y, helper)) return 0;
        }
    }
    if (y - 1 >= 0) { 
        if (board[x][y - 1]!= !GROUPCOLOUR && !helper[x][y-1]) {
            if (!checkAlive(GROUPCOLOUR, x, y - 1, helper)) return 0;
        }
    }
    if (y + 1 < size) { 
        if (board[x][y + 1]!= !GROUPCOLOUR && !helper[x][y+1]) {
            if (!checkAlive(GROUPCOLOUR, x, y + 1, helper)) return 0;
        }
    }

    return 1; //if return 1, group is dead. Helper will also be set with co-ords of all stones to kill
}

int Board::removeGroup(std::vector<std::vector<bool>> helper) {

}