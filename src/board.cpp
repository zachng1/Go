#include "board.h"
#include <QtWidgets>

Board::Board(int s) :
    QGraphicsRectItem(0, 0, (s * 50), (s * 50)),
    squares(std::vector<std::vector<Square *>> (s, std::vector<Square *> (s, nullptr))),
    board(std::vector<std::vector<Intersection *>> (s + 1, std::vector<Intersection *> (s + 1, nullptr))),
    helper(std::vector<std::vector<bool>> (s, std::vector<bool> (s, false))),
    s(s)
{
    QPen pen;
    pen.setStyle(Qt::SolidLine);
    pen.setBrush(Qt::black);
    pen.setWidth(2);
    setPen(pen);
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor::fromRgb(220, 179, 92));
    setBrush(brush);
    for (int i = 0; i < s; i++) {
        for (int j = 0; j < s; j++) {
           squares[j][i] = new Square((j * 50), (i * 50), 50, 50, this);
        }
    }
    for (int i = 0; i < s + 1; i++) {
        for (int j = 0 ; j < s + 1; j++) {
            board[j][i] = new Intersection((j * 50) - 2, (i * 50) - 2, 5, 5, this);
        }
    }
}

//FIX
Board::~Board() {
    for (int i = 0; i < s; i++) {
        for (int j = 0; j < s; j++) {
            delete board[j][i];
        }
    }
}

int Board::placeStone(int COLOUR, int x, int y) {
    if (x * y < 0) return -1; //no negative coords
       if (x >= s || y >= s) return -1; //must be within size

       switch (COLOUR) {
           case EMPTY:
           case BLACK:
           case WHITE: break;
           default: return -1; //have to place black white or empty
       }

       switch (board[x][y]->status) {
           case EMPTY: break;
           default: return -1; //can't place on already existing spot
       }

       board[x][y]->status = COLOUR;
       return 0;
};

//return 0 if group is alive, 1 if dead, and -1 if you are checking an empty group
//if group is dead, helper will be set with co-ords of stones to kill
//helper MUST be reset before calling again
int Board::checkAlive(int GROUPCOLOUR, int x, int y) {
    if (GROUPCOLOUR != WHITE && GROUPCOLOUR != BLACK) return -1; //shouldn't be checking non w/b group
    if (board[x][y]->status == EMPTY) return 0; //if empty reached: alive

    helper[x][y] = true; //mark as checked so we don't get stuck in recursion loop

    //look to all left right up down for empty space, only if not already checked and if not opposite colour
    //these are ugly i know -- but had to separate the first if statement to avoid out of bounds access on board
    if (x + 1 < s) {
        if (board[x + 1][y]->status != !GROUPCOLOUR && !helper[x+1][y]) {
            if (!checkAlive(GROUPCOLOUR, x + 1, y)) return 0;
        }
    }
    if (x - 1 >= 0) {
        if (board[x - 1][y]->status != !GROUPCOLOUR && !helper[x-1][y]) {
            if (!checkAlive(GROUPCOLOUR, x - 1, y)) return 0;
        }
    }
    if (y - 1 >= 0) { 
        if (board[x][y - 1]->status != !GROUPCOLOUR && !helper[x][y-1]) {
            if (!checkAlive(GROUPCOLOUR, x, y - 1)) return 0;
        }
    }
    if (y + 1 < s) {
        if (board[x][y + 1]->status != !GROUPCOLOUR && !helper[x][y+1]) {
            if (!checkAlive(GROUPCOLOUR, x, y + 1)) return 0;
        }
    }
    return 1; //if return 1, group is dead. Helper will also be set with co-ords of all stones to kill
}

int Board::removeGroup() {
    int removed = 0;
    for (int i = 0; i < s; i++) {
        for (int j = 0; j < s; j++) {
            if (helper[j][i]) {
                board[j][i]->status = EMPTY;
                removed++;
            }
        }
    }
    return removed;
}

bool Board::checkPosStatus(int COLOUR, int x, int y) {
    if (board[x][y]->status == COLOUR) {
        return true;
    }
    else return false;
}

int Board::size() {
    return s;
}
