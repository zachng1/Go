#include "game.h"

#include <QWidget>

Game::Game(QObject * parent) : QGraphicsScene(parent), b(new Board(18))
{
    this->addItem(b);
}


