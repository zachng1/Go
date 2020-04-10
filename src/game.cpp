#include "game.h"

#include <QWidget>

Game::Game(int s, QWidget * parent) : QGraphicsView(parent),
    scene(new QGraphicsScene),
    board(new Board(s)),
    helper(std::vector<std::vector<bool>> (s + 1, std::vector<bool> (s + 1, false))),
    turn(0), pass(0), s(s),
    hoverx(-1), hovery(-1)
{
    scene->addItem(board);
    setScene(scene);
    setMouseTracking(true);
}

void Game::mousePressEvent(QMouseEvent *event) {
    if (event->button()==Qt::RightButton) {
        pass++;
        turn++;
        //if pass == 2, end game
    }
    else if (event->button()==Qt::LeftButton) {
        pass = 0;
        QPointF position = mapToScene(event->pos());
        //convert coordinates into array indexes
        int x = (int) std::round(((position.x())/ 51) - 0.5);
        int y = (int) std::round(((position.y())/ 51) - 0.5);

        if ( x > s || y > s || x < 0 || y < 0) return;
        if (board->posPermanent(x, y)) return;

        board->placeStone(whosTurn(), x, y);

        if (x + 1 < s + 1) {
            if (board->checkPosStatus(!whosTurn(), x + 1, y) &&
                    checkAlive(!whosTurn(), x + 1, y) > 0) {
                removeGroup();
            }
            resetHelper();
        }
        if (x - 1 >= 0) {
            if (board->checkPosStatus(!whosTurn(), x - 1, y) &&
                    checkAlive(!whosTurn(), x - 1, y) > 0) {
                removeGroup();
            }
            resetHelper();
        }
        if (y + 1 < s + 1) {
            if (board->checkPosStatus(!whosTurn(), x, y + 1) &&
                    checkAlive(!whosTurn(), x, y + 1) > 0) {
                removeGroup();
            }
            resetHelper();
        }
        if (y - 1 >= 0) {
            if (board->checkPosStatus(!whosTurn(), x, y - 1) &&
                    checkAlive(!whosTurn(), x, y - 1) > 0) {
                removeGroup();
            }
            resetHelper();
        }

        //finally, make sure you haven't killed your own group
        //which is an invalid move
        if (checkAlive(whosTurn(), x, y) > 0) {
            std::cout << "oop" << std::endl;
            board->placeStone(EMPTY, x, y);
            return;
        }
        resetHelper();

        turn++;
        //do something with killed here?
    }
    QGraphicsView::mousePressEvent(event);
}

void Game::mouseMoveEvent(QMouseEvent *event) {
    QPointF position = mapToScene(event->pos());

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
        board->placeStone(whosTurn(), hoverx, hovery, true);
    }
    //if mouse is in a new position
    else if (x != hoverx || y != hovery) {
        //if the old position was a hoverstone (aka not a placed one)
        //remove it
        if (!board->posPermanent(hoverx, hovery)) {
            board->placeStone(EMPTY, hoverx, hovery);
        }
        //if the new position was not a placed stone
        //put a hover stone there
        if (!board->posPermanent(x, y)) {
            board->placeStone(whosTurn(), x, y, true);
        }
        //update mouse position indexes
        hoverx = x;
        hovery = y;
    }
}

int Game::passes(){
    return pass;
}

int Game::checkAlive(int GROUPCOLOUR, int x, int y){
    if (GROUPCOLOUR != WHITE && GROUPCOLOUR != BLACK) return -1; //shouldn't be checking non w/b group: don't need to reset helper bc will only happen on first call
    //final return condition -- if we never reach an empty square group is dead
    if (board->checkPosStatus(EMPTY, x, y)) {
        resetHelper();
        return 0; //if empty reached: alive
    }

    helper[x][y] = true; //mark as checked so we don't get stuck in recursion loop

    //look to all left right up down for empty space, only if not already checked and if not opposite colour
    //these are ugly i know -- but had to separate the first if statement to avoid out of bounds access on board
    if (x + 1 < s + 1) {
        if (!board->checkPosStatus(!GROUPCOLOUR, x+1, y) && !helper[x+1][y]) {
            if (!checkAlive(GROUPCOLOUR, x + 1, y)) {
                resetHelper();
                return 0;
            }
        }
    }
    if (x - 1 >= 0) {
        if (!board->checkPosStatus(!GROUPCOLOUR, x-1, y) && !helper[x-1][y]) {
            if (!checkAlive(GROUPCOLOUR, x - 1, y)) {
                resetHelper();
                return 0;
            }
        }
    }
    if (y - 1 >= 0) {
        if (!board->checkPosStatus(!GROUPCOLOUR, x, y-1) && !helper[x][y-1]) {
            if (!checkAlive(GROUPCOLOUR, x, y - 1)) {
                resetHelper();
                return 0;
            }
        }
    }
    if (y + 1 < s + 1) {
        if (!board->checkPosStatus(!GROUPCOLOUR, x, y+1) && !helper[x][y+1]) {
            if (!checkAlive(GROUPCOLOUR, x, y + 1)) {
                resetHelper();
                return 0;
            }
        }
    }
    return 1;
}
int Game::removeGroup() {
    int removed = 0;
    for (int i = 0; i < s + 1; i++) {
        for (int j = 0; j < s + 1; j++) {
            if (helper[j][i]) {
                board->placeStone(EMPTY, j, i, true);
            }
        }
    }
    return removed;
}

void Game::resetHelper() {
    for (int i = 0; i < s+1; i++) {
        for (int j = 0; j < s+1; j++) {
            helper[j][i] = false;
        }
    }
}

int Game::whosTurn() {
    if (turn % 2 == 0) {
        return BLACK;
    }
    else return WHITE;
}
