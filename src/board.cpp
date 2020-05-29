#include "board.h"
#include <QtWidgets>

Board::Board(int s) :
    QGraphicsRectItem(0, 0, ((s + 1) * (50 + 1)), ((s + 1) * (50 + 1))),
    squares(std::vector<std::vector<Square *>> (s, std::vector<Square *> (s, nullptr))),
    board(std::vector<std::vector<Intersection *>> (s + 1, std::vector<Intersection *> (s + 1, nullptr))), 
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
           squares[j][i] = new Square(((j + 0.5) * (50 + 1)) + 1, ((i + 0.5) * (50 + 1)) + 1, 50, 50, this);
        }
    }

    //add some math to cater for other sizes..
    for (int i = 0; i < s + 1; i++) {
        for (int j = 0 ; j < s + 1; j++) {
            //setting up corner intersections
            if ((j == 3 && i == 3) ||
                (j == 9 && i == 3) ||
                (j == 15 && i == 3) ||
                (j == 3 && i == 9) ||
                (j == 3 && i == 15) ||
                (j == 9 && i == 9) ||
                (j == 9 && i == 15) ||
                (j == 15 && i == 9) ||
                    (j == 15 && i == 15)) {
                board[j][i] = new Intersection(Qt::black, -10, -10, 20, 20, this);
                board[j][i]->setPos((((double) j + 0.5) * (50 + 1)), (((double)i + 0.5) * (50 + 1)));
            }
            else {
                board[j][i] = new Intersection(Qt::transparent, -10, -10, 20, 20, this);
                board[j][i]->setPos((((double)j + 0.5) * (50 + 1)), (((double)i + 0.5) * (50 + 1)));
            }
        }
    }
}

int Board::placeStone(int COLOUR, int x, int y, bool hover) {
    if (x * y < 0) return -1; //no negative coords
    if (x > s || y > s) return -1; //must be within size

    if (COLOUR == EMPTY) {
        board[x][y]->setStatus(EMPTY, false);
        return 0;
    }
    else if (hover){
        board[x][y]->setStatus(COLOUR, false);
        return 0;
    }
    else {
        board[x][y]->setStatus(COLOUR, true);
        return 0;
    }
}

bool Board::checkPosStatus(int COLOUR, int x, int y) {
    if (board[x][y]->status() == COLOUR) {
        return true;
    }
    else return false;
}

bool Board::posPermanent(int x, int y) {
    return board[x][y]->permanent();
}

int Board::size() {
    return s;
}

