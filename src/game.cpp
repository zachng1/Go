#include "game.h"

#include <QWidget>

Game::Game(int s, QWidget * parent) : QGraphicsView(parent),
    scene(new QGraphicsScene),
    b(new Board(s)),
    pass(0)
{
    scene->addItem(b);
    setScene(scene);
}

void Game::mousePressEvent(QMouseEvent *event) {
    if (event->button()==Qt::RightButton) {
        pass++;
    }
    else if (event->button()==Qt::LeftButton) {
        pass = 0;
    }
    QGraphicsView::mousePressEvent(event);
}

int Game::passes(){
    return pass;
}

int Game::bscore() {
    int s = b->bscore();
    return s;
}
int Game::wscore() {
    int s = b->wscore();
    return s;
}
