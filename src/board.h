#ifndef BOARD
#define BOARD

#include <vector>
#include <iostream>

enum space_state {BLACK, WHITE, EMPTY};

class Board {
    public:
    Board();
    Board(int s);
    ~Board();
    void printBoard();
    int placeStone(int COLOUR, int x, int y);
    int checkAlive(int GROUPCOLOUR, int x, int y, std::vector<std::vector<bool>> &helper);
    int removeGroup(std::vector<std::vector<bool>> helper);
    bool checkPosStatus(int COLOUR, int x, int y);
    int size();

    private:
    std::vector<std::vector<int>> board;
    int s;

};


#endif
