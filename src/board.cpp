#include "board.h"
#include <QtWidgets>

Board::Board(int s) :
    QGraphicsRectItem(0, 0, ((s + 1) * (50 + 2)), ((s + 1) * (50 + 2))),
    squares(std::vector<std::vector<Square *>> (s, std::vector<Square *> (s, nullptr))),
    board(std::vector<std::vector<Intersection *>> (s + 1, std::vector<Intersection *> (s + 1, nullptr))),
    helper(std::vector<std::vector<bool>> (s + 1, std::vector<bool> (s + 1, false))),
    s(s),
    turn(0),
    hoverx(-1), hovery(-1)
{
    setAcceptHoverEvents(true);

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
                board[j][i]->setPos((((double) j + 0.5) * 51), (((double)i + 0.5) * 51));
            }
            else {
                board[j][i] = new Intersection(Qt::transparent, -10, -10, 20, 20, this);
                board[j][i]->setPos((((double)j + 0.5) * 51), (((double)i + 0.5) * 51));
            }
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

void Board::hoverStone(int COLOUR, int x, int y) {
    board[x][y]->setStatus(COLOUR, false);
}

void Board::removeHoverStone(int x, int y) {
    board[x][y]->setStatus(EMPTY, false);
}

int Board::placeStone(int COLOUR, int x, int y) {
    if (x * y < 0) return -1; //no negative coords
    if (x > s || y > s) return -1; //must be within size


    switch (COLOUR) {
        case EMPTY:
        case BLACK:
        case WHITE: break;
        default: return -1; //have to place black white or empty
    }
    if (COLOUR != WHITE && COLOUR != BLACK) {
        switch (board[x][y]->status()) {
            case EMPTY: break;
            default: return -1;
            //can't place on already existing spot
        }
    }
    removeHoverStone(x, y);
    board[x][y]->setStatus(COLOUR, true);
    return 0;
}

//return 0 if group is alive and -1 if you are checking an empty group
//if group is dead, return 1 and helper will be set with group to kill
int Board::checkAlive(int GROUPCOLOUR, int x, int y) {
    if (GROUPCOLOUR != WHITE && GROUPCOLOUR != BLACK) return -1; //shouldn't be checking non w/b group: don't need to reset helper bc will only happen on first call
    //final return condition -- if we never reach an empty square group is dead
    if (board[x][y]->status() == EMPTY) {
        resetHelper();
        return 0; //if empty reached: alive
    }

    helper[x][y] = true; //mark as checked so we don't get stuck in recursion loop

    //look to all left right up down for empty space, only if not already checked and if not opposite colour
    //these are ugly i know -- but had to separate the first if statement to avoid out of bounds access on board
    if (x + 1 < s + 1) {
        if (board[x + 1][y]->status() != !GROUPCOLOUR && !helper[x+1][y]) {
            if (!checkAlive(GROUPCOLOUR, x + 1, y)) {
                resetHelper();
                return 0;
            }
        }
    }
    if (x - 1 >= 0) {
        if (board[x - 1][y]->status() != !GROUPCOLOUR && !helper[x-1][y]) {
            if (!checkAlive(GROUPCOLOUR, x - 1, y)) {
                resetHelper();
                return 0;
            }
        }
    }
    if (y - 1 >= 0) { 
        if (board[x][y - 1]->status() != !GROUPCOLOUR && !helper[x][y-1]) {
            if (!checkAlive(GROUPCOLOUR, x, y - 1)) {
                resetHelper();
                return 0;
            }
        }
    }
    if (y + 1 < s + 1) {
        if (board[x][y + 1]->status() != !GROUPCOLOUR && !helper[x][y+1]) {
            if (!checkAlive(GROUPCOLOUR, x, y + 1)) {
                resetHelper();
                return 0;
            }
        }
    }
    return 1;
}

int Board::removeGroup() {
    int removed = 0;
    for (int i = 0; i < s + 1; i++) {
        for (int j = 0; j < s + 1; j++) {
            if (helper[j][i]) {
                board[j][i]->setStatus(EMPTY, false);
                removed++;
            }
        }
    }
    return removed;
}

bool Board::checkPosStatus(int COLOUR, int x, int y) {
    if (board[x][y]->status() == COLOUR) {
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

void Board::hoverMoveEvent(QGraphicsSceneHoverEvent *event) {
    QPointF position = event->lastScenePos();

    //convert coordinates into array indexes
    //the other way is setting hover enter event for intersection
    //but then to get stone colour intersection would need to get info from board
    int x = (int) std::round(((position.x())/ 51) - 0.5);
    int y = (int) std::round(((position.y())/ 51) - 0.5);

    if ( x > s || y > s || x < 0 || y < 0) return;
    //first condition is checking if this is the first hover event when hx and hy = -1 each
    if (hoverx + hovery == -2) {
        hoverx = x;
        hovery = y;
        hoverStone(whosTurn(), hoverx, hovery);
    }
    //if mouse is in a new position
    else if (x != hoverx || y != hovery) {
        //if the old position was a hoverstone (aka not a placed one)
        //remove it
        if (!board[hoverx][hovery]->permanent()) {
            removeHoverStone(hoverx, hovery);
        }
        //if the new position was not a placed stone
        //put a hover stone there
        if (!board[x][y]->permanent()) {
            hoverStone(whosTurn(), x, y);
        }
        //update mouse position indexes
        hoverx = x;
        hovery = y;
    }
}

void Board::mousePressEvent(QGraphicsSceneMouseEvent *event) {

    //debug at any time by setting a breakpoint here
    if (event->button() == Qt::RightButton) {
        return;
    }
    int killed = 0;
    QPointF position = event->lastScenePos();
    //convert coordinates into array indexes
    int x = (int) std::round(((position.x())/ 51) - 0.5);
    int y = (int) std::round(((position.y())/ 51) - 0.5);

    if ( x > s || y > s || x < 0 || y < 0) return;
    if (board[x][y]->permanent()) return;

    placeStone(whosTurn(), x, y);

    if (x + 1 < s + 1) {
        if (board[x+1][y]->status() == !whosTurn() &&
                checkAlive(!whosTurn(), x + 1, y) > 0) {
            killed += removeGroup();
        }
        resetHelper();
    }
    if (x - 1 >= 0) {
        if (board[x-1][y]->status() == !whosTurn() &&
                checkAlive(!whosTurn(), x - 1, y) > 0) {
            killed += removeGroup();
        }
        resetHelper();
    }
    if (y + 1 < s + 1) {
        if (board[x][y+1]->status() == !whosTurn() &&
                checkAlive(!whosTurn(), x, y + 1) > 0) {
            killed += removeGroup();
        }
        resetHelper();
    }
    if (y - 1 >= 0) {
        if (board[x][y-1]->status() == !whosTurn() &&
                checkAlive(!whosTurn(), x, y - 1) > 0) {
            killed += removeGroup();
        }
        resetHelper();
    }

    //finally, make sure you haven't killed your own group
    //which is an invalid move
    if (checkAlive(whosTurn(), x, y) > 0) {
        board[x][y]->setStatus(EMPTY, false);
        return;
    }
    resetHelper();

    turn++;
    //do something with killed here?
}

int Board::whosTurn() {
    if (turn % 2 == 0) {
        return BLACK;
    }
    else return WHITE;
}
