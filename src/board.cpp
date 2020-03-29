#include "board.h"
#include <QtWidgets>

Board::Board(int s) :
    QGraphicsRectItem(0, 0, ((s + 1) * (50 + 2)), ((s + 1) * (50 + 2))),
    squares(std::vector<std::vector<Square *>> (s, std::vector<Square *> (s, nullptr))),
    board(std::vector<std::vector<Intersection *>> (s + 1, std::vector<Intersection *> (s + 1, nullptr))),
    helper(std::vector<std::vector<bool>> (s + 1, std::vector<bool> (s + 1, false))),
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
    //set up squares and intersection points
    for (int i = 0; i < s; i++) {
        for (int j = 0; j < s; j++) {
           squares[j][i] = new Square(((j + 0.5) * 51) + 1, ((i + 0.5) * 51) + 1, 50, 50, this);
        }
    }
    for (int i = 0; i < s + 1; i++) {
        for (int j = 0 ; j < s + 1; j++) {
            if ((j == 3 && i == 3) ||
                (j == 9 && i == 3) ||
                (j == 15 && i == 3) ||
                (j == 3 && i == 9) ||
                (j == 3 && i == 15) ||
                (j == 9 && i == 9) ||
                (j == 9 && i == 15) ||
                (j == 15 && i == 9) ||
                    (j == 15 && i == 15)) {
                board[j][i] = new Intersection(Qt::black, ((j + 0.5) * 51) - 12.5, ((i + 0.5) * 51) - 12.5, 25, 25, this);
            }
            else {
                board[j][i] = new Intersection(Qt::transparent, ((j + 0.5) * 51) - 12.5, ((i + 0.5) * 51) - 12.5, 25, 25, this);
            }
            board[j][i]->givePosition(((j + 0.5) * 51), ((i + 0.5) * 51));
            board[j][i]->setCoords(j, i);
        }
    }
}

Board::~Board() {
    for (int i = 0; i < s + 1; i++) {
        for (int j = 0; j < s + 1; j++) {
            delete board[j][i];
        }
    }
    for (int i = 0; i < s; i++) {
        for (int j = 0; j< s; j++) {
            delete squares[j][i];
        }
    }
    delete this;
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
       if (COLOUR != WHITE || COLOUR != BLACK) {
           switch (board[x][y]->Status()) {
               case EMPTY: break;
               default: return -1; //can't place on already existing spot
           }
       }

       board[x][y]->setStatus(COLOUR);
       return 0;
};

//return 0 if group is alive and -1 if you are checking an empty group
//if group is dead, removes group and returns size of group removed
int Board::checkAlive(int GROUPCOLOUR, int x, int y) {
    if (GROUPCOLOUR != WHITE && GROUPCOLOUR != BLACK) return -1; //shouldn't be checking non w/b group: don't need to reset helper bc will only happen on first call
    if (board[x][y]->Status() == EMPTY) {
        resetHelper();
        return 0; //if empty reached: alive
    }

    helper[x][y] = true; //mark as checked so we don't get stuck in recursion loop

    //look to all left right up down for empty space, only if not already checked and if not opposite colour
    //these are ugly i know -- but had to separate the first if statement to avoid out of bounds access on board
    if (x + 1 < s + 1) {
        if (board[x + 1][y]->Status() != !GROUPCOLOUR && !helper[x+1][y]) {
            if (!checkAlive(GROUPCOLOUR, x + 1, y)) {
                resetHelper();
                return 0;
            }
        }
    }
    if (x - 1 >= 0) {
        if (board[x - 1][y]->Status() != !GROUPCOLOUR && !helper[x-1][y]) {
            if (!checkAlive(GROUPCOLOUR, x - 1, y)) {
                resetHelper();
                return 0;
            }
        }
    }
    if (y - 1 >= 0) { 
        if (board[x][y - 1]->Status() != !GROUPCOLOUR && !helper[x][y-1]) {
            if (!checkAlive(GROUPCOLOUR, x, y - 1)) {
                resetHelper();
                return 0;
            }
        }
    }
    if (y + 1 < s + 1) {
        if (board[x][y + 1]->Status() != !GROUPCOLOUR && !helper[x][y+1]) {
            if (!checkAlive(GROUPCOLOUR, x, y + 1)) {
                resetHelper();
                return 0;
            }
        }
    }
    int removed = removeGroup();
    resetHelper();
    return removed;
}

int Board::removeGroup() {
    int removed = 0;
    for (int i = 0; i < s; i++) {
        for (int j = 0; j < s; j++) {
            if (helper[j][i]) {
                board[j][i]->setStatus(EMPTY);
                removed++;
            }
        }
    }
    return removed;
}

bool Board::checkPosStatus(int COLOUR, int x, int y) {
    if (board[x][y]->Status() == COLOUR) {
        return true;
    }
    else return false;
}

int Board::size() {
    return s;
}

void Board::resetHelper() {
    for (int i = 0; i < s+1; i++) {
        for (int j = 0; j < s+1; j++) {
            helper[j][i] = false;
        }
    }
}
